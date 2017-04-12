#include "lectureWav.h"

int main()
{
    FichierWav leSon;
    int ret = chargeSonEnMemoire(NOM_FICHIER_ENTREE, &leSon);
    if(ret == OK)
        afficheEnteteWav(leSon.entete);
    char *canalGauche;
    recupCanalGauche(&canalGauche,leSon);

    for(int i = 0; i <50; i++){
        printf("\n%x",canalGauche[i]);
    }
    return OK;
}
