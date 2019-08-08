// Inclusão de bibliotecas 
#include <LiquidCrystal.h>
#include "pitches.h"

// Os pinos utilizados no Arduino
int pinoLED = 2;
int pinoLabirinto = 3;
int pinoBuzzer = 9;
int pinoSirene = 10;
int melody[] = {
 NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};
LiquidCrystal lcd(7, 8, 5, 4, 6, 11);


// Declaração das variáveis auxiliares
int nivel = 0;
long int tempoAnterior = 0;
int deltaT = 200;
int tomBuzzer = 3000;
int estadoBotao = LOW;
int estadoBuzzer = LOW;


void setup() {

  // Define os pinos int 

  pinMode(pinoLabirinto, INPUT_PULLUP); 

  pinMode(pinoBuzzer, OUTPUT);

  pinMode(pinoSirene, OUTPUT);

  digitalWrite(pinoLED, HIGH);

  digitalWrite(pinoSirene, HIGH); //noTone(pinoSirene);

  Serial.begin(9600);
    //Inicializando o LCD e informando o tamanho de 16 colunas e 2 linhas
  //que é o tamanho do LCD JHD 162A usado neste projeto.
  lcd.begin(16, 2); 
}

void loop() { 
 lcd.clear(); //limpa o display do LCD.     
 lcd.print("E ai");  // Leitura da tela
  delay(3000); 
  
 lcd.setCursor(0,1);   //posiciona cursor na coluna 0 linha 1 do LCD
 lcd.print("Preparado(a)?"); //imprime a string no display do LCD.
  delay(3000);   
  
Serial.println(nivel); // jogo em ação 

  estadoBotao = digitalRead(pinoLabirinto);
 if (estadoBotao == LOW) {
  delay(50);
estadoBotao = digitalRead(pinoLabirinto);
while (!digitalRead(pinoLabirinto)) {
  delay(1);
}
if (estadoBotao == LOW) {
 nivel = nivel + 1;
 }
}
 if (nivel == 2) {
 deltaT = 100;
tomBuzzer = 3500;
}
 lcd.clear();
  lcd.print("Se concentra");
  delay(2000);
  
 if (nivel == 3) {
 deltaT = 50;
 tomBuzzer = 4000;
 }
if (nivel == 4) {
  noTone(pinoBuzzer);//digitalWrite(pinoBuzzer, LOW);
while (1) {
  digitalWrite(pinoSirene, LOW); //tone(pinoSirene, 4000);
}
}
if (((millis() - tempoAnterior) > deltaT) && (nivel >= 1)) {
if (estadoBuzzer) {
tone(pinoBuzzer, tomBuzzer);
}
 else {
noTone(pinoBuzzer);
}
estadoBuzzer = !estadoBuzzer;
tempoAnterior = millis();
 }
  
  lcd.clear();
  lcd.print("Você perdeu");
  lcd.setCursor(0,1);
  lcd.print("seu noob");
  delay(4000);
}
