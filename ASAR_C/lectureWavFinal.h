#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <time.h>
#ifndef ENTETE_H
#define ENTETE_H


typedef struct { //structure ou seront stockées les infoRmations importantes  de l'entete
    char FileTypeBlocID[5];  /* devra être une chaine de caractères terminée par 0 */
    unsigned int FileSize;
    char FileFormatID[5];    /* devra être une chaine de caractères terminée par 0 */
    char FormatBlocID[5];	 /* devra être une chaine de caractères terminée par 0 */
    int BlocSize;
    short int AudioFormat;
    short int NbrCanaux;
    int Frequence;
    int BytePerSec;
    short int BytePerBloc;
    short int BytePerSample;
}EnTeteWav;

typedef struct{  //structure principale. Permet de manitupler les fihcier wav.
    EnTeteWav entete;
    char motData[5]; 	/* devra être une chaine de caractères terminée par 0 */
    int tailleSon;
    char *son;
}FichierWav;



/************************************/
/****** definition prototypes  ******/
/************************************/
/*lectureWav.c*/
void litEnteteWav(FILE *fSon, EnTeteWav *eTwav);
int litCorpsWav(FILE *fSon, FichierWav *fwav);
int chargeSonEnMemoire(char *nomDeFichierWav, FichierWav *wav);
void afficheEnteteWav(EnTeteWav enTeteWav);
int conversionFloat20msCanalI(float** tab, char canalChoisi, int numEchantillonDepart);


/************************************/
/****** definition constantes  ******/
/************************************/
#define ERREUR 0
#define OK 1
#define OFFSET_4CHAR 4
#define OFFSET_INT 4
#define OFFSET_SHORT 2

/** Fichier dont le programme s'occupe **/
#define NOM_FICHIER_ENTREE "3Bonjours2.wav" //Le fichier lu. (se trouve au même endroit que les fichiers c)

#endif
