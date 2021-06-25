///////////////////////////////////////////////////////////////////////////////
/// @file T6963.cpp
/// @copy Copyright (C) 2021 Will Cooke
/// @brief Controls 240x64 T6963 display using T6963 (DG-24064-09-S2RB)
//////////////////////////////////////////////////////////////////////////////

#include T6963.h





// TODO: We can simplify a lot of code by storing the pin #'s in an array
//static int dataPins[8];

////////////////////////////////////////////////////////////////////////////////
///  pin mapping
///  @brief which array word holds which pin number
////////////////////////////////////////////////////////////////////////////////

enum pinmap
{
  PIN_D0    0,
  PIN_D1    1,
  PIN_D2    2,
  PIN_D3    3,
  PIN_D4    4,
  PIN_D5    5,
  PIN_D6    6,
  PIN_D7    7,
  PIN_WR    8,
  PIN_RD    9,
  PIN_CE   10,
  PIN_CD   11,
  PIN_RES  12,
  PIN_FS   13
}


////////////////////////////////////////////////////////////////////////////////
///  @fn T6963
///  @brief  Constructor.  Assigns pins, initializes display
///  @param[in] d0   pin assigned for data 0
///  @param[in] d1   pin assigned for data 1
///  @param[in] d2   pin assigned for data 2
///  @param[in] d3   pin assigned for data 3
///  @param[in] d4   pin assigned for data 4
///  @param[in] d5   pin assigned for data 5
///  @param[in] d6   pin assigned for data 6
///  @param[in] d7   pin assigned for data 7
///  @param[in] wr   pin assigned for /write
///  @param[in] rd   pin assigned for /read
///  @param[in] ce   pin assigned for /chip enable
///  @param[in] cd   pin assigned for command /data
///  @param[in] res  pin assigned for /reset:  0 if not used
///  @param[in] fs   pin assigned for font select: 0 if not used
////////////////////////////////////////////////////////////////////////////////

T6963::T6963(int d0, int d1, int d2, int d3, int d4, int d5, int d6, int d7, 
             int wr, int rd, int ce, int cd, int res = 0, int fs = 0)
{
  pins[PIN_D0] = d0;
  pins[PIN_D1] = d1;
  pins[PIN_D2] = d2;
  pins[PIN_D3] = d3;
  pins[PIN_D4] = d4;
  pins[PIN_D5] = d5;
  pins[PIN_D6] = d6;
  pins[PIN_D7] = d7;
  pins[PIN_WR] = wr;
  pins[PIN_RD] = rd;
  pins[PIN_CE] = ce;
  pins[PIN_CD] = cd;
  pins[PIN_RES] = res;
  pins[PIN_FS] = fs;
  
              
}

////////////////////////////////////////////////////////////////////////////////
///  @fn ports_init
///  @brief  Initializes all gpio ports for use
///  @return  True if initialized, false otherwise
////////////////////////////////////////////////////////////////////////////////
bool T6963::ports_init()
{
  bool rtn = false;
  
  pinMode(pins[PIN_CE], OUTPUT);
  digitalWrite(pins[PIN_CE], HIGH);
  pinMode(pins[PIN_WR], OUTPUT);
  digitalWrite(pins[PIN_WR], HIGH);
  pinMode(pins[PIN_RD], OUTPUT);
  digitalWrite(pins[PIN_CD], HIGH);
  pinMode(pins[PIN_CD], OUTPUT);

  if(pins[PIN_RES] != 0)
  {
    pinMode(pins[PIN_RES], OUTPUT);
    digitalWrite(pins[PIN_RES], LOW);   // Reset while we're here
  }
  if(pins[PIN_FS] != 0)
  {
    pinMode(pins[PIN_FS], OUTPUT);
    digitalWrite(pins[PIN_FS], HIGH);  // 6x8 font
  }
  
  setDataDirection(OUTPUT);
  
  delay(5);  // Give RESET 5 milliseconds
  digitalWrite(pins[PIN_RES], HIGH);

  rtn = true;
  return rtn;
}

