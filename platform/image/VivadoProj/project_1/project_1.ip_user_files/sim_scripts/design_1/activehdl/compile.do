vlib work
vlib activehdl

vlib activehdl/xilinx_vip
vlib activehdl/xil_defaultlib
vlib activehdl/xpm
vlib activehdl/xlconcat_v2_1_3
vlib activehdl/v_frmbuf_wr_v2_1_2
vlib activehdl/v_csc_v1_0_13
vlib activehdl/xlslice_v1_0_2
vlib activehdl/v_demosaic_v1_0_5
vlib activehdl/v_vid_in_axi4s_v4_0_9
vlib activehdl/xlconstant_v1_1_6
vlib activehdl/util_vector_logic_v2_0_1

vmap xilinx_vip activehdl/xilinx_vip
vmap xil_defaultlib activehdl/xil_defaultlib
vmap xpm activehdl/xpm
vmap xlconcat_v2_1_3 activehdl/xlconcat_v2_1_3
vmap v_frmbuf_wr_v2_1_2 activehdl/v_frmbuf_wr_v2_1_2
vmap v_csc_v1_0_13 activehdl/v_csc_v1_0_13
vmap xlslice_v1_0_2 activehdl/xlslice_v1_0_2
vmap v_demosaic_v1_0_5 activehdl/v_demosaic_v1_0_5
vmap v_vid_in_axi4s_v4_0_9 activehdl/v_vid_in_axi4s_v4_0_9
vmap xlconstant_v1_1_6 activehdl/xlconstant_v1_1_6
vmap util_vector_logic_v2_0_1 activehdl/util_vector_logic_v2_0_1

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

vlog -work xil_defaultlib  -sv2k12 "+incdir+../../../bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/1ddd/hdl/verilog" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/b2d0/hdl/verilog" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"/tools/Xilinx/Vivado/2019.1/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
"/tools/Xilinx/Vivado/2019.1/data/ip/xpm/xpm_fifo/hdl/xpm_fifo.sv" \
"/tools/Xilinx/Vivado/2019.1/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \

vcom -work xpm -93 \
"/tools/Xilinx/Vivado/2019.1/data/ip/xpm/xpm_VCOMP.vhd" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/1ddd/hdl/verilog" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/b2d0/hdl/verilog" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"/media/kuhiu/5e8324a1-752c-4afa-961c-05d693d0ddc6/SmartNavSys/platform/image/VivadoProj/project_1/project_1.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1/design_1_processing_system7_0_0_sim_netlist.v" \
"../../../bd/design_1/ip/design_1_xbar_0_1/design_1_xbar_0_sim_netlist.v" \
"../../../bd/design_1/ip/design_1_rst_ps7_0_50M_0_1/design_1_rst_ps7_0_50M_0_sim_netlist.v" \
"../../../bd/design_1/ip/design_1_axi_timer_0_0/design_1_axi_timer_0_0_sim_netlist.v" \
"../../../bd/design_1/ip/design_1_axi_gpio_0_0_1/design_1_axi_gpio_0_0_sim_netlist.v" \
"../../../bd/design_1/ip/design_1_axi_gpio_1_0_1/design_1_axi_gpio_1_0_sim_netlist.v" \

vlog -work xlconcat_v2_1_3  -v2k5 "+incdir+../../../bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/1ddd/hdl/verilog" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/b2d0/hdl/verilog" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../../project_1.srcs/sources_1/bd/design_1/ipshared/442e/hdl/xlconcat_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/1ddd/hdl/verilog" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/b2d0/hdl/verilog" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_xlconcat_0_0/sim/design_1_xlconcat_0_0.v" \
"../../../bd/design_1/ip/design_1_axi_gpio_2_0/design_1_axi_gpio_2_0_sim_netlist.v" \
"../../../bd/design_1/ip/design_1_axi_gpio_2_1/design_1_axi_gpio_2_1_sim_netlist.v" \
"../../../bd/design_1/ip/design_1_axi_gpio_4_0/design_1_axi_gpio_4_0_sim_netlist.v" \
"../../../bd/design_1/ip/design_1_axi_gpio_5_0/design_1_axi_gpio_5_0_sim_netlist.v" \
"../../../bd/design_1/ip/design_1_axi_timer_1_0/design_1_axi_timer_1_0_sim_netlist.v" \
"../../../bd/design_1/ip/design_1_axi_gpio_6_0/design_1_axi_gpio_6_0_sim_netlist.v" \

