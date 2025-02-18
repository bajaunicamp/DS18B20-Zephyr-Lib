/**
 * @file
 * @brief Biblioteca para comunicação com sensor de temperatura.
 *
 * Este arquivo contém as definições e funções necessárias para inicialiazar 
 * e ler dados do sensor de temperatura de acordo com as necessidades da equipe
 * UNICAP Baja SAE
 *
 * @author Lucas Mendonça
 */

/**
 * @brief Tenta obter a leitura de temperatura do sensor. A temperatura é lida
 * em graus Celsius e tem resolução de 0.0625.
 * 
 * @return Caso consiga obter a temperatura, retorna a temperatura lida. Caso
 * não consiga obter a leitura do sensor, retorna FLT_MIN (da biblioteca float.h).
 */
float ds18b20_get_temperature();

