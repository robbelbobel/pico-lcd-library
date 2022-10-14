#ifndef LCD_H
#define LCD_H

#include "pico/stdlib.h"

class LCD{
    private:
    // Private Class Variables
    uint8_t RS, RW, E, D0, D1, D2, D3, D4, D5, D6, D7;

    // Private Class Functions
    void init();
    void set_data_pins_direction(const uint8_t direction);
    void set_data_pins(const uint8_t data);
    void write_instruction(const uint8_t instruction);

    public:
    //Public Class Functions
    LCD(const uint8_t RS, const uint8_t RW, const uint8_t E, const uint8_t D0, const uint8_t D1, const uint8_t D2, const uint8_t D3, const uint8_t D4, const uint8_t D5, const uint8_t D6, const uint8_t D7);

    void clear();

    void set_cursor_position(const uint8_t position);
    void cursor_return_home();

    void write_character(const char character);
    void write_string(const char* string, const uint8_t length);
    void write_string_intervalled(const char* string, const uint8_t length, const uint8_t interval);

    void set_entry_mode(const uint8_t dir, const uint8_t shift);
    void set_display_control(const uint8_t display, const uint8_t cursor, const uint8_t blinking);
    void set_function(const uint8_t data_length, const uint8_t display_lines, const uint8_t font);

};

#endif