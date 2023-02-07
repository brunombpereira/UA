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

-- DATE "11/29/2022 21:35:23"

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

ENTITY 	Bit_Parallel_Adder_eight_bits IS
    PORT (
	S0 : OUT std_logic;
	A0 : IN std_logic;
	B0 : IN std_logic;
	C : IN std_logic;
	A1 : IN std_logic;
	B1 : IN std_logic;
	A2 : IN std_logic;
	B2 : IN std_logic;
	A3 : IN std_logic;
	B3 : IN std_logic;
	S1 : OUT std_logic;
	S2 : OUT std_logic;
	S3 : OUT std_logic;
	S4 : OUT std_logic;
	A4 : IN std_logic;
	B4 : IN std_logic;
	A5 : IN std_logic;
	B5 : IN std_logic;
	A6 : IN std_logic;
	B6 : IN std_logic;
	A7 : IN std_logic;
	B7 : IN std_logic;
	S5 : OUT std_logic;
	S6 : OUT std_logic;
	S7 : OUT std_logic;
	C1 : OUT std_logic
	);
END Bit_Parallel_Adder_eight_bits;

ARCHITECTURE structure OF Bit_Parallel_Adder_eight_bits IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_S0 : std_logic;
SIGNAL ww_A0 : std_logic;
SIGNAL ww_B0 : std_logic;
SIGNAL ww_C : std_logic;
SIGNAL ww_A1 : std_logic;
SIGNAL ww_B1 : std_logic;
SIGNAL ww_A2 : std_logic;
SIGNAL ww_B2 : std_logic;
SIGNAL ww_A3 : std_logic;
SIGNAL ww_B3 : std_logic;
SIGNAL ww_S1 : std_logic;
SIGNAL ww_S2 : std_logic;
SIGNAL ww_S3 : std_logic;
SIGNAL ww_S4 : std_logic;
SIGNAL ww_A4 : std_logic;
SIGNAL ww_B4 : std_logic;
SIGNAL ww_A5 : std_logic;
SIGNAL ww_B5 : std_logic;
SIGNAL ww_A6 : std_logic;
SIGNAL ww_B6 : std_logic;
SIGNAL ww_A7 : std_logic;
SIGNAL ww_B7 : std_logic;
SIGNAL ww_S5 : std_logic;
SIGNAL ww_S6 : std_logic;
SIGNAL ww_S7 : std_logic;
SIGNAL ww_C1 : std_logic;
SIGNAL \S0~output_o\ : std_logic;
SIGNAL \S1~output_o\ : std_logic;
SIGNAL \S2~output_o\ : std_logic;
SIGNAL \S3~output_o\ : std_logic;
SIGNAL \S4~output_o\ : std_logic;
SIGNAL \S5~output_o\ : std_logic;
SIGNAL \S6~output_o\ : std_logic;
SIGNAL \S7~output_o\ : std_logic;
SIGNAL \C1~output_o\ : std_logic;
SIGNAL \A0~input_o\ : std_logic;
SIGNAL \B0~input_o\ : std_logic;
SIGNAL \C~input_o\ : std_logic;
SIGNAL \inst|Full_Adder_1|XOR2~0_combout\ : std_logic;
SIGNAL \B1~input_o\ : std_logic;
SIGNAL \A1~input_o\ : std_logic;
SIGNAL \inst|Full_Adder_1|OR2_2~0_combout\ : std_logic;
SIGNAL \inst|Full_Adder_2|XOR2~combout\ : std_logic;
SIGNAL \inst|Full_Adder_2|OR2_2~0_combout\ : std_logic;
SIGNAL \A2~input_o\ : std_logic;
SIGNAL \B2~input_o\ : std_logic;
SIGNAL \inst|Full_Adder_3|XOR2~combout\ : std_logic;
SIGNAL \inst|Full_Adder_3|OR2_2~0_combout\ : std_logic;
SIGNAL \A3~input_o\ : std_logic;
SIGNAL \B3~input_o\ : std_logic;
SIGNAL \inst|Full_Adder_4|XOR2~combout\ : std_logic;
SIGNAL \inst|Full_Adder_4|OR2_2~0_combout\ : std_logic;
SIGNAL \A4~input_o\ : std_logic;
SIGNAL \B4~input_o\ : std_logic;
SIGNAL \inst2|Full_Adder_1|XOR2~combout\ : std_logic;
SIGNAL \inst2|Full_Adder_1|OR2_2~0_combout\ : std_logic;
SIGNAL \A5~input_o\ : std_logic;
SIGNAL \B5~input_o\ : std_logic;
SIGNAL \inst2|Full_Adder_2|XOR2~combout\ : std_logic;
SIGNAL \inst2|Full_Adder_2|OR2_2~0_combout\ : std_logic;
SIGNAL \A6~input_o\ : std_logic;
SIGNAL \B6~input_o\ : std_logic;
SIGNAL \inst2|Full_Adder_3|XOR2~combout\ : std_logic;
SIGNAL \inst2|Full_Adder_3|OR2_2~0_combout\ : std_logic;
SIGNAL \A7~input_o\ : std_logic;
SIGNAL \B7~input_o\ : std_logic;
SIGNAL \inst2|Full_Adder_4|XOR2~combout\ : std_logic;
SIGNAL \inst2|Full_Adder_4|OR2_2~0_combout\ : std_logic;

