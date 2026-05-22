#include <Adafruit_LiquidCrystal.h>

// NOTA:
// estamos usando a biblioteca Adafruit pois o <LiquidCrystal_I2C.h> não estava funcionando 

Adafruit_LiquidCrystal lcd(0);

// definição dos pinos
const int pinoTemp = A0;
const int pinoPot = A1;
const int pinoLed = 8;

// definição dos limites críticos
const float limiteTemp = 40.0;
const int limitePot = 800;

void setup() {
  // inicialização das comunicações (UART E I2C)
  Serial.begin(115200);
  
  lcd.begin(16, 2);
  lcd.setBacklight(1);
  
  pinMode(pinoLed, OUTPUT);
  
  lcd.setCursor(0, 0);
  lcd.print("Hub Industrial");
  delay(2000);
  lcd.clear();
}

void loop() {
  // camada de percepção
  int leituraTempRaw = analogRead(pinoTemp);
  float tensao = leituraTempRaw * (5.0 / 1024.0);
  float temperaturaC = (tensao - 0.5) * 100.0;
  
  int leituraPot = analogRead(pinoPot);

  // transmissão UART (Monitor Serial)
  Serial.print("Temp: ");
  Serial.print(temperaturaC);
  Serial.print(" C | Pressao: ");
  Serial.println(leituraPot);

  // lógica cyber-física
  if (temperaturaC > limiteTemp || leituraPot > limitePot) {
    digitalWrite(pinoLed, HIGH); 
    
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("ALERTA!");
    delay(500); 
    lcd.clear();
    delay(500); 
    
  } else {
    digitalWrite(pinoLed, LOW); 
    
    lcd.setCursor(0, 0);
    lcd.print("T: ");
    lcd.print(temperaturaC);
    lcd.print(" C   ");
    
    lcd.setCursor(0, 1);
    lcd.print("P: ");
    lcd.print(leituraPot);
    lcd.print("      ");
    
    delay(500); 
  }
}