////////////////////////////////////////////////////////////////////////////////
///  @fn setDataDirection
///  @brief  Sets Data Bus pins direction
///  @param[in]  INPUT, OUTPUT to choose direction
////////////////////////////////////////////////////////////////////////////////

void T6963::setDataDirection(int dir)
{
  for(int p = PIN_D0; p <= PIN_D7; p++)  // assumes data pins in order in array
  {
    pinMode(pins[p], dir);
  }
//  pinMode(T6963_D0, dir);
//  pinMode(T6963_D1, dir);
//  pinMode(T6963_D2, dir);
//  pinMode(T6963_D3, dir);
//  pinMode(T6963_D4, dir);
//  pinMode(T6963_D5, dir);
//  pinMode(T6963_D6, dir);
//  pinMode(T6963_D7, dir);
}


////////////////////////////////////////////////////////////////////////////////
///  @fn setDataBits
///  @brief Sets output data onto data bus pins
///  @param[in] d: Byte to set on bus pins
////////////////////////////////////////////////////////////////////////////////

void T6963::setDataBits(uint8_t d)
{
  for(int b = 0; b < 8; b++)   // assumes data pins in order (0 to 7) in array
  {
    digitalWrite(pins[PIN_D0 + b], d & 0x01)
    d >>= 1;
  }
  //digitalWrite(T6963_D0, d & 0x01);
  //d >>= 1;
  //digitalWrite(T6963_D1, d & 0x01);
  //d >>= 1;
  //digitalWrite(T6963_D2, d & 0x01);
  //d >>= 1;
  //digitalWrite(T6963_D3, d & 0x01);
  //d >>= 1;
  //digitalWrite(T6963_D4, d & 0x01);
  //d >>= 1;
  //digitalWrite(T6963_D5, d & 0x01);
  //d >>= 1;
  //digitalWrite(T6963_D6, d & 0x01);
  //d >>= 1;
  //digitalWrite(T6963_D7, d & 0x01);
}

////////////////////////////////////////////////////////////////////////////////
///  @fn getDataBits
///  @brief  Reads data bus pins
///  @return  Byte value read from pins
////////////////////////////////////////////////////////////////////////////////

uint8_t T6963::getDataBits()
{
  uint8_t rtn = 0;
  for(int b = 0; b < 8; b++)  // Assumes data pins in order 0 to 7 in array
  {
    rtn <<= 1;
    if(digitalRead(pins[PIN_D7 - b]) == HIGH)
    {
      rtn |= 0x01;
    }
  }
  
//  if(digitalRead(T6963_D7) == HIGH)
//  {
//    rtn |= (1 << 7);
//  }
//  if(digitalRead(T6963_D6) == HIGH)
//  {
//    rtn |= (1 << 6);
//  }
//  if(digitalRead(T6963_D5) == HIGH)
//  {
//    rtn |= (1 << 5);
//  }
//  if(digitalRead(T6963_D4) == HIGH)
//  {
//    rtn |= (1 << 4);
//  }
//  if(digitalRead(T6963_D3) == HIGH)
//  {
//    rtn |= (1 << 3);
//  }
//  if(digitalRead(T6963_D2) == HIGH)
//  {
//    rtn |= (1 << 2);
//  }
//  if(digitalRead(T6963_D1) == HIGH)
//  {
//    rtn |= (1 << 1);
//  }
//  if(digitalRead(T6963_D0) == HIGH)
//  {
//    rtn |= (1 << 0);
//  }

  return rtn;
}


////////////////////////////////////////////////////////////////////////////////
///  @fn getStatus
///  @brief  Retrieves status byte from T6963 controller
///  @return  T6963 status byte
////////////////////////////////////////////////////////////////////////////////
uint8_t T6963::getStatus()
{
  uint8_t rtn = 0;
  setDataDirection(INPUT);
  digitalWrite(pins[PIN_CD], HIGH);
  digitalWrite(pins[PIN_RD], LOW);
  digitalWrite(pins[PIN_CE], LOW);
  rtn = getDataBits();
  digitalWrite(pins[PIN_CE], HIGH);
  digitalWrite(pins[PIN_RD], HIGH);
  setDataDirection(OUTPUT);
  return rtn;
  
}

