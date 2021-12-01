//Serial.h

#pragma once
#include "ftd2xx.h"

class CSerial
{
public:

  char TxBuffer[255];
  char RxBuffer[255];
  char numSerie[20]; // Le num�ro de s�rie de la carte

  //Constructor
  CSerial(void);

  //Destructor
  ~CSerial();

  //Print all FTDI devices serial number
  void listDevice(void);

  //Open communication
  bool open(char * p_serialNumber);

  //Configuration
  void config(void);

  //Ecriture de donn�es
  void CSerial::transmit_data(DWORD nbBytes);

  //Lecture de donn�es
  void CSerial::receive_data(DWORD nbBytes);

  //Close communication
  void close(void);

  // Retourne le nb de cartes connect�es. -1 si erreur
  DWORD CSerial::ret_nb_cartes_connectees(void);

  // Retourne le num�ro de s�rie de la carte connect�e : 1, 2, ..
  // Curieusement cette m�thode ne peut �tre appel�e qu'une seule fois
  // Retourne -1 si erreur, 0 sinon
  char* CSerial::ret_num_serie(DWORD numCarte);

protected:
   FT_STATUS m_ftStatus; 
   FT_HANDLE m_ftHandle;

	
};