vlog -work v_frmbuf_wr_v2_1_2  -v2k5 "+incdir+../../../bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/1ddd/hdl/verilog" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/b2d0/hdl/verilog" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/hdl/v_frmbuf_wr_v2_1_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/1ddd/hdl/verilog" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/b2d0/hdl/verilog" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_v_frmbuf_wr_0_0/sim/design_1_v_frmbuf_wr_0_0.v" \
"../../../bd/design_1/ip/design_1_smartconnect_0_0/design_1_smartconnect_0_0_sim_netlist.v" \

vlog -work v_csc_v1_0_13  -v2k5 "+incdir+../../../bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/1ddd/hdl/verilog" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/b2d0/hdl/verilog" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/hdl/v_csc_v1_0_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/1ddd/hdl/verilog" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/b2d0/hdl/verilog" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/sim/bd_d92b_csc_0.v" \
"../../../bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/sim/bd_d92b.v" \
"../../../bd/design_1/ip/design_1_v_proc_ss_0_0/sim/design_1_v_proc_ss_0_0.v" \

vlog -work xlslice_v1_0_2  -v2k5 "+incdir+../../../bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/1ddd/hdl/verilog" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/b2d0/hdl/verilog" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../../project_1.srcs/sources_1/bd/design_1/ipshared/f044/hdl/xlslice_v1_0_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/1ddd/hdl/verilog" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/b2d0/hdl/verilog" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_xlslice_0_0/sim/design_1_xlslice_0_0.v" \
"../../../bd/design_1/ip/design_1_xlslice_0_1/sim/design_1_xlslice_0_1.v" \

vlog -work v_demosaic_v1_0_5  -v2k5 "+incdir+../../../bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/1ddd/hdl/verilog" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/b2d0/hdl/verilog" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/hdl/v_demosaic_v1_0_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/1ddd/hdl/verilog" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/b2d0/hdl/verilog" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_v_demosaic_0_0/sim/design_1_v_demosaic_0_0.v" \
"../../../bd/design_1/ip/design_1_xlslice_1_0/sim/design_1_xlslice_1_0.v" \

vlog -work v_vid_in_axi4s_v4_0_9  -v2k5 "+incdir+../../../bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/1ddd/hdl/verilog" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/b2d0/hdl/verilog" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../../project_1.srcs/sources_1/bd/design_1/ipshared/b2aa/hdl/v_vid_in_axi4s_v4_0_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/1ddd/hdl/verilog" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/b2d0/hdl/verilog" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_v_vid_in_axi4s_0_0/sim/design_1_v_vid_in_axi4s_0_0.v" \

vlog -work xlconstant_v1_1_6  -v2k5 "+incdir+../../../bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/1ddd/hdl/verilog" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/b2d0/hdl/verilog" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../../project_1.srcs/sources_1/bd/design_1/ipshared/66e7/hdl/xlconstant_v1_1_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/1ddd/hdl/verilog" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/b2d0/hdl/verilog" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_xlconstant_0_0/sim/design_1_xlconstant_0_0.v" \
"../../../bd/design_1/ip/design_1_xlconstant_0_1/sim/design_1_xlconstant_0_1.v" \
"../../../bd/design_1/ip/design_1_xlslice_2_0/sim/design_1_xlslice_2_0.v" \

vlog -work util_vector_logic_v2_0_1  -v2k5 "+incdir+../../../bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/1ddd/hdl/verilog" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/b2d0/hdl/verilog" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../../project_1.srcs/sources_1/bd/design_1/ipshared/2137/hdl/util_vector_logic_v2_0_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/src" "+incdir+../../../bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/1ddd/hdl/verilog" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ipshared/b2d0/hdl/verilog" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_proc_ss_0_0/bd_0/ip/ip_0/src" "+incdir+../../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/src" "+incdir+/tools/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_util_vector_logic_0_0/sim/design_1_util_vector_logic_0_0.v" \
"../../../bd/design_1/ip/design_1_util_vector_logic_0_1/sim/design_1_util_vector_logic_0_1.v" \
"../../../bd/design_1/ip/design_1_util_vector_logic_1_0/sim/design_1_util_vector_logic_1_0.v" \
"../../../bd/design_1/ip/design_1_auto_pc_0/design_1_auto_pc_0_sim_netlist.v" \
"../../../bd/design_1/sim/design_1.v" \

vlog -work xil_defaultlib \
"glbl.v"

