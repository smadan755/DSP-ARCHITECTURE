`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 12/27/2024 06:27:04 PM
// Design Name: 
// Module Name: FullSubtractor
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


module FullSubtractor(A,B,Bin, Diff, Bout);
input A,B,Bin;
output Diff, Bout;

assign  Diff = A ^ B ^ Bin;

assign  Bout = (~A && B) || (B && Bin) || (~A && Bin);

endmodule