////////////////////////////////////////////////////////////////////////////////
///  @fn getData
///  @brief  Gets data byte from T6963 controller 
///  @return  Data byte read from controller
////////////////////////////////////////////////////////////////////////////////
uint8_t T6963::getData()
{
  uint8_t rtn = 0;
  setDataDirection(INPUT);
  digitalWrite(pins[PIN_CD], LOW);
  digitalWrite(pins[PIN_RD], LOW);
  digitalWrite(pins[PIN_CE], LOW);
 // delay(1);
  rtn = getDataBits();
  digitalWrite(pins[PIN_CE], HIGH);
  digitalWrite(pins[PIN_RD], HIGH);
  setDataDirection(OUTPUT);
  return rtn;
  
}

////////////////////////////////////////////////////////////////////////////////
///  @fn wait
///  @brief   Waits for STATUS0 and STATUS1 to both indicate ready
////////////////////////////////////////////////////////////////////////////////
void T6963::wait()
{
  while(getStatus() & 0x03 != 3);
}

////////////////////////////////////////////////////////////////////////////////
///  @fn waitAuto
///  @brief   Waits for STATUS2 or STATUS3 to either indicate ready
////////////////////////////////////////////////////////////////////////////////
void T6963::waitAuto()
{
  while(getStatus() & 0x0c == 0);  // wait while neither bit set
}

////////////////////////////////////////////////////////////////////////////////
///  @fn waitAutoRead
///  @brief  Waits until auto read capable bit is set
////////////////////////////////////////////////////////////////////////////////
void T6963::waitAutoRead()
{
  while(getStatus() & 0x04 != 4);
}

////////////////////////////////////////////////////////////////////////////////
///  @fn waitAutoWrite
///  @brief Waits until auto write capable bit is set
////////////////////////////////////////////////////////////////////////////////
void T6963::waitAutoWrite()
{
  while(getStatus() & 0x08 != 8);
}

////////////////////////////////////////////////////////////////////////////////
///  @fn writeDataByte
///  @brief  Send a byte of data to controller
///  @param[in]  dat The data byte to send
////////////////////////////////////////////////////////////////////////////////
void T6963::writeDataByte(uint8_t dat)
{
  wait();
  setDataDirection(OUTPUT);
  setDataBits(dat);
  digitalWrite(T6963_CD, LOW);
  digitalWrite(T6963_WR, LOW);
  digitalWrite(T6963_CE, LOW);
 // delay(1);
  digitalWrite(T6963_CE, HIGH);  // min pulse width 80 nS
  digitalWrite(T6963_WR, HIGH);
}

////////////////////////////////////////////////////////////////////////////////
///  @fn writeCommandByte
///  @brief  Sends a command byte to controller. Send parameters prior to cmd.
///  @param[in] cmd The command byte to send
////////////////////////////////////////////////////////////////////////////////
void T6963::writeCommandByte(uint8_t cmd)
{
  wait();
  setDataDirection(OUTPUT);
  setDataBits(cmd);
  digitalWrite(T6963_CD, HIGH);
  digitalWrite(T6963_WR, LOW);
  digitalWrite(T6963_CE, LOW);
 // delay(1);
  digitalWrite(T6963_CE, HIGH);  // min pulse width 80 nS
  digitalWrite(T6963_WR, HIGH);
}

////////////////////////////////////////////////////////////////////////////////
///  @fn setCursor
///  @brief  Set cursor location
///  @param[in] x The horizontal coordinate (0 to 127)
///  @param[in] y The vertical coordinate (0 to 63)
///  @return  Zero on success, -1 if out of bounds
////////////////////////////////////////////////////////////////////////////////
int T6963::setCursor(int x, int y)
{
  int rtn = 0;
  if(x < 0 || x > 127 || y < 0 || y > 63)
  {
    rtn = -1;
  }
  else
  {
    writeDataByte(x);
    writeDataByte(y);
    writeCommandByte(T6963_SET_CURSOR_POINTER);
  }
  return rtn;
}


