#include "hardware.h"
#include "hardware/adc.h"

Ledbank::Ledbank(const std::vector<uint>& leds) :
  m_leds(leds)
{
  for (auto led : m_leds) {
      gpio_init(led);
      gpio_set_dir(led, GPIO_OUT);
    }
}

void Ledbank::chase()
{
  for (auto led : m_leds)
    gpio_put(led, 0);

  if (++m_position == m_leds.size()) 
    m_position = 0;

  gpio_put(m_leds[m_position], 1);
}

void Ledbank::toggle()
{
  m_onoff = !m_onoff;
  for (auto led : m_leds)
    gpio_put(led, m_onoff);
}

RGBLed::RGBLed(const std::vector<uint>& leds) :
  Ledbank(leds) {}


void RGBLed::setColor(const std::vector<uint>& rgb)
{
  uint i = 0;
  for (auto led : m_leds)
    gpio_put(led, rgb[i++]);
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

ADC::ADC(uint pin)
{
  adc_init();
  adc_gpio_init(pin);
  adc_select_input(0);
}

uint ADC::getValue()
{
  return adc_read();
}
