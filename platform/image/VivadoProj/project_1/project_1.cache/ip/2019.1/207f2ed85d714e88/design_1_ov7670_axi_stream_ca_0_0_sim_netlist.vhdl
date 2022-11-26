-- Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2019.1 (lin64) Build 2552052 Fri May 24 14:47:09 MDT 2019
-- Date        : Sat Nov  5 17:23:03 2022
-- Host        : kuhiu-Aspire-A515-51G running 64-bit Ubuntu 16.04.7 LTS
-- Command     : write_vhdl -force -mode funcsim -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
--               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ design_1_ov7670_axi_stream_ca_0_0_sim_netlist.vhdl
-- Design      : design_1_ov7670_axi_stream_ca_0_0
-- Purpose     : This VHDL netlist is a functional simulation representation of the design and should not be modified or
--               synthesized. This netlist cannot be used for SDF annotated simulation.
-- Device      : xc7z010clg400-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ov7670_axi_stream_capture is
  port (
    m_axis_tvalid : out STD_LOGIC;
    m_axis_tlast : out STD_LOGIC;
    m_axis_tuser : out STD_LOGIC;
    m_axis_tdata : out STD_LOGIC_VECTOR ( 15 downto 0 );
    href : in STD_LOGIC;
    pclk : in STD_LOGIC;
    vsync : in STD_LOGIC;
    d : in STD_LOGIC_VECTOR ( 7 downto 0 )
  );
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ov7670_axi_stream_capture;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ov7670_axi_stream_capture is
  signal \address[0]_i_2_n_0\ : STD_LOGIC;
  signal address_reg : STD_LOGIC_VECTOR ( 18 downto 0 );
  signal \address_reg[0]_i_1_n_0\ : STD_LOGIC;
  signal \address_reg[0]_i_1_n_1\ : STD_LOGIC;
  signal \address_reg[0]_i_1_n_2\ : STD_LOGIC;
  signal \address_reg[0]_i_1_n_3\ : STD_LOGIC;
  signal \address_reg[0]_i_1_n_4\ : STD_LOGIC;
  signal \address_reg[0]_i_1_n_5\ : STD_LOGIC;
  signal \address_reg[0]_i_1_n_6\ : STD_LOGIC;
  signal \address_reg[0]_i_1_n_7\ : STD_LOGIC;
  signal \address_reg[12]_i_1_n_0\ : STD_LOGIC;
  signal \address_reg[12]_i_1_n_1\ : STD_LOGIC;
  signal \address_reg[12]_i_1_n_2\ : STD_LOGIC;
  signal \address_reg[12]_i_1_n_3\ : STD_LOGIC;
  signal \address_reg[12]_i_1_n_4\ : STD_LOGIC;
  signal \address_reg[12]_i_1_n_5\ : STD_LOGIC;
  signal \address_reg[12]_i_1_n_6\ : STD_LOGIC;
  signal \address_reg[12]_i_1_n_7\ : STD_LOGIC;
  signal \address_reg[16]_i_1_n_2\ : STD_LOGIC;
  signal \address_reg[16]_i_1_n_3\ : STD_LOGIC;
  signal \address_reg[16]_i_1_n_5\ : STD_LOGIC;
  signal \address_reg[16]_i_1_n_6\ : STD_LOGIC;
  signal \address_reg[16]_i_1_n_7\ : STD_LOGIC;
  signal \address_reg[4]_i_1_n_0\ : STD_LOGIC;
  signal \address_reg[4]_i_1_n_1\ : STD_LOGIC;
  signal \address_reg[4]_i_1_n_2\ : STD_LOGIC;
  signal \address_reg[4]_i_1_n_3\ : STD_LOGIC;
  signal \address_reg[4]_i_1_n_4\ : STD_LOGIC;
  signal \address_reg[4]_i_1_n_5\ : STD_LOGIC;
  signal \address_reg[4]_i_1_n_6\ : STD_LOGIC;
  signal \address_reg[4]_i_1_n_7\ : STD_LOGIC;
  signal \address_reg[8]_i_1_n_0\ : STD_LOGIC;
  signal \address_reg[8]_i_1_n_1\ : STD_LOGIC;
  signal \address_reg[8]_i_1_n_2\ : STD_LOGIC;
  signal \address_reg[8]_i_1_n_3\ : STD_LOGIC;
  signal \address_reg[8]_i_1_n_4\ : STD_LOGIC;
  signal \address_reg[8]_i_1_n_5\ : STD_LOGIC;
  signal \address_reg[8]_i_1_n_6\ : STD_LOGIC;
  signal \address_reg[8]_i_1_n_7\ : STD_LOGIC;
  signal \eol1__103_carry__0_i_1_n_0\ : STD_LOGIC;
  signal \eol1__103_carry__0_i_2_n_0\ : STD_LOGIC;
  signal \eol1__103_carry__0_i_3_n_0\ : STD_LOGIC;
  signal \eol1__103_carry__0_i_4_n_0\ : STD_LOGIC;
  signal \eol1__103_carry__0_n_0\ : STD_LOGIC;
  signal \eol1__103_carry__0_n_1\ : STD_LOGIC;
  signal \eol1__103_carry__0_n_2\ : STD_LOGIC;
  signal \eol1__103_carry__0_n_3\ : STD_LOGIC;
  signal \eol1__103_carry__0_n_4\ : STD_LOGIC;
  signal \eol1__103_carry__0_n_5\ : STD_LOGIC;
  signal \eol1__103_carry__1_i_1_n_0\ : STD_LOGIC;
  signal \eol1__103_carry__1_i_2_n_0\ : STD_LOGIC;
  signal \eol1__103_carry__1_n_3\ : STD_LOGIC;
  signal \eol1__103_carry__1_n_6\ : STD_LOGIC;
  signal \eol1__103_carry__1_n_7\ : STD_LOGIC;
  signal \eol1__103_carry_i_1_n_0\ : STD_LOGIC;
  signal \eol1__103_carry_i_2_n_0\ : STD_LOGIC;
  signal \eol1__103_carry_i_3_n_0\ : STD_LOGIC;
  signal \eol1__103_carry_i_4_n_0\ : STD_LOGIC;
  signal \eol1__103_carry_n_0\ : STD_LOGIC;
  signal \eol1__103_carry_n_1\ : STD_LOGIC;
  signal \eol1__103_carry_n_2\ : STD_LOGIC;
  signal \eol1__103_carry_n_3\ : STD_LOGIC;
  signal \eol1__60_carry__0_i_1_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__0_i_2_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__0_i_3_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__0_i_4_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__0_i_5_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__0_i_6_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__0_i_7_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__0_i_8_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__0_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__0_n_1\ : STD_LOGIC;
  signal \eol1__60_carry__0_n_2\ : STD_LOGIC;
  signal \eol1__60_carry__0_n_3\ : STD_LOGIC;
  signal \eol1__60_carry__1_i_10_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__1_i_11_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__1_i_12_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__1_i_1_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__1_i_2_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__1_i_3_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__1_i_4_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__1_i_5_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__1_i_6_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__1_i_7_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__1_i_8_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__1_i_9_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__1_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__1_n_1\ : STD_LOGIC;
  signal \eol1__60_carry__1_n_2\ : STD_LOGIC;
  signal \eol1__60_carry__1_n_3\ : STD_LOGIC;
  signal \eol1__60_carry__2_i_10_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__2_i_11_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__2_i_12_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__2_i_1_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__2_i_2_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__2_i_3_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__2_i_4_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__2_i_5_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__2_i_6_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__2_i_7_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__2_i_8_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__2_i_9_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__2_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__2_n_1\ : STD_LOGIC;
  signal \eol1__60_carry__2_n_2\ : STD_LOGIC;
  signal \eol1__60_carry__2_n_3\ : STD_LOGIC;
  signal \eol1__60_carry__2_n_4\ : STD_LOGIC;
  signal \eol1__60_carry__2_n_5\ : STD_LOGIC;
  signal \eol1__60_carry__3_i_1_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__3_i_2_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__3_i_3_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__3_i_4_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__3_i_5_n_0\ : STD_LOGIC;
  signal \eol1__60_carry__3_n_3\ : STD_LOGIC;
  signal \eol1__60_carry__3_n_6\ : STD_LOGIC;
  signal \eol1__60_carry__3_n_7\ : STD_LOGIC;
  signal \eol1__60_carry_i_1_n_0\ : STD_LOGIC;
  signal \eol1__60_carry_i_2_n_0\ : STD_LOGIC;
  signal \eol1__60_carry_i_3_n_0\ : STD_LOGIC;
  signal \eol1__60_carry_n_0\ : STD_LOGIC;
  signal \eol1__60_carry_n_1\ : STD_LOGIC;
  signal \eol1__60_carry_n_2\ : STD_LOGIC;
  signal \eol1__60_carry_n_3\ : STD_LOGIC;
  signal \eol1__97_carry_i_1_n_0\ : STD_LOGIC;
  signal \eol1__97_carry_i_2_n_0\ : STD_LOGIC;
  signal \eol1__97_carry_n_2\ : STD_LOGIC;
  signal \eol1__97_carry_n_3\ : STD_LOGIC;
  signal \eol1__97_carry_n_5\ : STD_LOGIC;
  signal \eol1__97_carry_n_6\ : STD_LOGIC;
  signal \eol1__97_carry_n_7\ : STD_LOGIC;
  signal \eol1_carry__0_i_1_n_0\ : STD_LOGIC;
  signal \eol1_carry__0_i_2_n_0\ : STD_LOGIC;
  signal \eol1_carry__0_i_3_n_0\ : STD_LOGIC;
  signal \eol1_carry__0_i_4_n_0\ : STD_LOGIC;
  signal \eol1_carry__0_i_5_n_0\ : STD_LOGIC;
  signal \eol1_carry__0_i_6_n_0\ : STD_LOGIC;
  signal \eol1_carry__0_i_7_n_0\ : STD_LOGIC;
  signal \eol1_carry__0_n_0\ : STD_LOGIC;
  signal \eol1_carry__0_n_1\ : STD_LOGIC;
  signal \eol1_carry__0_n_2\ : STD_LOGIC;
  signal \eol1_carry__0_n_3\ : STD_LOGIC;
  signal \eol1_carry__0_n_4\ : STD_LOGIC;
  signal \eol1_carry__0_n_5\ : STD_LOGIC;
  signal \eol1_carry__0_n_6\ : STD_LOGIC;
  signal \eol1_carry__0_n_7\ : STD_LOGIC;
  signal \eol1_carry__1_i_1_n_0\ : STD_LOGIC;
  signal \eol1_carry__1_i_2_n_0\ : STD_LOGIC;
  signal \eol1_carry__1_i_3_n_0\ : STD_LOGIC;
  signal \eol1_carry__1_i_4_n_0\ : STD_LOGIC;
  signal \eol1_carry__1_i_5_n_0\ : STD_LOGIC;
  signal \eol1_carry__1_i_6_n_0\ : STD_LOGIC;
  signal \eol1_carry__1_i_7_n_0\ : STD_LOGIC;
  signal \eol1_carry__1_i_8_n_0\ : STD_LOGIC;
  signal \eol1_carry__1_n_0\ : STD_LOGIC;
  signal \eol1_carry__1_n_1\ : STD_LOGIC;
  signal \eol1_carry__1_n_2\ : STD_LOGIC;
  signal \eol1_carry__1_n_3\ : STD_LOGIC;
  signal \eol1_carry__1_n_4\ : STD_LOGIC;
  signal \eol1_carry__1_n_5\ : STD_LOGIC;
  signal \eol1_carry__1_n_6\ : STD_LOGIC;
  signal \eol1_carry__1_n_7\ : STD_LOGIC;
  signal \eol1_carry__2_i_1_n_0\ : STD_LOGIC;
  signal \eol1_carry__2_i_2_n_0\ : STD_LOGIC;
  signal \eol1_carry__2_i_3_n_0\ : STD_LOGIC;
  signal \eol1_carry__2_i_4_n_0\ : STD_LOGIC;
  signal \eol1_carry__2_i_5_n_0\ : STD_LOGIC;
  signal \eol1_carry__2_i_6_n_0\ : STD_LOGIC;
  signal \eol1_carry__2_i_7_n_0\ : STD_LOGIC;
  signal \eol1_carry__2_i_8_n_0\ : STD_LOGIC;
  signal \eol1_carry__2_n_0\ : STD_LOGIC;
  signal \eol1_carry__2_n_1\ : STD_LOGIC;
  signal \eol1_carry__2_n_2\ : STD_LOGIC;
  signal \eol1_carry__2_n_3\ : STD_LOGIC;
  signal \eol1_carry__2_n_4\ : STD_LOGIC;
  signal \eol1_carry__2_n_5\ : STD_LOGIC;
  signal \eol1_carry__2_n_6\ : STD_LOGIC;
  signal \eol1_carry__2_n_7\ : STD_LOGIC;
  signal \eol1_carry__3_i_1_n_0\ : STD_LOGIC;
  signal \eol1_carry__3_i_2_n_0\ : STD_LOGIC;
  signal \eol1_carry__3_i_3_n_0\ : STD_LOGIC;
  signal \eol1_carry__3_i_4_n_0\ : STD_LOGIC;
  signal \eol1_carry__3_i_5_n_0\ : STD_LOGIC;
  signal \eol1_carry__3_i_6_n_0\ : STD_LOGIC;
  signal \eol1_carry__3_i_7_n_0\ : STD_LOGIC;
  signal \eol1_carry__3_i_8_n_0\ : STD_LOGIC;
  signal \eol1_carry__3_n_0\ : STD_LOGIC;
  signal \eol1_carry__3_n_1\ : STD_LOGIC;
  signal \eol1_carry__3_n_2\ : STD_LOGIC;
  signal \eol1_carry__3_n_3\ : STD_LOGIC;
  signal \eol1_carry__3_n_4\ : STD_LOGIC;
  signal \eol1_carry__3_n_5\ : STD_LOGIC;
  signal \eol1_carry__3_n_6\ : STD_LOGIC;
  signal \eol1_carry__3_n_7\ : STD_LOGIC;
  signal \eol1_carry__4_i_1_n_0\ : STD_LOGIC;
  signal \eol1_carry__4_i_2_n_0\ : STD_LOGIC;
  signal \eol1_carry__4_i_3_n_0\ : STD_LOGIC;
  signal \eol1_carry__4_n_3\ : STD_LOGIC;
  signal \eol1_carry__4_n_6\ : STD_LOGIC;
  signal \eol1_carry__4_n_7\ : STD_LOGIC;
  signal eol1_carry_i_1_n_0 : STD_LOGIC;
  signal eol1_carry_i_2_n_0 : STD_LOGIC;
  signal eol1_carry_i_3_n_0 : STD_LOGIC;
  signal eol1_carry_n_0 : STD_LOGIC;
  signal eol1_carry_n_1 : STD_LOGIC;
  signal eol1_carry_n_2 : STD_LOGIC;
  signal eol1_carry_n_3 : STD_LOGIC;
  signal eol_i_1_n_0 : STD_LOGIC;
  signal eol_i_2_n_0 : STD_LOGIC;
  signal eol_i_3_n_0 : STD_LOGIC;
  signal href_last : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \href_last[0]_i_1_n_0\ : STD_LOGIC;
  signal latched_href : STD_LOGIC;
  signal latched_vsync : STD_LOGIC;
  signal \^m_axis_tdata\ : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal \^m_axis_tvalid\ : STD_LOGIC;
  signal p_0_in : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal sel0 : STD_LOGIC_VECTOR ( 5 downto 0 );
  signal sof_i_1_n_0 : STD_LOGIC;
  signal sof_i_2_n_0 : STD_LOGIC;
  signal sof_i_3_n_0 : STD_LOGIC;
  signal sof_i_4_n_0 : STD_LOGIC;
  signal sof_i_5_n_0 : STD_LOGIC;
  signal sof_i_6_n_0 : STD_LOGIC;
  signal we_reg_i_1_n_0 : STD_LOGIC;
  signal \NLW_address_reg[16]_i_1_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 2 );
  signal \NLW_address_reg[16]_i_1_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 to 3 );
  signal \NLW_eol1__103_carry__1_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 1 );
  signal \NLW_eol1__103_carry__1_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 2 );
  signal \NLW_eol1__60_carry_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_eol1__60_carry__0_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_eol1__60_carry__1_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_eol1__60_carry__2_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal \NLW_eol1__60_carry__3_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 1 );
  signal \NLW_eol1__60_carry__3_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 2 );
  signal \NLW_eol1__97_carry_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 2 );
  signal \NLW_eol1__97_carry_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 to 3 );
  signal NLW_eol1_carry_O_UNCONNECTED : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_eol1_carry__4_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 1 );
  signal \NLW_eol1_carry__4_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 2 );
  attribute HLUTNM : string;
  attribute HLUTNM of \eol1__60_carry__0_i_3\ : label is "lutpair13";
  attribute HLUTNM of \eol1__60_carry__0_i_7\ : label is "lutpair13";
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \eol1__60_carry__0_i_8\ : label is "soft_lutpair2";
  attribute SOFT_HLUTNM of \eol1__60_carry__1_i_10\ : label is "soft_lutpair3";
  attribute SOFT_HLUTNM of \eol1__60_carry__1_i_11\ : label is "soft_lutpair2";
  attribute SOFT_HLUTNM of \eol1__60_carry__1_i_12\ : label is "soft_lutpair3";
  attribute SOFT_HLUTNM of \eol1__60_carry__2_i_10\ : label is "soft_lutpair4";
  attribute SOFT_HLUTNM of \eol1__60_carry__2_i_11\ : label is "soft_lutpair0";
  attribute SOFT_HLUTNM of \eol1__60_carry__2_i_12\ : label is "soft_lutpair4";
  attribute SOFT_HLUTNM of \eol1__60_carry__2_i_9\ : label is "soft_lutpair5";
  attribute SOFT_HLUTNM of \eol1__60_carry__3_i_4\ : label is "soft_lutpair1";
  attribute SOFT_HLUTNM of \eol1__60_carry__3_i_5\ : label is "soft_lutpair5";
  attribute HLUTNM of \eol1_carry__0_i_1\ : label is "lutpair1";
  attribute HLUTNM of \eol1_carry__0_i_2\ : label is "lutpair0";
  attribute HLUTNM of \eol1_carry__0_i_4\ : label is "lutpair2";
  attribute HLUTNM of \eol1_carry__0_i_5\ : label is "lutpair1";
  attribute HLUTNM of \eol1_carry__0_i_6\ : label is "lutpair0";
  attribute HLUTNM of \eol1_carry__1_i_1\ : label is "lutpair5";
  attribute HLUTNM of \eol1_carry__1_i_2\ : label is "lutpair4";
  attribute HLUTNM of \eol1_carry__1_i_3\ : label is "lutpair3";
  attribute HLUTNM of \eol1_carry__1_i_4\ : label is "lutpair2";
  attribute HLUTNM of \eol1_carry__1_i_5\ : label is "lutpair6";
  attribute HLUTNM of \eol1_carry__1_i_6\ : label is "lutpair5";
  attribute HLUTNM of \eol1_carry__1_i_7\ : label is "lutpair4";
  attribute HLUTNM of \eol1_carry__1_i_8\ : label is "lutpair3";
  attribute HLUTNM of \eol1_carry__2_i_1\ : label is "lutpair9";
  attribute HLUTNM of \eol1_carry__2_i_2\ : label is "lutpair8";
  attribute HLUTNM of \eol1_carry__2_i_3\ : label is "lutpair7";
  attribute HLUTNM of \eol1_carry__2_i_4\ : label is "lutpair6";
  attribute HLUTNM of \eol1_carry__2_i_5\ : label is "lutpair10";
  attribute HLUTNM of \eol1_carry__2_i_6\ : label is "lutpair9";
  attribute HLUTNM of \eol1_carry__2_i_7\ : label is "lutpair8";
  attribute HLUTNM of \eol1_carry__2_i_8\ : label is "lutpair7";
  attribute HLUTNM of \eol1_carry__3_i_2\ : label is "lutpair12";
  attribute HLUTNM of \eol1_carry__3_i_3\ : label is "lutpair11";
  attribute HLUTNM of \eol1_carry__3_i_4\ : label is "lutpair10";
  attribute HLUTNM of \eol1_carry__3_i_7\ : label is "lutpair12";
  attribute HLUTNM of \eol1_carry__3_i_8\ : label is "lutpair11";
  attribute SOFT_HLUTNM of \href_last[0]_i_1\ : label is "soft_lutpair6";
  attribute SOFT_HLUTNM of sof_i_4 : label is "soft_lutpair1";
  attribute SOFT_HLUTNM of sof_i_6 : label is "soft_lutpair0";
  attribute SOFT_HLUTNM of we_reg_i_1 : label is "soft_lutpair6";
