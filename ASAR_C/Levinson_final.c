#include "lectureWavFinal.h"

#define NR_END 1
#define FREE_ARG char*

void opti(float* tab,float *rA,int n,int ordre){
    double sAmeliore;
    int bloc,k,max;
    for(int i=0; i<ordre+1; i++){
        sAmeliore = 0;
        bloc = 0;
        if(i>0)
            max = ((n)/(2*i)-1);
        else
            max = 0;
        while(bloc<max){
            int index = bloc*2*i;
            for(int p=0;p<i;p++){
                sAmeliore += (tab[index]+tab[index+2*i])*tab[index+i];
                index++;
            }
            bloc++;
        }
        k = bloc*2*i;
        while(k+i<n){
            sAmeliore += tab[k]*tab[k+i];
            k++;
        }
        rA[i] = sAmeliore;
    }
}

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

    int p = 5; //Ordre égale à AR(p-1)
    p = p+1;
    float *data;
    int taille;

    taille = conversionFloat20msCanalI(&data,1);//donnees recuperees a partir du fichier wav

    int i;
    float r[p];
    double som;

	//Calcul des coéfficients d'autocorrélation
    opti(data,&r,taille,p);

    //Mise en forme du tableau des coeffs d'autocorrelation rr[] pour Levinson()
    float rr[2*p-1];

    int k;
    for(k=0; k<2*p-2; k++){
        if(k == 0){
            rr[k] = 0;
        }
        else if(k<=p-2){
            rr[k] = r[p-k-1];
        }
        else{
            rr[k] = r[k-p+1];
        }
    }

    float a[p]; //Initialisation d'un tableau vide pour les coeffs d'autoregression

    Levinson(rr, a, r, p-1); //Resolution du systeme
    printf("\na = [" ); //Affichage de la solution -> affichage des coeffs d'autoregression

    for(i=1; i<p; i++){
        if(i<p-1){
            printf("%1.4f, ", -a[i]);
        }
        else{
            printf("%1.4f", -a[i]);
        }
    }

    printf("]\n");


    return;
}


