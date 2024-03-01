#include "pico/stdlib.h"
#include "hardware.h"
#include <iostream>
#include <vector>

int main() {
    stdio_init_all();
    std::cout << "Hallo" << '\n'; // needs serial monitor settings in diagram.json
    const uint BUTTONPIN = 21;
    const std::vector<uint> LEDPINS = {2, 3, 4, 5};
    const uint TSLEEP = 5;
  


    Ledbank ledbank(LEDPINS);
    Button button(BUTTONPIN);

    uint count = 0;
    while (true) {
      if (button.isPressed()) {
        count++;
        if (count == (1 << LEDPINS.size()) - 1) 
          count = 1;
        std::cout << count << '\n';
        ledbank.displayDual(count);
      }
      sleep_ms(TSLEEP);
           
    }

}


