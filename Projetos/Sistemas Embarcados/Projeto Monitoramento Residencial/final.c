int state = 1;        // Variavel para armazenar o dado lido.
int velocity;
int last = 1;

sbit LCD_RS at RE2_bit;   // PINO 2 DO PORTD LIGADO AO RS DO DISPLAY
sbit LCD_EN at RE1_bit;   // PINO 3 DO PORTD LIGADO AO EN DO DISPLAY
sbit LCD_D7 at RD7_bit;  // PINO 7 DO PORTD LIGADO AO D7 DO DISPLAY
sbit LCD_D6 at RD6_bit;  // PINO 6 DO PORTD LIGADO AO D6 DO DISPLAY
sbit LCD_D5 at RD5_bit;  // PINO 5 DO PORTD LIGADO AO D5 DO DISPLAY
sbit LCD_D4 at RD4_bit;  // PINO 4 DO PORTD LIGADO AO D4 DO DISPLAY

// Selecionando direção de fluxo de dados dos pinos utilizados para a comunicação com display LCD
sbit LCD_RS_Direction at TRISE2_bit;  // SETA DIREÇÃO DO FLUXO DE DADOS DO PINO 2 DO PORTD
sbit LCD_EN_Direction at TRISE1_bit;  // SETA DIREÇÃO DO FLUXO DE DADOS DO PINO 3 DO PORTD
sbit LCD_D7_Direction at TRISD7_bit;  // SETA DIREÇÃO DO FLUXO DE DADOS DO PINO 7 DO PORTD
sbit LCD_D6_Direction at TRISD6_bit;  // SETA DIREÇÃO DO FLUXO DE DADOS DO PINO 6 DO PORTD
sbit LCD_D5_Direction at TRISD5_bit;  // SETA DIREÇÃO DO FLUXO DE DADOS DO PINO 5 DO PORTD
sbit LCD_D4_Direction at TRISD4_bit;  // SETA DIREÇÃO DO FLUXO DE DADOS DO PINO 4 DO PORTD


void main(){

   UART1_Init(9600);
   
   ADCON1  = 0x0F;
   
   Lcd_Init();                               //Inicializa módulo LCD
   Lcd_Cmd(_LCD_CURSOR_OFF);                 //Apaga cursor
   Lcd_Cmd(_LCD_CLEAR);                      //Limpa display
   
   UART1_Init(9600);  // Utiliza bibliotecas do compilador para configuração o Baud rate.

   //Declarando o Buzzer
   TRISC.RC1 = 0;      //PORT C configurado como saída

   //Declarando o LED
   TRISB =0;            // Define todos os pinos do PORTB como saída.
   PORTB = 1;           // Colocar todos os pinos em nível baixo.

   //Declarando a Ventoinha ??
   PWM1_Init(5000);      // Inicializa módulo PWM com 5Khz
   PWM1_Start();         // Start PWM

   while(1){
   delay_ms(100);
       if(UART1_Data_Ready()){
         state = UART1_Read();
       }
       if(state == 1){
         PORTB.RB7 = 0;
         PORTC.RC1 = 1;
         if(last != 1){
           Lcd_Cmd(_LCD_CLEAR);
           last = 1;
         }
         Lcd_Out(1,1,"Sistema");
         Lcd_Out(2,1,"Desativado");
         PWM1_Set_Duty(0);
       }
       else if(state == 2){
         PORTB.RB7 = 0;
         PORTC.RC1 = 1;
         PWM1_Set_Duty(100);
         if(last != 2){
           Lcd_Cmd(_LCD_CLEAR);
           last = 2;
         }
         Lcd_Out(1,1,"Sistema Ativo");
         Lcd_Out(2,1,"Nenhuma Deteccao");
       }
       else if(state == 3){
         PORTB.RB7 = 1;
         PORTC.RC1 = 0;
         PWM1_Set_Duty(180);
         if(last != 3){
           Lcd_Cmd(_LCD_CLEAR);
           last = 3;
         }
         Lcd_Out(1,1,"Invasao!!");
         Lcd_Out(2,1,"Alarme Acionado");
         delay_ms(100);
         PORTB.RB7 = 0;
         PORTC.RC1 = 1;
       }
     //}
   }
}