begin
  m_axis_tdata(15 downto 0) <= \^m_axis_tdata\(15 downto 0);
  m_axis_tvalid <= \^m_axis_tvalid\;
\address[0]_i_2\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => address_reg(0),
      O => \address[0]_i_2_n_0\
    );
\address_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => \^m_axis_tvalid\,
      D => \address_reg[0]_i_1_n_7\,
      Q => address_reg(0),
      R => latched_vsync
    );
\address_reg[0]_i_1\: unisim.vcomponents.CARRY4
     port map (
      CI => '0',
      CO(3) => \address_reg[0]_i_1_n_0\,
      CO(2) => \address_reg[0]_i_1_n_1\,
      CO(1) => \address_reg[0]_i_1_n_2\,
      CO(0) => \address_reg[0]_i_1_n_3\,
      CYINIT => '0',
      DI(3 downto 0) => B"0001",
      O(3) => \address_reg[0]_i_1_n_4\,
      O(2) => \address_reg[0]_i_1_n_5\,
      O(1) => \address_reg[0]_i_1_n_6\,
      O(0) => \address_reg[0]_i_1_n_7\,
      S(3 downto 1) => address_reg(3 downto 1),
      S(0) => \address[0]_i_2_n_0\
    );
\address_reg[10]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => \^m_axis_tvalid\,
      D => \address_reg[8]_i_1_n_5\,
      Q => address_reg(10),
      R => latched_vsync
    );
