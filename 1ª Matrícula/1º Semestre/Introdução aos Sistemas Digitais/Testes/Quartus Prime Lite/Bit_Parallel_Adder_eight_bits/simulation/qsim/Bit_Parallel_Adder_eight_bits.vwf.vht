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
-- Generated on "11/29/2022 21:35:23"
                                                             
-- Vhdl Test Bench(with test vectors) for design  :          Bit_Parallel_Adder_eight_bits
-- 
-- Simulation tool : 3rd Party
-- 

LIBRARY ieee;                                               
USE ieee.std_logic_1164.all;                                

ENTITY Bit_Parallel_Adder_eight_bits_vhd_vec_tst IS
END Bit_Parallel_Adder_eight_bits_vhd_vec_tst;
ARCHITECTURE Bit_Parallel_Adder_eight_bits_arch OF Bit_Parallel_Adder_eight_bits_vhd_vec_tst IS
-- constants                                                 
-- signals                                                   
SIGNAL A0 : STD_LOGIC;
SIGNAL A1 : STD_LOGIC;
SIGNAL A2 : STD_LOGIC;
SIGNAL A3 : STD_LOGIC;
SIGNAL A4 : STD_LOGIC;
SIGNAL A5 : STD_LOGIC;
SIGNAL A6 : STD_LOGIC;
SIGNAL A7 : STD_LOGIC;
SIGNAL B0 : STD_LOGIC;
SIGNAL B1 : STD_LOGIC;
SIGNAL B2 : STD_LOGIC;
SIGNAL B3 : STD_LOGIC;
SIGNAL B4 : STD_LOGIC;
SIGNAL B5 : STD_LOGIC;
SIGNAL B6 : STD_LOGIC;
SIGNAL B7 : STD_LOGIC;
SIGNAL C : STD_LOGIC;
SIGNAL C1 : STD_LOGIC;
SIGNAL S0 : STD_LOGIC;
SIGNAL S1 : STD_LOGIC;
SIGNAL S2 : STD_LOGIC;
SIGNAL S3 : STD_LOGIC;
SIGNAL S4 : STD_LOGIC;
SIGNAL S5 : STD_LOGIC;
SIGNAL S6 : STD_LOGIC;
SIGNAL S7 : STD_LOGIC;
COMPONENT Bit_Parallel_Adder_eight_bits
	PORT (
	A0 : IN STD_LOGIC;
	A1 : IN STD_LOGIC;
	A2 : IN STD_LOGIC;
	A3 : IN STD_LOGIC;
	A4 : IN STD_LOGIC;
	A5 : IN STD_LOGIC;
	A6 : IN STD_LOGIC;
	A7 : IN STD_LOGIC;
	B0 : IN STD_LOGIC;
	B1 : IN STD_LOGIC;
	B2 : IN STD_LOGIC;
	B3 : IN STD_LOGIC;
	B4 : IN STD_LOGIC;
	B5 : IN STD_LOGIC;
	B6 : IN STD_LOGIC;
	B7 : IN STD_LOGIC;
	C : IN STD_LOGIC;
	C1 : OUT STD_LOGIC;
	S0 : OUT STD_LOGIC;
	S1 : OUT STD_LOGIC;
	S2 : OUT STD_LOGIC;
	S3 : OUT STD_LOGIC;
	S4 : OUT STD_LOGIC;
	S5 : OUT STD_LOGIC;
	S6 : OUT STD_LOGIC;
	S7 : OUT STD_LOGIC
	);
END COMPONENT;
BEGIN
	i1 : Bit_Parallel_Adder_eight_bits
	PORT MAP (
-- list connections between master ports and signals
	A0 => A0,
	A1 => A1,
	A2 => A2,
	A3 => A3,
	A4 => A4,
	A5 => A5,
	A6 => A6,
	A7 => A7,
	B0 => B0,
	B1 => B1,
	B2 => B2,
	B3 => B3,
	B4 => B4,
	B5 => B5,
	B6 => B6,
	B7 => B7,
	C => C,
	C1 => C1,
	S0 => S0,
	S1 => S1,
	S2 => S2,
	S3 => S3,
	S4 => S4,
	S5 => S5,
	S6 => S6,
	S7 => S7
	);

-- A0
t_prcs_A0: PROCESS
BEGIN
	A0 <= '0';
	WAIT FOR 50000 ps;
	A0 <= '1';
	WAIT FOR 90000 ps;
	A0 <= '0';
	WAIT FOR 70000 ps;
	A0 <= '1';
	WAIT FOR 140000 ps;
	A0 <= '0';
WAIT;
END PROCESS t_prcs_A0;

-- A1
t_prcs_A1: PROCESS
BEGIN
	A1 <= '0';
	WAIT FOR 50000 ps;
	A1 <= '1';
	WAIT FOR 90000 ps;
	A1 <= '0';
	WAIT FOR 70000 ps;
	A1 <= '1';
	WAIT FOR 140000 ps;
	A1 <= '0';
	WAIT FOR 100000 ps;
	A1 <= '1';
	WAIT FOR 90000 ps;
	A1 <= '0';
WAIT;
END PROCESS t_prcs_A1;

-- A2
t_prcs_A2: PROCESS
BEGIN
	A2 <= '0';
	WAIT FOR 50000 ps;
	A2 <= '1';
	WAIT FOR 90000 ps;
	A2 <= '0';
	WAIT FOR 70000 ps;
	A2 <= '1';
	WAIT FOR 140000 ps;
	A2 <= '0';
	WAIT FOR 100000 ps;
	A2 <= '1';
	WAIT FOR 90000 ps;
	A2 <= '0';
WAIT;
END PROCESS t_prcs_A2;

