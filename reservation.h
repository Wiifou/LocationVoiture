#ifndef RESERVATION_H
#define RESERVATION_H

#include"vehicules.h"
#include"client.h"

typedef struct reservations{
	int num_reserv;
	int date_debut[3];  //date jj/mm/aa
	int date_fin[3];
	long int num_permis;
	char immat[10];
	vehicules *veve;
	clients *client;
}reservations;

#endif
