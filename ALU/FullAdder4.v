module FullAdder4(S, A, B, Cin, Cout);
    input [3:0] A, B;
    output [3:0] S;
    input Cin;
    output Cout;
    wire [2:0] C;

    // Using named port mapping to be explicit
    FullAdder FA0(.X(A[0]), .Y(B[0]), .Cin(Cin),  .Z(S[0]), .Cout(C[0]));
    FullAdder FA1(.X(A[1]), .Y(B[1]), .Cin(C[0]), .Z(S[1]), .Cout(C[1]));
    FullAdder FA2(.X(A[2]), .Y(B[2]), .Cin(C[1]), .Z(S[2]), .Cout(C[2])); 
    FullAdder FA3(.X(A[3]), .Y(B[3]), .Cin(C[2]), .Z(S[3]), .Cout(Cout)); 
endmodule