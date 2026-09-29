#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Botao.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

Botao btnCima(14);
Botao btnBaixo(13);
Botao btnEnter(12);

const int pinLedA = 4;
const int pinLedB = 7;
const int pinLedC = 46;
const int pinLedD = 10;

void setup()
{
  btnCima.iniciar();
  btnBaixo.iniciar();
  btnEnter.iniciar();

  Serial.begin(115200);

  lcd.init();
  lcd.backlight();
  pinMode(pinLedA, OUTPUT);
  pinMode(pinLedB, OUTPUT);
  pinMode(pinLedC, OUTPUT);
  pinMode(pinLedD, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("> LED A DESLIGADO");
  lcd.setCursor(0, 1);
  lcd.print("  LED B DESLIGADO");
  lcd.setCursor(0, 2);
  lcd.print("  LED C DESLIGADO");
  lcd.setCursor(0, 3);
  lcd.print("  LED D DESLIGADO");
}

void loop()
{
  btnBaixo.atualizar();
  btnCima.atualizar();
  btnEnter.atualizar();

  static int posicaoSeletor = 0;
  static int posicaoSeletorAnterior = 0;
  static bool estadoLedA = 0;
  static bool estadoLedB = 0;
  static bool estadoLedC = 0;
  static bool estadoLedD = 0;
  bool alteracaoDisplay = 0;

  if (btnBaixo.pressionou())
  {
    if (posicaoSeletor < 3)
      posicaoSeletor++;
  }
  if (btnCima.pressionou())
  {
    if (posicaoSeletor > 0)
      posicaoSeletor--;
  }
  if (btnEnter.pressionou())
  {
    if (posicaoSeletor == 0)
      estadoLedA = !estadoLedA;
    else if (posicaoSeletor == 1)
      estadoLedB = !estadoLedB;
    else if (posicaoSeletor == 2)
      estadoLedC = !estadoLedC;
    else
      estadoLedD = !estadoLedD;
    alteracaoDisplay = 1;
  }

  //=============LEDs=======================
  digitalWrite(pinLedA, estadoLedA);
  digitalWrite(pinLedB, estadoLedB);
  digitalWrite(pinLedC, estadoLedC);
  digitalWrite(pinLedD, estadoLedD);

  //============DISPLAY====================
  if (posicaoSeletor != posicaoSeletorAnterior)
  {
    lcd.setCursor(0, posicaoSeletor);
    lcd.print(">");
    lcd.setCursor(0, posicaoSeletorAnterior);
    lcd.print(" ");
    posicaoSeletorAnterior = posicaoSeletor;
  }

  if (alteracaoDisplay)
  {
    lcd.setCursor(8, 0);
    if (estadoLedA)
      lcd.print("LIGADO   ");
    else
      lcd.print("DESLIGADO");
    lcd.setCursor(8, 1);
    if (estadoLedB)
      lcd.print("LIGADO   ");
    else
      lcd.print("DESLIGADO");
    lcd.setCursor(8, 2);
    if (estadoLedC)
      lcd.print("LIGADO   ");
    else
      lcd.print("DESLIGADO");
    lcd.setCursor(8, 3);
    if (estadoLedD)
      lcd.print("LIGADO   ");
    else
      lcd.print("DESLIGADO");
  }
}