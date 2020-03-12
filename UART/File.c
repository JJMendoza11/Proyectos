/*
 * File.c
 *
 *  Created on: 26 oct. 2019
 *      Author: lucky
 */


#include<stdio.h>
#include <stdlib.h>
#include "File.h"

FILE *MyFilePtr;

unsigned char File_vfnCreateFile ( void )
{

	MyFilePtr = fopen("C:\\Users\\lucky\\Desktop\\Lab3_Embe.txt", "w");

	if( MyFilePtr == NULL )
	{
		return 0;
	}
	else
	{
		fclose(MyFilePtr);
		return 1;
	}
}

unsigned char cnt= 0;

void File_vfnWriteOnFile ( unsigned char *Buffer, unsigned char SizeofBFF )
{
	MyFilePtr = fopen("C:\\Users\\lucky\\Desktop\\Lab3_Embe.txt", "r+");
	fseek(MyFilePtr, -1, SEEK_END);
		while(SizeofBFF)
		{
			fputc(*Buffer,MyFilePtr);
			SizeofBFF--;
			Buffer++;
		}
		fprintf(MyFilePtr, "\n");
	fclose(MyFilePtr);
}
