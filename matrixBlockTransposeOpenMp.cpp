#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
#include <vector>
#include <ctime>
#include <iostream>

using namespace std;

void swopBlock(vector<vector<int>>* tempMatrix, int tempRow, int tempCol)
{
    swop(&(*tempMatrix)[tempRow][tempCol], &(*tempMatrix)[tempCol][tempRow]);
    swop(&( *tempMatrix )[ tempRow ][ tempCol + 1 ], &( *tempMatrix )[ tempCol ][ tempRow + 1 ]);
    swop(&( *tempMatrix )[ tempRow+1 ][ tempCol ], &( *tempMatrix )[ tempCol + 1 ][ tempRow ]);
    swop(&( *tempMatrix )[ tempRow+1 ][ tempCol+1 ], &( *tempMatrix )[ tempCol+1 ][ tempRow+1 ]);
}

void blockTransposeOpenMP( vector<vector<int>>* theMatrix) 
{
    // #pragma parellel for shared(matrixA, colVec, row, col)
    // {
        for (auto row = 0; row < theMatrix->size (); row + 2)
        {
            for ( auto col = 0; col < theMatrix->size (); col + 2 )
            {
                if (row != col)
                {
                    swop(&((*theMatrix)[row][col]), &((*theMatrix)[row+1][col-1]));
                }
            }
        }
    // }
    // #pragma parellel for shared(matrixA, colVec, row, col)
    // {
        for (auto row = 0; row < theMatrix->size (); row + 2)
        {
            for ( auto col = 0; col < theMatrix->size () ; col + 2 )
            {
                if (row != col)
                {
                    swopBlock(theMatrix, row, col);
                }
            }
        }
    // }

    int N = theMatrix->size();

    for(auto row = 0; row < N ; ++row)
    {
        int col = 0;
        while(col < N)
        {
             cout << (*theMatrix)[row][col] << " ";
            ++col;
        }
        cout << endl;
    }



    


}