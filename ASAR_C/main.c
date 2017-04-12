#include "lectureWav.h"

int main()
{
    FichierWav leSon;
    int ret = chargeSonEnMemoire(NOM_FICHIER_ENTREE, &leSon);
    if(ret == OK)
        afficheEnteteWav(leSon.entete);
<<<<<<< HEAD
    float *canalGauche;
    recupCanalGauche(&canalGauche,leSon);


    for(int i = 0; i <20; i++){
        printf("\n %f",canalGauche[i]);
    }
    return OK;
}
/*    float a = (((char)(0b11111010)<<8)+(char)0b11111111); //fa.ff
    a = a/32765;
    printf("\n%f",a);
    a = (((char)(0b11111111)<<8)+(char)0b01011111); //mirroir de fa.ff => ff.5f
    a = a/32765;
    printf("\n%f",a);
    a = (((char)(0b11111111)<<8)+(char)0b11110101); //mirroir de ff.af => ff.f5
    a = a/32765;
    int16_t b = -0.0001831;
    printf("\n%f",b);
    */
=======
    char *canalGauche;
    //recupCanalGauche(canalGauche,leSon);
    for(int i = 0; i <4*50; i=i+4){
        float a = (leSon.son[i]<<8)+leSon.son[i+1];
        a = a/131072;
        float b = (leSon.son[i+2]<<8)+leSon.son[i+3];
        b = b/131072;
        printf("\n%f %f %d",a,b,i);
    }
    return OK;
}
>>>>>>> parent of e4d781d... Récupération du canal gauche de l'enregistrement
