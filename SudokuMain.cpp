// main.cpp
// create magic square via algorithm in Horstmann, Big C++, Chapter 6
#include <iostream>
#include <cassert>
//#include <vector>
#include "Vector.h"
#include <utility>
#include "Sudoku.h"
using namespace std;
int main()
{
    Vector<Vector<int> > mysudoku;
    read_sudoku(mysudoku);
    print_sudoku(mysudoku);
    if (test_sudoku(mysudoku))
    {
        cout << endl;
        cout << "YES, this is a solved 6x6 Sudoku :-)"
        << endl << endl;
    }
    else
    {
        cout << endl;
        cout << "TOO BAD ... this is not yet a 6x6 Sudoku solution :-("
        << endl << endl;
        cout << "Solving the rest..." << endl << endl;
        Vector<pair<int, int> > z_cells;
        z_cells = find_zero(mysudoku);
        cout << "These cells still need values: " << endl;
        for(int i = 0; i < z_cells.size(); ++i) {
            cout << "(" << z_cells[i].first << "," << z_cells[i].second << ")\t";
        }
        cout << endl << endl;
        if(fill_sudoku(mysudoku, z_cells) == 1)
        {
            cout << "Now solved :-)" << endl;
            print_sudoku(mysudoku);
        } else {
            cout << "Too bad ... could not find solution" << endl;
        }
      }
    return 0;
}
