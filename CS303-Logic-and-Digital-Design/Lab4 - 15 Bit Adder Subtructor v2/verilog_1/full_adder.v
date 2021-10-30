`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:32:54 11/14/2019 
// Design Name: 
// Module Name:    full_adder 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module full_adder(A,B,Cin,S,Carry);
	input A,B,Cin;
	output S,Carry;
	wire w1,w2,w3;
	assign w1 = A^B;
	assign S = w1 ^ Cin;
	assign w2 = w1 & Cin;
	assign w3 = A & B;
	assign Carry = w2 | w3;
endmodule
