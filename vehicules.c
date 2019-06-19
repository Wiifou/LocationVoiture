#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"vehicules.h"
#include"liste.h"
#include"chaine.h"

//Initialise un maillon de la liste véhicule 
liste* getListeVehicule(FILE* file, liste** tete)
{
	char * donne;
	char ** tabdonne;
	int nb;
	donne=malloc(sizeof(char)*40);
	liste* maillon = NULL;
	maillon = malloc(sizeof(*maillon));
	maillon->suivant=NULL;
	maillon->data.vehicule=initialiseNullV();
	fscanf(file,"%s",donne);
	fonct(donne,&tabdonne,&nb,';');
	maillon->data.vehicule=initialiseVehi(tabdonne[0],tabdonne[1],tabdonne[2],atoi(tabdonne[3]),atoi(tabdonne[4]),*tabdonne[5]);
	maillon=ajouteVehiculeListe(maillon,tete);					//Ajoute avec la nouvelle voiture dans la liste
	return maillon;
}

vehicules initialiseVehi(char immat[10],char marque[15], char modele[15], short int millesime,int kilometrage, char categorie)
{
	vehicules v;
	strcpy(v.immat,immat);
	strcpy(v.marque,marque);
	strcpy(v.modele,modele);
	v.millesime=millesime;
	v.kilometrage=kilometrage;
	v.categorie=categorie;
	return v;
}

vehicules initialiseNullV()
{
	vehicules v; 
	strcpy(v.immat,"");
	strcpy(v.marque,"");
	strcpy(v.modele,"");
	v.millesime=0;
	v.kilometrage=0;
	v.categorie=0;
	v.teteResActu=NULL;
	return v;
}

//Ajoute un mailon  de type vehicule a la bonne place dans la liste
liste* ajouteVehiculeListe(liste* new,liste ** tete)
{
	liste* precedent=NULL;
	precedent = malloc(sizeof(*precedent));
	precedent->suivant=NULL;
	precedent=cherchePrecedentVoiture(new->data.vehicule.immat,*tete); 
	if(precedent==NULL)
	{
		new->suivant=*tete;
		*tete=new;
		
	}else{		
		new->suivant = precedent->suivant;
		precedent->suivant=new;
	}
	new->type = VEHICULE;
	return new;
}


//Cherhce le precedent maillon
liste *cherchePrecedentVoiture(char * n,liste * ptrtete)
{
	liste*ptr=ptrtete;
	liste*precendent=NULL;
	
	if(ptr!=NULL)

		while(ptr!=NULL && superieurTest(ptr->data.vehicule.immat,n)==0)
		{
			precendent=ptr;
			ptr=ptr->suivant;
		}
		return precendent;	
}
//revoie 1 si chaine 1 > chaine 2 dans l'alphabet
int superieurTest(char * chaine1,char* chaine2)
{
	int n=0;
	int r=0;
	do
	{
		if(chaine1[n]>chaine2[n])
		{
			r=1;
		}
		else if(chaine1[n]<chaine2[n])
		{
			r=0;
		}
		else
		{
			n++;
		}
			
	}while(chaine1[n]==chaine2[n]);
	return r;
}


liste *cherchePrecedentReservation(int n,liste * ptrtete)
{
	liste*ptr=ptrtete;
	liste*precendent=NULL;
		while(ptr!=NULL && ptr->data.reservation.num_reserv<n)
		{
			precendent=ptr;
			ptr=ptr->suivant;
		}
		return precendent;	
}


//Ajoute une reservation a une liste
liste* ajouteReservation(liste* new, liste ** tete)
{
	liste* precedent=NULL;
	precedent=cherchePrecedentReservation(new->data.reservation.num_reserv,*tete);
	
	if(precedent==NULL)
	{
		new->suivant=*tete;
		*tete=new;
		
	}else{		
		new->suivant = precedent->suivant;
		precedent->suivant=new;
	}
	new->type = RESERVATION;
	return new;
}
//Suprimme une reservation a une liste
liste * supprimeReservation(liste * supr,liste **tete)
{
	liste* precedent=NULL;
	precedent=cherchePrecedentReservation(supr->data.reservation.num_reserv,*tete);
	if(precedent==NULL)
	{
		*tete=supr->suivant;
		
	}else
	{
		precedent->suivant=supr->suivant;
	}
	supr->suivant=NULL;
	
	return supr;
}



void getListeClient(FILE* file, liste** tete)
{
	liste* maillon = NULL;
	char * donne;
	char ** tabdonne;
	char * ptrconver;
	int nb;
	int date_naissance[3];
	int date_permis[3];
	donne=malloc(sizeof(char)*40);
	maillon = malloc(sizeof(*maillon));
	maillon->data.client=initialiseNullC();
	fscanf(file,"%s",donne);
	
	fonct(donne,&tabdonne,&nb,';');
	Decoupedate(tabdonne[1],date_naissance);
	Decoupedate(tabdonne[2],date_permis);
	maillon->data.client=initialiseClient(strtol(tabdonne[0],&ptrconver,10),date_naissance,date_permis,tabdonne[3],tabdonne[4]);
	maillon=ajouteClientListe(maillon,tete);
}

