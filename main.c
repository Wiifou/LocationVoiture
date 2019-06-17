#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"vehicules.h"
#include"liste.h"



int main(void)
{
	liste* vehicule;
	vehicule=lireListe(VEHICULE);
	afficheListe(vehicule);
	liste* client;
	client=lireListe(CLIENT);
	afficheListe(client);
	liste* reservation;
	reservation=lireListeReservation(client,vehicule);
	afficheListe(reservation);
	return 0;
}

