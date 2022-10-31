-- Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2019.1 (lin64) Build 2552052 Fri May 24 14:47:09 MDT 2019
-- Date        : Sun Aug 15 02:32:18 2021
-- Host        : martin-Aspire-A515-51G running 64-bit Ubuntu 16.04.7 LTS
-- Command     : write_vhdl -force -mode synth_stub -rename_top design_1_ov7670_axi_stream_ca_0_0 -prefix
--               design_1_ov7670_axi_stream_ca_0_0_ design_1_ov7670_axi_stream_ca_0_0_stub.vhdl
-- Design      : design_1_ov7670_axi_stream_ca_0_0
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xc7z010clg400-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity design_1_ov7670_axi_stream_ca_0_0 is
  Port ( 
    pclk : in STD_LOGIC;
    vsync : in STD_LOGIC;
    href : in STD_LOGIC;
    d : in STD_LOGIC_VECTOR ( 7 downto 0 );
    m_axis_tvalid : out STD_LOGIC;
    m_axis_tready : in STD_LOGIC;
    m_axis_tlast : out STD_LOGIC;
    m_axis_tdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    m_axis_tuser : out STD_LOGIC;
    aclk : out STD_LOGIC
  );

end design_1_ov7670_axi_stream_ca_0_0;

architecture stub of design_1_ov7670_axi_stream_ca_0_0 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "pclk,vsync,href,d[7:0],m_axis_tvalid,m_axis_tready,m_axis_tlast,m_axis_tdata[31:0],m_axis_tuser,aclk";
attribute x_core_info : string;
attribute x_core_info of stub : architecture is "ov7670_axi_stream_capture,Vivado 2019.1";
begin
end;
