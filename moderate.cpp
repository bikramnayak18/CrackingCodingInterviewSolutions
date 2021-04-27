#include<iostream>
#include<algorithm>
#include<stack>
#include<math.h>
#include<unordered_set>
#include<unordered_map>
#include<vector>
#include "rapidxml.hpp"

using namespace std;

int flip(int bit){
    return 1^ bit;
}

//return 1 if diff is +ve else 0
int getSign(int diff){
    int a = (diff>>31) & 1;
    return flip(a);
}

//a>0 b<0 a=1, sign(a)
//a<0 b>0 a=0, sign(a)
//a, b both have same sign sign(a-b)
int getMax(int a, int b){
    int asign = getSign(a);
    int bsign = getSign(b);
    int diffsign = getSign(a-b);
    int absign = asign^bsign;//if different will result in 1
    int csign = flip(absign);
    int k = absign*asign + csign*diffsign ;
    int q = flip(k);
    return a*k + b*q;
}

int findMinPair(int arr1[], int arr2[], int asize, int bsize){
    
    sort(arr1, arr1+asize);
    sort(arr2, arr2+asize);
    int min = INT_MAX;
    int i=0, j=0;
    
    while(i<asize && j<bsize){
        int diff = abs(arr1[i]-arr2[j]);
        if(diff ==0) return 0;
        if(min> diff)
            min = diff;
        if(arr1[i]>arr2[j])
            j++;
        if(arr1[i]<arr2[j])
            i++;
    }

    return min;
}

string convert(int number){
    string small[] = {"", "one","two", "three", "four","five","six","seven","eight","nine","ten","eleven","twelve"
                        ,"thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"};
    string med[] = {"","","twenty","thirty","fourty","fifty","sixty","seventy","eighty","ninety"} ;                       
   
    string output="";
    if(number>=100){
        int a = number/100;
        output += small[a] +" hundred ";
        number %= 100;
    }
    if(number>19){
        int a = number/10;
        output += med[a];
        number %= 10;
    }
    if(number>0){
        output += " " + small[number];
    }
    return output;
}

string convertNumberToString(int input){
    if(input==0) return "Zero";
    string large[] = {"","thousand","million","billion","trillion"};
    string output ="";
    stack<int> partials;
    while(input>0){
        partials.push(input%1000);
        input /= 1000;
    }

    while(!partials.empty()){
        int size = partials.size();
        int a = partials.top();
        partials.pop();
        output += convert(a)+" " + large[size-1]+" ";
    }
    return output;
}

class Person{
    int birth, death;
    Person(int birth, int death){
        this->birth = birth;
        this->death = death;
    }

    int maxLivingYear(Person persons[], int n, int min, int max){
        int count[max - min +2]= {0};
        for(int i=0;i<n;i++){
            int index = persons[i].birth - min;
            count[index]++;
            index = persons[i].death - min;
            count[index+1]--;
        }

        int maxAlive = -1;
        int currentlyAlive = 0;
        int maxYear=0;
        for(int i=min ;i<max+2;i++){
            currentlyAlive += count[i];
            if(maxAlive < currentlyAlive){
                maxYear = i+min;
                maxAlive = currentlyAlive;
            }
        }

        return maxYear;
    }
};


class Operation{
    int a, b;

    int negate(int a){
        a = INT_MAX - a + 1;
        a |= 1<<31;
        return a;
    }

    public: Operation(int a, int b){
        this->a = a;
        this->b = b;
    }
    
    int add(int a, int b){
        return a+b;
    }

    int subtract(int a, int b){
        return add(a, negate(b));
    }

    int multiple(int a, int b){
        if(a<b)
            return multiple(b, a);
        int result=0;
        for(int i=0;i<b;i++)            
            result += a;
        return result;
    }

    //assuming a, b are positive
    int divide(int a, int b){
        int sign;
        if( (a<0 && b<0) || (a>0 && b>0) )
            sign = 1;
        else
            sign = 0;
        a = abs(a);
        b = abs(b);
        int count =0;
        int product = 0;
        while(product+ b <=a)
        {
            product += b;
            count ++;
        }
        if(sign==0)
            count = negate(count);
        return count; 
    }
};

void getAllLengths(int k , int total, int shorter, int longer, unordered_set<int> &lengths, unordered_set<string> visited){
    if(k==0){
        lengths.insert(total);
        return;
    }
    string key = to_string(k)+" "+to_string(total);
    if(visited.find(key) != visited.end())
        return ;
    else
        visited.insert(key);
    getAllLengths(k-1,total+shorter, shorter, longer, lengths, visited);
    getAllLengths(k-1,total+longer, shorter, longer, lengths, visited);
}

