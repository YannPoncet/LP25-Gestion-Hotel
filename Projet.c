
#include <Projet.h>


int main(int argc, char* argv[])
{
	printf("\n===== GESTION D'HOTEL =====\n");
	int rep1=0;
	int rep2=0;
	Hotel hotel = createHotel();
	recuperer(&hotel);
	printf("===== Bonjour =====\n");
	printf("Dans tous ce programme, si vous ne savez pas répondre à une question, tapez 0\n");
	do
	{
		printf("\n\nQue voulez vous faire ?");
		printf("\nGerer les chambres................1");
		printf("\nGerer les clients.................2");
		printf("\nGerer les locations...............3");
		printf("\nSupprimer les données actuelles...4");
		printf("\nSauvegarder.......................5");
		printf("\nSauvegarder et Quitter............6");
		printf("\nQuitter...........................7\n");

		scanf("%i",&rep1);
		switch(rep1)
		{
			case 1:
		       		printf("\nAjouter une chambre...............1");
				printf("\nModifier une chambre..............2");
				printf("\nSupprimer une chambre.............3");
	      			printf("\nAfficher la liste des chambres....4");
				printf("\nRetour............................5\n");

				scanf("%i",&rep2);
				switch(rep2)
				{
					case 1:
					{
						ajoutChambre(&hotel);
						break;
					}
					case 2:
					{
						modifChambre(&hotel);
						break;
					}
					case 3:
					{ //Crochets nécessaires si on veut créer de nouvelles variables dans les cases
						int numero=0;
						int test=0;
						printf("Quel est le numero de la chambre à supprimer ?\n");
						vider_buffer();
						test=scanf("%i",&numero);
						while(test!=1)
						{
							printf("\nDonnee entree non valide");
							printf("Quel est le numero de la chambre à supprimer ?\n");
							vider_buffer();
							test=scanf("%i",&numero);

						}
						removeChambre(numero,&hotel);	
						break;
					}
					case 4:
						printChambre(&hotel);
						break;
					default:
						break;
				}
		        	break;
			case 2:
		       		printf("\nAjouter un client.................1");
				printf("\nModifier un client................2");
				printf("\nSupprimer un client...............3");
				printf("\nAfficher la liste des clients.....4");
				printf("\nRetour............................5\n");

				scanf("%i",&rep2);
				switch(rep2)
				{
					case 1:
					{
						ajoutClient(&hotel);
						break;
					}
					case 2:
					{
						modifClient(&hotel);
						break;
					}
					case 3:
					{
						int index=0;
						int test=0;
						printf("Quel est l'index du client à supprimer ?\n");
						vider_buffer();
						test=scanf("%i",&index);
						while(test!=1)
						{
							printf("\nDonnee entree non valide");
							printf("Quel est l'index du client à supprimer ?\n");
							vider_buffer();
							test=scanf("%i",&index);

						}
						removeClient(index,&hotel);
						break;
					}
					case 4:
						printClient(&hotel);
						break;
					default:
						break;
				}
		        	break;
			case 3:
                		printf("\nLouer une chambre.................1");
				printf("\nRendre une chambre................2");
				printf("\nAfficher les chambres louées......3");
				printf("\nAfficher les clients dans l'hotel.4");
				printf("\nRetour............................5\n");

				scanf("%i",&rep2);
				switch(rep2)
				{
					case 1:
					    	louerChambre(&hotel);
						break;
					case 2:
                        			rendreChambre(&hotel);
						break;
					case 3:
					    	printChambreLouee(&hotel);
						break;
					case 4:
					    	printClientPresent(&hotel);
						break;
					default:
						break;
				}
		        	break;
			case 4:
				supprHotel(&hotel);
				break;
			case 5:
				sauvegarder(&hotel);
				break;
			case 6:
				sauvegarder(&hotel);
		        	printf("Au revoir\n");
		        	break;
			case 7:
				printf("Au revoir\n");
				break;
			default:
		        	printf("\nVeuillez choisir un nombre entre 1 et 7.");
		        	break;
		}
    	}while(rep1!=6 && rep1!=7);
	return 0;
}

