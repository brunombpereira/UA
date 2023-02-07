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

-- DATE "11/30/2022 13:38:14"

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

ENTITY 	Two_Bit_Multiplier IS
    PORT (
	p0 : OUT std_logic;
	A0 : IN std_logic;
	B0 : IN std_logic;
	P1 : OUT std_logic;
	A1 : IN std_logic;
	B0_1 : IN std_logic;
	A0_1 : IN std_logic;
	B1 : IN std_logic;
	P2 : OUT std_logic;
	A1_1 : IN std_logic;
	B1_1 : IN std_logic;
	P3 : OUT std_logic
	);
END Two_Bit_Multiplier;

ARCHITECTURE structure OF Two_Bit_Multiplier IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_p0 : std_logic;
SIGNAL ww_A0 : std_logic;
SIGNAL ww_B0 : std_logic;
SIGNAL ww_P1 : std_logic;
SIGNAL ww_A1 : std_logic;
SIGNAL ww_B0_1 : std_logic;
SIGNAL ww_A0_1 : std_logic;
SIGNAL ww_B1 : std_logic;
SIGNAL ww_P2 : std_logic;
SIGNAL ww_A1_1 : std_logic;
SIGNAL ww_B1_1 : std_logic;
SIGNAL ww_P3 : std_logic;
SIGNAL \p0~output_o\ : std_logic;
SIGNAL \P1~output_o\ : std_logic;
SIGNAL \P2~output_o\ : std_logic;
SIGNAL \P3~output_o\ : std_logic;
SIGNAL \A0~input_o\ : std_logic;
SIGNAL \B0~input_o\ : std_logic;
SIGNAL \AND2_1~combout\ : std_logic;
SIGNAL \A1~input_o\ : std_logic;
SIGNAL \A0_1~input_o\ : std_logic;
SIGNAL \B1~input_o\ : std_logic;
SIGNAL \B0_1~input_o\ : std_logic;
SIGNAL \XOR1~combout\ : std_logic;
SIGNAL \AND2_5~combout\ : std_logic;
SIGNAL \A1_1~input_o\ : std_logic;
SIGNAL \B1_1~input_o\ : std_logic;
SIGNAL \XOR2~combout\ : std_logic;
SIGNAL \AND2_6~combout\ : std_logic;

BEGIN

p0 <= ww_p0;
ww_A0 <= A0;
ww_B0 <= B0;
P1 <= ww_P1;
ww_A1 <= A1;
ww_B0_1 <= B0_1;
ww_A0_1 <= A0_1;
ww_B1 <= B1;
P2 <= ww_P2;
ww_A1_1 <= A1_1;
ww_B1_1 <= B1_1;
P3 <= ww_P3;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;

\p0~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \AND2_1~combout\,
	devoe => ww_devoe,
	o => \p0~output_o\);

\P1~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \XOR1~combout\,
	devoe => ww_devoe,
	o => \P1~output_o\);

\P2~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \XOR2~combout\,
	devoe => ww_devoe,
	o => \P2~output_o\);

\P3~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \AND2_6~combout\,
	devoe => ww_devoe,
	o => \P3~output_o\);

\A0~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_A0,
	o => \A0~input_o\);

\B0~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_B0,
	o => \B0~input_o\);

AND2_1 : cycloneive_lcell_comb
-- Equation(s):
-- \AND2_1~combout\ = (\A0~input_o\ & \B0~input_o\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000100010001000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \A0~input_o\,
	datab => \B0~input_o\,
	combout => \AND2_1~combout\);

\A1~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_A1,
	o => \A1~input_o\);

\A0_1~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_A0_1,
	o => \A0_1~input_o\);

\B1~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_B1,
	o => \B1~input_o\);

\B0_1~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_B0_1,
	o => \B0_1~input_o\);

XOR1 : cycloneive_lcell_comb
-- Equation(s):
-- \XOR1~combout\ = (\A1~input_o\ & (\B0_1~input_o\ $ (((\A0_1~input_o\ & \B1~input_o\))))) # (!\A1~input_o\ & (\A0_1~input_o\ & (\B1~input_o\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0110101011000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \A1~input_o\,
	datab => \A0_1~input_o\,
	datac => \B1~input_o\,
	datad => \B0_1~input_o\,
	combout => \XOR1~combout\);

AND2_5 : cycloneive_lcell_comb
-- Equation(s):
-- \AND2_5~combout\ = (\A1~input_o\ & (\B0_1~input_o\ & (\A0_1~input_o\ & \B1~input_o\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \A1~input_o\,
	datab => \B0_1~input_o\,
	datac => \A0_1~input_o\,
	datad => \B1~input_o\,
	combout => \AND2_5~combout\);

\A1_1~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_A1_1,
	o => \A1_1~input_o\);

\B1_1~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_B1_1,
	o => \B1_1~input_o\);

XOR2 : cycloneive_lcell_comb
-- Equation(s):
-- \XOR2~combout\ = \AND2_5~combout\ $ (((\A1_1~input_o\ & \B1_1~input_o\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110011001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \AND2_5~combout\,
	datac => \A1_1~input_o\,
	datad => \B1_1~input_o\,
	combout => \XOR2~combout\);

AND2_6 : cycloneive_lcell_comb
-- Equation(s):
-- \AND2_6~combout\ = (\AND2_5~combout\ & (\A1_1~input_o\ & \B1_1~input_o\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000010000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \AND2_5~combout\,
	datab => \A1_1~input_o\,
	datac => \B1_1~input_o\,
	combout => \AND2_6~combout\);

ww_p0 <= \p0~output_o\;

ww_P1 <= \P1~output_o\;

ww_P2 <= \P2~output_o\;

ww_P3 <= \P3~output_o\;
END structure;


