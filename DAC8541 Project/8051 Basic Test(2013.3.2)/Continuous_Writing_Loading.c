#include <reg_mpc82g516.h>
#include "typedef.h"
#include "delaytime.h"
#include "ADC_Ctrl.h"
#include "DAC8541_Ctrl.h"

void Timer1_8Bit_Auto_Reload_StartUp(u8 loadLength);

void main(void){
	
	SingleShot_Config(period_270,UseP10,CurrentP10);
	
	//Init Process
	P1=0xff;
	DAC8541_Init();
	P1=0x00;
	delay(1000);
	P1=0xff;
	delay(1000);
	
	//Four testing outputs
	//Value 1 (1/4 of AVCC)
	WriteDAC(16383);
	P1=0x00;
	delay(1000);
	P1=0xff;
	delay(1000);
	
	//Value 2 (3/4 of AVCC)
	WriteDAC(49151);
	P1=0x00;
	delay(1000);
	P1=0xff;
	delay(1000);
	
	//Value 3 (1/8 of AVCC)
	WriteDAC(8191);
	P1=0x00;
	delay(1000);
	P1=0xff;
	delay(1000);
	
	//Value 4 (MAX of AVCC)
	WriteDAC(65535);
	P1=0x00;
	delay(1000);
	P1=0xff;
	delay(1000);
	
	//delay shows that system going into continuous loading state
	delay(2000);
	
	Timer1_8Bit_Auto_Reload_StartUp(50);
	
	while(1){
		
	}
}

void Timer1_8Bit_Auto_Reload_StartUp(u8 loadLength){
	
	//Stop Timer1
	TR1=0;
	//Disable Timer1 interrupt(clear ET1)
	IE&=0xF7;	
	
	//clear Timer1's Mode(M1, M0)
	TMOD&=0xDF;
	//set Timer1's Mode(M1, M0) as 8 Bit Auto-Reload Mode
	TMOD|=0x20;
	
	//clear AUXR2's T1X12
	AUXR2&=0xBF;
	//set AUXR2's T1X12(select Fosc as Timer1's Source)
	AUXR2|=0x40;
	
	//set loadLength
	TL1=loadLength;
	TH1=loadLength;
	
	//This will set ET1 and EA(in case of EA is not enabled)
	IE|=0x88;
	
	//Start Timer1
	TR1=1;

}

void Timer1_INT(void) interrupt 3
{
	u16 value_get=SingleShot_Process()*64;
	//P12=~P12;
	
	//if(value_get<=16320)		WriteDAC(8160);
	if(value_get<=32704)		WriteDAC(24544);
	//else if(value_get<=49088)		WriteDAC(40928);
	else if(value_get<=65472)		WriteDAC(57312);
	
}
