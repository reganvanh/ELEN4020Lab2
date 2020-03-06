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

using namespace std;

// void swop(int* num1, int* num2)
// {
//     *num1 = *num1 + *num2;
//     *num2 = *num1 - *num2;
//     *num1 = *num1 - *num2; 

// }

int main()
{
    auto matrixSize = 4096;
    auto matrixA = vector<vector<int>>{};
    auto colVec = vector<int>{};
    auto num = 0;
    double wtime;

    srand(47);
        for(auto row = 0; row < matrixSize ; ++row)
        {
            for(auto col = 0; col < matrixSize ; ++col)
            {
                colVec.push_back(rand()%matrixSize);
                cout << *(--colVec.end()) << " "; 
            }

            matrixA.push_back(colVec);
            colVec.erase(colVec.begin(), colVec.end());
            cout << endl;
        }
    
        wtime = omp_get_wtime ( );  //Start timing
        
        MatrixTransposeNaive(&matrixA);

        wtime = omp_get_wtime ( ) - wtime;  // Stop timing

        cout << "Naive Approach : Time to transpose a N = " << matrixSize  << " matrix : " <<  wtime <<  " s." << endl;


        wtime = omp_get_wtime ( );  //Start timing
        
            blockTransposeOpenMP(&matrixA);

        wtime = omp_get_wtime ( ) - wtime;  // Stop timing

        cout << "Block Method : Time to transpose a N = " << matrixSize  << " matrix : " <<  wtime <<  " s." << endl;

    return 0;
}