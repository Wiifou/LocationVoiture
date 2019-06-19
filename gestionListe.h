void afficheListe(liste* tete);
void menu(liste **Lvoiture,liste **Lreservation,liste **client );
void ajouteVoiture(liste ** Lvoiture);
void ajouteReservationScan(liste ** Lres, liste * voiture, liste* Lclient,int taille);
void SetListeResActuVoiture(liste * voiture,liste *reservation);

void InitialiseChaineParVoiture(vehicules* v,reservations * reservation);
void afficheHisto(liste * voiture);
void ChoixVehicule(liste * voiture,int date_debut[3],int date_fin[3]);
int superDate(int date1[3],int date2[3]);
int superInt(int x,int y);
int seChevauche(int date_debut1[3],int date_fin1[3],int date_debut2[3],int date_fin2[3]);
int TestHistoDate(int date_debut[3],int date_fin[3], vehicules v);

void ParcourVoitureLibre(liste * voiture, int date_debut[3],int date_fin[3], char categorie);
char lireCaractere();
void scanfDate(int date[3]);
