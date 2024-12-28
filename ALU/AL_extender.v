module AL_extender(A,B,IA,IB,Cin,Control,Output, Cout);

input [3:0] A, B;
output reg [3:0] IA, IB;
output reg Cin;
input [2:0] Control;
output reg [3:0] Output;
output reg Cout;

wire [3:0] ADD_out;
wire [3:0] ADD_cout;


FullAdder4 FA4 (ADD_out, IA, IB, Cin, ADD_cout);

always @(*) begin
    case(Control)
        3'b000: begin
            IA = A;
            IB = B;
            Cin = 0;
            
            Output = ADD_out;
            Cout = ADD_cout;
            
        end
        
        3'b001: begin
            IA = A;
            IB = ~B;
            Cin = 1;
            
            Output = ADD_out;
            Cout = ADD_cout;
        end
        
        3'b010: begin
            IA = A;
            IB = 1;
            Cin = 0;
            
            Output = ADD_out;
            Cout = ADD_cout;
        end
        
        3'b011: begin
            IA = A;
            IB = 0;
            Cin = 0;
            
            Output = ADD_out;
            Cout = ADD_cout;
        end
        
        3'b100: begin
            IA = A & B;
            IB = 0;
            Cin = 0;
            
            Output = ADD_out;
            Cout = ADD_cout;
        end
        
        3'b101: begin
            IA = A | B;
            IB = 0;
            Cin = 0;
            
            Output = ADD_out;
            Cout = ADD_cout;
        end
        
        3'b110: begin
            IA = A ^ B;
            IB = 0;
            Cin = 0;
            
            Output = ADD_out;
            Cout = ADD_cout;
        end
        
        3'b111: begin
            IA = ~A;
            IB = 0;
            Cin = 0;
            
            Output = ADD_out;
            Cout = ADD_cout;
        end
        
        default: begin
            IA = A;
            IB = B;
            Cin = 0;
            
            Output = ADD_out;
            Cout = ADD_cout;
        end
    endcase
end
    






endmodule