/******************************************************************************
 * Biblioteca: LCD I2C (lcd_i2c.h)
 * Autor: Elison Nogueira
 * Data: 18/11/2024
 *
 * Descrição:
 * Interface para controle de display LCD 16x2/20x4 via I2C usando PCF8574
 *
 * Requer:
 * - Biblioteca I2C do mikroC PRO for PIC
 * - Display LCD HD44780 com módulo I2C PCF8574
 *****************************************************************************/

#ifndef LCD_I2C_H
#define LCD_I2C_H

// Endereço do módulo I2C PCF8574
#define LCD_ADDR 0x4E

// Comandos do LCD
#define _LCD_FIRST_ROW          0x80                                            //Posiciona cursor na primeira linha
#define _LCD_SECOND_ROW         0xC0                                            //Posiciona cursor na segunda linha
#define _LCD_THIRD_ROW          0x94                                            //Posiciona cursor na terceira linha
#define _LCD_FOURTH_ROW         0xD4                                            //Posiciona cursor na quarta linha
#define _LCD_CLEAR              0x01                                            //Limpa o display
#define _LCD_RETURN_HOME        0x02                                            //Retorna cursor para posição inicial
#define _LCD_CURSOR_OFF         0x0C                                            //Desliga o cursor
#define _LCD_UNDERLINE_ON       0x0E                                            //Liga cursor sublinhado
#define _LCD_BLINK_CURSOR_ON    0x0F                                            //Liga cursor piscante
#define _LCD_MOVE_CURSOR_LEFT   0x10                                            //Move cursor para esquerda
#define _LCD_MOVE_CURSOR_RIGHT  0x14                                            //Move cursor para direita
#define _LCD_TURN_ON            0x0C                                            //Liga o display
#define _LCD_TURN_OFF           0x08                                            //Desliga o display
#define _LCD_SHIFT_LEFT         0x18                                            //Desloca display para esquerda
#define _LCD_SHIFT_RIGHT        0x1E                                            //Desloca display para direita

// Protótipos das funções
void I2C_LCD_Init(void);                                                        //Inicializa o LCD
void I2C_LCD_Cmd(char cmd);                                                     //Envia comando
void I2C_LCD_Chr(char row, char column, char chr);                              //Escreve caractere na posição
void I2C_LCD_Chr_Cp(char chr);                                                  //Escreve caractere na posição atual
void I2C_LCD_Out(char row, char col, char *text);                               //Escreve string na posição
void I2C_LCD_Out_Cp(char *text);                                                //Escreve string na posição atual

#endif