/******************************************************************************
 * Projeto: Display LCD HD44780 com m�dulo I2C PCF8574
 * Autor: Elison Nogueira
 * Data de Cria��o: 18/11/2024
 * Vers�o: 1.0
 * Plataforma: PIC18F25K50 (Microchip)
 * Compilador: mikroC Pro for PIC v7.6.0
 *
 * Descri��o:
 * Este projeto implementa um Display LCD HD44780 com m�dulo I2C PCF8574.
 *
 * Hardware Necess�rio:
 * - Microcontrolador PIC18F25K50 (16Mhz de clock)
 * - Display LCD HD44780 (16x2/20x4) (I2C)
 * - M�dulo I2C PCF8574
 * - Fonte de alimenta��o 5V
 *
 * Funcionalidades:
 * - Exibi��o caracteres ou strings no display LCD I2C
 *
 * Refer�ncias:
 * - Datasheet PIC18F25K50
 * - Datasheet PCF8574
 * - Datasheet HD44780
 * - Documenta��o do MikroC Pro for PIC
 *
 * Configura��es dos Registradores iniciais:
 * - CONFIG1L : $300000 : 0x0000
 * - CONFIG1H : $300001 : 0x0003
 * - CONFIG2L : $300002 : 0x005F
 * - CONFIG2H : $300003 : 0x003C
 * - CONFIG3H : $300005 : 0x00D3
 * - CONFIG4L : $300006 : 0x0081
 * - CONFIG5L : $300008 : 0x000F
 * - CONFIG5H : $300009 : 0x00C0
 * - CONFIG6L : $30000A : 0x000F
 * - CONFIG6H : $30000B : 0x00E0
 * - CONFIG7L : $30000C : 0x000F
 * - CONFIG7H : $30000D : 0x0040
  *****************************************************************************/

// Incluindo bibliotecas
#include "bibis/lcd_i2c.h"

// Vari�veis globais

void inicializar_sistema() {
    // Inicializa comunica��o I2C
    I2C1_Init(100000);
    delay_ms(100);

    // Inicializa LCD
    I2C_LCD_Init();
}

void main() {
    // Inicializa sistema
    inicializar_sistema();

    // Loop principal
    while(1) {
        I2C_LCD_Out(1, 1, "LCD I2C 16x2");
        delay_ms(5000);
    }
}