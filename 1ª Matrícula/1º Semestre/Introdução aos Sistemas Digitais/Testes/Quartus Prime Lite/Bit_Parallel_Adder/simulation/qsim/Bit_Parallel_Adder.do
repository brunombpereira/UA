onerror {exit -code 1}
vlib work
vlog -work work Bit_Parallel_Adder.vo
vlog -work work Bit_Parallel_Adder.vwf.vt
vsim -c -t 1ps -L cycloneive_ver -L altera_ver -L altera_mf_ver -L 220model_ver -L sgate_ver -L altera_lnsim_ver work.Bit_Parallel_Adder_vlg_vec_tst
vcd file -direction Bit_Parallel_Adder.msim.vcd
vcd add -internal Bit_Parallel_Adder_vlg_vec_tst/*
vcd add -internal Bit_Parallel_Adder_vlg_vec_tst/i1/*
proc simTimestamp {} {
    echo "Simulation time: $::now ps"
    if { [string equal running [runStatus]] } {
        after 2500 simTimestamp
    }
}
after 2500 simTimestamp
run -all
quit -f

