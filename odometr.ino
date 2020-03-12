
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <avr/eeprom.h>
#include <OneWire.h>
OneWire ds(8);//объект onewire для датчика ds18b20


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels


#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);  //дисплей обновляется быстрее!!!!!!!
volatile int counterImpuls=0;
volatile unsigned long counterImpuls_forSpeed=0;
unsigned long counterImpuls_forSpeed_last=0;
unsigned long lastTime=0;
unsigned long lastTime_1=0;
unsigned long last_press=0;
unsigned long timer_eeprom=0;
unsigned long last_time_temp=0; 
float speed_1=0;
float probeg[3] {0, 0, 0};//{259741, 693, 6500};
 //1 osn_rasstoyanie=259741;
 //2 sut_rasstoyanie=693;
 //3 to_rasstoyanie=6500;
unsigned int sw_i=1;//(schetchik knopki disp);
unsigned int value=0;//(schetchik knopki dlya sbrosa probega)
boolean button_flag=0;
boolean button;
byte schet;
int temp=0;
boolean fool_odo=false;
boolean fool_day=false;
boolean fool_speed=false;
boolean fool_to=false;
boolean fool_temp=false;

/////////////////////////////void_setup/////////////////////
void setup() {
  eeprom_read_block((void*)&probeg, 0, sizeof(probeg));
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP); //датчик скорости
  attachInterrupt(0, impuls, RISING);
//////////////////////////////setup dlya obrabotki botton
pinMode(A2, INPUT_PULLUP);//knopka
pinMode(A1, INPUT);//падение напряжения на этом пине активирует запись массива пробегов в EEPROM

