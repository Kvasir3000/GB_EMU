#pragma once

enum OPCODE
{
	LD_A_n =     0x3E,
	LD_B_n =     0x06,
	LD_C_n =     0x0E,
	LD_D_n =     0x16,
	LD_E_n =     0x1E,
	LD_H_n =     0x26,
	LD_L_n =     0x2E,
	LD_A_A =     0x7F,
	LD_A_B =     0x78,
	LD_A_C =     0x79,
	LD_A_C_IO =  0xF2,
	LD_A_D =     0x7A,
	LD_A_E =     0x7B,
	LD_A_H =     0x7C,
	LD_A_L =     0x7D,
	LD_A_BC =    0x0A,
	LD_A_DE =    0x1A,
	LD_A_HL =    0x7E,
	LDD_A_HL =   0x3A,
	LDI_A_HL =   0x2A,
	LD_A_nn =    0xFA,
	LDH_A_n =    0xF0,
	LD_B_A =     0x47,
	LD_B_B =     0x40,
	LD_B_C =     0x41,
	LD_B_D =     0x42,
	LD_B_E =     0x43,
	LD_B_H =     0x44,
	LD_B_L =     0x45,
	LD_B_HL =    0x46,
	LD_C_A =     0x4F,
	LD_C_A_IO =  0xE2,
	LD_C_B =     0x48,
	LD_C_C =     0x49,
	LD_C_D =     0x4A,
	LD_C_E =     0x4B,
	LD_C_H =     0x4C,
	LD_C_L =     0x4D,
	LD_C_HL =    0x4E,
	LD_D_A =     0x57,
	LD_D_B =     0x50,
	LD_D_C =     0x51,
	LD_D_D =     0x52,
	LD_D_E =     0x53,
	LD_D_H =     0x54,
	LD_D_L =     0x55,
	LD_D_HL =    0x56,
	LD_E_A =     0x5F,
	LD_E_B =     0x58,
	LD_E_C =     0x59,
	LD_E_D =     0x5A,
	LD_E_E =     0x5B,
	LD_E_H =     0x5C,
	LD_E_L =     0x5D,
	LD_E_HL =    0x5E,
	LD_H_A =     0x67,
	LD_H_B =     0x60,
	LD_H_C =     0x61,
	LD_H_D =     0x62,
	LD_H_E =     0x63,
	LD_H_H =     0x64,
	LD_H_L =     0x65,
	LD_H_HL =    0x66,
	LD_L_A =     0x6F,
	LD_L_B =     0x68,
	LD_L_C =     0x69,
	LD_L_D =     0x6A,
	LD_L_E =     0x6B,
	LD_L_H =     0x6C,
	LD_L_L =     0x6D,
	LD_L_HL =    0x6E,
	LD_HL_A =    0x77,
	LD_HL_B =    0x70,
	LD_HL_C =    0x71,
	LD_HL_D =    0x72,
	LD_HL_E =    0x73,
	LD_HL_H =    0x74,
	LD_HL_L =    0x75,
	LD_HL_n =    0x36,
	LDD_HL_A =   0x32,
	LDI_HL_A =   0x22,
	LD_BC_A =    0x02,
	LD_DE_A =    0x12,
	LD_nn_A =    0xEA,
	LDH_n_A =    0xE0,
	LD_BC_nn =   0x01,
	LD_DE_nn =   0x11,
	LD_HL_nn =   0x21,
	LD_SP_nn =   0x31,
	LD_SP_HL =   0xF9,
	LD_HL_SP_n = 0xF8,
	LD_nn_SP =   0x08,
	PUSH_AF =    0xF5,
	PUSH_BC =    0xC5,
	PUSH_DE =    0xD5,
	PUSH_HL =    0xE5,
	POP_AF =     0xF1,
	POP_BC =     0xC1,
	POP_DE =     0xD1,
	POP_HL =     0xE1,
	ADD_A_A =    0x87,
	ADD_A_B =    0x80,
	ADD_A_C =    0x81,
	ADD_A_D =    0x82,
	ADD_A_E =    0x83,
	ADD_A_H =    0x84,
	ADD_A_L =    0x85,
	ADD_A_HL =   0x86,
	ADD_A_n =    0xC6,
	ADC_A_A =    0x8F,
	ADC_A_B =    0x88,
	ADC_A_C =    0x89,
	ADC_A_D =    0x8A,
	ADC_A_E =    0x8B,
	ADC_A_H =    0x8C,
	ADC_A_L =    0x8D,
	ADC_A_HL =   0x8E,
	ADC_A_n =    0xCE,
	SUB_A =      0x97,
	SUB_B =      0x90,
	SUB_C =      0x91,
	SUB_D =      0x92,
	SUB_E =      0x93,
	SUB_H =      0x94,
	SUB_L =      0x95,
	SUB_HL =     0x96,
	SUB_n =      0xD6,
	SBC_A_A =    0x9F,
	SBC_A_B =    0x98,
	SBC_A_C =    0x99,
	SBC_A_D =    0x9A,
	SBC_A_E =    0x9B,
	SBC_A_H =    0x9C,
	SBC_A_L =    0x9D,
	SBC_A_HL =   0x9E,
	SBC_A_n =    0xDE,
	AND_A =      0xA7,
	AND_B =      0xA0,
	AND_C =      0xA1,
	AND_D =      0xA2,
	AND_E =      0xA3,
	AND_H =      0xA4,
	AND_L =      0xA5,
	AND_HL =     0xA6,
	AND_n =      0xE6,
	OR_A =       0xB7,
	OR_B =       0xB0,
	OR_C =       0xB1,
	OR_D =       0xB2,
	OR_E =       0xB3,
	OR_H =       0xB4,
	OR_L =       0xB5,
	OR_HL =      0xB6,
	OR_n =       0xF6,
	XOR_A =      0xAF,
	XOR_B =      0xA8,
	XOR_C =      0xA9,
	XOR_D =      0xAA,
	XOR_E =      0xAB,
	XOR_H =      0xAC,
	XOR_L =      0xAD,
	XOR_HL =     0xAE,
	XOR_n =      0xEE,
	CP_A =       0xBF,
	CP_B =       0xB8,
	CP_C =       0xB9,
	CP_D =       0xBA,
	CP_E =       0xBB,
	CP_H =       0xBC,
	CP_L =       0xBD,
	CP_HL =      0xBE,
	CP_n =       0xFE,
	INC_A =      0x3C,
	INC_B =      0x04,
	INC_C =      0x0C,
	INC_D =      0x14,
	INC_E =      0x1C,
	INC_H =      0x24,
	INC_L =      0x2C,
	INC_HL_A =   0x34,
	DEC_A =      0x3D,
	DEC_B =      0x05,
	DEC_C =      0x0D,
	DEC_D =      0x15,
	DEC_E =      0x1D,
	DEC_H =      0x25,
	DEC_L =      0x2D,
	DEC_HL_A =   0x35,
	ADD_HL_BC =  0x09,
	ADD_HL_DE =  0x19,
    ADD_HL_HL =  0x29,
	ADD_HL_SP =  0x39,
	ADD_SP_n =   0xE8,
	INC_BC =     0x03,
	INC_DE =     0x13,
	INC_HL =     0x23,
	INC_SP =     0x33,
	DEC_BC =     0x0B,
	DEC_DE =     0x1B,
	DEC_HL =     0x2B,
	DEC_SP =     0x3B,
	DAA =        0x27,
  	CPL =        0x2F,
	CCF =        0x3F,
	SCF =        0x37,
	NOP =        0x00,
	HALT =       0x76,
	STOP =       0x10, 
	DI =         0xF3,
    EI =         0xFB, 
	RLCA =       0x07,
	RLA =        0x17,
	RRCA =       0x0F,
	RRA =        0x1F,
	JP_nn =      0xC3,
	JP_NZ =      0xC2,
	JP_Z =       0xCA,
	JP_NC =      0xD2,
	JP_C =       0xDA, 
	JP_HL =      0xE9,
	JR_n =       0x18,
	JR_NZ =      0x20,
	JR_Z =       0x28,
	JR_NC =      0x30,
	JR_C =       0x38,
	CALL_nn =    0xCD,
	CALL_NZ =    0xC4,
	CALL_Z =     0xCC,
	CALL_NC =    0xD4,
	CALL_C =     0xDC,
	RST_00 =     0xC7,
	RST_08 =     0xCF,
	RST_10 =     0xD7,
	RST_18 =     0xDF,
	RST_20 =     0xE7,
	RST_28 =     0xEF,
	RST_30 =     0xF7,
	RST_38 =     0xFF,
	RET =        0xC9,
	RET_NZ =     0xC0,
	RET_Z =      0xC8,
	RET_NC =     0xD0,
	RET_C =      0xD8,
	RETI =       0xD9,
};