\address_reg[11]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => \^m_axis_tvalid\,
      D => \address_reg[8]_i_1_n_4\,
      Q => address_reg(11),
      R => latched_vsync
    );
\address_reg[12]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => \^m_axis_tvalid\,
      D => \address_reg[12]_i_1_n_7\,
      Q => address_reg(12),
      R => latched_vsync
    );
\address_reg[12]_i_1\: unisim.vcomponents.CARRY4
     port map (
      CI => \address_reg[8]_i_1_n_0\,
      CO(3) => \address_reg[12]_i_1_n_0\,
      CO(2) => \address_reg[12]_i_1_n_1\,
      CO(1) => \address_reg[12]_i_1_n_2\,
      CO(0) => \address_reg[12]_i_1_n_3\,
      CYINIT => '0',
      DI(3 downto 0) => B"0000",
      O(3) => \address_reg[12]_i_1_n_4\,
      O(2) => \address_reg[12]_i_1_n_5\,
      O(1) => \address_reg[12]_i_1_n_6\,
      O(0) => \address_reg[12]_i_1_n_7\,
      S(3 downto 0) => address_reg(15 downto 12)
    );
\address_reg[13]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => \^m_axis_tvalid\,
      D => \address_reg[12]_i_1_n_6\,
      Q => address_reg(13),
      R => latched_vsync
    );
\address_reg[14]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => \^m_axis_tvalid\,
      D => \address_reg[12]_i_1_n_5\,
      Q => address_reg(14),
      R => latched_vsync
    );
\address_reg[15]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => \^m_axis_tvalid\,
      D => \address_reg[12]_i_1_n_4\,
      Q => address_reg(15),
      R => latched_vsync
    );
\address_reg[16]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => \^m_axis_tvalid\,
      D => \address_reg[16]_i_1_n_7\,
      Q => address_reg(16),
      R => latched_vsync
    );
\address_reg[16]_i_1\: unisim.vcomponents.CARRY4
     port map (
      CI => \address_reg[12]_i_1_n_0\,
      CO(3 downto 2) => \NLW_address_reg[16]_i_1_CO_UNCONNECTED\(3 downto 2),
      CO(1) => \address_reg[16]_i_1_n_2\,
      CO(0) => \address_reg[16]_i_1_n_3\,
      CYINIT => '0',
      DI(3 downto 0) => B"0000",
      O(3) => \NLW_address_reg[16]_i_1_O_UNCONNECTED\(3),
      O(2) => \address_reg[16]_i_1_n_5\,
      O(1) => \address_reg[16]_i_1_n_6\,
      O(0) => \address_reg[16]_i_1_n_7\,
      S(3) => '0',
      S(2 downto 0) => address_reg(18 downto 16)
    );
\address_reg[17]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => \^m_axis_tvalid\,
      D => \address_reg[16]_i_1_n_6\,
      Q => address_reg(17),
      R => latched_vsync
    );
\address_reg[18]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => \^m_axis_tvalid\,
      D => \address_reg[16]_i_1_n_5\,
      Q => address_reg(18),
      R => latched_vsync
    );
\address_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => \^m_axis_tvalid\,
      D => \address_reg[0]_i_1_n_6\,
      Q => address_reg(1),
      R => latched_vsync
    );
\address_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => \^m_axis_tvalid\,
      D => \address_reg[0]_i_1_n_5\,
      Q => address_reg(2),
      R => latched_vsync
    );
\address_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => \^m_axis_tvalid\,
      D => \address_reg[0]_i_1_n_4\,
      Q => address_reg(3),
      R => latched_vsync
    );
\address_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => \^m_axis_tvalid\,
      D => \address_reg[4]_i_1_n_7\,
      Q => address_reg(4),
      R => latched_vsync
    );
\address_reg[4]_i_1\: unisim.vcomponents.CARRY4
     port map (
      CI => \address_reg[0]_i_1_n_0\,
      CO(3) => \address_reg[4]_i_1_n_0\,
      CO(2) => \address_reg[4]_i_1_n_1\,
      CO(1) => \address_reg[4]_i_1_n_2\,
      CO(0) => \address_reg[4]_i_1_n_3\,
      CYINIT => '0',
      DI(3 downto 0) => B"0000",
      O(3) => \address_reg[4]_i_1_n_4\,
      O(2) => \address_reg[4]_i_1_n_5\,
      O(1) => \address_reg[4]_i_1_n_6\,
      O(0) => \address_reg[4]_i_1_n_7\,
      S(3 downto 0) => address_reg(7 downto 4)
    );
\address_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => \^m_axis_tvalid\,
      D => \address_reg[4]_i_1_n_6\,
      Q => address_reg(5),
      R => latched_vsync
    );
\address_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => \^m_axis_tvalid\,
      D => \address_reg[4]_i_1_n_5\,
      Q => address_reg(6),
      R => latched_vsync
    );
\address_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => \^m_axis_tvalid\,
      D => \address_reg[4]_i_1_n_4\,
      Q => address_reg(7),
      R => latched_vsync
    );
\address_reg[8]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => \^m_axis_tvalid\,
      D => \address_reg[8]_i_1_n_7\,
      Q => address_reg(8),
      R => latched_vsync
    );
\address_reg[8]_i_1\: unisim.vcomponents.CARRY4
     port map (
      CI => \address_reg[4]_i_1_n_0\,
      CO(3) => \address_reg[8]_i_1_n_0\,
      CO(2) => \address_reg[8]_i_1_n_1\,
      CO(1) => \address_reg[8]_i_1_n_2\,
      CO(0) => \address_reg[8]_i_1_n_3\,
      CYINIT => '0',
      DI(3 downto 0) => B"0000",
      O(3) => \address_reg[8]_i_1_n_4\,
      O(2) => \address_reg[8]_i_1_n_5\,
      O(1) => \address_reg[8]_i_1_n_6\,
      O(0) => \address_reg[8]_i_1_n_7\,
      S(3 downto 0) => address_reg(11 downto 8)
    );
\address_reg[9]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => \^m_axis_tvalid\,
      D => \address_reg[8]_i_1_n_6\,
      Q => address_reg(9),
      R => latched_vsync
    );
\d_latch_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => latched_href,
      D => p_0_in(0),
      Q => \^m_axis_tdata\(11),
      R => '0'
    );
\d_latch_reg[10]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => latched_href,
      D => \^m_axis_tdata\(13),
      Q => \^m_axis_tdata\(10),
      R => '0'
    );
\d_latch_reg[11]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => latched_href,
      D => \^m_axis_tdata\(14),
      Q => \^m_axis_tdata\(0),
      R => '0'
    );
