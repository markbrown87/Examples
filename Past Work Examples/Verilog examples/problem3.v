/* 	Created by Mark Brown
	Group: Andre Bell and Mark Brown
	Date: 15/11/2017
	Description:
		Design (A) the control logic and (B) control logic for ALU
*/

//Control function for Control Logic
module Control(opcode, ALUSrc, ALUOp, RegDst, MemWrite, MemRead, Branch, Jump, MemToReg, RegWrite);
input[5:0] opcode; //6 bit operation code
output ALUSrc, RegDst, MemWrite, MemRead, Branch, Jump, MemToReg, RegWrite; // output control lines
output[1:0] ALUOp; // 2bit intermediate output for controlling ALU

reg ALUSrc, RegDst, MemWrite, MemRead, Branch, Jump, MemToReg, RegWrite;
reg [1:0] ALUOp;

always @(*)
	begin	
		//R-type
		if(opcode == 6'b000000)
		begin
			 ALUOp = 2'b10;
			 ALUSrc = 0;
			 RegDst = 1;
			 MemWrite = 0;
			 MemRead = 0;
			 Branch = 0;
			 Jump = 0;
			 MemToReg = 0;
			 RegWrite = 1;
		end
			
		//SW 
		else if(opcode == 6'b101011)
		begin
			 ALUOp = 2'b00;
			 ALUSrc = 1;
			 RegDst = 0;
			 MemWrite = 1;
			 MemRead = 0;
			 Branch = 0;
			 Jump = 0;
			 MemToReg = 0;
			 RegWrite = 0;
		end
			
		//LW
		else if(opcode == 6'b100011)
		begin
			 ALUOp = 2'b00;
			 ALUSrc = 1;
			 RegDst = 0;
			 MemWrite = 0;
			 MemRead = 1;
			 Branch = 0;
			 Jump = 0;
			 MemToReg = 1;
			 RegWrite = 1;
		end
			
		//Branch
		else if(opcode == 6'b000100)
		begin
			 ALUOp = 2'b01;
			 ALUSrc = 0;
			 RegDst = 0;
			 MemWrite = 0;
			 MemRead = 0;
			 Branch = 1;
			 Jump = 0;
			 MemToReg = 0;
			 RegWrite = 0;
		end
			
		//Jump
		else if(opcode == 6'b000010)
		begin
			 ALUOp = 2'b10;
			 ALUSrc = 0;
			 RegDst = 0;
			 MemWrite = 0;
			 MemRead = 0;
			 Branch = 0;
			 Jump = 1;
			 MemToReg = 0;
			 RegWrite = 0;
		end
	end
endmodule


//Control function for Control ALU logic
module ALUOpToALUControl(ALUOp, Funct, ALUControl);
input[1:0] ALUOp; // From the above control
input[5:0] Funct; // From the instruction
output[3:0] ALUControl; // to ALU (HW3B): (ainv, binv, op[1:0])

reg[3:0] ALUControl;

always @(*)
	begin
		//StoreWrod/LoadWord
		if(ALUOp == 2'b00)
		begin
			 ALUControl = 4'b0010;
		end
		
		//Branch
		else if(ALUOp == 2'b01)
		begin
			 ALUControl = 4'b0110;
		end
			
		//R-Type
		else if(ALUOp == 2'b10)
		begin
		
			//And operation
			if(Funct == 6'b100100)
			begin
				 ALUControl = 4'b0000;
			end
				
			//Or operation
			else if(Funct == 6'b100101)
			begin
				 ALUControl = 4'b0001;
			end
				
			//Add operation
			else if(Funct == 6'b100000)
			begin
				 ALUControl = 4'b0010;
			end
				
			//Sub operation
			else if(Funct == 6'b100010)
			begin
				 ALUControl = 4'b0110;
			end
				
			//SLT operation
			else if(Funct == 6'b101010)
			begin
				 ALUControl = 4'b0111;
			end
		end
	end
endmodule