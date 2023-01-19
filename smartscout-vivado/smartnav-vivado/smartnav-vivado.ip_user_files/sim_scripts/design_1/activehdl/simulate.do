onbreak {quit -force}
onerror {quit -force}

asim -t 1ps +access +r +m+design_1 -L xilinx_vip -L xil_defaultlib -L xpm -L xlconcat_v2_1_3 -L v_frmbuf_wr_v2_1_2 -L xlslice_v1_0_2 -L v_demosaic_v1_0_5 -L v_vid_in_axi4s_v4_0_9 -L xlconstant_v1_1_6 -L xilinx_vip -L unisims_ver -L unimacro_ver -L secureip -O5 xil_defaultlib.design_1 xil_defaultlib.glbl

do {wave.do}

view wave
view structure

do {design_1.udo}

run -all

endsim

quit -force
