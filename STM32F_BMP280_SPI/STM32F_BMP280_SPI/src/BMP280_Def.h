/*
 * BMP280_Def.h
 *
 *  Created on: 3 Kas 2022
 *      Author: mehme
 */

#include "RccConfig.h"

#ifndef BMP280_DEF_H_
#define BMP280_DEF_H_

		//Define BMP280 chip id
#define BMP280_Id 0x58

		//Define BMP280 Register Address
#define Base_Reg_Adr       ((uint8_t)0xF3)  //Base address is status register address same time.
#define Ctrl_Meas_Reg_Adr  (Base_Reg_Adr+0x01)
#define Config_Reg_Adr     (Base_Reg_Adr+0x02)
#define Press_Msb_Reg_Adr  (Base_Reg_Adr+0x04)
#define Press_Lsb_Reg_Adr  (Base_Reg_Adr+0x05)
#define Press_XLsb_Reg_Adr (Base_Reg_Adr+0x06)
#define Temp_Msb_Reg_Adr   (Base_Reg_Adr+0x07)
#define Temp_Lsb_Reg_Adr   (Base_Reg_Adr+0x08)
#define Temp_XLsb_Reg_Adr  (Base_Reg_Adr+0x09)

#define Reset_Reg_Adr      ((uint8_t)0xE0)
#define Chip_Id_Reg_Adr	   ((uint8_t)0xD0)

		//Define Calibration Parameters Register Address
#define Dig_T1_Lsb_Reg_Adr ((uint8_t)0x88) //Dig_T1_Lsb is first address of Calibration Parameters
#define Dig_T1_Msb_Reg_Adr (Dig_T1_Lsb_Reg_Adr+0x01)
#define Dig_T2_Lsb_Reg_Adr (Dig_T1_Lsb_Reg_Adr+0x02)
#define Dig_T2_Msb_Reg_Adr (Dig_T1_Lsb_Reg_Adr+0x03)
#define Dig_T3_Lsb_Reg_Adr (Dig_T1_Lsb_Reg_Adr+0x04)
#define Dig_T3_Msb_Reg_Adr (Dig_T1_Lsb_Reg_Adr+0x05)
#define Dig_P1_Lsb_Reg_Adr (Dig_T1_Lsb_Reg_Adr+0x06)
#define Dig_P1_Msb_Reg_Adr (Dig_T1_Lsb_Reg_Adr+0x07)
#define Dig_P2_Lsb_Reg_Adr (Dig_T1_Lsb_Reg_Adr+0x08)
#define Dig_P2_Msb_Reg_Adr (Dig_T1_Lsb_Reg_Adr+0x09)
#define Dig_P3_Lsb_Reg_Adr (Dig_T1_Lsb_Reg_Adr+0x0A)
#define Dig_P3_Msb_Reg_Adr (Dig_T1_Lsb_Reg_Adr+0x0B)
#define Dig_P4_Lsb_Reg_Adr (Dig_T1_Lsb_Reg_Adr+0x0C)
#define Dig_P4_Msb_Reg_Adr (Dig_T1_Lsb_Reg_Adr+0x0D)
#define Dig_P5_Lsb_Reg_Adr (Dig_T1_Lsb_Reg_Adr+0x0E)
#define Dig_P5_Msb_Reg_Adr (Dig_T1_Lsb_Reg_Adr+0x0F)
#define Dig_P6_Lsb_Reg_Adr (Dig_T1_Lsb_Reg_Adr+0x10)
#define Dig_P6_Msb_Reg_Adr (Dig_T1_Lsb_Reg_Adr+0x11)
#define Dig_P7_Lsb_Reg_Adr (Dig_T1_Lsb_Reg_Adr+0x12)
#define Dig_P7_Msb_Reg_Adr (Dig_T1_Lsb_Reg_Adr+0x13)
#define Dig_P8_Lsb_Reg_Adr (Dig_T1_Lsb_Reg_Adr+0x14)
#define Dig_P8_Msb_Reg_Adr (Dig_T1_Lsb_Reg_Adr+0x15)
#define Dig_P9_Lsb_Reg_Adr (Dig_T1_Lsb_Reg_Adr+0x16)
#define Dig_P9_Msb_Reg_Adr (Dig_T1_Lsb_Reg_Adr+0x17)


			//Define Crtl_Meas Register Parameters value
