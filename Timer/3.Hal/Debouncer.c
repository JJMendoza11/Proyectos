#include "Debouncer.h"
#include "GPIODriver.h"
#include "Timer.h"
#include "Micros2_practica1.h"


tstDbncrInfo astPinsData[enTotalPins];

uint_8 Dbncr_vfnRiseDec(uint_8 SearchPin);

void DbncrInit(uint_8 PinVal){
	static uint_8 u8Index=0;
		astPinsData[u8Index].Pin=PinVal;
		u8Index++;
}

void Dbncr(uint_8 u8Pin2Check){
	astPinsData[u8Pin2Check].u8Shots[astPinsData[u8Pin2Check].u8Cntr]=GPIO_u8fnReadPin(astPinsData[u8Pin2Check].Pin);
	if(astPinsData[u8Pin2Check].u8Shots[astPinsData[u8Pin2Check].u8Cntr]!=astPinsData[u8Pin2Check].u8Stablestate){
		astPinsData[u8Pin2Check].u8Cntr++;
	}else{
		astPinsData[u8Pin2Check].u8Cntr=0;
	}

	if(astPinsData[u8Pin2Check].u8Shots[0]==astPinsData[u8Pin2Check].u8Shots[LastValue]){
		astPinsData[u8Pin2Check].LastStableState=astPinsData[u8Pin2Check].u8Stablestate;
		astPinsData[u8Pin2Check].u8Stablestate=astPinsData[u8Pin2Check].u8Shots[LastValue];
		astPinsData[u8Pin2Check].u8Cntr=0;
	}else{
		/*No Used*/
	}

}

uint_8 Dbncr_vfnRiseDec(uint_8 SearchPin){
	if((astPinsData[SearchPin].LastStableState==0)&&(astPinsData[SearchPin].u8Stablestate==1)){
		return 1;
	}else{
		return 0;
	}
}


void Check_Left_Bttn(void){
	Dbncr(enPin1);
	if(Dbncr_vfnRiseDec(enPin1)){
		Timer_vfnShiftLeft();
	}else{
		/*No Used*/
	}
}

void Check_Right_Bttn(void){
	Dbncr(enPin2);
	if(Dbncr_vfnRiseDec(enPin2)){
		Timer_vfnShiftRight();
	}else{
		/*No Used*/
	}
}



void Check_Up_Bttn(void){
	Dbncr(enPin3);
	if(Dbncr_vfnRiseDec(enPin3)){
		Timer_vfnShiftUp();
	}else{
		/*No Used*/
	}
}

void Check_Down_Bttn(void){
	Dbncr(enPin4);
	if(Dbncr_vfnRiseDec(enPin4)){
		Timer_vfnShiftDown();
	}else{
		/*No Used*/
	}
}

void Check_Conf_Bttn(void){
	Dbncr(enPin5);
	if(Dbncr_vfnRiseDec(enPin5)){
		vfnState_Configuracion();
	}else{
		/*No Used*/
	}
}

void Check_Run_Bttn(void){
	Dbncr(enPin6);
	if(Dbncr_vfnRiseDec(enPin6)){
		vfnState_Run();
	}else{
		/*No Used*/
	}
}