unordered_set<int> allLengths(int shorter, int longer, int k){
    unordered_set<int> lengths;
    unordered_set<string> visited;
    getAllLengths(k, 0, shorter, longer, lengths, visited)   ;
    return lengths;
}

pair<int, int> findSubArray(int arr[], int length){
    int m =0;
    int n = length-1;
    
    //increasing subsequence
    while(m<length-2 && arr[m]<arr[m+1])
        m++;
    
    while(n>0 && arr[n]>arr[n-1])
        n--;

    int* minElement = std::min_element(arr+m+1, arr+n+1);
    while(arr[m]>*minElement)
        m--;
    int* maxElement = std::max_element(arr+m, arr+n);
    while(arr[n]<*maxElement)
        n++;
    pair<int, int> mn(m+1,n-1);
    return mn;
}

class point{
    public: int x, y;
    point(int x, int y){
        this->x = x;
        this->y = y;
    }
};

class Line{
    public: point p1, p2;
    float slope;
    float yIntercept;
    float xIntercept;
    bool infineSlope = false;
    
    Line(point pt1, point pt2):p1(pt1.x, pt1.y),p2(pt2.x,pt2.y){
        // this->p1.x = x1;
        // this->p1.y = y1;
        // this->p2.x = x2;
        // this->p2.y = y2;
        if(p2.x - p1.x == 0){
            infineSlope = true;
            xIntercept = p1.x;
            slope = -1;
        }else{            
            slope = (p2.y - p1.y)/(p2.x - p1.x);
            yIntercept = p1.y - slope * p1.x;
        }
    }
    float getSlope(){
        return slope;
    }

    float getYIntercept(){
        return yIntercept;
    }

    float getXIntercept(){
        return xIntercept;
    }
    bool isEquivalent(Line second){
        if(infineSlope && xIntercept == second.getXIntercept())
            return true;
        else if(slope == second.slope && yIntercept == second.getYIntercept())
            return true;
        else
            return false;            
    }
};

unordered_map<float, vector<Line>> getAllLine(point points[], int n){
    unordered_map<float, vector<Line>> totalLines;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            //Line newLine(points[i].x, points[i].y, points[j].x, points[j].y);
            Line newLine(points[i], points[j]);
            float key = newLine.getSlope();
            totalLines[key].push_back(newLine);
        }
    }
    return totalLines;
}

void bestLine(point points[], int n){
    unordered_map<float, vector<Line>> totalLines = getAllLine(points, n);
    int maxPointsByLine=0;
    for(auto itr = totalLines.begin();itr!=totalLines.end();itr++){
        int count = 1;
        vector<Line> lines = itr->second;
        Line firstLine = (*lines.begin());
        for(auto ptr = lines.begin()+1;ptr!=lines.end();ptr++){
            cout<<firstLine.isEquivalent(*ptr)<<endl;
        }
            //cout<<ptr->p1.x<<ptr->p1.y<<":"<<ptr->p2.x<<ptr->p2.y<<endl;
        if(maxPointsByLine < count )
            maxPointsByLine = count;
    }
}

int max(int a, int b){
	if(a>b) return a;
	return b;
}

int highestCommon(string str1, string str2){
	int m = str1.length();
	int n = str2.length();
	cout<<m<<":"<<n<<endl;
	int arr[m+1][n+1];
	for(int i=0;i<=m;i++){
		for(int j=0;j<=n;j++)
		{
			if(i==0 || j==0)
				arr[i][j]=0;
			else if(str1[i-1] == str2[j-1])
				arr[i][j] = arr[i-1][j-1] +1;
			else
				arr[i][j] = max(arr[i-1][j],arr[i][j-1]);
		}
	}
	return arr[m][n];
}

pair<int, int> findHits(string solution, string guess, int slots){
    int hits=0;
    unordered_map<char, int> unmatched;
    for(int i=0;i<slots;i++){
        if(solution[i] == guess[i]){
            hits++;
            guess[i] = 'x';
        }else{
            char key = solution[i];
            if(unmatched.find(key)!=unmatched.end())
                unmatched[key] = 1;
            else
                unmatched[key]++;
        }
    }

    int pseudo = 0;
    for(int i =0;i<slots;i++){
        char key = guess[i];
        if(unmatched.find(key)!=unmatched.end()){
            pseudo++;
            if(--unmatched[key] == 0)
                unmatched.erase(key);
        }
    }
    return make_pair(hits, pseudo);
}

int findPondLength(int *arr,int m, int n, int i, int j){
    if(i<0 || i>=m || j<0 || j>=n || arr[i*n+j]!=0)
        return 0;
    arr[i*n+j] = -1;

    int count = 1;
    for(int row=-1;row<=1;row++)
        for(int col=-1;col<=1;col++)
            count += findPondLength(arr,m, n, i+row, j+col);
    
    return count;
}