//Define Power Mode

#define SleepMode  ((uint8_t)0x00)
#define ForcedMode ((uint8_t)0x01)
#define NormalMode ((uint8_t)0x03)

//Define Pressure Oversampling

#define Press_Osx1  ((uint8_t)0x01)
#define Press_Osx2  ((uint8_t)0x02)
#define Press_Osx4  ((uint8_t)0x03)
#define Press_Osx8  ((uint8_t)0x04)
#define Press_Osx16 ((uint8_t)0x05)

//Define Temperature Oversampling

#define Temp_Osx1  ((uint8_t)0x01)
#define Temp_Osx2  ((uint8_t)0x02)
#define Temp_Osx4  ((uint8_t)0x03)
#define Temp_Osx8  ((uint8_t)0x04)
#define Temp_Osx16 ((uint8_t)0x05)

		//Define Config Register Parameters Value

//Define number of Spi communication wire

#define spi3w_En  ((uint8_t)0x01)  // To use 3 wire for SPI Interface
#define spi3w_Dis ((uint8_t)0x00) // To use 3 wire for SPI Interface

//Define IIR Filter Parameters Value

#define Filter_Off       ((uint8_t)0x00)
#define Filter_Coeff_2   ((uint8_t)0x01)
#define Filter_Coeff_4   ((uint8_t)0x02)
#define Filter_Coeff_8   ((uint8_t)0x03)
#define Filter_Coeff_16  ((uint8_t)0x04)

//Define Standby Time Parameters Value

#define Tstandby_0_5  ((uint8_t)0x00)
#define Tstandby_62_5 ((uint8_t)0x01)
#define Tstandby_125  ((uint8_t)0x02)
#define Tstandby_250  ((uint8_t)0x03)
#define Tstandby_500  ((uint8_t)0x04)
#define Tstandby_1000 ((uint8_t)0x05)
#define Tstandby_2000 ((uint8_t)0x06)
#define Tstandby_4000 ((uint8_t)0x07)

//Define Soft Reset

#define Soft_Reset ((uint8_t)0xB6)

//To form Ctrl_Meas register
typedef struct{

	uint8_t mode:2;
	uint8_t osrs_p:3;
	uint8_t osrs_t:3;

}ctrl_meas;

//To form Config register
typedef struct{

	uint8_t spi_3w_enable:1;
	uint8_t reserved:1;
	uint8_t IIrFilter:3;
	uint8_t t_sb:3;
}config;

//Define Compensation Parameter Data Type In Structer

typedef struct{

	uint16_t dig_T1;
	int16_t dig_T2;
	int16_t dig_T3;
	uint16_t dig_P1;
	int16_t dig_P2;
	int16_t dig_P3;
	int16_t dig_P4;
	int16_t dig_P5;
	int16_t dig_P6;
	int16_t dig_P7;
	int16_t dig_P8;
	int16_t dig_P9;

}Calibration_Value;


typedef struct{
	int32_t Temp_Value;
	uint32_t Press_Value;
}Get_Temp_and_Press_ADC;

typedef struct{

	int32_t Temp_Value;
	int32_t Press_Value;
	int32_t t_fine;
}Result_of_Temp_and_Press;

typedef struct{

	uint8_t Device_Id;
	ctrl_meas Ctrl_Meas_Reg;
	config Config_Reg;
	Calibration_Value Cali_Val;
	Result_of_Temp_and_Press Results;

}DEV_BMP280;

//Defines Functions
void BMP280_Read_Id(DEV_BMP280 *Dev);
void BMP280_Config_Ctrl(DEV_BMP280 *Dev);
void SPIWrite(uint8_t RegAdr,uint8_t Value);
void SPIRead(uint8_t RegAdr,uint8_t *Data,uint8_t Size);
void Get_Calibration_Data(DEV_BMP280 *Dev);
void Get_Temp_and_Press_Value(Get_Temp_and_Press_ADC *Temp_Press);
void Calculation_Temp_Value(DEV_BMP280 *Dev,const Get_Temp_and_Press_ADC *Temp_Press);
void Calculation_Press_Value(DEV_BMP280 *Dev,const Get_Temp_and_Press_ADC *Temp_Press);

#endif /* BMP280_DEF_H_ */
