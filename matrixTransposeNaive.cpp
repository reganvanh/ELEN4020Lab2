#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
#include <vector>
#include <iostream>

using namespace std ;

void swop(int* num1, int* num2)
{
    *num1 = *num1 + *num2;
    *num2 = *num1 - *num2;
    *num1 = *num1 - *num2; 

}

void MatrixTransposeNaive( vector<vector<int>>* tempMatrix )
{
    auto col = 0;
    auto N = (tempMatrix->size ());
    #pragma omp parellel for shared(tempMatrix, row, col)
    {      
        for(auto row = 1; row < N ; ++row)
        {
            col = 0;
            while(col < row)
            {
                swop(&(*tempMatrix)[row][col], &(*tempMatrix)[col][row]);
                ++col;
            }
        }
    }

}