Hotel createHotel() //Initialise l'hotel
{
	Hotel hotel;
	hotel.nbChambres=0;
	hotel.nbClients=0;
	hotel.firstChambre=NULL;
	hotel.lastChambre=NULL;
	hotel.firstClient=NULL;
	hotel.lastClient=NULL;
	return hotel;
}
void louerChambre (Hotel* hotel)//Permet de louer une chambre
{
	int numChambre=0;
	ChambreElement* Chbre;
	ClientElement* tmp;
	if (isChambreEmpty(hotel))
	{
		printf("L'hotel est vide.");
	}
	else
	{
		printf("\nQuel est le numero de la chambre a louer ? ");
		scanf("%i",&numChambre);
		while(numChambre<hotel->firstChambre->chambre->ch_Numero|| numChambre>hotel->lastChambre->chambre->ch_Numero)
		{
			printf("\nErreur, le numéro entré est trop petit ou trop grand");
			printf("\nQuel est le numero de la chambre a louer ? ");
			scanf("%i",&numChambre);	//Récupère le numéro de la chambre
		}
		Chbre = hotel->firstChambre;
		while(Chbre->chambre->ch_Numero != numChambre)	//Cherche la chambre en question
		{
			Chbre = Chbre->nextChambre;
		}
		if(Chbre->chambre->ch_ID_Client != 0)	//Vérifie si elle est louée ou pas
		{
			printf("\nLa chambre est deja louee");
		}
		else
		{
			printf("\nQuel est l'ID du client souhaitant louer la chambre ? ");
			scanf("%i",&Chbre->chambre->ch_ID_Client);
			tmp = hotel->firstClient;
			while(tmp!=NULL && tmp->client->clt_Index != Chbre->chambre->ch_ID_Client)
			{
				tmp = tmp->nextClient;
			}
			if(tmp!=NULL)
			{
				tmp->client->clt_NbChambres++;
				tmp->client->clt_AUneChambre=1; 
			}
			else
			{
				printf("\nL'ID entre ne correspond a aucun client, fin de l'operation\n");
				Chbre->chambre->ch_ID_Client=0;
			}
			
		}
	}
}

void rendreChambre(Hotel* hotel)// permet de rendre une chambre louée
{
	int numChambre=0;
	ChambreElement* ChbreElem;
	ClientElement* ClientElem;
	if (isChambreEmpty(hotel))
	{
		printf("L'hotel est vide.");
	}
	else
	{
		printf("\nQuel est le numero de la chambre a rendre ? ");
		scanf("%i",&numChambre);
		while(numChambre<hotel->firstChambre->chambre->ch_Numero|| numChambre>hotel->lastChambre->chambre->ch_Numero)
		{
			printf("\nErreur, le numéro entré est trop petit ou trop grand");
			printf("\nQuel est le numero de la chambre a rendre ? ");
			scanf("%i",&numChambre);	//Récupère le numéro de la chambre
		}

		ChbreElem = hotel->firstChambre;
		while(ChbreElem->chambre->ch_Numero != numChambre)//cherche la chambre a rendre
		{
			ChbreElem = ChbreElem->nextChambre;
		}

		if(ChbreElem->chambre->ch_ID_Client==0)
		{
			printf("\nCette chambre n'est pas louee");
		}
		else
		{
			ClientElem = hotel->firstClient;
			while(ClientElem->client->clt_Index != ChbreElem->chambre->ch_ID_Client)// cherche le client qui possede la chambre
			{
				ClientElem = ClientElem->nextClient;
			}
		
			ChbreElem->chambre->ch_ID_Client = 0;//actualise l'ID du client de la chambre
			if(ClientElem->client->clt_NbChambres>0)
			{
				ClientElem->client->clt_NbChambres--;//actualise le nombre de chambre que possède le client
			}
			if(ClientElem->client->clt_NbChambres==0)
			{
				ClientElem->client->clt_AUneChambre=0; //Si le client n'a plus de chambres, on met le booléen à 0
			}
		}
		
	}
}

void printChambreLouee(Hotel* hotel)//permet d'afficher toutes les chambres louées
{
	if(isChambreEmpty(hotel))
	{
		printf("\nL'hotel ne possede pas de chambres\n");
	}
	else
	{
		int trouveChambre=0;
		ChambreElement* tmp = hotel->firstChambre;//Se positionne sur la première chambre de l'hotel
		while(tmp!=NULL) //traverse toutes les chambres pour les afficher
		{
			if(tmp->chambre->ch_ID_Client!=0)	//Si la chambre est occupée, on l'affiche
			{
				trouveChambre=1;
				printf("\n");
				printf("Numero de la chambre : %i, taille : %i, ID du client : %i",tmp->chambre->ch_Numero, tmp->chambre->ch_Taille, tmp->chambre->ch_ID_Client);
			}
			tmp=tmp->nextChambre;
		}
		if(trouveChambre==0)
		{
			printf("\nAucune chambre n'est louee");
		}
	}
}

