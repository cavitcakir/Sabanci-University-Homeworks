`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    18:30:21 12/15/2019 
// Design Name: 
// Module Name:    atm_machine 
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
module atm_machine (input clk,
                     input rst,
                     input BTN3, BTN2, BTN1,
                     input [3:0] SW,
                     output reg [7:0] LED,                                     // LED[7] is the left most-LED
                     output reg [6:0] digit4, digit3, digit2, digit1  // digit4 is the left-most SSD
                    );
						  
	reg [3:0] password;
	reg [15:0] balance; 
	reg [2:0] current_state;
	reg [2:0] next_state;
	
	
	wire isTimeUp;
	wire isTimeUp2;
	reg [1:0] passCnt;
	 // timer connections
	 reg start_timer_5sec ;
	 reg start_timer_2_5sec ;
	 reg isCorrect;
	 
	 parameter IDLE = 0,PASS = 1, MENU = 2, CHANGEPASS= 3, ACCOUNT =4, isReset = 5;
	 
	// sequential part - state transitions
	always @ (posedge clk or posedge rst)
	begin
			// your code goes here
			if(rst == 1)
				begin
					current_state <= isReset;
				end
			else
				begin
					current_state <= next_state;
				end
	end

always @ (posedge clk or posedge rst)
	begin
			// your code goes here
			if(rst == 1)
				begin
				start_timer_5sec <= 0;
				start_timer_2_5sec<= 0;
				password <= 4'b0000;
				balance<= 0;
				passCnt <= 0;
				isCorrect <= 0;
					
				end
			else if(current_state == PASS)
				begin
				if(start_timer_5sec == 0)
						begin
							if(BTN1) 
								begin
									passCnt <= 0;
								end
							else if(BTN3)
								begin
									if(SW == password)
										begin
											passCnt <= 0;
										end
									else if(passCnt != 3)
										begin
											passCnt <= passCnt + 1;
										end
									else 
										begin
											start_timer_5sec <= start_timer_5sec;
										end
								end
							else if(passCnt == 3)
								begin
											start_timer_5sec <= 1;
								end
						end
					
					if(isTimeUp) 
						begin
							start_timer_5sec <= 0;
							passCnt <= 0;
						end
				end
			else if(current_state == ACCOUNT)
				begin
				if(start_timer_2_5sec == 0)
					begin
						if(BTN2) 
							begin
								if(SW > balance)
									begin
										start_timer_2_5sec <= 1;
									end
								else
									begin
										balance <= balance - SW;
									end
							end
						else if(BTN3)
							begin
								balance <= balance + SW;
							end
					end
				else
					begin
						if(isTimeUp2)
							begin
								start_timer_2_5sec <= 0;
							end
						end
				end
			else if(current_state == CHANGEPASS )
				begin
					if(isCorrect)
					begin
						if(BTN3)
						begin
							password <= SW;
							isCorrect <= 0;
						end
						else if(BTN1)
						begin
							isCorrect <= 0;
						end
					end
					else if(start_timer_5sec == 0)
						begin
							if(BTN3)
								begin
									if(SW == password)
										begin
											passCnt <= 0;
											isCorrect <= 1;
										end
									else if(passCnt < 3)
										begin
											passCnt <= passCnt + 1;
											isCorrect <= 0;
										end
									else 
										begin
											start_timer_5sec <= 1;
											isCorrect <= 0;
										end
								end
							else if(BTN1) 
							begin
							isCorrect <= 0;
							end
							else if(passCnt == 3)
							begin
								start_timer_5sec <= 1;
								isCorrect <= 0;
							end
						end
					else
						begin
							if(isTimeUp) 
								begin
									start_timer_5sec <= 0;
									passCnt <= 0;
								end
						end
				end
				else if(current_state == isReset)
				begin
				start_timer_5sec <= 0;
				start_timer_2_5sec<= 0;
				password <= 4'b0000;
				balance<= 0;
				passCnt <= 0;
				isCorrect <= 0;
			end
	end

	
	// combinational part - next state definitions
	always @(*)
	begin
			// your code goes here	
			case(current_state)
				IDLE: begin
					LED[0] = 1;
					LED[1] = 0;
					LED[2] = 0;
					LED[3] = 0;
					LED[4] = 0;
					LED[5] = 0;
					LED[6] = 0;
					LED[7] = 0;
					
					digit4 = 7'b0110001; // C
					digit3 = 7'b0001000; // A
					digit2 = 7'b0111001; // r
					digit1 = 7'b1000010; // d
					
					
					if(BTN3) next_state = PASS;
					else next_state = IDLE;
				end
				
				PASS : begin
					if(passCnt == 0)
						begin
							digit4 = 7'b0011000; // P
							digit3 = 7'b0110000; // E
							digit2 = 7'b1111110; // -
							digit1 = 7'b0000110; // 3			
					LED[0] = 0;
					LED[1] = 0;
					LED[2] = 0;
					LED[3] = 0;
					LED[4] = 0;
					LED[5] = 0;
					LED[6] = 0;
					LED[7] = 1;
						end
					else if(passCnt == 1)
						begin
							digit4 = 7'b0011000; // P
							digit3 = 7'b0110000; // E
							digit2 = 7'b1111110; // -
							digit1 = 7'b0010010; // 2
							LED[6] = 1;
							LED[0] = 0;
							LED[1] = 0;
							LED[2] = 0;
							LED[3] = 0;
							LED[4] = 0;
							LED[5] = 0;
							LED[7] = 1;
							
						end
					else if(passCnt == 2)
						begin
							digit4 = 7'b0011000; // P
							digit3 = 7'b0110000; // E
							digit2 = 7'b1111110 ;// -
							digit1 = 7'b1001111 ;// 1
							LED[5] = 1;		
							LED[6] = 1;
							LED[7] = 1;		
							LED[0] = 0;
							LED[1] = 0;
							LED[2] = 0;
							LED[3] = 0;
							LED[4] = 0;	
						end
					else
						begin
							LED[0] = 1;
							LED[1] = 1;
							LED[2] = 1;
							LED[3] = 1;
							LED[4] = 1;
							LED[5] = 1;
							LED[6] = 1;
							LED[7] = 1;
							digit4 = 7'b0111000 ;// F
							digit3 = 7'b0001000 ;// A
							digit2 = 7'b1001111 ;// I
							digit1 = 7'b1110001; // L
						end
					if(start_timer_5sec == 0)
						begin
							if(BTN1) 
								begin
									next_state = IDLE;
								end
							else if(BTN3)
								begin
									if(SW == password)
										begin
											next_state = MENU;
										end
									else if(passCnt < 3)
										begin
											next_state = PASS;
										end
									else 
										begin
											next_state = PASS;
										end
								end
							else
								begin 
									next_state = PASS; 
								end
						end
					else
						begin
							if(isTimeUp) 
								begin
									next_state = IDLE;
								end
							else
								begin
									next_state = PASS;
								end
						end
				end
				
				MENU : begin
					LED[0] = 0;
					LED[1] = 0;
					LED[2] = 0;
					LED[3] = 0;
					LED[4] = 1;
					LED[5] = 0;
					LED[6] = 0;
					LED[7] = 0;
					
					digit4 = 7'b0000001; // O
					digit3 = 7'b0011000; // P
					digit2 = 7'b0110000; // E
					digit1 = 7'b0001001; // n
					
					if(BTN1) next_state = IDLE;
					else if(BTN2) next_state = CHANGEPASS;
					else if(BTN3) next_state = ACCOUNT;
					else next_state = MENU;
				end
				
				ACCOUNT : begin
					
				if(balance[3:0]== 4'b0000)begin//0
				digit1 = 7'b0000001;
				end
				else if(balance[3:0]== 4'b0001)begin//1
				digit1 = 7'b1001111;
				end
				else if(balance[3:0]== 4'b0010)begin//2
				digit1 = 7'b0010010;
				end
				else if(balance[3:0]== 4'b0011)begin//3
				digit1 = 7'b0000110;
				end
				else if(balance[3:0]== 4'b0100)begin//4
				digit1 = 7'b1001100;
				end
				else if(balance[3:0]== 4'b0101)begin//5
				digit1 = 7'b0100100;
				end
				else if(balance[3:0]== 4'b0110)begin//6
				digit1 = 7'b0100000;
				end
				else if(balance[3:0]== 4'b0111)begin//7
				digit1 = 7'b0001111;
				end
				else if(balance[3:0]== 4'b1000)begin//8
				digit1 = 7'b0000000;
				end
				else if(balance[3:0]== 4'b1001)begin//9
				digit1 = 7'b0000100;
				end
				else if(balance[3:0]== 4'b1010)begin//10
				digit1 = 7'b0001000;
				end
				else if(balance[3:0]== 4'b1011)begin//11
				digit1 = 7'b0000000;
				end
				else if(balance[3:0]== 4'b1100)begin//12
				digit1 = 7'b0110001;
				end
				else if(balance[3:0]== 4'b1101)begin//13
				digit1 = 7'b0000001;
				end
				else if(balance[3:0]== 4'b1110)begin//14
				digit1 = 7'b0110000;
				end
				else begin//15
				digit1 = 7'b0111000;
				end
				
				
				if(balance[7:4]== 4'b0000)begin//0
				digit2 = 7'b0000001;
				end
				else if(balance[7:4]== 4'b0001)begin//1
				digit2 = 7'b1001111;
				end
				else if(balance[7:4]== 4'b0010)begin//2
				digit2 = 7'b0010010;
				end
				else if(balance[7:4]== 4'b0011)begin//3
				digit2 = 7'b0000110;
				end
				else if(balance[7:4]== 4'b0100)begin//4
				digit2 = 7'b1001100;
				end
				else if(balance[7:4]== 4'b0101)begin//5
				digit2 = 7'b0100100;
				end
				else if(balance[7:4]== 4'b0110)begin//6
				digit2 = 7'b0100000;
				end
				else if(balance[7:4]== 4'b0111)begin//7
				digit2 = 7'b0001111;
				end
				else if(balance[7:4]== 4'b1000)begin//8
				digit2 = 7'b0000000;
				end
				else if(balance[7:4]== 4'b1001)begin//9
				digit2 = 7'b0000100;
				end
				else if(balance[7:4]== 4'b1010)begin//10
				digit2 = 7'b0001000;
				end
				else if(balance[7:4]== 4'b1011)begin//11
				digit2 = 7'b0000000;
				end
				else if(balance[7:4]== 4'b1100)begin//12
				digit2 = 7'b0110001;
				end
				else if(balance[7:4]== 4'b1101)begin//13
				digit2 = 7'b0000001;
				end
				else if(balance[7:4]== 4'b1110)begin//14
				digit2 = 7'b0110000;
				end
				else begin//15
				digit2 = 7'b0111000;
				end
				
				
				
				if(balance[11:8]== 4'b0000)begin//0
				digit3 = 7'b0000001;
				end
				else if(balance[11:8]== 4'b0001)begin//1
				digit3 = 7'b1001111;
				end
				else if(balance[11:8]== 4'b0010)begin//2
				digit3 = 7'b0010010;
				end
				else if(balance[11:8]== 4'b0011)begin//3
				digit3 = 7'b0000110;
				end
				else if(balance[11:8]== 4'b0100)begin//4
				digit3 = 7'b1001100;
				end
				else if(balance[11:8]== 4'b0101)begin//5
				digit3 = 7'b0100100;
				end
				else if(balance[11:8]== 4'b0110)begin//6
				digit3 = 7'b0100000;
				end
				else if(balance[11:8]== 4'b0111)begin//7
				digit3 = 7'b0001111;
				end
				else if(balance[11:8]== 4'b1000)begin//8
				digit3 = 7'b0000000;
				end
				else if(balance[11:8]== 4'b1001)begin//9
				digit3 = 7'b0000100;
				end
				else if(balance[11:8]== 4'b1010)begin//10
				digit3 = 7'b0001000;
				end
				else if(balance[11:8]== 4'b1011)begin//11
				digit3 = 7'b0000000;
				end
				else if(balance[11:8]== 4'b1100)begin//12
				digit3 = 7'b0110001;
				end
				else if(balance[11:8]== 4'b1101)begin//13
				digit3 = 7'b0000001;
				end
				else if(balance[11:8]== 4'b1110)begin//14
				digit3 = 7'b0110000;
				end
				else begin//15
				digit3 = 7'b0111000;
				end
				
				
				
				if(balance[15:12]== 4'b0000)begin//0
				digit4 = 7'b0000001;
				end
				else if(balance[15:12]== 4'b0001)begin//1
				digit4 = 7'b1001111;
				end
				else if(balance[15:12]== 4'b0010)begin//2
				digit4 = 7'b0010010;
				end
				else if(balance[15:12]== 4'b0011)begin//3
				digit4 = 7'b0000110;
				end
				else if(balance[15:12]== 4'b0100)begin//4
				digit4 = 7'b1001100;
				end
				else if(balance[15:12]== 4'b0101)begin//5
				digit4 = 7'b0100100;
				end
				else if(balance[15:12]== 4'b0110)begin//6
				digit4 = 7'b0100000;
				end
				else if(balance[15:12]== 4'b0111)begin//7
				digit4 = 7'b0001111;
				end
				else if(balance[15:12]== 4'b1000)begin//8
				digit4 = 7'b0000000;
				end
				else if(balance[15:12]== 4'b1001)begin//9
				digit4 = 7'b0000100;
				end
				else if(balance[15:12]== 4'b1010)begin//10
				digit4 = 7'b0001000;
				end
				else if(balance[15:12]== 4'b1011)begin//11
				digit4 = 7'b0000000;
				end 
				else if(balance[15:12]== 4'b1100)begin//12
				digit4 = 7'b0110001;
				end 
				else if(balance[15:12]== 4'b1101)begin//13
				digit4 = 7'b0000001;
				end 
				else if(balance[15:12]== 4'b1110)begin//14
				digit4 = 7'b0110000;
				end 
				else begin//15
				digit4 = 7'b0111000;
				end
					
					if(start_timer_2_5sec == 0)
					begin
					
					LED[0] = 0;
					LED[1] = 0;
					LED[2] = 0;
					LED[3] = 1;
					LED[4] = 0;
					LED[5] = 0;
					LED[6] = 0;
					LED[7] = 0;
							digit4 = digit4; // -
							digit3 = digit3; // n
							digit2 = digit2; // A
							digit1 = digit1; // -
						if(BTN1) 
						begin
							next_state = MENU;
						end
						else if(BTN2) 
							begin
								next_state = ACCOUNT;
							end
						else if(BTN3)
							begin
								next_state = ACCOUNT;
							end
						else next_state = ACCOUNT;
					end
					else
					begin
						if(isTimeUp2)
						begin
							digit4 = 7'b1111110; // -
							digit3 = 7'b0001001; // n
							digit2 = 7'b0001000; // A
							digit1 = 7'b1111110; // -
							LED[0] = 0;
							LED[1] = 0;
							LED[2] = 0;
							LED[3] = 1;
							LED[4] = 0;
							LED[5] = 0;
							LED[6] = 0;
							LED[7] = 0;
							next_state = ACCOUNT;
						end
						else
						begin
							LED[0] = 1;
							LED[1] = 1;
							LED[2] = 1;
							LED[3] = 1;
							LED[4] = 1;
							LED[5] = 1;
							LED[6] = 1;
							LED[7] = 1;
					
							digit4 = 7'b1111110; // -
							digit3 = 7'b0001001; // n
							digit2 = 7'b0001000; // A
							digit1 = 7'b1111110; // -
							next_state = ACCOUNT;
						end
					end
				end
				
				CHANGEPASS : begin
				if(isCorrect == 0)
				begin
					
				if(passCnt == 0 )
						begin
							digit4 = 7'b0011000; // P
							digit3 = 7'b0110001; // C
							digit2 = 7'b1111110; // -
							digit1 = 7'b0000110; // 3
							LED[0] = 0;
					LED[1] = 0;
					LED[2] = 1;
					LED[3] = 0;
					LED[4] = 0;
					LED[5] = 0;
					LED[6] = 0;
					LED[7] = 0;			
						end
					else if(passCnt == 1)
						begin
							digit4 = 7'b0011000; // P
							digit3 = 7'b0110001; // C
							digit2 = 7'b1111110; // -
							digit1 = 7'b0010010; // 2
							LED[1] = 1;
					LED[0] = 0;
					LED[2] = 1;
					LED[3] = 0;
					LED[4] = 0;
					LED[5] = 0;
					LED[6] = 0;
					LED[7] = 0;				
						end
					else if(passCnt == 2)
						begin
							digit4 = 7'b0011000; // P
							digit3 = 7'b0110001; // C
							digit2 = 7'b1111110; // -
							digit1 = 7'b1001111; // 1
							LED[1] = 1;				
							LED[0] = 1;
					LED[2] = 1;
					LED[3] = 0;
					LED[4] = 0;
					LED[5] = 0;
					LED[6] = 0;
					LED[7] = 0;				
						end
					else
						begin
							LED[0] = 1;
							LED[1] = 1;
							LED[2] = 1;
							LED[3] = 1;
							LED[4] = 1;
							LED[5] = 1;
							LED[6] = 1;
							LED[7] = 1;
							digit4 = 7'b0111000; // F
							digit3 = 7'b0001000; // A
							digit2 = 7'b1001111; // I
							digit1 = 7'b1110001; // L
						end
					end
					if(isCorrect)
					begin
					
							LED[0] = 0;
							LED[1] = 1;
							LED[2] = 0;
							LED[3] = 0;
							LED[4] = 0;
							LED[5] = 0;
							LED[6] = 0;
							LED[7] = 0;
							digit4 = 7'b0011000; // P
							digit3 = 7'b0001000; // A
							digit2 = 7'b0100100; // S
							digit1 = 7'b0100100; // S
					
						if(BTN3)
						begin
							next_state = MENU;
						end
						else if(BTN1)
						begin
							next_state = MENU;
						end
						else
						begin
							next_state = CHANGEPASS;
						end
					end
					else if(start_timer_5sec == 0)
						begin
							if(BTN3)
								begin
									if(SW == password)
										begin
											next_state = CHANGEPASS;
										end
									else if(passCnt < 3)
										begin
											next_state = CHANGEPASS;
										end
									else 
										begin
											next_state = CHANGEPASS;
										end
								end
							
							else if(BTN1) 
							begin
							next_state = MENU;
							end
							else next_state = CHANGEPASS;
						end
					else
						begin
							if(isTimeUp == 0) 
								begin
									next_state = CHANGEPASS;
								end
							else
								begin
									next_state = IDLE;
								end
						end
				end
			
			isReset : begin
				LED[0] = 0;
				LED[1] = 0;
				LED[2] = 0;
				LED[3] = 0;
				LED[4] = 0;
				LED[5] = 0;
				LED[6] = 0;
				LED[7] = 0;
				digit4 = 7'b1111111; // ""
				digit3 = 7'b1111111; // ""
				digit2 = 7'b1111111; // ""
				digit1 = 7'b1111111; // ""
				next_state = IDLE;
			end
			default: begin
			LED[0] = 0;
				LED[1] = 0;
				LED[2] = 0;
				LED[3] = 0;
				LED[4] = 0;
				LED[5] = 0;
				LED[6] = 0;
				LED[7] = 0;
				digit4 = 7'b1111111; // ""
				digit3 = 7'b1111111; // ""
				digit2 = 7'b1111111; // ""
				digit1 = 7'b1111111; // ""
				next_state = IDLE;
			end
	endcase
		// additional always statements
end


timer5 my_timer (clk,rst,start_timer_5sec,isTimeUp);
timer2_5 my_timer_2 (clk,rst,start_timer_2_5sec,isTimeUp2);


endmodule

module timer5(clk,rst,start_timer_5sec,isTimeUp);
// DO NOT MODIFY or DELETE THIS MODULE
// timer runs when start_timer is 1

input  clk,rst;
input  start_timer_5sec;
output reg isTimeUp;
reg [9:0]timeCnt ;

always @ (posedge clk or posedge rst) begin
	if(rst) begin
		timeCnt <= 0;
		isTimeUp <= 0;
	end
	else begin
		if(start_timer_5sec)
			begin
				if(timeCnt < 98)
					timeCnt <= timeCnt + 1;
				else 
					timeCnt <= timeCnt;
			end
		else 
			begin
				timeCnt <= 0;
			end
		
		 isTimeUp <= (timeCnt == 98);
		 //isTimeUp <= 1;
	end
end

endmodule

module timer2_5(clk,rst,start_timer_2_5sec,isTimeUp2);
// DO NOT MODIFY or DELETE THIS MODULE
// timer runs when start_timer is 1

input  clk,rst;
input  start_timer_2_5sec;
output reg isTimeUp2;
reg [9:0]timeCnt2;

always @ (posedge clk or posedge rst) begin
	if(rst) begin
		timeCnt2 <= 0;
		isTimeUp2 <= 0;
	end
	else begin
		if(start_timer_2_5sec)
			begin
				if(timeCnt2 < 48)
					timeCnt2 <= timeCnt2 + 1;
				else 
					timeCnt2 <= timeCnt2;
			end
		else 
			begin
				timeCnt2 <= 0;
			end
		
		 isTimeUp2 <= (timeCnt2 == 48);
		 //isTimeUp2 <= 1;
	end
end

endmodule





















