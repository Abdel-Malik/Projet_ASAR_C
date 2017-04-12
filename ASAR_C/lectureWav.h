#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#ifndef ENTETE_H
#define ENTETE_H

/**TODO
Pensez à vérifier que
sur le système embarqué
sizeof(int) = 4octets**/

typedef struct { //structure (globale) ou seront stockées les infos importantes  de l'entete
    char FileTypeBlocID[5];  /* devra être une chaine de caractères terminée par 0 */
    unsigned int FileSize;
    char FileFormatID[5];
    char FormatBlocID[5];
    int BlocSize;
    short int AudioFormat;
    short int NbrCanaux;
    int Frequence;
    int BytePerSec;
    short int BytePerBloc;
    short int BytePerSample;
}EnTeteWav;

typedef struct{
    EnTeteWav entete;
    char motData[5];
    int tailleSon;
    char *son;
    int ptZoneSon;
}FichierWav;



/************************************/
/****** definition prototypes  ******/
/************************************/
/*lectureWav.c*/
void litEnteteWav(FILE *fSon, EnTeteWav *eTwav);
int litCorpsWav(FILE *fSon, FichierWav *fwav);
int chargeSonEnMemoire(char *nomDeFichierWav, FichierWav *wav);
void afficheEnteteWav(EnTeteWav enTeteWav);
<<<<<<< HEAD
void recupCanalGauche(float **canalGauche, FichierWav leSon);
=======
void recupCanalGauche(char *canalGauche, FichierWav leSon);
>>>>>>> parent of e4d781d... Récupération du canal gauche de l'enregistrement


/************************************/
/****** definition constantes  ******/
/************************************/
#define ERREUR 0
#define OK 1
#define OFFSET_4CHAR 4
#define OFFSET_INT 4
#define OFFSET_SHORT 2
//#define OFFSET_...//TODO//

/** Fichier dont le programme s'occupe **/
#define NOM_FICHIER_ENTREE "ASAR/Phone.wav"

#endif
