#pragma once
#include "pico/stdlib.h"
#include <vector>

class Ledbank {
  public:
    Ledbank(const std::vector<uint>& leds);
    void toggle();
    void chase();
  protected:
    const std::vector<uint>& m_leds;
    bool m_onoff = 0;
    uint m_position = 0;
};

class RGBLed : public Ledbank {
  public: 
    RGBLed(const std::vector<uint>& leds);
    void setColor(const std::vector<uint>& rgb);
};

class Button {
  public:
    Button(uint pin);
    bool isPressed();
  private:
    uint m_pin;
};

class ADC {
  public:
    ADC(uint pin);
    uint getValue();
};