void printClientPresent(Hotel* hotel)
{
	if(isClientEmpty(hotel))
	{
		printf("\nL'hotel ne possede pas de clients\n");
	}
	else
	{
		int trouveClient=0;
		ClientElement* tmp = hotel->firstClient;
		while(tmp!=NULL)  //Traverse les clients pour les afficher
		{
			if(tmp->client->clt_AUneChambre==1) //Si le client a une chambre, on l'affiche
			{
				trouveClient=1;
				printf("\n");
				printf("ID du client : %i, nom : %s, ",tmp->client->clt_Index, tmp->client->clt_Nom);
				printf("nombre de chambres : %i",tmp->client->clt_NbChambres);
			}
			tmp=tmp->nextClient;
		}
		if(trouveClient==0)
		{
			printf("\nAucun client n'est dans l'hotel");
		}
	}
}

void printChambre(Hotel* hotel)	//Affiche la liste de toutes les chambres
{
	if(isChambreEmpty(hotel))
	{
		printf("\nL'hotel ne possede pas de chambres\n");
	}
	else
	{
		printf("\nL'hotel possède actuellement %i chambres\n",hotel->nbChambres);
		ChambreElement* tmp = hotel->firstChambre;
		while(tmp!=NULL) //Traverse toutes les chambres pour les afficher
		{
			printf("\n");
			printf("Numero de la chambre : %i, taille : %i, ",tmp->chambre->ch_Numero, tmp->chambre->ch_Taille);
			if(tmp->chambre->ch_ID_Client==0)
			{
				printf("libre\n");
			}
			else
			{
				printf("ID du client : %i\n",tmp->chambre->ch_ID_Client);
			}
			tmp=tmp->nextChambre;
		}
	}
}

void printClient(Hotel* hotel)	//Affiche la liste de tous les clients
{
	if(isClientEmpty(hotel))
	{
		printf("\nL'hotel ne possede pas de clients\n");
	}
	else
	{
		printf("\nL'hotel a actuellement %i clients\n",hotel->nbClients);
		ClientElement* tmp = hotel->firstClient;
		while(tmp!=NULL)  //Traverse tous les clients pour les afficher
		{
			printf("\n");
			printf("ID du client : %i, nom : %s, ",tmp->client->clt_Index, tmp->client->clt_Nom);
			if(tmp->client->clt_NbChambres==0)
			{
				printf("aucune chambre");
			}
			else
			{
				printf("nombre de chambres : %i",tmp->client->clt_NbChambres);
			}
			tmp=tmp->nextClient;
		}
	}
}

Chambre* createChambre() //Utilisé pour créer une chambre (/!\ pas un ChambreElement)
{
	Chambre* chambre = (Chambre*)malloc(sizeof(Chambre));
	chambre->ch_ID_Client=0;
	printf("Quel est le numero de chambre : ");
	scanf("%i",&chambre->ch_Numero);
	printf("Quelle est la taille de la chambre : ");
	scanf("%i",&chambre->ch_Taille);
	return chambre;
}

Client* createClient() //Utilisé pour créer un client (/!\ pas un ClientElement)
{
	Client* client = (Client*)malloc(sizeof(Client));
	client->clt_Index=0;
	client->clt_NbChambres=0;
	client->clt_AUneChambre=0;
	printf("Quel est le nom du client : ");
	scanf("%s",client->clt_Nom);
	return client;
}

void ajoutChambre(Hotel* hotel)
{
	Chambre* chambre = createChambre();
	insertChambre(chambre,hotel);
}

void ajoutClient(Hotel* hotel)
{
	Client* client = createClient();
	insertClient(client,hotel);
}

