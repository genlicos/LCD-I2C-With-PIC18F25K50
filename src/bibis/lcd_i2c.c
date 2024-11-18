/******************************************************************************
* Biblioteca: LCD I2C (lcd_i2c.c)
* Autor: Elison Nogueira
* Data: 18/11/2024
*
* Descri��o:
* Implementa��o das fun��es para controle de display LCD via I2C usando PCF8574.
* Permite controle de displays LCD 16x2/20x4 utilizando interface I2C.
*****************************************************************************/

#include "lcd_i2c.h"

// Envia comando para o LCD via barramento I2C em modo 4 bits
void I2C_LCD_Cmd(char cmd) {
   char hi_nibble, lo_nibble;
   char rs = 0x00;                                                              //RS=0 sinaliza envio de comando

   hi_nibble = cmd & 0xF0;                                                      //Mascara 4 bits mais significativos
   lo_nibble = (cmd << 4) & 0xF0;                                               //Desloca e mascara 4 bits menos significativos

   I2C1_Start();                                                                //Inicia comunica��o I2C
   I2C1_Is_Idle();                                                              //Aguarda barramento livre
   I2C1_Wr(LCD_ADDR);                                                           //Endere�a dispositivo LCD
   I2C1_Is_Idle();
   I2C1_Wr(hi_nibble | rs | 0x04 | 0x08);                                       //Habilita EN e backlight, envia nibble alto
   I2C1_Is_Idle();
   Delay_us(50);                                                                //Tempo para processamento do LCD
   I2C1_Wr(hi_nibble | rs | 0x00 | 0x08);                                       //Desabilita EN, mant�m backlight
   I2C1_Is_Idle();
   Delay_us(100);
   I2C1_Wr(lo_nibble | rs | 0x04 | 0x08);                                       //Habilita EN e backlight, envia nibble baixo
   I2C1_Is_Idle();
   Delay_us(50);
   I2C1_Wr(lo_nibble | rs | 0x00 | 0x08);                                       //Desabilita EN, mant�m backlight
   I2C1_Is_Idle();
   I2C1_Stop();                                                                 //Encerra comunica��o I2C

   if(cmd == _LCD_CLEAR)                                                        //Se comando for limpar display
       Delay_ms(2);                                                             //Aguarda processamento completo
}

// Posiciona cursor e escreve caractere na posi��o especificada
void I2C_LCD_Chr(char row, char column, char chr) {
   char hi_nibble, lo_nibble;
   char rs = 0x01;                                                              //RS=1 sinaliza envio de dado

   switch(row){                                                                 //Seleciona endere�o conforme linha
       case 1:
           I2C_LCD_Cmd(0x80 + (column - 1));                                    //Endere�o primeira linha + coluna
           break;
       case 2:
           I2C_LCD_Cmd(0xC0 + (column - 1));                                    //Endere�o segunda linha + coluna
           break;
       case 3:
           I2C_LCD_Cmd(0x94 + (column - 1));                                    //Endere�o terceira linha + coluna
           break;
       case 4:
           I2C_LCD_Cmd(0xD4 + (column - 1));                                    //Endere�o quarta linha + coluna
           break;
   }

   hi_nibble = chr & 0xF0;                                                      //Prepara nibble alto do caractere
   lo_nibble = (chr << 4) & 0xF0;                                               //Prepara nibble baixo do caractere

   I2C1_Start();
   I2C1_Is_Idle();
   I2C1_Wr(LCD_ADDR);
   I2C1_Is_Idle();
   I2C1_Wr(hi_nibble | rs | 0x04 | 0x08);                                       //Envia nibble alto com RS=1
   I2C1_Is_Idle();
   Delay_us(50);
   I2C1_Wr(hi_nibble | rs | 0x00 | 0x08);
   I2C1_Is_Idle();
   Delay_us(100);
   I2C1_Wr(lo_nibble | rs | 0x04 | 0x08);                                       //Envia nibble baixo com RS=1
   I2C1_Is_Idle();
   Delay_us(50);
   I2C1_Wr(lo_nibble | rs | 0x00 | 0x08);
   I2C1_Is_Idle();
   I2C1_Stop();
}

