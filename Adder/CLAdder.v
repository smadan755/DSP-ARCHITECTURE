module CLAdder(A, B, Cin, S, P, G);

input A,B,Cin;
output S,P,G;

assign P = A ^ B;
assign G = A & B;
assign S = P ^ Cin;


endmodule