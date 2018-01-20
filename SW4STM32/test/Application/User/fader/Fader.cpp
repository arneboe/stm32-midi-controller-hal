#include <fader/Fader.h>
#include <hardwareSetup/Hardware.h>

Fader Faders::faders[NUM_FADERS];
static uint16_t adcValues[NUM_FADERS] = {0};

void Fader::update(uint16_t adcValue)
{

}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	for(int i = 0; i < NUM_FADERS; ++i)
	{
		Faders::faders[i].update(adcValues[i]);
	}

	//start next reading
	if (HAL_ADC_Start_DMA(&Hardware::adc1, (uint32_t*)adcValues, NUM_FADERS) != HAL_OK)
	{
		Hardware::ErroHandler(__FILE__, __LINE__, "fader dma error");
	}
}

void Faders::start()
{
	if (HAL_ADC_Start_DMA(&Hardware::adc1, (uint32_t*)adcValues, NUM_FADERS) != HAL_OK)
	{
		Hardware::ErroHandler(__FILE__, __LINE__, "fader dma error");
	}
}
