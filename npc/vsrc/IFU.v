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
    input  mem_rvalid,
    input  mem_wvalid
);
  localparam FETCH = 2'h0;
  localparam EXEC = 2'h1;
  localparam LOAD_WB = 2'h2;
  localparam STORE_WB = 2'h3;

  reg [1:0] state;

  import "DPI-C" function int pmem_read(
    input int  raddr,
    input byte rmask
  );
  assign inst_valid = !rst && (((state == EXEC) || (state == LOAD_WB)) || (state == STORE_WB));
  assign commit = !rst && (((state == STORE_WB) && mem_wvalid || (state == LOAD_WB) && mem_rvalid || (state == EXEC) && !is_load && !is_store));
  assign exec_phase = !rst && (state == EXEC);

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
          if (is_load) state <= LOAD_WB;
          else if (is_store) state <= STORE_WB;
          else state <= FETCH;
        end
        LOAD_WB:  if (mem_rvalid) state <= FETCH;
        STORE_WB: if (mem_wvalid) state <= FETCH;
        default:  state <= FETCH;
      endcase
    end
  end
endmodule

