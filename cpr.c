/*------------------------------------------------------------
Fichier: cpr.c

Nom et Numéro étudiant: Océane Prud'Homme (300272920) et Lili Rose Théoret (300342096)


Description: Ce programme contient le code pour la creation
             d'un processus enfant et y attacher un tuyau.
	     L'enfant envoyera des messages par le tuyau
	     qui seront ensuite envoyes a la sortie standard.

Explication du processus zombie
(point 5 de "A completer" dans le devoir):

	(s.v.p. completez cette partie);
	Un processus zombie est un processus enfant terminé dont le parent n’a pas encore récupéré le statut avec wait(). 
	Il ne consomme pas de ressources, mais garde une entrée dans la table des processus. 
	S’il y en a trop, ils peuvent empêcher la création de nouveaux processus
	Lorsque le parent appelle wait(), le processus se termine normalement.
	Site reference: https://www.geeksforgeeks.org/operating-systems/zombie-processes-prevention/


-------------------------------------------------------------*/
#include <stdio.h>
#include <sys/select.h>

/* Prototype */
void creerEnfantEtLire(int );

/*-------------------------------------------------------------
Function: main
Arguments: 
	int ac	- nombre d'arguments de la commande
	char **av - tableau de pointeurs aux arguments de commande
Description:
	Extrait le nombre de processus a creer de la ligne de
	commande. Si une erreur a lieu, le processus termine.
	Appel creerEnfantEtLire pour creer un enfant, et lire
	les donnees de l'enfant.
-------------------------------------------------------------*/

int main(int ac, char **av)
{
    int numeroProcessus; 

    if(ac == 2)
    {
       if(sscanf(av[1],"%d",&numeroProcessus) == 1)
       {
           creerEnfantEtLire(numeroProcessus);
       }
       else fprintf(stderr,"Ne peut pas traduire argument\n");
    }
    else fprintf(stderr,"Arguments pas valide\n");
    return(0);
}


/*-------------------------------------------------------------
Function: creerEnfantEtLire
Arguments: 
	int prcNum - le numero de processus
Description:
	Cree l'enfant, en y passant prcNum-1. Utilise prcNum
	comme identificateur de ce processus. Aussi, lit les
	messages du bout de lecture du tuyau et l'envoie a 
	la sortie standard (df 1). Lorsqu'aucune donnee peut
	etre lue du tuyau, termine.
-------------------------------------------------------------*/

void creerEnfantEtLire(int prcNum)
{

    /* S.V.P. completez cette fonction selon les
       instructions du devoirs. */
}