void insertChambre(Chambre* chambre, Hotel* hotel) //Permet d'ajouter une chambre en fonction de son numéro
{
	ChambreElement* newChambre = (ChambreElement*)malloc(sizeof(ChambreElement));
	newChambre->chambre = chambre;

	if(!isChambreEmpty(hotel))
	{
		ChambreElement* tmp = hotel->firstChambre;
		//On cherche la première chambre ayant un numéro supérieur à celui de la chambre à ajouter
		while(tmp!=NULL && tmp->chambre->ch_Numero < newChambre->chambre->ch_Numero)
		{
			tmp=tmp->nextChambre;
		}

		if(tmp==NULL) //Si c'est le plus grand numéro, on ajoute la chambre à la fin
		{
			newChambre->nextChambre=NULL;
			newChambre->prevChambre = hotel->lastChambre;
			hotel->lastChambre->nextChambre = newChambre;
			hotel->lastChambre = newChambre;
		}
		else if(tmp->chambre->ch_Numero == newChambre->chambre->ch_Numero) //Si le numéro existe déjà, on affiche une erreur
		{
			printf("\nCe numero de chambre est deja attribue\n");
		}
		else if(tmp==hotel->firstChambre) //Si le numéro est le plus petit de l'hotel, on ajoute la chambre au début
		{
			newChambre->prevChambre=NULL;
			hotel->firstChambre->prevChambre = newChambre;
			newChambre->nextChambre = hotel->firstChambre;
			hotel->firstChambre = newChambre;
		}
		else	//Dans les autres cas on ajoute la chambre au bon endroit (en fonction des numéros)
		{
			newChambre->nextChambre = tmp;
			newChambre->prevChambre = tmp->prevChambre;
			tmp->prevChambre->nextChambre = newChambre;
			tmp->prevChambre = newChambre;

		}
	}
	else	//Si l'hotel est vide on ajoute simplement la chambre
	{
		newChambre->nextChambre = NULL;
		hotel->lastChambre = newChambre;
		newChambre->prevChambre = NULL;
		hotel->firstChambre = newChambre;
	}
	hotel->nbChambres ++;
}

void insertClient(Client* client, Hotel* hotel)	//Permet d'ajouter un client en fonction de son nom
{	
	ClientElement* newClient = (ClientElement*)malloc(sizeof(ClientElement));
	newClient->client = client;

	if(!isClientEmpty(hotel))
	{
		ClientElement* tmp = hotel->firstClient;
		//On cherche le premier client ayant un nom "supérieur" (ordre alphabétique) à celui du client à ajouter
		while(tmp!=NULL && strcmp(tmp->client->clt_Nom,newClient->client->clt_Nom)<0)
		{
			tmp=tmp->nextClient;
		}

		if(tmp==NULL)	//Si c'est le plus grand nom, on ajoute le client à la fin
		{
			newClient->nextClient=NULL;
			newClient->prevClient = hotel->lastClient;
			hotel->lastClient->nextClient = newClient;
			hotel->lastClient = newClient;
		}
		else if(strcmp(tmp->client->clt_Nom,newClient->client->clt_Nom)==0)	//Si le nom existe déjà, on affiche une erreur
		{
			printf("\nCe client est deja dans l'hotel\n");
		}
		else if(tmp==hotel->firstClient)	//Si le nom est le plus petit de l'hotel, on ajoute le client au début
		{
			newClient->prevClient=NULL;
			hotel->firstClient->prevClient = newClient;
			newClient->nextClient = hotel->firstClient;
			hotel->firstClient = newClient;
		}
		else	//Dans les autres cas on ajoute le client au bon endroit (en fonction des noms)
		{
			newClient->nextClient = tmp;
			newClient->prevClient = tmp->prevClient;
			tmp->prevClient->nextClient = newClient;
			tmp->prevClient = newClient;
		}
		
		if(newClient->client->clt_Index==0)
		{
			tmp = hotel->firstClient;
			while(tmp!=NULL)
			{
				if(newClient->client->clt_Index<tmp->client->clt_Index)
				{
					newClient->client->clt_Index = tmp->client->clt_Index;
				}
				tmp=tmp->nextClient;
			}
			newClient->client->clt_Index++;
		}
		

	}
	else	//Si l'hotel est vide on ajoute simplement le client
	{
		newClient->nextClient = NULL;
		hotel->lastClient = newClient;
		newClient->prevClient = NULL;
		hotel->firstClient = newClient;
		newClient->client->clt_Index=1;
	}

	

	hotel->nbClients ++;
}

