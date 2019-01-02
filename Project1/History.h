//
//  History.hpp
//  Gas
//
//  Created by Juan Piao on 1/10/18.
//  Copyright © 2018 Piao. All rights reserved.
//

#ifndef History_hpp
#define History_hpp
#include "globals.h"
class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    int   m_rows;
    int   m_cols;
    int   m_convert[MAXROWS][MAXCOLS];

};

#endif /* History_hpp */
