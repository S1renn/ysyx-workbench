`default_nettype none

module IFU (
    input clk,
    input rst,
    input [31:0] pc,
    output reg [31:0] ifu_rdata,
    output inst_valid,

    input  is_load,
    input  is_store,
    output commit,
    output exec_phase,
    input  ls_done,
    output ls_req_valid,
    input  mem_handshake,  // CPU 请求被 LSU 接收，不是 AXI 地址握手。

    // AXI4-Lite Read Address Channel
    output wire [31:0] m_axi_araddr,
    // output wire [ 2:0] ifu_axi_arprot,
    output wire        m_axi_arvalid,
    input  wire        m_axi_arready,

    // AXI4-Lite Read Data Channel
    input  wire [31:0] m_axi_rdata,
    input  wire [ 1:0] m_axi_rresp,
    input  wire        m_axi_rvalid,
    output wire        m_axi_rready
);
  localparam FETCH_ADDR = 2'd0;
  localparam FETCH_DATA = 2'd1;
  localparam EXEC       = 2'd2;
  localparam LS_WB      = 2'd3;

  reg [1:0] state;

  wire ar_fire = m_axi_arvalid && m_axi_arready;
  wire r_fire = m_axi_rvalid && m_axi_rready;

  // PC 只在 commit 时改变，因此地址等待期间保持稳定。
  assign m_axi_araddr = pc;
  assign m_axi_arvalid = !rst && (state == FETCH_ADDR);
  assign m_axi_rready = !rst && (state == FETCH_DATA);
  assign inst_valid = !rst && ((state == EXEC) || (state == LS_WB));
  assign commit = !rst && (((state == LS_WB) && ls_done) ||
                          ((state == EXEC) && !is_load && !is_store));
  assign exec_phase = !rst && (state == EXEC);
  assign ls_req_valid = exec_phase && (is_load || is_store);

  always @(posedge clk) begin
    if (rst) begin
      ifu_rdata <= 32'b0;
      state <= FETCH_ADDR;
    end else begin
      case (state)
        FETCH_ADDR: begin
          if (ar_fire) state <= FETCH_DATA;
        end
        FETCH_DATA: begin
          if (r_fire) begin
            ifu_rdata <= m_axi_rdata;
            state <= EXEC;
          end
        end
        EXEC: begin
          if (is_store || is_load) begin
            if (mem_handshake) state <= LS_WB;
          end else state <= FETCH_ADDR;
        end
        LS_WB: begin
          if (ls_done) state <= FETCH_ADDR;
        end
        default: state <= FETCH_ADDR;
      endcase
    end
  end
endmodule

`default_nettype wire

