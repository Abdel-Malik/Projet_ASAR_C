#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#ifndef ENTETE_H
#define ENTETE_H

 typedef struct { //structure (globale) ou seront stockées les infos importantes  de l'entete
  char FileTypeBlocID[5];  /* devra être une chaine de caractères terminée par 0 */
  int FileSize;
  int FileFormatID;
  char[5] FileFormatID;
  int FormatBlocID;
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


/************************************/
/****** definition constantes  ******/
/************************************/
#define ERREUR 0
#define OK 1
//#define OFFSET_...//TODO//

/** Fichier dont le programme s'occupe **/
#define NOM_FICHIER_ENTREE "pianoLa.wav"

#endif
