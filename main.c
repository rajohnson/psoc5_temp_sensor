#include "project.h"

int main(void) {
    uint32_t loop_count = 0;
    CyGlobalIntEnable; /* Enable global interrupts. */

    LCD_Char_1_Start();
    LCD_Char_1_IsReady();
    LCD_Char_1_Position(0, 0);
    LCD_Char_1_IsReady();
    LCD_Char_1_PrintString("12345678901234567890");

    LCD_Char_1_IsReady();
    LCD_Char_1_Position(1, 0);
    LCD_Char_1_IsReady();
    LCD_Char_1_PrintString("23456789012345678901");

    LCD_Char_1_IsReady();
    LCD_Char_1_Position(2, 0);
    LCD_Char_1_IsReady();
    LCD_Char_1_PrintString("34567890123456789012");

    LCD_Char_1_IsReady();
    LCD_Char_1_Position(3, 0);
    LCD_Char_1_IsReady();
    LCD_Char_1_PrintString("45678901234567890123");

    for(;;) {
        LCD_Char_1_IsReady();
        LCD_Char_1_Position(3, 0);
        LCD_Char_1_IsReady();
        LCD_Char_1_PrintString("                    ");
        LCD_Char_1_Position(3, 0);
        LCD_Char_1_PrintU32Number(loop_count++);

        CyDelay(400);
    }
}
