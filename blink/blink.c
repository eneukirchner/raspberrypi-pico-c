/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include <stdio.h>


const uint LEDS[] = {2, 3, 4, 5, 6, 7, 8, 9};
const int BUTTON1 = 18, BUTTON2 = 19;
const int ADC_INPUT = 26;

const uint RGB[] = {10, 11, 12};

const int PWM_RANGE = 255;

uint run = 1; // 1 = led chase running, 0 = RGB led running

void gpio_callback(uint gpio, uint32_t events) {
	run = (gpio == BUTTON1) ? 1 : 0;
}

void init_leds()
{
    uint nleds = sizeof(LEDS)/sizeof(uint);
    for (int led = 0; led < nleds; led++) {
        gpio_init(LEDS[led]);
        gpio_set_dir(LEDS[led], GPIO_OUT);
    }
}

void run_leds()
{
    uint nleds = sizeof(LEDS)/sizeof(uint);
    for (int led = 0; led < nleds; led++)
    {
        if (!run)
            break;
        gpio_put(LEDS[led], 1);
        uint tsleep = adc_read()/4 + 10;
        sleep_ms(tsleep);
        gpio_put(LEDS[led], 0);
    }
}

void init_rgb()
{
    uint slice_num[3];
    for (uint pin = 0; pin < 3; pin++) {
        gpio_set_function(RGB[pin], GPIO_FUNC_PWM);
        slice_num[pin] = pwm_gpio_to_slice_num(RGB[pin]);       
        pwm_set_clkdiv(slice_num[pin], 125);
        pwm_set_wrap(slice_num[pin], 1023);
        pwm_set_enabled(slice_num[pin], true);
    }
}

void change_color_rgb()
{
    uint red_duty_cycle = 0;
    uint green_duty_cycle = 0;
    uint blue_duty_cycle = 0;

    // Transition from Red to Green
    for (int i = 0; i <= PWM_RANGE; i++)
    {
        if (run)
            break;
        red_duty_cycle = PWM_RANGE - i;
        green_duty_cycle = i;
        pwm_set_gpio_level(RGB[0], red_duty_cycle);
        pwm_set_gpio_level(RGB[1], green_duty_cycle);
        sleep_ms(10);
    }

    // Transition from Green to Blue
    for (int i = 0; i <= PWM_RANGE; i++)
    {
        if (run)
            break;
        green_duty_cycle = PWM_RANGE - i;
        blue_duty_cycle = i;
        pwm_set_gpio_level(RGB[1], green_duty_cycle);
        pwm_set_gpio_level(RGB[2], blue_duty_cycle);
        sleep_ms(10);
    }

    // Transition from Blue to Red
    for (int i = 0; i <= PWM_RANGE; i++)
    {
        if (run)
            break;
        blue_duty_cycle = PWM_RANGE - i;
        red_duty_cycle = i;
        pwm_set_gpio_level(RGB[2], blue_duty_cycle);
        pwm_set_gpio_level(RGB[0], red_duty_cycle);
        sleep_ms(10);
    }
    if (run) {
        pwm_set_gpio_level(RGB[0], 0);
        pwm_set_gpio_level(RGB[1], 0);
        pwm_set_gpio_level(RGB[2], 0);
    }
}

int main() {
    stdio_init_all();
    printf("hallo\n");

    gpio_set_irq_enabled(BUTTON1, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(BUTTON2, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_callback(&gpio_callback);
    irq_set_enabled(IO_IRQ_BANK0, true);

    init_leds();
       
    adc_init();
    adc_gpio_init(ADC_INPUT);
    adc_select_input(0);

    init_rgb();

    while(1) {      
	    change_color_rgb();
        run_leds();    
    }
    return 0;
}
