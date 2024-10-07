#include <iostream>
#include <iomanip>
#include <cassert>
//#include <vector>
#include "Vector.h"
#include <string>
#include <fstream>
#include <utility>
#include "Sudoku.h"
using namespace std;
// reads 6x6 sudoku puzzle;
void read_sudoku(Vector<Vector<int> >& sud)
{
ifstream inp;
Vector<int> nums;
string file;
cout << endl;
cout << "Which sudoku textfile? ";
cin >> file;
inp.open(file);
int next;
inp >> next;
while (!inp.fail())
{
nums.push_back(next);
inp >> next;
}
inp.close();
assert(nums.size() == 36);
int k = 0;
for (int i = 1; i <= 6; i++)
{
Vector<int> row;
for (int j = 1; j <= 6; j++)
{
row.push_back(nums[k]);
k++;
}
sud.push_back(row);
}
return;
}
void print_sudoku(const Vector<Vector<int> >& sud)
{
assert(sud.size() == 6 && sud[0].size() == 6);
cout << endl;
cout << "+------+-------+" << endl;
for (int i = 0; i < 6; i++)
{
cout << "|";
for (int j = 0; j < 6; j++)
if ((j + 1) % 3 == 0)
if (sud[i][j] == 0)
cout << left << setw(2) << "_" << "| ";
else
cout << left << setw(2) << sud[i][j] << "| ";
else
if (sud[i][j] == 0)
cout << left << setw(2) << "_";
else
cout << left << setw(2) << sud[i][j];
if ((i + 1) % 2 == 0)
cout << endl
<< "+------+-------+" << endl;
else
cout << endl;
}
cout << endl;
return;
}
bool test_sudoku(const Vector<Vector<int> >& sud)
{
assert(sud.size() == 6  && sud[0].size() == 6);
for (int i = 0; i < 6; i++)
if (!row_1to6(i, sud))
return false;
for (int i = 0; i < 6; i++)
if (!col_1to6(i, sud))
return false;
for (int i = 0; i < 6; i++)
if (!rect_1to6(i, sud))
return false;
return true;
}
bool row_1to6(int i, const Vector<Vector<int> >& sud)
{
for (int k = 1; k <= 6; k++)
{
bool found = false;
for (int j = 0; j < 6; j++)
{
if (k == sud[i][j])
{
found = true;
break;
}
}
if (!found)
return false;// k not in row i
}
// pass: each k in{ 1..6 } was found in row i;
return true;
}
bool col_1to6(int j, const Vector<Vector<int> >& sud)
{
for (int k = 1; k <= 6; k++)
{
bool found = false;
for (int i = 0; i < 6; i++)
{
if (k == sud[i][j])
{
found = true;
break;
}
}
if (!found)
return false;// k not in col j
}
// pass: each k in{ 1..6 } was found in col j;
return true;
}
bool rect_1to6(int n, const Vector<Vector<int> >& sud)
{
Vector<int> rownos;
Vector<int> colnos;
rec_rows_cols(n, rownos, colnos);
for (int k = 1; k <= 6; k++)
{
bool found = false;
for (int i = 0; i < 2; i++)
{
int r = rownos[i];
for (int j = 0; j < 3; j++)
{
int c = colnos[j];
if (k == sud[r][c])
{
found = true;
break;
}
}
if (found)
break;
}
if (!found)
return false;
}
return true;
}
void rec_rows_cols(int n, Vector<int>& rownos, Vector<int>& colnos)
{
assert(0 <= n && n < 6);
///NEW LINE
Vector<int> rows01(2);
rows01[0] = 0;
rows01[1] = 1;

  
//Vector<int> rows23{ 2,3 };

Vector<int> rows23(2);
rows23[0] = 2;
rows23[1] = 3;
  
//Vector<int> rows45{ 4,5 };

Vector<int> rows45(2);
rows45[0] = 4;
rows45[1] = 5;
  
//Vector<int> cols012{ 0,1,2 };

Vector<int> cols012(3);
cols012[0] = 0;
cols012[1] = 1;
cols012[2] = 2;
  
//Vector<int> cols345{ 3,4,5 };
Vector<int> cols345(3);
cols345[0] = 3;
cols345[1] = 4;
cols345[2] = 5;
if (n == 0)
{
rownos = rows01;
colnos = cols012;
}
else if (n == 1)
{
rownos = rows01;
colnos = cols345;
}
else if (n == 2)
{
rownos = rows23;
colnos = cols012;
}
else if (n == 3)
{
rownos = rows23;
colnos = cols345;
}
else if (n == 4)
{
rownos = rows45;
colnos = cols012;
}
else
{
rownos = rows45;
colnos = cols345;
}
return;
}
Vector<pair<int, int>>find_zero(const Vector<Vector<int> >& sud) {
    Vector<pair<int, int> > z_cells;
    pair<int, int> coord;
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 6; j++)
            if(sud[i][j] == 0) {
                coord.first = i;
                coord.second = j;
                z_cells.push_back(coord);
            }
    }
    return z_cells;
}
int fill_sudoku(Vector<Vector<int> >& sud, const Vector<pair<int, int> >& z_cells) 
{
    for(int i = 1; i <= 6; i++) {
        sud[z_cells[0].first][z_cells[0].second] = i;
        for(int j = 1; j <= 6; j++)
        {
            sud[z_cells[1].first][z_cells[1].second] = j;
            for(int k = 1; k <= 6; k++) {
              sud[z_cells[2].first][z_cells[2].second] = k;
              if(test_sudoku(sud)) {
                return 1;
              }
            }
        }
    }
  return 0;
  }
