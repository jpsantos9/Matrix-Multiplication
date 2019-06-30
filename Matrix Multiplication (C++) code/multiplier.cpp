#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
using namespace std;

//print matrix
void printMat (int matrix [100][100], int size[2]){
    for (int i=0;i<size[0];i++){
        for (int j=0;j<size[1];j++){
            cout<<matrix[i][j]<<"\t";
        }
        cout<<endl;
    }
    cout<<"size: "<<size[0]<<"x"<<size[1];
    cout<<endl;
    cout<<endl;
}

//put file content to multi-array
void outputFile (string fname, int matrix[100][100], int size[2]) {
    string line;
    ifstream theFile (fname.c_str(), ios::in);
    int j=0,i=0;
    while (getline(theFile, line)) {
        //theFile.get(word, ' ');
        istringstream buf(line);
        for(string word; buf >> word; ) {
            //cout<<word<<"|";
            matrix[i][j]=stoi(word);
            j++;
        }
        i++;
        size[0]=i;
        size[1]=j;
        j=0;
        //cout<<"#";
    }
}

//multiply matrix
void multiply (int matA[100][100], int sizeA[2], int matB[100][100], int sizeB[2], int matAns[100][100], int sizeAns[2]) {
    sizeAns[0]=sizeA[0];
    sizeAns[1]=sizeB[1];
    int sum=0;
    //cout<<sizeAns[0]<<sizeAns[1];
    for (int i=0;i<sizeAns[0];i++){
        for (int j=0;j<sizeAns[1];j++){
            for (int k=0;k<sizeA[1];k++){
                sum=sum+(matA[i][k]*matB[k][j]);
            }
            //cout<<sum;
            matAns[i][j]=sum;
            sum=0;
        }
    }
}

int main(){
    string file1, file2;
    //ask for file names
    cout<<"file 1: ";
    cin>>file1;
    cout<<"file 2: ";
    cin>>file2;
    auto start = chrono::steady_clock::now();
    //get files and put in array
    int matA[100][100], matB [100][100], matAns [100][100];
    int sizeA[2], sizeB[2], sizeAns[2];
    outputFile(file1, matA, sizeA);
    cout<<"Matrix A"<<endl;
    printMat(matA, sizeA);
    outputFile(file2, matB, sizeB);
    cout<<"Matrix B"<<endl;
    printMat(matB, sizeB);

    multiply(matA, sizeA, matB, sizeB, matAns, sizeAns);
    cout<<"Matrix Ans"<<endl;
    printMat(matAns, sizeAns);
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout << chrono::duration <double, milli> (diff).count() << " ms" << endl;
    return 0;
}
