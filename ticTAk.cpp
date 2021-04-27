#include<iostream>

using namespace std;

class point{
    int row;
    int col;
    public: 
        point(int row, int col){
            this->row = row;
            this->col = col;
        }

    bool inBound(int row, int col, int size){
        return row>=0 && row<size && col>=0 && col<size;
    }

    bool travelRow(int** board, int row,int size){
        int start = board[row][0];
        for(int i=0;i<size;i++){
            if(start != board[row][i])
                return false;
        }
        return true;
    }
};

int main(){
  
    cout<<"hello";
}