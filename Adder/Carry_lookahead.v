module Carry_lookahead #(
    parameter WIDTH = 16
)(
    input [WIDTH-1:0] A, B,
    input Cin,
    output [WIDTH-1:0] S,
    output Cout
);
    wire [WIDTH-1:0] P, G;
    wire [WIDTH:0] C;   
    
    assign C[0] = Cin;  

    // Generate CLAdder instances
    generate
        genvar i;
        for(i = 0; i < WIDTH; i = i + 1) begin : cla_cells
            CLAdder bit_adder(
                .A(A[i]),
                .B(B[i]),
                .Cin(C[i]),
                .S(S[i]),
                .P(P[i]),
                .G(G[i])
            );
        end
    endgenerate

    // Generate carry equations (bottom-up Dynamic Programming)
        
    generate
    genvar j;
        for(j = 1; j <= WIDTH; j = j + 1) begin : carry_gen
            assign C[j] = G[j-1] | (P[j-1] & C[j-1]);
        end
    endgenerate

    assign Cout = C[WIDTH];

endmodule