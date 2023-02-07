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

-- DATE "12/06/2022 23:46:11"

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

ENTITY 	DecoderDemo IS
    PORT (
	Y0 : OUT std_logic;
	E1 : IN std_logic;
	E0_L : IN std_logic;
	X1 : IN std_logic;
	X0 : IN std_logic;
	Y1 : OUT std_logic;
	Y2 : OUT std_logic;
	Y3 : OUT std_logic
	);
END DecoderDemo;

ARCHITECTURE structure OF DecoderDemo IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_Y0 : std_logic;
SIGNAL ww_E1 : std_logic;
SIGNAL ww_E0_L : std_logic;
SIGNAL ww_X1 : std_logic;
SIGNAL ww_X0 : std_logic;
SIGNAL ww_Y1 : std_logic;
SIGNAL ww_Y2 : std_logic;
SIGNAL ww_Y3 : std_logic;
SIGNAL \Y0~output_o\ : std_logic;
SIGNAL \Y1~output_o\ : std_logic;
SIGNAL \Y2~output_o\ : std_logic;
SIGNAL \Y3~output_o\ : std_logic;
SIGNAL \E1~input_o\ : std_logic;
SIGNAL \X0~input_o\ : std_logic;
SIGNAL \X1~input_o\ : std_logic;
SIGNAL \E0_L~input_o\ : std_logic;
SIGNAL \Dec2_4|AND4_1~combout\ : std_logic;
SIGNAL \Dec2_4|AND4_2~combout\ : std_logic;
SIGNAL \Dec2_4|AND4_3~combout\ : std_logic;
SIGNAL \Dec2_4|AND4_4~combout\ : std_logic;

BEGIN

Y0 <= ww_Y0;
ww_E1 <= E1;
ww_E0_L <= E0_L;
ww_X1 <= X1;
ww_X0 <= X0;
Y1 <= ww_Y1;
Y2 <= ww_Y2;
Y3 <= ww_Y3;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;

\Y0~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \Dec2_4|AND4_1~combout\,
	devoe => ww_devoe,
	o => \Y0~output_o\);

\Y1~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \Dec2_4|AND4_2~combout\,
	devoe => ww_devoe,
	o => \Y1~output_o\);

\Y2~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \Dec2_4|AND4_3~combout\,
	devoe => ww_devoe,
	o => \Y2~output_o\);

\Y3~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \Dec2_4|AND4_4~combout\,
	devoe => ww_devoe,
	o => \Y3~output_o\);

\E1~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_E1,
	o => \E1~input_o\);

\X0~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_X0,
	o => \X0~input_o\);

\X1~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_X1,
	o => \X1~input_o\);

\E0_L~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_E0_L,
	o => \E0_L~input_o\);

\Dec2_4|AND4_1\ : cycloneive_lcell_comb
-- Equation(s):
-- \Dec2_4|AND4_1~combout\ = (\E1~input_o\ & (!\X0~input_o\ & (!\X1~input_o\ & !\E0_L~input_o\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \E1~input_o\,
	datab => \X0~input_o\,
	datac => \X1~input_o\,
	datad => \E0_L~input_o\,
	combout => \Dec2_4|AND4_1~combout\);

\Dec2_4|AND4_2\ : cycloneive_lcell_comb
-- Equation(s):
-- \Dec2_4|AND4_2~combout\ = (\X1~input_o\ & (\E1~input_o\ & (!\X0~input_o\ & !\E0_L~input_o\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000001000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \X1~input_o\,
	datab => \E1~input_o\,
	datac => \X0~input_o\,
	datad => \E0_L~input_o\,
	combout => \Dec2_4|AND4_2~combout\);

\Dec2_4|AND4_3\ : cycloneive_lcell_comb
-- Equation(s):
-- \Dec2_4|AND4_3~combout\ = (\X0~input_o\ & (\E1~input_o\ & (!\X1~input_o\ & !\E0_L~input_o\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000001000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \X0~input_o\,
	datab => \E1~input_o\,
	datac => \X1~input_o\,
	datad => \E0_L~input_o\,
	combout => \Dec2_4|AND4_3~combout\);

\Dec2_4|AND4_4\ : cycloneive_lcell_comb
-- Equation(s):
-- \Dec2_4|AND4_4~combout\ = (\X0~input_o\ & (\X1~input_o\ & (\E1~input_o\ & !\E0_L~input_o\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000010000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \X0~input_o\,
	datab => \X1~input_o\,
	datac => \E1~input_o\,
	datad => \E0_L~input_o\,
	combout => \Dec2_4|AND4_4~combout\);

ww_Y0 <= \Y0~output_o\;

ww_Y1 <= \Y1~output_o\;

ww_Y2 <= \Y2~output_o\;

ww_Y3 <= \Y3~output_o\;
END structure;


