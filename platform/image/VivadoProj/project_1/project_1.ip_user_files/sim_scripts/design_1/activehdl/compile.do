vlib work
vlib activehdl

vlib activehdl/xilinx_vip
vlib activehdl/xil_defaultlib
vlib activehdl/xpm
vlib activehdl/xlconcat_v2_1_3

vmap xilinx_vip activehdl/xilinx_vip
vmap xil_defaultlib activehdl/xil_defaultlib
vmap xpm activehdl/xpm
vmap xlconcat_v2_1_3 activehdl/xlconcat_v2_1_3

vlog -work xilinx_vip  -sv2k12 "+incdir+/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/axi4stream_vip_axi4streampc.sv" \
"/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/axi_vip_axi4pc.sv" \
"/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/xil_common_vip_pkg.sv" \
"/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/axi4stream_vip_pkg.sv" \
"/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/axi_vip_pkg.sv" \
"/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/axi4stream_vip_if.sv" \
"/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/axi_vip_if.sv" \
"/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/clk_vip_if.sv" \
"/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/rst_vip_if.sv" \

vlog -work xil_defaultlib  -sv2k12 "+incdir+../../../../ov7670.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../ov7670.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../ov7670.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1" "+incdir+../../../../ov7670.srcs/sources_1/bd/design_1/ipshared/ec9e/hdl" "+incdir+../../../../ov7670.srcs/sources_1/bd/design_1/ipshared/c923" "+incdir+/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"/tools/Xilinx/Vivado/2019.1/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
"/tools/Xilinx/Vivado/2019.1/data/ip/xpm/xpm_fifo/hdl/xpm_fifo.sv" \
"/tools/Xilinx/Vivado/2019.1/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \

vcom -work xpm -93 \
"/tools/Xilinx/Vivado/2019.1/data/ip/xpm/xpm_VCOMP.vhd" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../ov7670.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../ov7670.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../ov7670.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1" "+incdir+../../../../ov7670.srcs/sources_1/bd/design_1/ipshared/ec9e/hdl" "+incdir+../../../../ov7670.srcs/sources_1/bd/design_1/ipshared/c923" "+incdir+/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_processing_system7_0_0_1/design_1_processing_system7_0_0_sim_netlist.v" \
"../../../bd/design_1/ip/design_1_axi_vdma_0_0/design_1_axi_vdma_0_0_sim_netlist.v" \
"../../../bd/design_1/ip/design_1_xbar_0_1/design_1_xbar_0_sim_netlist.v" \
"../../../bd/design_1/ip/design_1_rst_ps7_0_50M_0_1/design_1_rst_ps7_0_50M_0_sim_netlist.v" \
"../../../bd/design_1/ip/design_1_clk_wiz_0_0/design_1_clk_wiz_0_0_sim_netlist.v" \
"../../../bd/design_1/ip/design_1_ov7670_axi_stream_ca_0_0/design_1_ov7670_axi_stream_ca_0_0_sim_netlist.v" \
"../../../bd/design_1/ip/design_1_axi_timer_0_0/design_1_axi_timer_0_0_sim_netlist.v" \
"../../../bd/design_1/ip/design_1_axi_gpio_0_0_1/design_1_axi_gpio_0_0_sim_netlist.v" \
"../../../bd/design_1/ip/design_1_axi_gpio_1_0_1/design_1_axi_gpio_1_0_sim_netlist.v" \

vlog -work xlconcat_v2_1_3  -v2k5 "+incdir+../../../../ov7670.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../ov7670.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../ov7670.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1" "+incdir+../../../../ov7670.srcs/sources_1/bd/design_1/ipshared/ec9e/hdl" "+incdir+../../../../ov7670.srcs/sources_1/bd/design_1/ipshared/c923" "+incdir+/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../../ov7670.srcs/sources_1/bd/design_1/ipshared/442e/hdl/xlconcat_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../ov7670.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../ov7670.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../ov7670.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1" "+incdir+../../../../ov7670.srcs/sources_1/bd/design_1/ipshared/ec9e/hdl" "+incdir+../../../../ov7670.srcs/sources_1/bd/design_1/ipshared/c923" "+incdir+/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_xlconcat_0_0/sim/design_1_xlconcat_0_0.v" \
"../../../bd/design_1/ip/design_1_axi_gpio_2_0/design_1_axi_gpio_2_0_sim_netlist.v" \
"../../../bd/design_1/ip/design_1_axi_gpio_2_1/design_1_axi_gpio_2_1_sim_netlist.v" \
"../../../bd/design_1/ip/design_1_axi_gpio_4_0/design_1_axi_gpio_4_0_sim_netlist.v" \
"../../../bd/design_1/ip/design_1_axi_gpio_5_0/design_1_axi_gpio_5_0_sim_netlist.v" \
"../../../bd/design_1/ip/design_1_auto_pc_0_1/design_1_auto_pc_0_sim_netlist.v" \
"../../../bd/design_1/ip/design_1_auto_us_0/design_1_auto_us_0_sim_netlist.v" \
"../../../bd/design_1/ip/design_1_auto_pc_1_1/design_1_auto_pc_1_sim_netlist.v" \
"../../../bd/design_1/sim/design_1.v" \

vlog -work xil_defaultlib \
"glbl.v"

