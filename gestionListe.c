#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"vehicules.h"
#include"liste.h"
#include"gestionListe.h"

//Affiche n'importe quelle liste 
void afficheListe(liste* tete)
{
	liste* maillon = tete;
	if(maillon->type == VEHICULE)
		while(maillon != NULL)
		{
			printf("%s;%s;%s;%hd;%d;%c\n",maillon->data.vehicule.immat,maillon->data.vehicule.marque,maillon->data.vehicule.modele,maillon->data.vehicule.millesime,maillon->data.vehicule.kilometrage,maillon->data.vehicule.categorie);
			
		maillon = maillon->suivant;
		}
	else if(maillon->type == RESERVATION)
		while(maillon != NULL)
		{
		printf("%d;%d/%d/%d;%d/%d/%d;%ld;%s\n",maillon->data.reservation.num_reserv,maillon->data.reservation.date_debut[0],maillon->data.reservation.date_debut[1],maillon->data.reservation.date_debut[2],maillon->data.reservation.date_fin[0],maillon->data.reservation.date_fin[1],maillon->data.reservation.date_fin[2],maillon->data.reservation.num_permis,maillon->data.reservation.immat);
		printf("Voiture pointé : \n");
		printf("%s;%s;%s;%hd;%d;%c\n",maillon->data.reservation.veve->immat,maillon->data.reservation.veve->marque,maillon->data.reservation.veve->modele,maillon->data.reservation.veve->millesime,maillon->data.reservation.veve->kilometrage,maillon->data.reservation.veve->categorie);
		printf("Client pointé : \n");
		printf("%ld;%d/%d/%d;%d/%d/%d;%s;%s\n", maillon->data.reservation.client->num_permis, maillon->data.reservation.client->date_naissance[0], maillon->data.reservation.client->date_naissance[1], maillon->data.reservation.client->date_naissance[2], maillon->data.reservation.client->date_permis[0], maillon->data.reservation.client->date_permis[1], maillon->data.reservation.client->date_permis[2], maillon->data.reservation.client->prenom, maillon->data.reservation.client->nom);

		maillon = maillon->suivant;
		}
	else if(maillon->type == CLIENT)
	while(maillon != NULL)
		{
			printf("%ld;%d/%d/%d;%d/%d/%d;%s;%s\n", maillon->data.client.num_permis, maillon->data.client.date_naissance[0], maillon->data.client.date_naissance[1], maillon->data.client.date_naissance[2], maillon->data.client.date_permis[0], maillon->data.client.date_permis[1], maillon->data.client.date_permis[2], maillon->data.client.prenom, maillon->data.client.nom);
		maillon = maillon->suivant;
		}
}

void menu(liste **Lvoiture,liste **client,liste **Lreservation )
{
	char cmd[20];
	while(strcmp(cmd,"quit")!=0)
	{
		printf("> ");
		scanf("%s",cmd);
		if(strcmp(cmd,"affichelistes")==0)
		{
			afficheListe(*Lvoiture);
			printf("\n");
			afficheListe(*client);
			printf("\n");
			afficheListe(*Lreservation);
		}
		if(strcmp(cmd,"ajoutevoiture")==0)
		{
			ajouteVoiture(Lvoiture);
		}
		if(strcmp(cmd,"ajoutereservation")==0)
		{
			ajouteReservationScan(Lreservation,*Lvoiture,*client,CalcultailleChaine(*Lreservation));
		}
		if(strcmp(cmd,"affichehisto")==0)
		{
			afficheHisto(*Lvoiture);
		}
		if(strcmp(cmd,"test")==0)
		{
			int d[3];
			int dd[3];
			d[0]=1;
			d[1]=3;
			d[2]=2000;
			dd[0]=1;
			dd[1]=4;
			dd[2]=1999;
			printf("%d/%d/%d  test %d/%d/%d egale %d\n",d[0],d[1],d[2],dd[0],dd[1],dd[2],superDate(d,dd));
		}
	}
	
}
//Affiche l'hosto d'une voiture a partir de son immat
void afficheHisto(liste * voiture)
{
	liste * maillon;
	char immat[10];
	int test=1;
	vehicules * ptrV;
	while(test)
	{
		printf("Immatriculation : ");
		scanf("%s",immat);
		if(strlen(immat)==9 && immat[2]=='-' && immat[6]=='-')
		{
			test=0;
		}
	}
	ptrV=detectVoiture(voiture,immat);
	
	if(ptrV==NULL)
	{
		printf("Il n'y a aucune voiture avec cette plaque\n");
	}
	else
	{
		maillon=ptrV->teteResActu;
		while(maillon!=NULL)
		{
			printf("Réservé du %d/%d/%d au %d/%d/%d\n",maillon->data.historique.res->date_debut[0],maillon->data.historique.res->date_debut[1],maillon->data.historique.res->date_debut[2],maillon->data.historique.res->date_fin[0],maillon->data.historique.res->date_fin[1],maillon->data.historique.res->date_fin[2]);
			maillon=maillon->suivant;
		}
	}
}


