/*------------------------------------------------------------
Fichier: cpr.c

Nom et Numéro étudiant: Océane Prud'Homme (300272920) et Lili Rose Théoret (300342096)
Groupe #1 sur Brightspace.

Description: Ce programme contient le code pour la creation
             d'un processus enfant et y attacher un tuyau.
	     L'enfant envoyera des messages par le tuyau
	     qui seront ensuite envoyes a la sortie standard.

Explication du processus zombie
(point 5 de "A completer" dans le devoir):

	Un processus zombie est un processus enfant terminé dont le parent n’a pas encore récupéré le statut avec wait(). 
	Il ne consomme pas de ressources, mais garde une entrée dans la table des processus. 
	S’il y en a trop, ils peuvent empêcher la création de nouveaux processus
	Lorsque le parent appelle wait(), le processus se termine normalement.
	Dans ce cas-ci, le parent n'appelle jamais wait(). Le zombie "meurt" lorsque le parent termine.
	Site reference: https://www.geeksforgeeks.org/operating-systems/zombie-processes-prevention/


-------------------------------------------------------------*/
#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


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
    int fd[2];	// Descripteurs de fichiers pour le bout de lecture et le bout d'écriture du tuyau
    pid_t pid;	// PID
    char buffer[256];	// Buffer pour les messages
    int nbCharLus;	// Nombre de caractères lus via read()

    sprintf(buffer, "Processus %d commence\n", prcNum);	// Print dans le tampon de mémoire
    write(1, buffer, strlen(buffer));	// Écrire les données du tampon dans la sortie standard

    fflush(stdout);	// Force l'écriture immédiate

    if(prcNum == 1)	// Cas final du dernier enfant
    {
        sleep(5);	// Dormir pendant sqrt(25) secondes

        sprintf(buffer, "Processus %d termine\n", prcNum);	// Print dans le tampon de mémoire
        write(1, buffer, strlen(buffer));	// Écrire les données du tampon dans la sortie standard

        sleep(10);	// Dormir pendant 5*2 secondes

        return;	// Fin de la méthode
    }

    if(pipe(fd) == -1)	// Création du pipe
    {
        perror("pipe");
        exit(1);
    }

    pid = fork();	// Création de l'enfant du processus parent

    if(pid < 0)	// Erreur dans la création de l'enfant du processus parent
    {
        perror("fork");
        exit(1);
    }

    if(pid == 0)	// Car l'enfant à 0 dans sa variable pid
    {
        char prochainNum[20];	// Pour indiquer le numéro du prochain enfant

        close(fd[0]);	// Fermer le bout de lecture pour écrire

        dup2(fd[1], 1);	// Redirige la sortie standard vers le bout d'écriture du pipe

        close(fd[1]);	// Fermer le bout d'écriture puisque l'écriture est terminée

        sprintf(prochainNum, "%d", prcNum - 1);	// Print dans le tampon de mémoire

        char *args[] = {"./cpr", prochainNum, NULL};	// Arguments à passer à la prochaine exécution de cpr.c

        execvp(args[0], args);	// Remplace l'image du processus avec le programme spécifié, ici cpr.c défini dans la ligne précédente

        perror("execvp");	// En cas d'erreur du execvp, ne devrait pas s'exécuter
        exit(1);	// Fin en cas d'erreur du execvp, ne devrait pas s'exécuter
    }

    else	// Si le pid est supérieur à 0, alors c'est le processus parent
    {
        close(fd[1]);	// Fermer le bout d'écriture pour pouvoir lire

        while((nbCharLus = read(fd[0], buffer, sizeof(buffer))) > 0)	// Lecture du pipe
        {
            write(1, buffer, nbCharLus);	// Écriture dans le pipe
        }

        close(fd[0]);	// Fermer le bout de lecture

        sprintf(buffer, "Processus %d termine\n", prcNum);	// Print dans le tampon de mémoire
        write(1, buffer, strlen(buffer));	// Écrire les données du tampon dans la sortie standard

        sleep(10);	// Dormir pendant 20/2 secondes
    }
}
