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

// 1
void PrintVect( float vect[N], int from, int numel ) {      // funció per imprimir un número numel d'elements des de la posició from
    int i;                                  // declarem la variable pel bucle
    for (i=from;i<from+numel;i++){               
        printf("%f ",vect[i]);            // imprimim element per element
    }
    printf("\n");
}

// 2
void PrintRow( float mat[N][N], int row, int from, int numel ) {    // funció per imprimir un número numel d'elements des de la posició from i una fila row
    int i;                                  // declarem la variable pel bucle
    for (i=from;i<numel;i++){               
        printf("%f ",mat[row][i]);        // imprimim element per element
    }
    printf("\n");
}

// 3
void MultEscalar( float vect[N], float vectres[N], float alfa ) {  // funció per calcular la funció escalar de un vector i una constant
    int i;                                  // declarem la variable pel bucle
    for (i = 0; i < N; i++) {
        vectres[i] = vect[i] * alfa;            // multipliquem cada element per la constant i la guardem a un vector nou
    }
}

// 4
float Scalar( float vect1[N], float vect2[N] ) {        // funció per fer el producte escalar entre dos vectors
    int i;                                  // declarem la variable pel bucle
    float resultat=0;                       // declarem la variable per assignar-li el resultat 
    for (i=0;i<N;i++) {
        resultat += vect1[i] * vect2[i];    // sumem al resutat cada una de les multiplicacions entre els elements dels vectors
    }
    return resultat;                        // retornem el resultat de la funció
}

// 5
float Magnitude( float vect[N] ) {          // funció per calcular la magnitud d'un vector
    float sumaquadrats = 0;                 
    for (int i = 0; i < N; i++) {
        sumaquadrats += vect[i] * vect[i];  // sumem tots els quadrats amb un bucle en una variable
    } 
    return sqrt(sumaquadrats);                        // retornem l'arrel quadrada de la variable de la suma total
}

// 6
int Ortogonal( float vect1[N], float vect2[N] ) {        // funció per determinar si dos vectors són ortogonals
    float multiplescalar = Scalar(vect1, vect2);    // calculem la multiplicació escalar dels dos vectors
    if (multiplescalar == 0) {
        return 1;                           // si la multiplicació escalar és 0, els vectors són ortogonals i retornem el valor 1
    } else {
        return 0;                           // si la multiplicació escalar no és 0, els vectors no són ortogonals i retornem el valor 0
    }
}

// 7
void  Projection( float vect1[N], float vect2[N], float vectres[N] )  { // funció per calcular el vector projecció d'un vector 1 sobre un vector 2 
    float prodescalar = Scalar(vect1, vect2);     // calculem la multiplicació escalar dels dos vectors
    float quadrat = Magnitude(vect2) * Magnitude(vect2);            // calculem el quadrat de la magnitud del segon vector
    
    float projeccioescalar = prodescalar / quadrat;     // fem la projecció amb la divisió de la multiplicaicó escalar entre la magnitud
    MultEscalar (vect2, vectres, projeccioescalar);  // trobem el resultat de la funció fent la multiplicació escalar de la projecció escalar i el vector 2
}

// 8
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

// 9
float Onenorm( float M[N][N] ) {            // funció per calcular la norma-ú d'una matriu
    float suma_columna;
    float max_suma = 0;
    float max_columna = 0;                  // creem les variables temporals necessàries per a fer els pròxims càlculs
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

// 10
float NormFrobenius( float M[N][N] ) {      // funció per calcular la norma de Frobenius d'una matriu
    float sumaquadrats = 0;                 // creem les variables temporals necessàries per a fer els pròxims càlculs
    for (int i = 0; i < N; i++) {           // bucle per anar fila per fila
        for (int j = 0; j < N; j++) {       // bucle per anar columna per columna
            sumaquadrats = sumaquadrats + ( M[i][j] * M[i][j] );    // sumem el quadrat de cada element a la variable temporal
        }
    }
    float resultat = sqrt(sumaquadrats);    // definim la variable resultat com l'arrel quadrada de la suma dels quadrats
    return resultat;                        // retornem el resultat (norma de Frobenius)
}

// 11
int DiagonalDom( float M[N][N] ) {          // funció per determinar si una funció és diagonal dominant o no
    float element_diag = 0;
    float suma_nodiag;                      //creem les variables temporals per a fer els càlculs
    for (int i = 0; i < N; i++) {           // bucle per anar fila per fila
        suma_nodiag = 0;                    // definim la suma dels elements que no son de la diagonal com a 0 a cada inici de fila
        for (int j = 0; j < N; j++) {       // bucle per anar columna per columna
            if (i!=j)                       
                suma_nodiag = suma_nodiag + fabs(M[i][j]); // si l'element no pertany a la diagonal l'afegim a la suma d'aquests elements
        }
        if (fabs(M[i][i])<suma_nodiag)      // quan i si la suma dels elements de la fila que no pertanyen a la diagonal superen el valor d'aquest, 
            return 0;                       // s'atura el bucle i es retorna 0, no és diagonal dominant
    }
    return 1;                               // si mai es supera, al final de la funció es retorna 1, és diagonal  dominant
}

// 12
void Matriu_x_Vector( float M[N][N], float vect[N], float vectres[N] ) {    // funció per multiplicar una matriu per un vector
   for (int i = 0; i < N; i++) {            // bucle per anar fila per fila a la matriu
        vectres[i] = 0;
        for (int j = 0; j < N; j++) {       // bulce per anar columna per columna a la matriu i element per element al vector
            vectres[i] += M[i][j] * vect[j];// definim l'element del vector resultant com 
        }
    }
}

// 13
int Jacobi(float M[N][N], float vect[N], float vectres[N], unsigned iter) { // funció per a solucionar sistemes d’equacions lineals amb el mètode Jacobi
    float vector[N] = {0};                  // Creem un vector temporal amb tots els elements a zero per emmagatzemar els valors de cada iteració
    if (!DiagonalDom(M)) {                  // Comprovem si la matriu és diagonal dominant
        return 0;                           // No es pot aplicar el mètode de Jacobi
    }
    for (unsigned k = 0; k < iter; k++) {               // Apliquem el mètode de Jacobi, bucle per repetir el procés el número indicat
        for (int i = 0; i < N; i++) {                   // Bucle per anar fila per fila
            float suma = 0;                             // Definim la suma de la fila 0 al principi del bucle, és a dir, cada canvi de fila
            for (int j = 0; j < N; j++) {               // Bucle per anar columna per columna
                if (i != j) {
                    suma += M[i][j] * vector[j];        // Afegim a la suma els productes del elements no diagonals amb el valor actual de vector
                }
            }
            vectres[i] = (vect[i] - suma) / M[i][i];    // Calculem del nou valor del vector resultat amb la fórmula del mètode de Jacobi
        }
        for (int i = 0; i < N; i++) {                   // Actualitzem el vector amb els nous valors del resultant per a la següent iteració
            vector[i] = vectres[i];
        }
    }
    return 1;                                           // Indiquem que el mètode de Jacobi s'ha aplicat
}

int main(){
    InitData ();
    PrintVect (V1,0,10);
    PrintVect (V1,256,10);
    PrintVect (V2,0,10);
    PrintVect (V2,256,10);
    PrintVect (V3,0,10);
    PrintVect (V3,256,10);
}
