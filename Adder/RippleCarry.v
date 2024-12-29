module RippleCarry #(parameter WIDTH = 32)(A, B, Cin, S, Cout);

input [WIDTH-1:0] A, B;
input Cin;

output [WIDTH-1:0] S;
output Cout;

wire [WIDTH:0] C;

assign C[0] = Cin;


genvar i;
generate
    for (i = 0; i < WIDTH; i = i + 1) begin : FULL_ADDERS
        FullAdder FA(A[i], B[i], C[i], S[i], C[i+1]);
    end
endgenerate


assign Cout = C[WIDTH];


endmodule
 