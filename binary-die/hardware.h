#pragma once
#include "pico/stdlib.h"
#include <vector>

class Ledbank {
  public:
    Ledbank(const std::vector<uint>& leds);
    void displayDual(uint value);
  private:
    const std::vector<uint>& m_leds;
};

class Button {
  public:
    Button(uint pin);
    bool isPressed();
  private:
    uint m_pin;
};