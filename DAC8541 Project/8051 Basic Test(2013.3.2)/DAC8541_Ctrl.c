/*
*	Control functions of DAC8541 Parallel 16 bit DAC.
*
*	|Author | Wayne
*	|Date   | 2013.2.23
* |Version| 1
*		
*	|NOTE   | P0->Control,P0.0~P0.7(CS,RW,LDAC,RST,RSTSEL,BTCUSB,PD1,PD0)
*						P2->Bit0~Bit7(P2.0~P2.7)
*						P3->Bit8~Bit15(P3.0~P3.7)	
*/

#include <reg_mpc82g516.h>
#include "typedef.h"
#include "delaytime.h"
#include "DAC8541_Ctrl.h"

void DAC8541_Init(void){
	
	//IO Port Mode Config.
	P0M0=0x00;
	P0M1=0xff;		//Set P0(Control) PP output.
	P2M0=0x00;
	P2M1=0x00;		//Set P2 Bi-dir.
	P3M0=0x00;
	P3M1=0x00;		//Set P3 Bi-dir.
	
	//Control Signal Initialation Config.
	CS=1;		           //Set CS high.
	BTCUSB=0;          //Set BTCUSB low(unipolar straight binary).
	PD1=0;	           //Set PD1 low(Disable power down mode).
	PD0=0;		         //Set PD0 low(Disable power down mode).
	ResetDAC(resetToMid);       //Reset to mid-scale
	
}

void ResetDAC(u8 resetMode){
	
	RST=0;     //Set RST low.
	if(resetMode==resetToMid)    RSTSEL=1;  //Set RSTSEL high(reset to mid-scale).
	else if(resetMode==resetToMin)    RSTSEL=0;  //Set RSTSEL low(reset to min-scale).
	//defualt?
	RST=1;     //Set RST high(rising edge trigger).
	
}

void WriteDAC(u16 value){		//Single shot Writing.    //write BTC mode function?
	
	LDAC=0;            //Set LDAC low.
	RW=0;		           //Set RW low(write mode).
		
	//Set value to IO.
	LByte=value&0xff;
	HByte=(value>>8)&0xff;
	
	CS=0;		           //Set CS low(enable activity,let input data into DAC register).
	
	//Load value on the register to DAC output.
	LDAC=1;            //Set LDAC high(rising edge trigger).
	
	CS=1;							 //Set CS high(disable activity,latch data in register).
}
