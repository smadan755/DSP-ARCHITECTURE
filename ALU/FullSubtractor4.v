`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 12/27/2024 07:01:50 PM
// Design Name: 
// Module Name: FullSubtractor4
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


module FullSubtractor4(A,B,Bin,Diff,Bout);
input [3:0] A,B;
input Bin;
output [3:0] Diff;
output Bout;

wire [2:0] Bline;

FullSubtractor FS0(A[0], B[0], Bin,Diff[0], Bline[0] );
FullSubtractor FS1(A[1], B[1], Bline[0],Diff[1], Bline[1] );
FullSubtractor FS2(A[2], B[2], Bline[1],Diff[2], Bline[2] );
FullSubtractor FS3(A[3], B[3], Bline[2],Diff[3], Bout );


endmodule
