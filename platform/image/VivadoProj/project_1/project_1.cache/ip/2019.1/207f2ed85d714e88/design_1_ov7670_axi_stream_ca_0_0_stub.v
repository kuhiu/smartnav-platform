// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2019.1 (lin64) Build 2552052 Fri May 24 14:47:09 MDT 2019
// Date        : Sat Nov  5 17:23:02 2022
// Host        : kuhiu-Aspire-A515-51G running 64-bit Ubuntu 16.04.7 LTS
// Command     : write_verilog -force -mode synth_stub -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
//               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ design_1_ov7670_axi_stream_ca_0_0_stub.v
// Design      : design_1_ov7670_axi_stream_ca_0_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7z010clg400-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* x_core_info = "ov7670_axi_stream_capture,Vivado 2019.1" *)
module decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix(pclk, vsync, href, d, m_axis_tvalid, m_axis_tready, 
  m_axis_tlast, m_axis_tdata, m_axis_tuser, aclk)
/* synthesis syn_black_box black_box_pad_pin="pclk,vsync,href,d[7:0],m_axis_tvalid,m_axis_tready,m_axis_tlast,m_axis_tdata[23:0],m_axis_tuser,aclk" */;
  input pclk;
  input vsync;
  input href;
  input [7:0]d;
  output m_axis_tvalid;
  input m_axis_tready;
  output m_axis_tlast;
  output [23:0]m_axis_tdata;
  output m_axis_tuser;
  output aclk;
endmodule
