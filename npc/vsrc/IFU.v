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
    output ls_req_valid
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
          if (is_load || is_store) state <= LS_WB;
          else state <= FETCH;
        end
        LS_WB:   if (ls_done) state <= FETCH;
        default: state <= FETCH;
      endcase
    end
  end
endmodule