////////////////////////////////////////////////////////////////////////////////
///  @fn setOffsetPointer
///  @brief  Sets high five bits of char gen RAM location (2K granularity)
///  @param[in]  offs  The offset page (0 to 31)
///  @return  Zero on success, -1 if out of bounds
////////////////////////////////////////////////////////////////////////////////
int T6963::setOffsetPointer(uint8_t offs)
{
  int rtn = 0;
  if(offs > 31)
  {
    rtn = -1;
  }
  else
  {
    writeDataByte(offs);
    writeDataByte(0);
    writeCommandByte(T6963_SET_OFFSET_REGISTER);
  }
  return rtn;
}


////////////////////////////////////////////////////////////////////////////////
///  @fn setAddress
///  @brief  Sets controller RAM address for reads and writes
///  @param[in] addr  The RAM address to set (0 to 65535) (8191 on DG24064)
////////////////////////////////////////////////////////////////////////////////
void T6963::setAddress(uint16_t addr)
{
  writeDataByte(addr & 0xff); // low byte
  writeDataByte( (addr >> 8) & 0xff);  // high byte
  writeCommandByte(T6963_SET_ADDRESS_POINTER);
}


////////////////////////////////////////////////////////////////////////////////
///  @fn setTextHomeAddress
///  @brief  Sets RAM address used as top left text displayed text character
///  @param[in] addr The RAM address to use for top left character (0 - 65535)
////////////////////////////////////////////////////////////////////////////////
void T6963::setTextHomeAddress(uint16_t addr)
{
  writeDataByte(addr & 0xff);
  writeDataByte( (addr >> 8) & 0xff);
  writeCommandByte(T6963_SET_TEXT_HOME_ADDRESS);
}

////////////////////////////////////////////////////////////////////////////////
///  @fn setGraphicHomeAddress
///  @brief Sets RAM address of top left graphics byte or text attribute byte
///  @param[in] addr The RAM address for graphics or attributes (0 - 65535)
////////////////////////////////////////////////////////////////////////////////
void T6963::setGraphicHomeAddress(uint16_t addr)
{
  writeDataByte(addr & 0xff);
  writeDataByte( (addr >> 8) & 0xff);
  _writeCommandByte(T6963_SET_GRAPHIC_HOME_ADDRESS);
}

////////////////////////////////////////////////////////////////////////////////
///  @fn setTextArea
///  @brief  Define number of columns for text area of RAM, independent of h/w
///  @param[in] cols  Number of text columns
////////////////////////////////////////////////////////////////////////////////
void T6963::setTextArea(uint8_t cols)
{
  writeDataByte(cols);
  writeDataByte(0);
  writeCommandByte(T6963_SET_TEXT_AREA);
}

////////////////////////////////////////////////////////////////////////////////
///  @fn setGraphicArea
///  @brief Define number of (text) columns for graphic area, independent of h/w
///  @param[in] cols Number of text columns
////////////////////////////////////////////////////////////////////////////////
void T6963::setGraphicArea(uint8_t cols)
{
  writeDataByte(cols);
  writeDataByte(0);
  writeCommandByte(T6963_SET_GRAPHIC_AREA);
}

////////////////////////////////////////////////////////////////////////////////
///  @fn setOrMode
///  @brief Set mode to OR text and graphic data and choose character generator
///  @param[in] CG choose 0 (default) for ROM, non-zero for RAM char gen
////////////////////////////////////////////////////////////////////////////////
void T6963::setOrMode(uint8_t CG = 0)
{
  if(CG != 0)
  {
    CG = T6963_MODE_RAM_CG;
  }
  writeCommandByte(T6963_SET_OR_MODE | CG);
}

