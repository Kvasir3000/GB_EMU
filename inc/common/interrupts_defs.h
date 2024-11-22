#pragma once 

//#define IE                     0xFFFF
#define IE_VBLANK_MASK           0x01
#define IE_LCD_MASK              0x02
#define IE_TIMER_MASK            0x04
#define IE_SERIAL_MASK           0x08
#define IE_JOYPAD_MASK           0x10

//#define IF                     0xFF0F
#define IF_VBLANK_MASK           0x01
#define IF_LCD_MASK              0x02
#define IF_TIMER_MASK            0x04
#define IF_SERIAL_MASK           0x08
#define IF_JOYPAD_MASK           0x10
#define IF_VBLANK_CLEAR_MASK     0xFE
#define IF_LCD_CLEAR_MASK        0xFD
#define IF_TIMER_CLEAR_MASK      0xFB
#define IF_SERIAL_CLEAR_MASK     0xF7
#define IF_JOYPAD_CLEAR_MASK     0xEF
 
#define INTERRUPT_SRC_VBLANK     0x40
#define INTERRUPT_SRC_STAT       0x48
#define INTERRUPT_SRC_TIMER      0x50
#define INTERRUPT_SRC_SERIAL     0x58
#define INTERRUPT_SRC_JOYPAD     0x60

#define REQUEST_TIMER_INTERRUPT  0b0001
#define REQUEST_VBLANK_INTERRUPT 0b0010
#define REQUEST_LCD_INTERRUPT    0b0100
#define REQUEST_JOYPAD_INTERRUPT 0b1000