void findPond(int* arr, int m, int n){
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(arr[i*n+j]==0){
                cout<<findPondLength(arr,m,n, i, j)<<endl;
            }
        }
    }
}

int maxSumSubArray(int arr[], int m){
    int max = std::max(arr[0], -INT_MAX);
    int runningSum = std::max(0,arr[0]);
    for(int i=1;i<m;i++){
        max = std::max(runningSum+arr[i], max);
        runningSum = std::max(runningSum+arr[i], 0);
    }
    return max;
}

int countFreq(string pattern, char c){
    int count =0;
    for(int i=0;(i=pattern.find(c,i))!=std::string::npos;i++)
        count++;
    return count;
}

bool check(string value, int offset, int size, int offset2){
    for(int i=0;i<size;i++){
        if(value[offset+i] !=value[offset2+i])
            return false;
    }
    return true;
}

bool matchCurrentPattern(string value, string pattern, int altIndex, int mainLength, int altLength){
    char mainChar = pattern[0];
    char altChar = mainChar=='a'?'b':'a';
    int starting = 0;
    for(int i=0;i<pattern.length();i++){
        int offset = pattern[i] == mainChar?0:altIndex*mainLength;
        int size = pattern[i] == mainChar?mainLength:altLength;
        if(!check(value, offset, size, starting))
            return false;
        starting += size;
    }
    if(starting == value.length())
        return true;
    else
        return false;
}


string buildFromPattern( string pattern, string main, string alt){
    char mainChar = pattern[0];
    string output ="";
    int index = 0;
    for(int i=0;i<pattern.length();i++){
        if(pattern[i] == mainChar)
            output += main;
        else
            output += alt;
    }
    return output;
}

bool matchPattern(string value, string pattern){
    int totalLength = value.length();
    char mainChar = pattern[0];
    
    char altChar;
    if(mainChar=='a')
        altChar='b';
    else
        altChar='a';
    int mainCount = countFreq(pattern, mainChar);
    int altCount = countFreq(pattern, altChar);
    int firstAlt = pattern.find(altChar);
    int maxMain = totalLength/mainCount;
    for(int i=1;i<=maxMain;i++){
        int mainLength=i;
        int remainingLenth = totalLength - (mainLength*mainCount);
        if(altCount==0 || remainingLenth%altCount==0)
        {
            int altLength= altCount==0?0:remainingLenth/altCount;
            string mainString = value.substr(0,i);
            string altString = altCount==0?"": value.substr(mainLength*firstAlt, altLength);
            bool match = matchCurrentPattern(value, pattern,  firstAlt, mainLength, altLength);
            if(match){
                cout<<mainString<<" : "<<altString<<endl;
                return true;
            }
        }
    }
    return false;
}

class Square{
    int left, right, bottom, top, size;
    public:
    Square(int x1, int x2, int y1, int y2){
        left = x1;
        right = x2;
        bottom = y1;
        top = y2;
        size = x2 - x1;
    }

    int getSize(){
        return this->size;
    }

    point getMiddle(){
        return point( (this->left+this->right)/2,(this->top+this->bottom)/2);
    }
    
    point extend(point mid1, point mid2, int size){
        
        if(mid1.x == mid2.x)
        {
            return point(mid1.x, mid1.y + size/2);
        }

        double slope = (mid1.y-mid2.y)/(mid1.x-mid2.x);
        double x1, y1;
        if(abs(slope)==1){
            x1 = mid1.x + size/2.0;
            y1 = mid1.y + size/2.0;
        }
        else if(abs(slope)<1){
            x1 = mid1.x + size/2.0;
            y1 = slope *(x1 - mid1.x) + mid1.y;
        }
        else if(abs(slope)>1){
            y1 = mid1.y + size/2.0;
            x1 = (y1 - mid1.y)/slope + mid1.x;
        }

        return point(x1, y1);
    }

    void findLine(Square other){
        point p1 = extend(this->getMiddle(), other.getMiddle(), this->getSize());
        point p2 = extend(this->getMiddle(), other.getMiddle(), -this->getSize());
        point p3 = extend(other.getMiddle(), this->getMiddle(), other.getSize());
        point p4 = extend(other.getMiddle(), this->getMiddle(), -other.getSize());
        point start = p1;
        point end = p1;
        point p[] = {p2, p3, p4};
        for(int i =0;i<3;i++){
            if(start.x>p[i].x ||(start.x == p[i].x && start.y<p[i].y))
                start = p[i];
            else if(end.x<p[i].x || (end.x == p[i].x && end.y>p[i].y))                
                end = p[i];
        }

        cout<<"Start "<<start.x<<" : "<<start.y<<endl;
        cout<<"End "<<end.x<<" : "<<end.y<<endl;
    }

};

