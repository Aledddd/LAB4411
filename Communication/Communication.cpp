// Communication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "serial.h"



int _tmain(int argc, _TCHAR* argv[])
{
	CSerial carte_1, carte_2;
	char c;
	DWORD nbCartesConnectees = 0;

	//Print all devices serial numbers
	carte_1.listDevice();

	nbCartesConnectees = carte_1.ret_nb_cartes_connectees();
	printf("Nombre de cartes connectees : %d\n", nbCartesConnectees);

	// Ouverture de la carte
	// Soit vous indiquez en argument le numéro de série de la carte, exemple : l_serial.open("DAYLHURK")
	//
	// Soit vous récupérez le numéro de série dynamiquement. 
	// En argument, 1 pour la première carte, 2 pour la 2e
	// C'est plus pratique si vous changez de carte entre les séances de TP
	if (carte_1.open(carte_1.ret_num_serie(1)) == true && carte_2.open(carte_2.ret_num_serie(2)) == true)
	{
		carte_1.TxBuffer[255] = {};
		carte_2.TxBuffer[255] = {};
		carte_1.RxBuffer[255] = {};
		carte_2.RxBuffer[255] = {};
		for (int i = 0; i < 100; i++) {
			carte_1.TxBuffer[i] = 'a';
			printf("%c ", carte_1.TxBuffer[i]);
		}
		printf("\n");
		while (1) {
			printf("Appuyer sur une touche : ");
			c = _getch();
			printf("\nTouche appuyée : %c\n", c);
			
			if (c != 'd') {
				while (carte_1.RxBuffer[0] != 'z') {
					printf("Carte_1 TX : ");
					carte_1.transmit_data(1);
					carte_2.receive_data(1);
					for (int i = 0; i < 100; i++) {
						carte_2.TxBuffer[0] = carte_2.RxBuffer[0] + 1;
					}
					printf("Carte_2 TX : ");
					carte_2.transmit_data(1);
					carte_1.receive_data(1);
					for (int i = 0; i < 100; i++) {
						carte_1.TxBuffer[0] = carte_1.RxBuffer[0] + 1;
					}
				}
			}
			else {
				carte_1.close();
				carte_2.close();
				exit(-1);
			}
			for (int i = 0; i < 100; i++) {
				carte_1.TxBuffer[i] = 'a';
				carte_1.RxBuffer[i] = NULL;
			}
		printf("\n");
		}
	}
	else {
		printf("!!! Echec ouverture de la carte\n");
	}

  _getch();
	return 0;
}

