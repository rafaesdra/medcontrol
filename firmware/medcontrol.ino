#include <LiquidCrystal.h>
#include <Servo.h>

// LCD: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

Servo servo;

const int servoPin = 9;
const int buzzerPin = 10;
const int ledPin = 8;
const int botaoPin = 7;

// Notas
#define DO 262
#define RE 294
#define MI 330
#define FA 349
#define SOL 392
#define LA 440

void tocarAlerta() {

  int melodia[] = {
    DO, DO, SOL, SOL, LA, LA, SOL,
    FA, FA, MI, MI, RE, RE, DO
  };

  int duracao[] = {
    300, 300, 300, 300, 300, 300, 600,
    300, 300, 300, 300, 300, 300, 600
  };

  for (int i = 0; i < 14; i++) {
    tone(buzzerPin, melodia[i], duracao[i]);
    delay(duracao[i] + 50);
  }

  noTone(buzzerPin);
}

void setup() {

  servo.attach(servoPin);
  servo.write(0);

  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(botaoPin, INPUT_PULLUP);

  digitalWrite(ledPin, LOW);

  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("MedControl");

  lcd.setCursor(0, 1);
  lcd.print("Iniciando...");

  delay(2000);
}

void loop() {

  // Abre compartimento
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hora remedio!");

  servo.write(90);

  digitalWrite(ledPin, HIGH);

  tocarAlerta();

  lcd.setCursor(0, 1);
  lcd.print("Aperte apos tomar");

  // Aguarda botão
  while (digitalRead(botaoPin) == HIGH) {

    // mantém o alerta piscando a cada alguns segundos
    delay(100);
  }

  // Confirmação
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Confirmado!");

  digitalWrite(ledPin, LOW);
  noTone(buzzerPin);

  delay(1000);

  // Fecha
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Fechando...");

  servo.write(0);

  delay(1500);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Finalizado!");

  delay(5000);
}
