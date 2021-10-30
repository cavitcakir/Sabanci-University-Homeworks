`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    23:14:20 11/14/2019 
// Design Name: 
// Module Name:    schm 
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
module schm(P0,P1,P2,G0,G1,G2,C0,C1,C2,C3);
input P0,P1,P2,G0,G1,G2,C0;
output C1,C2,C3;
wire w1,w2,w3,w4,w5,w6;

assign w1 = P0&P1&P2&C0;
assign w2 = P1&P2&G0;
assign w3 = P2&G1;
assign w4 = P0&P1&C0;
assign w5 = P1&G0;
assign w6 = P0&C0;

assign C3 = G2 | w1 | w2 | w3;
assign C2 = w4 | w5 | G1;
assign C1 = w6 | G0;

endmodule
