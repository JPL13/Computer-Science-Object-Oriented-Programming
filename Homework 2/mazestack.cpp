#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows,  int nCols, int sr, int sc, int er, int ec)
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
{
	
    
    stack<Coord> coordStack;     // declare a stack of Coords
    coordStack.push(Coord(sr,sc));  //Push the starting coordinate (sr,sc) onto the coordinate stack
    maze[sr][sc]='-'; //update maze[sr][sc] to indicate that the algorithm has encountered it
    
    while(!coordStack.empty())
    {
        Coord current = coordStack.top();
        int r=current.r();
        int c=current.c();
        coordStack.pop();
        cerr<<r<<" "<<c<<endl;
        
        if(r==er&&c==ec)  //solved the maze, return true
            return true;
        
        //if can move East
        if(maze[r][c+1]=='.')
        {   coordStack.push(Coord(r,c+1)); // push the coordinate (r,c+1) onto the stack
            maze[r][c+1]='-';//update maze to indicate the algorithm has encountered it
        }
       
        //if can move South
        if(maze[r+1][c]=='.')
        {   coordStack.push(Coord(r+1,c)); // push the coordinate onto the stack
            maze[r+1][c]='-';//update maze to indicate the algorithm has encountered it
        }
        //if can move WEST
        if(maze[r][c-1]=='.')
        {   coordStack.push(Coord(r,c-1)); // push the coordinate onto the stack
            maze[r][c-1]='-';//update maze to indicate the algorithm has encountered it
        }
        //if can move NORTH
        if(maze[r-1][c]=='.')
        {   coordStack.push(Coord(r-1,c)); // push the coordinate onto the stack
            maze[r-1][c]='-';//update maze to indicate the algorithm has encountered it
        }
       
    }
    
    return false;
}