BEGIN

S0 <= ww_S0;
ww_A0 <= A0;
ww_B0 <= B0;
ww_C <= C;
ww_A1 <= A1;
ww_B1 <= B1;
ww_A2 <= A2;
ww_B2 <= B2;
ww_A3 <= A3;
ww_B3 <= B3;
S1 <= ww_S1;
S2 <= ww_S2;
S3 <= ww_S3;
S4 <= ww_S4;
ww_A4 <= A4;
ww_B4 <= B4;
ww_A5 <= A5;
ww_B5 <= B5;
ww_A6 <= A6;
ww_B6 <= B6;
ww_A7 <= A7;
ww_B7 <= B7;
S5 <= ww_S5;
S6 <= ww_S6;
S7 <= ww_S7;
C1 <= ww_C1;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;

\S0~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst|Full_Adder_1|XOR2~0_combout\,
	devoe => ww_devoe,
	o => \S0~output_o\);

\S1~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst|Full_Adder_2|XOR2~combout\,
	devoe => ww_devoe,
	o => \S1~output_o\);

\S2~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst|Full_Adder_3|XOR2~combout\,
	devoe => ww_devoe,
	o => \S2~output_o\);

\S3~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst|Full_Adder_4|XOR2~combout\,
	devoe => ww_devoe,
	o => \S3~output_o\);

\S4~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst2|Full_Adder_1|XOR2~combout\,
	devoe => ww_devoe,
	o => \S4~output_o\);

\S5~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst2|Full_Adder_2|XOR2~combout\,
	devoe => ww_devoe,
	o => \S5~output_o\);

\S6~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst2|Full_Adder_3|XOR2~combout\,
	devoe => ww_devoe,
	o => \S6~output_o\);

\S7~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst2|Full_Adder_4|XOR2~combout\,
	devoe => ww_devoe,
	o => \S7~output_o\);

\C1~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst2|Full_Adder_4|OR2_2~0_combout\,
	devoe => ww_devoe,
	o => \C1~output_o\);

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

\C~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_C,
	o => \C~input_o\);

\inst|Full_Adder_1|XOR2~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|Full_Adder_1|XOR2~0_combout\ = \A0~input_o\ $ (\B0~input_o\ $ (\C~input_o\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1001011010010110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \A0~input_o\,
	datab => \B0~input_o\,
	datac => \C~input_o\,
	combout => \inst|Full_Adder_1|XOR2~0_combout\);

\B1~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_B1,
	o => \B1~input_o\);

\A1~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_A1,
	o => \A1~input_o\);