////////////////////////////////////////////////////////////////////////////////
///  @fn setXorMode
///  @brief Set mode to XOR text and graphic data, choose character generator
///  @param[in] CG choose 0 (default) for ROM, non-zero for RAM char gen
////////////////////////////////////////////////////////////////////////////////
void T6963::setXorMode(uint8_t CG = 0)
{
  if(CG != 0)
  {
    CG = T6963_MODE_RAM_CG;
  }
  writeCommandByte(T6963_SET_EXOR_MODE | CG);
}

////////////////////////////////////////////////////////////////////////////////
///  @fn setAndMode
///  @brief Set mode to AND text and graphic data, choose character generator
///  @param[in] CG choose 0 (default) for ROM, non-zero for RAM char gen
////////////////////////////////////////////////////////////////////////////////
void T6963::setAndMode(uint8_t CG = 0)
{
  if(CG != 0)
  {
    CG = T6963_MODE_RAM_CG;
  }
  writeCommandByte(T6963_SET_AND_MODE | CG);
}

////////////////////////////////////////////////////////////////////////////////
///  @fn setTextAttributeMode
///  @brief Set text attribute mode and choose character generator
///  @param[in] CG choose 0 (default) for ROM, non-zero for RAM char gen
////////////////////////////////////////////////////////////////////////////////
void T6963::setTextAttributeMode(uint8_t CG = 0)
{
  if(CG != 0)
  {
    CG = T6963_MODE_RAM_CG;
  }
  writeCommandByte(T6963_SET_TEXT_ATTRIBUTE_MODE | CG);
}

////////////////////////////////////////////////////////////////////////////////
///  @fn setDisplayMode
///  @brief  Choose to display or not, text, graphics, cursor, blink
///  @param[in] txt Set non-zero to display text.
///  @param[in] grph Set non-zero to display graphics.
///  @param[in] curs Set non-zero to display the cursor.
///  @param[in] blnk Set non-zero to make the cursor blink.
////////////////////////////////////////////////////////////////////////////////
void T6963::setDisplayMode(uint8_t txt = 0, uint8_t grph = 0, uint8_t curs = 0, uint8_t blnk = 0)
{
  uint8_t cmd = T6963_DISPLAY_MODE;
  if(txt != 0)
  {
    cmd |= T6963_DISPLAY_TEXT;
  }
  if(grph != 0)
  {
    cmd |= T6963_DISPLAY_GRAPHICS;
  }
  if(curs != 0)
  {
    cmd |= T6963_DISPLAY_CURSOR;
  }
  if(blnk != 0)
  {
    cmd |= T6963_DISPLAY_BLINK;
  }
  writeCommandByte(cmd);
}

////////////////////////////////////////////////////////////////////////////////
///  @fn setCursorSize
///  @brief Select size of cursor from 1 (bottom only) to 8 (full block)
///  @param[in] siz Number of lines to use for cursor.
////////////////////////////////////////////////////////////////////////////////
void T6963::setCursorSize(uint8_t siz)
{
  if(siz > 8)
  {
    siz = 8;
  }
  if(siz < 1)
  {
    siz = 1;
  }
  siz--;  // Convert 1 to 8 to 0 to 7
  writeCommandByte(T6963_CURSOR_SIZE  | siz );
}

#define T6963_AUTO_WRITE_SET              0xb0     // Set auto write mode
#define T6963_AUTO_READ_SET               0xb1     // Set auto read mode
#define T6963_AUTO_RESET                  0xb2     // Reset ???

// After one of these commands, only command is  RESET
// Set Address Pointer first

// From manual
//  Auto Read                  Auto Write
//  set addr pntr              set addr pntr
//  status check  0,1          status check  0,1
//  send auto read             send auto write
//  status check 2             status check 3
//  data read                  data write

//  repeat                     repeat
//  status check 2             status check 2
//  data read                  data write

//  status check 2             status check 2
//  auto reset                 auto reset

////////////////////////////////////////////////////////////////////////////////
///  @fn T6963_setAutoWrite
///  @brief  Begins the autowrite mode.  Stays in that mode until autoreset.
////////////////////////////////////////////////////////////////////////////////
void T6963_setAutoWrite()
{
  T6963_writeCommandByte(T6963_AUTO_WRITE_SET);
}

