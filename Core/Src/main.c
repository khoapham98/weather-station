#include "main.h"
#include "timer.h"
#include "dht11.h"

uint8_t data[5] = { 0 };
char data_correct = 0;

int main()
{
	TIM2_Init();
	DHT11_Init();

	while (1)
	{
		receive_data(data);
		data_correct = check_sum(data);
		delay_ms(1000);
	}
	return 0;
}
