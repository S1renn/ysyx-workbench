module Arbiter (
    //READ
    //to ifu
    //AR
    input  [31:0] i_s_ifu_axi_araddr,
    input         i_s_ifu_axi_arvalid,
    output        o_s_ifu_axi_arready,
    //R
    output [31:0] o_s_ifu_axi_rdata,
    output [ 1:0] o_s_ifu_axi_rresp,
    output        o_s_ifu_axi_rvalid,
    input         i_s_ifu_axi_rready,
    //to lsu
    //AR
    input  [31:0] i_s_lsu_axi_araddr,
    input         i_s_lsu_axi_arvalid,
    output        o_s_lsu_axi_arready,
    //R
    output [31:0] o_s_lsu_axi_rdata,
    output [ 1:0] o_s_lsu_axi_rresp,
    output        o_s_lsu_axi_rvalid,
    input         i_s_lsu_axi_rready,
    //to mem
    //AR
    output [31:0] o_m_mem_axi_araddr,
    output        o_m_mem_axi_arvalid,
    input         i_m_mem_axi_arready,
    //R
    input  [31:0] i_m_mem_axi_rdata,
    input  [ 1:0] i_m_mem_axi_rresp,
    input         i_m_mem_axi_rvalid,
    output        o_m_mem_axi_rready,
    //WRITE
    //to ifu
    //AW
    input  [31:0] i_s_ifu_axi_awaddr,
    input         i_s_ifu_axi_awvalid,
    output        o_s_ifu_axi_awready,
    //W
    input  [31:0] i_s_ifu_axi_wdata,
    input  [ 3:0] i_s_ifu_axi_wstrb,
    input         i_s_ifu_axi_wvalid,
    output        o_s_ifu_axi_wready,
    //B
    output [ 1:0] o_s_ifu_axi_bresp,
    output        o_s_ifu_axi_bvalid,
    input         i_s_ifu_axi_bready,
    //to lsu
    //AW
    input  [31:0] i_s_lsu_axi_awaddr,
    input         i_s_lsu_axi_awvalid,
    output        o_s_lsu_axi_awready,
    //W
    input  [31:0] i_s_lsu_axi_wdata,
    input  [ 3:0] i_s_lsu_axi_wstrb,
    input         i_s_lsu_axi_wvalid,
    output        o_s_lsu_axi_wready,
    //B
    output [ 1:0] o_s_lsu_axi_bresp,
    output        o_s_lsu_axi_bvalid,
    input         i_s_lsu_axi_bready,

    //to mem
    //AW
    output [31:0] o_m_mem_axi_awaddr,
    output        o_m_mem_axi_awvalid,
    input         i_m_mem_axi_awready,
    //W
    output [31:0] o_m_mem_axi_wdata,
    output [ 3:0] o_m_mem_axi_wstrb,
    output        o_m_mem_axi_wvalid,
    input         i_m_mem_axi_wready,
    //B
    input  [ 1:0] i_m_mem_axi_bresp,
    input         i_m_mem_axi_bvalid,
    output        o_m_mem_axi_bready,



    // 0 = IFU, 1 = LSU。外部控制必须从请求开始保持到响应握手结束。
    input owner
);



  //AR
  assign o_m_mem_axi_araddr  = owner ? i_s_lsu_axi_araddr : i_s_ifu_axi_araddr;
  assign o_m_mem_axi_arvalid = owner ? i_s_lsu_axi_arvalid : i_s_ifu_axi_arvalid;
  assign o_s_lsu_axi_arready = owner ? i_m_mem_axi_arready : 0;
  assign o_s_ifu_axi_arready = ~owner ? i_m_mem_axi_arready : 0;
  //R
  assign o_m_mem_axi_rready  = owner ? i_s_lsu_axi_rready : i_s_ifu_axi_rready;
  assign o_s_lsu_axi_rvalid  = owner ? i_m_mem_axi_rvalid : 0;
  assign o_s_ifu_axi_rvalid  = ~owner ? i_m_mem_axi_rvalid : 0;
  assign o_s_lsu_axi_rdata   = owner ? i_m_mem_axi_rdata : 0;
  assign o_s_ifu_axi_rdata   = ~owner ? i_m_mem_axi_rdata : 0;
  assign o_s_lsu_axi_rresp   = owner ? i_m_mem_axi_rresp : 0;
  assign o_s_ifu_axi_rresp   = ~owner ? i_m_mem_axi_rresp : 0;
  //AW
  assign o_m_mem_axi_awaddr  = owner ? i_s_lsu_axi_awaddr : i_s_ifu_axi_awaddr;
  assign o_m_mem_axi_awvalid = owner ? i_s_lsu_axi_awvalid : i_s_ifu_axi_awvalid;
  assign o_s_lsu_axi_awready = owner ? i_m_mem_axi_awready : 0;
  assign o_s_ifu_axi_awready = ~owner ? i_m_mem_axi_awready : 0;
  //W
  assign o_m_mem_axi_wvalid  = owner ? i_s_lsu_axi_wvalid : i_s_ifu_axi_wvalid;
  assign o_s_lsu_axi_wready  = owner ? i_m_mem_axi_wready : 0;
  assign o_s_ifu_axi_wready  = ~owner ? i_m_mem_axi_wready : 0;
  assign o_m_mem_axi_wdata   = owner ? i_s_lsu_axi_wdata : i_s_ifu_axi_wdata;
  assign o_m_mem_axi_wstrb   = owner ? i_s_lsu_axi_wstrb : i_s_ifu_axi_wstrb;
  //B
  assign o_s_lsu_axi_bresp   = owner ? i_m_mem_axi_bresp : 0;
  assign o_s_ifu_axi_bresp   = ~owner ? i_m_mem_axi_bresp : 0;
  assign o_s_lsu_axi_bvalid  = owner ? i_m_mem_axi_bvalid : 0;
  assign o_s_ifu_axi_bvalid  = ~owner ? i_m_mem_axi_bvalid : 0;
  assign o_m_mem_axi_bready  = owner ? i_s_lsu_axi_bready : i_s_ifu_axi_bready;

endmodule

