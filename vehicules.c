#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"vehicules.h"
#include"liste.h"


//Initialise un maillon de la liste véhicule 
liste* getListeVehicule(FILE* file, liste** tete)
{

	liste* maillon = NULL;
	
	maillon = malloc(sizeof(*maillon));
	maillon->suivant=NULL;
	
	maillon->data.vehicule=initialiseNullV();
	fscanf(file, "%s;",maillon->data.vehicule.immat);
	fgetc(file);
	fgetc(file);										//Saisie les données  à partir du fichier
	fscanf(file, "%s;",maillon->data.vehicule.marque);
	fgetc(file);
	fgetc(file);
	fscanf(file, "%s;",maillon->data.vehicule.modele);
	fgetc(file);
	fgetc(file);
	fscanf(file, "%hd;",&maillon->data.vehicule.millesime);
	fscanf(file, "%d;",&maillon->data.vehicule.kilometrage);
	fscanf(file, "%c",&maillon->data.vehicule.categorie);
	maillon=ajouteVehiculeListe(maillon,tete);					//Ajoute avec la nouvelle voiture dans la liste
	return maillon;
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
	
		while(ptr!=NULL && superieurTest(ptr->data.vehicule.immat,n)==0)
		{
			precendent=ptr;
			ptr=ptr->suivant;
		}
		return precendent;	
}
//revoie 1 si chaine1 et dans l'alphabet par rapport à chaine 2
int superieurTest(char * chaine1,char* chaine2)
{
	int n=0;
	while(chaine1[n]==chaine2[n])
	{
		if(chaine1[n]<chaine2[n])
		{
			return 1;
		}
		else if(chaine1[n]<chaine2[n])
		{
			return 0;
		}
		else
		{
			n++;
		}
			
	}
	return 0;
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
	maillon = malloc(sizeof(*maillon));
	maillon->data.client=initialiseNullC();
	fscanf(file, "%ld;",&maillon->data.client.num_permis);
	fscanf(file, "%d/",&maillon->data.client.date_naissance[0]);
	fscanf(file, "%d/",&maillon->data.client.date_naissance[1]);
	fscanf(file, "%d;",&maillon->data.client.date_naissance[2]);
	fscanf(file, "%d/",&maillon->data.client.date_permis[0]);
	fscanf(file, "%d/",&maillon->data.client.date_permis[1]);
	fscanf(file, "%d;",&maillon->data.client.date_permis[2]);
	fscanf(file, "%s;",maillon->data.client.prenom);
	fgetc(file);
	fgetc(file);
	fscanf(file, "%s;",maillon->data.client.nom);
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

liste* ajouteClientListe(liste* new,liste ** tete)
{
	liste* precedent=NULL;
	precedent=cherchePrecedentVoiture(new->data.client.nom,*tete); 
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
	maillon = malloc(sizeof(*maillon));
	fscanf(file, "%d;",&maillon->data.reservation.num_reserv);
	fscanf(file, "%d/",&maillon->data.reservation.date_debut[0]);
	fscanf(file, "%d/",&maillon->data.reservation.date_debut[1]);
	fscanf(file, "%d;",&maillon->data.reservation.date_debut[2]);
	fscanf(file, "%d/",&maillon->data.reservation.date_fin[0]);
	fscanf(file, "%d/",&maillon->data.reservation.date_fin[1]);
	fscanf(file, "%d;",&maillon->data.reservation.date_fin[2]);
	fscanf(file, "%ld;",&maillon->data.reservation.num_permis);
	fscanf(file, "%s;",maillon->data.reservation.immat);
	maillon->data.reservation.veve = NULL;
	maillon->data.reservation.client = NULL;
	maillon->data.reservation.veve = detectVoiture(ptreTeteVoiture, maillon->data.reservation.immat);
	maillon->data.reservation.client = detectClient(ptrteteClient, maillon->data.reservation.num_permis);
	maillon=ajouteReservation(maillon,tete);
	return maillon;
}

//Recherhce une voiture par rapport a l'immat
vehicules* detectVoiture(liste* tete, char  *immat)
{
	liste *maillon = tete;
	//printf("Entre\n");
	//printf("Maillon : %s  \n",immat);
	
	while(maillon != NULL && strcmp(maillon->data.vehicule.immat, immat)!=0)
	{
		//printf("Maillon : %s  maillon :%p\n",maillon->data.vehicule.immat,maillon);
		maillon = maillon->suivant;
	}	
	//printf("Sortie avec maillon =%p \n",maillon);
	vehicules* veve=NULL;
	vehicules null;
	if(maillon==NULL)
	{
		null=initialiseNullV();
		veve=&null;
	}
	else
	{
	
	veve = &(maillon)->data.vehicule;
	
	}
	//printf("Sortie avec maillon =%p \n",veve->data.vehicule.immat);
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
		printf("Reservation : \n");	
		printf("%d;%d/%d/%d;%d/%d/%d;%ld;%s\n",maillon->data.reservation.num_reserv,maillon->data.reservation.date_debut[0],maillon->data.reservation.date_debut[1],maillon->data.reservation.date_debut[2],maillon->data.reservation.date_fin[0],maillon->data.reservation.date_fin[1],maillon->data.reservation.date_fin[2],maillon->data.reservation.num_permis,maillon->data.reservation.immat);
		printf("Voiture pointé : \n");
		printf("%s;%s;%s;%hd;%d;%c\n",maillon->data.reservation.veve->immat,maillon->data.reservation.veve->marque,maillon->data.reservation.veve->modele,maillon->data.reservation.veve->millesime,maillon->data.reservation.veve->kilometrage,maillon->data.reservation.veve->categorie);
		printf("Client pointé : \n");
		printf("%ld;%d/%d/%d;%d/%d/%d;%s;%s\n", maillon->data.reservation.client->num_permis, maillon->data.reservation.client->date_naissance[0], maillon->data.reservation.client->date_naissance[1], maillon->data.reservation.client->date_naissance[2], maillon->data.reservation.client->date_permis[0], maillon->data.reservation.client->date_permis[1], maillon->data.reservation.client->date_permis[2], maillon->data.reservation.client->prenom, maillon->data.reservation.client->nom);
		printf("\n");
		maillon = maillon->suivant;
		}
	else if(maillon->type == CLIENT)
	while(maillon != NULL)
		{
			printf("%ld;%d/%d/%d;%d/%d/%d;%s;%s\n", maillon->data.client.num_permis, maillon->data.client.date_naissance[0], maillon->data.client.date_naissance[1], maillon->data.client.date_naissance[2], maillon->data.client.date_permis[0], maillon->data.client.date_permis[1], maillon->data.client.date_permis[2], maillon->data.client.prenom, maillon->data.client.nom);
		maillon = maillon->suivant;
		}
}

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




