//////////////////////////////////////////////////////////////////////////////
/// @file T6963.h
/// @copy Copyright (C) 2021 Will Cooke
/// @brief Controls 240x64 T6963 display using T6963 (DG-24064-09-S2RB)
//////////////////////////////////////////////////////////////////////////////


#ifndef T6963_H
#define T6963_H

#include "Arduino.h"


// Pin definitions
#define T6963_WR        2         // write
#define T6963_RD        3         // Read
#define T6963_CE       A5         // Chip Enable
#define T6963_CD       A4         // Command / /Data
#define T6963_RES      A3         // Reset
#define T6963_D0        4         // Data 0
#define T6963_D1        5         // Data 1
#define T6963_D2        6         // Data 2
#define T6963_D3        7         // Data 3
#define T6963_D4        8         // Data 4
#define T6963_D5        9         // Data 5
#define T6963_D6       10         // Data 6
#define T6963_D7       11         // Data 7
#define T6963_FONT     12         // Font Select LOW: 8x8, HIGH: 6x8

// T6963 Command Definitions

// ****   NOTE!   ****
// When using MSB=0 commands, a status read must be performed
// Pointer Set Commands
//   0 0 1 0 0 N2 N1 N0
#define T6963_SET_CURSOR_POINTER          0x21     // [X Address] [Y Address]
#define T6963_SET_OFFSET_REGISTER         0x22     // [Data] [0]
#define T6963_SET_ADDRESS_POINTER         0x24     // [Low Address] [High Address]

// Control Word Set Commands
//  0  1  0  0  0  0 N1 N0
#define T6963_SET_TEXT_HOME_ADDRESS       0x40     // [Low Address] [High Address]
#define T6963_SET_TEXT_AREA               0x41     // [Columns] [0]
#define T6963_SET_GRAPHIC_HOME_ADDRESS    0x42     // [Low Address] [High Address]
#define T6963_SET_GRAPHIC_AREA            0x43     // [Columns] [0]

// Mode Set Commands
//  1  0  0  0 CG N2 N1 N0    // CG = char gen, N2-N0 = logic mode
#define T6963_SET_MODE                    0x80     // Generic SET MODE command
#define T6963_MODE_CG_ROM                 (1 << 3) // Use RAM character generator
#define T6963_MODE_OR                     0x00     // Set OR mode
#define T6963_MODE_XOR                    0x01     // Set XOR mode
#define T6963_MODE_AND                    0x03     // Set AND mode
#define T6963_MODE_ATTRIBUTE              0x04     // Set Text / Attribute mode

#define T6963_SET_OR_MODE                 0x80     // Set graphics OR mode
#define T6963_SET_EXOR_MODE               0x81     // Set graphics XOR mode
#define T6963_SET_AND_MODE                0x83     // Set graphics AND mode
#define T6963_SET_TEXT_ATTRIBUTE_MODE     0x84     // Set text attribute mode
#define T6963_SET_INTERNAL_CG_ROM_MODE    0x80     // Set Internal Char Gen mode
#define T6963_SET_EXTERNAL_CG_RAM_MODE    0x84     // Set External Char Gen mode

// Add or OR below modes with SET_MODE command
#define T6963_MODE_RAM_CG                (1 << 3)  // Use RAM character generator
#define T6963_MODE_OR                     0x00     // OR Mode
#define T6963_MODE_EXOR                   0x01     // XOR mode
#define T6963_MODE_AND                    0x03     // AND mode
#define T6963_MODE_TEXT_ATTRIBUTE         0x04     // TEXT ATTRIBUTE MODE




// Display Modes Set
//  1  0  0  1 N3 N2 N1 N0  // N3 = graphics, N2 = text, N1 = cursor, N0 = cursor blink
#define T6963_DISPLAY_GRAPHICS          (1 << 3)   // Turn on/off graphics mode
#define T6963_DISPLAY_TEXT              (1 << 2)   // Turn on/off text mode
#define T6963_DISPLAY_CURSOR            (1 << 1)   // Turn on/off cursor
#define T6963_DISPLAY_BLINK             (1 << 0)   // Turn on/off cursor blink

#define T6963_DISPLAY_MODE                0x90     // Generic display mode cmd, add modes
#define T6963_DISPLAY_OFF                 0x90     // Turn off display
#define T6963_CURSOR_ON_BLINK_OFF         0x92     // Turn on cursor, blink off
#define T6963_CURSOR_ON_BLINK_ON          0x93     // Turn cursor on, blink on
#define T6963_TEXT_ON_GRAPHIC_OFF         0x94     // Turn text on, graphic off
#define T6963_TEXT_OFF_GRAPHIC_ON         0x98     // Turn text off, graphic on
#define T6963_TEXT_ON_GRAPHIC_ON          0x9c     // Turn text on, graphic on


// Cursor Pattern Select
//  1  0  1  0  0 N2 N1 N0   N2-N0 Number lines for cursor +1
#define T6963_CURSOR_SIZE                 0xa0     // Set number lines for cursor
#define T6963_CURSOR_SIZE_1               0xa0     // Set 1 line cursor (bottom line)
#define T6963_CURSOR_SIZE_2               0xa1     // Set 2 line cursor
#define T6963_CURSOR_SIZE_3               0xa2     // Set 3 line cursor
#define T6963_CURSOR_SIZE_4               0xa3     // Set 4 line cursor
#define T6963_CURSOR_SIZE_5               0xa4     // Set 5 line cursor
#define T6963_CURSOR_SIZE_6               0xa5     // Set 6 line cursor
#define T6963_CURSOR_SIZE_7               0xa6     // Set 7 line cursor
#define T6963_CURSOR_SIZE_8               0xa7     // Set 8 line cursor (block)

