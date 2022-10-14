#include <string>
#include "lcd.h"

int main(){
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    LCD lcd(2, 3, 4, 5, 11, 6, 7, 8, 9, 12, 10);

    std::string hello_world_str = "Dag Kobus!";
    lcd.write_string_intervalled(hello_world_str.c_str(), hello_world_str.length(), 200);

    return 0;
}