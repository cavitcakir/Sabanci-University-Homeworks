`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    00:13:55 11/15/2019 
// Design Name: 
// Module Name:    hybrid_cla 
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
module hybrid_cla(C0,A,B,S,Carry,V);
	input [14:0]A,B;
	input C0;
	output [14:0]S;
	output Carry,V;
	wire b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14,w1,w2,w3,w4;
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
	
	CLA kda1(A[0],A[1],A[2],b0,b1,b2,C0,w1,S[0],S[1],S[2]);
	CLA kda2(A[3],A[4],A[5],b3,b4,b5,w1,w2,S[3],S[4],S[5]);
	CLA kda3 (A[6],A[7],A[8],b6,b7,b8,w2,w3,S[6],S[7],S[8]);
	CLA kda4 (A[9],A[10],A[11],b9,b10,b11,w3,w4,S[9],S[10],S[11]);
	
	wire l1,l2,l3,l4,l5,l6,lc1,lc2;

	assign l1 = A[12] ^ b12;
	assign l2 = A[12] & b12;
	assign l3 = A[13]^b13;
	assign l4 = A[13]&b13;
	assign l5 = A[14]^b14;
	assign l6 = A[14]&b14;

	schm kds1 (l5,l3,l1,l6,l4,l2,C0,lc1,lc2,C3);
	assign S[14] = l1 ^ lc2;
	assign S[13] = lc1 ^ l3;
	assign S[12] = w4 ^ l5;
	
	assign V = lc2 ^ C3;
	assign Carry = C3;

endmodule
