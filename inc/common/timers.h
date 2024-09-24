#pragma once 

#define DIV                     0xFF04
#define DIV_FREQ_CLK            255 


#define TIMA                    0xFF05

#define TMA                     0xFF06

#define TAC                     0xFF07
#define TAC_CLOCK_MASK          0x03
#define TAC_ENABLE_MASK         0x04
#define TAC_CLOCK_00_4096_HZ    0x00
#define TAC_CLOCK_01_262144_HZ  0x01
#define TAC_CLOCK_10_65536_HZ   0x02
#define TAC_CLOCK_11_16384_HZ   0x03
