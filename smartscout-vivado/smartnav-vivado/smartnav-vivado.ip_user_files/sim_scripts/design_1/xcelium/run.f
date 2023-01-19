-makelib xcelium_lib/xilinx_vip -sv \
  "/opt/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/axi4stream_vip_axi4streampc.sv" \
  "/opt/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/axi_vip_axi4pc.sv" \
  "/opt/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/xil_common_vip_pkg.sv" \
  "/opt/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/axi4stream_vip_pkg.sv" \
  "/opt/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/axi_vip_pkg.sv" \
  "/opt/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/axi4stream_vip_if.sv" \
  "/opt/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/axi_vip_if.sv" \
  "/opt/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/clk_vip_if.sv" \
  "/opt/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/rst_vip_if.sv" \
-endlib
-makelib xcelium_lib/xil_defaultlib -sv \
  "/opt/Xilinx/Vivado/2019.1/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
  "/opt/Xilinx/Vivado/2019.1/data/ip/xpm/xpm_fifo/hdl/xpm_fifo.sv" \
  "/opt/Xilinx/Vivado/2019.1/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \
-endlib
-makelib xcelium_lib/xpm \
  "/opt/Xilinx/Vivado/2019.1/data/ip/xpm/xpm_VCOMP.vhd" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/design_1/ip/design_1_processing_system7_0_0_1/design_1_processing_system7_0_0_sim_netlist.v" \
  "../../../bd/design_1/ip/design_1_xbar_0_1/design_1_xbar_0_sim_netlist.v" \
  "../../../bd/design_1/ip/design_1_rst_ps7_0_50M_0_1/design_1_rst_ps7_0_50M_0_sim_netlist.v" \
  "../../../bd/design_1/ip/design_1_axi_timer_0_0/design_1_axi_timer_0_0_sim_netlist.v" \
-endlib
-makelib xcelium_lib/xlconcat_v2_1_3 \
  "../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/442e/hdl/xlconcat_v2_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/design_1/ip/design_1_xlconcat_0_0/sim/design_1_xlconcat_0_0.v" \
  "../../../bd/design_1/ip/design_1_axi_gpio_2_0/design_1_axi_gpio_2_0_sim_netlist.v" \
  "../../../bd/design_1/ip/design_1_axi_gpio_2_1/design_1_axi_gpio_2_1_sim_netlist.v" \
  "../../../bd/design_1/ip/design_1_axi_gpio_4_0/design_1_axi_gpio_4_0_sim_netlist.v" \
  "../../../bd/design_1/ip/design_1_axi_timer_1_0/design_1_axi_timer_1_0_sim_netlist.v" \
-endlib
-makelib xcelium_lib/v_frmbuf_wr_v2_1_2 \
  "../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/hdl/v_frmbuf_wr_v2_1_rfs.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/design_1/ip/design_1_v_frmbuf_wr_0_0/sim/design_1_v_frmbuf_wr_0_0.v" \
  "../../../bd/design_1/ip/design_1_smartconnect_0_0/design_1_smartconnect_0_0_sim_netlist.v" \
-endlib
-makelib xcelium_lib/xlslice_v1_0_2 \
  "../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/f044/hdl/xlslice_v1_0_vl_rfs.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/design_1/ip/design_1_xlslice_0_0/sim/design_1_xlslice_0_0.v" \
-endlib
-makelib xcelium_lib/v_demosaic_v1_0_5 \
  "../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/hdl/v_demosaic_v1_0_rfs.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/design_1/ip/design_1_v_demosaic_0_0/sim/design_1_v_demosaic_0_0.v" \
  "../../../bd/design_1/ip/design_1_xlslice_1_0/sim/design_1_xlslice_1_0.v" \
-endlib
-makelib xcelium_lib/v_vid_in_axi4s_v4_0_9 \
  "../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/b2aa/hdl/v_vid_in_axi4s_v4_0_vl_rfs.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/design_1/ip/design_1_v_vid_in_axi4s_0_0/sim/design_1_v_vid_in_axi4s_0_0.v" \
-endlib
-makelib xcelium_lib/xlconstant_v1_1_6 \
  "../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/66e7/hdl/xlconstant_v1_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/design_1/ip/design_1_xlconstant_0_0/sim/design_1_xlconstant_0_0.v" \
  "../../../bd/design_1/ip/design_1_xlconstant_0_1/sim/design_1_xlconstant_0_1.v" \
  "../../../bd/design_1/ip/design_1_xlslice_1_1/sim/design_1_xlslice_1_1.v" \
  "../../../bd/design_1/ip/design_1_xlslice_1_2/sim/design_1_xlslice_1_2.v" \
  "../../../bd/design_1/ip/design_1_axi_timer_1_1/design_1_axi_timer_1_1_sim_netlist.v" \
  "../../../bd/design_1/ip/design_1_axi_timer_1_2/design_1_axi_timer_1_2_sim_netlist.v" \
  "../../../bd/design_1/ip/design_1_xlslice_1_3/sim/design_1_xlslice_1_3.v" \
  "../../../bd/design_1/ip/design_1_xlslice_4_0/sim/design_1_xlslice_4_0.v" \
  "../../../bd/design_1/ip/design_1_xlslice_4_1/sim/design_1_xlslice_4_1.v" \
  "../../../bd/design_1/ip/design_1_xlslice_4_2/sim/design_1_xlslice_4_2.v" \
  "../../../bd/design_1/ip/design_1_xlslice_1_4/sim/design_1_xlslice_1_4.v" \
  "../../../bd/design_1/ip/design_1_xlslice_8_0/sim/design_1_xlslice_8_0.v" \
  "../../../bd/design_1/ip/design_1_xlslice_8_1/sim/design_1_xlslice_8_1.v" \
  "../../../bd/design_1/ip/design_1_xlslice_8_2/sim/design_1_xlslice_8_2.v" \
  "../../../bd/design_1/ip/design_1_xlslice_0_0_0/sim/design_1_xlslice_0_0_0.v" \
  "../../../bd/design_1/ip/design_1_xlslice_0_1_0/sim/design_1_xlslice_0_1_0.v" \
  "../../../bd/design_1/ip/design_1_xlslice_0_1_1/sim/design_1_xlslice_0_1_1.v" \
  "../../../bd/design_1/ip/design_1_xlslice_0_1_2/sim/design_1_xlslice_0_1_2.v" \
  "../../../bd/design_1/ip/design_1_auto_pc_0/design_1_auto_pc_0_sim_netlist.v" \
  "../../../bd/design_1/sim/design_1.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  glbl.v
-endlib

