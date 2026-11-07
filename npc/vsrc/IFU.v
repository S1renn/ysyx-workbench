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
    input  mem_handshake,

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
  localparam FETCH = 2'h0;
  localparam EXEC  = 2'h1;
  localparam LS_WB = 2'h2;

  reg [1:0] state;

  import "DPI-C" function int pmem_read(
    input int  raddr,
    input byte rmask
  );
  assign inst_valid = !rst && (((state == EXEC) || (state == LS_WB)));
  assign commit = !rst && (((state == LS_WB) && ls_done || (state == EXEC) && !is_load && !is_store));
  assign exec_phase = !rst && (state == EXEC);
  assign ls_req_valid = exec_phase && (is_load || is_store);

  always @(posedge clk) begin
    if (rst) begin
      ifu_rdata <= 32'b0;
      state <= FETCH;
    end else begin
      case (state)
        FETCH: begin
          ifu_rdata <= pmem_read(pc, 8'h0f);
          state <= EXEC;
        end
        EXEC: begin
          if (mem_handshake && (is_store || is_load)) begin
            state <= LS_WB;
          end else if (!mem_handshake && (is_store || is_load)) state <= EXEC;
          else state <= FETCH;
        end
        LS_WB: begin
          if (ls_done) state <= FETCH;
        end
        default: state <= FETCH;
      endcase
    end
  end
endmodule

