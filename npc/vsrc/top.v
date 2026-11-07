module top (
    input clk,
    input rst,
    output reg [31:0] pc,
    output reg [31:0] inst,
    output wire [31:0] x10,
    output wire [31:0] x15,
    output wire [31:0] rdata1,
    output wire [31:0] rdata2,
    output wire [31:0] imm,
    output wire commit

);


  wire is_store;
  wire gpr_write_en = gpr_wen && commit;
  wire mem_read_en;
  wire mem_write_en;
  wire [31:0] dnpc;
  wire [31:0] mem_wdata;
  wire [3:0] mem_wmask;
  wire [3:0] mem_rmask;
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

  wire [6:0] opcode;
  wire [2:0] func3;
  wire inst_valid;

  //pc
  always @(posedge clk) begin
    if (rst) begin
      pc <= 32'h8000_0000;
    end else if (commit) begin
      pc <= dnpc;
    end
  end

  IFU inst_fetch (
      .clk          (clk),
      .rst          (rst),
      .pc           (pc),
      .ifu_rdata    (inst),
      .inst_valid   (inst_valid),
      .commit       (commit),
      .is_load      (is_load),
      .is_store     (is_store),
      .exec_phase   (exec_phase),
      .ls_done      (ls_done),
      .ls_req_valid (ls_req_valid),
      .mem_handshake(mem_handshake),

      .m_axi_araddr (ifu_axi_araddr),
      .m_axi_arvalid(ifu_axi_arvalid),
      .m_axi_arready(ifu_axi_arready),
      .m_axi_rdata  (ifu_axi_rdata),
      .m_axi_rresp  (ifu_axi_rresp),
      .m_axi_rvalid (ifu_axi_rvalid),
      .m_axi_rready (ifu_axi_rready)
  );
  //wire commit;
  wire exec_phase;
  wire mem_rvalid;
  wire ls_req_valid;
  wire ls_done;
  wire mem_req_valid;
  wire mem_handshake;
  LSU u_lsu (
      .clk(clk),
      .rst(rst),

      .req_valid (ls_req_valid),  //cpu -> lsu
      .is_store  (is_store),
      .is_load   (is_load),
      .func3     (func3),
      .addr      (addr),
      .store_data(store_data),

      .done     (ls_done),   //lsu -> cpu
      .load_data(load_data),

      .mem_req_valid(mem_req_valid),  //lsu -> mem
      .mem_wen      (mem_write_en),   //lsu -> mem
      .mem_ren      (mem_read_en),
      .mem_addr     (mem_addr),
      .mem_wdata    (mem_wdata),
      .mem_wmask    (lsu_mem_wmask),
      .mem_rmask    (lsu_mem_rmask),

      .mem_resp_valid(mem_resp_valid),  //mem -> lsu
      //.mem_req_ready (mem_req_ready),
      .mem_rdata     (mem_rdata)
  );
  wire [31:0] load_data;
  wire [31:0] mem_addr;
  wire [3:0] lsu_mem_rmask;
  wire [3:0] lsu_mem_wmask;
  wire [31:0] store_data;
  wire mem_wvalid;

  Arbiter u_Arbiter (
      .i_s_ifu_axi_araddr (i_s_ifu_axi_araddr),
      .i_s_ifu_axi_arvalid(i_s_ifu_axi_arvalid),
      .o_s_ifu_axi_arready(o_s_ifu_axi_arready),
      .o_s_ifu_axi_rdata  (o_s_ifu_axi_rdata),
      .o_s_ifu_axi_rresp  (o_s_ifu_axi_rresp),
      .o_s_ifu_axi_rvalid (o_s_ifu_axi_rvalid),
      .i_s_ifu_axi_rready (i_s_ifu_axi_rready),
      .i_s_lsu_axi_araddr (i_s_lsu_axi_araddr),
      .i_s_lsu_axi_arvalid(i_s_lsu_axi_arvalid),
      .o_s_lsu_axi_arready(o_s_lsu_axi_arready),
      .o_s_lsu_axi_rdata  (o_s_lsu_axi_rdata),
      .o_s_lsu_axi_rresp  (o_s_lsu_axi_rresp),
      .o_s_lsu_axi_rvalid (o_s_lsu_axi_rvalid),
      .i_s_lsu_axi_rready (i_s_lsu_axi_rready),
      .o_m_mem_axi_araddr (o_m_mem_axi_araddr),
      .o_m_mem_axi_arvalid(o_m_mem_axi_arvalid),
      .i_m_mem_axi_arready(i_m_mem_axi_arready),
      .i_m_mem_axi_rdata  (i_m_mem_axi_rdata),
      .i_m_mem_axi_rresp  (i_m_mem_axi_rresp),
      .i_m_mem_axi_rvalid (i_m_mem_axi_rvalid),
      .o_m_mem_axi_rready (o_m_mem_axi_rready),
      .i_s_ifu_axi_awaddr (i_s_ifu_axi_awaddr),
      .i_s_ifu_axi_awvalid(i_s_ifu_axi_awvalid),
      .o_s_ifu_axi_awready(o_s_ifu_axi_awready),
      .i_s_ifu_axi_wdata  (i_s_ifu_axi_wdata),
      .i_s_ifu_axi_wstrb  (i_s_ifu_axi_wstrb),
      .i_s_ifu_axi_wvalid (i_s_ifu_axi_wvalid),
      .o_s_ifu_axi_wready (o_s_ifu_axi_wready),
      .o_s_ifu_axi_bresp  (o_s_ifu_axi_bresp),
      .o_s_ifu_axi_bvalid (o_s_ifu_axi_bvalid),
      .i_s_ifu_axi_bready (i_s_ifu_axi_bready),
      .i_s_lsu_axi_awaddr (i_s_lsu_axi_awaddr),
      .i_s_lsu_axi_awvalid(i_s_lsu_axi_awvalid),
      .o_s_lsu_axi_awready(o_s_lsu_axi_awready),
      .i_s_lsu_axi_wdata  (i_s_lsu_axi_wdata),
      .i_s_lsu_axi_wstrb  (i_s_lsu_axi_wstrb),
      .i_s_lsu_axi_wvalid (i_s_lsu_axi_wvalid),
      .o_s_lsu_axi_wready (o_s_lsu_axi_wready),
      .o_s_lsu_axi_bresp  (o_s_lsu_axi_bresp),
      .o_s_lsu_axi_bvalid (o_s_lsu_axi_bvalid),
      .i_s_lsu_axi_bready (i_s_lsu_axi_bready),
      .o_m_mem_axi_awaddr (o_m_mem_axi_awaddr),
      .o_m_mem_axi_awvalid(o_m_mem_axi_awvalid),
      .i_m_mem_axi_awready(i_m_mem_axi_awready),
      .o_m_mem_axi_wdata  (o_m_mem_axi_wdata),
      .o_m_mem_axi_wstrb  (o_m_mem_axi_wstrb),
      .o_m_mem_axi_wvalid (o_m_mem_axi_wvalid),
      .i_m_mem_axi_wready (i_m_mem_axi_wready),
      .i_m_mem_axi_bresp  (i_m_mem_axi_bresp),
      .i_m_mem_axi_bvalid (i_m_mem_axi_bvalid),
      .o_m_mem_axi_bready (o_m_mem_axi_bready),
      .owner              (owner)
  );


  MEM ram (
      .clk(clk),
      .rst(rst),
      .raddr(mem_addr),
      .rdata(mem_rdata),
      .rmask(mem_rmask),
      .lsu_rmask(lsu_mem_rmask),
      .lsu_wmask(lsu_mem_wmask),
      .waddr(mem_addr),
      .wdata(mem_wdata),
      .wmask(mem_wmask),
      .is_store(is_store),
      .is_load(is_load),
      .wen(mem_write_en),
      .ren(mem_read_en),
      .mem_req_valid(mem_req_valid),
      .func3(func3),
      .opcode(opcode),
      .mem_resp_valid(mem_resp_valid),
      .mem_req_ready(mem_req_ready),
      .mem_handshake(mem_handshake)
  );
  wire mem_resp_valid;
  wire mem_req_ready;

  IDU inst_decode (
      .clk(clk),
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
      .func3     (func3),
      //.pc         (pc )
      .is_store  (is_store),
      .is_load   (is_load)


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
      .inst_valid(inst_valid),
      .inst      (inst),
      .imm       (imm),
      .rs1       (rdata1),
      .rs2       (rdata2),
      .opcode    (opcode),
      .func3     (func3),
      .gpr_wdata (gpr_wdata),
      .store_data(store_data),

      .is_store(is_store),
      .is_load (is_load),

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
      .mem_rdata (mem_rdata),
      .mem_raddr (mem_raddr),
      .mem_waddr (mem_waddr),
      .mem_rmask (mem_rmask),
      .mem_wmask (mem_wmask),
      .addr      (addr),
      .rd        (gpr_waddr),
      .mepc_wdata(mepc_wdata)


  );
  wire  [31:0] addr;

  wire  [31:0] mtvec_wdata;
  wire  [31:0] mstatus_wdata;
  wire  [31:0] mcause_wdata;
  logic [31:0] ifu_axi_araddr;
  logic        ifu_axi_arvalid;
  logic        ifu_axi_rready;
  logic        is_load;

  //wire [31:0] mepc_wdata;
  //wire [31:0] final_gpr_wdata = (inst[6:0] == 7'b0000011) ? mem_rdata : gpr_wdata;

  GPR gpr (
      .clk        (clk),
      .rst        (rst),
      .gpr_wen    (gpr_write_en),
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
      .opcode(opcode),
      .func3(func3),
      .load_data(load_data),
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
