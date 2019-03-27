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
     ���B�zseat number�A�M��P�_n�O�_���٬O���ơF�A�B�zpreference�A�M��P�_n�O�_���٬O����
     with a given n, S[i]=�Nn�Ӯy����b�A������_�ƦA���W����
                     P[i]=�Nn�Ӯy����b�A�����W�A����
     for a known occupied seat j,�N�Q�e����m�ܬ�0

     for a given K,���T�w�n�@�ӯ��ަ�m�A�A����1,2,3...,(K-1)�ӥh�ݦ��S���s��K�ӡA�Y���N�h��̤jpreference���զX


   coded by ���a�s, ID: H24031354, email: kevin040208@gmail.com
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
    int os[20]= {0}; //occupied seat �̦h�u�|��20�ӡA�]����l�N�]�̤j�i���20
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
    int cnt=0; //cnt�������X��occupied seat�A�ت��O���F���᭱for�j�馳�d��
    while(true)
    {
        cin >> occu; //�Ĥ@������o��|�Ncin���Ĥ@�Ӥ�����Joccu�A�ĤG������o��h�|�Ncin�ĤG�Ӥ�����Joccu�A�᭱�w������
        if(occu!=0)
        {
            os[i] = occu;
            i++;
            cnt++;
        }
        else
        {
            break; //�J��0�N���X�j��
        }
    }

    for(int p=0; p<cnt;p++){
        for(int q=0; q<n; q++){
            if(os[p]==S[q]){
                S[q] = 0; //occupied seat�N�ܦ�0
                P[q] = 0; //occupied seat�N�ܦ�0
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
    int stat=0,maxside=0; //stat�������X�ӳs�򪺪Ŧ�Amaxside�����̦h���s��Ŧ��
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

    //�H�U������j�ر��p�Aif�����N��S��K�ӳs��Ŧ�Aelse�h�N��K�ӥH�W���s��y��
    if(K > maxside){
        cout <<"Sorry! No "<<K<<" adjacent seats!";
    }
    else{
        //seatindex��̤jpreference���y��զX���̥��䪺�y����ަ�m�Atotalpreference��̤jpreference�y��զX���`preference
        int seatindex=-1,totalpreference=0,y=0,z=0,w,x;
        for(w=0;w<=(n-K);w++){ //w�����ަ�m
            y=0;
            z=0;
            for(x=0;x<K;x++){ //x���T�ww���U�A����w����+1,+2,...,+(K-1)�Ӯy��
                if(S[w+x]!=0){
                    y++; //y��C���j�M���X�ӳs��y��
                    z = z+P[w+x];//z��C���j�M��preference
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