int* getTarget(int arr1[], int m, int arr2[], int n)
{
    int sum1=0, sum2=0;
    for(int i=0;i<m;i++)
        sum1 += arr1[i];
    for(int i=0;i<n;i++)
        sum2 += arr2[i];
    int target =(sum1-sum2)/2;        
    if(target%2!=0)return NULL;
    int* diff = &target;
    return diff;
}

unordered_set<int> getHashedValue(int arr[], int m){
    unordered_set<int> output;
    for(int i=0;i<m;i++)
        output.insert(arr[i]);

    return output;
}

void findPair(int arr1[], int m, int arr2[], int n){
    int target = *getTarget(arr1, m, arr2, n);
    //int *target = getTarget(arr1, m, arr2, n);
    unordered_set<int> hashedVal = getHashedValue(arr2, n);
   for(int i=0;i<m;i++)
   {
        int a = arr1[i];
        int b = a - target;
        //int b = a - *target;//this value was changing on every iteration
        if(hashedVal.find(b)!=hashedVal.end()){
            hashedVal.erase(b);
            cout<<a<<":"<<b<<endl;
        }
    }
}

void pairSum(int arr[], int m, int targetSum){
    unordered_map<int, int> dict;
    for(int i=0;i<m;i++){
        int a = arr[i];
        int rem = targetSum - a;
        if(dict.find(a) != dict.end())
            dict[a]++;
        else
            dict[a] = 1;            
        if(dict.find(rem)!=dict.end() && dict[rem]>0){
            cout<<a<<":"<<rem<<endl;
            dict[rem]--;
            dict[a]--;
        }
    }
}


int main(){
    int arr[] = {-2,-1,0,3,5,6,7,9,13,14};
    int size = sizeof(arr)/sizeof(arr[0]);
    pairSum(arr, size, 9);
    // int arr[] = {4,1,2,1,1,2};
    // int brr[] = {3,6,3,3};
    // findPair(arr,6,brr,4);
    // Square one(0,4,0,4);
    // Square two(-6,-10,-4,-8);
    // one.findLine(two);
    // string value ="catcatgocatcatgocat";
    // string pattern = "aabaaba";
    // cout<<"result : "<<matchPattern(value, pattern);
    // int hit ,pseudo;
    // tie(hit,  pseudo) = findHits("RRRG","GGGR",4);
    // cout<<hit<<":"<<pseudo;
    // int arr[][4]={{0,2,3,0},{0,1,0,1},{1,2,0,4},{0,1,0,1}};
    // int m=4;
    // int n =4;
    
    // findPond(&arr[0][0], m, n);
    // string virus;
	// std::getline(cin, virus);
	// string cases;
    // std::getline(cin, cases);
    // int n = stoi(cases);
	// while((n--)>0){
	// 	string person;
	// 	std::getline(cin, person);
	// 	int length = highestCommon(virus,person);
	// 	if(length == person.length())
	// 		cout<<"POSITIVE"<<endl;
	// 	else	
	// 		cout<<"NEGATIVE"<<endl;
	// }
    // point p1(1,1);
    // point p2(3,3);
    // point p3(0,5);
    // point p4(7,5);
    // point p5(3,0);
    // point p6(-1,0);
    // point points[] = {p1,p2,p3,p4,p5,p6};
    // bestLine(points, 6);
    // int arr[] = {1,2,4,7,10,11,8,12,14,16,16,18,19};
    // int length = sizeof(arr)/sizeof(arr[0]);
    // int m,  n;
    // tie(m, n) = findSubArray(arr, length);
    // cout<<m<<" "<<n<<endl;
    // int k=4, shorter = 1, longer = 2;
    // unordered_set<int> lengths =  allLengths(shorter, longer, k);
    // for(auto itr = lengths.begin();itr!=lengths.end();itr++)
    //     cout<<*itr<<" ";
    // int a=-36, b =-12;
    // Operation obj(a,b);
    // cout<<  obj.divide(a,b)<<endl;
    // int negative=12;
    // cout<< ((INT_MAX - negative + 1)|(1<<31));
    //  int n ;
    // cin>>n;
    // cout<<"value is "<<convertNumberToString(n);
    // int a[] = {1,3,15,11,2};
    // int b[] = {23,127,235,19,8};
    // int asize = sizeof(a)/sizeof(a[0]);
    // int bsize = sizeof(b)/sizeof(b[0]);
    // cout <<"min value is "<<findMinPair(a, b, asize, bsize);
    // int a = -INT_MAX + 2, b=6;
    // cout<<"enter value";
    // //cin>>a>>b;
    // cout<<"max value "<<getMax(a,b);
}