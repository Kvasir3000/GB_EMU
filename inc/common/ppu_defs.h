#pragma once 

#define LCD_RESOLUTION_X               160
#define LCD_RESOLUTION_Y               144 
#define LCD_RESOLUTION_SCALER          4

#define LCD_OBJECT_Y_OFFSET            16
#define LCD_OBJECT_X_OFFSET            8
#define LCD_WINDOW_X_OFFSET            7

#define TILE_DIMENSION                 8
#define TILE_MAP_DIMENSION             32
#define TILE_MAP_PIXEL_DIMENSION       TILE_DIMENSION * TILE_MAP_DIMENSION

#define TILE_SIZE                      16

#define MODE_0_HORIZONTAL_BLANK_DOTS   204
#define MODE_2_OAM_SCAN_DOTS           80
#define MODE_3_DRAWING_PIXELS_DOTS     172
#define SCANLINE_DOTS                  MODE_0_HORIZONTAL_BLANK_DOTS + MODE_3_DRAWING_PIXELS_DOTS + MODE_2_OAM_SCAN_DOTS
#define MODE_1_VERTICAL_BLANK_DOTS     SCANLINE_DOTS
#define END_OF_FRAME_SCANLINE          153


#define LCDC_BG_WINDOW_ENABLE          0b00000001 
#define LCDC_OBJ_ENABLE                0b00000010 
#define LCDC_OBJ_SIZE                  0b00000100 
#define LCDC_BG_TILE_MAP               0b00001000 
#define LCDC_BG_WINDOW_TILE_DATA       0b00010000 
#define LCDC_WINDOW_ENABLE             0b00100000 
#define LCDC_WINDOW_TILE_MAP           0b01000000
#define LCDC_LCD_PPU_ENABLE            0b10000000

#define LCD_STAT_PPU_MODE              0b00000011
#define LCD_STAT_LYC_LY                0b00000100
#define LCD_STAT_MODE_0                0b00001000
#define LCD_STAT_MODE_1                0b00010000
#define LCD_STAT_MODE_2                0b00100000
#define LCD_STAT_LYX_SELECT            0b01000000


#define WINDOW_TILE_MAP_BASE_0         0x9800
#define WINDOW_TILE_MAP_BASE_1         0x9C00
#define BG_TILE_MAP_BASE_0             0x9800
#define BG_TILE_MAP_BASE_1             0x9C00
#define TILE_DATA_BASE_0               0x9000
#define TILE_DATA_BASE_1               0x8000

#define PIXEL_MASK                     0b11

#define OAM_ATTRIBUTES_CGB_PALLETE     0b00000111 // CGB only
#define OAM_ATTRIBUTES_BANK            0b00001000 // CGB only
#define OAM_ATTRIBUTES_DMG_PALLETE     0b00010000
#define OAM_ATTRIBUTES_X_FLIP          0b00100000
#define OAM_ATTRIBUTES_Y_FLIP          0b01000000 
#define OAM_ATTRIBUTES_PRIORITY        0b10000000 

#define TRANSPERENT_PIXEL              0

