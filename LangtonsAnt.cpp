#include<iostream>
#include<vector>
using namespace std;

class Position{
    public: 
    int row, column;
    Position(int x, int y){
        this->row = x;
        this->column = y;
    }
};

class Ant{
    public: 
    enum Orientation{
        right, left, up, down
    };
    Orientation orientation;
    Position position;
    Ant(int x, int y):position(x,y){
        orientation = right;
    }

    Orientation turn(bool clockWise){
        if (orientation == left)
            return clockWise?up:down;
        else if(orientation == right)
            return clockWise?down:up;
        else if(orientation == up )
            return clockWise?right:left;
        else 
            return clockWise?left:right;
    }

    void move(){
        if(orientation == left)
            position.column--;
        else if(orientation == right)
            position.column++;
        else if(orientation == up)
            position.row--;
        else
            position.row++;
    }

    void adjustPosition(int shiftRow, int shiftCol){
        position.column += shiftCol;
        position.row += shiftRow;
    }
};

class Grid{
    public: 
    vector<vector<bool>> grid;
    Ant ant;

    Grid():ant(0,0){
        grid.resize(1);
        grid[0].resize(1);
        grid[0][0] = false;
    }

    void flip(Position position){
        int row = position.row;
        int col = position.column;
        grid[row][col] = grid[row][col]?false:true;
    }

    void copyToNewGrid(vector<vector<bool>> &newGrid, vector<vector<bool>> oldGrid, int rowShift, int colShift){
        int row = oldGrid.size();
        int col = oldGrid[0].size();
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                newGrid[i+rowShift][j+colShift] = oldGrid[i][l];
            }
        }
    }

    void ensureFit(Position position )
    {
        int rowShift=0,colShift=0;
        int m=grid.size();
        int n=grid[0].size();
        if(position.row<0 ){
            rowShift = m;
            m +=  m;
        }else if(position.row>=m){
            m += m;
        }
        if(position.column<0){
            colShift = n;
            n += n;
        }else if(position.column>=n){
            n += n;
        }

        if(m != grid.size() || n!=grid[0].size()){
            vector<vector<bool>> newGrid;
            newGrid.resize(m);
            for(auto i:m)
                newGrid[i].resize(n);
            copyToNewGrid(newGrid, grid, rowShift,colShift) ;
            ant.adjustPosition(rowShift, colShift);
            grid = newGrid;
        }
    }

    void move(){
        ant.turn(grid[ant.position.row][ant.position.column]);
        flip(ant.position);
        ant.move();
    }
};

int main(){
    cout<<"hello world";
}