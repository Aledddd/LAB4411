// Communication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "serial.h"



int _tmain(int argc, _TCHAR* argv[])
{
  CSerial carte_1,carte_2;
  DWORD nbCartesConnectees = 0;

  //Print all devices serial numbers
  carte_1.listDevice();

  nbCartesConnectees = carte_1.ret_nb_cartes_connectees();
  printf("Nombre de cartes connectees : %d\n", nbCartesConnectees);

  // Ouverture de la carte
  // Soit vous indiquez en argument le num�ro de s�rie de la carte, exemple : l_serial.open("DAYLHURK")
  //
  // Soit vous r�cup�rez le num�ro de s�rie dynamiquement. 
  // En argument, 1 pour la premi�re carte, 2 pour la 2e
  // C'est plus pratique si vous changez de carte entre les s�ances de TP
  if (carte_1.open(carte_1.ret_num_serie(1))==true && carte_2.open(carte_2.ret_num_serie(2)) == true)
  {
	  /*printf("Config BandRate carte_1...\n");
	  carte_1.config();
	  printf("Config BandRate carte_2...\n");
	  carte_2.config();*/
	  carte_1.TxBuffer[0] = 'a';
	  /*carte_1.transmit_data(1);
	  carte_2.receive_data(1);
	  carte_2.TxBuffer[0] += 1;
	  carte_2.transmit_data(1);
	  carte_1.receive_data(1);*/
	// while (carte_1.RxBuffer[0] != 'c' || carte_2.RxBuffer[0] != 'c') {
		 printf("Carte_1 TX : ");
		carte_1.transmit_data(1);
		printf("Carte_2 RX : ");
		carte_2.receive_data(1);
		printf("Carte_2 TX : ");
		carte_2.transmit_data(1);
		printf("Carte_1 RX : ");
		carte_1.receive_data(1);
	// }
	  carte_1.close();
	  carte_2.close();
  }
  else {
	  printf("!!! Echec ouverture de la carte\n");
  }



  _getch();
	return 0;
}

