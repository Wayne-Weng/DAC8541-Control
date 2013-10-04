/*
*
*/

#include "typedef.h"

#ifndef _ADC_Ctrl_
#define _ADC_Ctrl_

	#define ADCON 0x80
	#define period_270 0x60
	#define period_360 0x40
	#define period_540 0x20
	#define period_1080 0x00
	
	#define UseP10 0x01
	#define UseP11 0x02
	#define UseP12 0x04
	#define UseP13 0x08
	#define UseP14 0x10
	#define UseP15 0x20
	#define UseP16 0x40
	#define UseP17 0x80
	
	#define CurrentP10 0x00
	#define CurrentP11 0x01
	#define CurrentP12 0x02
	#define CurrentP13 0x03
	#define CurrentP14 0x04
	#define CurrentP15 0x05
	#define CurrentP16 0x06
	#define CurrentP17 0x07
	
	#define ADCI 0x10
	#define ADCS 0x08
	
	void SingleShot_Config(u8 speed,u8 channelUsed,u8 currentChannel);
	u16 SingleShot_Process(void);

#endif