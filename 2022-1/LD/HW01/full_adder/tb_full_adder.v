//Test

`timescale 1ns/1ns

module tb_full_adder();
reg x, y, z;
wire s, c;

full_adder u0(x, y, z, s, c);

initial
begin
x=0; y=0; z=0;
#200; x=0; y=0; z=1;
#200; x=0; y=1; z=0;
#200; x=0; y=1; z=1;
#200; x=1; y=0; z=0;
#200; x=1; y=0; z=1;
#200; x=1; y=1; z=0;
#200; x=1; y=1; z=1;
end

endmodule