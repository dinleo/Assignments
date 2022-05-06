module full_adder(x, y, z, s, c);
input x, y, z;
output s, c;

wire c1, s1, c2;

half_adder u1(x, y, s1, c1);
half_adder u2(s1, z, s, c2);
or u3(c, c1, c2);

endmodule
