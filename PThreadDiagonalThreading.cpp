#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

//////////////////////////////////////////////////////////
struct MatrixDetails
{ int _matrixSize, _numberOfThreads, threadNumber;
  int** _matrix;
};   
//////////////////////////////////////////////////////////

void* DoDiagTransposition(void *tempMatrixDetails)
//Algorithm respondible for 2d matrix multiplication. Iterates through Matrices multiply corresponding row and column values
//then summing them together and inserting this new value into the output matrix.

{
  int ThreadNumber;
  int blockSize;
  int endRow;
  int beginRow;
  int temp;
  int iCount = 0;
  
  int** g_matrix = ((struct MatrixDetails *)tempMatrixDetails) -> _matrix;
  int g_matrixSize = ((struct MatrixDetails *)tempMatrixDetails) -> _matrixSize;
  int g_numberOfThreads = ((struct MatrixDetails *)tempMatrixDetails) -> _numberOfThreads;
  ThreadNumber = ((struct MatrixDetails *)tempMatrixDetails) -> threadNumber;

  blockSize = g_matrixSize/g_numberOfThreads;
  endRow = (ThreadNumber+1)*blockSize;
  beginRow = ThreadNumber*blockSize;

  for (int i = beginRow; i < endRow; i++) 
  {     
        for (int k = i; k < g_matrixSize; k++)
        {
            temp = g_matrix[i][k];
            g_matrix[i][k] = g_matrix[k][i];
            g_matrix[k][i] = temp;           
        }
  }
}

void outputMatrix(int** tempMatrix, int mSize)
//Funtion to output a matrix to the console
{
  int j;

  for (int i = 0; i < mSize; i++) 
  {
    for (j = 0; j < mSize-1; j++) 
    {
      printf("%d, ", tempMatrix[i][j]);
    }
    printf("%d", tempMatrix[i][j]);
    putchar('\n');
  }
}

void DiagonalTransposition(int** matrixToTranspose, int matrixSize, int numberOfThreads)
{
  struct MatrixDetails *tempMatrixDetails;
  pthread_t * pThreads;

  tempMatrixDetails = (struct MatrixDetails *)malloc(numberOfThreads*sizeof(MatrixDetails));
  pThreads = (pthread_t*)malloc(numberOfThreads*sizeof(pthread_t));

  //printf("Matrix to Transpose \n\n");
  //outputMatrix(matrixToTranspose, matrixSize);
  //printf("\n");

//Each Thread deaks with a portion of the matrix multiplication, with the portion to be covered being dictated by the threadNumber
//which is a reference to a specific segment of data
  for (int i = 0; i < numberOfThreads; i++) 
  {
    (tempMatrixDetails + i) -> _matrixSize = matrixSize;
    (tempMatrixDetails + i) -> _numberOfThreads = numberOfThreads;
    (tempMatrixDetails + i) -> _matrix = matrixToTranspose;
    (tempMatrixDetails + i) -> threadNumber = i;

    pthread_create(&pThreads[i], NULL, DoDiagTransposition, (void *) (tempMatrixDetails + i));
  }

  for (int i = 0; i < numberOfThreads; i++) 
  {
    pthread_join(pThreads[i], NULL);
  }

  //printf("\nTransposed Matirx\n\n");
  //outputMatrix(matrixToTranspose, matrixSize);
}