////////////////////////////////////////////////////////////////////////////////
///  @fn T6963_setAutoRead
///  @brief Begins the autoread mode.  Stays in that mode until autoreset.
////////////////////////////////////////////////////////////////////////////////
void T6963_setAutoRead()
{
  T6963_writeCommandByte(T6963_AUTO_READ_SET);
}

////////////////////////////////////////////////////////////////////////////////
///  @fn T6963_setAutoReset
///  @brief  Ends autoread or autowrite mode.
////////////////////////////////////////////////////////////////////////////////
void T6963_setAutoReset()
{
  T6963_writeCommandByte(T6963_AUTO_RESET);
}

#define T6963_DATA_WRITE_INC              0xc0     // write data and increment
#define T6963_DATA_WRITE_DEC              0xc2     // write data and decrement
#define T6963_DATA_WRITE                  0xc4     // write and stay in place
#define T6963_DATA_READ_INC               0xc1     // read data and increment
#define T6963_DATA_READ_DEC               0xc3     // Read data and decrement
#define T6963_DATA_READ                   0xc5     // Read and stay in place

////////////////////////////////////////////////////////////////////////////////
///  @fn T6963_dataWriteIncrement
///  @brief  Write data at current address, increment address
///  @param[in] dat The data to write to RAM
////////////////////////////////////////////////////////////////////////////////
void T6963_dataWriteIncrement(uint8_t dat)
{
  wait();
  T6963_writeDataByte(dat);
  wait();
  T6963_writeCommandByte(T6963_DATA_WRITE_INC);
}

////////////////////////////////////////////////////////////////////////////////
///  @fn T6963_dataWriteDecrement
///  @brief Write data at current address, decrement address
///  @param[in] dat The data to write to RAM
////////////////////////////////////////////////////////////////////////////////
void T6963_dataWriteDecrement(uint8_t dat)
{
  wait();
  T6963_writeDataByte(dat);
  wait();
  T6963_writeCommandByte(T6963_DATA_WRITE_DEC);
}

////////////////////////////////////////////////////////////////////////////////
///  @fn T6963_dataWrite
///  @brief  Write data at current address, leave address as is.
///  @param[in] dat The data to write to RAM
///  @return
////////////////////////////////////////////////////////////////////////////////
void T6963_dataWrite(uint8_t dat)
{
  wait();
  T6963_writeDataByte(dat);
  wait();
  T6963_writeCommandByte(T6963_DATA_WRITE_INC);
}

////////////////////////////////////////////////////////////////////////////////
///  @fn T6963_dataReadIncrement
///  @brief  Read data from current address, increment address
///  @return  The byte read from RAM
////////////////////////////////////////////////////////////////////////////////
uint8_t T6963_dataReadIncrement()
{
  uint8_t rtn = 0;
  wait();
  T6963_writeCommandByte(T6963_DATA_READ_INC);
  wait();
 // TODO rtn =T6963_readDataByte();
  return rtn;
}

////////////////////////////////////////////////////////////////////////////////
///  @fn T6963_dataReadDecrement
///  @brief Read Data from current address, decrement address
///  @return The byte read from RAM
////////////////////////////////////////////////////////////////////////////////
uint8_t T6963_dataReadDecrement()
{
  uint8_t rtn = 0;
  wait();
  T6963_writeCommandByte(T6963_DATA_READ_DEC);
  wait();
 // TODO rtn =T6963_readDataByte();
  return rtn;
}

////////////////////////////////////////////////////////////////////////////////
///  @fn T6963_dataRead
///  @brief Read byte from current address, leave address as is.
///  @return The byte read from RAM
////////////////////////////////////////////////////////////////////////////////
uint8_t T6963_dataRead()
{
  uint8_t rtn = 0;
  wait();
  T6963_writeCommandByte(T6963_DATA_READ);
  wait();
 // TODO rtn =T6963_readDataByte();
  return rtn;
}

