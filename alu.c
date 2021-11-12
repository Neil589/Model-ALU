// PID: 730363127 
// I pledge the COMP 211 honor code.

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "alu.h"

// ----------------------------------------
// Simulate add and subtract arithmetic digital logic circuit
// 
// ----------------------------------------
void arithmetic_fun_exe(arithmetic* circuit){
	circuit->Y = circuit->Sub == '0' ? circuit->A + circuit->B : circuit->A - circuit->B;
}

int arithmetic_fun_cfg(arithmetic* circuit){
	if(circuit->Sub != '0' && circuit->Sub != '1'){
		return CONFIG_ERROR;
	}else{
		return OK;
	}
}

// ----------------------------------------
// Simulate shifting digital logic circuit
// 
// ----------------------------------------
void shift_fun_exe(shift* circuit){
	circuit->Y = strcmp(circuit->Bool, "00") == 0 ? circuit->B << circuit->A : circuit->B >> circuit->A;
}

int shift_fun_cfg(shift* circuit){
	if(strcmp(circuit->Bool, "00") != 0 && strcmp(circuit->Bool, "01") != 0 && strcmp(circuit->Bool, "10") != 0  && strcmp(circuit->Bool, "11") != 0){
		return CONFIG_ERROR;
	}else{
		return OK;
	}
}

// ----------------------------------------
// Simulate boolean logic digital logic circuit
// 
// ----------------------------------------
void logic_fun_exe(logic* circuit){
	if(circuit->Bool[0] == '0'){
		if(circuit->Bool[1] == '0'){
			circuit->Y = circuit->A & circuit->B;
		}else{
			circuit->Y = circuit->A | circuit->B;
		}
	}else{
		if(circuit->Bool[1] == '0'){
			circuit->Y = circuit->A ^ circuit->B;
		}else{
			circuit->Y = ~(circuit->A | circuit->B);
		}
	}
}

int logic_fun_cfg(logic* circuit){
	if(strcmp(circuit->Bool, "00") != 0 && strcmp(circuit->Bool, "01") != 0 && strcmp(circuit->Bool, "10") != 0  && strcmp(circuit->Bool, "11") != 0){
		return CONFIG_ERROR;
	}else{
		return OK;
	}
}

// ----------------------------------------
// Simulate multiplexor (MUX) digital logic circuit
// 
// ----------------------------------------
void mux_fun_exe(mux* circuit){
	circuit->Y = circuit->Selector == '0' ? circuit->A : circuit->B;
}

int mux_fun_cfg(mux* circuit){
	if(circuit->Selector != '0' && circuit->Selector != '1'){
		return CONFIG_ERROR;
	}else{
		return OK;
	}
}

// ----------------------------------------
// Initialize the simulated MUX, shift, logic, and arithmetic
// hardware components.
//
// args:
//			None
//
// return:
//			None
// ----------------------------------------
void initialize_alu() {
	math_mux = (mux*)malloc(sizeof(mux));
	shft_mux = (mux*)malloc(sizeof(mux));
	shift_circuit = (shift*)malloc(sizeof(shift));
	logic_circuit = (logic*)malloc(sizeof(logic));
	arithmetic_circuit = (arithmetic*)malloc(sizeof(arithmetic));

	math_mux->A = 0;
	math_mux->B = 0;
	math_mux->Y = 0;
	math_mux->Selector = '0';

	shft_mux->A = 0;
	shft_mux->B = 0;
	shft_mux->Y = 0;
	shft_mux->Selector = '0';

	shift_circuit->A = 0;
	shift_circuit->B = 0;
	shift_circuit->Y = 0;
	shift_circuit->Bool = (char*)malloc(sizeof(char) * 3);
	strcpy(shift_circuit->Bool, "00");

	logic_circuit->A = 0;
	logic_circuit->B = 0;
	logic_circuit->Y = 0;
	logic_circuit->Bool = (char*)malloc(sizeof(char) * 3);
	strcpy(logic_circuit->Bool, "00");

	arithmetic_circuit->A = 0;
	arithmetic_circuit->B = 0;
	arithmetic_circuit->Y = 0;
	arithmetic_circuit->Sub = '0';
} // end initialize_alu() function

// ----------------------------------------
// Configure ALU using ALUFN bits
// In our simulator a configuration bit is represented by 
// an 8-bit ASCII character value (per the 5-bit ALUFN Table)
//
// args:
//			Sub = add or subtract circuit configuration bits
//			Bool = shifter and boolean circult configuration bits
//			Shft = MUX selector bit
//			Math = MUX selector bit
//
// return:
//			CONFIG_ERROR for an unsupported configuration value
//        	PASS when all configuration values are correct
// ----------------------------------------
int configure_alu(char Sub, char* Bool, char Shft, char Math){
	arithmetic_circuit->Sub = Sub;
	strcpy(shift_circuit->Bool, Bool);
	strcpy(logic_circuit->Bool, Bool);
	shft_mux->Selector = Shft;
	math_mux->Selector = Math;
	return (arithmetic_fun_cfg(arithmetic_circuit) == OK 
			&& shift_fun_cfg(shift_circuit) == OK
			&& logic_fun_cfg(logic_circuit) == OK
			&& mux_fun_cfg(shft_mux) == OK
			&& mux_fun_cfg(math_mux) == OK) 
		? OK : CONFIG_ERROR;
} // end configure_alu() function

// ----------------------------------------
// Run ALU
//
// args:
//			A = signed 2's complement 32 bit integer value
//			B = signed 2's complement 32 bit integer value
//
// return:
//			Result = signed 2's complement 32 bit integer value
// ----------------------------------------
int run_alu(int A, int B){
	// Set
	arithmetic_circuit->A = shift_circuit->A = logic_circuit->A = A;
	arithmetic_circuit->B = shift_circuit->B = logic_circuit->B = B;
	// Clock
	arithmetic_fun_exe(arithmetic_circuit);
	shift_fun_exe(shift_circuit);
	logic_fun_exe(logic_circuit);
	// Set
	shft_mux->A = logic_circuit->Y;
	shft_mux->B = shift_circuit->Y;
	// Clock
	mux_fun_exe(shft_mux);
	// Set
	math_mux->A = shft_mux->Y;
	math_mux->B = arithmetic_circuit->Y;
	// Clock
	mux_fun_exe(math_mux);
	return math_mux->Y;
} // end run_alu() function

