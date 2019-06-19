
#ifndef VEHICULES_H
#define VEHICULES_H



typedef struct vehicules{
	char immat[10];
	char marque[15];
	char modele[15];
	short int millesime;
	int kilometrage;
	char categorie;
	struct liste * teteResActu;
}vehicules;

#endif
