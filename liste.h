#ifndef LISTE_H
#define LISTE_H

#include"vehicules.h"
#include"reservation.h"
typedef struct histo{
	int nbreparation;
	struct reservations *res;
}histo;

typedef enum typeListe{
	VEHICULE, RESERVATION, CLIENT, HISTO
}typeListe;

union datas{
	vehicules vehicule;
	reservations reservation;
	clients client;
	histo historique;
};

typedef struct liste{
	int type;
	union datas data;
	struct liste *suivant;
}liste;



liste* lireListe(int i);
void lireListeT(void);
liste *cherchePrecedentVoiture(char* n,liste * ptrtete);
int superieurTest(char * chaine1,char* chaine2);
liste* ajouteVehiculeListe(liste* new,liste ** tete);
liste* ajouteReservation(liste* new, liste ** tete);
vehicules* detectVoiture(liste* tete, char immat[10]);

vehicules initialiseNullV();
clients initialiseNullC();
liste *cherchePrecedentClient(char * n,liste * ptrtete);
liste* ajouteClientListe(liste* new,liste ** tete);
liste* lireListeReservation(liste * ptrteteClient,liste * ptreTeteVoiture);
void getListeReservation(FILE* file, liste** tete,liste * ptrteteClient,liste * ptreTeteVoiture);
int CalcultailleChaine(liste *tete);
clients* detectClient(liste* tete, long int num);
vehicules initialiseVehi(char immat[10],char marque[15], char modele[15], short int millesime,int kilometrage, char categorie);

int CalcultailleINT(long int Valeur);
char* ajouteZero(long int x);
void ecritListeFichierClient(liste* tete);
void ecritListeFichierReservation(liste * tete);
void ecritListeFichierVoiture(liste * tete);
clients initialiseClient(long int num_permis,int date_naissance[3],int date_permis[3], char prenom[15],char nom[30]);
void Decoupedate(char * chaine,int date[3]);
reservations initialiseRes(int num_reserv, int date_debut[3], int date_fin[3], long int num_permis,char immat[10]);

#endif