void modifChambre(Hotel* hotel)
{
	int numero=0;
	char rep='y';
	printf("\nQuel est le numero de la chambre a modifier ? ");
	scanf("%i",&numero);
	ChambreElement* modChambre = hotel->firstChambre;
	while(modChambre!=NULL && modChambre->chambre->ch_Numero!=numero)	//On cherche la chambre ayant le bon numéro
	{
		modChambre=modChambre->nextChambre;
	}
	if(modChambre!=NULL)
	{
		printf("\nVoulez vous modifier le numero de la chambre ? (y/n) ");
		vider_buffer();
		scanf("%c",&rep);
		if(rep=='y' || rep=='Y')
		{
			printf("\n Quelle est le nouveau numero de la chambre ? ");
			scanf("%i",&modChambre->chambre->ch_Numero);

			// Il faut replacer la chambre à modifier donc d'abord l'isoler puis la replacer
			if(modChambre->prevChambre==NULL) //Si la chambre à modifier est en tete de liste
			{
				hotel->firstChambre=modChambre->nextChambre;
				modChambre->nextChambre->prevChambre=NULL;
			}
			else if(modChambre->nextChambre==NULL) //Si la chambre à modifier est en queue de liste
			{
				hotel->lastChambre=modChambre->prevChambre;
				modChambre->prevChambre->nextChambre=NULL;
			}
			else //Si on est ni en tete ni en queue de liste
			{
				modChambre->prevChambre->nextChambre=modChambre->nextChambre;
				modChambre->nextChambre->prevChambre=modChambre->prevChambre;
			}

			ChambreElement* tmp = hotel->firstChambre;
			//On cherche la première chambre ayant un numéro inférieur à celui de la chambre à ajouter
			while(tmp!=NULL && tmp->chambre->ch_Numero < modChambre->chambre->ch_Numero)
			{
				tmp=tmp->nextChambre;
			}

			if(tmp==NULL) //Si c'est le plus grand numéro, on ajoute la chambre à la fin
			{
				modChambre->nextChambre=NULL;
				modChambre->prevChambre = hotel->lastChambre;
				hotel->lastChambre->nextChambre = modChambre;
				hotel->lastChambre = modChambre;
			}
			else if(tmp->chambre->ch_Numero == modChambre->chambre->ch_Numero) //Si le numéro existe déjà, on affiche une erreur
			{
				printf("\nCe numero de chambre est deja attribue\n");
			}
			else if(tmp==hotel->firstChambre) //Si le numéro est le plus petit de l'hotel, on ajoute la chambre au début
			{
				modChambre->prevChambre=NULL;
				hotel->firstChambre->prevChambre = modChambre;
				modChambre->nextChambre = hotel->firstChambre;
				hotel->firstChambre = modChambre;
			}
			else	//Dans les autres cas on ajoute la chambre au bon endroit (en fonction des numéros)
			{
				modChambre->nextChambre = tmp;
				modChambre->prevChambre = tmp->prevChambre;
				tmp->prevChambre->nextChambre = modChambre;
				tmp->prevChambre = modChambre;
			}
		}

		printf("\nVoulez vous modifier la taille de la chambre ? (y/n) ");
		vider_buffer();
		scanf("%c",&rep);
		if(rep=='y' || rep=='Y')
		{
			printf("\n Quelle est la nouvelle taille de la chambre ? ");
			scanf("%i",&modChambre->chambre->ch_Taille);
		}
	}
	else
	{
		printf("\nCette chambre n'existe pas\n");
	}
}

