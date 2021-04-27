#include <bits/stdc++.h>
#include<unordered_map>
#include<unordered_set>
using namespace std;

vector<string> split_string(string);
//1,1,1
bool attack(int n, int r, int c, pair<int,int> defense, int k){
    if(r<=0 || r>n )
        return false;
    if(c<=0 || c>n )
        return false;
    if(k==0)
        return true;
    else{
         if(defense.first == r && defense.second == c)   
            return false;
    }
    
    return true;
}

// Complete the queensAttack function below.
int queensAttack(int n, int k, int r_q, int c_q, vector<vector<int>> obstacles) {
    pair<int, int> left(r_q,0);
    pair<int, int> right(r_q,n+1);
    pair<int, int> top(n+1, c_q);
    pair<int, int> bottom(0, c_q);
    int rowHeight = n - r_q;
    int colHeight = c_q - 1;
    int diagonal = rowHeight<colHeight?rowHeight+1:colHeight+1;
    pair<int, int> topLeft(r_q + diagonal, c_q - diagonal);
    rowHeight = n - r_q;
    colHeight = n - c_q;
    diagonal = rowHeight<colHeight?rowHeight+1:colHeight+1;
    pair<int, int> topRight(r_q + diagonal, c_q + diagonal);
    rowHeight = r_q - 1;
    colHeight = c_q - 1;
    diagonal = rowHeight<colHeight?rowHeight+1:colHeight+1;
    pair<int, int> bottomLeft(r_q - diagonal, c_q - diagonal);
    rowHeight = r_q - 1;
    colHeight = n - c_q;
    diagonal = rowHeight<colHeight?rowHeight+1:colHeight+1;
    pair<int, int> bottomRight(r_q - diagonal,c_q + diagonal);
    
    if(k>0){
        for(int i=0;i<k;i++){
            if(obstacles[i][0] == r_q && obstacles[i][1]<c_q)//row data .. left
            {
                 if(left.second<obstacles[i][1])   
                 {
                     left.first = obstacles[i][0];
                     left.second = obstacles[i][1];
                 }
            }else if(obstacles[i][0] == r_q && obstacles[i][1]>c_q)//row data .. right
            {
                 if(right.second>obstacles[i][1])   
                 {
                     right.first = obstacles[i][0];
                     right.second = obstacles[i][1];
                 }
            }else if(obstacles[i][1] == c_q && obstacles[i][0]>r_q)//col data .. top
            {
                 if(top.first>obstacles[i][0])   
                 {
                     top.first = obstacles[i][0];
                     top.second = obstacles[i][1];
                 }
            }
            else if(obstacles[i][1] == c_q && obstacles[i][0]<r_q)//col data .. bottom
            {
                 if(bottom.first<obstacles[i][0])   
                 {
                     bottom.first = obstacles[i][0];
                     bottom.second = obstacles[i][1];
                 }
            }else{
                int dy = obstacles[i][0] - r_q;
                int dx = obstacles[i][1] - c_q;
                if(abs(dy) == abs(dx) && dy<0)//bottom
                {
                    if(dx>0 && obstacles[i][0] > bottomRight.first){//right
                        bottomRight.first = obstacles[i][0];
                        bottomRight.second = obstacles[i][1];
                    }else if(dx<0 && obstacles[i][0] > bottomLeft.first){
                        int x = obstacles[i][0];
                        int y = obstacles[i][1];
                        bottomLeft.first = obstacles[i][0];
                        bottomLeft.second = obstacles[i][1];
                    }
                }else if(abs(dy) == abs(dx) && dy>0){//top
                    if(dx>0 && obstacles[i][0] < topRight.first){//right
                        topRight.first = obstacles[i][0];
                        topRight.second = obstacles[i][1];
                    }else if(dx<0 && obstacles[i][0] < topLeft.first){//left
                        topLeft.first = obstacles[i][0];
                        topLeft.second = obstacles[i][1];
                    }
                }
            }
        }
    }
    int output=0;
    int leftDistance =  c_q - left.second - 1;
    int rightDistance =  right.second - c_q - 1;
    int topDistance = top.first - r_q - 1;
    int bottomDistance = r_q - bottom.first - 1;
    int topLeftDistance = n == r_q || 1 == c_q?0: (topLeft.first - r_q - 1);
    int topRightDistance = n == r_q || n == c_q?0:topRight.first - r_q - 1;
    int bottomLeftDistance = 1 == r_q || 1 == c_q ?0: r_q - bottomLeft.first - 1;
    int bottomRightDistance = 1 == r_q || n == c_q?0: r_q - bottomRight.first - 1; 
    output = leftDistance + rightDistance + topDistance + bottomDistance 
    + topLeftDistance + topRightDistance + bottomLeftDistance + bottomRightDistance ;
    //  int i = r_q;
    //  int j = c_q;
    //  int output = 0 ;
    //  while(attack(n, i, --j, map, k)){
    //      output++;
    //  }
    //  i = r_q;
    //  j = c_q;
    //  while(attack(n, i, ++j, map, k)){
    //      output++;
    //  }
    //  i = r_q;
    //  j = c_q;
    //  while(attack(n, --i, j, map, k)){
    //      output++;
    //  }
    //  i = r_q;
    //  j = c_q;
    //  while(attack(n, ++i, j, map, k)){
    //      output++;
    //  }
    //  i = r_q;
    //  j = c_q;
    //  while(attack(n, --i, --j, map, k)){
    //      output++;
    //  }
    //  i = r_q;
    //  j = c_q;
    //  while(attack(n, ++i, ++j, map, k)){
    //      output++;
    //  }
    //  i = r_q;
    //  j = c_q;
    //  while(attack(n, ++i, --j, map, k)){
    //      output++;
    //  }
    //  i = r_q;
    //  j = c_q;
    //  while(attack(n, --i, ++j, map, k)){
    //      output++;
    //  }
    cout<<output<<endl;
     return output;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nk_temp;
    getline(cin, nk_temp);

    vector<string> nk = split_string(nk_temp);

    int n = stoi(nk[0]);

    int k = stoi(nk[1]);

    string r_qC_q_temp;
    getline(cin, r_qC_q_temp);

    vector<string> r_qC_q = split_string(r_qC_q_temp);

    int r_q = stoi(r_qC_q[0]);

    int c_q = stoi(r_qC_q[1]);

    vector<vector<int>> obstacles(k);
    for (int i = 0; i < k; i++) {
        obstacles[i].resize(2);

        for (int j = 0; j < 2; j++) {
            cin >> obstacles[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int result = queensAttack(n, k, r_q, c_q, obstacles);

    fout << result << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
