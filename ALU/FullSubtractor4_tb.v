`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 12/27/2024 07:13:56 PM
// Design Name: 
// Module Name: FullSubtractor4_tb
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module FullSubtractor4_tb;

reg [3:0] A;
reg [3:0] B;
reg Bin;

wire [3:0] Diff;
wire Bout;

FullSubtractor4 dut(
    .A(A),
    .B(B),
    .Bin(Bin),
    .Diff(Diff),
    .Bout(Bout)

);

initial begin
    A = 4'b1001; B = 4'b0011; Bin = 1'b1; #20;
    
    $display("Result for A = %b, B = %b, Bin = %b : Diff = %b, Bout = %b", A,B,Bin,Diff,Bout);
    
    A = 4'b0011; B = 4'b0110; Bin = 1'b1; #20;
    
    $display("Result for A = %b, B = %b, Bin = %b : Diff = %b, Bout = %b", A,B,Bin,Diff,Bout);
    
end



endmodule
