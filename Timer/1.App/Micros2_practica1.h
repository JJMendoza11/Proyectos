/*
 * Micros2_practica1.h
 *
 *  Created on: 22 sep. 2019
 *      Author: lucky
 */

#ifndef MICROS2_PRACTICA1_H_
#define MICROS2_PRACTICA1_H_

#define idle		 	0
#define Configuration	1
#define Run 			2
#define Pins2Use 		6
#define ClkVal 			1538
#define OneSeg 			790
#define TriggerBttn 	8

typedef enum{
	Left=20,
	Right,
	Up,
	Down,
	Conf=29,
	Start
}enPinConf;

void vfnState_Configuracion(void);
void vfnState_Run(void);
void vfnWhile(void);

#endif /* 1_APP_MICROS2_PRACTICA1_H_ */
