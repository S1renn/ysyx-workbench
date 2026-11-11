`default_nettype none

module top (
    input clk,
    input rst,
    output reg [31:0] pc,
    output wire [31:0] inst,
    output wire [31:0] x10,
    output wire [31:0] x15,
    output wire [31:0] rdata1,
    output wire [31:0] rdata2,
    output wire [31:0] imm,
    output wire commit
);
  wire is_load;
  wire is_store;
  wire inst_valid;
  wire ls_req_valid;
  wire ls_req_ready;
  wire ls_done;
  wire [1:0] ls_resp;
  wire mem_handshake = ls_req_valid && ls_req_ready;
  wire [31:0] load_data;
  wire [31:0] addr;
  wire [31:0] store_data;
  wire [31:0] dnpc;
  wire [6:0] opcode;
  wire [2:0] func3;
  wire [4:0] raddr1;
  wire [4:0] raddr2;
  wire [4:0] gpr_waddr;
  wire [31:0] gpr_wdata;
  wire gpr_wen;
  wire gpr_write_en = gpr_wen && commit;
  wire wen_mtvec;
  wire wen_mepc;
  wire wen_mcause;
  wire wen_mstatus;
  wire [31:0] mepc_wdata;
  wire [31:0] mtvec_wdata;
  wire [31:0] mstatus_wdata;
  wire [31:0] mcause_wdata;
  wire [31:0] mepc_rdata;
  wire [31:0] mtvec_rdata;
  wire [31:0] mstatus_rdata;
  wire [31:0] mcause_rdata;

  // IFU 只使用读通道，LSU 使用读写五个通道。
  wire [31:0] ifu_axi_araddr;
  wire        ifu_axi_arvalid;
  wire        ifu_axi_arready;
  wire [31:0] ifu_axi_rdata;
  wire [ 1:0] ifu_axi_rresp;
  wire        ifu_axi_rvalid;
  wire        ifu_axi_rready;

  wire [31:0] lsu_axi_araddr;
  wire        lsu_axi_arvalid;
  wire        lsu_axi_arready;
  wire [31:0] lsu_axi_rdata;
  wire [ 1:0] lsu_axi_rresp;
  wire        lsu_axi_rvalid;
  wire        lsu_axi_rready;
  wire [31:0] lsu_axi_awaddr;
  wire        lsu_axi_awvalid;
  wire        lsu_axi_awready;
  wire [31:0] lsu_axi_wdata;
  wire [ 3:0] lsu_axi_wstrb;
  wire        lsu_axi_wvalid;
  wire        lsu_axi_wready;
  wire [ 1:0] lsu_axi_bresp;
  wire        lsu_axi_bvalid;
  wire        lsu_axi_bready;

  wire [31:0] mem_axi_araddr;
  wire        mem_axi_arvalid;
  wire        mem_axi_arready;
  wire [31:0] mem_axi_rdata;
  wire [ 1:0] mem_axi_rresp;
  wire        mem_axi_rvalid;
  wire        mem_axi_rready;
  wire [31:0] mem_axi_awaddr;
  wire        mem_axi_awvalid;
  wire        mem_axi_awready;
  wire [31:0] mem_axi_wdata;
  wire [ 3:0] mem_axi_wstrb;
  wire        mem_axi_wvalid;
  wire        mem_axi_wready;
  wire [ 1:0] mem_axi_bresp;
  wire        mem_axi_bvalid;
  wire        mem_axi_bready;

  // 当前 CPU 串行执行：取指响应完成后才执行，访存完成后才取下一条。
  // LSU 接收请求时取得总线，直到响应握手结束才交还 IFU。
  reg owner;
  always @(posedge clk) begin
    if (rst) owner <= 1'b0;
    else if (mem_handshake) owner <= 1'b1;
    else if (ls_done) owner <= 1'b0;
  end

  always @(posedge clk) begin
    if (rst) pc <= 32'h8000_0000;
    else if (commit) pc <= dnpc;
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
      .exec_phase   (),
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

  LSU_axi u_lsu (
      .clk                (clk),
      .rst                (rst),
      .req_valid          (ls_req_valid),
      .req_ready          (ls_req_ready),
      .inst_type          (is_load),
      .func3              (func3),
      .addr               (addr),
      .store_data         (store_data),
      .done               (ls_done),
      .resp               (ls_resp),
      .load_data          (load_data),
      .o_m_lsu_axi_araddr (lsu_axi_araddr),
      .o_m_lsu_axi_arvalid(lsu_axi_arvalid),
      .i_m_lsu_axi_arready(lsu_axi_arready),
      .i_m_lsu_axi_rdata  (lsu_axi_rdata),
      .i_m_lsu_axi_rresp  (lsu_axi_rresp),
      .i_m_lsu_axi_rvalid (lsu_axi_rvalid),
      .o_m_lsu_axi_rready (lsu_axi_rready),
      .o_m_lsu_axi_awaddr (lsu_axi_awaddr),
      .o_m_lsu_axi_awvalid(lsu_axi_awvalid),
      .i_m_lsu_axi_awready(lsu_axi_awready),
      .o_m_lsu_axi_wdata  (lsu_axi_wdata),
      .o_m_lsu_axi_wstrb  (lsu_axi_wstrb),
      .o_m_lsu_axi_wvalid (lsu_axi_wvalid),
      .i_m_lsu_axi_wready (lsu_axi_wready),
      .i_m_lsu_axi_bresp  (lsu_axi_bresp),
      .i_m_lsu_axi_bvalid (lsu_axi_bvalid),
      .o_m_lsu_axi_bready (lsu_axi_bready)
  );

  Arbiter u_Arbiter (
      .i_s_ifu_axi_araddr (ifu_axi_araddr),
      .i_s_ifu_axi_arvalid(ifu_axi_arvalid),
      .o_s_ifu_axi_arready(ifu_axi_arready),
      .o_s_ifu_axi_rdata  (ifu_axi_rdata),
      .o_s_ifu_axi_rresp  (ifu_axi_rresp),
      .o_s_ifu_axi_rvalid (ifu_axi_rvalid),
      .i_s_ifu_axi_rready (ifu_axi_rready),
      .i_s_lsu_axi_araddr (lsu_axi_araddr),
      .i_s_lsu_axi_arvalid(lsu_axi_arvalid),
      .o_s_lsu_axi_arready(lsu_axi_arready),
      .o_s_lsu_axi_rdata  (lsu_axi_rdata),
      .o_s_lsu_axi_rresp  (lsu_axi_rresp),
      .o_s_lsu_axi_rvalid (lsu_axi_rvalid),
      .i_s_lsu_axi_rready (lsu_axi_rready),
      .i_s_lsu_axi_awaddr (lsu_axi_awaddr),
      .i_s_lsu_axi_awvalid(lsu_axi_awvalid),
      .o_s_lsu_axi_awready(lsu_axi_awready),
      .i_s_lsu_axi_wdata  (lsu_axi_wdata),
      .i_s_lsu_axi_wstrb  (lsu_axi_wstrb),
      .i_s_lsu_axi_wvalid (lsu_axi_wvalid),
      .o_s_lsu_axi_wready (lsu_axi_wready),
      .o_s_lsu_axi_bresp  (lsu_axi_bresp),
      .o_s_lsu_axi_bvalid (lsu_axi_bvalid),
      .i_s_lsu_axi_bready (lsu_axi_bready),
      .i_s_ifu_axi_awaddr (32'b0),
      .i_s_ifu_axi_awvalid(1'b0),
      .o_s_ifu_axi_awready(),
      .i_s_ifu_axi_wdata  (32'b0),
      .i_s_ifu_axi_wstrb  (4'b0),
      .i_s_ifu_axi_wvalid (1'b0),
      .o_s_ifu_axi_wready (),
      .o_s_ifu_axi_bresp  (),
      .o_s_ifu_axi_bvalid (),
      .i_s_ifu_axi_bready (1'b0),
      .o_m_mem_axi_araddr (mem_axi_araddr),
      .o_m_mem_axi_arvalid(mem_axi_arvalid),
      .i_m_mem_axi_arready(mem_axi_arready),
      .i_m_mem_axi_rdata  (mem_axi_rdata),
      .i_m_mem_axi_rresp  (mem_axi_rresp),
      .i_m_mem_axi_rvalid (mem_axi_rvalid),
      .o_m_mem_axi_rready (mem_axi_rready),
      .o_m_mem_axi_awaddr (mem_axi_awaddr),
      .o_m_mem_axi_awvalid(mem_axi_awvalid),
      .i_m_mem_axi_awready(mem_axi_awready),
      .o_m_mem_axi_wdata  (mem_axi_wdata),
      .o_m_mem_axi_wstrb  (mem_axi_wstrb),
      .o_m_mem_axi_wvalid (mem_axi_wvalid),
      .i_m_mem_axi_wready (mem_axi_wready),
      .i_m_mem_axi_bresp  (mem_axi_bresp),
      .i_m_mem_axi_bvalid (mem_axi_bvalid),
      .o_m_mem_axi_bready (mem_axi_bready),
      .owner              (owner)
  );

  MEM ram (
      .clk                (clk),
      .rst                (rst),
      .i_s_mem_axi_araddr (mem_axi_araddr),
      .i_s_mem_axi_arvalid(mem_axi_arvalid),
      .o_s_mem_axi_arready(mem_axi_arready),
      .o_s_mem_axi_rdata  (mem_axi_rdata),
      .o_s_mem_axi_rresp  (mem_axi_rresp),
      .o_s_mem_axi_rvalid (mem_axi_rvalid),
      .i_s_mem_axi_rready (mem_axi_rready),
      .i_s_mem_axi_awaddr (mem_axi_awaddr),
      .i_s_mem_axi_awvalid(mem_axi_awvalid),
      .o_s_mem_axi_awready(mem_axi_awready),
      .i_s_mem_axi_wdata  (mem_axi_wdata),
      .i_s_mem_axi_wstrb  (mem_axi_wstrb),
      .i_s_mem_axi_wvalid (mem_axi_wvalid),
      .o_s_mem_axi_wready (mem_axi_wready),
      .o_s_mem_axi_bresp  (mem_axi_bresp),
      .o_s_mem_axi_bvalid (mem_axi_bvalid),
      .i_s_mem_axi_bready (mem_axi_bready)
  );

  IDU inst_decode (
      .clk(clk),
      .gpr_wen(gpr_wen),
      .gpr_ren(),
      .mem_wen(),
      .mem_ren(),
      .inst      (inst),
      .inst_valid(inst_valid),
      .imm       (imm),
      .rs1       (raddr1),
      .rs2       (raddr2),
      .rd        (gpr_waddr),
      .opcode    (opcode),
      .func3     (func3),
      .is_store  (is_store),
      .is_load   (is_load)
  );

  EXU inst_execute (
      .clk       (clk),
      .rst       (rst),
      .commit    (commit),
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
      .gpr_raddr (),
      .gpr_rdata (),
      .mem_rdata (lsu_axi_rdata),
      .mem_raddr (),
      .mem_waddr (),
      .mem_rmask (),
      .mem_wmask (),
      .addr      (addr),
      .rd        (gpr_waddr),
      .mepc_wdata(mepc_wdata)
  );

  GPR gpr (
      .clk        (clk),
      .rst        (rst),
      .gpr_wen    (gpr_write_en),
      .wen_mstatus(wen_mstatus && commit),
      .wen_mtvec  (wen_mtvec && commit),
      .wen_mepc   (wen_mepc && commit),
      .wen_mcause (wen_mcause && commit),
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

`default_nettype wire
