module MEM (

    input clk,
    input rst,

    //AR
    input  [31:0] i_s_mem_axi_araddr,
    input         i_s_mem_axi_arvalid,
    output        o_s_mem_axi_arready,
    //R
    output [31:0] o_s_mem_axi_rdata,
    output        o_s_mem_axi_rvalid,
    input         i_s_mem_axi_rready,
    output [ 1:0] o_s_mem_axi_rresp,
    //AW
    input  [31:0] i_s_mem_axi_awaddr,
    input         i_s_mem_axi_awvalid,
    output        o_s_mem_axi_awready,
    //W
    input  [31:0] i_s_mem_axi_wdata,
    input  [ 3:0] i_s_mem_axi_wstrb,
    input         i_s_mem_axi_wvalid,
    output        o_s_mem_axi_wready,
    //B
    output [ 1:0] o_s_mem_axi_bresp,
    output        o_s_mem_axi_bvalid,
    input         i_s_mem_axi_bready
);



  /* ---------------- DPI-C 接口 ---------------- */
  // 读内存函数
  import "DPI-C" function int pmem_read(
    input int  raddr,
    input byte rmask
  );

  // 写内存函数
  import "DPI-C" function void pmem_write(
    input int  waddr,
    input int  wdata,
    input byte wmask
  );

  localparam IDLE          = 3'h0;
  localparam READ_WAIT     = 3'h1;
  localparam READ_RESP     = 3'h2;
  localparam WRITE_WAIT    = 3'h3;
  localparam WRITE_COLLECT = 3'h4;
  localparam WRITE_RESP    = 3'h5;

  reg [2:0] state;
  reg [31:0] req_raddr;
  reg [3:0] req_rmask;
  reg [31:0] req_waddr;
  reg [3:0] req_wstrb;
  reg [31:0] req_wdata;
  reg [3:0] wait_count;
  reg got_aw;
  reg got_w;
  reg [31:0] read_data;

  assign o_s_mem_axi_rdata = read_data;
  assign o_s_mem_axi_arready = !rst && (state == IDLE);
  assign o_s_mem_axi_rvalid = (state == READ_RESP);
  assign o_s_mem_axi_awready = !rst && (state == IDLE || (state == WRITE_COLLECT && !got_aw));
  assign o_s_mem_axi_wready = !rst && (state == IDLE || (state == WRITE_COLLECT && !got_w));
  assign o_s_mem_axi_bvalid = !rst && (state == WRITE_RESP);

  assign ar_fire = i_s_mem_axi_arvalid && o_s_mem_axi_arready;
  assign r_fire = o_s_mem_axi_rvalid && i_s_mem_axi_rready;
  assign aw_fire = i_s_mem_axi_awvalid && o_s_mem_axi_awready;
  assign w_fire = o_s_mem_axi_wvalid && i_s_mem_axi_wready;
  assign b_fire = o_s_mem_axi_bvalid && i_s_mem_axi_bready;


  /* ---------------- data_read ---------------- */

  always @(posedge clk) begin
    if (rst) begin
      state <= IDLE;
      got_aw <= 0;
      got_w <= 0;
      wait_count <= 0;
      req_raddr = 0;
      req_waddr = 0;
      req_wstrb = 0;
      req_wdata = 0;

    end else begin
      case (state)
        IDLE: begin
          if (ar_fire) begin
            req_raddr <= i_s_mem_axi_araddr;
            wait_count <= 0;
            state <= READ_WAIT;
          end else if (aw_fire || w_fire) begin
            got_aw <= aw_fire;
            got_w  <= w_fire;
            if (aw_fire) begin
              req_waddr <= i_s_mem_axi_awaddr;
            end
            if (w_fire) begin
              req_wdata <= i_s_mem_axi_wdata;
              req_wstrb <= i_s_mem_axi_wstrb;
            end
            wait_count <= 0;
            if (aw_fire && w_fire) begin
              state <= WRITE_WAIT;
            end else state <= WRITE_COLLECT;
          end
        end
        READ_WAIT: begin
          if (wait_count < 15) begin
            wait_count <= wait_count + 1;
          end else begin
            read_data <= pmem_read(req_raddr, 8'h0f);
            state <= READ_RESP;
          end
        end
        WRITE_COLLECT: begin //数据锁存 在此状态下的数据只锁存了一个通道的 还要锁存另一个通道的
          if (aw_fire) begin
            got_aw <= 1;
            req_waddr <= i_s_mem_axi_awaddr;
          end
          if (w_fire) begin
            got_w <= 1;
            req_wdate <= i_s_mem_axi_wdata;
            req_wstrb <= i_s_mem_axi_wstrb;
          end
          if (got_aw && got_w) state <= WRITE_WAIT;
        end
        WRITE_WAIT: begin
          if (wait_count < 15) begin
            wait_count <= wait_count + 1;
          end else begin
            pmem_write(req_waddr, req_wdata, {4'b0, req_wstrb});
            state <= WRITE_RESP;
          end
        end
        READ_RESP: begin
          if (r_fire) begin
            state <= IDLE;
            wait_count <= 0;
          end
        end
        WRITE_RESP: begin
          if (b_fire) begin
            got_aw <= 0;
            got_w <= 0;
            wait_count <= 0;
            state <= IDLE;
            o_s_mem_axi_bresp <= 1;
          end
        end
        default: state <= IDLE;
      endcase
    end
  end

endmodule
