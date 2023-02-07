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

-- DATE "11/22/2022 19:21:25"

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

ENTITY 	GateDemo IS
    PORT (
	outPort : OUT std_logic;
	inPort0 : IN std_logic;
	inPort1 : IN std_logic
	);
END GateDemo;

ARCHITECTURE structure OF GateDemo IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_outPort : std_logic;
SIGNAL ww_inPort0 : std_logic;
SIGNAL ww_inPort1 : std_logic;
SIGNAL \outPort~output_o\ : std_logic;
SIGNAL \inPort0~input_o\ : std_logic;
SIGNAL \inPort1~input_o\ : std_logic;
SIGNAL \AND2_1~combout\ : std_logic;

BEGIN

outPort <= ww_outPort;
ww_inPort0 <= inPort0;
ww_inPort1 <= inPort1;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;

\outPort~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \AND2_1~combout\,
	devoe => ww_devoe,
	o => \outPort~output_o\);

\inPort0~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_inPort0,
	o => \inPort0~input_o\);

\inPort1~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_inPort1,
	o => \inPort1~input_o\);

AND2_1 : cycloneive_lcell_comb
-- Equation(s):
-- \AND2_1~combout\ = (\inPort0~input_o\ & \inPort1~input_o\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000100010001000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inPort0~input_o\,
	datab => \inPort1~input_o\,
	combout => \AND2_1~combout\);

ww_outPort <= \outPort~output_o\;
END structure;


