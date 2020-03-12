
#include "Micros2_practica1.h"
#include "GPIODriver.h"
#include "Debouncer.h"
#include "Timer.h"

typedef unsigned short uint16;

void vfnRun_Check(void);

static uint16 u16Clk=ClkVal;
uint16 u8Seg=0;
uint16 u16TimerClk=0;
uint8  u8_20mS=0;
uint8 au8Pins2Use[Pins2Use]={Left,Right,Up,Down,Conf,Start};
uint8 StateMachineVal=0;

int main(void){

	GPIO_vfnDriverInit();
	GPIO_vfnLEDriverInit();
	GPIO_vfnDriverInptsInit(&au8Pins2Use[0],sizeof(au8Pins2Use));

	while(1){
		vfnWhile();
		u8Seg++;
		u8_20mS++;
		if(u8Seg==OneSeg){
			GPIO_vfnToggleLEd();
		}
	if (StateMachineVal==idle){
			Timer_vfnIdle();
			if (u8_20mS==TriggerBttn){
				u8_20mS=0;
				Check_Conf_Bttn();
				Check_Run_Bttn();
			}else{
				/*No Used*/
			}
		}
		else if (StateMachineVal==Configuration){
			if (u8_20mS==TriggerBttn){
				u8_20mS=0;
				Check_Conf_Bttn();
				Check_Left_Bttn();
				Check_Right_Bttn();
				Check_Up_Bttn();
				Check_Down_Bttn();
				Check_Run_Bttn();
			}else{
				/*No Used*/
			}
		}
		else if (StateMachineVal==Run){
			u16TimerClk++;
			if (u8_20mS==TriggerBttn)
			{
				u8_20mS=0;
				Check_Conf_Bttn();
				Check_Run_Bttn();
			}else{
				/*No used*/
			}
			if((u16TimerClk==OneSeg)&&(StateMachineVal==Run)){
				vfnTMR();
				vfnRun_Check();
				u16TimerClk=0;
			}else{
				/*No Used*/
			}
			Timer_vfnIdle();
		}
		if(u8Seg==OneSeg){
			u8Seg=0;
		}else{
			/*No used*/
		}
	}
	return 0;
}


void vfnWhile(void){
	while(u16Clk){
		u16Clk--;
	}
	u16Clk=ClkVal; //32500 será una macro
}

void vfnState_Configuracion(void){
	if(StateMachineVal==Configuration){
		StateMachineVal=idle;
	}else{
		StateMachineVal=Configuration;
	}
}

void vfnState_Run(void){
	if(StateMachineVal==Run){
		StateMachineVal=idle;
	}else{
		vfnRun_Check();
	}
}

void vfnRun_Check(void){
	if(vfnCheckTimer()){
		StateMachineVal=Run;
		u16TimerClk=0;
	}else{
		StateMachineVal=idle;
	}
}

