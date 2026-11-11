`default_nettype none

module LSU_axi (

    input         clk,
    input         rst,
    // CPU 请求：在 req_valid && req_ready 的上升沿保存请求。
    input         req_valid,
    output        req_ready,
    // inst_type: 0 = store, 1 = load；非访存指令令 req_valid = 0。
    input         inst_type,
    input  [ 2:0] func3,
    input  [31:0] addr,
    input  [31:0] store_data,
    // done 表示响应握手；CPU 在该上升沿采样 load_data 和 resp。
    output        done,
    output [ 1:0] resp,
    output reg [31:0] load_data,
    //
    output        o_m_lsu_axi_arvalid,
    input         i_m_lsu_axi_arready,
    output [31:0] o_m_lsu_axi_araddr,

    input         i_m_lsu_axi_rvalid,
    output        o_m_lsu_axi_rready,
    input  [31:0] i_m_lsu_axi_rdata,
    input  [ 1:0] i_m_lsu_axi_rresp,

    input         i_m_lsu_axi_awready,
    output        o_m_lsu_axi_awvalid,
    output [31:0] o_m_lsu_axi_awaddr,

    output        o_m_lsu_axi_wvalid,
    input         i_m_lsu_axi_wready,
    output reg [31:0] o_m_lsu_axi_wdata,
    output reg [ 3:0] o_m_lsu_axi_wstrb,
    //
    input         i_m_lsu_axi_bvalid,
    output        o_m_lsu_axi_bready,
    input  [ 1:0] i_m_lsu_axi_bresp


);
  localparam STORE = 1'b0;
  localparam LOAD  = 1'b1;

  localparam IDLE       = 3'd0;
  localparam READ_ADDR  = 3'd1;
  localparam READ_RESP  = 3'd2;
  localparam WRITE_SEND = 3'd3;
  localparam WRITE_RESP = 3'd4;

  reg [2:0] state;
  reg req_inst_type;
  reg [2:0] req_func3;
  reg [31:0] req_addr;
  reg [31:0] req_store_data;
  reg aw_sent;
  reg w_sent;

  wire req_fire;
  wire ar_fire;
  wire r_fire;
  wire aw_fire;
  wire w_fire;
  wire b_fire;

  assign req_ready = !rst && (state == IDLE);
  assign req_fire = req_valid && req_ready;

  // 保存完整地址用于字节选择；总线访问对齐后的 32 位字。
  assign o_m_lsu_axi_araddr = {req_addr[31:2], 2'b00};
  assign o_m_lsu_axi_awaddr = {req_addr[31:2], 2'b00};
  assign o_m_lsu_axi_arvalid = !rst && (state == READ_ADDR);
  assign o_m_lsu_axi_rready = !rst && (state == READ_RESP);
  assign o_m_lsu_axi_awvalid = !rst && (state == WRITE_SEND) && !aw_sent;
  assign o_m_lsu_axi_wvalid = !rst && (state == WRITE_SEND) && !w_sent;
  assign o_m_lsu_axi_bready = !rst && (state == WRITE_RESP);

  assign ar_fire = o_m_lsu_axi_arvalid && i_m_lsu_axi_arready;
  assign r_fire = i_m_lsu_axi_rvalid && o_m_lsu_axi_rready;
  assign aw_fire = o_m_lsu_axi_awvalid && i_m_lsu_axi_awready;
  assign w_fire = o_m_lsu_axi_wvalid && i_m_lsu_axi_wready;
  assign b_fire = i_m_lsu_axi_bvalid && o_m_lsu_axi_bready;

  // 响应握手就是事务结束；resp 单独表示结果，不把错误响应当成 OKAY。
  assign done = r_fire || b_fire;
  assign resp = (state == READ_RESP) ? i_m_lsu_axi_rresp :
                (state == WRITE_RESP) ? i_m_lsu_axi_bresp : 2'b00;

  always @(posedge clk) begin
    if (rst) begin
      state <= IDLE;
      req_inst_type <= STORE;
      req_func3 <= 3'b0;
      req_addr <= 32'b0;
      req_store_data <= 32'b0;
      aw_sent <= 1'b0;
      w_sent <= 1'b0;
    end else begin
      case (state)
        IDLE: begin
          if (req_fire) begin
            req_inst_type <= inst_type;
            req_func3 <= func3;
            req_addr <= addr;
            req_store_data <= store_data;
            aw_sent <= 1'b0;
            w_sent <= 1'b0;
            state <= (inst_type == LOAD) ? READ_ADDR : WRITE_SEND;
          end
        end
        READ_ADDR: begin
          if (ar_fire) state <= READ_RESP;
        end
        READ_RESP: begin
          if (r_fire) state <= IDLE;
        end
        WRITE_SEND: begin
          if (aw_fire) aw_sent <= 1'b1;
          if (w_fire) w_sent <= 1'b1;
          // 同时考虑以前完成的握手与当前上升沿的握手。
          if ((aw_sent || aw_fire) && (w_sent || w_fire)) state <= WRITE_RESP;
        end
        WRITE_RESP: begin
          if (b_fire) state <= IDLE;
        end
        default: state <= IDLE;
      endcase
    end
  end

  always @(*) begin
    o_m_lsu_axi_wdata = 0;
    o_m_lsu_axi_wstrb = 0;
    if (req_inst_type == STORE) begin
      if (req_func3 == 3'b010) begin
        o_m_lsu_axi_wdata = req_store_data;
        o_m_lsu_axi_wstrb = 4'b1111;
      end else if (req_func3 == 3'b000) begin
        case (req_addr[1:0])
          2'b00: begin
            o_m_lsu_axi_wstrb = 4'b0001;  // 写第 0 字节
            o_m_lsu_axi_wdata = {24'b0, req_store_data[7:0]};  // 将低 8 位放在最低位置
          end
          2'b01: begin
            o_m_lsu_axi_wstrb = 4'b0010;  // 写第 1 字节
            o_m_lsu_axi_wdata = {16'b0, req_store_data[7:0], 8'b0};  // 移位到 [15:8]
          end
          2'b10: begin
            o_m_lsu_axi_wstrb = 4'b0100;  // 写第 2 字节
            o_m_lsu_axi_wdata = {8'b0, req_store_data[7:0], 16'b0};  // 移位到 [23:16]
          end
          2'b11: begin
            o_m_lsu_axi_wstrb = 4'b1000;  // 写第 3 字节
            o_m_lsu_axi_wdata = {req_store_data[7:0], 24'b0};  // 移位到 [31:24]
          end
        endcase
      end else if (req_func3 == 3'b001) begin
        case (req_addr[1:0])
          2'b00: begin
            o_m_lsu_axi_wstrb = 4'b0011;
            o_m_lsu_axi_wdata = {16'b0, req_store_data[15:0]};  // 半字放在对应的数据通道
          end
          2'b10: begin
            o_m_lsu_axi_wstrb = 4'b1100;
            o_m_lsu_axi_wdata = {req_store_data[15:0], 16'b0};  // 半字放在对应的数据通道
          end
          default: begin
            o_m_lsu_axi_wstrb = 4'b0000;
            o_m_lsu_axi_wdata = 32'b0;
          end
        endcase
      end

    end
  end
  /*-----------------------load---------------------*/

  always @(*) begin
    load_data = 32'b0;
    // load_data 只在读响应阶段有意义，CPU 在 done 有效的上升沿采样。
    if (!rst && state == READ_RESP && req_inst_type == LOAD) begin
      if (req_func3 == 3'b010) begin
        load_data = i_m_lsu_axi_rdata;
      end else if (req_func3 == 3'b000) begin
        case (req_addr[1:0])
          2'b00: begin
            load_data = {{24{i_m_lsu_axi_rdata[7]}}, i_m_lsu_axi_rdata[7:0]};  // 符号扩展
          end
          2'b01: begin
            load_data = {{24{i_m_lsu_axi_rdata[15]}}, i_m_lsu_axi_rdata[15:8]};  // 符号扩展
          end
          2'b10: begin
            load_data = {{24{i_m_lsu_axi_rdata[23]}}, i_m_lsu_axi_rdata[23:16]};  // 符号扩展
          end
          2'b11: begin
            load_data = {{24{i_m_lsu_axi_rdata[31]}}, i_m_lsu_axi_rdata[31:24]};  // 符号扩展
          end
        endcase
      end else if (req_func3 == 3'b001) begin
        case (req_addr[1:0])
          2'b00: begin
            load_data = {{16{i_m_lsu_axi_rdata[15]}}, i_m_lsu_axi_rdata[15:0]};  // 符号扩展
          end
          2'b10: begin
            load_data = {{16{i_m_lsu_axi_rdata[31]}}, i_m_lsu_axi_rdata[31:16]};  // 符号扩展
          end
          default: begin
            // 保留原来的半字对齐约定，不支持跨字访问
            load_data = 32'b0;
          end
        endcase
      end else if (req_func3 == 3'b101) begin
        case (req_addr[1:0])
          2'b00: begin
            load_data = {16'b0, i_m_lsu_axi_rdata[15:0]};  // 零扩展
          end
          2'b10: begin
            load_data = {16'b0, i_m_lsu_axi_rdata[31:16]};  // 零扩展
          end
          default: begin
            // 保留原来的半字对齐约定，不支持跨字访问
            load_data = 32'b0;
          end
        endcase

      end else if (req_func3 == 3'b100) begin
        case (req_addr[1:0])
          2'b00: begin
            load_data = {24'b0, i_m_lsu_axi_rdata[7:0]};  // 零扩展
          end
          2'b01: begin
            load_data = {24'b0, i_m_lsu_axi_rdata[15:8]};  // 零扩展
          end
          2'b10: begin
            load_data = {24'b0, i_m_lsu_axi_rdata[23:16]};  // 零扩展
          end
          2'b11: begin
            load_data = {24'b0, i_m_lsu_axi_rdata[31:24]};  // 零扩展
          end

        endcase
      end
    end
  end

endmodule

`default_nettype wire