// Data Auto Read/Write
//  1  0  1  1  0  0 N1 N0      N0 = Data Auto Read N1 = Auto Reset (inc address pntr)
#define T6963_AUTO_WRITE_SET              0xb0     // Set auto write mode
#define T6963_AUTO_READ_SET               0xb1     // Set auto read mode
#define T6963_AUTO_RESET                  0xb2     // Reset ???

// Data Read/Write
//  1  1  0  0  0 N2 N1 N0   N2 = no inc/dec addr pntr, N1 = Addr pntr down, N0 = Read
#define T6963_DATA_WRITE_INC              0xc0     // write data and increment
#define T6963_DATA_WRITE_DEC              0xc2     // write data and decrement
#define T6963_DATA_WRITE                  0xc4     // write and stay in place
#define T6963_DATA_READ_INC               0xc1     // read data and increment
#define T6963_DATA_READ_DEC               0xc3     // Read data and decrement
#define T6963_DATA_READ                   0xc5     // Read and stay in place

// Screen peek
//   1  1  1  0  0  0  0  0
#define T6963_SCREEN_PEEK                 0xe0     // peek screen at current address

// Screen copy
//   1  1  1  0  1  0  0  0                Copies one line of displayed data
#define T6963_SCREEN_COPY                 0xe8    // Copies one line of data

// Bit SET/RESET
//   1  1  1  1 N3 N2 N1 N0   N3 = SET, N2-N0 = bit
#define T6963_SET_RESET                   0xf0     // Set/reset - add codes
#define T6963_SET                         0xf8     // Set any bit (add bit #)
#define T6963_SET_0                       0xf8     // Set bit 0 
#define T6963_SET_1                       0xf9     // Set bit 1
#define T6963_SET_2                       0xfa     // Set bit 2
#define T6963_SET_3                       0xfb     // Set bit 3
#define T6963_SET_4                       0xfc     // Set bit 4
#define T6963_SET_5                       0xfd     // Set bit 5
#define T6963_SET_6                       0xfe     // Set bit 6
#define T6963_SET_7                       0xff     // Set bit 7
#define T6963_RESET                       0xf0     // Reset any bit (add bit #)
#define T6963_RESET_0                     0xf0     // Reset bit 0
#define T6963_RESET_1                     0xf1     // Reset bit 1
#define T6963_RESET_2                     0xf2     // Reset bit 2
#define T6963_RESET_3                     0xf3     // Reset bit 3
#define T6963_RESET_4                     0xf4     // Reset bit 4
#define T6963_RESET_5                     0xf5     // Reset bit 5
#define T6963_RESET_6                     0xf6     // Reset bit 6
#define T6963_RESET_7                     0xf7     // Reset bit 7


//////////////////////////////////////////////////////////////////////////////
/// @class T6963
//////////////////////////////////////////////////////////////////////////////

class T6963
{
  public:
    T6963(int d0, int d1, int d2, int d3, int d4, int d5, int d6, int d7, 
          int wr, int rd, int ce, int cd, int fs, int res);
    void writeDataByte(uint8_t dat)
    void writeCommandByte(uint8_t cmd)
    int TsetCursor(int x, int y)
    int setOffsetPointer(uint8_t offs)
    void setAddress(uint16_t addr)
    void setTextHomeAddress(uint16_t addr)
    void setGraphicHomeAddress(uint16_t addr)
    void setTextArea(uint8_t cols)
    void setGraphicArea(uint8_t cols)
    void setOrMode(uint8_t CG = 0)
    void setXorMode(uint8_t CG = 0)
    void setAndMode(uint8_t CG = 0)
    void setTextAttributeMode(uint8_t CG = 0)
    void setDisplayMode(uint8_t txt = 0, uint8_t grph = 0, uint8_t curs = 0, uint8_t blnk = 0)
    void setCursorSize(uint8_t siz)
    void setAutoWrite()
    void setAutoRead()
    void setAutoReset()
    void dataWriteIncrement(uint8_t dat)
    void dataWriteDecrement(uint8_t dat)
    void dataWrite(uint8_t dat)
    uint8_t dataReadIncrement()
    uint8_t dataReadDecrement()
    uint8_t dataRead()
    uint8_t screenPeek()
    void screenCopy()
    void setBit(uint8_t b)
    void resetBit(uint8_t b)

  private:
    
    bool ports_init()
    void setDataDirection(int dir)
    void setDataBits(uint8_t d)
    static uint8_t getDataBits()
    uint8_t getStatus()
    uint8_t getData()
    void wait()
    void waitAuto()
    void waitAutoRead()
    void waitAutoWrite()

    uint8_t pins[14];  // d0-d7,wr,rd,ce,cd,fs,res

    uint16_t cursorPointer;
    uint16_t offsetPointer;   
    uint16_t addressPointer;

    uint16_t textHomeAddress;
    uint8_t textArea;
    uint16_t graphicHomeAddres;
    uint8_t graphicArea;

};

#endif
