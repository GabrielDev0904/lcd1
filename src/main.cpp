#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Botao.h>

LiquidCrystal_I2C lcd (0x27, 20, 4);

Botao btnCima(12);
Botao btnBaixo(13);
Botao btnEnter(14);

const int pinLeds[4] = {4, 7, 46, 10};


void setup() {

  btnCima.iniciar();
  btnBaixo.iniciar();
  btnEnter.iniciar();

  lcd.init();
  lcd.backlight();

for (int i = 0; i<4 ; i++) pinMode(pinLeds[i], OUTPUT);

 lcd.setCursor(0,0);
 lcd.print("> LED A OFF");
 lcd.setCursor(0,1);
 lcd.print(" LED B OFF");
 lcd.setCursor(0,2);
 lcd.print(" LED C OFF");
 lcd.setCursor(0,3);
 lcd.print(" LED D OFF");

}

void loop() {

  btnBaixo.atualizar();
  btnCima.atualizar();
  btnEnter.atualizar();


  static int posicaoSeletor = 0;
  static int posicaoSeletorAnterior = 0;

  static bool estadosLeds[4] = {0,0,0,0};
  bool alteracaoDisplay = 0;
  
  if (btnBaixo.pressionou()){
     if (posicaoSeletor < 3) posicaoSeletor ++;
    
  }

  if (btnCima.pressionou()){
     if (posicaoSeletor > 0) posicaoSeletor --;

  }

  if (btnEnter.pressionou()){
  estadosLeds[posicaoSeletor] = !estadosLeds[posicaoSeletor];
  alteracaoDisplay = 1;
    
  }

// ======================== display =================================

if (posicaoSeletor != posicaoSeletorAnterior){
  
  lcd.setCursor(0, posicaoSeletor);
  lcd.print(">");
  lcd.print(" ");
  posicaoSeletorAnterior = posicaoSeletor;
}

// =============== ATUALIZACAO DISPLAY =====================
if (alteracaoDisplay){

    lcd.setCursor(8,posicaoSeletor);
    lcd.print(estadosLeds[posicaoSeletor] ? "LIGADO    " : "DESLIGADO");

    //* estadosLeds[posicaoSeletor] ? lcd.print("LIGADO   "); : lcd.print("DESLIGADO   ");

}

    // ========================= LEDS ================================

   for(int i = 0; i < 4; i++) digitalWrite(pinLeds[i], estadosLeds[i]);
 
}