#include "lcd.h"

LCD::LCD(const uint8_t RS, const uint8_t RW, const uint8_t E, const uint8_t D0, const uint8_t D1, const uint8_t D2, const uint8_t D3, const uint8_t D4, const uint8_t D5, const uint8_t D6, const uint8_t D7){
    // Assign Class Variables
    LCD::RS = RS;
    LCD::RW = RW;
    LCD::E  = E;
    LCD::D0 = D0;
    LCD::D1 = D1;
    LCD::D2 = D2;
    LCD::D3 = D3;
    LCD::D4 = D4;
    LCD::D5 = D5;
    LCD::D6 = D6;
    LCD::D7 = D7;

    // Initialize Pins
    gpio_init(LCD::RS);
    gpio_init(LCD::RW);
    gpio_init(LCD::E);
    gpio_init(LCD::D0);
    gpio_init(LCD::D1);
    gpio_init(LCD::D2);
    gpio_init(LCD::D3);
    gpio_init(LCD::D4);
    gpio_init(LCD::D5);
    gpio_init(LCD::D6);
    gpio_init(LCD::D7);

    // Set Pin Directions
    gpio_set_dir(LCD::RS, GPIO_OUT);
    gpio_set_dir(LCD::RW, GPIO_OUT);
    gpio_set_dir(LCD::E,  GPIO_OUT);

    // Intialize LCD
    LCD::init();
}

void LCD::init(){
    //** Reset LCD **//
    sleep_ms(15);
    LCD::write_instruction(0b111100);
    sleep_ms(5);
    LCD::write_instruction(0b111100);
    sleep_us(110);
    LCD::write_instruction(0b111100);
    sleep_us(50);

    //** Initialization **//
    LCD::set_function(1, 1, 1);
    LCD::set_display_control(1, 1, 1);
    LCD::set_entry_mode(1, 0);
}

void LCD::set_data_pins_direction(const uint8_t direction){
    gpio_set_dir(LCD::D0, direction);
    gpio_set_dir(LCD::D1, direction);
    gpio_set_dir(LCD::D2, direction);
    gpio_set_dir(LCD::D3, direction);
    gpio_set_dir(LCD::D4, direction);
    gpio_set_dir(LCD::D5, direction);
    gpio_set_dir(LCD::D6, direction);
    gpio_set_dir(LCD::D7, direction);
}

void LCD::set_data_pins(const uint8_t data){
    LCD::set_data_pins_direction(GPIO_OUT);
    
    gpio_put(LCD::D0, data & 0b1);
    gpio_put(LCD::D1, (data >> 1) & 0b1);
    gpio_put(LCD::D2, (data >> 2) & 0b1);
    gpio_put(LCD::D3, (data >> 3) & 0b1);
    gpio_put(LCD::D4, (data >> 4) & 0b1);
    gpio_put(LCD::D5, (data >> 5) & 0b1);
    gpio_put(LCD::D6, (data >> 6) & 0b1);
    gpio_put(LCD::D7, data >> 7);
}

void LCD::write_instruction(const uint8_t instruction){
    gpio_put(LCD::RS, 0);
    gpio_put(LCD::RW, 0);

    LCD::set_data_pins_direction(GPIO_OUT);
    LCD::set_data_pins(instruction);

    gpio_put(LCD::E, 1);
    sleep_us(1);
    gpio_put(LCD::E, 0);
}

void LCD::clear(){
    write_instruction(0b1);
    sleep_ms(2);
}

void LCD::set_cursor_position(const uint8_t position){
    LCD::write_instruction((0b1 << 7) | position);
    sleep_us(50);
}

void LCD::cursor_return_home(){
    LCD::write_instruction(0b10);
}

void LCD::write_character(const char character){
    gpio_put(LCD::RS, 1);
    gpio_put(LCD::RW, 0);

    LCD::set_data_pins_direction(GPIO_OUT);
    LCD::set_data_pins(character);

    gpio_put(LCD::E, 1);
    sleep_us(1);
    gpio_put(LCD::E, 0);
    sleep_us(50);
}

void LCD::write_string(const char* string, const uint8_t length){
    for(uint8_t i = 0; i < length; i++){
        LCD::write_character(string[i]);
    }
}

void LCD::write_string_intervalled(const char* string, const uint8_t length, const uint8_t interval){
    for(uint8_t i = 0; i < length; i++){
        LCD::write_character(string[i]);
        sleep_ms(interval);
    }
}

void LCD::set_entry_mode(const uint8_t dir, const uint8_t shift){
    LCD::write_instruction((0b1 << 2) | ((dir & 0b1) << 1) | (shift & 0b1));
    sleep_us(50);
}
void LCD::set_display_control(const uint8_t display, const uint8_t cursor, const uint8_t blinking){
    LCD::write_instruction((0b1 << 3) | ((display & 0b1) << 2) | ((cursor & 0b1) << 1) | (blinking & 0b1));
    sleep_us(50);
}

void LCD::set_function(const uint8_t data_length, const uint8_t display_lines, const uint8_t font){
    LCD::write_instruction((0b1 << 5) | ((data_length & 0b1) << 4) | ((display_lines & 0b1) << 3) | ((font & 0b1) << 2));
    sleep_us(50);
}