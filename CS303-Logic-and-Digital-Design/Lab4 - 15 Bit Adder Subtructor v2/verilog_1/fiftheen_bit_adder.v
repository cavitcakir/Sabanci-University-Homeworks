`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:09:10 11/14/2019 
// Design Name: 
// Module Name:    fiftheen_bit_adder 
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
//full_adder(A,B,Cin,S,Carry)
//////////////////////////////////////////////////////////////////////////////////
module fiftheen_bit_adder(C0,A,B,S,Carry,V);
	input [14:0]A,B;
	input C0;
	output [14:0]S;
	output Carry,V;
	wire c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14;
	wire b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14;
	assign b0 = C0 ^ B[0];
	assign b1 = C0 ^ B[1];
	assign b2 = C0 ^ B[2];
	assign b3 = C0 ^ B[3];
	assign b4 = C0 ^ B[4];
	assign b5 = C0 ^ B[5];
	assign b6 = C0 ^ B[6];
	assign b7 = C0 ^ B[7];
	assign b8 = C0 ^ B[8];
	assign b9 = C0 ^ B[9];
	assign b10 = C0 ^ B[10];
	assign b11 = C0 ^ B[11];
	assign b12 = C0 ^ B[12];
	assign b13 = C0 ^ B[13];
	assign b14 = C0 ^ B[14];
	full_adder ad1(A[0],b0,C0,S[0],c1);
	full_adder ad2(A[1],b1,c1,S[1],c2);
	full_adder ad3 (A[2],b2,c2,S[2],c3);
	full_adder ad4 (A[3],b3,c3,S[3],c4);
	full_adder ad5 (A[4],b4,c4,S[4],c5);
	full_adder ad6 (A[5],b5,c5,S[5],c6);
	full_adder ad7 (A[6],b6,c6,S[6],c7);
	full_adder ad8 (A[7],b7,c7,S[7],c8);
	full_adder ad9 (A[8],b8,c8,S[8],c9);
	full_adder ad10 (A[9],b9,c9,S[9],c10);
	full_adder ad11 (A[10],b10,c10,S[10],c11);
	full_adder ad12 (A[11],b11,c11,S[11],c12);
	full_adder ad13 (A[12],b12,c12,S[12],c13); 
	full_adder ad14 (A[13],b13,c13,S[13],c14);
	full_adder ad15 (A[14],b14,c14,S[14],Carry);
	assign V = Carry ^ c14;

endmodule