\d_latch_reg[12]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => latched_href,
      D => \^m_axis_tdata\(15),
      Q => \^m_axis_tdata\(1),
      R => '0'
    );
\d_latch_reg[13]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => latched_href,
      D => \^m_axis_tdata\(5),
      Q => \^m_axis_tdata\(2),
      R => '0'
    );
\d_latch_reg[14]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => latched_href,
      D => \^m_axis_tdata\(6),
      Q => \^m_axis_tdata\(3),
      R => '0'
    );
\d_latch_reg[15]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => latched_href,
      D => \^m_axis_tdata\(7),
      Q => \^m_axis_tdata\(4),
      R => '0'
    );
\d_latch_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => latched_href,
      D => p_0_in(1),
      Q => \^m_axis_tdata\(12),
      R => '0'
    );
\d_latch_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => latched_href,
      D => p_0_in(2),
      Q => \^m_axis_tdata\(13),
      R => '0'
    );
\d_latch_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => latched_href,
      D => p_0_in(3),
      Q => \^m_axis_tdata\(14),
      R => '0'
    );
\d_latch_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => latched_href,
      D => p_0_in(4),
      Q => \^m_axis_tdata\(15),
      R => '0'
    );
\d_latch_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => latched_href,
      D => p_0_in(5),
      Q => \^m_axis_tdata\(5),
      R => '0'
    );
\d_latch_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => latched_href,
      D => p_0_in(6),
      Q => \^m_axis_tdata\(6),
      R => '0'
    );
\d_latch_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => latched_href,
      D => p_0_in(7),
      Q => \^m_axis_tdata\(7),
      R => '0'
    );
\d_latch_reg[8]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => latched_href,
      D => \^m_axis_tdata\(11),
      Q => \^m_axis_tdata\(8),
      R => '0'
    );
\d_latch_reg[9]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => latched_href,
      D => \^m_axis_tdata\(12),
      Q => \^m_axis_tdata\(9),
      R => '0'
    );
\eol1__103_carry\: unisim.vcomponents.CARRY4
     port map (
      CI => '0',
      CO(3) => \eol1__103_carry_n_0\,
      CO(2) => \eol1__103_carry_n_1\,
      CO(1) => \eol1__103_carry_n_2\,
      CO(0) => \eol1__103_carry_n_3\,
      CYINIT => '1',
      DI(3 downto 0) => address_reg(3 downto 0),
      O(3 downto 0) => sel0(3 downto 0),
      S(3) => \eol1__103_carry_i_1_n_0\,
      S(2) => \eol1__103_carry_i_2_n_0\,
      S(1) => \eol1__103_carry_i_3_n_0\,
      S(0) => \eol1__103_carry_i_4_n_0\
    );
\eol1__103_carry__0\: unisim.vcomponents.CARRY4
     port map (
      CI => \eol1__103_carry_n_0\,
      CO(3) => \eol1__103_carry__0_n_0\,
      CO(2) => \eol1__103_carry__0_n_1\,
      CO(1) => \eol1__103_carry__0_n_2\,
      CO(0) => \eol1__103_carry__0_n_3\,
      CYINIT => '0',
      DI(3 downto 0) => address_reg(7 downto 4),
      O(3) => \eol1__103_carry__0_n_4\,
      O(2) => \eol1__103_carry__0_n_5\,
      O(1 downto 0) => sel0(5 downto 4),
      S(3) => \eol1__103_carry__0_i_1_n_0\,
      S(2) => \eol1__103_carry__0_i_2_n_0\,
      S(1) => \eol1__103_carry__0_i_3_n_0\,
      S(0) => \eol1__103_carry__0_i_4_n_0\
    );
\eol1__103_carry__0_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => address_reg(7),
      I1 => \eol1__97_carry_n_7\,
      O => \eol1__103_carry__0_i_1_n_0\
    );
\eol1__103_carry__0_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => address_reg(6),
      I1 => \eol1__60_carry__2_n_5\,
      O => \eol1__103_carry__0_i_2_n_0\
    );
\eol1__103_carry__0_i_3\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => address_reg(5),
      O => \eol1__103_carry__0_i_3_n_0\
    );
\eol1__103_carry__0_i_4\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => address_reg(4),
      O => \eol1__103_carry__0_i_4_n_0\
    );
\eol1__103_carry__1\: unisim.vcomponents.CARRY4
     port map (
      CI => \eol1__103_carry__0_n_0\,
      CO(3 downto 1) => \NLW_eol1__103_carry__1_CO_UNCONNECTED\(3 downto 1),
      CO(0) => \eol1__103_carry__1_n_3\,
      CYINIT => '0',
      DI(3 downto 1) => B"000",
      DI(0) => address_reg(8),
      O(3 downto 2) => \NLW_eol1__103_carry__1_O_UNCONNECTED\(3 downto 2),
      O(1) => \eol1__103_carry__1_n_6\,
      O(0) => \eol1__103_carry__1_n_7\,
      S(3 downto 2) => B"00",
      S(1) => \eol1__103_carry__1_i_1_n_0\,
      S(0) => \eol1__103_carry__1_i_2_n_0\
    );
\eol1__103_carry__1_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => address_reg(9),
      I1 => \eol1__97_carry_n_5\,
      O => \eol1__103_carry__1_i_1_n_0\
    );
\eol1__103_carry__1_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => address_reg(8),
      I1 => \eol1__97_carry_n_6\,
      O => \eol1__103_carry__1_i_2_n_0\
    );
\eol1__103_carry_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => address_reg(3),
      O => \eol1__103_carry_i_1_n_0\
    );
\eol1__103_carry_i_2\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => address_reg(2),
      O => \eol1__103_carry_i_2_n_0\
    );
\eol1__103_carry_i_3\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => address_reg(1),
      O => \eol1__103_carry_i_3_n_0\
    );
\eol1__103_carry_i_4\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => address_reg(0),
      O => \eol1__103_carry_i_4_n_0\
    );
\eol1__60_carry\: unisim.vcomponents.CARRY4
     port map (
      CI => '0',
      CO(3) => \eol1__60_carry_n_0\,
      CO(2) => \eol1__60_carry_n_1\,
      CO(1) => \eol1__60_carry_n_2\,
      CO(0) => \eol1__60_carry_n_3\,
      CYINIT => '0',
      DI(3 downto 1) => address_reg(2 downto 0),
      DI(0) => '0',
      O(3 downto 0) => \NLW_eol1__60_carry_O_UNCONNECTED\(3 downto 0),
      S(3) => \eol1__60_carry_i_1_n_0\,
      S(2) => \eol1__60_carry_i_2_n_0\,
      S(1) => \eol1__60_carry_i_3_n_0\,
      S(0) => \eol1_carry__0_n_7\
    );
\eol1__60_carry__0\: unisim.vcomponents.CARRY4
     port map (
      CI => \eol1__60_carry_n_0\,
      CO(3) => \eol1__60_carry__0_n_0\,
      CO(2) => \eol1__60_carry__0_n_1\,
      CO(1) => \eol1__60_carry__0_n_2\,
      CO(0) => \eol1__60_carry__0_n_3\,
      CYINIT => '0',
      DI(3) => \eol1__60_carry__0_i_1_n_0\,
      DI(2) => \eol1__60_carry__0_i_2_n_0\,
      DI(1) => \eol1__60_carry__0_i_3_n_0\,
      DI(0) => address_reg(3),
      O(3 downto 0) => \NLW_eol1__60_carry__0_O_UNCONNECTED\(3 downto 0),
      S(3) => \eol1__60_carry__0_i_4_n_0\,
      S(2) => \eol1__60_carry__0_i_5_n_0\,
      S(1) => \eol1__60_carry__0_i_6_n_0\,
      S(0) => \eol1__60_carry__0_i_7_n_0\
    );
\eol1__60_carry__0_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"718E8E71"
    )
        port map (
      I0 => address_reg(0),
      I1 => \eol1_carry__1_n_5\,
      I2 => address_reg(2),
      I3 => \eol1__60_carry__0_i_8_n_0\,
      I4 => address_reg(6),
      O => \eol1__60_carry__0_i_1_n_0\
    );
\eol1__60_carry__0_i_2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9669"
    )
        port map (
      I0 => address_reg(2),
      I1 => \eol1_carry__1_n_5\,
      I2 => address_reg(0),
      I3 => address_reg(5),
      O => \eol1__60_carry__0_i_2_n_0\
    );
\eol1__60_carry__0_i_3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"B"
    )
        port map (
      I0 => \eol1_carry__1_n_7\,
      I1 => address_reg(0),
      O => \eol1__60_carry__0_i_3_n_0\
    );
\eol1__60_carry__0_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"6669966669996669"
    )
        port map (
      I0 => address_reg(6),
      I1 => \eol1__60_carry__0_i_8_n_0\,
      I2 => address_reg(0),
      I3 => \eol1_carry__1_n_5\,
      I4 => address_reg(2),
      I5 => address_reg(5),
      O => \eol1__60_carry__0_i_4_n_0\
    );
\eol1__60_carry__0_i_5\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"6A56"
    )
        port map (
      I0 => \eol1__60_carry__0_i_2_n_0\,
      I1 => address_reg(4),
      I2 => \eol1_carry__1_n_6\,
      I3 => address_reg(1),
      O => \eol1__60_carry__0_i_5_n_0\
    );
\eol1__60_carry__0_i_6\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9669"
    )
        port map (
      I0 => \eol1__60_carry__0_i_3_n_0\,
      I1 => address_reg(1),
      I2 => \eol1_carry__1_n_6\,
      I3 => address_reg(4),
      O => \eol1__60_carry__0_i_6_n_0\
    );
