# 
# Synthesis run script generated by Vivado
# 

set TIME_start [clock seconds] 
proc create_report { reportName command } {
  set status "."
  append status $reportName ".fail"
  if { [file exists $status] } {
    eval file delete [glob $status]
  }
  send_msg_id runtcl-4 info "Executing : $command"
  set retval [eval catch { $command } msg]
  if { $retval != 0 } {
    set fp [open $status w]
    close $fp
    send_msg_id runtcl-5 warning "$msg"
  }
}
set_param chipscope.maxJobs 2
create_project -in_memory -part xc7z010clg400-1

set_param project.singleFileAddWarning.threshold 0
set_param project.compositeFile.enableAutoGeneration 0
set_param synth.vivado.isSynthRun true
set_msg_config -source 4 -id {IP_Flow 19-2162} -severity warning -new_severity info
set_property webtalk.parent_dir /home/user/project/smartnav-vivado.cache/wt [current_project]
set_property parent.project_path /home/user/project/smartnav-vivado.xpr [current_project]
set_property XPM_LIBRARIES {XPM_CDC XPM_FIFO XPM_MEMORY} [current_project]
set_property default_lib xil_defaultlib [current_project]
set_property target_language Verilog [current_project]
set_property ip_repo_paths Tesis/Petalinux_Projects/ov7670/ov7670.srcs [current_project]
update_ip_catalog
set_property ip_output_repo /home/user/project/smartnav-vivado.cache/ip [current_project]
set_property ip_cache_permissions {read write} [current_project]
add_files /home/user/project/smartnav-vivado.sdk/led_blinky/Release/led_blinky.elf
add_files /home/user/project/smartnav-vivado.sdk/encoder/Debug/encoder.elf
set_property SCOPED_TO_REF design_1 [get_files -all /home/user/project/smartnav-vivado.sdk/encoder/Debug/encoder.elf]
set_property SCOPED_TO_CELLS microblaze_0 [get_files -all /home/user/project/smartnav-vivado.sdk/encoder/Debug/encoder.elf]
read_verilog /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/hdl/design_1_wrapper.v
add_files /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/design_1.bd
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0_1/design_1_processing_system7_0_0.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_rst_ps7_0_50M_0_1/design_1_rst_ps7_0_50M_0_board.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_rst_ps7_0_50M_0_1/design_1_rst_ps7_0_50M_0.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_axi_timer_0_0/design_1_axi_timer_0_0.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_axi_timer_0_0/design_1_axi_timer_0_0_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_axi_gpio_4_0/design_1_axi_gpio_4_0_board.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_axi_gpio_4_0/design_1_axi_gpio_4_0_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_axi_gpio_4_0/design_1_axi_gpio_4_0.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_axi_timer_1_0/design_1_axi_timer_1_0.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_axi_timer_1_0/design_1_axi_timer_1_0_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_v_frmbuf_wr_0_0/design_1_v_frmbuf_wr_0_0.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_smartconnect_0_0/ooc.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_smartconnect_0_0/bd_0/ip/ip_1/bd_48ac_psr_aclk_0_board.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_smartconnect_0_0/bd_0/ip/ip_1/bd_48ac_psr_aclk_0.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_smartconnect_0_0/bd_0/ip/ip_5/bd_48ac_s00a2s_0_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_smartconnect_0_0/bd_0/ip/ip_6/bd_48ac_sarn_0_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_smartconnect_0_0/bd_0/ip/ip_7/bd_48ac_srn_0_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_smartconnect_0_0/bd_0/ip/ip_8/bd_48ac_sawn_0_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_smartconnect_0_0/bd_0/ip/ip_9/bd_48ac_swn_0_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_smartconnect_0_0/bd_0/ip/ip_10/bd_48ac_sbn_0_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_smartconnect_0_0/bd_0/ip/ip_11/bd_48ac_m00s2a_0_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_v_demosaic_0_0/design_1_v_demosaic_0_0.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_v_vid_in_axi4s_0_0/design_1_v_vid_in_axi4s_0_0_clocks.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_v_vid_in_axi4s_0_0/design_1_v_vid_in_axi4s_0_0_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_axi_timer_1_1/design_1_axi_timer_1_1.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_axi_timer_1_1/design_1_axi_timer_1_1_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_axi_timer_1_2/design_1_axi_timer_1_2.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_axi_timer_1_2/design_1_axi_timer_1_2_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_microblaze_0_0/design_1_microblaze_0_0.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_microblaze_0_0/design_1_microblaze_0_0_ooc_debug.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_dlmb_v10_0/design_1_dlmb_v10_0.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_ilmb_v10_0/design_1_ilmb_v10_0.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_lmb_bram_0/design_1_lmb_bram_0_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_microblaze_0_axi_intc_0/design_1_microblaze_0_axi_intc_0.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_microblaze_0_axi_intc_0/design_1_microblaze_0_axi_intc_0_clocks.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_microblaze_0_axi_intc_0/design_1_microblaze_0_axi_intc_0_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_mdm_1_0/design_1_mdm_1_0.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_mdm_1_0/design_1_mdm_1_0_ooc_trace.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_mailbox_0_1/design_1_mailbox_0_1.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_mailbox_0_1/design_1_mailbox_0_1_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_axi_gpio_0_0/design_1_axi_gpio_0_0_board.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_axi_gpio_0_0/design_1_axi_gpio_0_0_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_axi_gpio_0_0/design_1_axi_gpio_0_0.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_axi_gpio_0_1/design_1_axi_gpio_0_1_board.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_axi_gpio_0_1/design_1_axi_gpio_0_1_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_axi_gpio_0_1/design_1_axi_gpio_0_1.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_axi_gpio_2_0/design_1_axi_gpio_2_0_board.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_axi_gpio_2_0/design_1_axi_gpio_2_0_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_axi_gpio_2_0/design_1_axi_gpio_2_0.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_auto_pc_0/design_1_auto_pc_0_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/design_1_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/user/project/smartnav-vivado.srcs/sources_1/bd/design_1/ip/design_1_microblaze_0_0/data/mb_bootloop_le.elf]

# Mark all dcp files as not used in implementation to prevent them from being
# stitched into the results of this synthesis run. Any black boxes in the
# design are intentionally left as such for best results. Dcp files will be
# stitched into the design at a later time, either when this synthesis run is
# opened, or when it is stitched into a dependent implementation run.
foreach dcp [get_files -quiet -all -filter file_type=="Design\ Checkpoint"] {
  set_property used_in_implementation false $dcp
}
read_xdc /home/user/project/smartnav-vivado.srcs/constrs_1/new/board.xdc
set_property used_in_implementation false [get_files /home/user/project/smartnav-vivado.srcs/constrs_1/new/board.xdc]

read_xdc dont_touch.xdc
set_property used_in_implementation false [get_files dont_touch.xdc]
set_param ips.enableIPCacheLiteLoad 1
close [open __synthesis_is_running__ w]

synth_design -top design_1_wrapper -part xc7z010clg400-1


# disable binary constraint mode for synth run checkpoints
set_param constraints.enableBinaryConstraints false
write_checkpoint -force -noxdef design_1_wrapper.dcp
file delete __synthesis_is_running__
close [open __synthesis_is_complete__ w]
