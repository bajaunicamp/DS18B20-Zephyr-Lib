#include "ds18b20.h"
#include <zephyr/kernel.h>
#include <stdlib.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>
#include <float.h>

LOG_MODULE_DECLARE();

static const struct gpio_dt_spec *const w1 =
    &(const struct gpio_dt_spec)GPIO_DT_SPEC_GET(DT_PATH(zephyr_user), gpios);

// Utiliza a contagem de ciclos do processador para criar delays de microssegundos
static void delay_us(uint32_t tempo_microssegundos){
  uint32_t val = k_cycle_get_32();
  uint32_t current_time = val;
  uint32_t tempo_cyc = k_us_to_cyc_floor32(tempo_microssegundos);
  while (abs(val - current_time) < tempo_cyc) {
    current_time = k_cycle_get_32();
  }
}

static uint8_t ds18b20_start(){
    if(!device_is_ready(w1)){
      LOG_ERR("O dispositivo não está pronto para ser usado.");
      return -1;
    }
    uint8_t ret;

    gpio_pin_configure_dt(w1, GPIO_OUTPUT);

    gpio_pin_set_dt(w1, 0);
    delay_us(480);

    gpio_pin_configure_dt(w1, GPIO_INPUT);
    delay_us(80);

    if (!gpio_pin_get_dt(w1))
        ret = 0;
    else
        LOG_ERR("Não houve resposta de presença do sensor.");
        ret = -1;

    delay_us(400);
    return ret;
}

// Transmite um byte pelo protocolo de comunicação OneWire para o sensor.
static void ds18b20_write(uint8_t data){
  gpio_pin_configure_dt(w1, GPIO_OUTPUT);

  for (int i = 0; i < 8; i++) {
    if ((data & (1 << i)) != 0) // if the bit is high
    {
      // write 1
      gpio_pin_configure_dt(w1, GPIO_OUTPUT);
      gpio_pin_set_dt(w1, 0);
      delay_us(1); // wait for 1 us

      gpio_pin_configure_dt(w1, GPIO_INPUT);
      delay_us(60); // wait for 60 us
    }

    else // if the bit is low
    {
      // write 0
      gpio_pin_configure_dt(w1, GPIO_OUTPUT);
      gpio_pin_set_dt(w1, 0);
      delay_us(60); // wait for 60 us

      gpio_pin_configure_dt(w1, GPIO_INPUT);
    }
  }
}

// Lê um byte enviado pelo sensor através do protocolo OneWire.
static uint8_t ds18b20_read(){
  uint8_t value = 0;
  gpio_pin_configure_dt(w1, GPIO_INPUT);

  for (int i = 0; i < 8; i++) {
    gpio_pin_configure_dt(w1, GPIO_OUTPUT);
    gpio_pin_set_dt(w1, 0);
    delay_us(2);                                // wait for 2 us
    gpio_pin_configure_dt(w1, GPIO_INPUT);
    if (gpio_pin_get_dt(w1)) // if the pin is HIGH
    {
      value |= 1 << i; // read = 1
    }
    delay_us(60); // wait for 60 us
  }
  return value;
}

float ds18b20_get_temperature(){
    if(ds18b20_start()) return FLT_MIN;
    ds18b20_write(0xCC);    // skip ROM
    ds18b20_write(0x44);    // convert t

    if(ds18b20_start()) return FLT_MIN;
    ds18b20_write(0xCC);    // skip ROM
    ds18b20_write(0xBE);    // Read Scratch-Pad

    float temperature = ds18b20_read();
    temperature += ds18b20_read() << 8;
    temperature /= 16.0;

    return temperature;
}