\eol1__60_carry__0_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"96"
    )
        port map (
      I0 => \eol1_carry__1_n_7\,
      I1 => address_reg(0),
      I2 => address_reg(3),
      O => \eol1__60_carry__0_i_7_n_0\
    );
\eol1__60_carry__0_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"96"
    )
        port map (
      I0 => address_reg(1),
      I1 => \eol1_carry__1_n_4\,
      I2 => address_reg(3),
      O => \eol1__60_carry__0_i_8_n_0\
    );
\eol1__60_carry__1\: unisim.vcomponents.CARRY4
     port map (
      CI => \eol1__60_carry__0_n_0\,
      CO(3) => \eol1__60_carry__1_n_0\,
      CO(2) => \eol1__60_carry__1_n_1\,
      CO(1) => \eol1__60_carry__1_n_2\,
      CO(0) => \eol1__60_carry__1_n_3\,
      CYINIT => '0',
      DI(3) => \eol1__60_carry__1_i_1_n_0\,
      DI(2) => \eol1__60_carry__1_i_2_n_0\,
      DI(1) => \eol1__60_carry__1_i_3_n_0\,
      DI(0) => \eol1__60_carry__1_i_4_n_0\,
      O(3 downto 0) => \NLW_eol1__60_carry__1_O_UNCONNECTED\(3 downto 0),
      S(3) => \eol1__60_carry__1_i_5_n_0\,
      S(2) => \eol1__60_carry__1_i_6_n_0\,
      S(1) => \eol1__60_carry__1_i_7_n_0\,
      S(0) => \eol1__60_carry__1_i_8_n_0\
    );
\eol1__60_carry__1_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"69FF0069"
    )
        port map (
      I0 => address_reg(4),
      I1 => \eol1_carry__2_n_5\,
      I2 => address_reg(6),
      I3 => \eol1__60_carry__1_i_9_n_0\,
      I4 => address_reg(9),
      O => \eol1__60_carry__1_i_1_n_0\
    );
\eol1__60_carry__1_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"2B"
    )
        port map (
      I0 => address_reg(4),
      I1 => \eol1_carry__2_n_7\,
      I2 => address_reg(2),
      O => \eol1__60_carry__1_i_10_n_0\
    );
\eol1__60_carry__1_i_11\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"2B"
    )
        port map (
      I0 => address_reg(3),
      I1 => \eol1_carry__1_n_4\,
      I2 => address_reg(1),
      O => \eol1__60_carry__1_i_11_n_0\
    );
\eol1__60_carry__1_i_12\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"2B"
    )
        port map (
      I0 => address_reg(6),
      I1 => \eol1_carry__2_n_5\,
      I2 => address_reg(4),
      O => \eol1__60_carry__1_i_12_n_0\
    );
\eol1__60_carry__1_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"6900FF69"
    )
        port map (
      I0 => address_reg(3),
      I1 => \eol1_carry__2_n_6\,
      I2 => address_reg(5),
      I3 => address_reg(8),
      I4 => \eol1__60_carry__1_i_10_n_0\,
      O => \eol1__60_carry__1_i_2_n_0\
    );
\eol1__60_carry__1_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"6900FF69"
    )
        port map (
      I0 => address_reg(2),
      I1 => \eol1_carry__2_n_7\,
      I2 => address_reg(4),
      I3 => address_reg(7),
      I4 => \eol1__60_carry__1_i_11_n_0\,
      O => \eol1__60_carry__1_i_3_n_0\
    );
\eol1__60_carry__1_i_4\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"DD4D4D44"
    )
        port map (
      I0 => \eol1__60_carry__0_i_8_n_0\,
      I1 => address_reg(6),
      I2 => address_reg(2),
      I3 => \eol1_carry__1_n_5\,
      I4 => address_reg(0),
      O => \eol1__60_carry__1_i_4_n_0\
    );
\eol1__60_carry__1_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"6996966996696996"
    )
        port map (
      I0 => \eol1__60_carry__1_i_1_n_0\,
      I1 => address_reg(10),
      I2 => address_reg(7),
      I3 => \eol1_carry__2_n_4\,
      I4 => address_reg(5),
      I5 => \eol1__60_carry__1_i_12_n_0\,
      O => \eol1__60_carry__1_i_5_n_0\
    );
\eol1__60_carry__1_i_6\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"6996966996696996"
    )
        port map (
      I0 => \eol1__60_carry__1_i_2_n_0\,
      I1 => address_reg(9),
      I2 => address_reg(6),
      I3 => \eol1_carry__2_n_5\,
      I4 => address_reg(4),
      I5 => \eol1__60_carry__1_i_9_n_0\,
      O => \eol1__60_carry__1_i_6_n_0\
    );
\eol1__60_carry__1_i_7\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"6996966996696996"
    )
        port map (
      I0 => \eol1__60_carry__1_i_3_n_0\,
      I1 => address_reg(8),
      I2 => address_reg(5),
      I3 => \eol1_carry__2_n_6\,
      I4 => address_reg(3),
      I5 => \eol1__60_carry__1_i_10_n_0\,
      O => \eol1__60_carry__1_i_7_n_0\
    );
\eol1__60_carry__1_i_8\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"6996966996696996"
    )
        port map (
      I0 => \eol1__60_carry__1_i_4_n_0\,
      I1 => address_reg(7),
      I2 => address_reg(4),
      I3 => \eol1_carry__2_n_7\,
      I4 => address_reg(2),
      I5 => \eol1__60_carry__1_i_11_n_0\,
      O => \eol1__60_carry__1_i_8_n_0\
    );
\eol1__60_carry__1_i_9\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"2B"
    )
        port map (
      I0 => address_reg(5),
      I1 => \eol1_carry__2_n_6\,
      I2 => address_reg(3),
      O => \eol1__60_carry__1_i_9_n_0\
    );
\eol1__60_carry__2\: unisim.vcomponents.CARRY4
     port map (
      CI => \eol1__60_carry__1_n_0\,
      CO(3) => \eol1__60_carry__2_n_0\,
      CO(2) => \eol1__60_carry__2_n_1\,
      CO(1) => \eol1__60_carry__2_n_2\,
      CO(0) => \eol1__60_carry__2_n_3\,
      CYINIT => '0',
      DI(3) => \eol1__60_carry__2_i_1_n_0\,
      DI(2) => \eol1__60_carry__2_i_2_n_0\,
      DI(1) => \eol1__60_carry__2_i_3_n_0\,
      DI(0) => \eol1__60_carry__2_i_4_n_0\,
      O(3) => \eol1__60_carry__2_n_4\,
      O(2) => \eol1__60_carry__2_n_5\,
      O(1 downto 0) => \NLW_eol1__60_carry__2_O_UNCONNECTED\(1 downto 0),
      S(3) => \eol1__60_carry__2_i_5_n_0\,
      S(2) => \eol1__60_carry__2_i_6_n_0\,
      S(1) => \eol1__60_carry__2_i_7_n_0\,
      S(0) => \eol1__60_carry__2_i_8_n_0\
    );
\eol1__60_carry__2_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"4DD4D44D"
    )
        port map (
      I0 => \eol1__60_carry__2_i_9_n_0\,
      I1 => address_reg(13),
      I2 => address_reg(8),
      I3 => \eol1_carry__3_n_5\,
      I4 => address_reg(10),
      O => \eol1__60_carry__2_i_1_n_0\
    );
\eol1__60_carry__2_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"2B"
    )
        port map (
      I0 => address_reg(8),
      I1 => \eol1_carry__3_n_7\,
      I2 => address_reg(6),
      O => \eol1__60_carry__2_i_10_n_0\
    );
\eol1__60_carry__2_i_11\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"2B"
    )
        port map (
      I0 => address_reg(7),
      I1 => \eol1_carry__2_n_4\,
      I2 => address_reg(5),
      O => \eol1__60_carry__2_i_11_n_0\
    );
\eol1__60_carry__2_i_12\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"2B"
    )
        port map (
      I0 => address_reg(10),
      I1 => \eol1_carry__3_n_5\,
      I2 => address_reg(8),
      O => \eol1__60_carry__2_i_12_n_0\
    );
\eol1__60_carry__2_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"4DD4D44D"
    )
        port map (
      I0 => \eol1__60_carry__2_i_10_n_0\,
      I1 => address_reg(12),
      I2 => address_reg(7),
      I3 => \eol1_carry__3_n_6\,
      I4 => address_reg(9),
      O => \eol1__60_carry__2_i_2_n_0\
    );
\eol1__60_carry__2_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"4DD4D44D"
    )
        port map (
      I0 => \eol1__60_carry__2_i_11_n_0\,
      I1 => address_reg(11),
      I2 => address_reg(6),
      I3 => \eol1_carry__3_n_7\,
      I4 => address_reg(8),
      O => \eol1__60_carry__2_i_3_n_0\
    );
\eol1__60_carry__2_i_4\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"69FF0069"
    )
        port map (
      I0 => address_reg(5),
      I1 => \eol1_carry__2_n_4\,
      I2 => address_reg(7),
      I3 => \eol1__60_carry__1_i_12_n_0\,
      I4 => address_reg(10),
      O => \eol1__60_carry__2_i_4_n_0\
    );
\eol1__60_carry__2_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"6996966996696996"
    )
        port map (
      I0 => \eol1__60_carry__2_i_1_n_0\,
      I1 => address_reg(14),
      I2 => address_reg(11),
      I3 => \eol1_carry__3_n_4\,
      I4 => address_reg(9),
      I5 => \eol1__60_carry__2_i_12_n_0\,
      O => \eol1__60_carry__2_i_5_n_0\
    );