logo_renault();
delay(3000);
display.clearDisplay();
disp_1();
disp_odo_line();
}
/////////////////////////////температурка
int temperature()
{
   byte data[2];
  ds.reset();
  ds.write(0xCC);
  ds.write(0x44);
  if (millis() - last_time_temp > 5000)
  {
    last_time_temp = millis();
    ds.reset();
    ds.write(0xCC);
    ds.write(0xBE);
    data[0] = ds.read();
    data[1] = ds.read();
    // Формируем значение
    temp = (data[1] << 8) + data[0]; temp = temp >> 4;
  }
}
////////////////////////////////LOGO renault/////////////////////////////////////////////////////////
void logo_renault() {
  int16_t i;
  int16_t n_x;
  int16_t k_x;
  int16_t n_y;
  int16_t k_y;
   n_x=24;//23
   n_y=17;
   k_x=16;//15
   k_y=32;
  display.clearDisplay(); // Clear display buffer
  /////////////////////////право низ
  for(i=0; i<=7; i++) {
    display.drawLine(n_x-=1, n_y, k_x-=1, k_y, SSD1306_WHITE);
    display.display(); 
    delay(70);
  }
   n_x=16;//15
   n_y=32;
   k_x=8;//7
   k_y=17;
   ///////////////////////лево низ
  for(i=0; i<=7; i++) {
    display.drawLine(n_x-=1, n_y, k_x-=1, k_y, SSD1306_WHITE);
    display.display(); 
    delay(70);
  }
  ////////////////////////лево верх и внутрянка
  byte x=1;
  byte y=17;
  byte x_2=12;
  byte y_2=7;
  
  for(byte i=0; i<8; i++)
  {
    for(byte j=0; j<2; j++)
    {
         display.drawPixel(x, y, SSD1306_WHITE);
         if(y_2<=16)
         {
         display.drawPixel(x_2, y_2, SSD1306_WHITE);
         }
         display.display(); 
         y--;
         if(y_2<16)
         {
         y_2++;
         }
    }
    x++;
    if(x_2>7)
    {
    x_2--;
    }
   }
////////////////////////верх
for(byte y=1; y==1; y++)
{
  for(byte x=9; x<=15; x++)
  {
    display.drawPixel(x, y, SSD1306_WHITE);
    display.display();
  }
}
   /////////////////////право верх
   byte x_1=16;
  byte y_1=2;
  byte x_3=17;
  byte y_3=17;
  for(byte i=0; i<8; i++)
  {
    for(byte j=0; j<2; j++)
    {
         display.drawPixel(x_1, y_1, SSD1306_WHITE);
         if(y_3>=8)
         {
         display.drawPixel(x_3, y_3, SSD1306_WHITE);
         }
         display.display(); 
         y_1++;
          if(y_3>8)
         {
         y_3--;
         }
    }
    x_1++;
    if(x_3>13)
    {
    x_3--;
    }
   }     
////////////////////////renault
byte r=128;
byte e=128;
byte n=128;
byte a=128;
byte u=128;
byte l=128;
byte t=128;
byte xl_line=75;
byte xr_line=75;
long time_line=0;
byte pz=32;
byte az=32;
byte sz=32;
byte s1z=32;
byte iz=32;
byte oz=32;
byte nz=32;
byte fz=32;
byte o1z=32;
byte rz=32;
byte lz=32;
byte i1z=32;
byte f1z=32;
byte ez=32;
    for(int x=0; t>117; x++)
    {
      if(xr_line<125 && millis()-time_line>25)
      {
      display.drawPixel(xl_line, 17, SSD1306_WHITE);
      display.drawPixel(xl_line, 18, SSD1306_WHITE);
      display.drawPixel(xr_line, 17, SSD1306_WHITE);
      display.drawPixel(xr_line, 18, SSD1306_WHITE);
      xl_line--;
      xr_line++;
      time_line=millis();
      }
      if(r>=29)
      {
      display.drawChar (r, 1, 'R', 1, 0, 2);
      r--;
      }
      if(r<80 && e>=44)
      {
      display.drawChar (e, 1, 'E', 1, 0, 2);
      e--;
      }
      if(r<40 && n>=59)
      {
      display.drawChar (n, 1, 'N', 1, 0, 2);
      n--;
      }
      if(n<88 && a>=74)
      {
      display.drawChar (a, 1, 'A', 1, 0, 2);
      a--;
      }
      if(a<90 && u>=89)
      {
      display.drawChar (u, 1, 'U', 1, 0, 2);
      u--;
      }
      if(u<100 && l>=104)
      {
      display.drawChar (l, 1, 'L', 1, 0, 2);
      l--;
      }
      if(l<110 && t>=118)
      {
      display.drawChar (t, 1, 'T', 1, 0, 2);
      t--;
      }
      //////////passion for life
      if(xr_line==125)
      {
        if(pz>=24)
        {
         display.drawChar (31, pz, 'P', 1, 0, 1);//шаг мелкого символа 5 пикселей
         pz--;
        }
        if(pz==23 && az>=24)
        {
         display.drawChar (37, az, 'A', 1, 0, 1);//шаг мелкого символа 5 пикселей
         az--;
        }
        if(az==23 && sz>=24)
        {
         display.drawChar (43, sz, 'S', 1, 0, 1);//шаг мелкого символа 5 пикселей
         sz--;
        }
        if(sz==23 && s1z>=24)
        {
         display.drawChar (49, s1z, 'S', 1, 0, 1);//шаг мелкого символа 5 пикселей
         s1z--;
        }
         if(s1z==23 && iz>=24)
        {
         display.drawChar (55, iz, 'I', 1, 0, 1);//шаг мелкого символа 5 пикселей
         iz--;
        }
        if(iz==23 && oz>=24)
        {
         display.drawChar (61, oz, 'O', 1, 0, 1);//шаг мелкого символа 5 пикселей
         oz--;
        }
        if(oz==23 && nz>=24)
        {
         display.drawChar (67, nz, 'N', 1, 0, 1);//шаг мелкого символа 5 пикселей
         nz--;
        }
        if(nz==23 && fz>=24)
        {
         display.drawChar (76, fz, 'F', 1, 0, 1);//шаг мелкого символа 5 пикселей
         fz--;
        }
        if(fz==23 && o1z>=24)
        {
         display.drawChar (82, o1z, 'O', 1, 0, 1);//шаг мелкого символа 5 пикселей
         o1z--;
        }
         if(o1z==23 && rz>=24)
        {
         display.drawChar (88, rz, 'R', 1, 0, 1);//шаг мелкого символа 5 пикселей
         rz--;
        }
        if(rz==23 && lz>=24)
        {
         display.drawChar (97, lz, 'L', 1, 0, 1);//шаг мелкого символа 5 пикселей
         lz--;
        }
        if(lz==23 && i1z>=24)
        {
         display.drawChar (103, i1z, 'I', 1, 0, 1);//шаг мелкого символа 5 пикселей
         i1z--;
        }
        if(i1z==23 && f1z>=24)
        {
         display.drawChar (109, f1z, 'F', 1, 0, 1);//шаг мелкого символа 5 пикселей
         f1z--;
        }
        if(f1z==23 && ez>=24)
        {
         display.drawChar (115, ez, 'E', 1, 0, 1);//шаг мелкого символа 5 пикселей
         ez--;
        }
      }
        display.display();
    }
}
////////////////////////////наматывает пробег///////////////////////////////////////////////////////////////
void impuls(){
//probeg
  counterImpuls++;
  counterImpuls_forSpeed++;
  if (counterImpuls%60==0)
    {
      probeg[1]+=0.01;
    }
  if (counterImpuls==600)
  { 
    probeg[0]+=0.1;
    probeg[2]-=0.1;
    counterImpuls=0;
  }
}
///////////////////////////////вывод на дисплей//////////////////////////////////////////////////////////////
void disp_1()
{
  //верхняя панель
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(5,4);// гориз\\верт
    display.print("ALL");
    display.display();
    delay(200);
    ///////////////////////
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(27,4);// гориз\\верт
    display.print("DAY");
    display.display();
    delay(200);
    ///////////////////////
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(49,4);// гориз\\верт
    display.print("SPEED");
    display.display();
    delay(200);
    ///////////////////////
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(83,4);// гориз\\верт
    display.print("TO");
    display.display();
    delay(200);
    ///////////////////////
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(99,4);// гориз\\верт
    display.print("TEMP");
    display.display();
    delay(200);
}
void disp_2()
{
  //верхняя панель
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(5,4);// гориз\\верт
    display.print("ALL");
  //  display.display();
    
    ///////////////////////
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(27,4);// гориз\\верт
    display.print("DAY");
 //   display.display();
    
    ///////////////////////
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(49,4);// гориз\\верт
    display.print("SPEED");
  //  display.display();
    
    ///////////////////////
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(83,4);// гориз\\верт
    display.print("TO");
  //  display.display();
    
    ///////////////////////
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(99,4);// гориз\\верт
    display.print("TEMP");
   // display.display();
    
}
///////////////////////////отрисовка линий
void disp_odo_line()
{
    byte v1_line=4;
    byte h1_line=3;
    display.drawPixel(3, 2, SSD1306_WHITE);//поворот
       for(byte x=0; v1_line<=22; x++)
       {
        display.drawPixel(v1_line, 1, SSD1306_WHITE);//гориз\\верт
        display.drawPixel(2, h1_line, SSD1306_WHITE);//гориз\\верт
        v1_line++;
        h1_line++;
        display.display();
       }
       display.drawPixel(23, 2, SSD1306_WHITE);//поворот
       v1_line=3;
       for(byte x=0; v1_line<=11; x++)
       {
        display.drawPixel(24, v1_line, SSD1306_WHITE);
        if(h1_line<=32)
        {
         display.drawPixel(2, h1_line, SSD1306_WHITE);
         h1_line++;
        }
        v1_line++;
        display.display();
       }
       display.drawPixel(25, 12, SSD1306_WHITE);//поворот
       v1_line=26;
       for(byte x=0; v1_line<=125; x++)
       {
        display.drawPixel(v1_line, 13, SSD1306_WHITE);
        v1_line++;
        display.display();
       }
       display.drawPixel(126, 14, SSD1306_WHITE);//поворот
       v1_line=15;
        for(byte x=0; v1_line<=32; x++)
       {
        display.drawPixel(127, v1_line, SSD1306_WHITE);
        v1_line++;
        display.display();
       }
}
///////////////////day_line
void disp_day_line()
{
    byte r_line=35;
    byte l_line=35;
    byte l1_line=15;
       for(byte x=0; r_line<=44; x++)
       {
        display.drawPixel(r_line, 1, SSD1306_WHITE);//гориз\\верт
        display.drawPixel(l_line, 1, SSD1306_WHITE);//гориз\\верт
        r_line++;
        l_line--;
        display.display();
       }
       display.drawPixel(45, 2, SSD1306_WHITE);//поворот
       display.drawPixel(25, 2, SSD1306_WHITE);//поворот
       r_line=3;
       l_line=3;
       for(byte x=0; l_line<=11; x++)
       {
        display.drawPixel(24, r_line, SSD1306_WHITE);
        display.drawPixel(46, l_line, SSD1306_WHITE);
        r_line++;
        l_line++;
        display.display();
       }
       display.drawPixel(23, 12, SSD1306_WHITE);//поворот
       display.drawPixel(47, 12, SSD1306_WHITE);//поворот
       r_line=48;
       l_line=22;
       for(byte x=0; r_line<=125; x++)
       {
        display.drawPixel(r_line, 13, SSD1306_WHITE);
        if(l_line>=3)
        {
         display.drawPixel(l_line, 13, SSD1306_WHITE);//tut
         l_line--;
        }
        if(l_line==2)
        {
          display.drawPixel(2, 14, SSD1306_WHITE);//поворот
          l_line=1;
        }
        if(l_line==1 && l1_line<=32)
        {
          display.drawPixel(1, l1_line, SSD1306_WHITE);
          l1_line++;
        }
        r_line++;
        display.display();
       }
        display.drawPixel(126, 14, SSD1306_WHITE);//поворот
       r_line=15;
       for(byte x=0; r_line<=32; x++)
       {
        display.drawPixel(127, r_line, SSD1306_WHITE);
       r_line++;
       display.display();
       }
}
///////////////speed
void disp_speed_line()
{
    byte r_line=63;
    byte l_line=63;

       for(byte x=0; r_line<=78; x++)
       {
        display.drawPixel(r_line, 1, SSD1306_WHITE);//гориз\\верт
        display.drawPixel(l_line, 1, SSD1306_WHITE);//гориз\\верт
        r_line++;
        l_line--;
        display.display();
       }
       display.drawPixel(47, 2, SSD1306_WHITE);//поворот
       display.drawPixel(79, 2, SSD1306_WHITE);//поворот
       r_line=3;
       l_line=3;
       for(byte x=0; l_line<=11; x++)
       {
        display.drawPixel(80, r_line, SSD1306_WHITE);
        display.drawPixel(46, l_line, SSD1306_WHITE);
        r_line++;
        l_line++;
        display.display();
       }
       display.drawPixel(45, 12, SSD1306_WHITE);//поворот
       display.drawPixel(81, 12, SSD1306_WHITE);//поворот
       r_line=82;
       l_line=44;
       for(byte x=0; r_line<=125; x++)
       {
        display.drawPixel(r_line, 13, SSD1306_WHITE);//гориз\\верт
        if(l_line>=3)
        {
         display.drawPixel(l_line, 13, SSD1306_WHITE);//гориз\\верт
         l_line--;
        }
        r_line++;
        display.display();
       }
       display.drawPixel(2, 14, SSD1306_WHITE);//поворот
       display.drawPixel(126, 14, SSD1306_WHITE);//поворот
       r_line=15;
       l_line=15;
      for(byte x=0; r_line<=32; x++)
       {
        display.drawPixel(127, r_line, SSD1306_WHITE);
        display.drawPixel(1, l_line, SSD1306_WHITE);
        r_line++;
        l_line++;
        display.display();
       }    
}
///////////////TO
void disp_to_line()
{
    byte r_line=88;
    byte l_line=88;
    byte l1_line=15;
       for(byte x=0; r_line<=94; x++)
       {
        display.drawPixel(r_line, 1, SSD1306_WHITE);//гориз\\верт    //1
        display.drawPixel(l_line, 1, SSD1306_WHITE);//гориз\\верт
        r_line++;
        l_line--;
        display.display();
       }
       display.drawPixel(81, 2, SSD1306_WHITE);//поворот
       display.drawPixel(95, 2, SSD1306_WHITE);//поворот
       r_line=3;
       l_line=3;
       for(byte x=0; l_line<=11; x++)
       {
        display.drawPixel(96, r_line, SSD1306_WHITE);      //2
        display.drawPixel(80, l_line, SSD1306_WHITE);
        r_line++;
        l_line++;
        display.display();
       }
       display.drawPixel(79, 12, SSD1306_WHITE);//поворот
       display.drawPixel(97, 12, SSD1306_WHITE);//поворот
       ///////////////////////////////////////
       r_line=98;
       l_line=78;
       for(byte x=0; l_line>=3; x++)
       {
        display.drawPixel(l_line, 13, SSD1306_WHITE);
        if(r_line<=125)
        {
         display.drawPixel(r_line, 13, SSD1306_WHITE);//tut   //3
         r_line++;
        }
        if(r_line==126)
        {
          display.drawPixel(126, 14, SSD1306_WHITE);//поворот
          r_line=129;
        }
        if(r_line==129 && l1_line<=32)
        {
          display.drawPixel(127, l1_line, SSD1306_WHITE);
          l1_line++;
       }
        l_line--;
        display.display();
       }
        display.drawPixel(2, 14, SSD1306_WHITE);//поворот
       l_line=15;
       for(byte x=0; l_line<=32; x++)
       {
        display.drawPixel(1, l_line, SSD1306_WHITE);
       l_line++;
       display.display();
       }
}
///////////////temp
void disp_temp_line()
{
    byte l_line=125;
    byte r_line=3;
    display.drawPixel(126, 2, SSD1306_WHITE);//поворот
       for(byte x=0; l_line>=98; x++)
       {
        display.drawPixel(l_line, 1, SSD1306_WHITE);//гориз\\верт
        display.drawPixel(127, r_line, SSD1306_WHITE);//гориз\\верт
        l_line--;
        r_line++;
        display.display();
       }
       display.drawPixel(97, 2, SSD1306_WHITE);//поворот
       l_line=3;
       for(byte x=0; l_line<=11; x++)
       {
        display.drawPixel(96, l_line, SSD1306_WHITE);
        if(r_line<=32)
        {
         display.drawPixel(127, r_line, SSD1306_WHITE);
         r_line++;
        }
        l_line++;
        display.display();
       }
       display.drawPixel(95, 12, SSD1306_WHITE);//поворот
       l_line=94;
       for(byte x=0; l_line>=3; x++)
       {
        display.drawPixel(l_line, 13, SSD1306_WHITE);
        l_line--;
        display.display();
       }
       display.drawPixel(2, 14, SSD1306_WHITE);//поворот
       l_line=15;
        for(byte x=0; l_line<=32; x++)
       {
        display.drawPixel(1, l_line, SSD1306_WHITE);
        l_line++;
        display.display();
       }
}
///////////////odo static
void disp_odo_line_static()
{
  display.drawPixel(3, 2, SSD1306_WHITE);//поворот
  display.drawLine(2, 3, 2, 32, SSD1306_WHITE);//гориз\\верт
  display.drawLine(4, 1, 22, 1, SSD1306_WHITE);//гориз\\верт
  display.drawPixel(23, 2, SSD1306_WHITE);//поворот
  display.drawLine(24, 3, 24, 11, SSD1306_WHITE);//гориз\\верт
  display.drawPixel(25, 12, SSD1306_WHITE);//поворот
  display.drawLine(26, 13, 125, 13, SSD1306_WHITE);//гориз\\верт
  display.drawPixel(126, 14, SSD1306_WHITE);//поворот
  display.drawLine(127, 15, 127, 32, SSD1306_WHITE);//гориз\\верт
}
//////////////day static
void disp_day_line_static()
{
  display.drawLine(26, 1, 44, 1, SSD1306_WHITE);//гориз\\верт
  display.drawPixel(25, 2, SSD1306_WHITE);//поворот
  display.drawPixel(45, 2, SSD1306_WHITE);//поворот
  display.drawLine(24, 3, 24, 11, SSD1306_WHITE);//гориз\\верт
  display.drawLine(46, 3, 46, 11, SSD1306_WHITE);//гориз\\верт
  display.drawPixel(23, 12, SSD1306_WHITE);//поворот
  display.drawPixel(47, 12, SSD1306_WHITE);//поворот//////////////////////////////проверить
  display.drawLine(22, 13, 3, 13, SSD1306_WHITE);//гориз\\верт
  display.drawLine(48, 13, 125, 13, SSD1306_WHITE);//гориз\\верт
  display.drawPixel(2, 14, SSD1306_WHITE);//поворот
  display.drawPixel(126, 14, SSD1306_WHITE);//поворот
  display.drawLine(1, 15, 1, 32, SSD1306_WHITE);//гориз\\верт
  display.drawLine(127, 15, 127, 32, SSD1306_WHITE);//гориз\\верт
}
//////////////speed static
void disp_speed_line_static()
{
  display.drawLine(48, 1, 78, 1, SSD1306_WHITE);//гориз\\верт
  display.drawPixel(47, 2, SSD1306_WHITE);//поворот
  display.drawPixel(79, 2, SSD1306_WHITE);//поворот
  display.drawLine(46, 3, 46, 11, SSD1306_WHITE);//гориз\\верт
  display.drawLine(80, 3, 80, 11, SSD1306_WHITE);//гориз\\верт
  display.drawPixel(45, 12, SSD1306_WHITE);//поворот
  display.drawPixel(81, 12, SSD1306_WHITE);//поворот
  display.drawLine(44, 13, 3, 13, SSD1306_WHITE);//гориз\\верт
  display.drawLine(82, 13, 125, 13, SSD1306_WHITE);//гориз\\верт
  display.drawPixel(2, 14, SSD1306_WHITE);//поворот
  display.drawPixel(126, 14, SSD1306_WHITE);//поворот
  display.drawLine(1, 15, 1, 32, SSD1306_WHITE);//гориз\\верт
  display.drawLine(127, 15, 127, 32, SSD1306_WHITE);//гориз\\верт
}
//////////////to static
void disp_to_line_static()
{
  display.drawLine(82, 1, 94, 1, SSD1306_WHITE);//гориз\\верт
  display.drawPixel(81, 2, SSD1306_WHITE);//поворот
  display.drawPixel(95, 2, SSD1306_WHITE);//поворот
  display.drawLine(80, 3, 80, 11, SSD1306_WHITE);//гориз\\верт
  display.drawLine(96, 3, 96, 11, SSD1306_WHITE);//гориз\\верт
  display.drawPixel(79, 12, SSD1306_WHITE);//поворот
  display.drawPixel(97, 12, SSD1306_WHITE);//поворот
  display.drawLine(78, 13, 3, 13, SSD1306_WHITE);//гориз\\верт
  display.drawLine(98, 13, 125, 13, SSD1306_WHITE);//гориз\\верт
  display.drawPixel(2, 14, SSD1306_WHITE);//поворот
  display.drawPixel(126, 14, SSD1306_WHITE);//поворот
  display.drawLine(1, 15, 1, 32, SSD1306_WHITE);//гориз\\верт
  display.drawLine(127, 15, 127, 32, SSD1306_WHITE);//гориз\\верт
}
///////////////temp static
void disp_temp_line_static()
{
  display.drawPixel(126, 2, SSD1306_WHITE);//поворот
  display.drawLine(98, 1, 125, 1, SSD1306_WHITE);//гориз\\верт
  display.drawLine(127, 3, 127, 32, SSD1306_WHITE);//гориз\\верт
  display.drawPixel(97, 2, SSD1306_WHITE);//поворот
  display.drawLine(96, 3, 96, 11, SSD1306_WHITE);//гориз\\верт
  display.drawPixel(95, 12, SSD1306_WHITE);//поворот
  display.drawLine(94, 13, 3, 13, SSD1306_WHITE);//гориз\\верт
  display.drawPixel(2, 14, SSD1306_WHITE);//поворот
  display.drawLine(1, 15, 1, 32, SSD1306_WHITE);//гориз\\верт
}
void disp()
{
  

  switch(sw_i)
  {
    case 1:
    {
    ////////////////////////////////////////////////////probeg;
//    if(fool_temp==false)
//    {
//     fool_temp=true;
//    }
    display.clearDisplay();
    disp_2();
//    if(fool_odo==false)
//   {
      disp_odo_line_static();
//    }
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(28,17);// гориз\\верт
    display.print(probeg[0], 0);
    display.println("km");
    display.display();
//    if(fool_odo==true)
//    {
//     disp_odo_line();
//     fool_odo=false;
//    }
    break;
    }
    case 2:
    {
    //////////////////////////////////////////////////day_probeg;
//    if(fool_odo==false)
//    {
//     fool_odo=true;
//    }
    display.clearDisplay();
    disp_2();
//    if(fool_day==false)
//    {
      disp_day_line_static();
//    }
    display.setTextSize(2);
    display.setTextColor(WHITE);
    if(probeg[1]>=0 && probeg[1]<10)
    {
      display.setCursor(52,17);
    }
    if(probeg[1]>9 && probeg[1]<100)
    {
      display.setCursor(40,17);
    }
    if(probeg[1]>99 && probeg[1]<1000)
    display.setCursor(28,17);
    display.print(probeg[1]);
    display.println("km");
    display.display();
//    if(fool_day==true)
//    {
//     disp_day_line();
//     fool_day=false;
//    }
    break;
    }
    case 3:
    {
    //////////////////////////////////////////////////////////////speed;
//    if(fool_day==false)
//    {
//     fool_day=true;
//    }
    display.clearDisplay();
    disp_2();
//    if(fool_speed==false)
//    {
      disp_speed_line_static();
//    }
    display.setTextSize(2);
    display.setTextColor(WHITE);
    if(speed_1<10 && speed_1>=0)
    {
     display.setCursor(64,17);
    }
    if(speed_1>9 && speed_1<100)
    {
      display.setCursor(52,17);
    }
    if(speed_1>99)
    {
      display.setCursor(40,17);
    }
    display.print(speed_1, 0);
    display.println("km/h");
    display.display();
//    if(fool_speed==true)
//    {
//     disp_speed_line();
//     fool_speed=false;
//   }
    break;
    }
    case 4:
    {
    //////////////////////////////////////////////////////////////////TO;
//    if(fool_speed==false)
//    {
//     fool_speed=true;
//    }
    display.clearDisplay();
    disp_2();
//    if(fool_to==false)
//    {
      disp_to_line_static();
//    }
    //disp_to_line();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    if(probeg[2]>=0 && probeg[2]<10)
    {
      display.setCursor(64,17);
    }
    if(probeg[2]>9 && probeg[2]<100)
    {
      display.setCursor(52,17);
    }
    if(probeg[2]>99 && probeg[2]<1000)
    {
      display.setCursor(40,17);
    }
    if(probeg[2]>999 && probeg[2]<10000)
    {
      display.setCursor(28,17);
    }
    display.print(probeg[2], 1);
    display.println("km");
    display.display();
//    if(fool_to==true)
//    {
//     disp_to_line();
//     fool_to=false;
//    }
    break;
    }
    case 5:
    {
    ///////////////////////////////////////////////////////////////////////temp;
//    if(fool_to==false)
//   {
//     fool_to=true;
//    }
    display.clearDisplay();
    disp_2();
   // if(fool_temp==false)       //условие для анимации линий
   // {
      disp_temp_line_static();
   // }
    
    display.setTextSize(2);
    display.setTextColor(WHITE);
    if(temp>=0 && temp<10)
    {
      display.setCursor(88,17);
    }
    if(temp>10 && temp<100)
    {
      display.setCursor(76,17);
    }
    if(temp<0 && temp>(0-10))
    {
      display.setCursor(76,17);
    }
    if(temp<(0-9) && temp>(0-100))
    {
      display.setCursor(64,17);
    }
    display.print(temp);
    display.println("`C");
    display.display();
   // if(fool_temp==true)
   // {
   //  disp_temp_line();
   //  fool_temp=false;
   // }
    break;
    
    }  
  }
}
///////////////////////////////////////////сбрасывает суточный пробег//////////////////////////
void   sbros_sut()
    {
      if(button==0) 
      {
        last_press=millis();
      }
      if(button==1 && millis()-last_press>=3000)
      {
        probeg[1]=0;
        button_flag=0;
      }
    }
