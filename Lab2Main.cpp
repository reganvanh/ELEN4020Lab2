#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
#include <vector>
#include <ctime>
#include <vector>
#include <iostream>
#include <ctime>
#include "matrixTransposeNaive.cpp"
#include "matrixBlockTransposeOpenMP.cpp"
#include "PThreadDiagonalThreading.cpp"
#include "OpenMPDiagonalThreading.cpp"

using namespace std;

int** CreateMatrix(int mSize)
//Indicates space in memory to be allocated to the matrix
{
  int* Blocks = (int*) malloc(mSize*mSize*sizeof(int));
  int** rowStart = (int**) malloc(mSize*sizeof(int*));
  for (int i = 0; i < mSize; ++i) 
  {
    rowStart[i] = &Blocks[i*mSize];
  }
  return rowStart;
}

void InitialiseRandomMatrix(int** tempMatrix, int mSize)
{
//Fills allocated matrix with random numbers in a specified range
  for (int i = 0; i < mSize; i++) 
  {
    for (int j = 0; j < mSize; j++) 
    {
      tempMatrix[i][j] = (rand()%mSize);
    }
  }
}

int main()
{ 
    int matrixSize[4] = {128, 1024, 2048 ,4096};
    auto matrixA = vector<vector<int>>{};
    auto colVec = vector<int>{};
    auto num = 0;
    double wtime;
    double total = 0;
    srand(47);

    for(int v = 0 ; v < 4 ; ++v)
    {
      for(auto row = 0; row < matrixSize[v] ; ++row)
      {
        for(auto col = 0; col < matrixSize[v] ; ++col)
        {
          colVec.push_back(rand()%matrixSize[v]);
          //cout << *(--colVec.end()) << " "; 
        }

        matrixA.push_back(colVec);
        colVec.erase(colVec.begin(), colVec.end());
        //cout << endl;
      }

        //------------------------------------------------------------------------
        //Performing Transposition using OpenMP
        //------------------------------------------------------------------------       

        for(int f = 0; f < 10 ;++f)
        {
            wtime = omp_get_wtime ( );  //Start timing            
            MatrixTransposeNaive(&matrixA);
            wtime = omp_get_wtime ( ) - wtime;  // Stop timing
            total = total + wtime;
        }

        cout << "Naive Approach OpenMP: Average Time to transpose a N = " << matrixSize[v]  << " matrix : " <<  total/10 <<  " s." << endl;
        
        total = 0;
        for(int f = 0; f < 10 ;++f)
        {
            wtime = omp_get_wtime ( );  //Start timing
            
            blockTransposeOpenMP(&matrixA);

            wtime = omp_get_wtime ( ) - wtime;  // Stop timing
        
            total = total + wtime;
        }

        cout << "Block Method OpenMP: Time to transpose a N = " << matrixSize[v]  << " matrix : " <<  total/10.0 <<  " s." << endl;

        matrixA.erase(matrixA.begin(), matrixA.end());

        //------------------------------------------------------------------------
        //Performing Diagonal Transposition using pThread
        //------------------------------------------------------------------------

        int numberOfThreads = 8;
        int size;
        int** matrixToTranspose;
        total = 0;
        size = matrixSize[v];
        matrixToTranspose = CreateMatrix(size);
        InitialiseRandomMatrix(matrixToTranspose, size);

        for(int f = 0; f< 10; ++f)
        {
            wtime = omp_get_wtime ( );  //Start timing            
            DiagonalTransposition(matrixToTranspose, size, numberOfThreads);
            wtime = omp_get_wtime ( ) - wtime;  // Stop timing
            total = total + wtime;
        }
        
        cout << "Diagonal Method pThread: Time to transpose a N = " << matrixSize[v]  << " matrix : " <<  total/10.0 <<  " s." << endl;

        delete matrixToTranspose;

        //------------------------------------------------------------------------
        //Performing Diagonal Transposition using OpenMP
        //------------------------------------------------------------------------

        int** matrixToTranspose2;
        total = 0;
        size = matrixSize[v];
        matrixToTranspose2 = CreateMatrix(size);
        InitialiseRandomMatrix(matrixToTranspose2, size);

        for(int f = 0; f< 10; ++f)
        {
            wtime = omp_get_wtime ( );  //Start timing
            
            DiagonalTranspositionOpenMP(matrixToTranspose2, size);

            wtime = omp_get_wtime ( ) - wtime;  // Stop timing
            total = total + wtime;
        }
        
        cout << "Diagonal Method OpenMP: Time to transpose a N = " << matrixSize[v]  << " matrix : " <<  total/10.0 <<  " s." << endl;

        delete matrixToTranspose2;
        
    }
    return 0;
}