// Escreve caractere na posi��o atual do cursor
void I2C_LCD_Chr_Cp(char chr) {
   char hi_nibble, lo_nibble;
   char rs = 0x01;                                                              //RS=1 para envio de dados

   hi_nibble = chr & 0xF0;                                                      //Prepara nibble alto
   lo_nibble = (chr << 4) & 0xF0;                                               //Prepara nibble baixo

   I2C1_Start();
   I2C1_Is_Idle();
   I2C1_Wr(LCD_ADDR);
   I2C1_Is_Idle();
   I2C1_Wr(hi_nibble | rs | 0x04 | 0x08);                                       //Envia primeiro nibble
   I2C1_Is_Idle();   Delay_us(50);                                              //Tempo para processamento
   I2C1_Wr(hi_nibble | rs | 0x00 | 0x08);
   I2C1_Is_Idle();
   Delay_us(100);
   I2C1_Wr(lo_nibble | rs | 0x04 | 0x08);                                       //Envia segundo nibble
   I2C1_Is_Idle();
   Delay_us(50);
   I2C1_Wr(lo_nibble | rs | 0x00 | 0x08);
   I2C1_Is_Idle();
   I2C1_Stop();
}

// Posiciona cursor e escreve string a partir da posi��o especificada
void I2C_LCD_Out(char row, char col, char *text) {
   while(*text) {                                                               //Enquanto houver caracteres na string
       I2C_LCD_Chr(row, col++, *text++);                                        //Escreve caractere e avan�a coluna e ponteiro
   }
}

// Escreve string a partir da posi��o atual do cursor
void I2C_LCD_Out_Cp(char *text) {
   while(*text) {                                                               //Enquanto houver caracteres na string
       I2C_LCD_Chr_Cp(*text++);                                                 //Escreve caractere e incrementa ponteiro
   }
}

// Inicializa display LCD no modo 4 bits via I2C
void I2C_LCD_Init() {
   char rs = 0x00;                                                              //RS=0 indica envio de comandos de inicializa��o

   I2C1_Start();                                                                //Inicia comunica��o I2C
   I2C1_Is_Idle();                                                              //Aguarda barramento livre
   I2C1_Wr(LCD_ADDR);                                                           //Endere�a o controlador do LCD via I2C
   I2C1_Is_Idle();                                                              //Aguarda confirma��o

   Delay_ms(3);                                                                 //Aguarda 3ms para estabiliza��o do LCD ap�s power-on

   // Primeira tentativa - Interface 8 bits
   I2C1_Wr(0x30 | rs | 0x04 | 0x08);                                            //Envia 0x30: configura interface 8 bits, EN=1, BL=1
   I2C1_Is_Idle();                                                              //Aguarda confirma��o
   Delay_us(50);                                                                //Aguarda processamento do LCD
   I2C1_Wr(0x30 | rs | 0x00 | 0x08);                                            //Mesmo comando com EN=0 para gerar pulso
   I2C1_Is_Idle();                                                              //Aguarda confirma��o
   Delay_ms(1);                                                                 //Delay entre comandos de inicializa��o

   // Segunda tentativa - Interface 8 bits
   I2C1_Wr(0x30 | rs | 0x04 | 0x08);                                            //Repete sequ�ncia anterior conforme datasheet
   I2C1_Is_Idle();                                                              //Aguarda confirma��o
   Delay_us(50);                                                                //Aguarda processamento do LCD
   I2C1_Wr(0x30 | rs | 0x00 | 0x08);                                            //Pulso EN
   I2C1_Is_Idle();                                                              //Aguarda confirma��o
   Delay_ms(1);                                                                 //Delay entre comandos

   // Terceira tentativa - Interface 8 bits
   I2C1_Wr(0x30 | rs | 0x04 | 0x08);                                            //Repete sequ�ncia pela terceira vez
   I2C1_Is_Idle();                                                              //Aguarda confirma��o
   Delay_us(50);                                                                //Aguarda processamento
   I2C1_Wr(0x30 | rs | 0x00 | 0x08);                                            //Pulso EN
   I2C1_Is_Idle();                                                              //Aguarda confirma��o
   Delay_ms(1);                                                                 //Delay entre comandos

   // Configura interface 4 bits
   I2C1_Wr(0x20 | rs | 0x04 | 0x08);                                            //Envia 0x20: configura interface 4 bits
   I2C1_Is_Idle();                                                              //Aguarda confirma��o
   Delay_us(50);                                                                //Aguarda processamento
   I2C1_Wr(0x20 | rs | 0x00 | 0x08);                                            //Pulso EN
   I2C1_Is_Idle();                                                              //Aguarda confirma��o
   I2C1_Stop();                                                                 //Encerra comunica��o I2C

   Delay_ms(1);                                                                 //Aguarda processamento final da interface

   // Configura par�metros de opera��o do LCD
   I2C_LCD_Cmd(0x28);                                                           //Configura: 4 bits, 2 linhas, matriz 5x7
   I2C_LCD_Cmd(0x06);                                                           //Configura cursor para incrementar � direita
   I2C_LCD_Cmd(_LCD_CURSOR_OFF);                                                //Desliga o cursor
   I2C_LCD_Cmd(_LCD_CLEAR);                                                     //Limpa display e posiciona cursor no in�cio
}