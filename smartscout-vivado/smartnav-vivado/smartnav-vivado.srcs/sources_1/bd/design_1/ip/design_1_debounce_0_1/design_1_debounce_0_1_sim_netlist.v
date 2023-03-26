// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2019.1 (lin64) Build 2552052 Fri May 24 14:47:09 MDT 2019
// Date        : Tue Mar 14 20:17:56 2023
// Host        : kuhiu-Aspire-A515-51G running 64-bit Ubuntu 18.04.6 LTS
// Command     : write_verilog -force -mode funcsim
//               /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_debounce_0_1/design_1_debounce_0_1_sim_netlist.v
// Design      : design_1_debounce_0_1
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xc7z010clg400-1
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "design_1_debounce_0_1,debounce,{}" *) (* downgradeipidentifiedwarnings = "yes" *) (* ip_definition_source = "package_project" *) 
(* x_core_info = "debounce,Vivado 2019.1" *) 
(* NotValidForBitStream *)
module design_1_debounce_0_1
   (clk,
    reset_n,
    button,
    result);
  (* x_interface_info = "xilinx.com:signal:clock:1.0 clk CLK" *) (* x_interface_parameter = "XIL_INTERFACENAME clk, FREQ_HZ 1e+08, PHASE 0.000, CLK_DOMAIN design_1_processing_system7_0_0_FCLK_CLK0, INSERT_VIP 0" *) input clk;
  (* x_interface_info = "xilinx.com:signal:reset:1.0 reset_n RST" *) (* x_interface_parameter = "XIL_INTERFACENAME reset_n, POLARITY ACTIVE_LOW, INSERT_VIP 0" *) input reset_n;
  input button;
  output result;

  wire button;
  wire clk;
  wire reset_n;
  wire result;

  design_1_debounce_0_1_debounce U0
       (.button(button),
        .clk(clk),
        .reset_n(reset_n),
        .result(result));
endmodule

