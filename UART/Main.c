/*
 * Main.c
 *
 *  Created on: 26 oct. 2019
 *      Author: lucky
 */

#include<stdio.h>
#include <stdlib.h>
#include "UART.h"
#include "File.h"

unsigned char buffer [255] = "";
static unsigned char *Myptr = &buffer[0];

int main ( void )
{
	if(UART_vfnCommInit())
	{
		if(File_vfnCreateFile())
			printf("Ready to receive information.");
	}
	while (1)
	{
		while(UART_vfnReceive(Myptr)==0){

		}
		 File_vfnWriteOnFile(Myptr, sizeof(buffer));
	}
	return 0;
}
