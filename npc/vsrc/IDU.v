module IDU (
    input clk,
    input [31:0] inst,
    input inst_valid,
    //input [31:0] pc,
    output reg gpr_wen,
    output reg mem_wen,
    output reg mem_ren,
    output reg gpr_ren,

    output reg [31:0] imm,
    output reg [ 4:0] rs1,
    output reg [ 4:0] rs2,
    output reg [ 4:0] rd,
    output reg [ 6:0] opcode,
    output reg [ 2:0] func3,

    output reg is_store,
    output reg is_load


);


  reg [2:0] inst_type;

  parameter I_TYPE = 3'b000;
  parameter R_TYPE = 3'b001;
  parameter U_TYPE = 3'b010;
  parameter J_TYPE = 3'b100;
  parameter S_TYPE = 3'b101;
  parameter B_TYPE = 3'b110;

  // Wire helper fields
  wire [6:0] op = inst[6:0];
  wire [2:0] f3 = inst[14:12];

  always @(*) begin
    // Default values
    //inst_valid = 1'b0;
    gpr_wen = 1'b0;
    mem_wen = 1'b0;
    mem_ren = 1'b0;
    gpr_ren = 1'b0;  // Added missing default
    inst_type = 3'b000;
    opcode = op;
    func3 = f3;
    imm = 32'b0;
    rs1 = 5'b0;
    rs2 = 5'b0;
    rd = 5'b0;
    is_store = 0;
    is_load = 0;

    if (inst_valid) begin
      // Decoding based on Opcode (7-bit)
      case (op)
        // --- U-TYPE ---
        // lui (0110111)
        7'b0110111: begin
          //inst_valid = 1'b1;
          gpr_wen   = 1'b1;
          inst_type = U_TYPE;
        end
        // auipc (0010111)
        7'b0010111: begin
          //inst_valid = 1'b1;
          gpr_wen   = 1'b1;
          inst_type = U_TYPE;
        end

        // --- J-TYPE ---
        // jal (1101111)
        7'b1101111: begin
          //inst_valid = 1'b1;
          gpr_wen   = 1'b1;
          inst_type = J_TYPE;
        end

        // --- I-TYPE ---
        // jalr (1100111)
        7'b1100111: begin
          //inst_valid = 1'b1;
          gpr_wen   = 1'b1;
          inst_type = I_TYPE;
          gpr_ren   = 1'b1;  // reads rs1
        end
        // load (0000011): lb, lh, lw, lbu, lhu
        7'b0000011: begin
          //inst_valid = 1'b1;
          gpr_wen   = 1'b1;
          mem_ren   = 1'b1;
          inst_type = I_TYPE;
          gpr_ren   = 1'b1;  // reads rs1
          is_load   = 1;
        end
        // OP-IMM (0010011): addi, slti, sltiu, xori, ori, andi, slli, srli, srai
        7'b0010011: begin
          //inst_valid = 1'b1;
          gpr_wen   = 1'b1;
          inst_type = I_TYPE;
          gpr_ren   = 1'b1;  // reads rs1
        end
        // SYSTEM (1110011): ecall, ebreak, csrrw, csrrs
        7'b1110011: begin
          //inst_valid = 1'b1;
          inst_type = I_TYPE;

          // Check func3 for environment calls vs CSRs
          if (f3 == 3'b000) begin

            gpr_wen = 1'b0;
            gpr_ren = 1'b0;
          end else begin
            // csrrw, csrrs etc write to GPR and read rs1
            gpr_wen = 1'b1;
            gpr_ren = 1'b1;
          end
        end

        // --- S-TYPE ---
        // store (0100011): sb, sh, sw
        7'b0100011: begin
          //inst_valid = 1'b1;
          mem_wen   = 1'b1;
          inst_type = S_TYPE;
          gpr_ren   = 1'b1;
          is_store  = 1;
        end

        // --- B-TYPE ---
        // branch (1100011): beq, bne, blt, bge, bltu, bgeu
        7'b1100011: begin
          //inst_valid = 1'b1;
          inst_type = B_TYPE;
          gpr_ren   = 1'b1;  // reads rs1, rs2 for comparison
        end

        // --- R-TYPE ---
        // OP (0110011): add, sub, sll, slt, sltu, xor, srl, sra, or, and
        7'b0110011: begin
          //inst_valid = 1'b1;
          gpr_wen   = 1'b1;
          inst_type = R_TYPE;
          gpr_ren   = 1'b1;  // reads rs1, rs2
        end

        default: begin
          //inst_valid = 1'b0;
        end
      endcase


      // Generate Immediates and Signals based on Type
      case (inst_type)
        I_TYPE: begin
          imm = {{20{inst[31]}}, inst[31:20]};
          rs1 = inst[19:15];
          rd  = inst[11:7];
        end
        R_TYPE: begin
          rs1 = inst[19:15];
          rs2 = inst[24:20];
          rd  = inst[11:7];
        end
        U_TYPE: begin
          imm = {inst[31:12], 12'b0};
          rd  = inst[11:7];
        end
        J_TYPE: begin
          imm = {{12{inst[31]}}, inst[19:12], inst[20], inst[30:21], 1'b0};
          rd  = inst[11:7];
        end
        S_TYPE: begin
          imm = {{20{inst[31]}}, inst[31:25], inst[11:7]};
          rs1 = inst[19:15];
          rs2 = inst[24:20];
        end
        B_TYPE: begin
          imm = {{20{inst[31]}}, inst[7], inst[30:25], inst[11:8], 1'b0};
          rs1 = inst[19:15];
          rs2 = inst[24:20];
        end
        default: begin
          imm = 32'b0;
          rs1 = 5'b0;
          rd  = 5'b0;
        end
      endcase
    end

  end

endmodule
