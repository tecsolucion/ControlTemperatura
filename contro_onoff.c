#INCLUDE <16F887.H>
#DEVICE ADC=10
#USE DELAY(CLOCK=8000000)
#FUSES NOWDT                    //No Watch Dog Timer
#FUSES INTRC_IO                 //Internal RC Osc, no CLKOUT
#FUSES NOPUT                    //No Power Up Timer
#FUSES NOMCLR                   //Master Clear pin used for I/O
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NOCPD                    //No EE protection
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOIESO                   //Internal External Switch Over mode disabled
#FUSES NOFCMEN                  //Fail-safe clock monitor disabled
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOWRT                    //Program memory not write protected
#FUSES BORV40                   //Brownout reset at 4.0V
#use rs232(baud=9600, xmit=pin_c6, rcv=pin_c7,bits=8)
#include "lcd.c" 

VOID MAIN(){


INT16 ya,referencia; //Variables para  lectura de ADC y señal de Control a modulo CCP
FLOAT rt,yt;

lcd_init();                   // Turn LCD ON, along with other initialization commands
   

/*
setup_timer_2(t2_div_by_4,249,1); //Configuracion   de Timer 2 para establecer frec. PWM a 1kHz
setup_ccp1(ccp_pwm); //Configurar modulo CCP1 en modo PWM
*/
setup_adc(adc_clock_internal);

setup_adc_ports(sAN0|sAN1|VSS_VDD);
  



while(true){

set_adc_channel(1);   // escogemos el canal 1 para leer el potenciometro
delay_ms(1);
referencia=read_adc();   // lectura digital del pot
delay_ms(1);

set_adc_channel(0); //Seleccionar Canal 0 para sensor de Temperatura
delay_ms(1);
ya=read_adc(); //lectura digital del sensor
delay_ms(1);

rT=referencia*(100.0/1024.0);

yT=500.0*ya/1024.0; //Escalizar señal de salida y(kT)

   lcd_gotoxy(1,1);              // point LCD cursor to col1 row1
   
   lcd_putc("Td:");
   
   
   lcd_gotoxy(5,1);
   
   printf(lcd_putc,"%2.1f C",rT);
   
    lcd_gotoxy(1,2);
    
      lcd_putc("Tm:");
   
   
   lcd_gotoxy(5,2);
   
   // point LCD cursor to col1 row2
     
     
     printf(lcd_putc,"%2.1f C",yT);


if (yt >= rt){
output_low(PIN_B0);
}
else {
output_high(PIN_B0);
}
}
} 