void modifClient(Hotel* hotel)
{
	int index=0;
	char rep='n';
	printf("\nQuel est l'index du client a modifier ? ");
	scanf("%i",&index);
	ClientElement* modClient = hotel->firstClient;
	while(modClient!=NULL && modClient->client->clt_Index!=index)	//On cherche le client ayant le bon numéro
	{
		modClient=modClient->nextClient;
	}

	if(modClient!=NULL)
	{
		printf("\nVoulez vous modifier l'index du client ? (y/n) ");
		vider_buffer();
		scanf("%c",&rep);
		if(rep=='y' || rep=='Y')
		{
			printf("\n Quelle est le nouvel index du client ? ");
			scanf("%i",&modClient->client->clt_Index);

			// Il faut replacer le client à modifier donc d'abord l'isoler puis la replacer
			if(modClient->prevClient==NULL) //Si le client à modifier est en tete de liste
			{
				hotel->firstClient=modClient->nextClient;
				modClient->nextClient->prevClient=NULL;
			}
			else if(modClient->nextClient==NULL) //Si le client à modifier est en queue de liste
			{
				hotel->lastClient=modClient->prevClient;
				modClient->prevClient->nextClient=NULL;
			}
			else //Si on est ni en tete ni en queue de liste
			{
				modClient->prevClient->nextClient=modClient->nextClient;
				modClient->nextClient->prevClient=modClient->prevClient;
			}

			ClientElement* tmp = hotel->firstClient;
			//On cherche le premier client ayant un nom "supérieur" (ordre alphabétique) à celui du client à ajouter
			while(tmp!=NULL && strcmp(tmp->client->clt_Nom,modClient->client->clt_Nom)<0)
			{
				tmp=tmp->nextClient;
			}

			if(tmp==NULL)	//Si c'est le plus grand nom, on ajoute le client à la fin
			{
				modClient->nextClient=NULL;
				modClient->prevClient = hotel->lastClient;
				hotel->lastClient->nextClient = modClient;
				hotel->lastClient = modClient;
			}
			else if(strcmp(tmp->client->clt_Nom,modClient->client->clt_Nom)==0)	//Si le nom existe déjà, on affiche une erreur
			{
				printf("\nCe client est deja dans l'hotel\n");
			}
			else if(tmp==hotel->firstClient)	//Si le nom est le plus petit de l'hotel, on ajoute le client au début
			{
				modClient->prevClient=NULL;
				hotel->firstClient->prevClient = modClient;
				modClient->nextClient = hotel->firstClient;
				hotel->firstClient = modClient;
			}
			else	//Dans les autres cas on ajoute le client au bon endroit (en fonction des noms)
			{
				modClient->nextClient = tmp;
				modClient->prevClient = tmp->prevClient;
				tmp->prevClient->nextClient = modClient;
				tmp->prevClient = modClient;
			}
		}

		printf("\nVoulez vous modifier le nom du client ? (y/n) ");
		vider_buffer();
		scanf("%c",&rep);
		if(rep=='y' || rep=='Y')
		{
			printf("\n Quelle est le nouveau nom du client ? ");
			scanf("%s",modClient->client->clt_Nom);
		}

	}
	else
	{
		printf("\nCe client n'existe pas\n");
	}
}

void removeChambre(int numero, Hotel* hotel)	//Permet de supprimer une chambre de la liste en fonction de son numéro
{
	if(!isChambreEmpty(hotel))
	{
		ChambreElement* tmp = hotel->firstChambre;
		while(tmp!=NULL && tmp->chambre->ch_Numero!=numero)	//On cherche la chambre ayant le bon numéro
		{
			tmp=tmp->nextChambre;
		}

		if(tmp!=NULL && tmp->chambre->ch_Numero==numero)	//Si on a trouvé une chambre, on l'isole puis on la free
		{
			if(tmp->chambre->ch_ID_Client!=0) //Si la chambre a un client, on réduit le nombre de chambres que possède le client
			{
				modifClientNbChambre(tmp->chambre->ch_ID_Client, hotel, -1);

				ClientElement* cltmp = hotel->firstClient;	//On cherche le client correspondant à l'ID
				while(cltmp!=NULL && cltmp->client->clt_Index!=tmp->chambre->ch_ID_Client) 
				{
					cltmp = cltmp->nextClient;
				}
				ChambreElement* chtmp = hotel->firstChambre;	//On cherche une autre chambre correspondant à cet ID
				while(chtmp!=NULL && chtmp->chambre->ch_ID_Client!=tmp->chambre->ch_ID_Client)
				{
					chtmp = chtmp->nextChambre;
				}			
				//Si on a trouvé un client sans trouver d'autre chambre, le client n'a plus de chambre
				if(cltmp!=NULL && chtmp==NULL) 
				{
					cltmp->client->clt_AUneChambre=0;
				}
			}

			if(tmp->prevChambre==NULL) //Si la chambre trouvée est la tete de la liste
			{
				hotel->firstChambre=tmp->nextChambre;
				tmp->nextChambre->prevChambre=NULL;
				free(tmp->chambre);
				tmp->chambre=NULL;
				free(tmp);
				tmp=NULL;
			}
			else if(tmp->nextChambre==NULL) //Si la chambre trouvée est la queue de la liste
			{
				hotel->lastChambre=tmp->prevChambre;
				tmp->prevChambre->nextChambre=NULL;
				free(tmp->chambre);
				tmp->chambre=NULL;
				free(tmp);
				tmp=NULL;
			}
			else	//Si on est ni en tete ni en queue de la liste
			{
				tmp->prevChambre->nextChambre=tmp->nextChambre;
				tmp->nextChambre->prevChambre=tmp->prevChambre;
				free(tmp->chambre);
				tmp->chambre=NULL;
				free(tmp);
				tmp=NULL;
			}
			hotel->nbChambres --;
		}
		else
		{
			printf("\nAucune chambre n'a ce numero");
		}
	}
	
}