//Ajoute une voiture dans la liste chaine
void ajouteVoiture(liste ** Lvoiture)
{
	
	char immat[10];
	char marque[15];
	char modele[15];
	short int millesime;
	int kilometrage;
	char categorie;
	int test=1;
	
	liste* maillon = NULL;
	maillon = malloc(sizeof(*maillon));
	maillon->suivant=NULL;
	
	while(test)
	{
		printf("Immatriculation : ");
		scanf("%s",immat);
		if(strlen(immat)==9 && immat[2]=='-' && immat[6]=='-')
		{
			test=0;
		}
	}
	test=1;
	printf("Modele : ");
	scanf("%s",modele);
	printf("Marque : ");
	scanf("%s",marque);
	printf("Millesime : ");
	scanf("%hu",&millesime);
	printf("Kilometrage : ");
	scanf("%d",&kilometrage);
	printf("Categorie : ");
	scanf("%c",&categorie);
	maillon->data.vehicule=initialiseNullV();
	maillon->data.vehicule=initialiseVehi(immat,marque,modele,millesime,kilometrage,categorie);
	maillon=ajouteVehiculeListe(maillon,Lvoiture);	
}
//Pour chaque voiture met en place sa liste chainer de reservation
void SetListeResActuVoiture(liste * voiture,liste *reservation)
{
	liste* res;
	res=reservation;
	vehicules* ptrvoiture;
	while (res !=NULL)
	{
		ptrvoiture=detectVoiture(voiture, res->data.reservation.immat);	
		InitialiseChaineParVoiture(ptrvoiture,&res->data.reservation);
		res=res->suivant;
	}
}
void InitialiseChaineParVoiture(vehicules* v,reservations * reservation)
{
	
	liste* new;
	new = malloc(sizeof(*new));
	new->type = HISTO;
	new->suivant=v->teteResActu;
	new->data.historique.res=reservation;
	v->teteResActu=new;
}

void ajouteReservationScan(liste ** Lres, liste * voiture, liste* Lclient,int taille)
{	
	
	int date_debut[3];
	int date_fin[3];
	
	
	int testReservation=1;
	
	while(testReservation)
	{
		printf("Date_debut : \n ");
		printf("Jour : ");
		scanf("%d",&date_debut[0]);
		printf("Mois :  ");
		scanf("%d",&date_debut[1]);
		printf("Année :  ");
		scanf("%d",&date_debut[2]);
		
		printf("Date_fin : \n ");
		printf("Jour :  ");
		scanf("%d",&date_fin[0]);
		printf("Mois :  ");
		scanf("%d",&date_fin[1]);
		printf("Année :  ");
		scanf("%d",&date_fin[2]);
		ChoixVehicule(voiture,date_debut,date_fin);
	}
}
//Choisi le vehicule idéal pour un reservation
void ChoixVehicule(liste * voiture,int date_debut[3],int date_fin[3])
{
	char immat[10];
	vehicules * ptrV;
	int test=1;
	int x;
	while(test)
		{
			printf("Immatriculation : ");
			scanf("%s",immat);
			if(strlen(immat)==9 && immat[2]=='-' && immat[6]=='-')
			{
				test=0;
			}
			ptrV=detectVoiture(voiture,immat);
			if(ptrV==NULL)
			{
				printf("Il n'y a aucune voiture avec cette plaque\n");
			}
			else
			{
				x=TestHistoDate(date_debut,date_fin,*ptrV);
				printf("x=%d\n",x);
				if(x==1)
				{
					printf("Cette voiture n'est pas libre à ces dates\n");
				}
			}
			
		}
}
//Parcour la liste histo d'une voiture et renvoi 1 si une date ce chevauche
int TestHistoDate(int date_debut[3],int date_fin[3], vehicules v)
{
	liste * maillon;
	int test=0;
	maillon=v.teteResActu;
	while (maillon!=NULL && test!=1)
	{
		test=seChevauche(date_debut,date_fin,maillon->data.historique.res->date_debut,maillon->data.historique.res->date_fin);
		maillon=maillon->suivant;
	}
	return test;
}

//Compre 2 intervalle de chaine et renvoie 1 si elle se chevauche
int seChevauche(int date_debut1[3],int date_fin1[3],int date_debut2[3],int date_fin2[3])
{
	if(superDate(date_debut1,date_debut2)){
		if(superDate(date_fin2,date_debut1)){
			return 1;
		}
		else{
			return 0;
		}
	}
	else
	{
		if(superDate(date_fin1,date_debut2)){
			return 1;
		}
		else{
			return 0;
		}
	}
	
	
}
//Compare 2 dates 1 et 2 et renvoi 1 si d1>d2
int superDate(int date1[3],int date2[3])
{
	if(date1[2]==date2[2])
	{
		if(date1[1]==date2[1])
		{
			return superInt(date1[0],date2[0]);
		}
		else
		{
			return superInt(date1[1],date2[1]);
		}
	}
	else
	{
		return superInt(date1[2],date2[2]);
	}
}
//Compare 2 nombre et renvoie 1 si le premeier et superieur au second
int superInt(int x,int y)
{
	if(x>y)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}




