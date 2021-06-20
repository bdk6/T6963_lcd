////////////////////////////////////////////////////////
/// @file T6963_lcd.ino
/// @copy Copyright (C) 2021 Will Cooke
/// @brief Controls 240x64 T6963 display using T6963 (DG-24064-09-S2RB)
////////////////////////////////////////////////////////


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
