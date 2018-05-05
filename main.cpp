
#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <fstream>
#include <iomanip>
#include <string>
#define END 25
#define FILENAME "statistical data(300K)-XD.csv"//輸出csv 檔名
#define DATA_SAVE_PATH ".\\data"//檔案儲存路徑
#define DATA_NAME_original  "-Original.txt"//排序前檔案
#define DATA_NAME_sorting  "-Soring.txt" //排序完畢檔案

using namespace std;

typedef unsigned long long ull;

// random generator function
int myrandom (int i) { return std::rand()%i;}
// return vector with random elements
vector<ull> random_vector(ull);
// Show vector elements
void show(vector<ull>);
// Bubble sort
void bubbleSort (vector<ull>&);
// Select sort
void selectSort(vector<ull>&);
// Quick sorting
void quickSort(vector<ull> &vec, int L, int R);
//Insertion sort
void insertSort(vector<ull>&);
//Heap sort
void heapSort(vector<ull>&);
void MaxHeapify(vector<ull>&, ull root, ull length);
void BuildMaxHeap(vector<ull> &);
//vector's data write back to XX.txt
void writeBackToTxt(vector<ull>& a,fstream& f){
  for(ull i = 0; i<a.size();i++ ){
      f << setw(7) << a[i] << ", ";
      if(((i+1)%10 ==0))
        f << "\n";
  }
}

