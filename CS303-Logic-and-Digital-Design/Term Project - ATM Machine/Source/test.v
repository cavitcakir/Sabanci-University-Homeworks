`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   20:45:56 12/15/2019
// Design Name:   atm_board
// Module Name:   C:/Xilinx/projects/tekrarbaslayalim/test.v
// Project Name:  tekrarbaslayalim
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: atm_board
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
	reg clk;
	reg rst;
	reg BTN3;
	reg BTN2;
	reg BTN1;
	reg [3:0] SW;

	// Outputs
	wire [7:0] LED;
	wire [6:0] digit4;
	wire [6:0] digit3;
	wire [6:0] digit2;
	wire [6:0] digit1;

	// Instantiate the Unit Under Test (UUT)
	atm_board uut (
		.clk(clk), 
		.rst(rst), 
		.BTN3(BTN3), 
		.BTN2(BTN2), 
		.BTN1(BTN1), 
		.SW(SW), 
		.LED(LED), 
		.digit4(digit4), 
		.digit3(digit3), 
		.digit2(digit2), 
		.digit1(digit1)
	);
	
always #5 clk = ~clk;

initial
begin
    // initilization
    clk  = 0;
    rst  = 0;
    BTN3 = 0;
    BTN2 = 0;
    BTN1 = 0;
    SW   = 0;
    
    // global resetff
    #100;
    
    // ------------------------- Scenario starts here -------------------------
    
    // ----- a.reset the circuit
    rst = 1;
    #20; 
    rst = 0;
    #20;
    
    // ------------- b.Inset the debit card by pressing BTN3
    BTN3 = 1;       // press BTN3
    #10;            // one clock
    BTN3 = 0;       // release BTN3
    #10;            // one clock
    
    #30;            // wait for some random time (we used 3 clock cycles delay, you can change it)
    /* This random wait time is used to mimic waiting times between push button operations */
    
    // ------------- c.Enter the password correctly and go to the ATM menu state
    SW   = 4'b0000; // set password
    BTN3 = 1;       // press BTN3
    #10;
    BTN3 = 0;       // release BTN3
    #10;
    
    #30;            // wait for some random time
    
    // ------------- d.Go to the money operation state by pressing BTN3
    BTN3 = 1;       // press BTN3
    #10;
    BTN3 = 0;       // release BTN3
    #10;
    
    #30;            // wait for some random time
    
    // ------------- e.Deposit 5 into your account (by setting the SW and pressing BTN3)
    SW   = 4'b0101; // set amount of money to 5
    BTN3 = 1;       // press BTN3
    #10;
    BTN3 = 0;       // release BTN3
    #10;
    
    #30;            // wait for some random time
    
    // ------------- f.Go back to the ATM menu by pressing BTN1
    BTN1 = 1;       // press BTN1
    #10;
    BTN1 = 0;       // release BTN1
    #10;
    
    #30;            // wait for some random time
    
    // ------------- g.Go to password change state by pressing BTN2
    BTN2 = 1;       // press BTN2
    #10;
    BTN2 = 0;       // release BTN2
    #10;
    
    #30;            // wait for some random time
    
    // ------------- h.Enter the current password correctly (by setting the SW and pressing BTN3)
    SW   = 4'b0000; // set the password
    BTN3 = 1;       // press BTN3
    #10;
    BTN3 = 0;       // release BTN3
    #10;
    
    #30;            // wait for some random time
    
    // ------------- i.Enter the new password (by setting the SW and pressing BTN3)
    SW   = 4'b1001; // set the new password (let's say it is 1001)
    BTN3 = 1;       // press BTN3
    #10;
    BTN3 = 0;       // release BTN3
    #10;
    
    #30;            // wait for some random time
    
    // ------------- j.Log out from the ATM by pressing BTN1
    BTN1 = 1;       // press BTN1
    #10;
    BTN1 = 0;       // release BTN1
    #10;
    
    #30;            // wait for some random time
    
    // ------------- k.Inset the debit card by pressing BTN3
    BTN3 = 1;       // press BTN3
    #10;
    BTN3 = 0;       // release BTN3
    #10;
    
    #30;            // wait for some random time
    
    // ------------- l.Enter the password wrong for 3 times (by setting the SW and pressing BTN3)
    // ------ first try
    SW   = 4'b0000; // set wrong password
    BTN3 = 1;       // press BTN3
    #10;
    BTN3 = 0;       // release BTN3
    #10;
    #30;            // wait for some random time
    // ------ second try
    SW   = 4'b0100; // set wrong password
    BTN3 = 1;       // press BTN3
    #10;
    BTN3 = 0;       // release BTN3
    #10;
    #30;            // wait for some random time
    // ------ third try
    SW   = 4'b0010; // set wrong password
    BTN3 = 1;       // press BTN3
    #10;
    BTN3 = 0;       // release BTN3
    #10;
    #30;            // wait for some random time
    
    /*
    Here your circuit should be locked for 5 seconds.
    You'll implement timer for realizing wait operation.
    */
    
    #(80*10);       // wait 80 clock cycles for lock operation (you should change this delay time based on your design)
    
    // ------------- m.Inset the debit card by pressing BTN3
    BTN3 = 1;       // press BTN3
    #10;            // one clock
    BTN3 = 0;       // release BTN3
    #10;            // one clock
    
    #30;            // wait for some random time
    
    // ------------- n.Enter the password correctly and go to the ATM menu state (by setting the SW and pressing BTN3)
    SW   = 4'b1001; // set password
    BTN3 = 1;       // press BTN3
    #10;
    BTN3 = 0;       // release BTN3
    #10;
    
    #30;            // wait for some random time
    
    // ------------- o.Go to the money operation state by pressing BTN3
    BTN3 = 1;       // press BTN3
    #10;
    BTN3 = 0;       // release BTN3
    #10;
    
    #30;            // wait for some random time
    
    // ------------- p.Withdraw 4 from your account (by setting the SW and pressing BTN2)
    SW   = 4'b0100; // set amount of money to 4
    BTN2 = 1;       // press BTN2
    #10;
    BTN2 = 0;       // release BTN2
    #10;
    
    #30;            // wait for some random time
    
    // ------------- q.Withdraw 2 from your account (by setting the SW and pressing BTN2)
    SW   = 4'b0010; // set amount of money to 4
    BTN2 = 1;       // press BTN2
    #10;
    BTN2 = 0;       // release BTN2
    #10;
    
    #30;            // wait for some random time
    
    /*
    Due to insufficient balance in your account 
    (you have 1 in your account but you try to witdraw 2)
    Your circuit should be locked for 2.5 seconds.
    You'll implement timer for realizing wait operation.
    */
    
    #(40*10);       // wait 40 clock cycles for lock operation (you should change this delay time based on your design)
    
    // ------------- r.Go back to the ATM menu state by pressing BTN1
    BTN1 = 1;       // press BTN1
    #10;
    BTN1 = 0;       // release BTN1
    #10;
    
    #30;            // wait for some random time
    
    // ------------- s.Go to the password change state by pressing BTN2
    BTN2 = 1;       // press BTN2
    #10;
    BTN2 = 0;       // release BTN2
    #10;
    
    #30;            // wait for some random time
    
    // ------------- t.Enter the current password wrong for 3 times (by setting the SW and pressing BTN3 -- you should be logged out)
    // ------ first try
    SW   = 4'b0100; // set wrong password
    BTN3 = 1;       // press BTN3
    #10;
    BTN3 = 0;       // release BTN3
    #10;
    #30;            // wait for some random time
    // ------ second try
    SW   = 4'b0000; // set wrong password
    BTN3 = 1;       // press BTN3
    #10;
    BTN3 = 0;       // release BTN3
    #10;
    #30;            // wait for some random time
    // ------ third try
    SW   = 4'b1110; // set wrong password
    BTN3 = 1;       // press BTN3
    #10;
    BTN3 = 0;       // release BTN3
    #10;
    #30;            // wait for some random time
    
    /*
    Here your circuit should be locked for 5 seconds.
    You'll implement timer for realizing wait operation.
    */
    
    #(80*10);       // wait 80 clock cycles for lock operation (you should change this delay time based on your design)
    
    // ------------------------- Scenario ends here -------------------------

end

endmodule