///////////////////////////////////////////сбрасывает обратный пробег после ТО//////////////////////////
void   sbros_to()
    {
      if(button==0) 
      {
        last_press=millis();
      }
      if(button==1 && millis()-last_press>=3000)
      {
        probeg[2]=7000;
        button_flag=0;
      }
    }
///////////////////////////void_loop////////////////////////////////////////////////////////////////////
void loop() {
temperature();

//счетчик кнопки
button=!digitalRead(A2);
  if(button==1 && button_flag==0) 
    {
      
      button_flag=1;
      
    }
    if(button==0 && button_flag==1)
    {
      
      button_flag=0;
      sw_i++;
    }
    if(sw_i==2)
    {
      sbros_sut();
    }
    if(sw_i==4)
      {
      sbros_to();
      }
  disp();
  if( sw_i==5) sw_i=0;
//////////////////speed
  if (millis()-lastTime>600)
  {
    lastTime=millis();
    speed_1=0.6*counterImpuls_forSpeed;
      if (speed_1<1)
      {
        speed_1=0;
      }
      counterImpuls_forSpeed=0;
  }
     ///запись пробегов в епром если зажигание выключили
     int save_VIN=digitalRead(A1);
     if(save_VIN==0 && millis()-timer_eeprom>=60000)//защита от тысячакратного записывания
     {
     ///////////////////////     eeprom_write_block((void*)&probeg, 0, sizeof(probeg));
      timer_eeprom=millis();
     }
     //при переполнении пробегов сбрасывается на ноль
     if (probeg[0]>=999999)
     {
      probeg[0]=0;
     }
     if(probeg[1]>=9999)
     {
      probeg[1]=0;
     }
}
