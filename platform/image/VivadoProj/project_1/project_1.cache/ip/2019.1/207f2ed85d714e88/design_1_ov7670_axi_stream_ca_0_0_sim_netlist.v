// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2019.1 (lin64) Build 2552052 Fri May 24 14:47:09 MDT 2019
// Date        : Sat Nov  5 17:23:03 2022
// Host        : kuhiu-Aspire-A515-51G running 64-bit Ubuntu 16.04.7 LTS
// Command     : write_verilog -force -mode funcsim -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
//               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ design_1_ov7670_axi_stream_ca_0_0_sim_netlist.v
// Design      : design_1_ov7670_axi_stream_ca_0_0
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xc7z010clg400-1
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "design_1_ov7670_axi_stream_ca_0_0,ov7670_axi_stream_capture,{}" *) (* downgradeipidentifiedwarnings = "yes" *) (* ip_definition_source = "package_project" *) 
(* x_core_info = "ov7670_axi_stream_capture,Vivado 2019.1" *) 
(* NotValidForBitStream *)
module decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix
   (pclk,
    vsync,
    href,
    d,
    m_axis_tvalid,
    m_axis_tready,
    m_axis_tlast,
    m_axis_tdata,
    m_axis_tuser,
    aclk);
  input pclk;
  input vsync;
  input href;
  input [7:0]d;
  output m_axis_tvalid;
  input m_axis_tready;
  output m_axis_tlast;
  output [23:0]m_axis_tdata;
  output m_axis_tuser;
  (* x_interface_info = "xilinx.com:signal:clock:1.0 aclk CLK" *) (* x_interface_parameter = "XIL_INTERFACENAME aclk, FREQ_HZ 100000000, PHASE 0.000, CLK_DOMAIN design_1_ov7670_axi_stream_ca_0_0_aclk, INSERT_VIP 0" *) output aclk;

  wire aclk;
  wire [7:0]d;
  wire href;
  wire [23:0]\^m_axis_tdata ;
  wire m_axis_tlast;
  wire m_axis_tuser;
  wire m_axis_tvalid;
  wire pclk;
  wire vsync;

  assign m_axis_tdata[23:19] = \^m_axis_tdata [23:19];
  assign m_axis_tdata[18] = \^m_axis_tdata [19];
  assign m_axis_tdata[17] = \^m_axis_tdata [19];
  assign m_axis_tdata[16] = \^m_axis_tdata [19];
  assign m_axis_tdata[15:10] = \^m_axis_tdata [15:10];
  assign m_axis_tdata[9] = \^m_axis_tdata [10];
  assign m_axis_tdata[8] = \^m_axis_tdata [10];
  assign m_axis_tdata[7:4] = \^m_axis_tdata [7:4];
  assign m_axis_tdata[3] = \^m_axis_tdata [0];
  assign m_axis_tdata[2] = \^m_axis_tdata [0];
  assign m_axis_tdata[1] = \^m_axis_tdata [0];
  assign m_axis_tdata[0] = \^m_axis_tdata [0];
  decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ov7670_axi_stream_capture U0
       (.d(d),
        .href(href),
        .m_axis_tdata({\^m_axis_tdata [23:19],\^m_axis_tdata [15:10],\^m_axis_tdata [7:4],\^m_axis_tdata [0]}),
        .m_axis_tlast(m_axis_tlast),
        .m_axis_tuser(m_axis_tuser),
        .m_axis_tvalid(m_axis_tvalid),
        .pclk(pclk),
        .vsync(vsync));
  LUT1 #(
    .INIT(2'h1)) 
    aclk_INST_0
       (.I0(pclk),
        .O(aclk));
endmodule

module decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ov7670_axi_stream_capture
   (m_axis_tvalid,
    m_axis_tlast,
    m_axis_tuser,
    m_axis_tdata,
    href,
    pclk,
    vsync,
    d);
  output m_axis_tvalid;
  output m_axis_tlast;
  output m_axis_tuser;
  output [15:0]m_axis_tdata;
  input href;
  input pclk;
  input vsync;
  input [7:0]d;

  wire \address[0]_i_2_n_0 ;
  wire [18:0]address_reg;
  wire \address_reg[0]_i_1_n_0 ;
  wire \address_reg[0]_i_1_n_1 ;
  wire \address_reg[0]_i_1_n_2 ;
  wire \address_reg[0]_i_1_n_3 ;
  wire \address_reg[0]_i_1_n_4 ;
  wire \address_reg[0]_i_1_n_5 ;
  wire \address_reg[0]_i_1_n_6 ;
  wire \address_reg[0]_i_1_n_7 ;
  wire \address_reg[12]_i_1_n_0 ;
  wire \address_reg[12]_i_1_n_1 ;
  wire \address_reg[12]_i_1_n_2 ;
  wire \address_reg[12]_i_1_n_3 ;
  wire \address_reg[12]_i_1_n_4 ;
  wire \address_reg[12]_i_1_n_5 ;
  wire \address_reg[12]_i_1_n_6 ;
  wire \address_reg[12]_i_1_n_7 ;
  wire \address_reg[16]_i_1_n_2 ;
  wire \address_reg[16]_i_1_n_3 ;
  wire \address_reg[16]_i_1_n_5 ;
  wire \address_reg[16]_i_1_n_6 ;
  wire \address_reg[16]_i_1_n_7 ;
  wire \address_reg[4]_i_1_n_0 ;
  wire \address_reg[4]_i_1_n_1 ;
  wire \address_reg[4]_i_1_n_2 ;
  wire \address_reg[4]_i_1_n_3 ;
  wire \address_reg[4]_i_1_n_4 ;
  wire \address_reg[4]_i_1_n_5 ;
  wire \address_reg[4]_i_1_n_6 ;
  wire \address_reg[4]_i_1_n_7 ;
  wire \address_reg[8]_i_1_n_0 ;
  wire \address_reg[8]_i_1_n_1 ;
  wire \address_reg[8]_i_1_n_2 ;
  wire \address_reg[8]_i_1_n_3 ;
  wire \address_reg[8]_i_1_n_4 ;
  wire \address_reg[8]_i_1_n_5 ;
  wire \address_reg[8]_i_1_n_6 ;
  wire \address_reg[8]_i_1_n_7 ;
  wire [7:0]d;
  wire eol1__103_carry__0_i_1_n_0;
  wire eol1__103_carry__0_i_2_n_0;
  wire eol1__103_carry__0_i_3_n_0;
  wire eol1__103_carry__0_i_4_n_0;
  wire eol1__103_carry__0_n_0;
  wire eol1__103_carry__0_n_1;
  wire eol1__103_carry__0_n_2;
  wire eol1__103_carry__0_n_3;
  wire eol1__103_carry__0_n_4;
  wire eol1__103_carry__0_n_5;
  wire eol1__103_carry__1_i_1_n_0;
  wire eol1__103_carry__1_i_2_n_0;
  wire eol1__103_carry__1_n_3;
  wire eol1__103_carry__1_n_6;
  wire eol1__103_carry__1_n_7;
  wire eol1__103_carry_i_1_n_0;
  wire eol1__103_carry_i_2_n_0;
  wire eol1__103_carry_i_3_n_0;
  wire eol1__103_carry_i_4_n_0;
  wire eol1__103_carry_n_0;
  wire eol1__103_carry_n_1;
  wire eol1__103_carry_n_2;
  wire eol1__103_carry_n_3;
  wire eol1__60_carry__0_i_1_n_0;
  wire eol1__60_carry__0_i_2_n_0;
  wire eol1__60_carry__0_i_3_n_0;
  wire eol1__60_carry__0_i_4_n_0;
  wire eol1__60_carry__0_i_5_n_0;
  wire eol1__60_carry__0_i_6_n_0;
  wire eol1__60_carry__0_i_7_n_0;
  wire eol1__60_carry__0_i_8_n_0;
  wire eol1__60_carry__0_n_0;
  wire eol1__60_carry__0_n_1;
  wire eol1__60_carry__0_n_2;
  wire eol1__60_carry__0_n_3;
  wire eol1__60_carry__1_i_10_n_0;
  wire eol1__60_carry__1_i_11_n_0;
  wire eol1__60_carry__1_i_12_n_0;
  wire eol1__60_carry__1_i_1_n_0;
  wire eol1__60_carry__1_i_2_n_0;
  wire eol1__60_carry__1_i_3_n_0;
  wire eol1__60_carry__1_i_4_n_0;
  wire eol1__60_carry__1_i_5_n_0;
  wire eol1__60_carry__1_i_6_n_0;
  wire eol1__60_carry__1_i_7_n_0;
  wire eol1__60_carry__1_i_8_n_0;
  wire eol1__60_carry__1_i_9_n_0;
  wire eol1__60_carry__1_n_0;
  wire eol1__60_carry__1_n_1;
  wire eol1__60_carry__1_n_2;
  wire eol1__60_carry__1_n_3;
  wire eol1__60_carry__2_i_10_n_0;
  wire eol1__60_carry__2_i_11_n_0;
  wire eol1__60_carry__2_i_12_n_0;
  wire eol1__60_carry__2_i_1_n_0;
  wire eol1__60_carry__2_i_2_n_0;
  wire eol1__60_carry__2_i_3_n_0;
  wire eol1__60_carry__2_i_4_n_0;
  wire eol1__60_carry__2_i_5_n_0;
  wire eol1__60_carry__2_i_6_n_0;
  wire eol1__60_carry__2_i_7_n_0;
  wire eol1__60_carry__2_i_8_n_0;
  wire eol1__60_carry__2_i_9_n_0;
  wire eol1__60_carry__2_n_0;
  wire eol1__60_carry__2_n_1;
  wire eol1__60_carry__2_n_2;
  wire eol1__60_carry__2_n_3;
  wire eol1__60_carry__2_n_4;
  wire eol1__60_carry__2_n_5;
  wire eol1__60_carry__3_i_1_n_0;
  wire eol1__60_carry__3_i_2_n_0;
  wire eol1__60_carry__3_i_3_n_0;
  wire eol1__60_carry__3_i_4_n_0;
  wire eol1__60_carry__3_i_5_n_0;
  wire eol1__60_carry__3_n_3;
  wire eol1__60_carry__3_n_6;
  wire eol1__60_carry__3_n_7;
  wire eol1__60_carry_i_1_n_0;
  wire eol1__60_carry_i_2_n_0;
  wire eol1__60_carry_i_3_n_0;
  wire eol1__60_carry_n_0;
  wire eol1__60_carry_n_1;
  wire eol1__60_carry_n_2;
  wire eol1__60_carry_n_3;
  wire eol1__97_carry_i_1_n_0;
  wire eol1__97_carry_i_2_n_0;
  wire eol1__97_carry_n_2;
  wire eol1__97_carry_n_3;
  wire eol1__97_carry_n_5;
  wire eol1__97_carry_n_6;
  wire eol1__97_carry_n_7;
  wire eol1_carry__0_i_1_n_0;
  wire eol1_carry__0_i_2_n_0;
  wire eol1_carry__0_i_3_n_0;
  wire eol1_carry__0_i_4_n_0;
  wire eol1_carry__0_i_5_n_0;
  wire eol1_carry__0_i_6_n_0;
  wire eol1_carry__0_i_7_n_0;
  wire eol1_carry__0_n_0;
  wire eol1_carry__0_n_1;
  wire eol1_carry__0_n_2;
  wire eol1_carry__0_n_3;
  wire eol1_carry__0_n_4;
  wire eol1_carry__0_n_5;
  wire eol1_carry__0_n_6;
  wire eol1_carry__0_n_7;
  wire eol1_carry__1_i_1_n_0;
  wire eol1_carry__1_i_2_n_0;
  wire eol1_carry__1_i_3_n_0;
  wire eol1_carry__1_i_4_n_0;
  wire eol1_carry__1_i_5_n_0;
  wire eol1_carry__1_i_6_n_0;
  wire eol1_carry__1_i_7_n_0;
  wire eol1_carry__1_i_8_n_0;
  wire eol1_carry__1_n_0;
  wire eol1_carry__1_n_1;
  wire eol1_carry__1_n_2;
  wire eol1_carry__1_n_3;
  wire eol1_carry__1_n_4;
  wire eol1_carry__1_n_5;
  wire eol1_carry__1_n_6;
  wire eol1_carry__1_n_7;
  wire eol1_carry__2_i_1_n_0;
  wire eol1_carry__2_i_2_n_0;
  wire eol1_carry__2_i_3_n_0;
  wire eol1_carry__2_i_4_n_0;
  wire eol1_carry__2_i_5_n_0;
  wire eol1_carry__2_i_6_n_0;
  wire eol1_carry__2_i_7_n_0;
  wire eol1_carry__2_i_8_n_0;
  wire eol1_carry__2_n_0;
  wire eol1_carry__2_n_1;
  wire eol1_carry__2_n_2;
  wire eol1_carry__2_n_3;
  wire eol1_carry__2_n_4;
  wire eol1_carry__2_n_5;
  wire eol1_carry__2_n_6;
  wire eol1_carry__2_n_7;
  wire eol1_carry__3_i_1_n_0;
  wire eol1_carry__3_i_2_n_0;
  wire eol1_carry__3_i_3_n_0;
  wire eol1_carry__3_i_4_n_0;
  wire eol1_carry__3_i_5_n_0;
  wire eol1_carry__3_i_6_n_0;
  wire eol1_carry__3_i_7_n_0;
  wire eol1_carry__3_i_8_n_0;
  wire eol1_carry__3_n_0;
  wire eol1_carry__3_n_1;
  wire eol1_carry__3_n_2;
  wire eol1_carry__3_n_3;
  wire eol1_carry__3_n_4;
  wire eol1_carry__3_n_5;
  wire eol1_carry__3_n_6;
  wire eol1_carry__3_n_7;
  wire eol1_carry__4_i_1_n_0;
  wire eol1_carry__4_i_2_n_0;
  wire eol1_carry__4_i_3_n_0;
  wire eol1_carry__4_n_3;
  wire eol1_carry__4_n_6;
  wire eol1_carry__4_n_7;
  wire eol1_carry_i_1_n_0;
  wire eol1_carry_i_2_n_0;
  wire eol1_carry_i_3_n_0;
  wire eol1_carry_n_0;
  wire eol1_carry_n_1;
  wire eol1_carry_n_2;
  wire eol1_carry_n_3;
  wire eol_i_1_n_0;
  wire eol_i_2_n_0;
  wire eol_i_3_n_0;
  wire href;
  wire [0:0]href_last;
  wire \href_last[0]_i_1_n_0 ;
  wire latched_href;
  wire latched_vsync;
  wire [15:0]m_axis_tdata;
  wire m_axis_tlast;
  wire m_axis_tuser;
  wire m_axis_tvalid;
  wire [7:0]p_0_in;
  wire pclk;
  wire [5:0]sel0;
  wire sof_i_1_n_0;
  wire sof_i_2_n_0;
  wire sof_i_3_n_0;
  wire sof_i_4_n_0;
  wire sof_i_5_n_0;
  wire sof_i_6_n_0;
  wire vsync;
  wire we_reg_i_1_n_0;
  wire [3:2]\NLW_address_reg[16]_i_1_CO_UNCONNECTED ;
  wire [3:3]\NLW_address_reg[16]_i_1_O_UNCONNECTED ;
  wire [3:1]NLW_eol1__103_carry__1_CO_UNCONNECTED;
  wire [3:2]NLW_eol1__103_carry__1_O_UNCONNECTED;
  wire [3:0]NLW_eol1__60_carry_O_UNCONNECTED;
  wire [3:0]NLW_eol1__60_carry__0_O_UNCONNECTED;
  wire [3:0]NLW_eol1__60_carry__1_O_UNCONNECTED;
  wire [1:0]NLW_eol1__60_carry__2_O_UNCONNECTED;
  wire [3:1]NLW_eol1__60_carry__3_CO_UNCONNECTED;
  wire [3:2]NLW_eol1__60_carry__3_O_UNCONNECTED;
  wire [3:2]NLW_eol1__97_carry_CO_UNCONNECTED;
  wire [3:3]NLW_eol1__97_carry_O_UNCONNECTED;
  wire [3:0]NLW_eol1_carry_O_UNCONNECTED;
  wire [3:1]NLW_eol1_carry__4_CO_UNCONNECTED;
  wire [3:2]NLW_eol1_carry__4_O_UNCONNECTED;

  LUT1 #(
    .INIT(2'h1)) 
    \address[0]_i_2 
       (.I0(address_reg[0]),
        .O(\address[0]_i_2_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \address_reg[0] 
       (.C(pclk),
        .CE(m_axis_tvalid),
        .D(\address_reg[0]_i_1_n_7 ),
        .Q(address_reg[0]),
        .R(latched_vsync));
  CARRY4 \address_reg[0]_i_1 
       (.CI(1'b0),
        .CO({\address_reg[0]_i_1_n_0 ,\address_reg[0]_i_1_n_1 ,\address_reg[0]_i_1_n_2 ,\address_reg[0]_i_1_n_3 }),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b1}),
        .O({\address_reg[0]_i_1_n_4 ,\address_reg[0]_i_1_n_5 ,\address_reg[0]_i_1_n_6 ,\address_reg[0]_i_1_n_7 }),
        .S({address_reg[3:1],\address[0]_i_2_n_0 }));
  FDRE #(
    .INIT(1'b0)) 
    \address_reg[10] 
       (.C(pclk),
        .CE(m_axis_tvalid),
        .D(\address_reg[8]_i_1_n_5 ),
        .Q(address_reg[10]),
        .R(latched_vsync));
  FDRE #(
    .INIT(1'b0)) 
    \address_reg[11] 
       (.C(pclk),
        .CE(m_axis_tvalid),
        .D(\address_reg[8]_i_1_n_4 ),
        .Q(address_reg[11]),
        .R(latched_vsync));
  FDRE #(
    .INIT(1'b0)) 
    \address_reg[12] 
       (.C(pclk),
        .CE(m_axis_tvalid),
        .D(\address_reg[12]_i_1_n_7 ),
        .Q(address_reg[12]),
        .R(latched_vsync));
  CARRY4 \address_reg[12]_i_1 
       (.CI(\address_reg[8]_i_1_n_0 ),
        .CO({\address_reg[12]_i_1_n_0 ,\address_reg[12]_i_1_n_1 ,\address_reg[12]_i_1_n_2 ,\address_reg[12]_i_1_n_3 }),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\address_reg[12]_i_1_n_4 ,\address_reg[12]_i_1_n_5 ,\address_reg[12]_i_1_n_6 ,\address_reg[12]_i_1_n_7 }),
        .S(address_reg[15:12]));
  FDRE #(
    .INIT(1'b0)) 
    \address_reg[13] 
       (.C(pclk),
        .CE(m_axis_tvalid),
        .D(\address_reg[12]_i_1_n_6 ),
        .Q(address_reg[13]),
        .R(latched_vsync));
  FDRE #(
    .INIT(1'b0)) 
    \address_reg[14] 
       (.C(pclk),
        .CE(m_axis_tvalid),
        .D(\address_reg[12]_i_1_n_5 ),
        .Q(address_reg[14]),
        .R(latched_vsync));
  FDRE #(
    .INIT(1'b0)) 
    \address_reg[15] 
       (.C(pclk),
        .CE(m_axis_tvalid),
        .D(\address_reg[12]_i_1_n_4 ),
        .Q(address_reg[15]),
        .R(latched_vsync));
  FDRE #(
    .INIT(1'b0)) 
    \address_reg[16] 
       (.C(pclk),
        .CE(m_axis_tvalid),
        .D(\address_reg[16]_i_1_n_7 ),
        .Q(address_reg[16]),
        .R(latched_vsync));
  CARRY4 \address_reg[16]_i_1 
       (.CI(\address_reg[12]_i_1_n_0 ),
        .CO({\NLW_address_reg[16]_i_1_CO_UNCONNECTED [3:2],\address_reg[16]_i_1_n_2 ,\address_reg[16]_i_1_n_3 }),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\NLW_address_reg[16]_i_1_O_UNCONNECTED [3],\address_reg[16]_i_1_n_5 ,\address_reg[16]_i_1_n_6 ,\address_reg[16]_i_1_n_7 }),
        .S({1'b0,address_reg[18:16]}));
  FDRE #(
    .INIT(1'b0)) 
    \address_reg[17] 
       (.C(pclk),
        .CE(m_axis_tvalid),
        .D(\address_reg[16]_i_1_n_6 ),
        .Q(address_reg[17]),
        .R(latched_vsync));
  FDRE #(
    .INIT(1'b0)) 
    \address_reg[18] 
       (.C(pclk),
        .CE(m_axis_tvalid),
        .D(\address_reg[16]_i_1_n_5 ),
        .Q(address_reg[18]),
        .R(latched_vsync));
  FDRE #(
    .INIT(1'b0)) 
    \address_reg[1] 
       (.C(pclk),
        .CE(m_axis_tvalid),
        .D(\address_reg[0]_i_1_n_6 ),
        .Q(address_reg[1]),
        .R(latched_vsync));
  FDRE #(
    .INIT(1'b0)) 
    \address_reg[2] 
       (.C(pclk),
        .CE(m_axis_tvalid),
        .D(\address_reg[0]_i_1_n_5 ),
        .Q(address_reg[2]),
        .R(latched_vsync));
  FDRE #(
    .INIT(1'b0)) 
    \address_reg[3] 
       (.C(pclk),
        .CE(m_axis_tvalid),
        .D(\address_reg[0]_i_1_n_4 ),
        .Q(address_reg[3]),
        .R(latched_vsync));
  FDRE #(
    .INIT(1'b0)) 
    \address_reg[4] 
       (.C(pclk),
        .CE(m_axis_tvalid),
        .D(\address_reg[4]_i_1_n_7 ),
        .Q(address_reg[4]),
        .R(latched_vsync));
  CARRY4 \address_reg[4]_i_1 
       (.CI(\address_reg[0]_i_1_n_0 ),
        .CO({\address_reg[4]_i_1_n_0 ,\address_reg[4]_i_1_n_1 ,\address_reg[4]_i_1_n_2 ,\address_reg[4]_i_1_n_3 }),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\address_reg[4]_i_1_n_4 ,\address_reg[4]_i_1_n_5 ,\address_reg[4]_i_1_n_6 ,\address_reg[4]_i_1_n_7 }),
        .S(address_reg[7:4]));
  FDRE #(
    .INIT(1'b0)) 
    \address_reg[5] 
       (.C(pclk),
        .CE(m_axis_tvalid),
        .D(\address_reg[4]_i_1_n_6 ),
        .Q(address_reg[5]),
        .R(latched_vsync));
  FDRE #(
    .INIT(1'b0)) 
    \address_reg[6] 
       (.C(pclk),
        .CE(m_axis_tvalid),
        .D(\address_reg[4]_i_1_n_5 ),
        .Q(address_reg[6]),
        .R(latched_vsync));
  FDRE #(
    .INIT(1'b0)) 
    \address_reg[7] 
       (.C(pclk),
        .CE(m_axis_tvalid),
        .D(\address_reg[4]_i_1_n_4 ),
        .Q(address_reg[7]),
        .R(latched_vsync));
  FDRE #(
    .INIT(1'b0)) 
    \address_reg[8] 
       (.C(pclk),
        .CE(m_axis_tvalid),
        .D(\address_reg[8]_i_1_n_7 ),
        .Q(address_reg[8]),
        .R(latched_vsync));
  CARRY4 \address_reg[8]_i_1 
       (.CI(\address_reg[4]_i_1_n_0 ),
        .CO({\address_reg[8]_i_1_n_0 ,\address_reg[8]_i_1_n_1 ,\address_reg[8]_i_1_n_2 ,\address_reg[8]_i_1_n_3 }),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\address_reg[8]_i_1_n_4 ,\address_reg[8]_i_1_n_5 ,\address_reg[8]_i_1_n_6 ,\address_reg[8]_i_1_n_7 }),
        .S(address_reg[11:8]));
  FDRE #(
    .INIT(1'b0)) 
    \address_reg[9] 
       (.C(pclk),
        .CE(m_axis_tvalid),
        .D(\address_reg[8]_i_1_n_6 ),
        .Q(address_reg[9]),
        .R(latched_vsync));
  FDRE #(
    .INIT(1'b0)) 
    \d_latch_reg[0] 
       (.C(pclk),
        .CE(latched_href),
        .D(p_0_in[0]),
        .Q(m_axis_tdata[11]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \d_latch_reg[10] 
       (.C(pclk),
        .CE(latched_href),
        .D(m_axis_tdata[13]),
        .Q(m_axis_tdata[10]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \d_latch_reg[11] 
       (.C(pclk),
        .CE(latched_href),
        .D(m_axis_tdata[14]),
        .Q(m_axis_tdata[0]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \d_latch_reg[12] 
       (.C(pclk),
        .CE(latched_href),
        .D(m_axis_tdata[15]),
        .Q(m_axis_tdata[1]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \d_latch_reg[13] 
       (.C(pclk),
        .CE(latched_href),
        .D(m_axis_tdata[5]),
        .Q(m_axis_tdata[2]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \d_latch_reg[14] 
       (.C(pclk),
        .CE(latched_href),
        .D(m_axis_tdata[6]),
        .Q(m_axis_tdata[3]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \d_latch_reg[15] 
       (.C(pclk),
        .CE(latched_href),
        .D(m_axis_tdata[7]),
        .Q(m_axis_tdata[4]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \d_latch_reg[1] 
       (.C(pclk),
        .CE(latched_href),
        .D(p_0_in[1]),
        .Q(m_axis_tdata[12]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \d_latch_reg[2] 
       (.C(pclk),
        .CE(latched_href),
        .D(p_0_in[2]),
        .Q(m_axis_tdata[13]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \d_latch_reg[3] 
       (.C(pclk),
        .CE(latched_href),
        .D(p_0_in[3]),
        .Q(m_axis_tdata[14]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \d_latch_reg[4] 
       (.C(pclk),
        .CE(latched_href),
        .D(p_0_in[4]),
        .Q(m_axis_tdata[15]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \d_latch_reg[5] 
       (.C(pclk),
        .CE(latched_href),
        .D(p_0_in[5]),
        .Q(m_axis_tdata[5]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \d_latch_reg[6] 
       (.C(pclk),
        .CE(latched_href),
        .D(p_0_in[6]),
        .Q(m_axis_tdata[6]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \d_latch_reg[7] 
       (.C(pclk),
        .CE(latched_href),
        .D(p_0_in[7]),
        .Q(m_axis_tdata[7]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \d_latch_reg[8] 
       (.C(pclk),
        .CE(latched_href),
        .D(m_axis_tdata[11]),
        .Q(m_axis_tdata[8]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \d_latch_reg[9] 
       (.C(pclk),
        .CE(latched_href),
        .D(m_axis_tdata[12]),
        .Q(m_axis_tdata[9]),
        .R(1'b0));
  CARRY4 eol1__103_carry
       (.CI(1'b0),
        .CO({eol1__103_carry_n_0,eol1__103_carry_n_1,eol1__103_carry_n_2,eol1__103_carry_n_3}),
        .CYINIT(1'b1),
        .DI(address_reg[3:0]),
        .O(sel0[3:0]),
        .S({eol1__103_carry_i_1_n_0,eol1__103_carry_i_2_n_0,eol1__103_carry_i_3_n_0,eol1__103_carry_i_4_n_0}));
  CARRY4 eol1__103_carry__0
       (.CI(eol1__103_carry_n_0),
        .CO({eol1__103_carry__0_n_0,eol1__103_carry__0_n_1,eol1__103_carry__0_n_2,eol1__103_carry__0_n_3}),
        .CYINIT(1'b0),
        .DI(address_reg[7:4]),
        .O({eol1__103_carry__0_n_4,eol1__103_carry__0_n_5,sel0[5:4]}),
        .S({eol1__103_carry__0_i_1_n_0,eol1__103_carry__0_i_2_n_0,eol1__103_carry__0_i_3_n_0,eol1__103_carry__0_i_4_n_0}));
  LUT2 #(
    .INIT(4'h9)) 
    eol1__103_carry__0_i_1
       (.I0(address_reg[7]),
        .I1(eol1__97_carry_n_7),
        .O(eol1__103_carry__0_i_1_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    eol1__103_carry__0_i_2
       (.I0(address_reg[6]),
        .I1(eol1__60_carry__2_n_5),
        .O(eol1__103_carry__0_i_2_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    eol1__103_carry__0_i_3
       (.I0(address_reg[5]),
        .O(eol1__103_carry__0_i_3_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    eol1__103_carry__0_i_4
       (.I0(address_reg[4]),
        .O(eol1__103_carry__0_i_4_n_0));
  CARRY4 eol1__103_carry__1
       (.CI(eol1__103_carry__0_n_0),
        .CO({NLW_eol1__103_carry__1_CO_UNCONNECTED[3:1],eol1__103_carry__1_n_3}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,address_reg[8]}),
        .O({NLW_eol1__103_carry__1_O_UNCONNECTED[3:2],eol1__103_carry__1_n_6,eol1__103_carry__1_n_7}),
        .S({1'b0,1'b0,eol1__103_carry__1_i_1_n_0,eol1__103_carry__1_i_2_n_0}));
  LUT2 #(
    .INIT(4'h9)) 
    eol1__103_carry__1_i_1
       (.I0(address_reg[9]),
        .I1(eol1__97_carry_n_5),
        .O(eol1__103_carry__1_i_1_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    eol1__103_carry__1_i_2
       (.I0(address_reg[8]),
        .I1(eol1__97_carry_n_6),
        .O(eol1__103_carry__1_i_2_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    eol1__103_carry_i_1
       (.I0(address_reg[3]),
        .O(eol1__103_carry_i_1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    eol1__103_carry_i_2
       (.I0(address_reg[2]),
        .O(eol1__103_carry_i_2_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    eol1__103_carry_i_3
       (.I0(address_reg[1]),
        .O(eol1__103_carry_i_3_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    eol1__103_carry_i_4
       (.I0(address_reg[0]),
        .O(eol1__103_carry_i_4_n_0));
  CARRY4 eol1__60_carry
       (.CI(1'b0),
        .CO({eol1__60_carry_n_0,eol1__60_carry_n_1,eol1__60_carry_n_2,eol1__60_carry_n_3}),
        .CYINIT(1'b0),
        .DI({address_reg[2:0],1'b0}),
        .O(NLW_eol1__60_carry_O_UNCONNECTED[3:0]),
        .S({eol1__60_carry_i_1_n_0,eol1__60_carry_i_2_n_0,eol1__60_carry_i_3_n_0,eol1_carry__0_n_7}));
  CARRY4 eol1__60_carry__0
       (.CI(eol1__60_carry_n_0),
        .CO({eol1__60_carry__0_n_0,eol1__60_carry__0_n_1,eol1__60_carry__0_n_2,eol1__60_carry__0_n_3}),
        .CYINIT(1'b0),
        .DI({eol1__60_carry__0_i_1_n_0,eol1__60_carry__0_i_2_n_0,eol1__60_carry__0_i_3_n_0,address_reg[3]}),
        .O(NLW_eol1__60_carry__0_O_UNCONNECTED[3:0]),
        .S({eol1__60_carry__0_i_4_n_0,eol1__60_carry__0_i_5_n_0,eol1__60_carry__0_i_6_n_0,eol1__60_carry__0_i_7_n_0}));
  LUT5 #(
    .INIT(32'h718E8E71)) 
    eol1__60_carry__0_i_1
       (.I0(address_reg[0]),
        .I1(eol1_carry__1_n_5),
        .I2(address_reg[2]),
        .I3(eol1__60_carry__0_i_8_n_0),
        .I4(address_reg[6]),
        .O(eol1__60_carry__0_i_1_n_0));
  LUT4 #(
    .INIT(16'h9669)) 
    eol1__60_carry__0_i_2
       (.I0(address_reg[2]),
        .I1(eol1_carry__1_n_5),
        .I2(address_reg[0]),
        .I3(address_reg[5]),
        .O(eol1__60_carry__0_i_2_n_0));
  (* HLUTNM = "lutpair13" *) 
  LUT2 #(
    .INIT(4'hB)) 
    eol1__60_carry__0_i_3
       (.I0(eol1_carry__1_n_7),
        .I1(address_reg[0]),
        .O(eol1__60_carry__0_i_3_n_0));
  LUT6 #(
    .INIT(64'h6669966669996669)) 
    eol1__60_carry__0_i_4
       (.I0(address_reg[6]),
        .I1(eol1__60_carry__0_i_8_n_0),
        .I2(address_reg[0]),
        .I3(eol1_carry__1_n_5),
        .I4(address_reg[2]),
        .I5(address_reg[5]),
        .O(eol1__60_carry__0_i_4_n_0));
  LUT4 #(
    .INIT(16'h6A56)) 
    eol1__60_carry__0_i_5
       (.I0(eol1__60_carry__0_i_2_n_0),
        .I1(address_reg[4]),
        .I2(eol1_carry__1_n_6),
        .I3(address_reg[1]),
        .O(eol1__60_carry__0_i_5_n_0));
  LUT4 #(
    .INIT(16'h9669)) 
    eol1__60_carry__0_i_6
       (.I0(eol1__60_carry__0_i_3_n_0),
        .I1(address_reg[1]),
        .I2(eol1_carry__1_n_6),
        .I3(address_reg[4]),
        .O(eol1__60_carry__0_i_6_n_0));
  (* HLUTNM = "lutpair13" *) 
  LUT3 #(
    .INIT(8'h96)) 
    eol1__60_carry__0_i_7
       (.I0(eol1_carry__1_n_7),
        .I1(address_reg[0]),
        .I2(address_reg[3]),
        .O(eol1__60_carry__0_i_7_n_0));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT3 #(
    .INIT(8'h96)) 
    eol1__60_carry__0_i_8
       (.I0(address_reg[1]),
        .I1(eol1_carry__1_n_4),
        .I2(address_reg[3]),
        .O(eol1__60_carry__0_i_8_n_0));
  CARRY4 eol1__60_carry__1
       (.CI(eol1__60_carry__0_n_0),
        .CO({eol1__60_carry__1_n_0,eol1__60_carry__1_n_1,eol1__60_carry__1_n_2,eol1__60_carry__1_n_3}),
        .CYINIT(1'b0),
        .DI({eol1__60_carry__1_i_1_n_0,eol1__60_carry__1_i_2_n_0,eol1__60_carry__1_i_3_n_0,eol1__60_carry__1_i_4_n_0}),
        .O(NLW_eol1__60_carry__1_O_UNCONNECTED[3:0]),
        .S({eol1__60_carry__1_i_5_n_0,eol1__60_carry__1_i_6_n_0,eol1__60_carry__1_i_7_n_0,eol1__60_carry__1_i_8_n_0}));
  LUT5 #(
    .INIT(32'h69FF0069)) 
    eol1__60_carry__1_i_1
       (.I0(address_reg[4]),
        .I1(eol1_carry__2_n_5),
        .I2(address_reg[6]),
        .I3(eol1__60_carry__1_i_9_n_0),
        .I4(address_reg[9]),
        .O(eol1__60_carry__1_i_1_n_0));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT3 #(
    .INIT(8'h2B)) 
    eol1__60_carry__1_i_10
       (.I0(address_reg[4]),
        .I1(eol1_carry__2_n_7),
        .I2(address_reg[2]),
        .O(eol1__60_carry__1_i_10_n_0));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT3 #(
    .INIT(8'h2B)) 
    eol1__60_carry__1_i_11
       (.I0(address_reg[3]),
        .I1(eol1_carry__1_n_4),
        .I2(address_reg[1]),
        .O(eol1__60_carry__1_i_11_n_0));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT3 #(
    .INIT(8'h2B)) 
    eol1__60_carry__1_i_12
       (.I0(address_reg[6]),
        .I1(eol1_carry__2_n_5),
        .I2(address_reg[4]),
        .O(eol1__60_carry__1_i_12_n_0));
  LUT5 #(
    .INIT(32'h6900FF69)) 
    eol1__60_carry__1_i_2
       (.I0(address_reg[3]),
        .I1(eol1_carry__2_n_6),
        .I2(address_reg[5]),
        .I3(address_reg[8]),
        .I4(eol1__60_carry__1_i_10_n_0),
        .O(eol1__60_carry__1_i_2_n_0));
  LUT5 #(
    .INIT(32'h6900FF69)) 
    eol1__60_carry__1_i_3
       (.I0(address_reg[2]),
        .I1(eol1_carry__2_n_7),
        .I2(address_reg[4]),
        .I3(address_reg[7]),
        .I4(eol1__60_carry__1_i_11_n_0),
        .O(eol1__60_carry__1_i_3_n_0));
  LUT5 #(
    .INIT(32'hDD4D4D44)) 
    eol1__60_carry__1_i_4
       (.I0(eol1__60_carry__0_i_8_n_0),
        .I1(address_reg[6]),
        .I2(address_reg[2]),
        .I3(eol1_carry__1_n_5),
        .I4(address_reg[0]),
        .O(eol1__60_carry__1_i_4_n_0));
  LUT6 #(
    .INIT(64'h6996966996696996)) 
    eol1__60_carry__1_i_5
       (.I0(eol1__60_carry__1_i_1_n_0),
        .I1(address_reg[10]),
        .I2(address_reg[7]),
        .I3(eol1_carry__2_n_4),
        .I4(address_reg[5]),
        .I5(eol1__60_carry__1_i_12_n_0),
        .O(eol1__60_carry__1_i_5_n_0));
  LUT6 #(
    .INIT(64'h6996966996696996)) 
    eol1__60_carry__1_i_6
       (.I0(eol1__60_carry__1_i_2_n_0),
        .I1(address_reg[9]),
        .I2(address_reg[6]),
        .I3(eol1_carry__2_n_5),
        .I4(address_reg[4]),
        .I5(eol1__60_carry__1_i_9_n_0),
        .O(eol1__60_carry__1_i_6_n_0));
  LUT6 #(
    .INIT(64'h6996966996696996)) 
    eol1__60_carry__1_i_7
       (.I0(eol1__60_carry__1_i_3_n_0),
        .I1(address_reg[8]),
        .I2(address_reg[5]),
        .I3(eol1_carry__2_n_6),
        .I4(address_reg[3]),
        .I5(eol1__60_carry__1_i_10_n_0),
        .O(eol1__60_carry__1_i_7_n_0));
  LUT6 #(
    .INIT(64'h6996966996696996)) 
    eol1__60_carry__1_i_8
       (.I0(eol1__60_carry__1_i_4_n_0),
        .I1(address_reg[7]),
        .I2(address_reg[4]),
        .I3(eol1_carry__2_n_7),
        .I4(address_reg[2]),
        .I5(eol1__60_carry__1_i_11_n_0),
        .O(eol1__60_carry__1_i_8_n_0));
  LUT3 #(
    .INIT(8'h2B)) 
    eol1__60_carry__1_i_9
       (.I0(address_reg[5]),
        .I1(eol1_carry__2_n_6),
        .I2(address_reg[3]),
        .O(eol1__60_carry__1_i_9_n_0));
  CARRY4 eol1__60_carry__2
       (.CI(eol1__60_carry__1_n_0),
        .CO({eol1__60_carry__2_n_0,eol1__60_carry__2_n_1,eol1__60_carry__2_n_2,eol1__60_carry__2_n_3}),
        .CYINIT(1'b0),
        .DI({eol1__60_carry__2_i_1_n_0,eol1__60_carry__2_i_2_n_0,eol1__60_carry__2_i_3_n_0,eol1__60_carry__2_i_4_n_0}),
        .O({eol1__60_carry__2_n_4,eol1__60_carry__2_n_5,NLW_eol1__60_carry__2_O_UNCONNECTED[1:0]}),
        .S({eol1__60_carry__2_i_5_n_0,eol1__60_carry__2_i_6_n_0,eol1__60_carry__2_i_7_n_0,eol1__60_carry__2_i_8_n_0}));
  LUT5 #(
    .INIT(32'h4DD4D44D)) 
    eol1__60_carry__2_i_1
       (.I0(eol1__60_carry__2_i_9_n_0),
        .I1(address_reg[13]),
        .I2(address_reg[8]),
        .I3(eol1_carry__3_n_5),
        .I4(address_reg[10]),
        .O(eol1__60_carry__2_i_1_n_0));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT3 #(
    .INIT(8'h2B)) 
    eol1__60_carry__2_i_10
       (.I0(address_reg[8]),
        .I1(eol1_carry__3_n_7),
        .I2(address_reg[6]),
        .O(eol1__60_carry__2_i_10_n_0));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT3 #(
    .INIT(8'h2B)) 
    eol1__60_carry__2_i_11
       (.I0(address_reg[7]),
        .I1(eol1_carry__2_n_4),
        .I2(address_reg[5]),
        .O(eol1__60_carry__2_i_11_n_0));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT3 #(
    .INIT(8'h2B)) 
    eol1__60_carry__2_i_12
       (.I0(address_reg[10]),
        .I1(eol1_carry__3_n_5),
        .I2(address_reg[8]),
        .O(eol1__60_carry__2_i_12_n_0));
  LUT5 #(
    .INIT(32'h4DD4D44D)) 
    eol1__60_carry__2_i_2
       (.I0(eol1__60_carry__2_i_10_n_0),
        .I1(address_reg[12]),
        .I2(address_reg[7]),
        .I3(eol1_carry__3_n_6),
        .I4(address_reg[9]),
        .O(eol1__60_carry__2_i_2_n_0));
  LUT5 #(
    .INIT(32'h4DD4D44D)) 
    eol1__60_carry__2_i_3
       (.I0(eol1__60_carry__2_i_11_n_0),
        .I1(address_reg[11]),
        .I2(address_reg[6]),
        .I3(eol1_carry__3_n_7),
        .I4(address_reg[8]),
        .O(eol1__60_carry__2_i_3_n_0));
  LUT5 #(
    .INIT(32'h69FF0069)) 
    eol1__60_carry__2_i_4
       (.I0(address_reg[5]),
        .I1(eol1_carry__2_n_4),
        .I2(address_reg[7]),
        .I3(eol1__60_carry__1_i_12_n_0),
        .I4(address_reg[10]),
        .O(eol1__60_carry__2_i_4_n_0));
  LUT6 #(
    .INIT(64'h6996966996696996)) 
    eol1__60_carry__2_i_5
       (.I0(eol1__60_carry__2_i_1_n_0),
        .I1(address_reg[14]),
        .I2(address_reg[11]),
        .I3(eol1_carry__3_n_4),
        .I4(address_reg[9]),
        .I5(eol1__60_carry__2_i_12_n_0),
        .O(eol1__60_carry__2_i_5_n_0));
  LUT6 #(
    .INIT(64'h6996966996696996)) 
    eol1__60_carry__2_i_6
       (.I0(eol1__60_carry__2_i_2_n_0),
        .I1(address_reg[13]),
        .I2(address_reg[10]),
        .I3(eol1_carry__3_n_5),
        .I4(address_reg[8]),
        .I5(eol1__60_carry__2_i_9_n_0),
        .O(eol1__60_carry__2_i_6_n_0));
  LUT6 #(
    .INIT(64'h6996966996696996)) 
    eol1__60_carry__2_i_7
       (.I0(eol1__60_carry__2_i_3_n_0),
        .I1(address_reg[12]),
        .I2(address_reg[9]),
        .I3(eol1_carry__3_n_6),
        .I4(address_reg[7]),
        .I5(eol1__60_carry__2_i_10_n_0),
        .O(eol1__60_carry__2_i_7_n_0));
  LUT6 #(
    .INIT(64'h6996966996696996)) 
    eol1__60_carry__2_i_8
       (.I0(eol1__60_carry__2_i_4_n_0),
        .I1(address_reg[11]),
        .I2(address_reg[8]),
        .I3(eol1_carry__3_n_7),
        .I4(address_reg[6]),
        .I5(eol1__60_carry__2_i_11_n_0),
        .O(eol1__60_carry__2_i_8_n_0));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT3 #(
    .INIT(8'h2B)) 
    eol1__60_carry__2_i_9
       (.I0(address_reg[9]),
        .I1(eol1_carry__3_n_6),
        .I2(address_reg[7]),
        .O(eol1__60_carry__2_i_9_n_0));
  CARRY4 eol1__60_carry__3
       (.CI(eol1__60_carry__2_n_0),
        .CO({NLW_eol1__60_carry__3_CO_UNCONNECTED[3:1],eol1__60_carry__3_n_3}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,eol1__60_carry__3_i_1_n_0}),
        .O({NLW_eol1__60_carry__3_O_UNCONNECTED[3:2],eol1__60_carry__3_n_6,eol1__60_carry__3_n_7}),
        .S({1'b0,1'b0,eol1__60_carry__3_i_2_n_0,eol1__60_carry__3_i_3_n_0}));
  LUT5 #(
    .INIT(32'h4DD4D44D)) 
    eol1__60_carry__3_i_1
       (.I0(eol1__60_carry__2_i_12_n_0),
        .I1(address_reg[14]),
        .I2(address_reg[9]),
        .I3(eol1_carry__3_n_4),
        .I4(address_reg[11]),
        .O(eol1__60_carry__3_i_1_n_0));
  LUT6 #(
    .INIT(64'h6559A665599A6559)) 
    eol1__60_carry__3_i_2
       (.I0(eol1__60_carry__3_i_4_n_0),
        .I1(address_reg[12]),
        .I2(eol1_carry__4_n_7),
        .I3(address_reg[10]),
        .I4(eol1__60_carry__3_i_5_n_0),
        .I5(address_reg[15]),
        .O(eol1__60_carry__3_i_2_n_0));
  LUT6 #(
    .INIT(64'h6996966996696996)) 
    eol1__60_carry__3_i_3
       (.I0(eol1__60_carry__3_i_1_n_0),
        .I1(address_reg[15]),
        .I2(address_reg[12]),
        .I3(eol1_carry__4_n_7),
        .I4(address_reg[10]),
        .I5(eol1__60_carry__3_i_5_n_0),
        .O(eol1__60_carry__3_i_3_n_0));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT4 #(
    .INIT(16'h9669)) 
    eol1__60_carry__3_i_4
       (.I0(address_reg[16]),
        .I1(address_reg[13]),
        .I2(eol1_carry__4_n_6),
        .I3(address_reg[11]),
        .O(eol1__60_carry__3_i_4_n_0));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT3 #(
    .INIT(8'h2B)) 
    eol1__60_carry__3_i_5
       (.I0(address_reg[11]),
        .I1(eol1_carry__3_n_4),
        .I2(address_reg[9]),
        .O(eol1__60_carry__3_i_5_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    eol1__60_carry_i_1
       (.I0(address_reg[2]),
        .I1(eol1_carry__0_n_4),
        .O(eol1__60_carry_i_1_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    eol1__60_carry_i_2
       (.I0(address_reg[1]),
        .I1(eol1_carry__0_n_5),
        .O(eol1__60_carry_i_2_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    eol1__60_carry_i_3
       (.I0(address_reg[0]),
        .I1(eol1_carry__0_n_6),
        .O(eol1__60_carry_i_3_n_0));
  CARRY4 eol1__97_carry
       (.CI(1'b0),
        .CO({NLW_eol1__97_carry_CO_UNCONNECTED[3:2],eol1__97_carry_n_2,eol1__97_carry_n_3}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,eol1__60_carry__3_n_7,1'b0}),
        .O({NLW_eol1__97_carry_O_UNCONNECTED[3],eol1__97_carry_n_5,eol1__97_carry_n_6,eol1__97_carry_n_7}),
        .S({1'b0,eol1__97_carry_i_1_n_0,eol1__97_carry_i_2_n_0,eol1__60_carry__2_n_4}));
  LUT2 #(
    .INIT(4'h6)) 
    eol1__97_carry_i_1
       (.I0(eol1__60_carry__2_n_4),
        .I1(eol1__60_carry__3_n_6),
        .O(eol1__97_carry_i_1_n_0));
  LUT2 #(
    .INIT(4'h6)) 
    eol1__97_carry_i_2
       (.I0(eol1__60_carry__3_n_7),
        .I1(eol1__60_carry__2_n_5),
        .O(eol1__97_carry_i_2_n_0));
  CARRY4 eol1_carry
       (.CI(1'b0),
        .CO({eol1_carry_n_0,eol1_carry_n_1,eol1_carry_n_2,eol1_carry_n_3}),
        .CYINIT(1'b0),
        .DI({address_reg[1:0],1'b0,1'b1}),
        .O(NLW_eol1_carry_O_UNCONNECTED[3:0]),
        .S({eol1_carry_i_1_n_0,eol1_carry_i_2_n_0,eol1_carry_i_3_n_0,address_reg[0]}));
  CARRY4 eol1_carry__0
       (.CI(eol1_carry_n_0),
        .CO({eol1_carry__0_n_0,eol1_carry__0_n_1,eol1_carry__0_n_2,eol1_carry__0_n_3}),
        .CYINIT(1'b0),
        .DI({eol1_carry__0_i_1_n_0,eol1_carry__0_i_2_n_0,eol1_carry__0_i_3_n_0,address_reg[2]}),
        .O({eol1_carry__0_n_4,eol1_carry__0_n_5,eol1_carry__0_n_6,eol1_carry__0_n_7}),
        .S({eol1_carry__0_i_4_n_0,eol1_carry__0_i_5_n_0,eol1_carry__0_i_6_n_0,eol1_carry__0_i_7_n_0}));
  (* HLUTNM = "lutpair1" *) 
  LUT3 #(
    .INIT(8'hD4)) 
    eol1_carry__0_i_1
       (.I0(address_reg[6]),
        .I1(address_reg[2]),
        .I2(address_reg[4]),
        .O(eol1_carry__0_i_1_n_0));
  (* HLUTNM = "lutpair0" *) 
  LUT3 #(
    .INIT(8'hB2)) 
    eol1_carry__0_i_2
       (.I0(address_reg[1]),
        .I1(address_reg[5]),
        .I2(address_reg[3]),
        .O(eol1_carry__0_i_2_n_0));
  LUT3 #(
    .INIT(8'h69)) 
    eol1_carry__0_i_3
       (.I0(address_reg[3]),
        .I1(address_reg[5]),
        .I2(address_reg[1]),
        .O(eol1_carry__0_i_3_n_0));
  (* HLUTNM = "lutpair2" *) 
  LUT4 #(
    .INIT(16'h9669)) 
    eol1_carry__0_i_4
       (.I0(address_reg[7]),
        .I1(address_reg[3]),
        .I2(address_reg[5]),
        .I3(eol1_carry__0_i_1_n_0),
        .O(eol1_carry__0_i_4_n_0));
  (* HLUTNM = "lutpair1" *) 
  LUT4 #(
    .INIT(16'h9669)) 
    eol1_carry__0_i_5
       (.I0(address_reg[6]),
        .I1(address_reg[2]),
        .I2(address_reg[4]),
        .I3(eol1_carry__0_i_2_n_0),
        .O(eol1_carry__0_i_5_n_0));
  (* HLUTNM = "lutpair0" *) 
  LUT5 #(
    .INIT(32'h69966969)) 
    eol1_carry__0_i_6
       (.I0(address_reg[1]),
        .I1(address_reg[5]),
        .I2(address_reg[3]),
        .I3(address_reg[4]),
        .I4(address_reg[0]),
        .O(eol1_carry__0_i_6_n_0));
  LUT3 #(
    .INIT(8'h69)) 
    eol1_carry__0_i_7
       (.I0(address_reg[4]),
        .I1(address_reg[0]),
        .I2(address_reg[2]),
        .O(eol1_carry__0_i_7_n_0));
  CARRY4 eol1_carry__1
       (.CI(eol1_carry__0_n_0),
        .CO({eol1_carry__1_n_0,eol1_carry__1_n_1,eol1_carry__1_n_2,eol1_carry__1_n_3}),
        .CYINIT(1'b0),
        .DI({eol1_carry__1_i_1_n_0,eol1_carry__1_i_2_n_0,eol1_carry__1_i_3_n_0,eol1_carry__1_i_4_n_0}),
        .O({eol1_carry__1_n_4,eol1_carry__1_n_5,eol1_carry__1_n_6,eol1_carry__1_n_7}),
        .S({eol1_carry__1_i_5_n_0,eol1_carry__1_i_6_n_0,eol1_carry__1_i_7_n_0,eol1_carry__1_i_8_n_0}));
  (* HLUTNM = "lutpair5" *) 
  LUT3 #(
    .INIT(8'hB2)) 
    eol1_carry__1_i_1
       (.I0(address_reg[6]),
        .I1(address_reg[10]),
        .I2(address_reg[8]),
        .O(eol1_carry__1_i_1_n_0));
  (* HLUTNM = "lutpair4" *) 
  LUT3 #(
    .INIT(8'hB2)) 
    eol1_carry__1_i_2
       (.I0(address_reg[5]),
        .I1(address_reg[9]),
        .I2(address_reg[7]),
        .O(eol1_carry__1_i_2_n_0));
  (* HLUTNM = "lutpair3" *) 
  LUT3 #(
    .INIT(8'hB2)) 
    eol1_carry__1_i_3
       (.I0(address_reg[4]),
        .I1(address_reg[8]),
        .I2(address_reg[6]),
        .O(eol1_carry__1_i_3_n_0));
  (* HLUTNM = "lutpair2" *) 
  LUT3 #(
    .INIT(8'hD4)) 
    eol1_carry__1_i_4
       (.I0(address_reg[7]),
        .I1(address_reg[3]),
        .I2(address_reg[5]),
        .O(eol1_carry__1_i_4_n_0));
  (* HLUTNM = "lutpair6" *) 
  LUT4 #(
    .INIT(16'h9669)) 
    eol1_carry__1_i_5
       (.I0(address_reg[7]),
        .I1(address_reg[11]),
        .I2(address_reg[9]),
        .I3(eol1_carry__1_i_1_n_0),
        .O(eol1_carry__1_i_5_n_0));
  (* HLUTNM = "lutpair5" *) 
  LUT4 #(
    .INIT(16'h9669)) 
    eol1_carry__1_i_6
       (.I0(address_reg[6]),
        .I1(address_reg[10]),
        .I2(address_reg[8]),
        .I3(eol1_carry__1_i_2_n_0),
        .O(eol1_carry__1_i_6_n_0));
  (* HLUTNM = "lutpair4" *) 
  LUT4 #(
    .INIT(16'h9669)) 
    eol1_carry__1_i_7
       (.I0(address_reg[5]),
        .I1(address_reg[9]),
        .I2(address_reg[7]),
        .I3(eol1_carry__1_i_3_n_0),
        .O(eol1_carry__1_i_7_n_0));
  (* HLUTNM = "lutpair3" *) 
  LUT4 #(
    .INIT(16'h9669)) 
    eol1_carry__1_i_8
       (.I0(address_reg[4]),
        .I1(address_reg[8]),
        .I2(address_reg[6]),
        .I3(eol1_carry__1_i_4_n_0),
        .O(eol1_carry__1_i_8_n_0));
  CARRY4 eol1_carry__2
       (.CI(eol1_carry__1_n_0),
        .CO({eol1_carry__2_n_0,eol1_carry__2_n_1,eol1_carry__2_n_2,eol1_carry__2_n_3}),
        .CYINIT(1'b0),
        .DI({eol1_carry__2_i_1_n_0,eol1_carry__2_i_2_n_0,eol1_carry__2_i_3_n_0,eol1_carry__2_i_4_n_0}),
        .O({eol1_carry__2_n_4,eol1_carry__2_n_5,eol1_carry__2_n_6,eol1_carry__2_n_7}),
        .S({eol1_carry__2_i_5_n_0,eol1_carry__2_i_6_n_0,eol1_carry__2_i_7_n_0,eol1_carry__2_i_8_n_0}));
  (* HLUTNM = "lutpair9" *) 
  LUT3 #(
    .INIT(8'hB2)) 
    eol1_carry__2_i_1
       (.I0(address_reg[10]),
        .I1(address_reg[14]),
        .I2(address_reg[12]),
        .O(eol1_carry__2_i_1_n_0));
  (* HLUTNM = "lutpair8" *) 
  LUT3 #(
    .INIT(8'hB2)) 
    eol1_carry__2_i_2
       (.I0(address_reg[9]),
        .I1(address_reg[13]),
        .I2(address_reg[11]),
        .O(eol1_carry__2_i_2_n_0));
  (* HLUTNM = "lutpair7" *) 
  LUT3 #(
    .INIT(8'hB2)) 
    eol1_carry__2_i_3
       (.I0(address_reg[8]),
        .I1(address_reg[12]),
        .I2(address_reg[10]),
        .O(eol1_carry__2_i_3_n_0));
  (* HLUTNM = "lutpair6" *) 
  LUT3 #(
    .INIT(8'hB2)) 
    eol1_carry__2_i_4
       (.I0(address_reg[7]),
        .I1(address_reg[11]),
        .I2(address_reg[9]),
        .O(eol1_carry__2_i_4_n_0));
  (* HLUTNM = "lutpair10" *) 
  LUT4 #(
    .INIT(16'h9669)) 
    eol1_carry__2_i_5
       (.I0(address_reg[13]),
        .I1(address_reg[15]),
        .I2(address_reg[11]),
        .I3(eol1_carry__2_i_1_n_0),
        .O(eol1_carry__2_i_5_n_0));
  (* HLUTNM = "lutpair9" *) 
  LUT4 #(
    .INIT(16'h9669)) 
    eol1_carry__2_i_6
       (.I0(address_reg[10]),
        .I1(address_reg[14]),
        .I2(address_reg[12]),
        .I3(eol1_carry__2_i_2_n_0),
        .O(eol1_carry__2_i_6_n_0));
  (* HLUTNM = "lutpair8" *) 
  LUT4 #(
    .INIT(16'h9669)) 
    eol1_carry__2_i_7
       (.I0(address_reg[9]),
        .I1(address_reg[13]),
        .I2(address_reg[11]),
        .I3(eol1_carry__2_i_3_n_0),
        .O(eol1_carry__2_i_7_n_0));
  (* HLUTNM = "lutpair7" *) 
  LUT4 #(
    .INIT(16'h9669)) 
    eol1_carry__2_i_8
       (.I0(address_reg[8]),
        .I1(address_reg[12]),
        .I2(address_reg[10]),
        .I3(eol1_carry__2_i_4_n_0),
        .O(eol1_carry__2_i_8_n_0));
  CARRY4 eol1_carry__3
       (.CI(eol1_carry__2_n_0),
        .CO({eol1_carry__3_n_0,eol1_carry__3_n_1,eol1_carry__3_n_2,eol1_carry__3_n_3}),
        .CYINIT(1'b0),
        .DI({eol1_carry__3_i_1_n_0,eol1_carry__3_i_2_n_0,eol1_carry__3_i_3_n_0,eol1_carry__3_i_4_n_0}),
        .O({eol1_carry__3_n_4,eol1_carry__3_n_5,eol1_carry__3_n_6,eol1_carry__3_n_7}),
        .S({eol1_carry__3_i_5_n_0,eol1_carry__3_i_6_n_0,eol1_carry__3_i_7_n_0,eol1_carry__3_i_8_n_0}));
  LUT3 #(
    .INIT(8'hB2)) 
    eol1_carry__3_i_1
       (.I0(address_reg[16]),
        .I1(address_reg[18]),
        .I2(address_reg[14]),
        .O(eol1_carry__3_i_1_n_0));
  (* HLUTNM = "lutpair12" *) 
  LUT3 #(
    .INIT(8'hB2)) 
    eol1_carry__3_i_2
       (.I0(address_reg[15]),
        .I1(address_reg[17]),
        .I2(address_reg[13]),
        .O(eol1_carry__3_i_2_n_0));
  (* HLUTNM = "lutpair11" *) 
  LUT3 #(
    .INIT(8'hB2)) 
    eol1_carry__3_i_3
       (.I0(address_reg[12]),
        .I1(address_reg[16]),
        .I2(address_reg[14]),
        .O(eol1_carry__3_i_3_n_0));
  (* HLUTNM = "lutpair10" *) 
  LUT3 #(
    .INIT(8'hB2)) 
    eol1_carry__3_i_4
       (.I0(address_reg[13]),
        .I1(address_reg[15]),
        .I2(address_reg[11]),
        .O(eol1_carry__3_i_4_n_0));
  LUT5 #(
    .INIT(32'h4DB2B24D)) 
    eol1_carry__3_i_5
       (.I0(address_reg[14]),
        .I1(address_reg[18]),
        .I2(address_reg[16]),
        .I3(address_reg[17]),
        .I4(address_reg[15]),
        .O(eol1_carry__3_i_5_n_0));
  LUT4 #(
    .INIT(16'h9669)) 
    eol1_carry__3_i_6
       (.I0(eol1_carry__3_i_2_n_0),
        .I1(address_reg[16]),
        .I2(address_reg[18]),
        .I3(address_reg[14]),
        .O(eol1_carry__3_i_6_n_0));
  (* HLUTNM = "lutpair12" *) 
  LUT4 #(
    .INIT(16'h9669)) 
    eol1_carry__3_i_7
       (.I0(address_reg[15]),
        .I1(address_reg[17]),
        .I2(address_reg[13]),
        .I3(eol1_carry__3_i_3_n_0),
        .O(eol1_carry__3_i_7_n_0));
  (* HLUTNM = "lutpair11" *) 
  LUT4 #(
    .INIT(16'h9669)) 
    eol1_carry__3_i_8
       (.I0(address_reg[12]),
        .I1(address_reg[16]),
        .I2(address_reg[14]),
        .I3(eol1_carry__3_i_4_n_0),
        .O(eol1_carry__3_i_8_n_0));
  CARRY4 eol1_carry__4
       (.CI(eol1_carry__3_n_0),
        .CO({NLW_eol1_carry__4_CO_UNCONNECTED[3:1],eol1_carry__4_n_3}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,eol1_carry__4_i_1_n_0}),
        .O({NLW_eol1_carry__4_O_UNCONNECTED[3:2],eol1_carry__4_n_6,eol1_carry__4_n_7}),
        .S({1'b0,1'b0,eol1_carry__4_i_2_n_0,eol1_carry__4_i_3_n_0}));
  LUT2 #(
    .INIT(4'hE)) 
    eol1_carry__4_i_1
       (.I0(address_reg[17]),
        .I1(address_reg[15]),
        .O(eol1_carry__4_i_1_n_0));
  LUT3 #(
    .INIT(8'hA9)) 
    eol1_carry__4_i_2
       (.I0(address_reg[17]),
        .I1(address_reg[18]),
        .I2(address_reg[16]),
        .O(eol1_carry__4_i_2_n_0));
  LUT4 #(
    .INIT(16'h1EE1)) 
    eol1_carry__4_i_3
       (.I0(address_reg[17]),
        .I1(address_reg[15]),
        .I2(address_reg[18]),
        .I3(address_reg[16]),
        .O(eol1_carry__4_i_3_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    eol1_carry_i_1
       (.I0(address_reg[1]),
        .I1(address_reg[3]),
        .O(eol1_carry_i_1_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    eol1_carry_i_2
       (.I0(address_reg[0]),
        .I1(address_reg[2]),
        .O(eol1_carry_i_2_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    eol1_carry_i_3
       (.I0(address_reg[1]),
        .O(eol1_carry_i_3_n_0));
  LUT5 #(
    .INIT(32'h00000040)) 
    eol_i_1
       (.I0(eol_i_2_n_0),
        .I1(sel0[2]),
        .I2(sel0[5]),
        .I3(eol1__103_carry__0_n_4),
        .I4(eol_i_3_n_0),
        .O(eol_i_1_n_0));
  LUT4 #(
    .INIT(16'h7FFF)) 
    eol_i_2
       (.I0(sel0[3]),
        .I1(sel0[0]),
        .I2(sel0[4]),
        .I3(sel0[1]),
        .O(eol_i_2_n_0));
  LUT3 #(
    .INIT(8'hBD)) 
    eol_i_3
       (.I0(eol1__103_carry__1_n_7),
        .I1(eol1__103_carry__0_n_5),
        .I2(eol1__103_carry__1_n_6),
        .O(eol_i_3_n_0));
  FDRE #(
    .INIT(1'b0)) 
    eol_reg
       (.C(pclk),
        .CE(1'b1),
        .D(eol_i_1_n_0),
        .Q(m_axis_tlast),
        .R(1'b0));
  (* SOFT_HLUTNM = "soft_lutpair6" *) 
  LUT3 #(
    .INIT(8'h04)) 
    \href_last[0]_i_1 
       (.I0(href_last),
        .I1(latched_href),
        .I2(latched_vsync),
        .O(\href_last[0]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \href_last_reg[0] 
       (.C(pclk),
        .CE(1'b1),
        .D(\href_last[0]_i_1_n_0 ),
        .Q(href_last),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0),
    .IS_C_INVERTED(1'b1)) 
    \latched_d_reg[0] 
       (.C(pclk),
        .CE(1'b1),
        .D(d[0]),
        .Q(p_0_in[0]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0),
    .IS_C_INVERTED(1'b1)) 
    \latched_d_reg[1] 
       (.C(pclk),
        .CE(1'b1),
        .D(d[1]),
        .Q(p_0_in[1]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0),
    .IS_C_INVERTED(1'b1)) 
    \latched_d_reg[2] 
       (.C(pclk),
        .CE(1'b1),
        .D(d[2]),
        .Q(p_0_in[2]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0),
    .IS_C_INVERTED(1'b1)) 
    \latched_d_reg[3] 
       (.C(pclk),
        .CE(1'b1),
        .D(d[3]),
        .Q(p_0_in[3]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0),
    .IS_C_INVERTED(1'b1)) 
    \latched_d_reg[4] 
       (.C(pclk),
        .CE(1'b1),
        .D(d[4]),
        .Q(p_0_in[4]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0),
    .IS_C_INVERTED(1'b1)) 
    \latched_d_reg[5] 
       (.C(pclk),
        .CE(1'b1),
        .D(d[5]),
        .Q(p_0_in[5]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0),
    .IS_C_INVERTED(1'b1)) 
    \latched_d_reg[6] 
       (.C(pclk),
        .CE(1'b1),
        .D(d[6]),
        .Q(p_0_in[6]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0),
    .IS_C_INVERTED(1'b1)) 
    \latched_d_reg[7] 
       (.C(pclk),
        .CE(1'b1),
        .D(d[7]),
        .Q(p_0_in[7]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0),
    .IS_C_INVERTED(1'b1)) 
    latched_href_reg
       (.C(pclk),
        .CE(1'b1),
        .D(href),
        .Q(latched_href),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0),
    .IS_C_INVERTED(1'b1)) 
    latched_vsync_reg
       (.C(pclk),
        .CE(1'b1),
        .D(vsync),
        .Q(latched_vsync),
        .R(1'b0));
  LUT5 #(
    .INIT(32'h00000002)) 
    sof_i_1
       (.I0(sof_i_2_n_0),
        .I1(sof_i_3_n_0),
        .I2(address_reg[0]),
        .I3(address_reg[14]),
        .I4(address_reg[10]),
        .O(sof_i_1_n_0));
  LUT6 #(
    .INIT(64'h0000000000000004)) 
    sof_i_2
       (.I0(sof_i_4_n_0),
        .I1(sof_i_5_n_0),
        .I2(address_reg[1]),
        .I3(address_reg[3]),
        .I4(address_reg[11]),
        .I5(address_reg[13]),
        .O(sof_i_2_n_0));
  LUT5 #(
    .INIT(32'hFFFFFFFE)) 
    sof_i_3
       (.I0(address_reg[4]),
        .I1(address_reg[6]),
        .I2(address_reg[2]),
        .I3(address_reg[9]),
        .I4(sof_i_6_n_0),
        .O(sof_i_3_n_0));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT2 #(
    .INIT(4'hE)) 
    sof_i_4
       (.I0(address_reg[16]),
        .I1(address_reg[18]),
        .O(sof_i_4_n_0));
  LUT2 #(
    .INIT(4'h1)) 
    sof_i_5
       (.I0(address_reg[15]),
        .I1(address_reg[17]),
        .O(sof_i_5_n_0));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT4 #(
    .INIT(16'hFFFE)) 
    sof_i_6
       (.I0(address_reg[12]),
        .I1(address_reg[8]),
        .I2(address_reg[7]),
        .I3(address_reg[5]),
        .O(sof_i_6_n_0));
  FDRE #(
    .INIT(1'b0)) 
    sof_reg
       (.C(pclk),
        .CE(1'b1),
        .D(sof_i_1_n_0),
        .Q(m_axis_tuser),
        .R(1'b0));
  (* SOFT_HLUTNM = "soft_lutpair6" *) 
  LUT2 #(
    .INIT(4'h2)) 
    we_reg_i_1
       (.I0(href_last),
        .I1(latched_vsync),
        .O(we_reg_i_1_n_0));
  FDRE #(
    .INIT(1'b0)) 
    we_reg_reg
       (.C(pclk),
        .CE(1'b1),
        .D(we_reg_i_1_n_0),
        .Q(m_axis_tvalid),
        .R(1'b0));
endmodule
`ifndef GLBL
`define GLBL
`timescale  1 ps / 1 ps

module glbl ();

    parameter ROC_WIDTH = 100000;
    parameter TOC_WIDTH = 0;

//--------   STARTUP Globals --------------
    wire GSR;
    wire GTS;
    wire GWE;
    wire PRLD;
    tri1 p_up_tmp;
    tri (weak1, strong0) PLL_LOCKG = p_up_tmp;

    wire PROGB_GLBL;
    wire CCLKO_GLBL;
    wire FCSBO_GLBL;
    wire [3:0] DO_GLBL;
    wire [3:0] DI_GLBL;
   
    reg GSR_int;
    reg GTS_int;
    reg PRLD_int;

//--------   JTAG Globals --------------
    wire JTAG_TDO_GLBL;
    wire JTAG_TCK_GLBL;
    wire JTAG_TDI_GLBL;
    wire JTAG_TMS_GLBL;
    wire JTAG_TRST_GLBL;

    reg JTAG_CAPTURE_GLBL;
    reg JTAG_RESET_GLBL;
    reg JTAG_SHIFT_GLBL;
    reg JTAG_UPDATE_GLBL;
    reg JTAG_RUNTEST_GLBL;

    reg JTAG_SEL1_GLBL = 0;
    reg JTAG_SEL2_GLBL = 0 ;
    reg JTAG_SEL3_GLBL = 0;
    reg JTAG_SEL4_GLBL = 0;

    reg JTAG_USER_TDO1_GLBL = 1'bz;
    reg JTAG_USER_TDO2_GLBL = 1'bz;
    reg JTAG_USER_TDO3_GLBL = 1'bz;
    reg JTAG_USER_TDO4_GLBL = 1'bz;

    assign (strong1, weak0) GSR = GSR_int;
    assign (strong1, weak0) GTS = GTS_int;
    assign (weak1, weak0) PRLD = PRLD_int;

    initial begin
	GSR_int = 1'b1;
	PRLD_int = 1'b1;
	#(ROC_WIDTH)
	GSR_int = 1'b0;
	PRLD_int = 1'b0;
    end

    initial begin
	GTS_int = 1'b1;
	#(TOC_WIDTH)
	GTS_int = 1'b0;
    end

endmodule
`endif
