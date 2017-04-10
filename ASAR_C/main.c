#include "lectureWav.h"

int main()
{

    FichierWav leSon;
    int ret = chargeSonEnMemoire(NOM_FICHIER_ENTREE, &leSon);
    if(ret == OK)
        afficheEnteteWav(leSon.entete);
    for(int i = 0; i <4*50; i=i+4){
        float a = (leSon.son[i]<<8)+leSon.son[i+1];
        a = a/131072;
        float b = (leSon.son[i+2]<<8)+leSon.son[i+3];
        b = b/131072;
        printf("\n%f %f %d",a,b,i);
    }
    return OK;
}