void removeClient(int index, Hotel* hotel)	//Permet de supprimer un client de la liste en fonction de son index
{
	if(!isClientEmpty(hotel))
	{
		ClientElement* tmp = hotel->firstClient;
		while(tmp!=NULL && tmp->client->clt_Index!=index)	//On cherche le client ayant le bon index
		{
			tmp=tmp->nextClient;
		}

		if(tmp!=NULL && tmp->client->clt_Index==index)	//Si on a trouvé un client, on l'isole puis on le free
		{
			if(tmp->client->clt_NbChambres!=0)
			{
				resetChambreClientID(index, hotel);
			}

			if(tmp->prevClient==NULL) //Si le client trouvé est la tete de la liste
			{
				hotel->firstClient=tmp->nextClient;
				tmp->nextClient->prevClient=NULL;
				free(tmp->client);
				tmp->client=NULL;
				free(tmp);
				tmp=NULL;
			}
			else if(tmp->nextClient==NULL) //Si le client trouvé est la queue de la liste
			{
				hotel->lastClient=tmp->prevClient;
				tmp->prevClient->nextClient=NULL;
				free(tmp->client);
				tmp->client=NULL;
				free(tmp);
				tmp=NULL;
			}
			else	//Si on est ni en tete ni en queue de la liste
			{
				tmp->prevClient->nextClient=tmp->nextClient;
				tmp->nextClient->prevClient=tmp->prevClient;
				free(tmp->client);
				tmp->client=NULL;
				free(tmp);
				tmp=NULL;
			}
			hotel->nbClients --;
		}
		else
		{
			printf("\nCe client n'est pas dans l'hotel\n");
		}
	}
	else
	{
		printf("\nIl n'y a pas de clients dans l'hotel\n");
	}	
}

void modifClientNbChambre(int index, Hotel* hotel, int mode)
{
	ClientElement* tmp = hotel->firstClient;
	while(tmp!=NULL && tmp->client->clt_Index!=index)
	{
		tmp=tmp->nextClient;
	}
	if(tmp!=NULL && (mode==1 || mode==-1))
	{
		tmp->client->clt_NbChambres+=mode;
	}
	else
	{
		printf("\nIl y a eu une erreur lors de la modification du nombre de chambres du client\n");
	}
}

void resetChambreClientID(int index, Hotel* hotel)
{
	ChambreElement* tmp = hotel->firstChambre;
	while(tmp!=NULL && index!=tmp->chambre->ch_ID_Client)
	{
		tmp=tmp->nextChambre;
	}

	if(tmp!=NULL)
	{
		tmp->chambre->ch_ID_Client=0;
	}
}

int sauvegarder(Hotel* hotel)
{
	int succes = 0;
	FILE* fichier = NULL;

	//Sauvegarde des chambre dans le fichier chambres.txt
	fichier = fopen("sauvegarde/chambres.txt", "w");
	if(fichier != NULL)
	{
		if(!isChambreEmpty(hotel))
		{
			ChambreElement* tmp = hotel->firstChambre;
			while(tmp!=NULL) //Traverse toutes les chambres pour les afficher
			{
		    		fprintf(fichier,"%i %i %i\n",tmp->chambre->ch_Numero, tmp->chambre->ch_Taille, tmp->chambre->ch_ID_Client);
				tmp=tmp->nextChambre;
			}
		}
		succes = 1;
		fclose(fichier);
	}


	//Sauvegarde des clients dans le fichier clients.txt
	fichier = fopen("sauvegarde/clients.txt", "w");
	if(fichier != NULL)
	{
		if(!isClientEmpty(hotel))
		{
			ClientElement* tmp = hotel->firstClient;
			while(tmp!=NULL) //Traverse tous les clients pour les afficher
			{
				fprintf(fichier,"%i %s %i\n",tmp->client->clt_Index, tmp->client->clt_Nom, tmp->client->clt_NbChambres);
				tmp=tmp->nextClient;
			}
		}
		fclose(fichier);
	}
	else
	{
		succes=0;
	}

	return succes;
}

