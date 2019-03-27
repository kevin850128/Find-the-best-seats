/*
   This code can be compiled and run ok.

   Given a row of n seats in a theater, you need to calculate and output the
   seat no., stored in S[i], i=0,...,n-1
   seat preference, stored in P[i], i=0,...,n-1

   Then, input the no. of occupied seats, output the seat no. & preference by
   replacing the status of the occupied seats by "X"

   Then, input the number of adjacent seats requested, denoted by K, output the
   selected seats of the maximal total preference, or NONE if no such seats.

   usage (how to run):
     seat  (then input n and alpha)

   input file:
     none

   output file:
     none

   compile (how to compile):
     g++ -o seat hw1.cpp

   pseudocode:
     先處理seat number，然後判斷n是奇數還是偶數；再處理preference，然後判斷n是奇數還是偶數
     with a given n, S[i]=將n個座位拆成兩半，先遞減奇數再遞增偶數
                     P[i]=將n個座位拆成兩半，先遞增再遞減
     for a known occupied seat j,將被占的位置變為0

     for a given K,先固定好一個索引位置，再往後1,2,3...,(K-1)個去看有沒有連續K個，若有就去找最大preference的組合


   coded by 江冠駒, ID: H24031354, email: kevin040208@gmail.com
   date: 2018.03.14
*/
#include <iostream>
#include <iomanip>
using namespace std ;

int main()
{
    //---begin--- PART 1: Declaration -----------
    int n=0, K=0;
    int S[20]= {0}; //Seat
    int P[20]= {0}; //Preference
    int os[20]= {0}; //occupied seat 最多只會有20個，因此初始就設最大可能值20
    //--- end --- PART 1: Declaration -----------



    //---begin--- PART 2: Calculate S[] & P[] -----------
    cout << "Number of seats n in [5,20] = ? ";  //input total seat
    cin >> n ;
    while(n<5||n>20)        //check if the input is right in the range[5,20].
    {
        cout << "!!WRONG!! Please input an integer in [5,20] = ? ";  //if not,input again.
        cin >> n;
    }
    cout << "Seat number: ";
    if(n%2==1){
        for(int j=n,k=0; j>0,k<((n+1)/2); j=j-2,k++){
            cout << j << " ";
            S[k] = j;
        }
        for(int j=2,k=((n+1)/2); j<n,k<n; j=j+2,k++){
            cout << j << " ";
            S[k] = j;
        }
    }
    else{
        for(int j=n-1,k=0; j>0,k<(n/2); j=j-2,k++){
            cout << j << " ";
            S[k] = j;
        }
        for(int j=2,k=(n/2); j<=n,k<n; j=j+2,k++){
            cout << j << " ";
            S[k] = j;
        }
    }
    cout << endl;
    cout << "Seat preference: ";
    if(n%2==1){
        for(int j=1,k=0; j<=((n+1)/2),k<((n+1)/2); j++,k++){
            cout << j << " ";
            P[k] = j;
        }
        for(int j=((n-1)/2),k=((n+1)/2); j>0,k<n; j--,k++){
            cout << j << " ";
            P[k] = j;
        }
    }
    else{
        for(int j=1,k=0; j<=(n/2),k<(n/2); j++,k++){
            cout << j << " ";
            P[k] = j;
        }
        for(int j=(n/2),k=(n/2); j>0,k<n; j--,k++){
            cout << j << " ";
            P[k] = j;
        }
    }
    cout << endl;
    //--- end --- PART 2: Calculate S[] & P[] -----------





    //---begin--- PART 3: Output Updated Seat Status with known Occupied seats -----------
    cout << "Occupied seat no.: ? ";
    int i=0;
    int occu=0;
    int cnt=0; //cnt紀錄有幾個occupied seat，目的是為了讓後面for迴圈有範圍
    while(true)
    {
        cin >> occu; //第一次執行這行會將cin的第一個元素放入occu，第二次執行這行則會將cin第二個元素放入occu，後面已次類推
        if(occu!=0)
        {
            os[i] = occu;
            i++;
            cnt++;
        }
        else
        {
            break; //遇到0就跳出迴圈
        }
    }

    for(int p=0; p<cnt;p++){
        for(int q=0; q<n; q++){
            if(os[p]==S[q]){
                S[q] = 0; //occupied seat就變成0
                P[q] = 0; //occupied seat就變成0
            }
        }
    }

    cout << "Seat number: ";
    int r=0;
    for(r=0; r<n; r++){
        if(S[r]==0){
            cout << "X ";
        }
        else{
            cout << S[r] <<" ";
        }
    }
    cout << endl << "Seat preference: ";
    for(r=0; r<n; r++){
        if(P[r]==0){
            cout << "X ";
        }
        else{
            cout << P[r] <<" ";
        }
    }
    //--- end --- PART 3: Output Updated Seat Status with known Occupied seats -----------



    //---begin--- PART 4: Seek optimal K adjacent seats -----------
    cout << endl <<"How many adjacent seats to seek? ";   //input how many adjacent seat(K) to calculate max seat preference
    cin >> K;
    int stat=0,maxside=0; //stat紀錄有幾個連續的空位，maxside紀錄最多的連續空位數
    for(int m=0;m<n;m++){
        if(S[m]!=0){
            stat++;
        }
        else{
            if(stat > maxside){
                maxside = stat;
            }
            stat=0;
        }
    }
    if(stat > maxside){
        maxside = stat;
    }

    //以下分成兩大種情況，if內的代表沒有K個連續空位，else則代表有K個以上的連續座位
    if(K > maxside){
        cout <<"Sorry! No "<<K<<" adjacent seats!";
    }
    else{
        //seatindex表最大preference的座位組合中最左邊的座位索引位置，totalpreference表最大preference座位組合的總preference
        int seatindex=-1,totalpreference=0,y=0,z=0,w,x;
        for(w=0;w<=(n-K);w++){ //w為索引位置
            y=0;
            z=0;
            for(x=0;x<K;x++){ //x為固定w之下，控制w往後+1,+2,...,+(K-1)個座位
                if(S[w+x]!=0){
                    y++; //y表每次搜尋有幾個連續座位
                    z = z+P[w+x];//z表每次搜尋的preference
                }
                else{
                    break;
                }
            }
            if(y==K&&z>totalpreference){
                seatindex = w;
                totalpreference = z;
            }
        }
        cout << "Best "<<K<<" adjacent seats: no. ";
        for(x=0;x<K;x++){
            cout << S[seatindex+x] << ", ";
        }
        cout << "with total preference "<<totalpreference<<".";
    }
   //--- end --- PART 4: Seek optimal K adjacent seats -----------

    cout << "Hello World";
    return 0 ;
}
