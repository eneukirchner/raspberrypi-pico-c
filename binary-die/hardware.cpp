#include "hardware.h"

Ledbank::Ledbank(const std::vector<uint>& leds) :
  m_leds(leds)
{
  for (auto led : m_leds) {
      gpio_init(led);
      gpio_set_dir(led, GPIO_OUT);
    }
}

// int to binary conversion
void Ledbank::displayDual(uint value)
{
  for (auto led : m_leds) {
      gpio_put(led, value & 0x01);
      value >>= 1;
  }
}

Button::Button(uint pin) :
  m_pin(pin)
{
  gpio_init(m_pin);
  gpio_set_pulls(m_pin, true, false);
  gpio_set_dir(m_pin, GPIO_IN);
}

bool Button::isPressed()
{
  return (gpio_get(m_pin) == 0);
}