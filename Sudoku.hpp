#ifndef SUDOKU_HPP_INCLUDED
#define SUDOKU_HPP_INCLUDED

class Sudoku {
    protected:
        int build_times ;
        int sudoku_size ;
        int cell_size ;
        int** sudoku ;

        /*   check if numbers were used in same cell
         */
        void check_cell( int x, int y, bool* used ) {
            int x_start = ( x / cell_size ) * cell_size ; // perform floor division then production.
            int y_start = ( y / cell_size ) * cell_size ;
            for ( int i = x_start ; i < x_start + cell_size ; ++i )
                for ( int j = y_start; j < y_start + cell_size ; ++j )
                    if ( sudoku[i][j] ) used[ sudoku[i][j] ] = true ;
        } // check_cell()

        /*  check if numbers were used in same column and same row
         */
        void check_cross( int x, int y, bool* used ) {
            for ( int i = 1 ; i < sudoku_size+1 ; ++i ) {
                if ( sudoku[x][i-1] )
                    used[ sudoku[x][i-1] ] = true ;
                if ( sudoku[i-1][y] )
                    used[ sudoku[i-1][y] ] = true ;
            } // for() 1 ~ sudoku_size
        } // check_cross()

        /*  generate and return a random number witch must be valid
         */
        int random_unused( bool* used ) {
            vector<int> v ;
            for ( int i = 1 ; i < sudoku_size+1 ; ++i )
                if ( !used[i] ) v.push_back( i ) ;
            return v.size() ? v[ rand() % v.size() ] : -1 ;
            // if there is no such number meets the rule, return -1.
        } // random_unused()

        /*  insert a valid number at specified (x, y)
         */
        bool insert_number( int x, int y ) {
            bool used[sudoku_size + 1] ;
            for ( int i = 0 ; i < sudoku_size+1 ; ++i ) used[i] = false ;
            check_cross( x, y, used ) ;
            check_cell( x, y, used ) ;
            sudoku[x][y] = random_unused( used ) ;
            return sudoku[x][y] != -1 ;
        } // insert_number()

        /*  main method to build the sudoku
         */
        bool build_sudoku(void) {
            for ( int x = 0 ; x < sudoku_size ; ++x )
                for ( int y = 0 ; y < sudoku_size ; ++y )
                    if ( !insert_number( x, y ) ) return false; // fail to insert a number.
            return true ;
        } // build_sudoku()

        /*  clear or initialize the sudoku
         */
        void clear(void) {
            for ( int x = 0 ; x < sudoku_size ; ++x )
                for ( int y = 0 ; y < sudoku_size ; ++y )
                    sudoku[x][y] = 0 ;
        } // clear()
    // end private
    public:
        /*  the constructor of Sudoku class
         */
        Sudoku( int size = 4 ) {
            if ( size != 9 ) size = 4 ; // only 4*4 or 9*9 sudoku is allowed
            sudoku_size = size ;
            cell_size = size % 3 ? 2 : 3 ;
            sudoku = new int*[ size ] ; // sudoku is a pointer of integer pointer (int**)
            for ( int i = 0 ; i < size ; ++i )
                sudoku[i] = new int[ size ] ;
            int times = 0 ;
            do {
                ++times ;
                clear() ;
            } while( !build_sudoku() ) ; // rebuild until success
            build_times = times ;
        } // constructor of Sudoku class

        /*  get how many times retried to build this sudoku
         */
        int times(void) {
            return build_times ;
        }

        /*   print out whole sudoku
         */
        void print_sudoku(void) {
            for ( int x = 0 ; x < sudoku_size ; ++x ) {
                for ( int y = 0 ; y < sudoku_size ; ++y )
                    cout << sudoku[x][y] << " " ;
                cout << endl ;
            } // for()
        } // print_sudoku()

        /*   print out the cell witch specified (x, y) located.
         */
        void print_cell( int x, int y ) {
            int x_start = ( x / cell_size ) * cell_size ; // perform floor division then production.
            int y_start = ( y / cell_size ) * cell_size ;
            for ( int i = x_start ; i < x_start + cell_size ; ++i ) {
                for ( int j = y_start; j < y_start + cell_size ; ++j )
                    cout << sudoku[i][j] << " " ;
                cout << endl ;
            } // for()
        } // print_cell()
    // end public
}; // class Sudoku

#endif // SUDOKU_HPP_INCLUDED
