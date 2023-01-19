vlib work
vlib riviera

vlib riviera/xilinx_vip
vlib riviera/xil_defaultlib
vlib riviera/xpm
vlib riviera/xlconcat_v2_1_3
vlib riviera/v_frmbuf_wr_v2_1_2
vlib riviera/xlslice_v1_0_2
vlib riviera/v_demosaic_v1_0_5
vlib riviera/v_vid_in_axi4s_v4_0_9
vlib riviera/xlconstant_v1_1_6

vmap xilinx_vip riviera/xilinx_vip
vmap xil_defaultlib riviera/xil_defaultlib
vmap xpm riviera/xpm
vmap xlconcat_v2_1_3 riviera/xlconcat_v2_1_3
vmap v_frmbuf_wr_v2_1_2 riviera/v_frmbuf_wr_v2_1_2
vmap xlslice_v1_0_2 riviera/xlslice_v1_0_2
vmap v_demosaic_v1_0_5 riviera/v_demosaic_v1_0_5
vmap v_vid_in_axi4s_v4_0_9 riviera/v_vid_in_axi4s_v4_0_9
vmap xlconstant_v1_1_6 riviera/xlconstant_v1_1_6

vlog -work xilinx_vip  -sv2k12 "+incdir+/opt/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"/opt/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/axi4stream_vip_axi4streampc.sv" \
"/opt/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/axi_vip_axi4pc.sv" \
"/opt/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/xil_common_vip_pkg.sv" \
"/opt/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/axi4stream_vip_pkg.sv" \
"/opt/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/axi_vip_pkg.sv" \
"/opt/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/axi4stream_vip_if.sv" \
"/opt/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/axi_vip_if.sv" \
"/opt/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/clk_vip_if.sv" \
"/opt/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/rst_vip_if.sv" \

vlog -work xil_defaultlib  -sv2k12 "+incdir+../../../bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/1ddd/hdl/verilog" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/b2d0/hdl/verilog" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+/opt/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"/opt/Xilinx/Vivado/2019.1/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
"/opt/Xilinx/Vivado/2019.1/data/ip/xpm/xpm_fifo/hdl/xpm_fifo.sv" \
"/opt/Xilinx/Vivado/2019.1/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \

vcom -work xpm -93 \
"/opt/Xilinx/Vivado/2019.1/data/ip/xpm/xpm_VCOMP.vhd" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/1ddd/hdl/verilog" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/b2d0/hdl/verilog" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+/opt/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_processing_system7_0_0_1/design_1_processing_system7_0_0_sim_netlist.v" \
"../../../bd/design_1/ip/design_1_xbar_0_1/design_1_xbar_0_sim_netlist.v" \
"../../../bd/design_1/ip/design_1_rst_ps7_0_50M_0_1/design_1_rst_ps7_0_50M_0_sim_netlist.v" \
"../../../bd/design_1/ip/design_1_axi_timer_0_0/design_1_axi_timer_0_0_sim_netlist.v" \

vlog -work xlconcat_v2_1_3  -v2k5 "+incdir+../../../bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/1ddd/hdl/verilog" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/b2d0/hdl/verilog" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+/opt/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/442e/hdl/xlconcat_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/1ddd/hdl/verilog" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/b2d0/hdl/verilog" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+/opt/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_xlconcat_0_0/sim/design_1_xlconcat_0_0.v" \
"../../../bd/design_1/ip/design_1_axi_gpio_2_0/design_1_axi_gpio_2_0_sim_netlist.v" \
"../../../bd/design_1/ip/design_1_axi_gpio_2_1/design_1_axi_gpio_2_1_sim_netlist.v" \
"../../../bd/design_1/ip/design_1_axi_gpio_4_0/design_1_axi_gpio_4_0_sim_netlist.v" \
"../../../bd/design_1/ip/design_1_axi_timer_1_0/design_1_axi_timer_1_0_sim_netlist.v" \

vlog -work v_frmbuf_wr_v2_1_2  -v2k5 "+incdir+../../../bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/1ddd/hdl/verilog" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/b2d0/hdl/verilog" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+/opt/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/hdl/v_frmbuf_wr_v2_1_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/1ddd/hdl/verilog" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/b2d0/hdl/verilog" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+/opt/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_v_frmbuf_wr_0_0/sim/design_1_v_frmbuf_wr_0_0.v" \
"../../../bd/design_1/ip/design_1_smartconnect_0_0/design_1_smartconnect_0_0_sim_netlist.v" \

vlog -work xlslice_v1_0_2  -v2k5 "+incdir+../../../bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/1ddd/hdl/verilog" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/b2d0/hdl/verilog" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+/opt/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/f044/hdl/xlslice_v1_0_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/1ddd/hdl/verilog" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/b2d0/hdl/verilog" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+/opt/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_xlslice_0_0/sim/design_1_xlslice_0_0.v" \

vlog -work v_demosaic_v1_0_5  -v2k5 "+incdir+../../../bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/1ddd/hdl/verilog" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/b2d0/hdl/verilog" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+/opt/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/hdl/v_demosaic_v1_0_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/1ddd/hdl/verilog" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/b2d0/hdl/verilog" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+/opt/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_v_demosaic_0_0/sim/design_1_v_demosaic_0_0.v" \
"../../../bd/design_1/ip/design_1_xlslice_1_0/sim/design_1_xlslice_1_0.v" \

vlog -work v_vid_in_axi4s_v4_0_9  -v2k5 "+incdir+../../../bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/1ddd/hdl/verilog" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/b2d0/hdl/verilog" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+/opt/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/b2aa/hdl/v_vid_in_axi4s_v4_0_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/1ddd/hdl/verilog" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/b2d0/hdl/verilog" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+/opt/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_v_vid_in_axi4s_0_0/sim/design_1_v_vid_in_axi4s_0_0.v" \

vlog -work xlconstant_v1_1_6  -v2k5 "+incdir+../../../bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/1ddd/hdl/verilog" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/b2d0/hdl/verilog" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+/opt/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/66e7/hdl/xlconstant_v1_1_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/1ddd/hdl/verilog" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ipshared/b2d0/hdl/verilog" "+incdir+../../../../smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+/opt/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
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

vlog -work xil_defaultlib \
"glbl.v"

