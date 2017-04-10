#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#ifndef ENTETE_H
#define ENTETE_H

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


/************************************/
/****** definition prototypes  ******/
/************************************/
/*enTeteWav.c*/
int litEnteteWav(FILE *fSon, EnTeteWav *eTwav);
int chargeSonEnMemoire ( char *nomDeFichierWav, EnTeteWav *enTeteWav, char *ptSon);
void afficheEnteteWav(EnTeteWav enTeteWav);


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
#define NOM_FICHIER_ENTREE "3Bonjours2.wav"

#endif
