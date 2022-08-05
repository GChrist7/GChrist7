#include <Keypad.h> // Biblioteca do codigo
#include <string.h>
#include "pitches.h"

const int Buzzer = 30;
const int pinopir = 11;
int presenca;
int pwm = 0;
int state = 1; //1: Desbloqueado  2: Ativo  3: Alarme
int last_state;

//módulo real
const byte LINHAS = 4; // Linhas do teclado
const byte COLUNAS = 4; // Colunas do teclado

char senha[4];

int lock;
int loc;

int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};



const char MATRIZ[LINHAS][COLUNAS] = { // Matriz de caracteres (mapeamento do teclado)
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

const byte PINOS_LINHAS[LINHAS] = {9, 8, 7, 6}; // Pinos de conexao com as linhas do teclado
const byte PINOS_COLUNAS[COLUNAS] = {5, 4, 3, 2}; // Pinos de conexao com as colunas do teclado

Keypad TM = Keypad(makeKeymap(MATRIZ), PINOS_LINHAS, PINOS_COLUNAS, LINHAS, COLUNAS); // Inicia teclado

int checkSenha(){
  if(senha[0] == '1'  && senha[1] == '2' && senha[2] == '3' && senha[3] == '4'){
    for(int i=0 ; i<4 ; i++){
      senha[i] = '0'; 
    }
    loc = 0;
    return 1;
  }
  else{
    for(int i=0 ; i<4 ; i++){
      senha[i] = '0'; 
    }
    loc = 0;
    return 0;
  }
}


void melodia(){
  int thisNote;
  int noteDuration;
  int pauseBetweenNotes;
  for (thisNote = 0; thisNote < 8; thisNote++) {
    noteDuration = 1000 / noteDurations[thisNote];
    tone(30, melody[thisNote], noteDuration);
    pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(30);
  }
}

void MudaEstado(){
   if(last_state == 1){
    state = 2;
   }  
   else if(last_state == 2){
    state = 1; 
   }
   else if(last_state == 3){
    state = 1;
   }
}

void setup() {
  Serial.begin(9600); // Inicia porta serial
  Serial1.begin(9600);
  pinMode(pinopir, INPUT);   //Define pino sensor como entrada
  pinMode(Buzzer, OUTPUT);
}

void loop() {

  char leitura = TM.getKey(); // Atribui a variavel a leitura do teclado
  presenca = digitalRead(pinopir); //Le o valor do sensor PIR
  
  if(presenca == HIGH && last_state == 2){
    state = 3;  
  }
  
  if(leitura){
    Serial.println(leitura);
    if(leitura == 'D'){ // 'D' confirma a senha
      lock = checkSenha();
    }
    else{
      senha[loc] = leitura;
      loc++;  
    }
  }

  if(lock == 1){
    melodia();
    lock = 0;
    MudaEstado();
  }

  if(state == 1){
    Serial1.write(1);
    Serial.println("Estado Desbloqueado");
    last_state = state;
  }
  else if(state == 2){
    Serial1.write(2);
    Serial.println("Estado Bloqueado");
    last_state = state;
  }
  else if(state == 3){
    Serial1.write(3);
    Serial.println("Estado Ativo");
    last_state = state;
  }
  state = 0;
}
 
