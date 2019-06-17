#ifndef CLIENT_H
#define CLIENT_H

typedef struct clients{
	long int num_permis;
	int date_naissance[3], date_permis[3];
	char prenom[15], nom[30];
}clients;

#endif
