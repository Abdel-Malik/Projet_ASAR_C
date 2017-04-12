#include "lectureWav.h"

int main()
{
    FichierWav leSon;
    int ret = chargeSonEnMemoire(NOM_FICHIER_ENTREE, &leSon);
    if(ret == OK)
        afficheEnteteWav(leSon.entete);
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
