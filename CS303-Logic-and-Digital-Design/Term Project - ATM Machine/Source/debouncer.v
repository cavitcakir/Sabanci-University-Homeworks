`timescale 1ns / 1ps

module debouncer(
	input 		clk,
	input 		rst,
	input 		noisy_in, // port from the push button
	output reg 	clean_out // port into the circuit
    );

reg noisy_in_reg;

reg clean_out_tmp1; // will be used to detect rising edge
reg clean_out_tmp2; // will be used to detect rising edge

always@(posedge clk or posedge rst)
begin
	if (rst==1'b1) begin
		noisy_in_reg <= 0;
		clean_out_tmp1 <= 0;
		clean_out_tmp2 <= 0;
		
		clean_out <= 0;
	end
	else begin
		// store the input
		noisy_in_reg <= noisy_in; 
		clean_out_tmp1 <= noisy_in_reg;
				
		// rising edge detect
		clean_out_tmp2 <= clean_out_tmp1;
		clean_out <= ~clean_out_tmp2 & clean_out_tmp1; // it produce a single pulse during a risingedge	
	end
end

endmodule
