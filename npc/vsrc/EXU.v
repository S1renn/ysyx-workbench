module EXU (
    input    clk,
    input    rst,
    input [31:0] pc,
    input [31:0] inst,
    input [31:0] imm,
    input [31:0] rs1,
    input [31:0] rs2,
    input [6:0] opcode,
    input [2:0] func3,
    input inst_valid,
    input [4:0] rd,


    input is_store,
    input is_load,

    input [31:0] mstatus_rdata,
    input [31:0] mtvec_rdata,
    input [31:0] mepc_rdata,
    input [31:0] mcause_rdata,

    output reg [31:0] mstatus_wdata,
    output reg [31:0] mtvec_wdata,
    output reg [31:0] mepc_wdata,
    output reg [31:0] mcause_wdata,



    output reg [31:0] dnpc,
    output reg [31:0] gpr_wdata,


    //output reg [1:0] csr_wen,
    output reg wen_mtvec,
    output reg wen_mepc,
    output reg wen_mcause,
    output reg wen_mstatus,


    // output reg [4:0] gpr_waddr,
    output reg [ 4:0] gpr_raddr,
    output reg [31:0] gpr_rdata,
    output reg [31:0] addr,
    output reg [31:0] mem_waddr,
    output reg [31:0] mem_raddr,
    input  reg [31:0] mem_rdata,
    output reg [ 3:0] mem_rmask,
    output reg [ 3:0] mem_wmask,
    output reg [31:0] store_data

);

  import "DPI-C" function void ebreak();
  import "DPI-C" function void invalid_inst_trap(
    int pc,
    int inst
  );

  import "DPI-C" function void log_ftrace(
    input int pc,
    input int target,
    input bit is_ret
  );


  reg [31:0] snpc;
  reg [31:0] alu_res;
  reg [31:0] tmp;

  always @(posedge clk) begin

    // Call 判定: JAL/JALR 且写入 ra (x1)
    // 第三个参数传 1'b0 (false)，表示“不是 Ret”
    if (opcode == 7'h67 && rd == 5'd0 && inst[19:15] == 5'd1) begin
      log_ftrace(pc, dnpc, 1'b1);


    end else if ((opcode == 7'h6f || opcode == 7'h67) && rd == 5'd1) begin
      log_ftrace(pc, dnpc, 1'b0);
    end

  end


  always @(*) begin
    // 防止产生 Latch
    alu_res = 32'b0;
    gpr_wdata = 32'b0;
    mem_wmask = 4'b0000;
    mem_rmask = 4'b0000;
    addr = 32'b0;
    store_data = 32'b0;

    mstatus_wdata = 0;
    mcause_wdata = 0;

    wen_mstatus = 0;
    wen_mtvec = 0;
    wen_mepc = 0;
    wen_mcause = 0;

    snpc = pc + 4;
    dnpc = snpc;





    if (inst_valid) begin

      //ecall

      if (inst == 32'b0000000_00000_00000_000_00000_1110011) begin
        mepc_wdata = pc;
        dnpc = mtvec_rdata;
        mcause_wdata = 32'h0b;
        wen_mcause = 1;
        wen_mepc = 1;
      end

      //mret
      if (inst == 32'h30200073) begin
        dnpc = mepc_rdata;
      end

      //csrrw
      if ((opcode == 7'b1110011) && (func3 == 3'b001)) begin
        case (imm)
          32'h300: begin
            tmp = mstatus_rdata;
          end
          32'h305: begin
            tmp = mtvec_rdata;
          end
          32'h341: begin
            tmp = mepc_rdata;
          end
          32'h342: begin
            tmp = mcause_rdata;
          end
          default: begin
            tmp = 32'b0;
          end
        endcase
        alu_res   = tmp;
        gpr_wdata = alu_res;
        case (imm)
          32'h300: begin
            mstatus_wdata = rs1;
            wen_mstatus   = 1;
          end
          32'h305: begin
            mtvec_wdata = rs1;
            wen_mtvec   = 1;
          end
          32'h341: begin
            mepc_wdata = rs1;
            wen_mepc   = 1;
          end
          32'h342: begin
            mcause_wdata = rs1;
            wen_mcause   = 1;
          end
          default: mcause_wdata = rs1;
        endcase
      end

      //cssrs
      if ((opcode == 7'b1110011) && (func3 == 3'b010)) begin
        case (imm)
          32'h300: begin
            tmp = mstatus_rdata;
          end
          32'h305: begin
            tmp = mtvec_rdata;
          end
          32'h341: begin
            tmp = mepc_rdata;
          end
          32'h342: begin
            tmp = mcause_rdata;
          end
          default: begin
            tmp = 32'b0;
          end
        endcase
        alu_res   = tmp;
        gpr_wdata = alu_res;
        case (imm)
          32'h300: begin
            mstatus_wdata = rs1 | tmp;
            wen_mstatus   = 1;
          end
          32'h305: begin
            mtvec_wdata = rs1 | tmp;
            wen_mtvec   = 1;
          end
          32'h341: begin
            mepc_wdata = rs1 | tmp;
            wen_mepc   = 1;
          end
          32'h342: begin
            mcause_wdata = rs1 | tmp;
            wen_mcause   = 1;
          end
        endcase
      end


      //ebreak
      if (opcode == 7'b1110011 && func3 == 3'b000 && inst[20] == 1) begin
        ebreak();
      end
      //addi
      if (opcode == 7'b0010011 && func3 == 3'b000) begin
        alu_res   = rs1 + imm;
        gpr_wdata = alu_res;
      end
      //xori
      if (opcode == 7'b0010011 && func3 == 3'b100) begin
        alu_res   = rs1 ^ imm;
        gpr_wdata = alu_res;
      end
      //ebreak
      // if (opcode == 7'b1110011 && func3 == 3'b000 && inst[20] == 1)begin ebreak(); end
      //add
      if (opcode == 7'b0110011 && func3 == 3'b000 && inst[30] == 0) begin
        alu_res   = rs1 + rs2;
        gpr_wdata = alu_res;
      end
      //sub
      if (opcode == 7'b0110011 && func3 == 3'b000 && inst[30] == 1) begin
        alu_res   = rs1 - rs2;
        gpr_wdata = alu_res;
      end
      //srai
      if (opcode == 7'b0010011 && func3 == 3'b101 && inst[30] == 1) begin
        alu_res   = $signed(rs1) >>> imm[4:0];
        gpr_wdata = alu_res;
      end
      //andi
      if (opcode == 7'b0010011 && func3 == 3'b111) begin
        alu_res   = rs1 & imm;
        gpr_wdata = alu_res;
      end
      //ori
      if (opcode == 7'b0010011 && func3 == 3'b110) begin
        alu_res   = rs1 | imm;
        gpr_wdata = alu_res;
      end
      //sll
      if (opcode == 7'b0110011 && func3 == 3'b001) begin
        alu_res   = rs1 << rs2[4:0];
        gpr_wdata = alu_res;
      end
      //srl
      if (opcode == 7'b0110011 && func3 == 3'b101 && inst[30] == 0) begin
        alu_res   = rs1 >> rs2[4:0];
        gpr_wdata = alu_res;
      end
      //sra
      if (opcode == 7'b0110011 && func3 == 3'b101 && inst[30] == 1) begin
        alu_res   = $signed(rs1) >>> rs2[4:0];
        gpr_wdata = alu_res;
      end



      //srli
      if (opcode == 7'b0010011 && func3 == 3'b101 && inst[30] == 0) begin
        alu_res   = rs1 >> imm[4:0];
        gpr_wdata = alu_res;
      end

      //slli
      if (opcode == 7'b0010011 && func3 == 3'b001) begin
        alu_res   = rs1 << imm[4:0];
        gpr_wdata = alu_res;
      end

      //div
      //if (opcode == 7'b0110011 && func3 == 3'b100) begin  end

      //xor
      if (opcode == 7'b0110011 && func3 == 3'b100) begin
        alu_res   = rs1 ^ rs2;
        gpr_wdata = alu_res;
      end
      //or
      if (opcode == 7'b0110011 && func3 == 3'b110) begin
        alu_res   = rs1 | rs2;
        gpr_wdata = alu_res;
      end
      //and
      if (opcode == 7'b0110011 && func3 == 3'b111) begin
        alu_res   = rs1 & rs2;
        gpr_wdata = alu_res;
      end
      //sltu
      if (opcode == 7'b0110011 && func3 == 3'b011) begin
        alu_res   = ($unsigned(rs1) < $unsigned(rs2)) ? 32'b1 : 32'b0;
        gpr_wdata = alu_res;
      end
      //slt
      if (opcode == 7'b0110011 && func3 == 3'b010) begin
        alu_res   = ($signed(rs1) < $signed(rs2)) ? 32'b1 : 32'b0;
        gpr_wdata = alu_res;
      end

      //sltiu
      if (opcode == 7'b0010011 && func3 == 3'b011) begin
        alu_res   = ($unsigned(rs1) < $unsigned(imm)) ? 32'b1 : 32'b0;
        gpr_wdata = alu_res;
      end
      //slti
      if (opcode == 7'b0010011 && func3 == 3'b010) begin
        alu_res   = ($signed(rs1) < $signed(imm)) ? 32'b1 : 32'b0;
        gpr_wdata = alu_res;
      end

      //beq
      if (opcode == 7'b1100011 && func3 == 3'b000) begin
        if (rs1 == rs2) dnpc = pc + imm;
      end

      //bne
      if (opcode == 7'b1100011 && func3 == 3'b001) begin
        if (rs1 != rs2) dnpc = pc + imm;
      end

      //bgeu
      if (opcode == 7'b1100011 && func3 == 3'b111) begin
        if ($unsigned(rs1) >= $unsigned(rs2)) dnpc = pc + imm;
      end

      //bge
      if (opcode == 7'b1100011 && func3 == 3'b101) begin
        if ($signed(rs1) >= $signed(rs2)) dnpc = pc + imm;
      end
      //blt
      if (opcode == 7'b1100011 && func3 == 3'b100) begin
        if ($signed(rs1) < $signed(rs2)) dnpc = pc + imm;
      end
      //bltu
      if (opcode == 7'b1100011 && func3 == 3'b110) begin
        if ($unsigned(rs1) < $unsigned(rs2)) dnpc = pc + imm;
      end
      //auipc
      if (opcode == 7'b0010111) begin
        alu_res   = pc + imm;
        gpr_wdata = alu_res;
      end
      //lui
      if (opcode == 7'b0110111) begin
        alu_res   = imm;
        gpr_wdata = alu_res;
      end
      //jal
      if (opcode == 7'b1101111) begin
        alu_res = snpc;
        gpr_wdata = alu_res;
        dnpc = pc + imm;
      end
      //jalr
      if (opcode == 7'b1100111 && func3 == 3'b000) begin
        alu_res = snpc;
        gpr_wdata = alu_res;
        dnpc = (rs1 + imm) & ~32'b1;
      end

      /*--------------------store_kind-------------------*/

      //sw
      if (opcode == 7'b0100011) begin
        addr = rs1 + imm;
        store_data = rs2;
      end
    end

    /*--------------------load_kind-------------------*/
    if (opcode == 7'b0000011) begin
      addr = rs1 + imm;
    end
  end
endmodule
