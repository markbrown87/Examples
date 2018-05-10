/* 	Created by Mark Brown
	Group: Andre Bell and Mark Brown
	Date: 15/11/2017
	Description:
		Design (A) a 16 to 32 bit sign extension unit, (B) 2 input 32-bit MUX, and (C) 2 input 5-bit MUX.	
*/

//Function to extend the sign of a 16bit input to 32bit result
module SignExtension(a, result);
input[15:0] a; //16 bit input
output[31:0] result; //32-bit output

reg[31:0] result;


//this takes the first 16 bits and adds them to result but then extends the
//  last bit a[15] and extends it 16 times to make the result 32bits.
always @(*)
	begin
		result[31:0] <= { {16{a[15]}}, a[15:0] };
	end
endmodule

//32bit 2 to 1 function that simulates a MUX selection between two inputs of 32bits
module Mux32Bit2to1(a, b, op, result);
input[31:0] a, b; //32-bit inputs
input op; 		   //one-bit selection input
output[31:0] result; //32-bit output

reg[31:0] result;

//Takes in the op selection with '0' returning 'b', and '1' returning 'a'
always @(*)
	begin
		result = (op) ? b : a; //test this - assign didn't work correctly last verilog homework
	end
endmodule

//5bit 2 to 1 function that simulates a MUX selection between two inputs of 5bits
module Mux5Bit2to1(a, b, op, result);
input[4:0] a, b; //5bit inputs
input op; //1bit selection input
output[4:0] result; //5bit result

reg[4:0] result;

//Takes in the op selection with '0' returning 'b', and '1' returning 'a'
//  100% the same as above 32bit MUX but for 5bits
always @(*)
	begin
		result = (op) ? b : a;
	end
endmodule