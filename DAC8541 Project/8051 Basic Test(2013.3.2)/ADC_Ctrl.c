/*
*	Control functions of ADC on MPC82G516
*
*	|Author | Wayne
*	|Date   | 2013.3.2
* |Version| 1
*		
*	|NOTE   |	
*	
*/

#include <reg_mpc82g516.h>
#include "typedef.h"
#include "ADC_Ctrl.h"

//|Input| convert speed, channel used, current Channel
void SingleShot_Config(u8 speed,u8 channelUsed,u8 currentChannel){
	
	//Input Port Hi-Z Config selection
	P1M0|=channelUsed;
	P1M1&=~channelUsed;
	
	//clear ADCTL(ADCON,SPEED1~0,ADCI,ADCS,CHS2~0)
	ADCTL&=0x00;
	//set the required details
	ADCTL|=ADCON|speed|currentChannel;
	
}

//To use this function, SingleShot_Config should be processed
u16 SingleShot_Process(void){

	//starting a convertion
	ADCTL|=ADCS;
	//Wait until finished(flag set)
	while(ADCTL&ADCI!=0x10);
	//clear ADCI
	ADCTL&=~ADCI;
	
	//return the concatenated result value	
	return ADCH*4+ADCL;
	
}

