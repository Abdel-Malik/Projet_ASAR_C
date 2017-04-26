#include "lectureWavFinal.h"


/***
param in : pointeur sur le tableau à allouer, le canal souhaité
param out  : taille du tableau;
  but : Récupération de floats représentant les échantillons du fichier
  Cas ou le canal choisi n'existe pas : Selection du premier canal. (gauche s'il en existe plusieurs)
***/
int conversionFloat20msCanalI(float** tab, char a){
    FichierWav leSon;
    int ret = chargeSonEnMemoire(NOM_FICHIER_ENTREE, &leSon);
	int nbSample = 0;
    if(a > leSon.entete.NbrCanaux)
        a = 1;
    if(ret != OK)
        afficheEnteteWav(leSon.entete);
	else
		nbSample = (leSon.entete.Frequence)/5;  //nombre d'échantillon du signal sur 20ms

	unsigned char *canalGauche = leSon.son;
    signed short int t;
    char nbOctets = leSon.entete.BytePerSample/8; //nombre d'octet sur lequel est codée un echantillon

    *tab = malloc(sizeof(float)*nbSample);
    for(int i = a-1; i <nbSample*leSon.entete.BytePerBloc; i=i+leSon.entete.BytePerBloc){ //K : groupe d'octets d'un échantillon. Lecture K par K [K char => float] K<=4
        t = canalGauche[i+nbOctets-1];
        for(int j = nbOctets-1; j>=0; j--){ //transforme les char d'un échantillon X en un float.
            t = (t<<8)+canalGauche[i+j];
        }
        (*tab)[i/leSon.entete.BytePerBloc] = (float)t/32768;
    }
    free(canalGauche);
    return nbSample;
}
/***
param in  : fichier son, une entete vide.
  but : Compléter la structure entête avec les informations se trouvant dans le fichier
***/
void litEnteteWav(FILE *fSon, EnTeteWav *eTwav){
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
}


/***
param in  : fichier son, corps vide.
  but : Compléter la structure FchierWav avec les informations se trouvant dans le fichier
***/
int litCorpsWav(FILE *fSon, FichierWav *fwav){

    fread(fwav->motData,sizeof(char),4,fSon);
    fwav->motData[4] = '\0';

    fread(&(fwav->tailleSon),sizeof(unsigned int),1,fSon);

    fwav->son = malloc(fwav->tailleSon);
    fread(fwav->son,sizeof(char),fwav->tailleSon,fSon);
    return OK;
}


/***
param in  : chemin d'accès vers le fichier wav d'entrée.
      out : pointeur sur la structure EnTeteWav.
      out : pointeur sur la zone mémoire du son.
  but : séparer en-tête et son et allouer des espaces mémoire.
***/
int chargeSonEnMemoire ( char *nomDeFichierWav, FichierWav *Wav){
    FILE *fSon;
    if ((fSon = fopen(nomDeFichierWav, "rb"))== NULL){
       printf ("probleme d'ouverture du fichier \"%s\"\n", nomDeFichierWav);
       return ERREUR;
    }
    litEnteteWav(fSon,&(Wav->entete));
    litCorpsWav(fSon,Wav);
    fclose(fSon);
    return OK;
}

/***
param
      in : enTete wav.
  but : Présenter les informations présentes dans l'entête.
***/
void afficheEnteteWav(EnTeteWav enTete){
    printf("**** En tete du fichier Wav **** \n");
    printf (" Type de bloc : %s\n",enTete.FileTypeBlocID);
    printf (" Taille du fichier : %u \n",enTete.FileSize+8);
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
