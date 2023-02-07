-- Copyright (C) 2020  Intel Corporation. All rights reserved.
-- Your use of Intel Corporation's design tools, logic functions 
-- and other software and tools, and any partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Intel Program License 
-- Subscription Agreement, the Intel Quartus Prime License Agreement,
-- the Intel FPGA IP License Agreement, or other applicable license
-- agreement, including, without limitation, that your use is for
-- the sole purpose of programming logic devices manufactured by
-- Intel and sold by Intel or its authorized distributors.  Please
-- refer to the applicable agreement for further details, at
-- https://fpgasoftware.intel.com/eula.

-- *****************************************************************************
-- This file contains a Vhdl test bench with test vectors .The test vectors     
-- are exported from a vector file in the Quartus Waveform Editor and apply to  
-- the top level entity of the current Quartus project .The user can use this   
-- testbench to simulate his design using a third-party simulation tool .       
-- *****************************************************************************
-- Generated on "01/01/2023 22:33:22"
                                                             
-- Vhdl Test Bench(with test vectors) for design  :          bloco_mef
-- 
-- Simulation tool : 3rd Party
-- 

LIBRARY ieee;                                               
USE ieee.std_logic_1164.all;                                

ENTITY bloco_mef_vhd_vec_tst IS
END bloco_mef_vhd_vec_tst;
ARCHITECTURE bloco_mef_arch OF bloco_mef_vhd_vec_tst IS
-- constants                                                 
-- signals                                                   
SIGNAL clock : STD_LOGIC;
SIGNAL reset_low : STD_LOGIC;
SIGNAL x : STD_LOGIC;
SIGNAL Y : STD_LOGIC_VECTOR(1 DOWNTO 0);
COMPONENT bloco_mef
	PORT (
	clock : IN STD_LOGIC;
	reset_low : IN STD_LOGIC;
	x : IN STD_LOGIC;
	Y : OUT STD_LOGIC_VECTOR(1 DOWNTO 0)
	);
END COMPONENT;
BEGIN
	i1 : bloco_mef
	PORT MAP (
-- list connections between master ports and signals
	clock => clock,
	reset_low => reset_low,
	x => x,
	Y => Y
	);

