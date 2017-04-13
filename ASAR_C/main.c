#include "lectureWav.h"

int main()
{
    float* t = extractionCanalGauche();
    printf("%f  %f  %f",t[0],t[1],t[2]);
}
