#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
#define N 512


float Mat[N][N];
float MatDD[N][N];
float V1[N];
float V2[N];
float V3[N]; 

void InitData(){ 
int i,j;
srand(334411); 
for( i = 0; i < N; i++ ) 
for( j = 0; j < N; j++ ){ 
Mat[i][j]=(((i*j)%3)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX)));  
if ( (abs(i - j) <= 3) && (i != j)) 
MatDD[i][j] = (((i*j)%3) ? -1 : 1)*(rand()/(1.0*RAND_MAX)); 
else if ( i == j ) 
MatDD[i][j]=(((i*j)%3)?-1:1)*(10000.0*(rand()/(1.0*RAND_MAX))); 
else MatDD[i][j] = 0.0; 
} 
for( i = 0; i < N; i++ ){ 
V1[i]=(i<N/2)?(((i*j)%3)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX))):0.0; 
V2[i]=(i>=N/2)?(((i*j)%3)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX))):0.0; 
V3[i]=(((i*j)%5)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX))); 
} 
} 

void PrintVect( float vect[N], int from, int numel ) {
    int i;
    for (i=from;i<numel;i++){
        printf("%f\n ",vect[i]);
    }
}

void PrintRow( float mat[N][N], int row, int from, int numel ) {
    int i;
    for (i=from;i<numel;i++){
        printf("%f\n ",mat[row][i]);
    }
}

void  MultEscalar( float vect[N], float vectres[N], float alfa ) {
    int i;
    for (i=0;i<N;i++){
        vectres[i]=vect[i]*alfa;
    }
}

float Scalar( float vect1[N], float vect2[N] ) {
    int i;
    float resultat=0;
    for (i=0;i<N;i++) {
        resultat += vect1[i] * vect2[i];
    }
    return resultat;
}

float Magnitude( float vect[N] ) {
    float sumaquadrats = 0;
    for (int i = 0; i < N; i++) {
        sumaquadrats += vect[i] * vect[i]; 
    }
    float resultat = sqrt(sumaquadrats);
    return resultat; 
}

intOrtogonal( float vect1[N], float vect2[N] ) {
    float multiplescalar = Scalar( vect1[N], vect2[N] );
    if (multiplescalar == 0) {
        return 1;
    } else {
        return 0;
    }
}

void  Projection( float vect1[N], float vect2[N], float vectres[N] )  {
    float prodescalar = Scalar(vect1, vect2); 
    float quadrat = Magnitude(vect2);
    
    float projeccioescalar = prodescalar / quadrat; 

    for (int i = 0; i < N; i++) {
        vectres[i] = projeccioescalar * vect2[i];
    }
    return vectres;
}

float Infininorm(float M[N][N]) {
    float max_suma = 0.0; 
    float suma_fila;

    for (int i = 0; i < N; i++) {
        suma_fila = 0.0;
        for (int j = 0; j < N; j++) {
            suma_fila += fabs(M[i][j]);
        }
        if (suma_fila > max_suma) {
            max_suma = suma_fila; 
        }
    }
    return max_suma;
}


int main(){}