//-----------------------------------------------------
int main () {
  fstream file,data_original,data_sorting;
  string casePath="",sDataName="",oDataName="",pt1,pt2;
  file.open(FILENAME, ios::out);
  if( !file ) cout << "open file failed!\n";
  else{
    clock_t start, stop;

    size_t index;//numbers[index];
    double BubRunTime[25][6]={0},avgBubTime[6]={0},
           InsRunTime[25][6]={0},avgInsTime[6]={0},
           SelRunTime[25][6]={0},avgSelTime[6]={0},
           QuiRunTime[25][6]={0},avgQuiTime[6]={0},
           HeapRunTime[25][6]={0},avgHeapTime[6]={0},
           sumTime;
    ull numbers[6] = {50000,100000,150000,200000,250000,300000},
        i;
    vector<ull> B,S,I,Q,H;//for bubble,select,insert,quick....


  for(int t=0 ; t<END ; t++){
      casePath = DATA_SAVE_PATH;
      casePath +=  "\\case";//switch caseN folder
      casePath += to_string(t+1);
      cout << "Folder Path: " << "\""<<casePath << "\"" << endl;

      cout << "********* Test time " << t+1 << " *********\n";
      file << "Case " << t+1 << ":           ,,,,,,\n";
      file << "Data Numbers ,,Bubble ,,Select ,,Insert ,,Quick ,,Heap\n";
      for( index=0;index<6;index++){

        i = numbers[index];
        file << i << "(c),,";

        //setting file name
        oDataName = "";
        oDataName = to_string(i)+DATA_NAME_original;
        sDataName = "";
        sDataName = to_string(i)+DATA_NAME_sorting;
        pt1 = "";pt2 = "";
        pt1 = casePath+"\\"+oDataName;
        pt2 = casePath+"\\"+sDataName;

        cout<< "oringal data path:" << pt1 << endl;
        cout<< "sorting data path:" << pt2 << endl;
        data_original.open( casePath+"\\"+oDataName, ios::out);
        data_sorting.open(  casePath+"\\"+sDataName, ios::out);
        if( !data_original || !data_sorting){
          cout << "open .txt failed!\n";
          system("pause");
          exit(1);
        }

        vector<ull> myvector = random_vector(i);//not sort "myvector"
        //write to original.txt;
        writeBackToTxt(myvector,data_original);

        B.assign(myvector.begin(), myvector.end());
        S.assign(myvector.begin(), myvector.end());
        Q.assign(myvector.begin(), myvector.end());
        I.assign(myvector.begin(), myvector.end());
        H.assign(myvector.begin(), myvector.end());
        cout << "sorting numbers " << i << " ..."<< endl;
        //bubble
        start = clock(); //開始時間
        bubbleSort(B);
        stop = clock(); //結束時間
        data_sorting << "Bubble sort result:\n";
        writeBackToTxt(  B,data_sorting);
        BubRunTime[t][index] = double(stop - start) / CLOCKS_PER_SEC;
        file <<  BubRunTime[t][index]  << " s,,";
        //select
        start = clock(); //開始時間
        selectSort(S);
        stop = clock(); //結束時間
        data_sorting << "\nSelect sort result:\n";
        writeBackToTxt(  S,data_sorting);
        SelRunTime[t][index] = double(stop - start) / CLOCKS_PER_SEC;
        file << SelRunTime[t][index]  << " s,,";
        //Insert
        start = clock(); //開始時間
        insertSort(I);
        stop = clock(); //結束時間
        data_sorting << "\nInsert sort result:\n";
        writeBackToTxt(  I,data_sorting);
        InsRunTime[t][index] = double(stop - start) / CLOCKS_PER_SEC;
        file << InsRunTime[t][index]  << " s,,";
        //quick
        start = clock(); //開始時間
        quickSort( Q, 0, Q.size()-1 );
        stop = clock(); //結束時間
        data_sorting << "\nQuick sort result:\n";
        writeBackToTxt(  Q,data_sorting);
        QuiRunTime[t][index] = double(stop - start) / CLOCKS_PER_SEC;
        file << QuiRunTime[t][index]  << " s,,";
        //HeapSort
        start = clock(); //開始時間
        heapSort(H);
        stop = clock(); //結束時間
        data_sorting << "\nHeap sort result:\n";
        writeBackToTxt(  H,data_sorting);
        HeapRunTime[t][index] = double(stop - start) / CLOCKS_PER_SEC;
        file << HeapRunTime[t][index]  << " s\n";
        cout << "-------------------------------------------" << endl;
        data_original.close();
        data_sorting.close();
      }
    file << ",,,,,,\n";
    }
    //----Calc All avgrange cost time for each case
    //calc bubble
    for(size_t i=0;i<END;i++)
       for(size_t c=0;c<6;c++)
         avgBubTime[c] += BubRunTime[i][c];
    for(size_t i=0;i<6;i++)
         avgBubTime[i]/=END;
    //calc select
    for(size_t i=0;i<END;i++)
      for(size_t c=0;c<6;c++)
        avgSelTime[c] += SelRunTime[i][c];
    for(size_t i=0;i<6;i++)
        avgSelTime[i]/=END;
    //calc insert
    for(size_t i=0;i<END;i++)
      for(size_t c=0;c<6;c++)
        avgInsTime[c] += InsRunTime[i][c];
    for(size_t i=0;i<6;i++)
        avgInsTime[i]/=END;
    //calc quick
    for(size_t i=0;i<END;i++)
      for(size_t c=0;c<6;c++)
        avgQuiTime[c] += QuiRunTime[i][c];
    for(size_t i=0;i<6;i++)
      avgQuiTime[i]/=END;
    //calc heap
    for(size_t i=0;i<END;i++)
      for(size_t c=0;c<6;c++)
        avgHeapTime[c] += HeapRunTime[i][c];
    for(size_t i=0;i<6;i++)
      avgHeapTime[i]/=END;
    //----End calc
    file << "Avgrange cost time : \n";
    file << "Data Number ,,Bubble ,,Select ,,Insert ,,Quick ,,Heap \n";

    for(size_t i=0;i<6;i++){
      file << numbers[i] << "(c),," << avgBubTime[i] << " s,,"
                                    << avgSelTime[i] << " s,,"
                                    << avgInsTime[i] << " s,,"
                                    << avgQuiTime[i] << " s,,"
                                    << avgHeapTime[i] << " s,,"
                                    << "\n";
    }
    file.close();
    cout << "output file -> "<< FILENAME << "complete!\n";
  }

  system("pause");
  return 0;
}
//-----------------------------------------------------
void MaxHeapify(vector<ull> &array, ull root, ull length){

    ull left = 2*root,      // 取得left child
    right = 2*root + 1,     // 取得right child
    largest;                // largest用來記錄包含root與child, 三者之中Key最大的node

    if (left <= length && array[left] > array[root])
        largest = left;
    else
        largest = root;
    if (right <= length && array[right] > array[largest])
        largest = right;
    if (largest != root) {                         // 如果目前root的Key不是三者中的最大
        swap(array.at(largest), array.at(root));   // 就調換root與三者中Key最大的node之位置
        MaxHeapify(array, largest, length);        // 調整新的subtree成Max Heap
    }
}

