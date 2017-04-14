#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "LectureWav.c"

#define NR_END 1
#define FREE_ARG char*


float *vector(long nl, long nh) /* allocate a float vector with subscript range v[nl..nh] */
{
	float *v;
	v = (float *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(float)));

	if (!v){
            printf("allocation failure in vector()");
	}

	return v-nl+NR_END;
}


void free_vector(float *v, long nl, long nh) /* free a float vector allocated with vector() */
{
	free((FREE_ARG) (v+nl-NR_END));
}

#define FREERETURN {free_vector(h,1,n);free_vector(g,1,n);return;}



void Levinson(float r[], float x[], float y[], int n){

    int j,k,m,m1,m2;
    float pp,pt1,pt2,qq,qt1,qt2,sd,sgd,sgn,shn,sxn;
    float *g, *h;


    if(r[n] == 0){
        printf("error : toeplitz-1 singular principal minor \n");
    }
    g = vector(1,n);
    h = vector(1,n);

    x[1] = y[1]/r[n]; //Initialize for the recursion

    if(n == 1) FREERETURN

    g[1] = r[n-1]/r[n];
    h[1] = r[n+1]/r[n];


    for(m=1; m<=n; m++){ //Main loop over the recursion
        m1 = m+1;
        sxn = -y[m1]; //Compute numerator and denominator for x,
        sd = -r[n];

        for(j=1; j<=m; j++){
            sxn += r[n+m1-j]*x[j];
            sd += r[n+m1-j]*g[m-j+1];
        }

        if(sd == 0){
            printf("error : toeplitz-2 singular principal minor \n");
        }
        x[m1] = sxn/sd; //whence x


        for(j=1; j<=m; j++){
            x[j] -= x[m1]*g[m-j+1];
        }

        if(m1 == n) FREERETURN
        sgn = -r[n-m1]; //Compute numerator and denominator for G and H,
        shn = -r[n+m1];
        sgd = -r[n];

        for(j=1; j<=m; j++){
            sgn += r[n+j-m1]*g[j];
            shn += r[n+m1-j]*h[j];
            sgd += r[n+j-m1]*h[m-j+1];
        }

        if(sgd == 0){
            printf("error : toeplitz-3 singular principal minor \n");
        }
        g[m1] = sgn/sgd;
        h[m1] = shn/sd;
        k = m;
        m2 = (m+1) >> 1;
        pp = g[m1];
        qq = h[m1];

        for(j=1; j<=m2; j++){
            pt1 = g[j];
            pt2 = g[k];
            qt1 = h[j];
            qt2 = h[k];
            g[j] = pt1-pp*qt2;
            g[k] = pt2-pp*qt1;
            h[j] = qt1-qq*pt2;
            h[k--] = qt2-qq*pt1;
        }

    } //Back for another recurrence

        printf("toeplitz - should not arrive here !");

    //return;
}





void main(){

    int p = 5; //Ordre p

    float *data = extractionCanalGauche(); //donnees recuperees a partir du fichier wav

    int n = p;

    int m = n+1;

    float y[m];
    y[0] = 0;

    int i;
    for(i=0; i<m; i++){ //creation de y[m] : y[m] -> y[0] = 0 et y[i+1] = tab[i], pour correspondre aux indices des tableaux de Levinson commencant a i=1
        y[i+1] = data[i];
    }


    float r[n]; //Calcul des coeff d'autocorrelation
    r[0] = 0;
    //float rx[m-1];

    float somme;

    int j; //creation de r[] qui calcule les coeffs d'autocorrelation a partir de tab[]
    for(i=0; i<m; i++){
        somme = 0;
        for(j=1; j<m-i; j++){
            somme += y[j]*y[i+j];
        }
        r[i] = somme;
    }


    //Mise en forme du tableau des coeffs d'autocorrelation rr[] pour Levinson()

    float rr[2*n-1];

    int k;
    for(k=0; k<2*n-2; k++){
        if(k == 0){
            rr[k] = 0;
        }
        else if(k<=n-2){
            rr[k] = r[n-k-1];
        }
        else{
            rr[k] = r[k-n+1];
        }
    }


    float a[n]; //Initialisation d'un tableau vide pour les coeffs d'autoregression

    Levinson(rr, a, r, n-1); //Resolution du systeme

    printf("\na = [" ); //Affichage de la solution -> affichage des coeffs d'autoregression

    for(i=1; i<n; i++){
        if(i<n-1){
            printf("%f, ", -a[i]);
        }
        else{
            printf("%f", -a[i]);
        }
    }

    printf("]\n");


    return;
}


