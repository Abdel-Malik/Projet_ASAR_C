#include "lectureWav.h"

int main()
{
    FichierWav leSon;
    int ret = chargeSonEnMemoire(NOM_FICHIER_ENTREE, &leSon);
    if(ret == OK)
        afficheEnteteWav(leSon.entete);
    char *canalGauche;
    recupCanalGauche(&canalGauche,leSon);
    float a = (((char)(0b11111010)<<8)+(char)0b11111111); //fa.ff
    a = a/32765;
    printf("\n%f",a);
    a = (((char)(0b11111111)<<8)+(char)0b01011111); //mirroir de fa.ff => ff.5f
    a = a/32765;
    printf("\n%f",a);
    a = (((char)(0b11111111)<<8)+(char)0b11110101); //mirroir de ff.af => ff.f5
    a = a/32765;
    int16_t b = -0.0001831;
    printf("\n%f",b);
    for(int i = 10; i <0; i=i+2){
        float a = (canalGauche[i+1]<<8)+canalGauche[i];
        a = a/32765;
        printf("\n%f et %d",a,i/2);
    }
    return OK;
}
