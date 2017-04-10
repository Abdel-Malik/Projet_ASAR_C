#include "lectureWav.h"

int litEnteteWav(FILE *fSon, EnTeteWav *eTwav){
    fseek(fSon,0,SEEK_SET);

    fread(eTwav->FileTypeBlocID,sizeof(char),4,fSon);
    eTwav->FileTypeBlocID[4] = '\0';

    fread(&(eTwav->FileSize),sizeof(unsigned int),1,fSon);

    fread(eTwav->FileFormatID,sizeof(char),4,fSon);
    eTwav->FileFormatID[4] = '\0';

    fread(eTwav->FormatBlocID,sizeof(char),4,fSon);
    eTwav->FormatBlocID[4] = '\0';

    fread(&(eTwav->BlocSize),sizeof(int),1,fSon);

    fread(&(eTwav->AudioFormat),sizeof(short int),1,fSon);

    fread(&(eTwav->NbrCanaux),sizeof(short int),1,fSon);

    fread(&(eTwav->Frequence),sizeof(int),1,fSon);

    fread(&(eTwav->BytePerSec),sizeof(int),1,fSon);

    fread(&(eTwav->BytePerBloc),sizeof(short int),1,fSon);

    fread(&(eTwav->BytePerSample),sizeof(short int),1,fSon);
    return OK;
}

/***
param in  : chemin d'accès vers le fichier wav d'entrée.
      out : pointeur sur la structure EnTeteWav.
      out : pointeur sur la zone mémoire du son.
  but : séparer en-tête et son et allouer des espaces mémoire.
***/
int chargeSonEnMemoire ( char *nomDeFichierWav, EnTeteWav *enTeteWav, char *ptSon){
    FILE *fSon;
    if ((fSon = fopen(nomDeFichierWav, "rb"))== NULL){
       printf (" probleme ouverture fichier %s\n", nomDeFichierWav);
       return ERREUR;
    }
    litEnteteWav(fSon,enTeteWav);

    //fseek(fichier,0,SEEK_SET);
    //fread(*ptEntete,(enTeteBMP->tailleFichier)-tailleIMG,1,fichier);
    //TODO
    fclose(fSon);
    return OK;
}

/***
param
      in : enTete bitmap.
  but : Présenter les informations présentes dans l'entête.
***/
void afficheEnteteWav(EnTeteWav enTete){
    printf("**** En tete du fichier Wav **** \n");
    printf (" Type de bloc : %s\n",enTete.FileTypeBlocID);
    printf (" Taille du fichier : %u \n",enTete.FileSize);
    printf (" Format : %s\n",enTete.FileFormatID);
    printf (" FormatBloc : %s\n",enTete.FormatBlocID);
    printf (" TailleBloc : %d\n",enTete.BlocSize);
    printf (" FormatAudio : %hd\n",enTete.AudioFormat);
    printf (" nombre de canaux : %hd\n",enTete.NbrCanaux);
    printf (" Frequence : %d\n",enTete.Frequence);
    printf (" nb octet/s : %d\n",enTete.BytePerSec);
    printf (" Nb octet par bloc : %hd\n",enTete.BytePerBloc);
    printf (" nb bit pour codage : %hd\n",enTete.BytePerSample);
}