\eol1__60_carry__2_i_6\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"6996966996696996"
    )
        port map (
      I0 => \eol1__60_carry__2_i_2_n_0\,
      I1 => address_reg(13),
      I2 => address_reg(10),
      I3 => \eol1_carry__3_n_5\,
      I4 => address_reg(8),
      I5 => \eol1__60_carry__2_i_9_n_0\,
      O => \eol1__60_carry__2_i_6_n_0\
    );
\eol1__60_carry__2_i_7\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"6996966996696996"
    )
        port map (
      I0 => \eol1__60_carry__2_i_3_n_0\,
      I1 => address_reg(12),
      I2 => address_reg(9),
      I3 => \eol1_carry__3_n_6\,
      I4 => address_reg(7),
      I5 => \eol1__60_carry__2_i_10_n_0\,
      O => \eol1__60_carry__2_i_7_n_0\
    );
\eol1__60_carry__2_i_8\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"6996966996696996"
    )
        port map (
      I0 => \eol1__60_carry__2_i_4_n_0\,
      I1 => address_reg(11),
      I2 => address_reg(8),
      I3 => \eol1_carry__3_n_7\,
      I4 => address_reg(6),
      I5 => \eol1__60_carry__2_i_11_n_0\,
      O => \eol1__60_carry__2_i_8_n_0\
    );
\eol1__60_carry__2_i_9\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"2B"
    )
        port map (
      I0 => address_reg(9),
      I1 => \eol1_carry__3_n_6\,
      I2 => address_reg(7),
      O => \eol1__60_carry__2_i_9_n_0\
    );
\eol1__60_carry__3\: unisim.vcomponents.CARRY4
     port map (
      CI => \eol1__60_carry__2_n_0\,
      CO(3 downto 1) => \NLW_eol1__60_carry__3_CO_UNCONNECTED\(3 downto 1),
      CO(0) => \eol1__60_carry__3_n_3\,
      CYINIT => '0',
      DI(3 downto 1) => B"000",
      DI(0) => \eol1__60_carry__3_i_1_n_0\,
      O(3 downto 2) => \NLW_eol1__60_carry__3_O_UNCONNECTED\(3 downto 2),
      O(1) => \eol1__60_carry__3_n_6\,
      O(0) => \eol1__60_carry__3_n_7\,
      S(3 downto 2) => B"00",
      S(1) => \eol1__60_carry__3_i_2_n_0\,
      S(0) => \eol1__60_carry__3_i_3_n_0\
    );
\eol1__60_carry__3_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"4DD4D44D"
    )
        port map (
      I0 => \eol1__60_carry__2_i_12_n_0\,
      I1 => address_reg(14),
      I2 => address_reg(9),
      I3 => \eol1_carry__3_n_4\,
      I4 => address_reg(11),
      O => \eol1__60_carry__3_i_1_n_0\
    );
\eol1__60_carry__3_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"6559A665599A6559"
    )
        port map (
      I0 => \eol1__60_carry__3_i_4_n_0\,
      I1 => address_reg(12),
      I2 => \eol1_carry__4_n_7\,
      I3 => address_reg(10),
      I4 => \eol1__60_carry__3_i_5_n_0\,
      I5 => address_reg(15),
      O => \eol1__60_carry__3_i_2_n_0\
    );
\eol1__60_carry__3_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"6996966996696996"
    )
        port map (
      I0 => \eol1__60_carry__3_i_1_n_0\,
      I1 => address_reg(15),
      I2 => address_reg(12),
      I3 => \eol1_carry__4_n_7\,
      I4 => address_reg(10),
      I5 => \eol1__60_carry__3_i_5_n_0\,
      O => \eol1__60_carry__3_i_3_n_0\
    );
\eol1__60_carry__3_i_4\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9669"
    )
        port map (
      I0 => address_reg(16),
      I1 => address_reg(13),
      I2 => \eol1_carry__4_n_6\,
      I3 => address_reg(11),
      O => \eol1__60_carry__3_i_4_n_0\
    );
\eol1__60_carry__3_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"2B"
    )
        port map (
      I0 => address_reg(11),
      I1 => \eol1_carry__3_n_4\,
      I2 => address_reg(9),
      O => \eol1__60_carry__3_i_5_n_0\
    );
\eol1__60_carry_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => address_reg(2),
      I1 => \eol1_carry__0_n_4\,
      O => \eol1__60_carry_i_1_n_0\
    );
\eol1__60_carry_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => address_reg(1),
      I1 => \eol1_carry__0_n_5\,
      O => \eol1__60_carry_i_2_n_0\
    );
\eol1__60_carry_i_3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => address_reg(0),
      I1 => \eol1_carry__0_n_6\,
      O => \eol1__60_carry_i_3_n_0\
    );
\eol1__97_carry\: unisim.vcomponents.CARRY4
     port map (
      CI => '0',
      CO(3 downto 2) => \NLW_eol1__97_carry_CO_UNCONNECTED\(3 downto 2),
      CO(1) => \eol1__97_carry_n_2\,
      CO(0) => \eol1__97_carry_n_3\,
      CYINIT => '0',
      DI(3 downto 2) => B"00",
      DI(1) => \eol1__60_carry__3_n_7\,
      DI(0) => '0',
      O(3) => \NLW_eol1__97_carry_O_UNCONNECTED\(3),
      O(2) => \eol1__97_carry_n_5\,
      O(1) => \eol1__97_carry_n_6\,
      O(0) => \eol1__97_carry_n_7\,
      S(3) => '0',
      S(2) => \eol1__97_carry_i_1_n_0\,
      S(1) => \eol1__97_carry_i_2_n_0\,
      S(0) => \eol1__60_carry__2_n_4\
    );
\eol1__97_carry_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => \eol1__60_carry__2_n_4\,
      I1 => \eol1__60_carry__3_n_6\,
      O => \eol1__97_carry_i_1_n_0\
    );
\eol1__97_carry_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => \eol1__60_carry__3_n_7\,
      I1 => \eol1__60_carry__2_n_5\,
      O => \eol1__97_carry_i_2_n_0\
    );
eol1_carry: unisim.vcomponents.CARRY4
     port map (
      CI => '0',
      CO(3) => eol1_carry_n_0,
      CO(2) => eol1_carry_n_1,
      CO(1) => eol1_carry_n_2,
      CO(0) => eol1_carry_n_3,
      CYINIT => '0',
      DI(3 downto 2) => address_reg(1 downto 0),
      DI(1 downto 0) => B"01",
      O(3 downto 0) => NLW_eol1_carry_O_UNCONNECTED(3 downto 0),
      S(3) => eol1_carry_i_1_n_0,
      S(2) => eol1_carry_i_2_n_0,
      S(1) => eol1_carry_i_3_n_0,
      S(0) => address_reg(0)
    );
\eol1_carry__0\: unisim.vcomponents.CARRY4
     port map (
      CI => eol1_carry_n_0,
      CO(3) => \eol1_carry__0_n_0\,
      CO(2) => \eol1_carry__0_n_1\,
      CO(1) => \eol1_carry__0_n_2\,
      CO(0) => \eol1_carry__0_n_3\,
      CYINIT => '0',
      DI(3) => \eol1_carry__0_i_1_n_0\,
      DI(2) => \eol1_carry__0_i_2_n_0\,
      DI(1) => \eol1_carry__0_i_3_n_0\,
      DI(0) => address_reg(2),
      O(3) => \eol1_carry__0_n_4\,
      O(2) => \eol1_carry__0_n_5\,
      O(1) => \eol1_carry__0_n_6\,
      O(0) => \eol1_carry__0_n_7\,
      S(3) => \eol1_carry__0_i_4_n_0\,
      S(2) => \eol1_carry__0_i_5_n_0\,
      S(1) => \eol1_carry__0_i_6_n_0\,
      S(0) => \eol1_carry__0_i_7_n_0\
    );
\eol1_carry__0_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"D4"
    )
        port map (
      I0 => address_reg(6),
      I1 => address_reg(2),
      I2 => address_reg(4),
      O => \eol1_carry__0_i_1_n_0\
    );
\eol1_carry__0_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B2"
    )
        port map (
      I0 => address_reg(1),
      I1 => address_reg(5),
      I2 => address_reg(3),
      O => \eol1_carry__0_i_2_n_0\
    );
\eol1_carry__0_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"69"
    )
        port map (
      I0 => address_reg(3),
      I1 => address_reg(5),
      I2 => address_reg(1),
      O => \eol1_carry__0_i_3_n_0\
    );
\eol1_carry__0_i_4\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9669"
    )
        port map (
      I0 => address_reg(7),
      I1 => address_reg(3),
      I2 => address_reg(5),
      I3 => \eol1_carry__0_i_1_n_0\,
      O => \eol1_carry__0_i_4_n_0\
    );
\eol1_carry__0_i_5\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9669"
    )
        port map (
      I0 => address_reg(6),
      I1 => address_reg(2),
      I2 => address_reg(4),
      I3 => \eol1_carry__0_i_2_n_0\,
      O => \eol1_carry__0_i_5_n_0\
    );
\eol1_carry__0_i_6\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"69966969"
    )
        port map (
      I0 => address_reg(1),
      I1 => address_reg(5),
      I2 => address_reg(3),
      I3 => address_reg(4),
      I4 => address_reg(0),
      O => \eol1_carry__0_i_6_n_0\
    );
\eol1_carry__0_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"69"
    )
        port map (
      I0 => address_reg(4),
      I1 => address_reg(0),
      I2 => address_reg(2),
      O => \eol1_carry__0_i_7_n_0\
    );