clients initialiseNullC()
{
	clients c;
	c.num_permis=0;
	c.date_naissance[0]=0;
	c.date_naissance[1]=0;
	c.date_naissance[2]=0;
	c.date_permis[0]=0;
	c.date_permis[1]=0;
	c.date_permis[2]=0;
	strcpy(c.prenom,"");
	strcpy(c.nom,"");
	return c;
}
void Decoupedate(char * chaine,int date[3])
{
	int nb;
	char **tabdonne;
	tabdonne=malloc(sizeof(char)*4);
	fonct(chaine,&tabdonne,&nb,'/');
	date[0]=atoi(tabdonne[0]);
	date[1]=atoi(tabdonne[1]);
	date[2]=atoi(tabdonne[2]);
}

clients initialiseClient(long int num_permis,int date_naissance[3],int date_permis[3], char prenom[15],char nom[30])
{
	clients c;
	c.num_permis=num_permis;
	c.date_naissance[0]=date_naissance[0];
	c.date_naissance[1]=date_naissance[1];
	c.date_naissance[2]=date_naissance[2];
	c.date_permis[0]=date_permis[0];
	c.date_permis[1]=date_permis[1];
	c.date_permis[2]=date_permis[2];
	strcpy(c.prenom,prenom);
	strcpy(c.nom,nom);
	return c;
}

liste* ajouteClientListe(liste* new,liste ** tete)
{
	liste* precedent=NULL;
	precedent=cherchePrecedentClient(new->data.client.nom,*tete); 
	if(precedent==NULL)
	{
		new->suivant=*tete;
		*tete=new;
		
	}else{		
		new->suivant = precedent->suivant;
		precedent->suivant=new;
	}
	new->type = CLIENT;
	return new;
}
//Trier par nom de famille
liste *cherchePrecedentClient(char * n,liste * ptrtete)
{
	liste*ptr=ptrtete;
	liste*precendent=NULL;
		while(ptr!=NULL && superieurTest(ptr->data.client.nom,n)==0)
		{
			precendent=ptr;
			ptr=ptr->suivant;
		}
		return precendent;	
}


//Initialise la liste chaine de VOITURE et CLIENT et revoi ptrtete a partir des fichiers
liste* lireListe(int i)
{
	int nb;
	FILE* file;
	liste* tete = NULL;
	
	liste* (*ptrFonction)(FILE*,liste*);
	if(i == VEHICULE)
	{
		file = fopen("vehicules.csv", "rt");
		fscanf(file,"%d;marque;modele;millesime;kilometrage;categorie", &nb);
		ptrFonction = getListeVehicule;

	}
	else if (i == CLIENT)
	{
		file = fopen("client.csv", "rt");
		fscanf(file,"%d;num_permis;date_naissance;date_permis;prenom;nom", &nb);
		ptrFonction = getListeClient;
	}
	int cmp;
	for(cmp = 0; cmp < nb; cmp++)
	{
	 (*ptrFonction)(file,&tete);
	}
	fclose(file);
	return tete;
}

void getListeReservation(FILE* file, liste** tete,liste * ptrteteClient,liste * ptreTeteVoiture)
{
	liste* maillon = NULL;
	char * donne;
	donne=malloc(sizeof(char)*100);
	char ** tabdonne;
	int nb;
	char* ptrconver;
	int date_debut[3];
	int date_fin[3];
	maillon = malloc(sizeof(*maillon));
	fscanf(file,"%s",donne);
	fonct(donne,&tabdonne,&nb,';');
	Decoupedate(tabdonne[1],date_debut);
	Decoupedate(tabdonne[2],date_fin);
	maillon->data.reservation=initialiseRes(atoi(tabdonne[0]),date_debut,date_fin,strtol(tabdonne[3],&ptrconver,10),tabdonne[4]);
	maillon->data.reservation.veve = NULL;
	maillon->data.reservation.client = NULL;
	maillon->data.reservation.veve = detectVoiture(ptreTeteVoiture, maillon->data.reservation.immat);
	maillon->data.reservation.client = detectClient(ptrteteClient, maillon->data.reservation.num_permis);
	maillon=ajouteReservation(maillon,tete);
	return maillon;
}

reservations initialiseRes(int num_reserv, int date_debut[3], int date_fin[3], long int num_permis,char immat[10]){
	reservations r;
	r.num_reserv=num_reserv;
	r.date_debut[0]=date_debut[0];
	r.date_debut[1]=date_debut[1];
	r.date_debut[2]=date_debut[2];
	r.date_fin[0]=date_fin[0];
	r.date_fin[1]=date_fin[1];
	r.date_fin[2]=date_fin[2];
	r.num_permis=num_permis;
	strcpy(r.immat,immat);
	return r;
}

