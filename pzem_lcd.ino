#if 1
#include <string.h>
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include <TouchScreen.h>
#define MINPRESSURE 200
#define MAXPRESSURE 1000
#include <PZEM004Tv30.h>
#define BLACK   0x0000
#define RED     0xF800
#define GREEN   0x07E0
#define WHITE   0xFFFF
#define GREY    0x8410
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSerif12pt7b.h>

#include <FreeDefaultFonts.h>

// ALL Touch panels and wiring is DIFFERENT
// copy-paste results from TouchScreen_Calibr_native.ino
//const int XP = 6, XM = A2, YP = A1, YM = 7; //ID=0x9341
//const int TS_LEFT = 907, TS_RT = 136, TS_TOP = 942, TS_BOT = 139;

const int XP = 6, XM = A2, YP = A1, YM = 7; //ID=0x9341
const int TS_LEFT = 907, TS_RT = 136, TS_TOP = 942, TS_BOT = 139;
int option = 1;

PZEM004Tv30 pzem(&Serial1);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Adafruit_GFX_Button on_btn, off_btn;

int pixel_x, pixel_y;     //Touch_getXY() updates global vars
bool Touch_getXY(void)
{
    TSPoint p = ts.getPoint();
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);   //because TFT control pins
    digitalWrite(XM, HIGH);
    bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
    if (pressed) {
        pixel_x = map(p.y, 954, 169, 0, 480); //.kbv makes sense to me
        pixel_y = map(p.x, 170, 938, 0, 320);
    }
    return pressed;
}


void setup(void)
{
    Serial.begin(9600);
    //pzem.resetEnergy();
    uint16_t ID = tft.readID();
    Serial.print("TFT ID = 0x");
    Serial.println(ID, HEX);
    Serial.println("Calibrate for your Touch Panel");
    if (ID == 0xD3D3) ID = 0x9486; // write-only shield
    tft.begin(ID);
    tft.setRotation(1);            //PORTRAIT
    
    delay(100);
    tft.fillScreen(BLACK);
    tft.setTextColor(CYAN, BLACK);
    tft.setTextSize(4);
    tft.setCursor(100,145);   
    tft.print("Arduitronics");
    tft.setTextSize(2);
    tft.setCursor(220,300); 
    tft.setTextColor(RED, BLACK);  
    tft.print("Copy right reserved!!");
    delay(4000);
    tft.fillScreen(BLACK);

    on_btn.initButton(&tft,  310, 290, 100, 40, WHITE, CYAN, BLACK, "Reset", 2);
    off_btn.initButton(&tft, 420, 290, 100, 40, WHITE, CYAN, BLACK, "Next", 2);
    on_btn.drawButton(false);
    off_btn.drawButton(false);
    //tft.fillRect(350, 30, 50, 40, RED); 
}

/* two buttons are quite simple
 */
void loop(void)
{
  //tft.fillScreen(BLACK);
  float voltage = pzem.voltage();
  float current = pzem.current();
  float power = pzem.power();
  float energy = pzem.energy();
  float frequency = pzem.frequency();
  float pf = pzem.pf();
  

  int movex = 180;
  if (option == 1){
      off_btn.initButton(&tft, 420, 290, 100, 40, WHITE, CYAN, BLACK, "Next", 2);
      on_btn.initButton(&tft,  310, 290, 100, 40, WHITE, CYAN, BLACK, "Reset", 2);
      //tft.fillScreen(BLACK);
      tft.setTextColor(CYAN, BLACK);
      tft.setTextSize(2);
      tft.setCursor(5,290);
      tft.print("www.arduitronics.com");
    
      tft.setTextColor(GREEN, BLACK);
      tft.setTextSize(3);
      tft.setCursor(5,30);
      tft.print("Energy");
      tft.setTextSize(6);
      tft.setCursor(5+movex, 10);
      tft.print(energy);
      tft.setTextSize(3);
      tft.setCursor(190+movex, 30);
      tft.print("kWh");
      
      tft.setTextSize(3);
      tft.setCursor(5,90);
      tft.print("Power");
      tft.setTextSize(6);
      tft.setCursor(5+movex, 70);
      tft.print(power);
      tft.setTextSize(3);
      tft.setCursor(230+movex, 90);
      tft.print("W"); 
     
      tft.setTextSize(3);
      tft.setCursor(5,150);
      tft.print("Voltage");
      tft.setTextSize(6);
      tft.setCursor(5+movex, 130);
      tft.print(voltage);
      tft.setTextSize(3);
      tft.setCursor(230+movex, 150);
      tft.print("V"); 
    
      tft.setTextSize(3);
      tft.setCursor(5,210);
      tft.print("Current");
      tft.setTextSize(6);
      tft.setCursor(5+movex, 190);
      tft.print(current);
      tft.setTextSize(3);
      tft.setCursor(230+movex, 210);
      tft.print("A"); 
  }
  else if(option ==2){
       off_btn.initButton(&tft, 420, 290, 100, 40, WHITE, CYAN, BLACK, "Back", 2);
       on_btn.initButton(&tft,  310, 290, 100, 40, WHITE, CYAN, BLACK, "Reset", 2);
       tft.setTextColor(CYAN, BLACK);
       tft.setTextSize(2);
       tft.setCursor(5,290);
       tft.print("www.arduitronics.com");
      
       tft.setTextColor(GREEN, BLACK);
       tft.setTextSize(3);
       tft.setCursor(5,30);
       tft.setTextSize(3);
       tft.print("Frequency");
       tft.setTextSize(6);
       tft.setCursor(5+movex, 10);
       tft.print(frequency);
       tft.setTextSize(3);
       tft.setCursor(190+movex, 30);
       tft.print("Hz");
       
       tft.setTextSize(3);
       tft.setCursor(5,95);
       tft.print("PF");
       tft.setTextSize(6);
       tft.setCursor(5+movex, 70);
       tft.print(pf);     
 }
   bool down = Touch_getXY();
   off_btn.press(down && off_btn.contains(pixel_x, pixel_y));
   if (off_btn.justReleased())
       off_btn.drawButton();
       on_btn.drawButton();

   if (off_btn.justPressed()) {
       tft.fillScreen(BLACK);
       off_btn.drawButton(true); 
       
       if (option ==1){
        option = 2;
       }
       else{
        option = 1;
       }   
   }
   on_btn.press(down && on_btn.contains(pixel_x, pixel_y));
   if (on_btn.justReleased())
      on_btn.drawButton();
      off_btn.drawButton();
      
   if (on_btn.justPressed()){
      tft.fillScreen(BLACK);
      tft.setTextColor(CYAN, BLACK);
      tft.setTextSize(4);
      tft.setCursor(100,145);   
      tft.print("Reset Energy");
      delay(2000);
      Serial.println("Reset Energy");
      pzem.resetEnergy();
      tft.fillScreen(BLACK);
      
   }
   
    delay(1000);
}
#endif
