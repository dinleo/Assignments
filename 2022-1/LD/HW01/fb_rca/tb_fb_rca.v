`timescale 1ns/1ns

module tb_fb_rca();
reg [3:0]x, y;
reg z;
wire [3:0]s;
wire c;

fb_rca u0(x, y, z, s, c);

initial
begin
x=4'b0000; y=4'b0000; z=0;
#200; x=4'b0000; y=4'b0000; z=1;
#200; x=4'b0001; y=4'b0001; z=0;
#200; x=4'b0001; y=4'b0001; z=1;
#200; x=4'b0100; y=4'b0011; z=0;
#200; x=4'b0100; y=4'b0011; z=1;
#200; x=4'b1111; y=4'b1111; z=0;
#200; x=4'b1111; y=4'b1111; z=1;
end

endmodule
