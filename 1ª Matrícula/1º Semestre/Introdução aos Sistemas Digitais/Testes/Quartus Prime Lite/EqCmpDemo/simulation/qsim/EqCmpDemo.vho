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

-- DATE "11/22/2022 20:55:07"

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

ENTITY 	EqCmpDemo IS
    PORT (
	cmpOut : OUT std_logic;
	input1 : IN std_logic_vector(3 DOWNTO 0);
	input0 : IN std_logic_vector(3 DOWNTO 0)
	);
END EqCmpDemo;

ARCHITECTURE structure OF EqCmpDemo IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_cmpOut : std_logic;
SIGNAL ww_input1 : std_logic_vector(3 DOWNTO 0);
SIGNAL ww_input0 : std_logic_vector(3 DOWNTO 0);
SIGNAL \cmpOut~output_o\ : std_logic;
SIGNAL \input1[0]~input_o\ : std_logic;
SIGNAL \input1[1]~input_o\ : std_logic;
SIGNAL \input0[1]~input_o\ : std_logic;
SIGNAL \input0[0]~input_o\ : std_logic;
SIGNAL \and_1~0_combout\ : std_logic;
SIGNAL \input1[2]~input_o\ : std_logic;
SIGNAL \input1[3]~input_o\ : std_logic;
SIGNAL \input0[3]~input_o\ : std_logic;
SIGNAL \input0[2]~input_o\ : std_logic;
SIGNAL \and_1~1_combout\ : std_logic;
SIGNAL \and_1~combout\ : std_logic;

BEGIN

cmpOut <= ww_cmpOut;
ww_input1 <= input1;
ww_input0 <= input0;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;

\cmpOut~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \and_1~combout\,
	devoe => ww_devoe,
	o => \cmpOut~output_o\);

\input1[0]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_input1(0),
	o => \input1[0]~input_o\);

\input1[1]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_input1(1),
	o => \input1[1]~input_o\);

\input0[1]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_input0(1),
	o => \input0[1]~input_o\);

\input0[0]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_input0(0),
	o => \input0[0]~input_o\);

\and_1~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \and_1~0_combout\ = (\input1[0]~input_o\ & (\input0[0]~input_o\ & (\input1[1]~input_o\ $ (!\input0[1]~input_o\)))) # (!\input1[0]~input_o\ & (!\input0[0]~input_o\ & (\input1[1]~input_o\ $ (!\input0[1]~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000001001000001",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \input1[0]~input_o\,
	datab => \input1[1]~input_o\,
	datac => \input0[1]~input_o\,
	datad => \input0[0]~input_o\,
	combout => \and_1~0_combout\);

\input1[2]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_input1(2),
	o => \input1[2]~input_o\);

\input1[3]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_input1(3),
	o => \input1[3]~input_o\);

\input0[3]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_input0(3),
	o => \input0[3]~input_o\);

\input0[2]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_input0(2),
	o => \input0[2]~input_o\);

\and_1~1\ : cycloneive_lcell_comb
-- Equation(s):
-- \and_1~1_combout\ = (\input1[2]~input_o\ & (\input0[2]~input_o\ & (\input1[3]~input_o\ $ (!\input0[3]~input_o\)))) # (!\input1[2]~input_o\ & (!\input0[2]~input_o\ & (\input1[3]~input_o\ $ (!\input0[3]~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000001001000001",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \input1[2]~input_o\,
	datab => \input1[3]~input_o\,
	datac => \input0[3]~input_o\,
	datad => \input0[2]~input_o\,
	combout => \and_1~1_combout\);

and_1 : cycloneive_lcell_comb
-- Equation(s):
-- \and_1~combout\ = (\and_1~0_combout\ & \and_1~1_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000100010001000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \and_1~0_combout\,
	datab => \and_1~1_combout\,
	combout => \and_1~combout\);

ww_cmpOut <= \cmpOut~output_o\;
END structure;


