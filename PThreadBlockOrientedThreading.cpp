#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void outMatrix(int** tempMatrix, int mSize)
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
void* DoBlockOrientedTranspositionStep1(void *tempMatrixDetails)
{
  int ThreadNumber;
  int blockSize;
  int endRow;
  int beginRow;
  int temp;
  int iCount = 0;
  int end;
  
  int** g_matrix = ((struct MatrixDetails *)tempMatrixDetails) -> _matrix;
  int g_matrixSize = ((struct MatrixDetails *)tempMatrixDetails) -> _matrixSize;
  int g_numberOfThreads = ((struct MatrixDetails *)tempMatrixDetails) -> _numberOfThreads;
  ThreadNumber = ((struct MatrixDetails *)tempMatrixDetails) -> threadNumber;

  blockSize = g_matrixSize/g_numberOfThreads;
  endRow = (ThreadNumber+1)*blockSize;
  beginRow = ThreadNumber*blockSize;
  if(ThreadNumber == g_numberOfThreads)
  {
      end = endRow -1;
  }
  else
  {
      end = endRow;
  }

  for (int row = beginRow; row < end; ++(++row)) 
  {     
        for ( auto col = 1; col < g_matrixSize; ++(++col))
            {
                if (row != col)
                {
                    temp = g_matrix[row][col];
                    g_matrix[row][col] = g_matrix[row + 1][col - 1];
                    g_matrix[row + 1][col - 1] = temp; 
                    
                }
            } 
  }
  
}
void* DoBlockOrientedTranspositionStep2(void *tempMatrixDetails)
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

  for (int row = beginRow; row < endRow; ++(++row)) 
  {  
         
        for (int col = row; col < g_matrixSize; ++(++col))
        {
            if (row != col)
                {
                    
                    temp = g_matrix[row][col];
                    g_matrix[row][col] = g_matrix[col][row];
                    g_matrix[col][row] = temp; 

                    
                    temp = g_matrix[row][col + 1];
                    g_matrix[row][col + 1] = g_matrix[col][row +1 ];
                    g_matrix[col][row +1 ] = temp; 

                    
                    temp = g_matrix[row + 1][col];
                    g_matrix[row + 1][col] = g_matrix[col + 1][row];
                    g_matrix[col + 1][row] = temp;

                    
                    temp = g_matrix[row + 1][col + 1];
                    g_matrix[row + 1][col + 1] = g_matrix[col + 1][row + 1];
                    g_matrix[col + 1][row + 1] = temp; 
                }
                    
        }
  }
  
}
void BlockOrientedTransposition(int** matrixToTranspose, int matrixSize, int numberOfThreads)
{
  struct MatrixDetails *tempMatrixDetails;
  pthread_t * pThreads;

  tempMatrixDetails = (struct MatrixDetails *)malloc(numberOfThreads*sizeof(MatrixDetails));
  pThreads = (pthread_t*)malloc(numberOfThreads*sizeof(pthread_t));

   //printf("Matrix to Transpose \n\n");
   //outMatrix(matrixToTranspose, matrixSize);
   //printf("\n");

  for (int i = 0; i < numberOfThreads; i++) 
  {
    (tempMatrixDetails + i) -> _matrixSize = matrixSize;
    (tempMatrixDetails + i) -> _numberOfThreads = numberOfThreads;
    (tempMatrixDetails + i) -> _matrix = matrixToTranspose;
    (tempMatrixDetails + i) -> threadNumber = i;

    pthread_create(&pThreads[i], NULL, DoBlockOrientedTranspositionStep1, (void *) (tempMatrixDetails + i));
  }

  for (int i = 0; i < numberOfThreads; i++) 
  {
    pthread_join(pThreads[i], NULL);
  }
  for (int i = 0; i < numberOfThreads; i++) 
  {
    (tempMatrixDetails + i) -> _matrixSize = matrixSize;
    (tempMatrixDetails + i) -> _numberOfThreads = numberOfThreads;
    (tempMatrixDetails + i) -> _matrix = matrixToTranspose;
    (tempMatrixDetails + i) -> threadNumber = i;

    pthread_create(&pThreads[i], NULL, DoBlockOrientedTranspositionStep2, (void *) (tempMatrixDetails + i));
  }

  for (int i = 0; i < numberOfThreads; i++) 
  {
    pthread_join(pThreads[i], NULL);
  }

   //printf("\n");
   //printf("Transposed Matirx\n\n");
   //outMatrix(matrixToTranspose, matrixSize);
   //printf("\n");
}    