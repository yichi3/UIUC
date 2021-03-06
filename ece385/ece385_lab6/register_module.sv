module register_module
			(	input logic[15:0]		BUS_val, IR,
				input logic				Clk, Reset,
				input logic				DRMUX, SR1MUX, LD_REG,
				output logic[15:0]	SR1_OUT, SR2_OUT
			);

			logic[2:0]	drmux, sr1mux;
			mux4 #(.width(3)) DR_MUX(.d0(IR[11:9]), .d1(3'b111), .d2(3'b0), .d3(3'b0), .s0(DRMUX), .s1(1'b0), .y(drmux));
			mux4 #(.width(3)) SR1_MUX(.d0(IR[11:9]), .d1(IR[8:6]), .d2(3'b0), .d3(3'b0), .s0(SR1MUX), .s1(1'b0), .y(sr1mux));
			register_file reg_file(.Clk, .Reset, .LD_REG, .SR1_OUT, .SR2_OUT,
										  .SR1(sr1mux), .SR2(IR[2:0]),
										  .DRMUX_OUT(drmux), .BUS_val);


endmodule

// this regster file only contains 8 registers and necessary control signals
module register_file
			(	input  logic 			Clk,
											Reset,
				input	logic[2:0]		SR1, DRMUX_OUT, SR2,
				input logic				LD_REG,
				input logic[15:0]		BUS_val,
			
				output logic[15:0]	SR1_OUT, SR2_OUT
			);

				logic[15:0]	reg_array [8];
				//sr1_out and sr2_out are outputs
				assign SR1_OUT = reg_array[SR1];
				assign SR2_OUT = reg_array[SR2];
				
 
				always_ff @ (posedge Clk)
				begin
					if(Reset) begin
						for(integer i = 0; i < 8; i = i + 1)
						begin
							reg_array[i] <= 16'b0;
						end
					end
					if(LD_REG) begin
						reg_array[DRMUX_OUT] <= BUS_val;
					end
				end

endmodule
