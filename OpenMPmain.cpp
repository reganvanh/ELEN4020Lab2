#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
#include <vector>
#include <ctime>
#include <vector>
#include <iostream>
#include <ctime>
#include "matrixTransposeNaive.cpp"

using namespace std;

int main()
{
    auto matrixSize = 1024;
    auto matrixA = vector<vector<int>>{};
    auto colVec = vector<int>{};
    auto num = 0;
    double wtime;

    wtime = omp_get_wtime ( );  //Start timing

    srand(47);

    #pragma parellel for shared(matrixA, colVec, row, col)
    {
        for(auto row = 0; row < matrixSize ; ++row)
        {
            // #pragma parellel for
            for(auto col = 0; col < matrixSize ; ++col)
            {
                colVec.push_back(rand()%20);
                cout << *(--colVec.end()) << " "; 
            }
            matrixA.push_back(colVec);
            colVec.erase(colVec.begin(), colVec.end());
            cout << endl;
        }
    }

    wtime = omp_get_wtime ( ) - wtime;  // Stop timing

        //cout << omp_get_max_threads ( ) << endl;
    cout << "Time to transpose a N = " << matrixSize  << " matrix : " <<  wtime <<  " s." << endl;
        cout << "Transposed Matrix" << endl;

    MatrixTransposeNaive(&matrixA);

    return 0;
}