-- clock
t_prcs_clock: PROCESS
BEGIN
	clock <= '0';
	WAIT FOR 5000 ps;
	clock <= '1';
	WAIT FOR 5000 ps;
	clock <= '0';
	WAIT FOR 5000 ps;
	clock <= '1';
	WAIT FOR 40000 ps;
	clock <= '0';
	WAIT FOR 5000 ps;
	clock <= '1';
	WAIT FOR 10000 ps;
	clock <= '0';
	WAIT FOR 25000 ps;
	clock <= '1';
	WAIT FOR 5000 ps;
	clock <= '0';
	WAIT FOR 10000 ps;
	clock <= '1';
	WAIT FOR 5000 ps;
	clock <= '0';
	WAIT FOR 5000 ps;
	clock <= '1';
	WAIT FOR 10000 ps;
	clock <= '0';
	WAIT FOR 5000 ps;
	clock <= '1';
	WAIT FOR 5000 ps;
	clock <= '0';
	WAIT FOR 5000 ps;
	clock <= '1';
	WAIT FOR 10000 ps;
	clock <= '0';
	WAIT FOR 10000 ps;
	clock <= '1';
	WAIT FOR 10000 ps;
	clock <= '0';
	WAIT FOR 20000 ps;
	clock <= '1';
	WAIT FOR 10000 ps;
	clock <= '0';
	WAIT FOR 5000 ps;
	clock <= '1';
	WAIT FOR 5000 ps;
	clock <= '0';
	WAIT FOR 5000 ps;
	clock <= '1';
	WAIT FOR 5000 ps;
	clock <= '0';
	WAIT FOR 10000 ps;
	clock <= '1';
	WAIT FOR 5000 ps;
	clock <= '0';
	WAIT FOR 5000 ps;
	clock <= '1';
	WAIT FOR 5000 ps;
	clock <= '0';
	WAIT FOR 10000 ps;
	clock <= '1';
	WAIT FOR 10000 ps;
	clock <= '0';
	WAIT FOR 15000 ps;
	clock <= '1';
	WAIT FOR 5000 ps;
	clock <= '0';
	WAIT FOR 5000 ps;
	clock <= '1';
	WAIT FOR 5000 ps;
	clock <= '0';
	WAIT FOR 10000 ps;
	clock <= '1';
	WAIT FOR 5000 ps;
	clock <= '0';
	WAIT FOR 10000 ps;
	clock <= '1';
	WAIT FOR 5000 ps;
	clock <= '0';
	WAIT FOR 40000 ps;
	clock <= '1';
	WAIT FOR 20000 ps;
	clock <= '0';
	WAIT FOR 20000 ps;
	clock <= '1';
	WAIT FOR 5000 ps;
	clock <= '0';
	WAIT FOR 5000 ps;
	clock <= '1';
	WAIT FOR 25000 ps;
	clock <= '0';
	WAIT FOR 10000 ps;
	clock <= '1';
	WAIT FOR 5000 ps;
	clock <= '0';
	WAIT FOR 20000 ps;
	clock <= '1';
	WAIT FOR 10000 ps;
	clock <= '0';
	WAIT FOR 15000 ps;
	clock <= '1';
	WAIT FOR 15000 ps;
	clock <= '0';
	WAIT FOR 15000 ps;
	clock <= '1';
	WAIT FOR 20000 ps;
	clock <= '0';
	WAIT FOR 10000 ps;
	clock <= '1';
	WAIT FOR 5000 ps;
	clock <= '0';
	WAIT FOR 5000 ps;
	clock <= '1';
	WAIT FOR 5000 ps;
	clock <= '0';
	WAIT FOR 5000 ps;
	clock <= '1';
	WAIT FOR 10000 ps;
	clock <= '0';
	WAIT FOR 15000 ps;
	clock <= '1';
	WAIT FOR 10000 ps;
	clock <= '0';
	WAIT FOR 5000 ps;
	clock <= '1';
	WAIT FOR 15000 ps;
	clock <= '0';
	WAIT FOR 5000 ps;
	clock <= '1';
	WAIT FOR 5000 ps;
	clock <= '0';
	WAIT FOR 5000 ps;
	clock <= '1';
	WAIT FOR 5000 ps;
	clock <= '0';
	WAIT FOR 20000 ps;
	clock <= '1';
	WAIT FOR 25000 ps;
	clock <= '0';
	WAIT FOR 5000 ps;
	clock <= '1';
	WAIT FOR 5000 ps;
	clock <= '0';
	WAIT FOR 15000 ps;
	clock <= '1';
	WAIT FOR 35000 ps;
	clock <= '0';
	WAIT FOR 20000 ps;
	clock <= '1';
	WAIT FOR 10000 ps;
	clock <= '0';
	WAIT FOR 5000 ps;
	clock <= '1';
	WAIT FOR 5000 ps;
	clock <= '0';
	WAIT FOR 10000 ps;
	clock <= '1';
	WAIT FOR 15000 ps;
	clock <= '0';
	WAIT FOR 5000 ps;
	clock <= '1';
	WAIT FOR 15000 ps;
	clock <= '0';
	WAIT FOR 5000 ps;
	clock <= '1';
	WAIT FOR 10000 ps;
	clock <= '0';
	WAIT FOR 5000 ps;
	clock <= '1';
	WAIT FOR 5000 ps;
	clock <= '0';
	WAIT FOR 10000 ps;
	clock <= '1';
	WAIT FOR 15000 ps;
	clock <= '0';
	WAIT FOR 5000 ps;
	clock <= '1';
	WAIT FOR 5000 ps;
	clock <= '0';
	WAIT FOR 5000 ps;
	clock <= '1';
	WAIT FOR 10000 ps;
	clock <= '0';
	WAIT FOR 10000 ps;
	clock <= '1';
	WAIT FOR 5000 ps;
	clock <= '0';
	WAIT FOR 5000 ps;
	clock <= '1';
	WAIT FOR 10000 ps;
	clock <= '0';
	WAIT FOR 5000 ps;
	clock <= '1';
	WAIT FOR 5000 ps;
	clock <= '0';
	WAIT FOR 5000 ps;
	clock <= '1';
	WAIT FOR 5000 ps;
	clock <= '0';
	WAIT FOR 5000 ps;
	clock <= '1';
	WAIT FOR 5000 ps;
	clock <= '0';
	WAIT FOR 10000 ps;
	clock <= '1';
WAIT;
END PROCESS t_prcs_clock;

-- reset_low
t_prcs_reset_low: PROCESS
BEGIN
	reset_low <= '1';
	WAIT FOR 40000 ps;
	reset_low <= '0';
	WAIT FOR 60000 ps;
	reset_low <= '1';
WAIT;
END PROCESS t_prcs_reset_low;

