#include <LiquidCrystal_I2C.h> https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads/

LiquidCrystal_I2C lcd(0x3f, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 


void setup() {
  Serial.begin(9600);
  lcd.begin(16, 1);
  lcd.home();
  lcd.clear();
  lcd.noBlink();
  lcd.noCursor();
  lcd.display();

  lcd.setCursor(16,1); //have to do this before autoscroll
  lcd.autoscroll();
}

void loop() {
  static int l = 0;
  char c = (char)('a'+l++);
  lcd.print(c);
  delay(333);
  if (l == 26) {
    l = 0;
    lcd.clear();
    lcd.setCursor(16,1);
    delay(666);
  }
}
