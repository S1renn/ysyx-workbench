module MEM (
    input clk,

    //data_read
    input rst,

    input [31:0] raddr,
    output reg [31:0] rdata,
    input [3:0] rmask,
    input [3:0] lsu_rmask,
    input [3:0] lsu_wmask,

    input [31:0] waddr,
    input [31:0] wdata,
    input [ 3:0] wmask,


    input is_store,
    input is_load,
    input wen,
    input ren,
    input mem_req_valid,
    //temp
    input [2:0] func3,
    input [6:0] opcode,

    output mem_resp_valid
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

  localparam IDLE  = 2'h0;
  localparam READ  = 2'h1;
  localparam WRITE = 2'h2;
  localparam RESP  = 2'h3;

  reg [ 1:0] state;
  reg [31:0] req_raddr;
  reg [ 3:0] req_rmask;
  reg [31:0] req_waddr;
  reg [ 3:0] req_wmask;
  reg [31:0] req_wdata;
  reg [ 3:0] wait_count;
  /* ---------------- data_read ---------------- */


  always @(posedge clk) begin
    if (rst) begin
      req_waddr <= 0;
      req_wdata <= 0;
      rdata <= 32'b0;
      state <= IDLE;
      req_raddr <= 0;
      req_rmask <= 0;
      req_wmask <= 0;
      mem_resp_valid <= 0;
      wait_count <= 4'h0;
    end else begin
      case (state)
        IDLE: begin
          mem_resp_valid <= 0;
          if (ren && mem_req_valid) begin
            req_raddr <= raddr;
            req_rmask <= is_load ? lsu_rmask : rmask;
            state <= READ;
          end else if (wen && mem_req_valid) begin
            req_waddr <= waddr;
            req_wdata <= wdata;
            req_wmask <= is_store ? lsu_wmask : wmask;
            state <= WRITE;
          end
        end
        READ: begin
          if (wait_count < 15) begin
            wait_count <= wait_count + 1;
          end else begin
            rdata <= pmem_read(req_raddr, {4'b0, req_rmask});
            state <= RESP;
          end
        end
        WRITE: begin
          if (wait_count < 15) begin
            wait_count <= wait_count + 1;
          end else begin
            pmem_write(req_waddr, req_wdata, {4'b0, req_wmask});
            state <= RESP;
          end
        end
        RESP: begin
          wait_count <= 0;
          state <= IDLE;
          mem_resp_valid <= 1;
        end

        default: state <= IDLE;
      endcase
    end
  end

endmodule
