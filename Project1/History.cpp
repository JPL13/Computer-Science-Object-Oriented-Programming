//
//  History.cpp
//  Gas
//
//  Created by Juan Piao on 1/10/18.
//  Copyright © 2018 Piao. All rights reserved.
//
#include <iostream>
#include "History.h"
#include "globals.h"
using namespace std;

History::History(int nRows, int nCols):m_rows(nRows),m_cols(nCols)
{
    int r, c;
    for (r = 0; r < m_rows; r++)
        for (c = 0; c < m_cols; c++)
            m_convert[r][c]=0;
    
}
bool History::record(int r, int c)
{
    if (r <= 0  ||  c <= 0  ||  r > m_rows  ||  c > m_cols)
        return false;
    else
        m_convert[r-1][c-1]++;
         return true;
}
void History::display() const
{
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    
    
    for (r = 0; r < m_rows; r++)
    {  for (c = 0; c < m_cols; c++)
        {
            int gridINT = m_convert[r][c];
            
            if (gridINT == 0)
            {
                grid[r][c] = '.';
            }
            else if (gridINT <26)
            {
                grid[r][c] = gridINT+64; // Change int type into char type by considering ASCII
            }
            else
            {
                grid[r][c] = 'Z';
            }
           
        }
    }
 
    // Draw the grid
    clearScreen();
    for (r = 0; r < m_rows; r++)
    {
        for (c = 0; c < m_cols; c++)
            cout << grid[r][c];
        cout << endl;
    }
  
     cout << endl;
}
