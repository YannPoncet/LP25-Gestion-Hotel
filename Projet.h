#ifndef __H_PROJET__
#define __H_PROJET__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//STRUCTURES
typedef struct Chambre
{
	int ch_Numero;
	int ch_Taille;
	int ch_ID_Client;
} Chambre;

typedef struct Client
{
	int clt_Index;
	char clt_Nom[50];
	int clt_NbChambres;
	int clt_AUneChambre;
} Client;

typedef struct ChambreElement
{
	Chambre* chambre;
	struct ChambreElement* nextChambre;
	struct ChambreElement* prevChambre;
} ChambreElement;

typedef struct ClientElement
{
	Client* client;
	struct ClientElement* nextClient;
	struct ClientElement* prevClient;
} ClientElement;

typedef struct Hotel
{
	ChambreElement* firstChambre;
	ChambreElement* lastChambre;
	int nbChambres;
	ClientElement* firstClient;
	ClientElement* lastClient;
	int nbClients;
}Hotel;

//FONCTIONS

Hotel createHotel();

void louerChambre(Hotel* hotel);

void rendreChambre(Hotel* hotel);

void printChambreLouee(Hotel* hotel);

void printClientPresent(Hotel* hotel);

void printChambre(Hotel* hotel);

void printClient(Hotel* hotel);

Chambre* createChambre();

Client* createClient();

void ajoutChambre(Hotel* hotel);

void ajoutClient(Hotel* hotel);

void insertChambre(Chambre* chambre, Hotel* hotel);

void insertClient(Client* client, Hotel* hotel);

void modifChambre(Hotel* hotel);

void modifClient(Hotel* hotel);

void removeChambre(int numero, Hotel* hotel);

void removeClient(int index, Hotel* hotel);

void modifClientNbChambre(int ID, Hotel* hotel, int mode);

void resetChambreClientID(int index, Hotel* hotel);

/*
* Cette fonction sert à sauvegarder le contenu de nos listes de clients et de chambres dans des fichiers textes,
* elle sera utilisée lorsque l'on quittera le programme et que l'utilisateur voudra sauvegarder les modifs
* @hotel: hotel qui devra être sauvegardé
* @return: retourne si la sauvegarde a bien été effectuée
*/
int sauvegarder(Hotel* hotel);

/*
* Cette fonction sert à récupérer le contenu de nos fichiers et à en faire des listes
* @hotel: hotel qui devra être sauvegardé
* @return: retourne si la sauvegarde a bien été effectuée
*/
void recuperer(Hotel* hotel);

void supprHotel(Hotel* hotel);

int isChambreEmpty(Hotel* hotel);

int isClientEmpty(Hotel* hotel);

int isEmpty(Hotel* hotel);

int testSiFichierVide(FILE* fichier);

void vider_buffer();

#endif
