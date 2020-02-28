#include <stdlib.h>
#include <stdio.h>
#//include "omp.h"
#include <vector>
#include <ctime>
#include <vector>
#include <iostream>
#include "matrixTransposeNaive.cpp"

using namespace std;

int main()
{
    auto matrixSize = 4;
    auto matrixA = vector<vector<int>>{};
    auto colVec = vector<int>{};
    auto num = 0;
    srand(47);
    for(auto row = 0; row < matrixSize ; ++row)
    {
        for(auto col = 0; col < matrixSize ; ++col)
        {
            colVec.push_back(rand()%20);
            cout << *(--colVec.end()) << " "; 
        }
        matrixA.push_back(colVec);
        colVec.erase(colVec.begin(), colVec.end());
        cout << endl;
    }
    cout << "Transposed Matrix" << endl;
    
    MatrixTransposeNaive(&matrixA);

    return 0;
}