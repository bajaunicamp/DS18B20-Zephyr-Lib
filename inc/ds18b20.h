#define CONFIG_SYS_CLOCK_TICKS_PER_SEC 100000000 // tempo entre ticks de 10 microssegundos

/**
 * @brief Obtém a leitura de temperatura do sensor. A temperatura é lida em graus Celsius e tem resolução de 0.0625.
 * 
 * @return Temperatura lida.
 */
float ds18b20_get_temperature();

