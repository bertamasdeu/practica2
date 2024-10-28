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

void PrintVect( float vect[N], int from, int numel ) {      // funció per imprimir un número numel d'elements des de la posició from
    int i;                                  // declarem la variable pel bucle
    for (i=from;i<numel;i++){               
        printf("%f\n ",vect[i]);            // imprimim element per element
    }
}

void PrintRow( float mat[N][N], int row, int from, int numel ) {    // funció per imprimir un número numel d'elements des de la posició from i una fila row
    int i;                                  // declarem la variable pel bucle
    for (i=from;i<numel;i++){               
        printf("%f\n ",mat[row][i]);        // imprimim element per element
    }
}

void  MultEscalar( float vect[N], float vectres[N], float alfa ) {  // funció per calcular la funció escalar de un vector i una constant
    int i;                                  // declarem la variable pel bucle
    for (i=0;i<N;i++){
        vectres[i]=vect[i]*alfa;            // multipliquem cada element per la constant i la guardem a un vector nou
    }
}

float Scalar( float vect1[N], float vect2[N] ) {        // funció per fer el producte escalar entre dos vectors
    int i;                                  // declarem la variable pel bucle
    float resultat=0;                       // declarem la variable per assignar-li el resultat 
    for (i=0;i<N;i++) {
        resultat += vect1[i] * vect2[i];    // sumem al resutat cada una de les multiplicacions entre els elements dels vectors
    }
    return resultat;                        // retornem el resultat de la funció
}

float Magnitude( float vect[N] ) {          // funció per calcular la magnitud d'un vector
    float sumaquadrats = 0;                 
    for (int i = 0; i < N; i++) {
        sumaquadrats += vect[i] * vect[i];  // sumem tots els quadrats amb un bucle en una variable
    }
    float resultat = sqrt(sumaquadrats);    // calculem l'arrel quadrada de la variable de la suma total
    return resultat;                        // retornem el resultat de la funció
}

intOrtogonal( float vect1[N], float vect2[N] ) {        // funció per determinar si dos vectors són ortogonals
    float multiplescalar = Scalar( vect1[N], vect2[N] );    // calculem la multiplicació escalar dels dos vectors
    if (multiplescalar == 0) {
        return 1;                           // si la multiplicació escalar és 0, els vectors són ortogonals i retornem el valor 1
    } else {
        return 0;                           // si la multiplicació escalar no és 0, els vectors no són ortogonals i retornem el valor 0
    }
}

void  Projection( float vect1[N], float vect2[N], float vectres[N] )  { // funció per calcular el vector projecció d'un vector 1 sobre un vector 2 
    float prodescalar = Scalar(vect1[N], vect2[N]);     // calculem la multiplicació escalar dels dos vectors
    float quadrat = Magnitude(vect2);                   // calculem la magnitud del segon vector
    
    float projeccioescalar = prodescalar / quadrat;     // fem la projecció amb la divisió de la multiplicaicó escalar entre la magnitud

    vectres[i] = MultEscalar (vect2[i], vectres[N], projeccioescalar);  // trobem el resultat de la funció fent la multiplicació escalar de la projecció escalar i el vector 2
}

float Infininorm(float M[N][N]) {           // funció per calcular la Infini-norma d’una matriu
    float max_suma = 0.0; 
    float suma_fila;                        // creem les variable necessàries per a fer els pròxims càlculs
    for (int i = 0; i < N; i++) {           // bucle per anar fila per fila
        suma_fila = 0;                      // assignem el valor 0 a la suma de la fila cada cop que la canvia
        for (int j = 0; j < N; j++) {       // creem un bucle per anar columna per columna dins la fila
            suma_fila += fabs(M[i][j]);     // calculem la suma dels valors absoluts dels elements de cada fila
        }
        if (suma_fila > max_suma)
            max_suma = suma_fila;           // si la suma supera el màxim establert, aquesta esdevé el nou màxim
    }
    return max_suma;                        // retornem la Infini-norma, que serà la suma amb el valor màxim
}

float Onenorm( float M[N][N] ) {            // funció per calcular la norma-ú d'una matriu
    float suma_columna;
    float max_columna = 0;                  // creem les variable necessàries per a fer els pròxims càlculs
    for (int j = 0; j < N; j++) {           // bucle per anar columna per columna
        suma_columna = 0;                   // assignem el valor 0 a la suma de la columna cada cop que la canvia
        for (int i = 0; i < N; i++) {       // creem un bucle per anar fila per fila dins la columna
            suma_columna += fabs(M[i][j]);  // calculem la suma de la columna
        }
        if (suma_columna > max_suma)
            max_suma = suma_columna;        // si la suma supera el màxim establert, aquesta esdevé el nou màxim
    }
    return max_suma;                        // retornem la norma-ú, que serà la suma amb el valor màxim
}

float NormFrobenius( float M[N][N] ) {
    float sumaquadrats = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            sumaquadrats = sumaquadrats + ( M[i][j] * M[i][j] );
        }
    }
    float resultat = sqrt(sumaquadrats);
    return resultat;
}

int DiagonalDom( float M[N][N] ) {
    float element_diag = 0;
    float suma_nodiag;
    for (int i = 0; i < N; i++) {
        suma_nodiag = 0;
        for (int j = 0; j < N; j++) {
            if (i!=j) 
                suma_nodiag = suma_nodiag + fabs(M[i][j]);
        }
        if (fabs(M[i][i])<suma_nodiag) 
            return 0;
    }
    return 1;
}

// FALTA EL 12 I EL 13
void Matriu_x_Vector( float M[N][N], float vect[N], float vectres[N] ) {

}

int main(){}