-- x
t_prcs_x: PROCESS
BEGIN
	x <= '0';
	WAIT FOR 5000 ps;
	x <= '1';
	WAIT FOR 10000 ps;
	x <= '0';
	WAIT FOR 10000 ps;
	x <= '1';
	WAIT FOR 10000 ps;
	x <= '0';
	WAIT FOR 5000 ps;
	x <= '1';
	WAIT FOR 40000 ps;
	x <= '0';
	WAIT FOR 5000 ps;
	x <= '1';
	WAIT FOR 5000 ps;
	x <= '0';
	WAIT FOR 10000 ps;
	x <= '1';
	WAIT FOR 25000 ps;
	x <= '0';
	WAIT FOR 5000 ps;
	x <= '1';
	WAIT FOR 10000 ps;
	x <= '0';
	WAIT FOR 10000 ps;
	x <= '1';
	WAIT FOR 15000 ps;
	x <= '0';
	WAIT FOR 10000 ps;
	x <= '1';
	WAIT FOR 15000 ps;
	x <= '0';
	WAIT FOR 25000 ps;
	x <= '1';
	WAIT FOR 5000 ps;
	x <= '0';
	WAIT FOR 10000 ps;
	x <= '1';
	WAIT FOR 5000 ps;
	x <= '0';
	WAIT FOR 10000 ps;
	x <= '1';
	WAIT FOR 5000 ps;
	x <= '0';
	WAIT FOR 5000 ps;
	x <= '1';
	WAIT FOR 5000 ps;
	x <= '0';
	WAIT FOR 15000 ps;
	x <= '1';
	WAIT FOR 10000 ps;
	x <= '0';
	WAIT FOR 10000 ps;
	x <= '1';
	WAIT FOR 5000 ps;
	x <= '0';
	WAIT FOR 30000 ps;
	x <= '1';
	WAIT FOR 20000 ps;
	x <= '0';
	WAIT FOR 20000 ps;
	x <= '1';
	WAIT FOR 5000 ps;
	x <= '0';
	WAIT FOR 25000 ps;
	x <= '1';
	WAIT FOR 20000 ps;
	x <= '0';
	WAIT FOR 5000 ps;
	x <= '1';
	WAIT FOR 5000 ps;
	x <= '0';
	WAIT FOR 5000 ps;
	x <= '1';
	WAIT FOR 15000 ps;
	x <= '0';
	WAIT FOR 10000 ps;
	x <= '1';
	WAIT FOR 35000 ps;
	x <= '0';
	WAIT FOR 5000 ps;
	x <= '1';
	WAIT FOR 15000 ps;
	x <= '0';
	WAIT FOR 5000 ps;
	x <= '1';
	WAIT FOR 5000 ps;
	x <= '0';
	WAIT FOR 5000 ps;
	x <= '1';
	WAIT FOR 5000 ps;
	x <= '0';
	WAIT FOR 5000 ps;
	x <= '1';
	WAIT FOR 5000 ps;
	x <= '0';
	WAIT FOR 5000 ps;
	x <= '1';
	WAIT FOR 15000 ps;
	x <= '0';
	WAIT FOR 15000 ps;
	x <= '1';
	WAIT FOR 10000 ps;
	x <= '0';
	WAIT FOR 5000 ps;
	x <= '1';
	WAIT FOR 5000 ps;
	x <= '0';
	WAIT FOR 20000 ps;
	x <= '1';
	WAIT FOR 10000 ps;
	x <= '0';
	WAIT FOR 5000 ps;
	x <= '1';
	WAIT FOR 5000 ps;
	x <= '0';
	WAIT FOR 15000 ps;
	x <= '1';
	WAIT FOR 10000 ps;
	x <= '0';
	WAIT FOR 10000 ps;
	x <= '1';
	WAIT FOR 5000 ps;
	x <= '0';
	WAIT FOR 15000 ps;
	x <= '1';
	WAIT FOR 5000 ps;
	x <= '0';
	WAIT FOR 5000 ps;
	x <= '1';
	WAIT FOR 15000 ps;
	x <= '0';
	WAIT FOR 5000 ps;
	x <= '1';
	WAIT FOR 25000 ps;
	x <= '0';
	WAIT FOR 15000 ps;
	x <= '1';
	WAIT FOR 10000 ps;
	x <= '0';
	WAIT FOR 10000 ps;
	x <= '1';
	WAIT FOR 5000 ps;
	x <= '0';
	WAIT FOR 5000 ps;
	x <= '1';
	WAIT FOR 5000 ps;
	x <= '0';
	WAIT FOR 5000 ps;
	x <= '1';
	WAIT FOR 10000 ps;
	x <= '0';
	WAIT FOR 20000 ps;
	x <= '1';
	WAIT FOR 15000 ps;
	x <= '0';
	WAIT FOR 15000 ps;
	x <= '1';
	WAIT FOR 10000 ps;
	x <= '0';
	WAIT FOR 5000 ps;
	x <= '1';
	WAIT FOR 15000 ps;
	x <= '0';
	WAIT FOR 5000 ps;
	x <= '1';
	WAIT FOR 35000 ps;
	x <= '0';
	WAIT FOR 20000 ps;
	x <= '1';
	WAIT FOR 5000 ps;
	x <= '0';
	WAIT FOR 5000 ps;
	x <= '1';
	WAIT FOR 5000 ps;
	x <= '0';
	WAIT FOR 5000 ps;
	x <= '1';
	WAIT FOR 5000 ps;
	x <= '0';
WAIT;
END PROCESS t_prcs_x;
END bloco_mef_arch;
