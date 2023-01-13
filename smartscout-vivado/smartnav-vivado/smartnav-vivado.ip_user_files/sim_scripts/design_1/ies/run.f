-makelib ies_lib/xilinx_vip -sv \
  "/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/axi4stream_vip_axi4streampc.sv" \
  "/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/axi_vip_axi4pc.sv" \
  "/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/xil_common_vip_pkg.sv" \
  "/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/axi4stream_vip_pkg.sv" \
  "/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/axi_vip_pkg.sv" \
  "/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/axi4stream_vip_if.sv" \
  "/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/axi_vip_if.sv" \
  "/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/clk_vip_if.sv" \
  "/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/rst_vip_if.sv" \
-endlib
-makelib ies_lib/xil_defaultlib -sv \
  "/tools/Xilinx/Vivado/2019.1/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
  "/tools/Xilinx/Vivado/2019.1/data/ip/xpm/xpm_fifo/hdl/xpm_fifo.sv" \
  "/tools/Xilinx/Vivado/2019.1/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \
-endlib
-makelib ies_lib/xpm \
  "/tools/Xilinx/Vivado/2019.1/data/ip/xpm/xpm_VCOMP.vhd" \
-endlib
-makelib ies_lib/xil_defaultlib \
  "/media/kuhiu/5e8324a1-752c-4afa-961c-05d693d0ddc6/SmartNavSys/platform/image/VivadoProj/project_1/project_1.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1/design_1_processing_system7_0_0_sim_netlist.v" \
  "../../../bd/design_1/ip/design_1_xbar_0_1/design_1_xbar_0_sim_netlist.v" \
  "../../../bd/design_1/ip/design_1_rst_ps7_0_50M_0_1/design_1_rst_ps7_0_50M_0_sim_netlist.v" \
  "../../../bd/design_1/ip/design_1_axi_timer_0_0/design_1_axi_timer_0_0_sim_netlist.v" \
  "../../../bd/design_1/ip/design_1_axi_gpio_0_0_1/design_1_axi_gpio_0_0_sim_netlist.v" \
  "../../../bd/design_1/ip/design_1_axi_gpio_1_0_1/design_1_axi_gpio_1_0_sim_netlist.v" \
-endlib
-makelib ies_lib/xlconcat_v2_1_3 \
  "../../../../project_1.srcs/sources_1/bd/design_1/ipshared/442e/hdl/xlconcat_v2_1_vl_rfs.v" \
-endlib
-makelib ies_lib/xil_defaultlib \
  "../../../bd/design_1/ip/design_1_xlconcat_0_0/sim/design_1_xlconcat_0_0.v" \
  "../../../bd/design_1/ip/design_1_axi_gpio_2_0/design_1_axi_gpio_2_0_sim_netlist.v" \
  "../../../bd/design_1/ip/design_1_axi_gpio_2_1/design_1_axi_gpio_2_1_sim_netlist.v" \
  "../../../bd/design_1/ip/design_1_axi_gpio_4_0/design_1_axi_gpio_4_0_sim_netlist.v" \
  "../../../bd/design_1/ip/design_1_axi_gpio_5_0/design_1_axi_gpio_5_0_sim_netlist.v" \
  "../../../bd/design_1/ip/design_1_axi_timer_1_0/design_1_axi_timer_1_0_sim_netlist.v" \
  "../../../bd/design_1/ip/design_1_axi_gpio_6_0/design_1_axi_gpio_6_0_sim_netlist.v" \
-endlib
-makelib ies_lib/v_frmbuf_wr_v2_1_2 \
  "../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/hdl/v_frmbuf_wr_v2_1_rfs.v" \
-endlib
-makelib ies_lib/xil_defaultlib \
  "../../../bd/design_1/ip/design_1_v_frmbuf_wr_0_0/sim/design_1_v_frmbuf_wr_0_0.v" \
  "../../../bd/design_1/ip/design_1_smartconnect_0_0/design_1_smartconnect_0_0_sim_netlist.v" \
-endlib
-makelib ies_lib/v_csc_v1_0_13 \
  "../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/hdl/v_csc_v1_0_rfs.v" \
-endlib
-makelib ies_lib/xil_defaultlib \
  "../../../bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/sim/bd_d92b_csc_0.v" \
  "../../../bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/sim/bd_d92b.v" \
  "../../../bd/design_1/ip/design_1_v_proc_ss_0_0/sim/design_1_v_proc_ss_0_0.v" \
-endlib
-makelib ies_lib/xlslice_v1_0_2 \
  "../../../../project_1.srcs/sources_1/bd/design_1/ipshared/f044/hdl/xlslice_v1_0_vl_rfs.v" \
-endlib
-makelib ies_lib/xil_defaultlib \
  "../../../bd/design_1/ip/design_1_xlslice_0_0/sim/design_1_xlslice_0_0.v" \
  "../../../bd/design_1/ip/design_1_xlslice_0_1/sim/design_1_xlslice_0_1.v" \
-endlib
-makelib ies_lib/v_demosaic_v1_0_5 \
  "../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/hdl/v_demosaic_v1_0_rfs.v" \
-endlib
-makelib ies_lib/xil_defaultlib \
  "../../../bd/design_1/ip/design_1_v_demosaic_0_0/sim/design_1_v_demosaic_0_0.v" \
  "../../../bd/design_1/ip/design_1_xlslice_1_0/sim/design_1_xlslice_1_0.v" \
-endlib
-makelib ies_lib/v_vid_in_axi4s_v4_0_9 \
  "../../../../project_1.srcs/sources_1/bd/design_1/ipshared/b2aa/hdl/v_vid_in_axi4s_v4_0_vl_rfs.v" \
-endlib
-makelib ies_lib/xil_defaultlib \
  "../../../bd/design_1/ip/design_1_v_vid_in_axi4s_0_0/sim/design_1_v_vid_in_axi4s_0_0.v" \
-endlib
-makelib ies_lib/xlconstant_v1_1_6 \
  "../../../../project_1.srcs/sources_1/bd/design_1/ipshared/66e7/hdl/xlconstant_v1_1_vl_rfs.v" \
-endlib
-makelib ies_lib/xil_defaultlib \
  "../../../bd/design_1/ip/design_1_xlconstant_0_0/sim/design_1_xlconstant_0_0.v" \
  "../../../bd/design_1/ip/design_1_xlconstant_0_1/sim/design_1_xlconstant_0_1.v" \
  "../../../bd/design_1/ip/design_1_xlslice_2_0/sim/design_1_xlslice_2_0.v" \
-endlib
-makelib ies_lib/util_vector_logic_v2_0_1 \
  "../../../../project_1.srcs/sources_1/bd/design_1/ipshared/2137/hdl/util_vector_logic_v2_0_vl_rfs.v" \
-endlib
-makelib ies_lib/xil_defaultlib \
  "../../../bd/design_1/ip/design_1_util_vector_logic_0_0/sim/design_1_util_vector_logic_0_0.v" \
  "../../../bd/design_1/ip/design_1_util_vector_logic_0_1/sim/design_1_util_vector_logic_0_1.v" \
  "../../../bd/design_1/ip/design_1_util_vector_logic_1_0/sim/design_1_util_vector_logic_1_0.v" \
  "../../../bd/design_1/ip/design_1_auto_pc_0/design_1_auto_pc_0_sim_netlist.v" \
  "../../../bd/design_1/sim/design_1.v" \
-endlib
-makelib ies_lib/xil_defaultlib \
  glbl.v
-endlib

