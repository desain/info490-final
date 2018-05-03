#include <CapacitiveSensor.h> //https://github.com/PaulStoffregen/CapacitiveSensor
#include <LiquidCrystal_I2C.h> //https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads/


int const sensorOutput = 4;
int const sensorInput = 8;
CapacitiveSensor touchSensor{sensorOutput, sensorInput};
int const touchSensorSamples = 30;
int const threshold = 1000;

LiquidCrystal_I2C lcd(0x3f, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16,1);
  lcd.home();
  lcd.clear();
  lcd.noBlink();
  lcd.noCursor();
  lcd.display();
  lcd.setCursor(16,1);
  lcd.autoscroll();
  Serial.println("up");
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.print(touchSensor.capacitiveSensor(touchSensorSamples));
  lcd.print(';');
  delay(1000);
}