////////////////////////////////////////////////////////////////////////////////
///  @fn T6963_screenPeek
///  @brief  Read display byte from screen, using address pointer to graphics.
///  @return Byte read from screen.
////////////////////////////////////////////////////////////////////////////////
uint8_t T6963_screenPeek()
{
  uint8_t rtn = 0;
  wait();
  T6963_writeCommandByte(T6963_SCREEN_PEEK);
  wait();
 // TODO rtn =T6963_readDataByte();
  return rtn;
}

////////////////////////////////////////////////////////////////////////////////
///  @fn T6963_screenCopy
///  @brief Copy one row of screen to graphics area
////////////////////////////////////////////////////////////////////////////////
void T6963_screenCopy()
{
  wait();
  T6963_writeCommandByte(T6963_SCREEN_COPY);
  wait();
 // TODO rtn =T6963_readDataByte();
}


#define T6963_SET_RESET                   0xf0     // Set/reset - add codes
#define T6963_SET                         0xf8     // Set any bit (add bit #)

////////////////////////////////////////////////////////////////////////////////
///  @fn T6963_setBit
///  @brief  Set a single bit at location in address pointer.
///  @param[in] b Bit number to set in byte (0 to 7)
////////////////////////////////////////////////////////////////////////////////
void T6963_setBit(uint8_t b)
{
  if(b < 8)
  {
    wait();
    T6963_writeCommandByte(T6963_SET | b);
  }
}

////////////////////////////////////////////////////////////////////////////////
///  @fn T6963_resetBit
///  @brief  Clear a single bit at location in addrss pointer
///  @param[in] b Bit number to clear in byte (0 to 7)
///  @return
////////////////////////////////////////////////////////////////////////////////
void T6963_resetBit(uint8_t b)
{
  if(b < 8)
  {
    wait();
    T6963_writeCommandByte(T6963_RESET | b);
  }
}






////////////////////////////////////////////////////////////////////////////////
///  @fn ports_init
///  @brief
///  @param[]
///  @return
////////////////////////////////////////////////////////////////////////////////

void setup() 
{
  // put your setup code here, to run once:
  delay(100);
  ports_init();
  T6963_setAddress(0);
  T6963_setCursor(0,0);
  T6963_setTextHomeAddress(0);
  T6963_setGraphicHomeAddress(2000);
  T6963_setDisplayMode(1,1,1,1);  // text, graphics, cursor, blink
 // T6963_setAddress(0);
  T6963_setTextArea(40);
  T6963_setGraphicArea(40);
  T6963_setOrMode(0);
  delay(100);
  for(int i = 0; i < 800; i++)
  {
    T6963_dataWriteIncrement(0);
  }
  T6963_setAddress(0);
  T6963_setAutoWrite();
  for(int i = 2000; i < 4000; i++)
  {
    T6963_writeDataByte(0);
  }
  T6963_setAutoReset();
  
  T6963_setAddress(0);
  for(uint8_t i = 0; i < 128; i++)
  {
    T6963_dataWriteIncrement(i);
  }
  for(uint8_t i = 0; i < 128; i++)
  {
    T6963_dataWriteIncrement(128-i);
  }
  delay(500);

  T6963_setAddress(0);
  T6963_setAutoWrite();
  for(int i = 0; i < 320; i++)
  {
    T6963_writeDataByte(0);  // space, clear screen
  }
  T6963_setAutoReset();
  delay(500);
  
  T6963_setAddress(0);
  T6963_setAutoWrite();
  for(int i = 0; i < 320; i++)
  {
    T6963_writeDataByte( (uint8_t) (i & 0x7f) );
  }
  T6963_setAutoReset();
  delay(2000);
  T6963_setAddress(2000);
  T6963_setAutoWrite();
  for(int i = 2000; i < 4000; i++)
  {
    T6963_writeDataByte( 0x55);
  }
  T6963_setAutoReset();
  
 

}

////////////////////////////////////////////////////////////////////////////////
///  @fn ports_init
///  @brief
///  @param[]
///  @return
////////////////////////////////////////////////////////////////////////////////

void loop() 
{
  // put your main code here, to run repeatedly:

}
