//--------------------------------------------------------------
// prodAx.c
//--------------------------------------------------------------
// Calcula el producto de una matriz m x n por un vector tamaño n
//--------------------------------------------------------------
// Auth.  JJCelada - Universidad del Valle de Guatemala
// Date   2021-10-06
// Vers.  1.0


#include <stdio.h>
#include <stdlib.h>


int number_of_threads= 12;


 void prodAx(int m, int n, double * restrict A, double * restrict x,
   double * restrict b);

 int main(int argc, char *argv[]) {
   double *A,*x,*b;
   int i, j, m, n;

   printf("Ingrese las dimensiones m y n de la matriz: ");
   scanf("%d %d",&m,&n);

   //---- Asignación de memoria para la matriz A ----
   if ( (A=(double *)malloc(m*n*sizeof(double))) == NULL )
    perror("memory allocation for A");

   //---- Asignación de memoria para el vector x ----
   if ( (x=(double *)malloc(n*sizeof(double))) == NULL )
    perror("memory allocation for x");

   //---- Asignación de memoria para el vector b ----
   if ( (b=(double *)malloc(m*sizeof(double))) == NULL )
    perror("memory allocation for b");

  printf("Initializing matrix A and vector x\n");

  //---- Inicialización con elementos aleatorios entre 1-7 y 1-13
  for (j=0; j<n; j++)
    x[j] = rand()%7+1;

  for (i=0; i<m; i++)
    for (j=0; j<n; j++)
      A[i*n+j] = rand()%13+1;

  printf("Calculando el producto Ax para m = %d n = %d\n",m,n);

  

//   //cout<< sliceSize << " ES el tamaño de los sub conjuntos"<< endl;
//   #pragma omp parallel for num_threads(number_of_threads)
    // for (int j = 0; j < number_of_threads;j++){
    //     int start = j*sliceSize;
    //     int end = (j+1)*sliceSize;
    //     //cout <<" El bloque numero"<< j << " empieza en"<<start<<" y termina en "<<end<< endl;
    //     par_qsort(Array,start,end);
    // }

    //Dividir la matriz y mandar en bloques iguales 
    int sliceSize= round(m/number_of_threads);
    printf("Se hara con %d Hilos y el tamanio es %d. El tamaño de las particiones deberia ser de %d \n", number_of_threads, m,  sliceSize);
    double start = omp_get_wtime();
    #pragma omp parallel for shared(m,n,A,x,b) private(i,j)
    for(i = 0; i < m; i++) {
        b[i] = 0.0; //inicialización elemento i del vec.
        for(j = 0; j < n; j++) {
        b[i] += A[i*n + j] * x[j]; //producto punto
        }
    }
// for (int j = 0; j < number_of_threads;j++){
//   (void) prodAx(m, n, A, x, b);
// }

  double end = omp_get_wtime();
  double delta = end - start;
  delta = delta*1000;
  printf("El tiempo de ejecucion paralelo fue de %d s %.15f \n" , delta);


//IMPRIMIR EL RESULTADO
  printf("\nb: \n");
  for(j=0; j<n; j++)
    printf("\t%0.0f ",b[j]);
  printf("\n\n");

  printf("El tiempo de ejecucion paralelo fue de %d s %.8f \n" , delta);
  free(A);free(x);free(b);

  return(0);
 }

/* ------------------------
 * prodAx
 * ------------------------
 */
void prodAx(int m, int n, double * restrict A, double * restrict x,
  double * restrict b){

    int i, j;

    for(i=0; i<m; i++){
      b[i]=0.0;


      for(j=0; j<n; j++){
        b[i] += A[i*n + j] * x[j];
      }
    }
  }//----prodAx----
