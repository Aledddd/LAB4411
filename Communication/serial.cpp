//Serial.cpp
#include "stdafx.h"

#include "serial.h"

//Constructor
CSerial::CSerial(void)
{
  m_ftStatus=FT_OK;
  m_ftHandle=NULL;
}

//Destructor
CSerial::~CSerial()
{
  close();
}

//Print all FTDI devices serial number
void CSerial::listDevice(void)
{
  FT_STATUS l_ftStatus; 
  DWORD l_numDevs;

  l_ftStatus = FT_ListDevices(&l_numDevs,NULL,FT_LIST_NUMBER_ONLY);
  if (l_ftStatus == FT_OK) 
  { 
    char l_buffer[64];
    for (DWORD l_devIndex=0;l_devIndex<l_numDevs;l_devIndex++)
    {
      l_ftStatus = FT_ListDevices((PVOID)l_devIndex,l_buffer,FT_LIST_BY_INDEX|FT_OPEN_BY_SERIAL_NUMBER);
      if (l_ftStatus == FT_OK)
      {
        printf("%d: '%s'\n",l_devIndex,l_buffer);
      }
    }
  }
}




//Open communication
/// Return true if successful
bool CSerial::open(char * p_serialNumber)
{
  m_ftStatus = FT_OpenEx(p_serialNumber,FT_OPEN_BY_SERIAL_NUMBER,&m_ftHandle);
  if  (m_ftStatus==FT_OK)
    return true;
  printf("Erreur d'ouverture de carte ! %s \n",p_serialNumber);
  return false;
}

//Close communication
void CSerial::close(void)
{
  if (m_ftHandle!=NULL)
    FT_Close(m_ftHandle);
  m_ftHandle=NULL;
}
//Return the number of devices connected
DWORD CSerial::ret_nb_cartes_connectees(void)
{
	DWORD numDevs = 0;
	FT_STATUS ftStatus = FT_ListDevices(&numDevs, NULL, FT_LIST_NUMBER_ONLY);
	if (ftStatus == FT_OK) {
		// FT_ListDevices OK, number of devices connected is in numDevs 
	}
	else {  // FT_ListDevices failed 
		return -1;
	}

	return numDevs;
}
//Retour the serial number of the device
char* CSerial::ret_num_serie(DWORD numCarte)
{
	DWORD devIndex = numCarte - 1; // first device char Buffer[64]; // more than enough room! 
	FT_STATUS ftStatus = FT_ListDevices((PVOID)devIndex, numSerie, FT_LIST_BY_INDEX | FT_OPEN_BY_SERIAL_NUMBER);
	if (ftStatus == FT_OK) {
		// FT_ListDevices OK, serial number is in Buffer 
		return numSerie;
	}
	else {
		// FT_ListDevices failed 
		printf("!!! ret_num_serie() : Impossible enumerer les cartes\n");
		return numSerie;
	}

}
//Devices Configuration
void CSerial::config(void)
{
	DWORD BaudRate;
	UCHAR WordLenght;
	UCHAR StopBit;
	UCHAR ParityBit;
	int baud,features,flowcontrol;
	printf("Config BaudRate ? (0 no / 1 yes)\n");
	scanf_s("%d", &baud);
	// Set the BaudRate
	if (baud == 1) {
		printf("Saisir la BaudRate (entre 300 et 3000 Baud : max supporté par la carte): ");
		scanf_s("%d", &BaudRate);
		m_ftStatus = FT_SetBaudRate(m_ftHandle, BaudRate);
		if (m_ftStatus == FT_OK) {
			printf("BaudRate modifiée !\n");
		}
		else {
			printf("Problème de configuration !\n");
			exit(-1);
		}
	}		
	// Configure the features for data process 
	printf("Config Data Features ? (0 no / 1 yes)\n");
	scanf_s("%d", &features);
	if (features == 1) {

		printf("Saisir la longueur du mot en bits : ");
		scanf_s("%c", &WordLenght);
		printf("Saisir la valeur du bit de stop : ");
		scanf_s("%d", &StopBit);
		printf("Saisir la valeur du bit de parité : ");
		scanf_s("%d", &ParityBit);
		m_ftStatus = FT_SetDataCharacteristics(m_ftHandle, WordLenght, StopBit, ParityBit);

		if (m_ftStatus == FT_OK) {
			printf("Caractéristiques modifiées !\n");
		}
		else {
			printf("Problème de configuration !\n");
			exit(-1);
		}
	}
	// Configure the flowcontrol
	printf("Config Read & Write Timeouts ? (0 no / 1 yes)\n");
	scanf_s("%d", &flowcontrol);
	if (flowcontrol == 1) {

	}

}

//Transmit/Writing Data
void CSerial::transmit_data(DWORD nbBytes) {
	DWORD BytesWritten;
	FT_STATUS fStatus = FT_Write(m_ftHandle,TxBuffer, nbBytes, &BytesWritten);
	if (fStatus == FT_OK) {
		printf("%c\n", TxBuffer[0]); 
	}
	else {
		printf("Problème de configuration !\n");
	}
}
//Receiving/Reading Data
void CSerial::receive_data(DWORD nbBytes) {
	DWORD BytesReceived;
	FT_STATUS fStatus = FT_Read(m_ftHandle,RxBuffer,nbBytes,&BytesReceived);
	if (fStatus == FT_OK) {
		printf("%c\n", RxBuffer[0]);
		RxBuffer[0] +=1;
		TxBuffer[0] = RxBuffer[0];

	}
	else {
		printf("Problème de configuration !\n");
	}
}