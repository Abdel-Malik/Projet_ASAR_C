#include "lectureWav.h"

int main()
{
    EnTeteWav enTeteWav;
    char *son;
    chargeSonEnMemoire(NOM_FICHIER_ENTREE, &enTeteWav, son);
    afficheEnteteWav(enTeteWav);
    return OK;
}
