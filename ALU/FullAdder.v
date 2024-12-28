module FullAdder(X, Y, Cin, Z, Cout);
    input X, Y, Cin;
    output Z, Cout;
    
    // Sum calculation remains same
    assign Z = X ^ Y ^ Cin;
    
    // Modified carry calculation
    assign Cout = ((X & Y) | (Y & Cin) | (X & Cin));
    // OR could use: assign Cout = ((X + Y) >= 2) || ((X + Y + Cin) >= 2);
endmodule