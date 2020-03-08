#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
#include <vector>
#include <ctime>
#include <iostream>

void outputMatrixOpenMP(int** tempMatrix, int mSize)
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

void DiagonalTranspositionOpenMP(int** matrixToTranspose, int matrixSize)
{
    int temp;
    //printf("Matrix to Transpose \n\n");
    //outputMatrixOpenMP(matrixToTranspose, matrixSize);
    //printf("\n");

    #pragma omp parellel for 
    {
        for (int i = 0; i < matrixSize; i++) 
        {     
            for (int k = i; k < matrixSize; k++)
            {
                temp = matrixToTranspose[i][k];
                matrixToTranspose[i][k] = matrixToTranspose[k][i];
                matrixToTranspose[k][i] = temp;           
            }
        }
    }

    //printf("Matrix to Transpose \n\n");
    //outputMatrixOpenMP(matrixToTranspose, matrixSize);
    //printf("\n");
}