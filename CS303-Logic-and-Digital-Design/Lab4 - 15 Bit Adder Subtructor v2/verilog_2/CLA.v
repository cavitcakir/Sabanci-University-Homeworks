`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    23:27:55 11/14/2019 
// Design Name: 
// Module Name:    CLA 
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
module CLA(A0,A1,A2,B0,B1,B2,C0,C3,S0,S1,S2);
input A0,A1,A2,B0,B1,B2,C0;
output C3,S0,S1,S2;
wire w1,w2,w3,w4,w5,w6,wc1,wc2;

assign w1 = A2 ^ B2;
assign w2 = A2 & B2;
assign w3 = A1^B1;
assign w4 = A1&B1;
assign w5 = A0^B0;
assign w6 = A0&B0;

schm kds2 (w5,w3,w1,w6,w4,w2,C0,wc1,wc2,C3);
assign S2 = w1 ^ wc2;
assign S1 = wc1 ^ w3;
assign S0 = C0 ^ w5;

endmodule
