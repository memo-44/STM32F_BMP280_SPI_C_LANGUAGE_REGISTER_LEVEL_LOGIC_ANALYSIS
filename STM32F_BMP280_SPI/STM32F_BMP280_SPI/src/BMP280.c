/*
 * BMP280.c
 *
 *  Created on: 3 Kas 2022
 *      Author: mehme
 */


#include "BMP280_Def.h"
#include "Spi1Config.h"
#include "Timer7Config.h"


void SPIWrite(uint8_t RegAdr,uint8_t Value){

	SPINCss();
	uint8_t Data[2];
	RegAdr=RegAdr&0x7F;
	Data[0]=RegAdr;
	Data[1]=Value;
	SPITrans(Data,2);
	SPICss();

}

void SPIRead(uint8_t RegAdr,uint8_t *Data,uint8_t Size){


	SPINCss();
	RegAdr=RegAdr|0x80;
	SPITrans(&RegAdr,1);
	SPIReceive(Data,Size);
	SPICss();


}
void BMP280_Read_Id(DEV_BMP280 *Dev){

	uint8_t Data[1],i=0;
	SPIWrite(Reset_Reg_Adr,Soft_Reset);//RESET BMP280
	Delay_ms(4);
	SPIRead(Chip_Id_Reg_Adr,Data,1);//GET DEVICE ID of BMP280
	Delay_us(10);

	/*IF WE DON'T GET DEVICE ID,TO TRY GIVEN FOLLOWING WHILE LOOP*/
	while(BMP280_Id!=Data[0]){
		Delay_us(250);
		if(i==5){
	/*IF WE STILL DON'T HAVE DEVICE ID,AFTER 5 TIMES TRAILS,IT WILL RESET AGAIN.*/
			SPIWrite(Reset_Reg_Adr,Soft_Reset);
			Delay_us(200);
		}

		SPIRead(Chip_Id_Reg_Adr,Data,1);
		i++;

		/*IF WE STILL DON'T HAVE DEVICE ID,AFTER 10 TIMES TRAILS,IT WILL LEAVE IN WHILE LOOP.*/
		if(i==10)
		break;

	}


		/*IF WE HAVE DEVICE ID,TO CONFIGURE MODE,DIGITAL INTERFACE,FILTER ETC.*/
	if(BMP280_Id==Data[0]){

		Dev->Device_Id=BMP280_Id;
		Dev->Ctrl_Meas_Reg.mode=NormalMode;
		Dev->Ctrl_Meas_Reg.osrs_p=Press_Osx16;
		Dev->Ctrl_Meas_Reg.osrs_t=Temp_Osx2;
		Dev->Config_Reg.spi_3w_enable=spi3w_Dis;
		Dev->Config_Reg.IIrFilter=Filter_Coeff_16;
		Dev->Config_Reg.t_sb=Tstandby_0_5;

	}
	/*IF WE DON'THAVE DEVICE ID,TO WRITE ERROR*/
	else{

		 //WRITE ERROR LINE
		 GPIOD->BSRRL |=(1<<13);
		 Delay_ms(1350);
	     GPIOD->BSRRH |=(1<<13);
	     Delay_ms(1350);
	     i=0;
	}
	i=0;

}

	/*TO GET COMPENSATION PARAMETER with THIS FUNCTION.
	 *YOU CAN LOOK on 21.PAGE in DATASHEET FOR DETAILED EXPLANATIONS
	 */
