`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   01:14:33 11/15/2019
// Design Name:   hybrid_cla
// Module Name:   C:/Users/veyseler/Desktop/cavitcakir_SectionA_Lab3/verilog_2/test.v
// Project Name:  verilog_2
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: hybrid_cla
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module test;

	// Inputs
	reg C0;
	reg [14:0] A;
	reg [14:0] B;

	// Outputs
	wire [14:0] S;
	wire Carry;
	wire V;

	// Instantiate the Unit Under Test (UUT)
	hybrid_cla uut (
		.C0(C0), 
		.A(A), 
		.B(B), 
		.S(S), 
		.Carry(Carry), 
		.V(V)
	);

	initial begin
		// Initialize Inputs
      C0 = 0; // no overflow addition wo carry
		A = 15'b000000000101111;
		B = 15'b000000000011111;
		#20;
		C0 = 0; // overflow addition wo carry
		A = 15'b010000000101111;
		B = 15'b010000000011111;
		#20;
		C0 = 0; // no overflow addition w carry ...
		A = 15'b110000000101111;
		B = 15'b110000000011111;
		#20;
		C0 = 0; // overflow addition w carry...
		A = 15'b100000000001111;
		B = 15'b100000000000001;
		
		#20;
		C0 = 1; // no overflow subtraction wo carry...
		A = 15'b000000000000111;
		B = 15'b000100000000001;
		#20;
		C0 = 1; // overflow subtraction wo carry...
		A = 15'b011111111010001;
		B = 15'b100000000000011;
		#20;
		C0 = 1; // no overflow subtraction w carry
		A = 15'b000000000101111;
		B = 15'b000000000011111;
		#20;
		C0 = 1; // overflow subtraction w carry
		A = 15'b101111111010001;
		B = 15'b010000000011111;
	end
      
endmodule

