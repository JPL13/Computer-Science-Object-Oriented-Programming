#include <iostream>
#include <queue>
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

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
{
    
    
    queue<Coord> coordQueue;     // declare a queue of Coords
    coordQueue.push(Coord(sr,sc));  //Push the starting coordinate (sr,sc) onto the coordinate queue
    maze[sr][sc]='-'; //update maze[sr][sc] to indicate that the algorithm has encountered it
    
    while(!coordQueue.empty())
    {
        Coord current = coordQueue.front();
        int r=current.r();
        int c=current.c();
        coordQueue.pop();
        cerr<<r<<" "<<c<<endl;
        
        if(r==er&&c==ec)  //solved the maze, return true
            return true;
        
        //if can move East
        if(maze[r][c+1]=='.')
        {   coordQueue.push(Coord(r,c+1)); // push the coordinate (r,c+1) onto the queue
            maze[r][c+1]='-';//update maze to indicate the algorithm has encountered it
        }
       
        //if can move South
        if(maze[r+1][c]=='.')
        {   coordQueue.push(Coord(r+1,c)); // push the coordinate onto the queue
            maze[r+1][c]='-';//update maze to indicate the algorithm has encountered it
        }
        //if can move WEST
        if(maze[r][c-1]=='.')
        {   coordQueue.push(Coord(r,c-1)); // push the coordinate onto the queue
            maze[r][c-1]='-';//update maze to indicate the algorithm has encountered it
        }
        //if can move NORTH
        if(maze[r-1][c]=='.')
        {   coordQueue.push(Coord(r-1,c)); // push the coordinate onto the queue
            maze[r-1][c]='-';//update maze to indicate the algorithm has encountered it
        }
       
    }
    
    return false;
}