(* ORIG_REF_NAME = "debounce" *) 
module design_1_debounce_0_1_debounce
   (result,
    clk,
    button,
    reset_n);
  output result;
  input clk;
  input button;
  input reset_n;

  wire button;
  wire clk;
  wire count0;
  wire \count[0]_i_1_n_0 ;
  wire \count[0]_i_4_n_0 ;
  wire [20:7]count_reg;
  wire \count_reg[0]_i_3_n_0 ;
  wire \count_reg[0]_i_3_n_1 ;
  wire \count_reg[0]_i_3_n_2 ;
  wire \count_reg[0]_i_3_n_3 ;
  wire \count_reg[0]_i_3_n_4 ;
  wire \count_reg[0]_i_3_n_5 ;
  wire \count_reg[0]_i_3_n_6 ;
  wire \count_reg[0]_i_3_n_7 ;
  wire \count_reg[12]_i_1_n_0 ;
  wire \count_reg[12]_i_1_n_1 ;
  wire \count_reg[12]_i_1_n_2 ;
  wire \count_reg[12]_i_1_n_3 ;
  wire \count_reg[12]_i_1_n_4 ;
  wire \count_reg[12]_i_1_n_5 ;
  wire \count_reg[12]_i_1_n_6 ;
  wire \count_reg[12]_i_1_n_7 ;
  wire \count_reg[16]_i_1_n_0 ;
  wire \count_reg[16]_i_1_n_1 ;
  wire \count_reg[16]_i_1_n_2 ;
  wire \count_reg[16]_i_1_n_3 ;
  wire \count_reg[16]_i_1_n_4 ;
  wire \count_reg[16]_i_1_n_5 ;
  wire \count_reg[16]_i_1_n_6 ;
  wire \count_reg[16]_i_1_n_7 ;
  wire \count_reg[20]_i_1_n_7 ;
  wire \count_reg[4]_i_1_n_0 ;
  wire \count_reg[4]_i_1_n_1 ;
  wire \count_reg[4]_i_1_n_2 ;
  wire \count_reg[4]_i_1_n_3 ;
  wire \count_reg[4]_i_1_n_4 ;
  wire \count_reg[4]_i_1_n_5 ;
  wire \count_reg[4]_i_1_n_6 ;
  wire \count_reg[4]_i_1_n_7 ;
  wire \count_reg[8]_i_1_n_0 ;
  wire \count_reg[8]_i_1_n_1 ;
  wire \count_reg[8]_i_1_n_2 ;
  wire \count_reg[8]_i_1_n_3 ;
  wire \count_reg[8]_i_1_n_4 ;
  wire \count_reg[8]_i_1_n_5 ;
  wire \count_reg[8]_i_1_n_6 ;
  wire \count_reg[8]_i_1_n_7 ;
  wire \count_reg_n_0_[0] ;
  wire \count_reg_n_0_[1] ;
  wire \count_reg_n_0_[2] ;
  wire \count_reg_n_0_[3] ;
  wire \count_reg_n_0_[4] ;
  wire \count_reg_n_0_[5] ;
  wire \count_reg_n_0_[6] ;
  wire \flipflops_reg_n_0_[0] ;
  wire p_0_in;
  wire p_0_in_0;
  wire reset_n;
  wire result;
  wire result_i_1_n_0;
  wire result_i_3_n_0;
  wire result_i_4_n_0;
  wire result_i_5_n_0;
  wire result_i_6_n_0;
  wire [3:0]\NLW_count_reg[20]_i_1_CO_UNCONNECTED ;
  wire [3:1]\NLW_count_reg[20]_i_1_O_UNCONNECTED ;

  LUT3 #(
    .INIT(8'h28)) 
    \count[0]_i_1 
       (.I0(reset_n),
        .I1(\flipflops_reg_n_0_[0] ),
        .I2(p_0_in_0),
        .O(\count[0]_i_1_n_0 ));
  LUT2 #(
    .INIT(4'h8)) 
    \count[0]_i_2 
       (.I0(reset_n),
        .I1(result_i_3_n_0),
        .O(count0));
  LUT1 #(
    .INIT(2'h1)) 
    \count[0]_i_4 
       (.I0(\count_reg_n_0_[0] ),
        .O(\count[0]_i_4_n_0 ));
  FDRE \count_reg[0] 
       (.C(clk),
        .CE(count0),
        .D(\count_reg[0]_i_3_n_7 ),
        .Q(\count_reg_n_0_[0] ),
        .R(\count[0]_i_1_n_0 ));
  CARRY4 \count_reg[0]_i_3 
       (.CI(1'b0),
        .CO({\count_reg[0]_i_3_n_0 ,\count_reg[0]_i_3_n_1 ,\count_reg[0]_i_3_n_2 ,\count_reg[0]_i_3_n_3 }),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b1}),
        .O({\count_reg[0]_i_3_n_4 ,\count_reg[0]_i_3_n_5 ,\count_reg[0]_i_3_n_6 ,\count_reg[0]_i_3_n_7 }),
        .S({\count_reg_n_0_[3] ,\count_reg_n_0_[2] ,\count_reg_n_0_[1] ,\count[0]_i_4_n_0 }));
  FDRE \count_reg[10] 
       (.C(clk),
        .CE(count0),
        .D(\count_reg[8]_i_1_n_5 ),
        .Q(count_reg[10]),
        .R(\count[0]_i_1_n_0 ));
  FDRE \count_reg[11] 
       (.C(clk),
        .CE(count0),
        .D(\count_reg[8]_i_1_n_4 ),
        .Q(count_reg[11]),
        .R(\count[0]_i_1_n_0 ));
  FDRE \count_reg[12] 
       (.C(clk),
        .CE(count0),
        .D(\count_reg[12]_i_1_n_7 ),
        .Q(count_reg[12]),
        .R(\count[0]_i_1_n_0 ));
  CARRY4 \count_reg[12]_i_1 
       (.CI(\count_reg[8]_i_1_n_0 ),
        .CO({\count_reg[12]_i_1_n_0 ,\count_reg[12]_i_1_n_1 ,\count_reg[12]_i_1_n_2 ,\count_reg[12]_i_1_n_3 }),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\count_reg[12]_i_1_n_4 ,\count_reg[12]_i_1_n_5 ,\count_reg[12]_i_1_n_6 ,\count_reg[12]_i_1_n_7 }),
        .S(count_reg[15:12]));
  FDRE \count_reg[13] 
       (.C(clk),
        .CE(count0),
        .D(\count_reg[12]_i_1_n_6 ),
        .Q(count_reg[13]),
        .R(\count[0]_i_1_n_0 ));
  FDRE \count_reg[14] 
       (.C(clk),
        .CE(count0),
        .D(\count_reg[12]_i_1_n_5 ),
        .Q(count_reg[14]),
        .R(\count[0]_i_1_n_0 ));
  FDRE \count_reg[15] 
       (.C(clk),
        .CE(count0),
        .D(\count_reg[12]_i_1_n_4 ),
        .Q(count_reg[15]),
        .R(\count[0]_i_1_n_0 ));
  FDRE \count_reg[16] 
       (.C(clk),
        .CE(count0),
        .D(\count_reg[16]_i_1_n_7 ),
        .Q(count_reg[16]),
        .R(\count[0]_i_1_n_0 ));
  CARRY4 \count_reg[16]_i_1 
       (.CI(\count_reg[12]_i_1_n_0 ),
        .CO({\count_reg[16]_i_1_n_0 ,\count_reg[16]_i_1_n_1 ,\count_reg[16]_i_1_n_2 ,\count_reg[16]_i_1_n_3 }),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\count_reg[16]_i_1_n_4 ,\count_reg[16]_i_1_n_5 ,\count_reg[16]_i_1_n_6 ,\count_reg[16]_i_1_n_7 }),
        .S(count_reg[19:16]));
  FDRE \count_reg[17] 
       (.C(clk),
        .CE(count0),
        .D(\count_reg[16]_i_1_n_6 ),
        .Q(count_reg[17]),
        .R(\count[0]_i_1_n_0 ));
  FDRE \count_reg[18] 
       (.C(clk),
        .CE(count0),
        .D(\count_reg[16]_i_1_n_5 ),
        .Q(count_reg[18]),
        .R(\count[0]_i_1_n_0 ));
  FDRE \count_reg[19] 
       (.C(clk),
        .CE(count0),
        .D(\count_reg[16]_i_1_n_4 ),
        .Q(count_reg[19]),
        .R(\count[0]_i_1_n_0 ));
  FDRE \count_reg[1] 
       (.C(clk),
        .CE(count0),
        .D(\count_reg[0]_i_3_n_6 ),
        .Q(\count_reg_n_0_[1] ),
        .R(\count[0]_i_1_n_0 ));
  FDRE \count_reg[20] 
       (.C(clk),
        .CE(count0),
        .D(\count_reg[20]_i_1_n_7 ),
        .Q(count_reg[20]),
        .R(\count[0]_i_1_n_0 ));
  CARRY4 \count_reg[20]_i_1 
       (.CI(\count_reg[16]_i_1_n_0 ),
        .CO(\NLW_count_reg[20]_i_1_CO_UNCONNECTED [3:0]),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\NLW_count_reg[20]_i_1_O_UNCONNECTED [3:1],\count_reg[20]_i_1_n_7 }),
        .S({1'b0,1'b0,1'b0,count_reg[20]}));
  FDRE \count_reg[2] 
       (.C(clk),
        .CE(count0),
        .D(\count_reg[0]_i_3_n_5 ),
        .Q(\count_reg_n_0_[2] ),
        .R(\count[0]_i_1_n_0 ));
  FDRE \count_reg[3] 
       (.C(clk),
        .CE(count0),
        .D(\count_reg[0]_i_3_n_4 ),
        .Q(\count_reg_n_0_[3] ),
        .R(\count[0]_i_1_n_0 ));
  FDRE \count_reg[4] 
       (.C(clk),
        .CE(count0),
        .D(\count_reg[4]_i_1_n_7 ),
        .Q(\count_reg_n_0_[4] ),
        .R(\count[0]_i_1_n_0 ));
  CARRY4 \count_reg[4]_i_1 
       (.CI(\count_reg[0]_i_3_n_0 ),
        .CO({\count_reg[4]_i_1_n_0 ,\count_reg[4]_i_1_n_1 ,\count_reg[4]_i_1_n_2 ,\count_reg[4]_i_1_n_3 }),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\count_reg[4]_i_1_n_4 ,\count_reg[4]_i_1_n_5 ,\count_reg[4]_i_1_n_6 ,\count_reg[4]_i_1_n_7 }),
        .S({count_reg[7],\count_reg_n_0_[6] ,\count_reg_n_0_[5] ,\count_reg_n_0_[4] }));
  FDRE \count_reg[5] 
       (.C(clk),
        .CE(count0),
        .D(\count_reg[4]_i_1_n_6 ),
        .Q(\count_reg_n_0_[5] ),
        .R(\count[0]_i_1_n_0 ));
  FDRE \count_reg[6] 
       (.C(clk),
        .CE(count0),
        .D(\count_reg[4]_i_1_n_5 ),
        .Q(\count_reg_n_0_[6] ),
        .R(\count[0]_i_1_n_0 ));
  FDRE \count_reg[7] 
       (.C(clk),
        .CE(count0),
        .D(\count_reg[4]_i_1_n_4 ),
        .Q(count_reg[7]),
        .R(\count[0]_i_1_n_0 ));
  FDRE \count_reg[8] 
       (.C(clk),
        .CE(count0),
        .D(\count_reg[8]_i_1_n_7 ),
        .Q(count_reg[8]),
        .R(\count[0]_i_1_n_0 ));
  CARRY4 \count_reg[8]_i_1 
       (.CI(\count_reg[4]_i_1_n_0 ),
        .CO({\count_reg[8]_i_1_n_0 ,\count_reg[8]_i_1_n_1 ,\count_reg[8]_i_1_n_2 ,\count_reg[8]_i_1_n_3 }),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\count_reg[8]_i_1_n_4 ,\count_reg[8]_i_1_n_5 ,\count_reg[8]_i_1_n_6 ,\count_reg[8]_i_1_n_7 }),
        .S(count_reg[11:8]));
  FDRE \count_reg[9] 
       (.C(clk),
        .CE(count0),
        .D(\count_reg[8]_i_1_n_6 ),
        .Q(count_reg[9]),
        .R(\count[0]_i_1_n_0 ));
  FDCE \flipflops_reg[0] 
       (.C(clk),
        .CE(1'b1),
        .CLR(p_0_in),
        .D(button),
        .Q(\flipflops_reg_n_0_[0] ));
  FDCE \flipflops_reg[1] 
       (.C(clk),
        .CE(1'b1),
        .CLR(p_0_in),
        .D(\flipflops_reg_n_0_[0] ),
        .Q(p_0_in_0));
  LUT4 #(
    .INIT(16'hFE08)) 
    result_i_1
       (.I0(\flipflops_reg_n_0_[0] ),
        .I1(p_0_in_0),
        .I2(result_i_3_n_0),
        .I3(result),
        .O(result_i_1_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    result_i_2
       (.I0(reset_n),
        .O(p_0_in));
  LUT5 #(
    .INIT(32'h1055FFFF)) 
    result_i_3
       (.I0(count_reg[16]),
        .I1(result_i_4_n_0),
        .I2(result_i_5_n_0),
        .I3(count_reg[15]),
        .I4(result_i_6_n_0),
        .O(result_i_3_n_0));
  LUT4 #(
    .INIT(16'hFFFE)) 
    result_i_4
       (.I0(count_reg[12]),
        .I1(count_reg[11]),
        .I2(count_reg[14]),
        .I3(count_reg[13]),
        .O(result_i_4_n_0));
  LUT4 #(
    .INIT(16'h01FF)) 
    result_i_5
       (.I0(count_reg[7]),
        .I1(count_reg[8]),
        .I2(count_reg[9]),
        .I3(count_reg[10]),
        .O(result_i_5_n_0));
  LUT4 #(
    .INIT(16'h8000)) 
    result_i_6
       (.I0(count_reg[18]),
        .I1(count_reg[17]),
        .I2(count_reg[20]),
        .I3(count_reg[19]),
        .O(result_i_6_n_0));
  FDCE result_reg
       (.C(clk),
        .CE(1'b1),
        .CLR(p_0_in),
        .D(result_i_1_n_0),
        .Q(result));
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