-- A3
t_prcs_A3: PROCESS
BEGIN
	A3 <= '0';
	WAIT FOR 50000 ps;
	A3 <= '1';
	WAIT FOR 90000 ps;
	A3 <= '0';
	WAIT FOR 70000 ps;
	A3 <= '1';
	WAIT FOR 140000 ps;
	A3 <= '0';
	WAIT FOR 100000 ps;
	A3 <= '1';
	WAIT FOR 90000 ps;
	A3 <= '0';
WAIT;
END PROCESS t_prcs_A3;

-- A4
t_prcs_A4: PROCESS
BEGIN
	A4 <= '0';
	WAIT FOR 50000 ps;
	A4 <= '1';
	WAIT FOR 90000 ps;
	A4 <= '0';
	WAIT FOR 70000 ps;
	A4 <= '1';
	WAIT FOR 140000 ps;
	A4 <= '0';
	WAIT FOR 100000 ps;
	A4 <= '1';
	WAIT FOR 90000 ps;
	A4 <= '0';
WAIT;
END PROCESS t_prcs_A4;

-- A5
t_prcs_A5: PROCESS
BEGIN
	A5 <= '0';
	WAIT FOR 50000 ps;
	A5 <= '1';
	WAIT FOR 90000 ps;
	A5 <= '0';
	WAIT FOR 70000 ps;
	A5 <= '1';
	WAIT FOR 140000 ps;
	A5 <= '0';
WAIT;
END PROCESS t_prcs_A5;

-- A6
t_prcs_A6: PROCESS
BEGIN
	A6 <= '0';
	WAIT FOR 50000 ps;
	A6 <= '1';
	WAIT FOR 90000 ps;
	A6 <= '0';
	WAIT FOR 70000 ps;
	A6 <= '1';
	WAIT FOR 140000 ps;
	A6 <= '0';
WAIT;
END PROCESS t_prcs_A6;

-- A7
t_prcs_A7: PROCESS
BEGIN
	A7 <= '0';
	WAIT FOR 50000 ps;
	A7 <= '1';
	WAIT FOR 90000 ps;
	A7 <= '0';
	WAIT FOR 70000 ps;
	A7 <= '1';
	WAIT FOR 140000 ps;
	A7 <= '0';
WAIT;
END PROCESS t_prcs_A7;

-- B0
t_prcs_B0: PROCESS
BEGIN
	B0 <= '0';
	WAIT FOR 50000 ps;
	B0 <= '1';
	WAIT FOR 90000 ps;
	B0 <= '0';
	WAIT FOR 70000 ps;
	B0 <= '1';
	WAIT FOR 140000 ps;
	B0 <= '0';
	WAIT FOR 120000 ps;
	B0 <= '1';
	WAIT FOR 80000 ps;
	B0 <= '0';
WAIT;
END PROCESS t_prcs_B0;

-- B1
t_prcs_B1: PROCESS
BEGIN
	B1 <= '0';
	WAIT FOR 50000 ps;
	B1 <= '1';
	WAIT FOR 90000 ps;
	B1 <= '0';
	WAIT FOR 70000 ps;
	B1 <= '1';
	WAIT FOR 140000 ps;
	B1 <= '0';
	WAIT FOR 120000 ps;
	B1 <= '1';
	WAIT FOR 80000 ps;
	B1 <= '0';
WAIT;
END PROCESS t_prcs_B1;

-- B2
t_prcs_B2: PROCESS
BEGIN
	B2 <= '0';
	WAIT FOR 50000 ps;
	B2 <= '1';
	WAIT FOR 90000 ps;
	B2 <= '0';
	WAIT FOR 70000 ps;
	B2 <= '1';
	WAIT FOR 140000 ps;
	B2 <= '0';
	WAIT FOR 120000 ps;
	B2 <= '1';
	WAIT FOR 80000 ps;
	B2 <= '0';
WAIT;
END PROCESS t_prcs_B2;

-- B3
t_prcs_B3: PROCESS
BEGIN
	B3 <= '0';
	WAIT FOR 50000 ps;
	B3 <= '1';
	WAIT FOR 90000 ps;
	B3 <= '0';
	WAIT FOR 330000 ps;
	B3 <= '1';
	WAIT FOR 80000 ps;
	B3 <= '0';
WAIT;
END PROCESS t_prcs_B3;

-- B4
t_prcs_B4: PROCESS
BEGIN
	B4 <= '0';
	WAIT FOR 50000 ps;
	B4 <= '1';
	WAIT FOR 90000 ps;
	B4 <= '0';
	WAIT FOR 330000 ps;
	B4 <= '1';
	WAIT FOR 80000 ps;
	B4 <= '0';
WAIT;
END PROCESS t_prcs_B4;

-- B5
t_prcs_B5: PROCESS
BEGIN
	B5 <= '0';
	WAIT FOR 50000 ps;
	B5 <= '1';
	WAIT FOR 90000 ps;
	B5 <= '0';
	WAIT FOR 330000 ps;
	B5 <= '1';
	WAIT FOR 80000 ps;
	B5 <= '0';
WAIT;
END PROCESS t_prcs_B5;

-- B6
t_prcs_B6: PROCESS
BEGIN
	B6 <= '0';
	WAIT FOR 50000 ps;
	B6 <= '1';
	WAIT FOR 90000 ps;
	B6 <= '0';
WAIT;
END PROCESS t_prcs_B6;

-- B7
t_prcs_B7: PROCESS
BEGIN
	B7 <= '0';
	WAIT FOR 50000 ps;
	B7 <= '1';
	WAIT FOR 90000 ps;
	B7 <= '0';
WAIT;
END PROCESS t_prcs_B7;

-- C
t_prcs_C: PROCESS
BEGIN
	C <= '0';
WAIT;
END PROCESS t_prcs_C;
END Bit_Parallel_Adder_eight_bits_arch;
