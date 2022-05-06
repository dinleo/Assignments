module fb_rca(x, y, z, s, c);

input [3:0]x, y;
input z;
output [3:0] s;
output c;

wire c1, s1, c2;

full_adder u1(x[0], y[0], z, s[0], c1);
full_adder u2(x[1], y[1], c1, s[1], c2);
full_adder u3(x[2], y[2], c2, s[2], c3);
full_adder u4(x[3], y[3], c3, s[3], c);

endmodule