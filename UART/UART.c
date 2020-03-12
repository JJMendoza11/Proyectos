/*
 * UART.c
 *
 *  Created on: 19 oct. 2019
 *      Author: lucky
 */


#include <Windows.h>
#include <stdio.h>
#include "UART.h"

			HANDLE hMyComm;                          // Handle to the Serial port
			char  ComPortName[] = "\\\\.\\COM5";   // Name of the Serial port(May Change) to be opened,
			BOOL  Status;                          // Status of the various operations
			DWORD dwEventMask;                     // Event mask to trigger
			char  TempChar;                        // Temporary Character
			char  SerialBuffer[256];               // Buffer Containing Rxed Data
			DWORD NoBytesRead = 0;                 // Bytes read by ReadFile()
			unsigned char i = 0;
			unsigned char j = 0;

	unsigned char UART_vfnCommInit( void )
		{
			/*---------------------------------- Opening the Serial Port -------------------------------------------*/

			hMyComm = CreateFile( ComPortName,                 // Name of the Port to be Opened
		                        GENERIC_READ | GENERIC_WRITE, // Read/Write Access
								0,                            // No Sharing, ports cant be shared
								NULL,                         // No Security
							    OPEN_EXISTING,                // Open existing port only
		                        0,                            // Non Overlapped I/O
		                        NULL);                        // Null for Comm Devices

			if (hMyComm == INVALID_HANDLE_VALUE)
			{
				printf("\n    Error! - Port %s can't be opened\n", ComPortName);
				return 0;
			}

			/*------------------------------- Setting the Parameters for the SerialPort ------------------------------*/

			DCB dcbSerialParams = { 0 };                         // Initializing DCB structure
			dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

			Status = GetCommState(hMyComm, &dcbSerialParams);      //retreives  the current settings

			if (Status == FALSE)
			{
				printf("\n    Error! in GetCommState()");
				return 0;
			}

			dcbSerialParams.BaudRate = CBR_115200;      // Setting BaudRate = 9600
			dcbSerialParams.ByteSize = 8;             // Setting ByteSize = 8
			dcbSerialParams.StopBits = ONESTOPBIT;    // Setting StopBits = 1
			dcbSerialParams.Parity = NOPARITY;        // Setting Parity = None

			Status = SetCommState(hMyComm, &dcbSerialParams);  //Configuring the port according to settings in DCB

			if (Status == FALSE)
				{
					printf("\n    Error! in Setting DCB Structure");
					return 0;
				}


			/*------------------------------------ Setting Timeouts --------------------------------------------------*/
			COMMTIMEOUTS timeouts = { 0 };
			timeouts.ReadIntervalTimeout         = 1;
			timeouts.ReadTotalTimeoutConstant    = 1;
			timeouts.ReadTotalTimeoutMultiplier  = 1;
			timeouts.WriteTotalTimeoutConstant   = 1;
			timeouts.WriteTotalTimeoutMultiplier = 1;

			if (SetCommTimeouts(hMyComm, &timeouts) == FALSE)
			{
				printf("\n\n    Error! in Setting Time Outs");
				return 0;
			}
			CloseHandle(hMyComm);
			return 1;
		}


			/*------------------------------------ Setting Receive Mask ----------------------------------------------*/

	unsigned char UART_vfnReceive(unsigned char *Buffer)
	{

		hMyComm = CreateFile( ComPortName,                 // Name of the Port to be Opened
	                        GENERIC_READ | GENERIC_WRITE, // Read/Write Access
							0,                            // No Sharing, ports cant be shared
							NULL,                         // No Security
						    OPEN_EXISTING,                // Open existing port only
	                        0,                            // Non Overlapped I/O
	                        NULL);                        // Null for Comm Devices

		if (hMyComm == INVALID_HANDLE_VALUE)
		{
			printf("\n    Error! - Port %s can't be opened\n", ComPortName);
			return 0;
		}

		/*------------------------------- Setting the Parameters for the SerialPort ------------------------------*/

		DCB dcbSerialParams = { 0 };                         // Initializing DCB structure
		dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

		Status = GetCommState(hMyComm, &dcbSerialParams);      //retreives  the current settings

		if (Status == FALSE)
		{
			while(!UART_vfnCommInit());
		}

			Status = SetCommMask(hMyComm, EV_RXCHAR); //Configure Windows to Monitor the serial device for Character Reception

			if (Status == FALSE)
			{
				printf("\n\n    Error! in Setting CommMask");
				return 0;
			}
	

           /*------------------------------------ Setting WaitComm() Event   ----------------------------------------*/

			Status = WaitCommEvent(hMyComm, &dwEventMask, NULL); //Wait for the character to be received

			/*-------------------------- Program will Wait here till a Character is received ------------------------*/

			if (Status == FALSE)
				{
					printf("\n    Error! in Setting WaitCommEvent()");
					return 0;
				}
			else //If  WaitCommEvent()==True Read the RXed data using ReadFile();
				{
					printf("\n\nCharacters Received...\n");
					do
						{
							Status = ReadFile(hMyComm, &TempChar, sizeof(TempChar), &NoBytesRead, NULL);
							SerialBuffer[i] = TempChar;
							i++;
							//printf("%c", TempChar);

					    }
					while (NoBytesRead > 0);

					for (j = 0; j < i-1; j++)
					{
						*Buffer = SerialBuffer[j];
						Buffer++;
					}

				}


				printf("\n\nClosing port..\n\n");
				CloseHandle(hMyComm);//Closing the Serial Port
				return 1;
		}
