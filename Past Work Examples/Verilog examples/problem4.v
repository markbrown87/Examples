/* 	Created by Mark Brown
	Group: Andre Bell and Mark Brown
	Date: 29/11/2017
	Description:
		register file module that uses two dimensional arrays, datamemory module (again two dim arrays),
		and InstructionMemory module (two dim array).
*/



//Register file where the information is read or written to a word of memory
module RegisterFile(ReadRegister1, ReadRegister2, WriteRegister, WriteData, RegWrite, Clk, ReadData1, ReadData2);
input [4:0] ReadRegister1, ReadRegister2; // Two registers to be read
input [4:0] WriteRegister; // Register address to write into
input [31:0] WriteData; // Data to be written into WriteRegister
input RegWrite; // RegWrite control signal. Data is written only when this signal is enabled
input Clk; // very important!
output [31:0] ReadData1, ReadData2;

reg[31:0] ReadData1, ReadData2;
reg[31:0] array[21:2];

always @(posedge Clk)
	begin
		ReadData1 = array[ReadRegister1];
		ReadData2 = array[ReadRegister2];
		
		if(RegWrite)
		begin
			array[WriteRegister] = WriteData;
		end
	end
endmodule



//Datamemory where data is stored/written 
module DataMemory(Address, WriteData, MemRead, MemWrite, Clk, ReadData);
input [31:0] Address; // 32-bit address to memory.
input [31:0] WriteData; // Data to be written into WriteRegister
input MemRead; // Data in memory location Address is read if this control is set 
input MemWrite; // WriteData is written in Address during positive clock edge if this control is set
input Clk; // very important!
output [31:0] ReadData; // Value read from memory location Address

reg[31:0] ReadData; 
reg[31:0] array[21:2];

always @(posedge Clk)
	begin
		if(MemRead)
		begin
			ReadData = array[Address];
		end
		if(MemWrite)
		begin
			array[Address] = WriteData;
		end
	end
endmodule



//instruction memory bank for running instructions
module InstructionMemory(Address, Clk, Instruction);
input [31:0] Address; // 32-bit address to memory.
input Clk; // very important!
output [31:0] Instruction; // Value read from memory location Address

reg[31:0] Instruction;
reg[31:0] array[21:2];

always @(posedge Clk)
	begin
	
		//add $t0, $s0, $s1
		Instruction = 'b00000010000100010100000000100000;
		array[Address] = Instruction;
	end
endmodule