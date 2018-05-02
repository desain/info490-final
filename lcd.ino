#include <LiquidCrystal_I2C.h>

//LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
LiquidCrystal_I2C lcd(0x3F);

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  lcd.clear();
  lcd.print("HI");
}

void loop() {
  // put your main code here, to run repeatedly:
}