\eol1_carry__1\: unisim.vcomponents.CARRY4
     port map (
      CI => \eol1_carry__0_n_0\,
      CO(3) => \eol1_carry__1_n_0\,
      CO(2) => \eol1_carry__1_n_1\,
      CO(1) => \eol1_carry__1_n_2\,
      CO(0) => \eol1_carry__1_n_3\,
      CYINIT => '0',
      DI(3) => \eol1_carry__1_i_1_n_0\,
      DI(2) => \eol1_carry__1_i_2_n_0\,
      DI(1) => \eol1_carry__1_i_3_n_0\,
      DI(0) => \eol1_carry__1_i_4_n_0\,
      O(3) => \eol1_carry__1_n_4\,
      O(2) => \eol1_carry__1_n_5\,
      O(1) => \eol1_carry__1_n_6\,
      O(0) => \eol1_carry__1_n_7\,
      S(3) => \eol1_carry__1_i_5_n_0\,
      S(2) => \eol1_carry__1_i_6_n_0\,
      S(1) => \eol1_carry__1_i_7_n_0\,
      S(0) => \eol1_carry__1_i_8_n_0\
    );
\eol1_carry__1_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B2"
    )
        port map (
      I0 => address_reg(6),
      I1 => address_reg(10),
      I2 => address_reg(8),
      O => \eol1_carry__1_i_1_n_0\
    );
\eol1_carry__1_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B2"
    )
        port map (
      I0 => address_reg(5),
      I1 => address_reg(9),
      I2 => address_reg(7),
      O => \eol1_carry__1_i_2_n_0\
    );
\eol1_carry__1_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B2"
    )
        port map (
      I0 => address_reg(4),
      I1 => address_reg(8),
      I2 => address_reg(6),
      O => \eol1_carry__1_i_3_n_0\
    );
\eol1_carry__1_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"D4"
    )
        port map (
      I0 => address_reg(7),
      I1 => address_reg(3),
      I2 => address_reg(5),
      O => \eol1_carry__1_i_4_n_0\
    );
\eol1_carry__1_i_5\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9669"
    )
        port map (
      I0 => address_reg(7),
      I1 => address_reg(11),
      I2 => address_reg(9),
      I3 => \eol1_carry__1_i_1_n_0\,
      O => \eol1_carry__1_i_5_n_0\
    );
\eol1_carry__1_i_6\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9669"
    )
        port map (
      I0 => address_reg(6),
      I1 => address_reg(10),
      I2 => address_reg(8),
      I3 => \eol1_carry__1_i_2_n_0\,
      O => \eol1_carry__1_i_6_n_0\
    );
\eol1_carry__1_i_7\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9669"
    )
        port map (
      I0 => address_reg(5),
      I1 => address_reg(9),
      I2 => address_reg(7),
      I3 => \eol1_carry__1_i_3_n_0\,
      O => \eol1_carry__1_i_7_n_0\
    );
\eol1_carry__1_i_8\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9669"
    )
        port map (
      I0 => address_reg(4),
      I1 => address_reg(8),
      I2 => address_reg(6),
      I3 => \eol1_carry__1_i_4_n_0\,
      O => \eol1_carry__1_i_8_n_0\
    );
\eol1_carry__2\: unisim.vcomponents.CARRY4
     port map (
      CI => \eol1_carry__1_n_0\,
      CO(3) => \eol1_carry__2_n_0\,
      CO(2) => \eol1_carry__2_n_1\,
      CO(1) => \eol1_carry__2_n_2\,
      CO(0) => \eol1_carry__2_n_3\,
      CYINIT => '0',
      DI(3) => \eol1_carry__2_i_1_n_0\,
      DI(2) => \eol1_carry__2_i_2_n_0\,
      DI(1) => \eol1_carry__2_i_3_n_0\,
      DI(0) => \eol1_carry__2_i_4_n_0\,
      O(3) => \eol1_carry__2_n_4\,
      O(2) => \eol1_carry__2_n_5\,
      O(1) => \eol1_carry__2_n_6\,
      O(0) => \eol1_carry__2_n_7\,
      S(3) => \eol1_carry__2_i_5_n_0\,
      S(2) => \eol1_carry__2_i_6_n_0\,
      S(1) => \eol1_carry__2_i_7_n_0\,
      S(0) => \eol1_carry__2_i_8_n_0\
    );
\eol1_carry__2_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B2"
    )
        port map (
      I0 => address_reg(10),
      I1 => address_reg(14),
      I2 => address_reg(12),
      O => \eol1_carry__2_i_1_n_0\
    );
\eol1_carry__2_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B2"
    )
        port map (
      I0 => address_reg(9),
      I1 => address_reg(13),
      I2 => address_reg(11),
      O => \eol1_carry__2_i_2_n_0\
    );
\eol1_carry__2_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B2"
    )
        port map (
      I0 => address_reg(8),
      I1 => address_reg(12),
      I2 => address_reg(10),
      O => \eol1_carry__2_i_3_n_0\
    );
\eol1_carry__2_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B2"
    )
        port map (
      I0 => address_reg(7),
      I1 => address_reg(11),
      I2 => address_reg(9),
      O => \eol1_carry__2_i_4_n_0\
    );
\eol1_carry__2_i_5\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9669"
    )
        port map (
      I0 => address_reg(13),
      I1 => address_reg(15),
      I2 => address_reg(11),
      I3 => \eol1_carry__2_i_1_n_0\,
      O => \eol1_carry__2_i_5_n_0\
    );
\eol1_carry__2_i_6\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9669"
    )
        port map (
      I0 => address_reg(10),
      I1 => address_reg(14),
      I2 => address_reg(12),
      I3 => \eol1_carry__2_i_2_n_0\,
      O => \eol1_carry__2_i_6_n_0\
    );
\eol1_carry__2_i_7\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9669"
    )
        port map (
      I0 => address_reg(9),
      I1 => address_reg(13),
      I2 => address_reg(11),
      I3 => \eol1_carry__2_i_3_n_0\,
      O => \eol1_carry__2_i_7_n_0\
    );
\eol1_carry__2_i_8\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9669"
    )
        port map (
      I0 => address_reg(8),
      I1 => address_reg(12),
      I2 => address_reg(10),
      I3 => \eol1_carry__2_i_4_n_0\,
      O => \eol1_carry__2_i_8_n_0\
    );
\eol1_carry__3\: unisim.vcomponents.CARRY4
     port map (
      CI => \eol1_carry__2_n_0\,
      CO(3) => \eol1_carry__3_n_0\,
      CO(2) => \eol1_carry__3_n_1\,
      CO(1) => \eol1_carry__3_n_2\,
      CO(0) => \eol1_carry__3_n_3\,
      CYINIT => '0',
      DI(3) => \eol1_carry__3_i_1_n_0\,
      DI(2) => \eol1_carry__3_i_2_n_0\,
      DI(1) => \eol1_carry__3_i_3_n_0\,
      DI(0) => \eol1_carry__3_i_4_n_0\,
      O(3) => \eol1_carry__3_n_4\,
      O(2) => \eol1_carry__3_n_5\,
      O(1) => \eol1_carry__3_n_6\,
      O(0) => \eol1_carry__3_n_7\,
      S(3) => \eol1_carry__3_i_5_n_0\,
      S(2) => \eol1_carry__3_i_6_n_0\,
      S(1) => \eol1_carry__3_i_7_n_0\,
      S(0) => \eol1_carry__3_i_8_n_0\
    );
\eol1_carry__3_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B2"
    )
        port map (
      I0 => address_reg(16),
      I1 => address_reg(18),
      I2 => address_reg(14),
      O => \eol1_carry__3_i_1_n_0\
    );
\eol1_carry__3_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B2"
    )
        port map (
      I0 => address_reg(15),
      I1 => address_reg(17),
      I2 => address_reg(13),
      O => \eol1_carry__3_i_2_n_0\
    );
\eol1_carry__3_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B2"
    )
        port map (
      I0 => address_reg(12),
      I1 => address_reg(16),
      I2 => address_reg(14),
      O => \eol1_carry__3_i_3_n_0\
    );
\eol1_carry__3_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B2"
    )
        port map (
      I0 => address_reg(13),
      I1 => address_reg(15),
      I2 => address_reg(11),
      O => \eol1_carry__3_i_4_n_0\
    );
\eol1_carry__3_i_5\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"4DB2B24D"
    )
        port map (
      I0 => address_reg(14),
      I1 => address_reg(18),
      I2 => address_reg(16),
      I3 => address_reg(17),
      I4 => address_reg(15),
      O => \eol1_carry__3_i_5_n_0\
    );
\eol1_carry__3_i_6\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9669"
    )
        port map (
      I0 => \eol1_carry__3_i_2_n_0\,
      I1 => address_reg(16),
      I2 => address_reg(18),
      I3 => address_reg(14),
      O => \eol1_carry__3_i_6_n_0\
    );
\eol1_carry__3_i_7\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9669"
    )
        port map (
      I0 => address_reg(15),
      I1 => address_reg(17),
      I2 => address_reg(13),
      I3 => \eol1_carry__3_i_3_n_0\,
      O => \eol1_carry__3_i_7_n_0\
    );
\eol1_carry__3_i_8\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9669"
    )
        port map (
      I0 => address_reg(12),
      I1 => address_reg(16),
      I2 => address_reg(14),
      I3 => \eol1_carry__3_i_4_n_0\,
      O => \eol1_carry__3_i_8_n_0\
    );
\eol1_carry__4\: unisim.vcomponents.CARRY4
     port map (
      CI => \eol1_carry__3_n_0\,
      CO(3 downto 1) => \NLW_eol1_carry__4_CO_UNCONNECTED\(3 downto 1),
      CO(0) => \eol1_carry__4_n_3\,
      CYINIT => '0',
      DI(3 downto 1) => B"000",
      DI(0) => \eol1_carry__4_i_1_n_0\,
      O(3 downto 2) => \NLW_eol1_carry__4_O_UNCONNECTED\(3 downto 2),
      O(1) => \eol1_carry__4_n_6\,
      O(0) => \eol1_carry__4_n_7\,
      S(3 downto 2) => B"00",
      S(1) => \eol1_carry__4_i_2_n_0\,
      S(0) => \eol1_carry__4_i_3_n_0\
    );
