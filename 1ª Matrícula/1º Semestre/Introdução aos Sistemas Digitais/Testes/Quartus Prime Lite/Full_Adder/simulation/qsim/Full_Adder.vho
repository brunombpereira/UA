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

-- VENDOR "Altera"
-- PROGRAM "Quartus Prime"
-- VERSION "Version 20.1.1 Build 720 11/11/2020 SJ Lite Edition"

-- DATE "11/28/2022 13:54:13"

-- 
-- Device: Altera EP4CE6E22C6 Package TQFP144
-- 

-- 
-- This VHDL file should be used for ModelSim-Altera (VHDL) only
-- 

LIBRARY CYCLONEIVE;
LIBRARY IEEE;
USE CYCLONEIVE.CYCLONEIVE_COMPONENTS.ALL;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY 	Full_Adder IS
    PORT (
	Sum : OUT std_logic;
	A : IN std_logic;
	B : IN std_logic;
	Ci : IN std_logic;
	Carry : OUT std_logic
	);
END Full_Adder;

ARCHITECTURE structure OF Full_Adder IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_Sum : std_logic;
SIGNAL ww_A : std_logic;
SIGNAL ww_B : std_logic;
SIGNAL ww_Ci : std_logic;
SIGNAL ww_Carry : std_logic;
SIGNAL \Sum~output_o\ : std_logic;
SIGNAL \Carry~output_o\ : std_logic;
SIGNAL \A~input_o\ : std_logic;
SIGNAL \B~input_o\ : std_logic;
SIGNAL \Ci~input_o\ : std_logic;
SIGNAL \XOR2~0_combout\ : std_logic;
SIGNAL \OR2_2~0_combout\ : std_logic;

BEGIN

Sum <= ww_Sum;
ww_A <= A;
ww_B <= B;
ww_Ci <= Ci;
Carry <= ww_Carry;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;

\Sum~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \XOR2~0_combout\,
	devoe => ww_devoe,
	o => \Sum~output_o\);

\Carry~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \OR2_2~0_combout\,
	devoe => ww_devoe,
	o => \Carry~output_o\);

\A~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_A,
	o => \A~input_o\);

\B~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_B,
	o => \B~input_o\);

\Ci~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_Ci,
	o => \Ci~input_o\);

\XOR2~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \XOR2~0_combout\ = \A~input_o\ $ (\B~input_o\ $ (\Ci~input_o\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1001011010010110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \A~input_o\,
	datab => \B~input_o\,
	datac => \Ci~input_o\,
	combout => \XOR2~0_combout\);

\OR2_2~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \OR2_2~0_combout\ = (\A~input_o\ & ((\B~input_o\) # (\Ci~input_o\))) # (!\A~input_o\ & (\B~input_o\ & \Ci~input_o\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1110100011101000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \A~input_o\,
	datab => \B~input_o\,
	datac => \Ci~input_o\,
	combout => \OR2_2~0_combout\);

ww_Sum <= \Sum~output_o\;

ww_Carry <= \Carry~output_o\;
END structure;