void BuildMaxHeap(vector<ull> &array){

    for (ull i = (ull)array.size()/2; i >= 1 ; i--) {
        MaxHeapify(array, i, (ull)array.size() - 1);// length要減一, 因為heap從1開始存放資料
    }
}

void heapSort(vector<ull> &array){
    array.insert(array.begin(), 0);                     // 將index(0)閒置
    BuildMaxHeap(array);                                // 將array調整成Max Heap

    ull size = (ull)array.size() -1;                    // size用來記錄「目前要處理的矩陣」之長度
    for (ull i = (ull)array.size() -1; i >= 2; i--) {
        swap(array.at(1), array.at(i));                 // 將最大值放到array的最後一個位置
        size--;
        MaxHeapify(array, 1, size);                     // 調整「忽略最後一個位置」的矩陣
    }
    array.erase(array.begin());                         // 將index(0)刪除
}
//-----------------------------------------------------
void insertSort(vector<ull> &a)
{
    for(int i=1; i<a.size(); i++)
    {
        int key = a[i];
        for(int j=i-1; j>-1; j--)
        {
            if (key < a[j])
            {
                a[j+1] = a[j];
                a[j] = key;
            }
            else break;
        }
    }
}
//-----------------------------------------------------
void quickSort(vector<ull> &vec, int L, int R) {
    int i, j, mid, piv;
    i = L;
    j = R;
    mid = L + (R - L) / 2;
    piv = vec[mid];

    while (i<R || j>L) {
        while (vec[i] < piv)
            i++;
        while (vec[j] > piv)
            j--;

        if (i <= j) {
            swap(vec.at(i),vec.at(j));
            i++;
            j--;
        }
        else {
            if (i < R)
                quickSort(vec, i, R);
            if (j > L)
                quickSort(vec, L, j);
            return;
        }
    }
}
//-----------------------------------------------------
void selectSort(vector<ull>& a){
  int vecsize = a.size();
  for (int j = 0; j < vecsize - 1; ++j) {
    int min = j;
    for (int i = j+1; i < vecsize; ++i) {
        if (a.at(min) > a.at(i))
            min = i;
    }
    if (min != j)
        swap(a.at(j), a.at(min));
  }
}
//-----------------------------------------------------
void bubbleSort(vector<ull>& a)
{
      bool swapp = true;
      while(swapp){
        swapp = false;
        for (size_t i = 0; i < a.size()-1; i++) {//size_t least 16 bit uint
            if (a[i]>a[i+1] ){
                a[i] += a[i+1];
                a[i+1] = a[i] - a[i+1];
                a[i] -=a[i+1];
                swapp = true;
            }
        }
    }
}
//-----------------------------------------------------
vector<ull> random_vector(ull size){
  srand ( unsigned ( time(0) ) );

  vector<ull> myvector;

  // set some values:
  for (int i=1; i<=size; ++i) myvector.push_back(i); // 1 2 3 4 5 6 7 8 9

  // using built-in random generator:
  random_shuffle ( myvector.begin(), myvector.end() );

  // using myrandom:
  random_shuffle ( myvector.begin(), myvector.end(), myrandom);
  return myvector;
}
//------------------------------------------
void show(vector<ull> x){
  for (vector<ull>::iterator it=x.begin(); it!=x.end(); ++it)
    cout << ' ' << *it;
  cout << endl;
}
//------------------------------------------