\eol1_carry__4_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => address_reg(17),
      I1 => address_reg(15),
      O => \eol1_carry__4_i_1_n_0\
    );
\eol1_carry__4_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A9"
    )
        port map (
      I0 => address_reg(17),
      I1 => address_reg(18),
      I2 => address_reg(16),
      O => \eol1_carry__4_i_2_n_0\
    );
\eol1_carry__4_i_3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"1EE1"
    )
        port map (
      I0 => address_reg(17),
      I1 => address_reg(15),
      I2 => address_reg(18),
      I3 => address_reg(16),
      O => \eol1_carry__4_i_3_n_0\
    );
eol1_carry_i_1: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => address_reg(1),
      I1 => address_reg(3),
      O => eol1_carry_i_1_n_0
    );
eol1_carry_i_2: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => address_reg(0),
      I1 => address_reg(2),
      O => eol1_carry_i_2_n_0
    );
eol1_carry_i_3: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => address_reg(1),
      O => eol1_carry_i_3_n_0
    );
eol_i_1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000040"
    )
        port map (
      I0 => eol_i_2_n_0,
      I1 => sel0(2),
      I2 => sel0(5),
      I3 => \eol1__103_carry__0_n_4\,
      I4 => eol_i_3_n_0,
      O => eol_i_1_n_0
    );
eol_i_2: unisim.vcomponents.LUT4
    generic map(
      INIT => X"7FFF"
    )
        port map (
      I0 => sel0(3),
      I1 => sel0(0),
      I2 => sel0(4),
      I3 => sel0(1),
      O => eol_i_2_n_0
    );
eol_i_3: unisim.vcomponents.LUT3
    generic map(
      INIT => X"BD"
    )
        port map (
      I0 => \eol1__103_carry__1_n_7\,
      I1 => \eol1__103_carry__0_n_5\,
      I2 => \eol1__103_carry__1_n_6\,
      O => eol_i_3_n_0
    );
eol_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => '1',
      D => eol_i_1_n_0,
      Q => m_axis_tlast,
      R => '0'
    );
\href_last[0]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => href_last(0),
      I1 => latched_href,
      I2 => latched_vsync,
      O => \href_last[0]_i_1_n_0\
    );
\href_last_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => '1',
      D => \href_last[0]_i_1_n_0\,
      Q => href_last(0),
      R => '0'
    );
\latched_d_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0',
      IS_C_INVERTED => '1'
    )
        port map (
      C => pclk,
      CE => '1',
      D => d(0),
      Q => p_0_in(0),
      R => '0'
    );
\latched_d_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0',
      IS_C_INVERTED => '1'
    )
        port map (
      C => pclk,
      CE => '1',
      D => d(1),
      Q => p_0_in(1),
      R => '0'
    );
\latched_d_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0',
      IS_C_INVERTED => '1'
    )
        port map (
      C => pclk,
      CE => '1',
      D => d(2),
      Q => p_0_in(2),
      R => '0'
    );
\latched_d_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0',
      IS_C_INVERTED => '1'
    )
        port map (
      C => pclk,
      CE => '1',
      D => d(3),
      Q => p_0_in(3),
      R => '0'
    );
\latched_d_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0',
      IS_C_INVERTED => '1'
    )
        port map (
      C => pclk,
      CE => '1',
      D => d(4),
      Q => p_0_in(4),
      R => '0'
    );
\latched_d_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0',
      IS_C_INVERTED => '1'
    )
        port map (
      C => pclk,
      CE => '1',
      D => d(5),
      Q => p_0_in(5),
      R => '0'
    );
\latched_d_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0',
      IS_C_INVERTED => '1'
    )
        port map (
      C => pclk,
      CE => '1',
      D => d(6),
      Q => p_0_in(6),
      R => '0'
    );
\latched_d_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0',
      IS_C_INVERTED => '1'
    )
        port map (
      C => pclk,
      CE => '1',
      D => d(7),
      Q => p_0_in(7),
      R => '0'
    );
latched_href_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0',
      IS_C_INVERTED => '1'
    )
        port map (
      C => pclk,
      CE => '1',
      D => href,
      Q => latched_href,
      R => '0'
    );
latched_vsync_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0',
      IS_C_INVERTED => '1'
    )
        port map (
      C => pclk,
      CE => '1',
      D => vsync,
      Q => latched_vsync,
      R => '0'
    );
sof_i_1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000002"
    )
        port map (
      I0 => sof_i_2_n_0,
      I1 => sof_i_3_n_0,
      I2 => address_reg(0),
      I3 => address_reg(14),
      I4 => address_reg(10),
      O => sof_i_1_n_0
    );
sof_i_2: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000000004"
    )
        port map (
      I0 => sof_i_4_n_0,
      I1 => sof_i_5_n_0,
      I2 => address_reg(1),
      I3 => address_reg(3),
      I4 => address_reg(11),
      I5 => address_reg(13),
      O => sof_i_2_n_0
    );
sof_i_3: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFFFFFE"
    )
        port map (
      I0 => address_reg(4),
      I1 => address_reg(6),
      I2 => address_reg(2),
      I3 => address_reg(9),
      I4 => sof_i_6_n_0,
      O => sof_i_3_n_0
    );
sof_i_4: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => address_reg(16),
      I1 => address_reg(18),
      O => sof_i_4_n_0
    );
sof_i_5: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => address_reg(15),
      I1 => address_reg(17),
      O => sof_i_5_n_0
    );
sof_i_6: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFE"
    )
        port map (
      I0 => address_reg(12),
      I1 => address_reg(8),
      I2 => address_reg(7),
      I3 => address_reg(5),
      O => sof_i_6_n_0
    );
sof_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => '1',
      D => sof_i_1_n_0,
      Q => m_axis_tuser,
      R => '0'
    );
we_reg_i_1: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => href_last(0),
      I1 => latched_vsync,
      O => we_reg_i_1_n_0
    );
we_reg_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => pclk,
      CE => '1',
      D => we_reg_i_1_n_0,
      Q => \^m_axis_tvalid\,
      R => '0'
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix is
  port (
    pclk : in STD_LOGIC;
    vsync : in STD_LOGIC;
    href : in STD_LOGIC;
    d : in STD_LOGIC_VECTOR ( 7 downto 0 );
    m_axis_tvalid : out STD_LOGIC;
    m_axis_tready : in STD_LOGIC;
    m_axis_tlast : out STD_LOGIC;
    m_axis_tdata : out STD_LOGIC_VECTOR ( 23 downto 0 );
    m_axis_tuser : out STD_LOGIC;
    aclk : out STD_LOGIC
  );
  attribute NotValidForBitStream : boolean;
  attribute NotValidForBitStream of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is true;
  attribute CHECK_LICENSE_TYPE : string;
  attribute CHECK_LICENSE_TYPE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "design_1_ov7670_axi_stream_ca_0_0,ov7670_axi_stream_capture,{}";
  attribute downgradeipidentifiedwarnings : string;
  attribute downgradeipidentifiedwarnings of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "yes";
  attribute ip_definition_source : string;
  attribute ip_definition_source of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "package_project";
  attribute x_core_info : string;
  attribute x_core_info of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "ov7670_axi_stream_capture,Vivado 2019.1";
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix is
  signal \^m_axis_tdata\ : STD_LOGIC_VECTOR ( 23 downto 0 );
  attribute x_interface_info : string;
  attribute x_interface_info of aclk : signal is "xilinx.com:signal:clock:1.0 aclk CLK";
  attribute x_interface_parameter : string;
  attribute x_interface_parameter of aclk : signal is "XIL_INTERFACENAME aclk, FREQ_HZ 100000000, PHASE 0.000, CLK_DOMAIN design_1_ov7670_axi_stream_ca_0_0_aclk, INSERT_VIP 0";
begin
  m_axis_tdata(23 downto 19) <= \^m_axis_tdata\(23 downto 19);
  m_axis_tdata(18) <= \^m_axis_tdata\(19);
  m_axis_tdata(17) <= \^m_axis_tdata\(19);
  m_axis_tdata(16) <= \^m_axis_tdata\(19);
  m_axis_tdata(15 downto 10) <= \^m_axis_tdata\(15 downto 10);
  m_axis_tdata(9) <= \^m_axis_tdata\(10);
  m_axis_tdata(8) <= \^m_axis_tdata\(10);
  m_axis_tdata(7 downto 4) <= \^m_axis_tdata\(7 downto 4);
  m_axis_tdata(3) <= \^m_axis_tdata\(0);
  m_axis_tdata(2) <= \^m_axis_tdata\(0);
  m_axis_tdata(1) <= \^m_axis_tdata\(0);
  m_axis_tdata(0) <= \^m_axis_tdata\(0);
U0: entity work.decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ov7670_axi_stream_capture
     port map (
      d(7 downto 0) => d(7 downto 0),
      href => href,
      m_axis_tdata(15 downto 11) => \^m_axis_tdata\(23 downto 19),
      m_axis_tdata(10 downto 5) => \^m_axis_tdata\(15 downto 10),
      m_axis_tdata(4 downto 1) => \^m_axis_tdata\(7 downto 4),
      m_axis_tdata(0) => \^m_axis_tdata\(0),
      m_axis_tlast => m_axis_tlast,
      m_axis_tuser => m_axis_tuser,
      m_axis_tvalid => m_axis_tvalid,
      pclk => pclk,
      vsync => vsync
    );
aclk_INST_0: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => pclk,
      O => aclk
    );
end STRUCTURE;