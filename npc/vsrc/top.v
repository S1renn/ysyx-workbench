module top (
    input clk,
    input rst,
    output reg [31:0] pc,
    output reg [31:0] inst,
    output wire [31:0] x10,
    output wire [31:0] x15,
    output wire [31:0] rdata1,
    output wire [31:0] rdata2,
    output wire [31:0] imm

);



  // always @(posedge clk) begin
  //     if (inst == 32'h00002503) begin // 这是 lw a0, 0(a0) 的指令码，你可以根据实际指令改
  //         $display("[Time:%t] PC:%x | GPR_WEN:1 | WADDR:%d | WDATA_FROM_EXU:%x | REAL_MEM_DATA:%x", 
  //                  $time, pc, gpr_waddr, gpr_wdata, mem_rdata);
  //     end
  // end



  wire [31:0] dnpc;
  wire [31:0] mem_wdata;
  wire [3:0] wmask;
  wire [3:0] rmask;
  //wire [31:0] gpr_wdata;
  wire [31:0] mem_inst;
  wire [31:0] mem_rdata;
  wire [31:0] mem_waddr;
  wire [31:0] mem_raddr;
  wire gpr_wen;
  wire gpr_ren;
  wire mem_wen;
  wire mem_ren;
  //wire [31:0] imm;
  wire [4:0] raddr1;
  wire [4:0] raddr2;
  //wire [31:0] rdata1;
  //wire [31:0] rdata2;
  wire inst_valid;

  wire [6:0] opcode;
  wire [2:0] func3;


  //always @(*) begin
  //wb_data = gpr_wdata;
  //end

  //pc
  always @(posedge clk) begin
    if (rst) begin
      pc <= 32'h8000_0000;
    end else begin
      pc <= dnpc;
    end
  end

  IFU inst_fetch (

      .inst    (inst),
      .mem_inst(mem_inst)

  );

  MEM ram (
      .clk(clk),

      //inst_read
      .inst_addr(pc),
      .inst_data(mem_inst),

      //data_read
      .rdata(mem_rdata),
      .raddr(mem_raddr),
      .rmask(rmask),

      //data_write
      .waddr(mem_waddr),
      .wdata(mem_wdata),
      .wmask(wmask),


      .wen(mem_wen),
      .ren(mem_ren)
  );

  IDU inst_decode (
      .gpr_wen(gpr_wen),
      .gpr_ren(gpr_ren),
      .mem_wen(mem_wen),
      .mem_ren(mem_ren),

      .inst      (inst),
      .inst_valid(inst_valid),
      .imm       (imm),
      .rs1       (raddr1),
      .rs2       (raddr2),
      .rd        (gpr_waddr),
      .opcode    (opcode),
      .func3     (func3)
      //.pc         (pc )
  );

  wire [4:0] gpr_waddr;
  wire [31:0] gpr_wdata;
  wire [31:0] gpr_rdata;
  wire [4:0] gpr_raddr;
  wire wen_mtvec;
  wire wen_mepc;
  wire wen_mcause;
  wire wen_mstatus;

  wire [31:0] mepc_wdata;
  wire [31:0] mtvec_rdata;
  wire [31:0] mstatus_rdata;
  //wire [31:0] mstatus_wdata;
  wire [31:0] mcause_rdata;
  //wire [31:0] mcause_wdata;
  wire [31:0] mepc_rdata;
  EXU inst_execute (
      .clk       (clk),
      .rst       (rst),
      .pc        (pc),
      .dnpc      (dnpc),
      .inst_valid(inst_valid | rst),
      .inst      (inst),
      .imm       (imm),
      .rs1       (rdata1),
      .rs2       (rdata2),
      .opcode    (opcode),
      .func3     (func3),
      .gpr_wdata (gpr_wdata),


      .mstatus_rdata(mstatus_rdata),
      .mtvec_rdata  (mtvec_rdata),
      .mepc_rdata   (mepc_rdata),
      .mcause_rdata (mcause_rdata),
      .mstatus_wdata(mstatus_wdata),
      .mtvec_wdata  (mtvec_wdata),

      .mcause_wdata(mcause_wdata),

      .wen_mstatus(wen_mstatus),
      .wen_mtvec  (wen_mtvec),
      .wen_mepc   (wen_mepc),
      .wen_mcause (wen_mcause),
      //.wen_mstatus  ( wen_mstatus),



      .gpr_raddr (gpr_raddr),
      .gpr_rdata (gpr_rdata),
      .mem_wdata (mem_wdata),
      .mem_rdata (mem_rdata),
      .mem_waddr (mem_waddr),
      .mem_raddr (mem_raddr),
      .wmask     (wmask),
      .rmask     (rmask),
      .rd        (gpr_waddr),
      .mepc_wdata(mepc_wdata)


  );

  wire [31:0] mtvec_wdata;
  wire [31:0] mstatus_wdata;
  wire [31:0] mcause_wdata;
  //wire [31:0] mepc_wdata;
  //wire [31:0] final_gpr_wdata = (inst[6:0] == 7'b0000011) ? mem_rdata : gpr_wdata;

  GPR gpr (
      .clk        (clk),
      .rst        (rst),
      .gpr_wen    (gpr_wen),
      .wen_mstatus(wen_mstatus),
      .wen_mtvec  (wen_mtvec),
      .wen_mepc   (wen_mepc),
      .wen_mcause (wen_mcause),

      .mepc_wdata(mepc_wdata),
      .mtvec_rdata(mtvec_rdata),
      .mstatus_rdata(mstatus_rdata),
      .mcause_rdata(mcause_rdata),
      .mstatus_wdata(mstatus_wdata),
      .mcause_wdata(mcause_wdata),
      .mtvec_wdata(mtvec_wdata),
      .mepc_rdata(mepc_rdata),

      .wdata (gpr_wdata),
      .waddr (gpr_waddr),
      .rdata1(rdata1),
      .rdata2(rdata2),
      .raddr1(raddr1),
      .raddr2(raddr2),
      .x10   (x10),
      .x15   (x15)
  );




endmodule