void recuperer(Hotel* hotel)
{
	FILE* fichier = NULL;

	//Récupération des chambres
	fichier = fopen("sauvegarde/chambres.txt", "r");
	if(fichier!=NULL && !testSiFichierVide(fichier))
	{
		rewind(fichier); //Remet le curseur au début du fichier
		while(!feof(fichier))
		{
			Chambre* chambre = (Chambre*)malloc(sizeof(Chambre));
			fscanf(fichier,"%i %i %i\n",&chambre->ch_Numero, &chambre->ch_Taille, &chambre->ch_ID_Client);
			insertChambre(chambre,hotel);
		}
		fclose(fichier);
	}


	//Récupération des clients
	fichier = fopen("sauvegarde/clients.txt", "r");
	if(fichier!=NULL && !testSiFichierVide(fichier))
	{
		rewind(fichier); //Remet le curseur au début du fichier
		while(!feof(fichier))
		{
			Client* client = (Client*)malloc(sizeof(Client));
			fscanf(fichier,"%i %s %i\n",&client->clt_Index, client->clt_Nom, &client->clt_NbChambres);
			insertClient(client,hotel);
		}
		fclose(fichier);
	}
}

void supprHotel(Hotel* hotel)
{
	FILE* fichier = NULL;

	//Suppression des chambres et des clients
	fichier = fopen("sauvegarde/chambres.txt", "w");
	fclose(fichier);

	fichier = fopen("sauvegarde/clients.txt", "w");
	fclose(fichier);

	ChambreElement* chtmp = NULL;
	ClientElement* cltmp = NULL;
	if(!isChambreEmpty(hotel))
	{
		chtmp = hotel->firstChambre->nextChambre;
	}
	if(!isClientEmpty(hotel))
	{
		cltmp = hotel->firstClient->nextClient;
	}

	
	
	while(cltmp!=NULL || chtmp!=NULL)
	{
		if(chtmp!=NULL)
		{
			free(chtmp->prevChambre->chambre);
			chtmp->prevChambre->chambre=NULL;
			free(chtmp->prevChambre);
			chtmp->prevChambre=NULL;
			chtmp=chtmp->nextChambre;
		}

		if(cltmp!=NULL)
		{
			free(cltmp->prevClient->client);
			cltmp->prevClient->client=NULL;
			free(cltmp->prevClient);
			cltmp->prevClient=NULL;
			cltmp=cltmp->nextClient;
		}
	}
	
	if(hotel->lastChambre!=NULL)
	{
		free(hotel->lastChambre->chambre);
		hotel->lastChambre->chambre=NULL;
		free(hotel->lastChambre);
		hotel->lastChambre=NULL;
	}

	if(hotel->lastClient!=NULL)
	{
		free(hotel->lastClient->client);
		hotel->lastClient->client=NULL;
		free(hotel->lastClient);
		hotel->lastClient=NULL;
	}


	hotel->firstChambre=NULL;
	hotel->lastChambre=NULL;

	hotel->firstClient=NULL;
	hotel->lastClient=NULL;

	hotel->nbChambres=0;
	hotel->nbClients=0;
}

int isChambreEmpty(Hotel* hotel)
{
	return hotel->firstChambre == NULL;
}

int isClientEmpty(Hotel* hotel)
{
	return hotel->firstClient == NULL;
}

int isEmpty(Hotel* hotel)
{
	return (hotel->firstChambre == NULL && hotel->firstClient == NULL);
}

int testSiFichierVide(FILE* fichier)
{
	int caracterePremier = 0;

	//On lit le prmeier caractère du fichier
	caracterePremier = fgetc(fichier);
	if(caracterePremier==EOF)
	{
		return 1; //le fichier est vide donc on retourne 1
	}
	return 0; //le fichier n'est pas vide donc on retourne 0
}

void vider_buffer()
{
	int c;

	do 
	{
		c = getchar();
	} while (c != '\n' && c != EOF);
}
