module LSU (
    input clk,
    input rst,

    input req_valid,
    input is_store,
    input [2:0] func3,
    input [6:0] opcode,
    input [31:0] addr,
    input [31:0] store_data,

    output done,
    output reg [31:0] load_data,

    output mem_req_valid,
    output mem_wen,
    output reg [31:0] mem_addr,
    output reg [31:0] mem_wdata,
    output reg [3:0] mem_wmask,
    output reg [3:0] mem_rmask,

    input mem_resp_valid,
    input [31:0] mem_rdata
);
  assign mem_addr = (opcode == 7'b0000011 || opcode == 7'b0100011) ? {addr[31:2], 2'b00} : 32'b0;
  /*-----------------------store---------------------*/
  always @(*) begin

    mem_wdata = 32'b0;
    mem_wmask = 4'b0;
    if (is_store && opcode == 7'b0100011) begin
      if (func3 == 3'b010) begin
        mem_wdata = store_data;
        mem_wmask = 4'b1111;
      end else if (func3 == 3'b000) begin
        case (addr[1:0])
          2'b00: begin
            mem_wmask = 4'b0001;  // 写第 0 字节
            mem_wdata = {24'b0, store_data[7:0]};  // 将低 8 位放在最低位置
          end
          2'b01: begin
            mem_wmask = 4'b0010;  // 写第 1 字节
            mem_wdata = {16'b0, store_data[7:0], 8'b0};  // 移位到 [15:8]
          end
          2'b10: begin
            mem_wmask = 4'b0100;  // 写第 2 字节
            mem_wdata = {8'b0, store_data[7:0], 16'b0};  // 移位到 [23:16]
          end
          2'b11: begin
            mem_wmask = 4'b1000;  // 写第 3 字节
            mem_wdata = {store_data[7:0], 24'b0};  // 移位到 [31:24]
          end
        endcase
      end else if (func3 == 3'b001) begin
        case (addr[1:0])
          2'b00: begin
            mem_wmask = 4'b0011;
            mem_wdata = {16'b0, store_data[15:0]};  // 移位到 [23:16]
          end
          2'b10: begin
            mem_wmask = 4'b1100;
            mem_wdata = {store_data[15:0], 16'b0};  // 移位到 [23:16]
          end
          default: begin
            mem_wmask = 4'b0000;
            mem_wdata = 32'b0;
          end
        endcase
      end

    end
  end
  /*-----------------------load---------------------*/

  always @(*) begin
    load_data = 32'b0;
    mem_rmask = 4'b0;
    if (!is_store && opcode == 7'b0000011) begin
      if (func3 == 3'b010) begin
        load_data = mem_rdata;
        mem_rmask = 4'b1111;
      end else if (func3 == 3'b000) begin
        case (addr[1:0])
          2'b00: begin
            mem_rmask = 4'b0001;  // 读第 0 字节
            load_data = {{24{mem_rdata[7]}}, mem_rdata[7:0]};  // 符号扩展
          end
          2'b01: begin
            mem_rmask = 4'b0010;  // 读第 1 字节
            load_data = {{24{mem_rdata[15]}}, mem_rdata[15:8]};  // 符号扩展
          end
          2'b10: begin
            mem_rmask = 4'b0100;  // 读第 2 字节
            load_data = {{24{mem_rdata[23]}}, mem_rdata[23:16]};  // 符号扩展
          end
          2'b11: begin
            mem_rmask = 4'b1000;  // 读第 3 字节
            load_data = {{24{mem_rdata[31]}}, mem_rdata[31:24]};  // 符号扩展
          end
        endcase
      end else if (func3 == 3'b001) begin
        case (addr[1:0])
          2'b00: begin
            mem_rmask = 4'b0011;  // 读第 0 和第 1 字节
            load_data = {{16{mem_rdata[15]}}, mem_rdata[15:0]};  // 符号扩展
          end
          2'b10: begin
            mem_rmask = 4'b1100;  // 读第 2 和第 3 字节
            load_data = {{16{mem_rdata[31]}}, mem_rdata[31:16]};  // 符号扩展
          end
          default: begin
            // 非法地址，设置 rmask 为 0，表示不读取任何数据
            mem_rmask = 4'b0000;
            load_data = 32'b0;
          end
        endcase
      end else if (func3 == 3'b101) begin
        case (addr[1:0])
          2'b00: begin
            mem_rmask = 4'b0011;  // 读第 0 和第 1 字节
            load_data = {16'b0, mem_rdata[15:0]};  // 零扩展
          end
          2'b10: begin
            mem_rmask = 4'b1100;  // 读第 2 和第 3 字节
            load_data = {16'b0, mem_rdata[31:16]};  // 零扩展
          end
          default: begin
            // 非法地址，设置 rmask 为 0，表示不读取任何数据
            mem_rmask = 4'b0000;
            load_data = 32'b0;
          end
        endcase

      end else if (func3 == 3'b100) begin
        case (addr[1:0])
          2'b00: begin
            mem_rmask = 4'b0001;  // 读第 0 字节
            load_data = {24'b0, mem_rdata[7:0]};  // 符号扩展
          end
          2'b01: begin
            mem_rmask = 4'b0010;  // 读第 1 字节
            load_data = {24'b0, mem_rdata[15:8]};  // 符号扩展
          end
          2'b10: begin
            mem_rmask = 4'b0100;  // 读第 2 字节
            load_data = {24'b0, mem_rdata[23:16]};  // 符号扩展
          end
          2'b11: begin
            mem_rmask = 4'b1000;  // 读第 3 字节
            load_data = {24'b0, mem_rdata[31:24]};  // 符号扩展
          end

        endcase
      end
    end



  end
endmodule
