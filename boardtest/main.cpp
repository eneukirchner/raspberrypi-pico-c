#include "pico/stdlib.h"
#include "hardware.h"
#include "config.h"
#include <iostream>

int main() {
  stdio_init_all();
  std::cout << "Hello" << '\n'; // needs serial monitor settings in diagram.json
  Ledbank ledbank(LEDPINS);
  RGBLed rgbled(RGBPINS);
  Button button1(BUTTONPINS[0]);
  Button button2(BUTTONPINS[1]);
  Button button3(BUTTONPINS[2]);
  Button button4(BUTTONPINS[3]);
  ADC poti(ADCPIN);

  while (true) {
    if (button1.isPressed())
      ledbank.chase();
    else
      ledbank.toggle();

    if (button2.isPressed())
      rgbled.setColor({1, 0, 0});
    else if (button3.isPressed())
      rgbled.setColor({0, 1, 0});
    else if (button4.isPressed())
      rgbled.setColor({0, 0, 1});
    else
      rgbled.toggle();

    uint tsleep = poti.getValue()/2 + 20;
    sleep_ms(tsleep);
  }

}