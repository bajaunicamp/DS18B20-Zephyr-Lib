# Biblioteca para uso do DS18B20

Essa biblioteca fornece o código necessário para controlar um sensor de temperatura DS18B20 a partir de um STM Blue Pill (STM32F103C6T6 ou STM32F103C8T6). 

## Como conectar o sensor
- Energize o STM
- Caso queira ler os logs do STM, conecte o RX de um leitor UART ao pino A9
- Conecte o fio GND (preto) ao ground.
- Conecte o fio VDD (vermelho) a uma fonte de tensão de 3 a 5.5V
- Conecte o fio DQ (amarelo) ao pino A1 do STM. Adicione a essa conexão um resistor de 4.7kΩ (veja o diagrama abaixo)
    - Para mudar esse pino, basta modificar o arquivo *stm32_min_dev_blue.overlay*. Se for fazer isso, verifique se o pino substituto apresenta diferenças significativas de hardware com relação ao pino A1, como uma resistência interna, por exemplo.

![diagrama de circuito do sensor](readme_src/circuito.png)

## Como usar a biblioteca
Sempre que quiser ler a temperatura do sensor, utilize a função **ds18b20_get_temperature()**. Note que há um valor de retorno da função (fora do intervalo de possíveis temperaturas lidas pelo sensor) que indica erro na leitura, então é necessário checar qual é o valor lido.

## Sobre os logs do STM
Caso haja algum problema ao se comunicar com o sensor, será emitido um log de erro.


## Possíveis problemas / problemas conhecidos
- O protocolo de comunicação OneWire possibilita a conexão de diversos sensores DS18B20 ao mesmo barramento, entretanto essa biblioteca consegue lidar com apenas um sensor.