//Recherhce une voiture par rapport a l'immat
vehicules* detectVoiture(liste* tete, char  *immat)
{
	liste *maillon = tete;
	while(maillon != NULL && strcmp(maillon->data.vehicule.immat, immat)!=0)
	{
		maillon = maillon->suivant;
	}	
	
	vehicules* veve;
	if(maillon==NULL)
	{
		veve=NULL;
	}
	else
	{
	veve = &(maillon->data.vehicule);
	}
	return veve;
}

//Recherche par rapport au nom
clients* detectClient(liste* tete, long int num)
{
	liste* maillon = tete;
	while(num != maillon->data.client.num_permis  && maillon != NULL)
	{
		maillon = maillon->suivant;
	}
	clients* clicli;
	if(maillon==NULL)
	{
		return NULL;
	}
	clicli = &(maillon)->data.client;
	return clicli;
}


//Initialise la liste Reservation avec le fichier la liste client et voiture
liste* lireListeReservation(liste * ptrteteClient,liste * ptreTeteVoiture)
{
	int nb;
	FILE* file;
	liste* tete = NULL;
	
		file = fopen("reservations.csv", "rt");
		fscanf(file,"%d;num_reservation;date_debut;date_fin;num_permis;immatriculation", &nb);
		
		int cmp;
	for(cmp = 0; cmp < nb; cmp++)
	{
	
	getListeReservation(file,&tete,ptrteteClient,ptreTeteVoiture);
	}
	fclose(file);	
	return tete;
}


//Affiche la liste véhicule ou reservation a partir d'un pointeur tete
int CalcultailleChaine(liste *tete)
{
	liste* maillon=tete;
	int n;
	while (maillon !=NULL)
	{
		n++;
		maillon=maillon->suivant;
	}
	return n;
}

void ecritListeFichier(liste* tete)
{
	int nb;
	FILE* file;
	if(tete->type == VEHICULE)
	{
		nb=CalcultailleChaine(tete);
		file = fopen("vehicules.csv", "wt");
		fprintf(file,"%d;marque;modele;millesime;kilometrage;categorie\n", nb);
		for(int i=0;i<nb;i++){
			fprintf(file,"%s;%s;%s;%d;%d;%c\n",tete->data.vehicule.immat,tete->data.vehicule.marque,tete->data.vehicule.modele,tete->data.vehicule.millesime,tete->data.vehicule.kilometrage,tete->data.vehicule.categorie);
			tete = tete->suivant;
		}
	}
	else if (tete->type == CLIENT)
	{
		nb=CalcultailleChaine(tete);
		file = fopen("client.csv", "wt");
		fprintf(file,"%d;num_permis;date_naissance;date_permis;prenom;nom\n", nb);
		for(int i=0;i<nb;i++){
			fprintf(file,"%s;%d/%d/%d;%d/%d/%d;%s;%s\n", ajouteZero(tete->data.client.num_permis), tete->data.client.date_naissance[0], tete->data.client.date_naissance[1], tete->data.client.date_naissance[2], tete->data.client.date_permis[0],tete->data.client.date_permis[1], tete->data.client.date_permis[2], tete->data.client.prenom, tete->data.client.nom);
			tete = tete->suivant;
		}
	}
	else if (tete->type == RESERVATION)
	{
		nb=CalcultailleChaine(tete);
		file = fopen("reservations.csv", "wt");
		fprintf(file,"%d;num_reservation;date_debut;date_fin;num_permis;immatriculation\n", nb);

		for(int i=0;i<nb;i++){
			//~ printf("%d;%d/%d/%d;%d/%d/%d;%s;%s\n",tete->data.reservation.num_reserv,tete->data.reservation.date_debut[0],tete->data.reservation.date_debut[1],tete->data.reservation.date_debut[2],tete->data.reservation.date_fin[0],tete->data.reservation.date_fin[1],tete->data.reservation.date_fin[2],ajouteZero(tete->data.reservation.num_permis),tete->data.reservation.immat);
			fprintf(file,"%d;%d/%d/%d;%d/%d/%d;%s;%s\n",tete->data.reservation.num_reserv,tete->data.reservation.date_debut[0],tete->data.reservation.date_debut[1],tete->data.reservation.date_debut[2],tete->data.reservation.date_fin[0],tete->data.reservation.date_fin[1],tete->data.reservation.date_fin[2],ajouteZero(tete->data.reservation.num_permis),tete->data.reservation.immat);

			tete = tete->suivant;
	}
}
	fclose(file);
}

char* ajouteZero(long int x)
{
	int size;
	size = CalcultailleINT(x);
	int i;
	char dest[12];
	char * rest;
	rest=malloc(12*sizeof(char));
	for(i=0;i< 12- size; i++)
		{
			if(i==0){
				strcpy(dest,"0");
			}
			else{
				strcat(dest,"0");
			}
		}
		sprintf(rest,"%s%ld",dest,x);
		return rest;
}




int CalcultailleINT(long int Valeur) {
	int Retour = 0;

	if(Valeur < 0)
	{
		Retour++;
		Valeur = -1 * Valeur;
	}

	while(Valeur !=0)
	{
		Retour++;
		Valeur = Valeur / 10;
	}

	return Retour;
}