\inst|Full_Adder_1|OR2_2~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|Full_Adder_1|OR2_2~0_combout\ = (\A0~input_o\ & ((\B0~input_o\) # (\C~input_o\))) # (!\A0~input_o\ & (\B0~input_o\ & \C~input_o\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1110100011101000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \A0~input_o\,
	datab => \B0~input_o\,
	datac => \C~input_o\,
	combout => \inst|Full_Adder_1|OR2_2~0_combout\);

\inst|Full_Adder_2|XOR2\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|Full_Adder_2|XOR2~combout\ = \B1~input_o\ $ (\A1~input_o\ $ (\inst|Full_Adder_1|OR2_2~0_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1001011010010110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \B1~input_o\,
	datab => \A1~input_o\,
	datac => \inst|Full_Adder_1|OR2_2~0_combout\,
	combout => \inst|Full_Adder_2|XOR2~combout\);

\inst|Full_Adder_2|OR2_2~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|Full_Adder_2|OR2_2~0_combout\ = (\B1~input_o\ & ((\A1~input_o\) # (\inst|Full_Adder_1|OR2_2~0_combout\))) # (!\B1~input_o\ & (\A1~input_o\ & \inst|Full_Adder_1|OR2_2~0_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1110100011101000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \B1~input_o\,
	datab => \A1~input_o\,
	datac => \inst|Full_Adder_1|OR2_2~0_combout\,
	combout => \inst|Full_Adder_2|OR2_2~0_combout\);

\A2~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_A2,
	o => \A2~input_o\);

\B2~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_B2,
	o => \B2~input_o\);

\inst|Full_Adder_3|XOR2\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|Full_Adder_3|XOR2~combout\ = \inst|Full_Adder_2|OR2_2~0_combout\ $ (\A2~input_o\ $ (\B2~input_o\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1001011010010110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst|Full_Adder_2|OR2_2~0_combout\,
	datab => \A2~input_o\,
	datac => \B2~input_o\,
	combout => \inst|Full_Adder_3|XOR2~combout\);

\inst|Full_Adder_3|OR2_2~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|Full_Adder_3|OR2_2~0_combout\ = (\inst|Full_Adder_2|OR2_2~0_combout\ & ((\A2~input_o\) # (\B2~input_o\))) # (!\inst|Full_Adder_2|OR2_2~0_combout\ & (\A2~input_o\ & \B2~input_o\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1110100011101000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst|Full_Adder_2|OR2_2~0_combout\,
	datab => \A2~input_o\,
	datac => \B2~input_o\,
	combout => \inst|Full_Adder_3|OR2_2~0_combout\);

\A3~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_A3,
	o => \A3~input_o\);

\B3~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_B3,
	o => \B3~input_o\);

\inst|Full_Adder_4|XOR2\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|Full_Adder_4|XOR2~combout\ = \inst|Full_Adder_3|OR2_2~0_combout\ $ (\A3~input_o\ $ (\B3~input_o\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1001011010010110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst|Full_Adder_3|OR2_2~0_combout\,
	datab => \A3~input_o\,
	datac => \B3~input_o\,
	combout => \inst|Full_Adder_4|XOR2~combout\);

\inst|Full_Adder_4|OR2_2~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|Full_Adder_4|OR2_2~0_combout\ = (\inst|Full_Adder_3|OR2_2~0_combout\ & ((\A3~input_o\) # (\B3~input_o\))) # (!\inst|Full_Adder_3|OR2_2~0_combout\ & (\A3~input_o\ & \B3~input_o\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1110100011101000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst|Full_Adder_3|OR2_2~0_combout\,
	datab => \A3~input_o\,
	datac => \B3~input_o\,
	combout => \inst|Full_Adder_4|OR2_2~0_combout\);

\A4~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_A4,
	o => \A4~input_o\);

\B4~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_B4,
	o => \B4~input_o\);

\inst2|Full_Adder_1|XOR2\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst2|Full_Adder_1|XOR2~combout\ = \inst|Full_Adder_4|OR2_2~0_combout\ $ (\A4~input_o\ $ (\B4~input_o\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1001011010010110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst|Full_Adder_4|OR2_2~0_combout\,
	datab => \A4~input_o\,
	datac => \B4~input_o\,
	combout => \inst2|Full_Adder_1|XOR2~combout\);

\inst2|Full_Adder_1|OR2_2~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst2|Full_Adder_1|OR2_2~0_combout\ = (\inst|Full_Adder_4|OR2_2~0_combout\ & ((\A4~input_o\) # (\B4~input_o\))) # (!\inst|Full_Adder_4|OR2_2~0_combout\ & (\A4~input_o\ & \B4~input_o\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1110100011101000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst|Full_Adder_4|OR2_2~0_combout\,
	datab => \A4~input_o\,
	datac => \B4~input_o\,
	combout => \inst2|Full_Adder_1|OR2_2~0_combout\);

\A5~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_A5,
	o => \A5~input_o\);

\B5~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_B5,
	o => \B5~input_o\);

\inst2|Full_Adder_2|XOR2\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst2|Full_Adder_2|XOR2~combout\ = \inst2|Full_Adder_1|OR2_2~0_combout\ $ (\A5~input_o\ $ (\B5~input_o\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1001011010010110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst2|Full_Adder_1|OR2_2~0_combout\,
	datab => \A5~input_o\,
	datac => \B5~input_o\,
	combout => \inst2|Full_Adder_2|XOR2~combout\);

\inst2|Full_Adder_2|OR2_2~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst2|Full_Adder_2|OR2_2~0_combout\ = (\inst2|Full_Adder_1|OR2_2~0_combout\ & ((\A5~input_o\) # (\B5~input_o\))) # (!\inst2|Full_Adder_1|OR2_2~0_combout\ & (\A5~input_o\ & \B5~input_o\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1110100011101000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst2|Full_Adder_1|OR2_2~0_combout\,
	datab => \A5~input_o\,
	datac => \B5~input_o\,
	combout => \inst2|Full_Adder_2|OR2_2~0_combout\);

\A6~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_A6,
	o => \A6~input_o\);

\B6~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_B6,
	o => \B6~input_o\);

\inst2|Full_Adder_3|XOR2\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst2|Full_Adder_3|XOR2~combout\ = \inst2|Full_Adder_2|OR2_2~0_combout\ $ (\A6~input_o\ $ (\B6~input_o\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1001011010010110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst2|Full_Adder_2|OR2_2~0_combout\,
	datab => \A6~input_o\,
	datac => \B6~input_o\,
	combout => \inst2|Full_Adder_3|XOR2~combout\);

\inst2|Full_Adder_3|OR2_2~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst2|Full_Adder_3|OR2_2~0_combout\ = (\inst2|Full_Adder_2|OR2_2~0_combout\ & ((\A6~input_o\) # (\B6~input_o\))) # (!\inst2|Full_Adder_2|OR2_2~0_combout\ & (\A6~input_o\ & \B6~input_o\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1110100011101000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst2|Full_Adder_2|OR2_2~0_combout\,
	datab => \A6~input_o\,
	datac => \B6~input_o\,
	combout => \inst2|Full_Adder_3|OR2_2~0_combout\);

\A7~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_A7,
	o => \A7~input_o\);

\B7~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_B7,
	o => \B7~input_o\);

\inst2|Full_Adder_4|XOR2\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst2|Full_Adder_4|XOR2~combout\ = \inst2|Full_Adder_3|OR2_2~0_combout\ $ (\A7~input_o\ $ (\B7~input_o\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1001011010010110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst2|Full_Adder_3|OR2_2~0_combout\,
	datab => \A7~input_o\,
	datac => \B7~input_o\,
	combout => \inst2|Full_Adder_4|XOR2~combout\);

\inst2|Full_Adder_4|OR2_2~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst2|Full_Adder_4|OR2_2~0_combout\ = (\inst2|Full_Adder_3|OR2_2~0_combout\ & ((\A7~input_o\) # (\B7~input_o\))) # (!\inst2|Full_Adder_3|OR2_2~0_combout\ & (\A7~input_o\ & \B7~input_o\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1110100011101000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst2|Full_Adder_3|OR2_2~0_combout\,
	datab => \A7~input_o\,
	datac => \B7~input_o\,
	combout => \inst2|Full_Adder_4|OR2_2~0_combout\);

ww_S0 <= \S0~output_o\;

ww_S1 <= \S1~output_o\;

ww_S2 <= \S2~output_o\;

ww_S3 <= \S3~output_o\;

ww_S4 <= \S4~output_o\;

ww_S5 <= \S5~output_o\;

ww_S6 <= \S6~output_o\;

ww_S7 <= \S7~output_o\;

ww_C1 <= \C1~output_o\;
END structure;


