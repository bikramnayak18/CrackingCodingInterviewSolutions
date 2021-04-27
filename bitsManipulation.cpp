#include<iostream>
#include<bitset>
#include<math.h>
using namespace std;

void printBitSet(int x){
    cout<< bitset<32>(x)<<endl;
}

void printBinary(unsigned int x){
    for(int i=31;i>=0;i--){
        cout<<(x>>i & 1);
    }
    cout<<endl;
}

void mergeBits(int m, int n, int i, int j){
    int allOnes = ~0;
    int left = allOnes<<(j+1);
    int right = (1<<i) - 1;
    int mask = left | right;
    int mCleared = m & mask;
    int nshift = n<<i;
    int merge = mCleared | nshift;
    printBitSet(m);
    printBitSet(n);
    printBitSet(merge);
}

void longest1(int n){
    if(~n==0){  
        cout<<"max length "<<32<<endl;
        return ;
    }
    int previous=0;
    int current = 0;
    int sum=0;
    int max = -1;
    int i=32;
    while(i-->0){
        if((n&1)==0){
            sum = previous + current;
            previous = current;
            current = 0;
            max = std::max(max, sum+1);
        }else{
            current++;
        }        
        n >>= 1;
    }
    cout<<"max length "<<max<<endl;
}

int nextSmallest(int n){
    int c1=0,c0=0, p=0;
    int temp = n;
    while(temp>0){
        if((temp&1)==0) c0++;
        else break;
        temp>>=1;
    }
    while(temp>0){
        if((temp&1)==1) c1++;
        else break;
        temp >>=1;
    }
    if((c1 + c0) ==31 || (c1+c0)==0) return -1;
    p = c0+c1;
    cout<< p;
    int mask = 1<<p;
    cout<<"input : ";printBinary(n);
    n |= mask;
    //printBinary(n);
    mask = ~0 - 1<<p - 1;
    n &= mask;
    //printBinary(n);
    mask = (1<<(c1-1)) - 1;
    n |= mask;
    cout<<"output : ";;;printBinary(n);
    return n;

}

int previousLargest(int n){
    int c1=0;
    int c0=0;
    int p=0;
    int temp=n;
    while(temp>0){
        if((temp&1)==0)
            break;
        c1++;
        temp >>= 1;
    }
    while(temp>0){
        if((temp&1)==1)
            break;
        c0++;
        temp >>= 1;
    }
     if((c1 + c0) ==31 || (c1+c0)==0) return -1;
     
    p = c1+c0;
    printBinary(n);
    int mask = (~0) ^ (1<<p);
    printBinary(mask);
    n &= mask;
    printBinary(n);
    mask = (1<<p) - 1;
    printBinary(mask);
    n |= mask;
    mask = (~0)<<(c0-1);
    n &= mask;
    cout<<"output";
    printBinary(n);
    return n;
}

int previousLargest2(int n){
    int c1=0;
    int c0=0;
    int p=0;
    int temp=n;
    while(temp>0){
        if((temp&1)==0)
            break;
        c1++;
        temp >>= 1;
    }
    while(temp>0){
        if((temp&1)==1)
            break;
        c0++;
        temp >>= 1;
    }
     if((c1 + c0) ==31 || (c1+c0)==0) return -1;
     
    p = c1+c0;
    int mask = (~0)<<(p+1);
    n &= mask;
    mask = 1<<(c1+1)-1;
    n |= mask;
    n <<= (c0-1);
    return n;
}

int numberOfFlips(int a, int b){
    printBinary(a);
    printBinary(b);
    int count =0;
    for(int c=a^b;c!=0;c &= (c-1))
        count++;
    return count;
}

int swap(unsigned int n){
    unsigned int even_bits = n & 0xAAAAAAAA;
    unsigned int odd_bits = n & 0x55555555;
    return (odd_bits<<1) | (even_bits>>1);
}

int main(){
    // int n = numberOfFlips(29,11221);
    // cout<<"number of flips "<<n;
    //mergeBits(1009997,20,2,7);
    //printBinary(-567);
    //printBinary(swap(23));
    previousLargest(40+20-9);
    // unsigned int x=-1;// pow(2,32)-1;
    // printBinary(x);
    // cout<<x<<" "<<INT_MAX<<endl;
    return 1;
}