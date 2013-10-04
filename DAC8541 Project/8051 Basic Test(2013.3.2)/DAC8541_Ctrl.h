/*
*
*/

#include "typedef.h"

#ifndef _DAC8541_Ctrl_
#define _DAC8541_Ctrl_

	#define CS     P00
	#define RW     P01
	#define LDAC   P02
	#define RST    P03
	#define RSTSEL P04
	#define BTCUSB P05
	#define PD1    P06
	#define PD0    P07
	
	#define CtrlIO P0
	#define HByte  P3
	#define LByte  P2
	
	#define resetToMid 1
	#define resetToMin 0
	
	void DAC8541_Init(void);
  void ResetDAC(u8 resetMode);
	void WriteDAC(u16 value);

#endif

