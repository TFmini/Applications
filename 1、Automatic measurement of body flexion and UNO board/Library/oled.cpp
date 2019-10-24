#include "Arduino.h"
#include "oled.h"

/*0.91 OLD库文件*/
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 0
Adafruit_SSD1306 display(OLED_RESET);
/*字模*/
/*dist: 30 X 12*/
static const unsigned char PROGMEM dist[] =  {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x07,0x00,0x60,0x00,0x00,0x40,0x00,0x00,0x03,0x00,0x60,0x00,0x00,0xC0,0x00,0x00,
0x03,0x00,0x00,0x00,0x00,0xC0,0x06,0x00,0x0F,0x00,0xE0,0x1F,0x03,0xF0,0x06,0x00,
0x1B,0x00,0x60,0x31,0x80,0xC0,0x00,0x00,0x33,0x00,0x60,0x18,0x00,0xC0,0x00,0x00,
0x33,0x00,0x60,0x0E,0x00,0xC0,0x00,0x00,0x33,0x00,0x60,0x03,0x00,0xC0,0x06,0x00,
0x33,0x00,0x60,0x31,0x80,0xD8,0x06,0x00,0x1D,0x80,0xF0,0x1F,0x00,0x70,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

static const unsigned char PROGMEM W6H12_0[]    =   {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x00,0x31,0x80,
0x31,0x80,0x33,0x80,0x35,0x80,0x35,0x80,0x39,0x80,0x31,0x80,0x31,0x80,0x1F,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static const unsigned char PROGMEM W6H12_1[]    =   {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x00,0x0E,0x00,
0x1E,0x00,0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,0x1F,0x80,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static const unsigned char PROGMEM W6H12_2[]    =   {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x00,0x31,0x80,
0x01,0x80,0x03,0x00,0x06,0x00,0x0C,0x00,0x18,0x00,0x30,0x00,0x31,0x80,0x3F,0x80,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static const unsigned char PROGMEM W6H12_3[]    =   {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x00,0x31,0x80,
0x01,0x80,0x01,0x80,0x0F,0x00,0x01,0x80,0x01,0x80,0x01,0x80,0x31,0x80,0x1F,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static const unsigned char PROGMEM W6H12_4[]    =   {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x07,0x00,
0x0F,0x00,0x1B,0x00,0x33,0x00,0x3F,0x80,0x03,0x00,0x03,0x00,0x03,0x00,0x07,0x80,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static const unsigned char PROGMEM W6H12_5[]    =   {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0x80,0x30,0x00,
0x30,0x00,0x30,0x00,0x3F,0x00,0x03,0x80,0x01,0x80,0x01,0x80,0x31,0x80,0x1F,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static const unsigned char PROGMEM W6H12_6[]    =   {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0E,0x00,0x18,0x00,
0x30,0x00,0x30,0x00,0x3F,0x00,0x31,0x80,0x31,0x80,0x31,0x80,0x31,0x80,0x1F,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static const unsigned char PROGMEM W6H12_7[]    =   {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0x80,0x31,0x80,
0x01,0x80,0x01,0x80,0x03,0x00,0x06,0x00,0x0C,0x00,0x0C,0x00,0x0C,0x00,0x0C,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static const unsigned char PROGMEM W6H12_8[]    =   {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x00,0x31,0x80,
0x31,0x80,0x31,0x80,0x1F,0x00,0x31,0x80,0x31,0x80,0x31,0x80,0x31,0x80,0x1F,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static const unsigned char PROGMEM W6H12_9[]    =   {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x00,0x31,0x80,
0x31,0x80,0x31,0x80,0x1F,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x03,0x00,0x1E,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static const unsigned char PROGMEM W6H12_neg[]  =   {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static const unsigned char PROGMEM W6H12_cm[]   =   {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x03,0xB0,0x31,0x83,
0xF8,0x30,0x03,0x58,0x30,0x03,0x58,0x30,0x03,0x58,0x31,0x83,0x58,0x1F,0x03,0x58,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

void oled_begin(void)
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // 初始化OLED屏
  display.clearDisplay();
}

void oled_measuring(void)
{
  display.clearDisplay();
  display.drawBitmap(0, 4, dist, 60, 24, 1);
  display.display();
}

void oled_result(int num)
{
  display.clearDisplay();
  display.drawBitmap(0, 4, dist, 60, 24, 1);
  lcd_display(num);
  display.drawBitmap(104, 4, W6H12_cm, 24, 24, 1);
  display.display();
}

void lcd_display(int t)
{
  if(t>=0)
  {
    lcd_display_pos(t);
  }
  if(t<0)
  {
    display.drawBitmap(62, 4, W6H12_neg, 12, 24, 1);
    t=abs(t);
    lcd_display_pos(t);
  }
}
void lcd_display_pos(int t)
{
  int a=t%10;
  int b=t/10;
  if(a==0&&b==0)
  {
    display.drawBitmap(90, 4, W6H12_0, 12, 24, 1);
  }
  if(a!=0||b!=0)
  {
  switch(a)
  {
    case 0 :
      display.drawBitmap(90, 4, W6H12_0, 12, 24, 1);
      break;
    case 1 :
      display.drawBitmap(90, 4, W6H12_1, 12, 24, 1);
      break;
    case 2 :
      display.drawBitmap(90, 4, W6H12_2, 12, 24, 1);
      break;
    case 3 :
      display.drawBitmap(90, 4, W6H12_3, 12, 24, 1);
      break;
    case 4 :
      display.drawBitmap(90, 4, W6H12_4, 12, 24, 1);
      break;
    case 5 :
      display.drawBitmap(90, 4, W6H12_5, 12, 24, 1);
      break;
     case 6 :
      display.drawBitmap(90, 4, W6H12_6, 12, 24, 1);
      break;
    case 7 :
      display.drawBitmap(90, 4, W6H12_7, 12, 24, 1);
      break;
    case 8 :
      display.drawBitmap(90, 4, W6H12_8, 12, 24, 1);
      break;
    case 9 :
      display.drawBitmap(90, 4, W6H12_9, 12, 24, 1);
      break;
  }
  }
  if(a!=0||b!=0)
  {
  switch(b)
  {
    case 0 :
      display.drawBitmap(76, 4, W6H12_0, 12, 24, 1);
      break;
    case 1 :
      display.drawBitmap(76, 4, W6H12_1, 12, 24, 1);
      break;
    case 2 :
      display.drawBitmap(76, 4, W6H12_2, 12, 24, 1);
      break;
    case 3 :
      display.drawBitmap(76, 4, W6H12_3, 12, 24, 1);
      break;
    case 4 :
      display.drawBitmap(76, 4, W6H12_4, 12, 24, 1);
      break;
    case 5 :
      display.drawBitmap(76, 4, W6H12_5, 12, 24, 1);
      break;
    case 6 :
      display.drawBitmap(76, 4, W6H12_6, 12, 24, 1);
      break;
    case 7 :
      display.drawBitmap(76, 4, W6H12_7, 12, 24, 1);
      break;
    case 8 :
      display.drawBitmap(76, 4, W6H12_8, 12, 24, 1);
      break;
    case 9 :
      display.drawBitmap(76, 4, W6H12_9, 12, 24, 1);
      break;
  }
  }
}
