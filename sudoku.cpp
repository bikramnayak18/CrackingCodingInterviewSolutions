#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;
    
    const int size = 9;    
    bool valid(unordered_set<char>& row, unordered_set<char>& col, unordered_set<char>& grid, char c){
        if(row.find(c) == row.end() && col.find(c) == col.end() && grid.find(c)==grid.end())
            return true;
        else 
            return false;
    }
        
    bool merged(unordered_set<char>& row, unordered_set<char>& col, unordered_set<char>& grid, unordered_set<char>& remaining){
        unordered_set<char> merge;
        for(auto itr=row.begin();itr!=row.end();itr++){
                merge.insert(*itr);
        }
        
        for(auto itr=col.begin();itr!=col.end();itr++){
                merge.insert(*itr);
        }
        
        for(auto itr=grid.begin();itr!=grid.end();itr++){
                merge.insert(*itr);
        }
        
        
        for(int i=49;i<=57;i++){           
            if(merge.find(i)==merge.end()){
                remaining.insert(i);
            }
        }
        //cout<<"coutn"<<remaining.size()<<endl;
        return remaining.size() >0;
    }    
    
    void getRow(const vector<vector<char>>& board, int i, unordered_set<char>& row){
        for(int col=0;col<size;col++)
            if(board[i][col]!='.')
                row.insert(board[i][col]);
    }
        
    void getCol(const vector<vector<char>>& board, int i, unordered_set<char>& col){
        for(int row=0 ;row<size;row++)
            if(board[row][i]!='.')
                col.insert(board[row][i]);
    }        
        
    void getGrid(const vector<vector<char>>& board, int i,int j, unordered_set<char>& grid){
        //cout<<"grid"<<i<<":"<<j<<endl;
        int rowEnd = (i/3)*3 + 3,
        colEnd = (j/3)*3 + 3;
        for(int row = (i/3)*3;row<rowEnd;row++){
            for(int col = (j/3)*3;col<colEnd;col++){
                //cout<<row<<":"<<col<<":"<<rowEnd<<":"<<colEnd<<endl;
                if(row!=i && col!=j && board[row][col]!='.'){
                    //cout<<"griding "<<board[row][col]<<endl;
                    grid.insert(board[row][col]);
                }
            }
        }
    }
        
   bool fillSudoku(vector<vector<char>>& board, int i, int j){
        if(i<size && j<size && board[i][j]=='.'){
            unordered_set<char> row;
            unordered_set<char> col;
            unordered_set<char> grid;
            unordered_set<char> remaining;
            //cout<<i<<":"<<j<<endl;
            getRow(board, i, row);
            getCol(board, j, col);
            getGrid(board, i,j, grid);
            for(int val=49;val<=57;val++)
            {
                if(valid(row, col, grid, val)){
                    board[i][j] = val;
                    bool placed = fillSudoku(board, i, j+1);
                    if(!placed)
                        board[i][j] ='.';
                    else
                        return placed;
                }
            }    
        }else if(i<size && j<size){
            return fillSudoku(board, i, j+1);   
        }        
        else if(i<size){
            j=0;
            i++;
            return fillSudoku(board, i, j);
        }
        else if(i==size)
            return true;
        return false;
    }
       
void solveSudoku(vector<vector<char>>& board) {
        fillSudoku(board,0,0);
    }
int main(){
    vector<vector<char>> board = 
    {{'5','3','.','.','7','.','.','.','.'},
    {'6','.','.','1','9','5','.','.','.'},
    {'.','9','8','.','.','.','.','6','.'},
    {'8','.','.','.','6','.','.','.','3'},
    {'4','.','.','8','.','3','.','.','1'},
    {'7','.','.','.','2','.','.','.','6'},
    {'.','6','.','.','.','.','2','8','.'},
    {'.','.','.','4','1','9','.','.','5'},
    {'.','.','.','.','8','.','.','7','9'}};
    solveSudoku(board);
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
}