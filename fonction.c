void ecritListe(liste* tete)
{
	int nb;
	FILE* file;
	if(tete->type == VEHICULE)
	{
		file = fopen("vehicules.csv", "rt");
		fscanf(file,"%d", &nb);
		file = fopen("vehicules.csv", "wt");
		fprintf(file,"%d;marque;modele;millesime;kilometrage;categorie\n", nb);
		for(int i=0;i<nb;i++){
			fprintf(file,"%s;%s;%s;%d;%d;%c\n",tete->data.vehicule.immat,tete->data.vehicule.marque,tete->data.vehicule.modele,tete->data.vehicule.millesime,tete->data.vehicule.kilometrage,tete->data.vehicule.categorie);
			tete = tete->suivant;
		}
	}
	else if (tete->type == CLIENT)
	{
		file = fopen("client.csv", "rt");
		fscanf(file,"%d", &nb);
		file = fopen("client_1.csv", "wt");
		fprintf(file,"%d;num_permis;date_naissance;date_permis;prenom;nom\n", nb);
		for(int i=0;i<nb;i++){
			fprintf(file,"%s;%d/%d/%d;%d/%d/%d;%s;%s\n", ajouteZero(tete->data.client.num_permis), tete->data.client.date_naissance[0], tete->data.client.date_naissance[1], tete->data.client.date_naissance[2], tete->data.client.date_permis[0],tete->data.client.date_permis[1], tete->data.client.date_permis[2], tete->data.client.prenom, tete->data.client.nom);
			tete = tete->suivant;
		}
	}
	else if (tete->type == RESERVATION)
	{
		file = fopen("reservations.csv", "rt");
		fscanf(file,"%d", &nb);
		file = fopen("reservations_1.csv", "wt");
		fprintf(file,"%d;num_reservation;date_debut;date_fin;num_permis;immatriculation\n", nb);

		for(int i=0;i<nb;i++){
			printf("%d;%d/%d/%d;%d/%d/%d;%s;%s\n",tete->data.reservation.num_reserv,tete->data.reservation.date_debut[0],tete->data.reservation.date_debut[1],tete->data.reservation.date_debut[2],tete->data.reservation.date_fin[0],tete->data.reservation.date_fin[1],tete->data.reservation.date_fin[2],ajouteZero(tete->data.reservation.num_permis),tete->data.reservation.immat);
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
