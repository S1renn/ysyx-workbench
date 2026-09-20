module GPR (
    input clk,
    input rst,
    input gpr_wen,
    input wen_mstatus,
    input wen_mtvec,
    input wen_mepc,
    input wen_mcause,
    input [4:0] waddr,
    input [31:0] wdata,
    input [4:0] raddr1,
    input [4:0] raddr2,

    input [31:0] mepc_wdata,
    input [31:0] mtvec_wdata,
    output reg [31:0] mstatus_rdata,
    output reg [31:0] mcause_rdata,
    output reg [31:0] mtvec_rdata,
    input [31:0] mstatus_wdata,
    input [31:0] mcause_wdata,
    output reg [31:0] mepc_rdata,

    output [31:0] rdata1,
    output [31:0] rdata2,
    output [31:0] x10,
    output [31:0] x15


);


  import "DPI-C" function void set_gpr_ptr(input logic [31:0] a[]);
  initial begin
    // 这里的 x 必须对应你定义的 reg [31:0] x [31:0];
    set_gpr_ptr(x[0]);
  end


  reg [31:0] x[31:0];
  reg [31:0] mcycle;
  reg [31:0] mcycleh;
  reg [31:0] mvendorid;
  reg [31:0] marchid;
  reg [31:0] mepc;
  reg [31:0] mtvec;
  reg [31:0] mcause;
  reg [31:0] mstatus;


  always @(posedge clk) begin
    if (rst) begin
      mtvec <= 32'b0;
      mepc <= 32'b0;
      mcause <= 32'b0;
      mstatus <= 32'h1800;  //to pass difftest
    end else begin
      // 使用独立的 if，互不干扰
      if (wen_mtvec) mtvec <= mtvec_wdata;
      if (wen_mepc) mepc <= mepc_wdata;
      if (wen_mcause) mcause <= mcause_wdata;
      if (wen_mstatus) mstatus <= mstatus_wdata;
    end
  end




  // r(x0) = 0
  assign mstatus_rdata = mstatus;
  assign mtvec_rdata = mtvec;
  assign mepc_rdata = mepc;
  assign mcause_rdata = mcause;

  assign rdata1 = (raddr1 == 5'b0) ? 32'b0 : x[raddr1];
  assign rdata2 = (raddr2 == 5'b0) ? 32'b0 : x[raddr2];

  assign x10 = x[10];
  assign x15 = x[15];



  always @(posedge clk) begin
    if (gpr_wen && (waddr != 5'b0)) begin
      x[waddr] <= wdata;
      //$display("[WB] Time:%t | Reg[%d] <- %h", $time, waddr, wdata);
    end

    //   if (gpr_wen && waddr == 5'd15) begin
    //     $display("[RF-Write] x15(a5) gets value: %x", wdata);
    //  end
  end

endmodule