void Get_Calibration_Data(DEV_BMP280 *Dev){

	uint8_t CalData[24]={0},i,j=0;

	for(i=0;i<24;i+=2){

		SPIRead((Dig_T1_Lsb_Reg_Adr+i),(&CalData[i]),2);
		Delay_us(50);

		/*IF READ VALUE is ZERO,THAT VALUE READ AGAIN*/
		while(CalData[i]==0 && CalData[i+1]==0)//YOU CAN ADD TRIM VALUE TO WHILE LOOP CONDITIONS
		{
			Delay_us(500);
			SPIRead((Dig_T1_Lsb_Reg_Adr+i),(&CalData[i]),2);
			j++;
			/*IF WE STILL DON'T ANY DATA,AFTER 10 TIMES TRAILS,IT WILL LEAVE IN WHILE LOOP.*/
			if(j==10)
			break;
		}
		if(j==10){
			/*****************************************************/
			//WRITE ERROR LINE
			//YOU CAN GIVE INFORMATION ABOUT ERROR ANOTHER with FUNCTION
			//FOR EXAMPLE YOU CAN DEFINE ERROR NUMBER.TO COMPARE ERROR NUMBER with
			//RETURN VALUE FROM FUNCTION,AFTER THAT TO WRITE ERROR to LCD,LED,SEVENSEGMENT ETC.
			//THUS,YOU CAN DETECT TO MAKE MISTAKE in WHICH LEVEL.
			/********************************************************************/
			GPIOD->BSRRL |=(1<<14);
	     	Delay_ms(1350);
	        GPIOD->BSRRH |=(1<<14);
		    Delay_ms(1350);

		}
		else{

			Dev->Cali_Val.dig_T1=((CalData[1]<<8) | CalData[0]);
			Dev->Cali_Val.dig_T2=((CalData[3]<<8) | CalData[2]);
			Dev->Cali_Val.dig_T3=((CalData[5]<<8) | CalData[4]);
			Dev->Cali_Val.dig_P1=((CalData[7]<<8) | CalData[6]);
			Dev->Cali_Val.dig_P2=((CalData[9]<<8) | CalData[8]);
			Dev->Cali_Val.dig_P3=((CalData[11]<<8) | CalData[10]);
			Dev->Cali_Val.dig_P4=((CalData[13]<<8) | CalData[12]);
			Dev->Cali_Val.dig_P5=((CalData[15]<<8) | CalData[14]);
			Dev->Cali_Val.dig_P6=((CalData[17]<<8) | CalData[16]);
			Dev->Cali_Val.dig_P7=((CalData[19]<<8) | CalData[18]);
			Dev->Cali_Val.dig_P8=((CalData[21]<<8) | CalData[20]);
			Dev->Cali_Val.dig_P9=((CalData[23]<<8) | CalData[22]);
		}
	}

}



/*
 *THIS FUNCTION SET BIT POSITION IN REGISTER AND ASSING REGISTER VALUE WITH RESPECT TO
 *REGISTER ADDRESS.YOU CAN LOOK THROUGH on 24. PAPER in BMP280 DATASHEET FOR MORE INFORMATION.
 */

static int8_t Set_Reg_Bit_Position_and_Value(const DEV_BMP280 *Dev,uint8_t RegAdr){

	uint8_t Value=0;
	if(Ctrl_Meas_Reg_Adr==RegAdr){

		Value=(Dev->Ctrl_Meas_Reg.osrs_t<<5)|(Dev->Ctrl_Meas_Reg.osrs_p<<2)|(Dev->Ctrl_Meas_Reg.mode<<0);
		return Value;
	}

	if(Config_Reg_Adr==RegAdr){

		Value=(Dev->Config_Reg.t_sb<<5)|(Dev->Config_Reg.IIrFilter<<2)|(Dev->Config_Reg.spi_3w_enable<<0);
		return Value;
	}

	return 0;
}




/*
 *THIS FUNCTION WRITE VALUE BOTH CONFIG REGISTER AND CTRL REGISTER.
 */

void BMP280_Config_Ctrl(DEV_BMP280 *Dev){



	if(BMP280_Id==Dev->Device_Id){	//CHECK ID

		SPIWrite(Ctrl_Meas_Reg_Adr,Set_Reg_Bit_Position_and_Value(Dev,Ctrl_Meas_Reg_Adr));
		Delay_us(250);
		SPIWrite(Config_Reg_Adr,Set_Reg_Bit_Position_and_Value(Dev,Config_Reg_Adr));

	}

}



/*
 *THIS FUNCTION TAKE RAW TEMPERATURE MEASUREMENT OUTPUT DATA AND RAW PRESURE MEASUREMENT
 *OUTPUT DATA.YOU CAN LOOK THROUGH BETWEEN on 24. PAPERS AND  on 27. PAPERS
 *in BMP280 DATASHEET FOR MORE INFORMATION.
 */

