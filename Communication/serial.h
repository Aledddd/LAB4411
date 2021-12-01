//Serial.h

#pragma once
#include "ftd2xx.h"

class CSerial
{
public:

  char TxBuffer[255];
  char RxBuffer[255];
  char numSerie[20]; // Le numéro de série de la carte

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

  //Ecriture de données
  void CSerial::transmit_data(DWORD nbBytes);

  //Lecture de données
  void CSerial::receive_data(DWORD nbBytes);

  //Close communication
  void close(void);

  // Retourne le nb de cartes connectées. -1 si erreur
  DWORD CSerial::ret_nb_cartes_connectees(void);

  // Retourne le numéro de série de la carte connectée : 1, 2, ..
  // Curieusement cette méthode ne peut être appelée qu'une seule fois
  // Retourne -1 si erreur, 0 sinon
  char* CSerial::ret_num_serie(DWORD numCarte);

protected:
   FT_STATUS m_ftStatus; 
   FT_HANDLE m_ftHandle;

	
};

