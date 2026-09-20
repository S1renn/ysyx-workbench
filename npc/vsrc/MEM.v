module MEM (
    input clk,

    //inst_read
    input  [31:0] inst_addr,
    output [31:0] inst_data,



    //data_read
    input  [31:0] raddr,
    output [31:0] rdata,
    input  [ 3:0] rmask,

    //write
    input [31:0] waddr,
    input [31:0] wdata,
    input [ 3:0] wmask,


    input wen,
    input ren
);



  /* ---------------- DPI-C 接口 ---------------- */
  // 读内存函数
  import "DPI-C" function void pmem_read(
    input  int  raddr,
    output int  rdata,
    input  byte rmask
  );

  // 写内存函数
  import "DPI-C" function void pmem_write(
    input int  waddr,
    input int  wdata,
    input byte wmask
  );




  /* ---------------- inst_read ---------------- */
  reg [31:0] inst_temp;
  always @(*) begin

    pmem_read(inst_addr, inst_temp, 8'b0000_1111);
  end

  assign inst_data = inst_temp;



  /* ---------------- data_read ---------------- */


  /* verilator lint_off UNOPTFLAT */
  reg [31:0] rdata_temp;
  /* verilator lint_on UNOPTFLAT */

  always @(*) begin
    if (ren) pmem_read(raddr, rdata_temp, {4'b0, rmask});

    else rdata_temp = 32'b0;
  end
  assign rdata = rdata_temp;




  /* ---------------- 写操作 (时序逻辑) ---------------- */
  always @(posedge clk) begin
    if (wen) begin
      // 只有 wen 有效时才调用 C++ 写函数
      pmem_write(waddr, wdata, {4'b0, wmask});
    end
  end

endmodule