void Get_Temp_and_Press_Value(Get_Temp_and_Press_ADC *Temp_Press){

	uint8_t Temp[3]={0};
	uint8_t Press[3]={0};

	SPIRead(Press_Msb_Reg_Adr,(&Press[0]),3);

	do{

	    Delay_ms(25);
	    SPIRead(Press_Msb_Reg_Adr,(&Press[0]),3);

	}while(0x80==Press[0]);//0X80 is RESET STATE VALUE FOR press_msb REGISTER
	//TO SKIP READING OTHER PRESSURE REGISTER AS LONG AS press_msb VALUE EQUAL TO 0x80

	Temp_Press->Press_Value=(int32_t)((((uint32_t) (Press[0])) << 12) | (((uint32_t) (Press[1])) << 4) | ((uint32_t)Press[2]>>4));


	SPIRead(Temp_Msb_Reg_Adr,(&Temp[0]),3);
	do{

		Delay_ms(20);
		SPIRead(Temp_Msb_Reg_Adr,(&Temp[0]),3);

	}while(0x80==Temp[0]);//0X80 is RESET STATE VALUE FOR temp_msb REGISTER
	//NOT READ OTHER PRESSURE REGISTER AS LONG AS temp_msb VALUE EQUAL TO 0x80

	Temp_Press->Temp_Value=(int32_t)((((int32_t)(Temp[0]))<<12)|(((int32_t)(Temp[1]))<<4)|(((int32_t)(Temp[2]))>>4));



}



/*
 *THIS IS CALCULATED TEMPERATURE VALUE BY USED RAW TEMPERATURE MEASUREMENT DATAS AND
 *COMPENSATION PARAMETERS.
 *YOU CAN LOOK THROUGH BETWEEN on 22. PAPERS AND  on 23. PAPERS in BMP280 DATASHEET FOR
 *MORE INFORMATION.
 */

void Calculation_Temp_Value(DEV_BMP280 *Dev,const Get_Temp_and_Press_ADC *Temp_Press){

	int32_t Var1,Var2;

	Var1=((((Temp_Press->Temp_Value>>3)-((int32_t)Dev->Cali_Val.dig_T1<<1)))*((int32_t)Dev->Cali_Val.dig_T2))>>11;

	Var2=(((((Temp_Press->Temp_Value>>4)-((int32_t)Dev->Cali_Val.dig_T1))*((Temp_Press->Temp_Value>>4)
			-((int32_t)Dev->Cali_Val.dig_T1)))>>12)*((int32_t)Dev->Cali_Val.dig_T3))>>14;

	Dev->Results.t_fine=(Var1+Var2);

	Dev->Results.Temp_Value=(Dev->Results.t_fine*5+128)>>8;
	Dev->Results.Temp_Value=Dev->Results.Temp_Value*0.01;


}



/*
 *THIS IS CALCULATED PRESSURE VALUE BY USED RAW TEMPERATURE MEASUREMENT DATAS AND
 *COMPENSATION PARAMETERS.
 *YOU CAN LOOK THROUGH BETWEEN on 22. PAPERS AND  on 23. PAPERS in BMP280 DATASHEET FOR
 *MORE INFORMATION.
 */

void Calculation_Press_Value(DEV_BMP280 *Dev,const Get_Temp_and_Press_ADC *Temp_Press){

	int64_t Var1,Var2;

	 Var1 = ((int64_t)(Dev->Results.t_fine/2))-64000;
	 Var2 = Var1 * Var1 * ((int64_t) Dev->Cali_Val.dig_P6)/32768;
	 Var2 = Var2 + Var1 * ((int64_t) Dev->Cali_Val.dig_P5)*2;
	 Var2 = (Var2/4) + (((int64_t) Dev->Cali_Val.dig_P4) * 65536);
	 Var1 = (((int64_t) Dev->Cali_Val.dig_P3)*Var1*Var1/524288+((int64_t) Dev->Cali_Val.dig_P2)*Var1)/524288;
	 Var1 = (1+Var1/32768)*((int64_t) Dev->Cali_Val.dig_P1);

	 Dev->Results.Press_Value=1048576-(int64_t)Temp_Press->Press_Value;
	 Dev->Results.Press_Value=(Dev->Results.Press_Value-(Var2/4096))*6250/Var1;
	 Var1=((int64_t)Dev->Cali_Val.dig_P9)*Dev->Results.Press_Value*Dev->Results.Press_Value/2147483648;
	 Var2=Dev->Results.Press_Value*((int64_t)Dev->Cali_Val.dig_P8)/32768;
	 Dev->Results.Press_Value=Dev->Results.Press_Value+(Var1+Var1+((int64_t)Dev->Cali_Val.dig_P7))/16;


}
