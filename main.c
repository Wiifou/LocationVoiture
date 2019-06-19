#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"vehicules.h"
#include"liste.h"
#include"gestionListe.h"


int main(void)
{
	//Initialisation des listes
	liste* vehicule;
	vehicule=lireListe(VEHICULE);
	
	liste* client;
	client=lireListe(CLIENT);
	liste* reservation;
	reservation=lireListeReservation(client,vehicule);
	
	
	//Mise a jour de voiture avec les infos de reservations
	SetListeResActuVoiture(vehicule,reservation);
	
	//Acces au menu
	menu(&vehicule,&client,&reservation);
	//Sauvegarde
	
	ecritListeFichierClient(client);
	ecritListeFichierVoiture(vehicule);
	ecritListeFichierReservation(reservation);
	
	
	return 0;
}

