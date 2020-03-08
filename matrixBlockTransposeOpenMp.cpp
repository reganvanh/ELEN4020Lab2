#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
#include <vector>
#include <ctime>
#include <iostream>

using namespace std;

void swopBlock(vector<vector<int>>* tempMatrix, int tempRow, int tempCol)
{
    swop(&(( *tempMatrix )[ tempRow ][ tempCol ]), &(( *tempMatrix )[ tempCol ][ tempRow ]));
    swop(&(( *tempMatrix )[ tempRow ][ tempCol + 1 ]), &(( *tempMatrix )[ tempCol ][ tempRow + 1 ]));
    swop(&(( *tempMatrix )[ tempRow+1 ][ tempCol ]), &(( *tempMatrix )[ tempCol + 1 ][ tempRow ]));
    swop(&(( *tempMatrix )[ tempRow+1 ][ tempCol+1 ]), &(( *tempMatrix )[ tempCol+1 ][ tempRow+1 ]));
}

void blockTransposeOpenMP( vector<vector<int>>* theMatrix) 
{
    int mSize = theMatrix->size ();


    #pragma omp parellel for shared (theMatrix, row, col)
    {
        for (auto row = 0; row < mSize -1; ++(++row))
        {
            for ( auto col = 1; col < mSize ; ++(++col))
            {
                if (row != col)
                {
                    swop(&((*theMatrix)[row][col]), &((*theMatrix)[row+1][col-1]));
                }
            }
        }
    }


    int temp = 0;
    #pragma omp parellel for shared (theMatrix, row, col)
    {
        for (auto row = 0; row < mSize ; ++(++row))
        {
            for ( auto col = row ; col < mSize ; ++(++col))
            {
                if (row != col)
                {
                    swopBlock(theMatrix, row, col);
                }
            }
        }
    }

}