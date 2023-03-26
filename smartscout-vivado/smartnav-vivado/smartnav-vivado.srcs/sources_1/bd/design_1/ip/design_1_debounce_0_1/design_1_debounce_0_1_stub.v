// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2019.1 (lin64) Build 2552052 Fri May 24 14:47:09 MDT 2019
// Date        : Tue Mar 14 20:17:56 2023
// Host        : kuhiu-Aspire-A515-51G running 64-bit Ubuntu 18.04.6 LTS
// Command     : write_verilog -force -mode synth_stub
//               /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_debounce_0_1/design_1_debounce_0_1_stub.v
// Design      : design_1_debounce_0_1
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7z010clg400-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* x_core_info = "debounce,Vivado 2019.1" *)
module design_1_debounce_0_1(clk, reset_n, button, result)
/* synthesis syn_black_box black_box_pad_pin="clk,reset_n,button,result" */;
  input clk;
  input reset_n;
  input button;
  output result;
endmodule
