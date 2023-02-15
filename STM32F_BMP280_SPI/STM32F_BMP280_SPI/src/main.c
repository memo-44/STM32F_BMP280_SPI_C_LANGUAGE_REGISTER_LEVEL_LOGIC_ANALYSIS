
#include "RccConfig.h"
#include "GpioConfig.h"
#include "Spi1Config.h"
#include "Timer7Config.h"
#include "BMP280_Def.h"

int main(void)
{
	SysClk();
	Gpio_Config();
	SPIConfig ();
	Timer7_Config();
	DEV_BMP280 Device={0,{0},{0},{0},{0}};
	Get_Temp_and_Press_ADC Temp_Press={0,0};


	SPIEnable();
    BMP280_Read_Id(&Device);
    Delay_us(350);
	Get_Calibration_Data(&Device);
	Delay_ms(10);
	BMP280_Config_Ctrl(&Device);
	Delay_ms(5);
	Get_Temp_and_Press_Value(&Temp_Press);
	Calculation_Temp_Value(&Device,&Temp_Press);
	Calculation_Press_Value(&Device,&Temp_Press);
	SPIDisable();

  while (1)
  {
	 GPIOD->BSRRL |=(1<<12);
	 Delay_ms(1000);
	 GPIOD->BSRRH |=(1<<12);
	 Delay_ms(1000);


  }

}


