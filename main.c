#include <float.h>
#include <math.h>
#include <stdio.h>

#include "project.h"

void lcd_init(void) {
    LCD_Char_1_Start();

    LCD_Char_1_Position(0, 0);
    LCD_Char_1_PrintString("                    ");

    LCD_Char_1_Position(1, 0);
    LCD_Char_1_PrintString("                    ");

    LCD_Char_1_Position(2, 0);
    LCD_Char_1_PrintString("                    ");

    LCD_Char_1_Position(3, 0);
    LCD_Char_1_PrintString("                    ");
}

void lcd_print_line_str_float_str(
    uint8_t line, char8* start, float number, char8* ending
) {
    int32_t num_whole = (int32_t)number;
    int32_t num_fractional = (int32_t)(number * 100) % 100;

    char8 str[21] = {0};
    sprintf(str, "%s %ld.%02ld %s", start, num_whole, num_fractional, ending);

    // blank line
    LCD_Char_1_Position(line, 0);
    LCD_Char_1_PrintString("                    ");

    // print line
    LCD_Char_1_Position(line, 0);
    LCD_Char_1_PrintString(str);
}

void adc_init(void) {
    AMux_1_Start();
    ADC_DelSig_1_Start();
}

uint16_t adc_read_channel_mv(uint8_t channel) {
    AMux_1_Select(channel);
    CyDelay(2);
    ADC_DelSig_1_StartConvert();
    ADC_DelSig_1_IsEndConversion(ADC_DelSig_1_WAIT_FOR_RESULT);
    uint16_t reading = ADC_DelSig_1_GetResult16();
    int16 millivolts = ADC_DelSig_1_CountsTo_mVolts(reading);
    return millivolts;
}

uint16_t adc_read_ref_mv(void) {
    return adc_read_channel_mv(0);
}

uint16_t adc_read_themistor_mv(void) {
    return adc_read_channel_mv(1);
}

float get_temperature_c_from_ratio(int16 reference, int16 themistor) {
    volatile uint32 themistor_resistance =
        Thermistor_2_GetResistance(reference, themistor);
    volatile int16 temperature_hundredths =
        Thermistor_2_GetTemperature(themistor_resistance);

    float temperature_c = (float)temperature_hundredths / 100.0f;
    return temperature_c;
}

int main(void) {
    CyGlobalIntEnable; /* Enable global interrupts. */

    lcd_init();
    adc_init();

    while(1) {
        int16 r1_millivolts = adc_read_ref_mv();
        int16 themistor_millivolts = adc_read_themistor_mv();

        float temperature_c =
            get_temperature_c_from_ratio(r1_millivolts, themistor_millivolts);
        float temperature_f = (temperature_c * 9 / 5) + 32;

        lcd_print_line_str_float_str(0, "T:", temperature_c, "Celsius");
        lcd_print_line_str_float_str(1, "T:", temperature_f, "Fahrenheit");

        CyDelay(500);
    }
}
