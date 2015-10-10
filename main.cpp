#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
using namespace std ;

#include "Sudoku.hpp"

int main( int argc, char** argv ) {
    srand(time(NULL));
    Sudoku sudoku(9);
    sudoku.print_sudoku() ;
    return 0 ;
} // main


