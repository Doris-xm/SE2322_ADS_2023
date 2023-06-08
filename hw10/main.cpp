#include <iostream>
#include <string>
#include "thread"
#include "mutex"
using namespace std;
int MaxThread = 8;
const int n = 40;
mutex mtx;
int* res;

int Fibonacci(int n) {

    if (n == 0 || n == 1) {
        return 1;
    }
    int res1, res2;
    if(MaxThread > 1) { //如果最大线程数大于1，就开两个线程
        {
            unique_lock<mutex> lock(mtx);
            MaxThread--;
        }

        thread t1([&] { res1 = Fibonacci(n - 1); });

        {
            unique_lock<mutex> lock(mtx);
            MaxThread--;
        }

        thread t2([&] { res2 = Fibonacci(n - 2); });

        t1.join();

        {
            unique_lock<mutex> lock(mtx);
            MaxThread++;
        }

        t2.join();

        {
            unique_lock<mutex> lock(mtx);
            MaxThread++;
        }

        return res1 + res2;

    }

    return Fibonacci(n - 1) + Fibonacci(n - 2);

}
int Fibbo(int n){
    if (n == 0 || n == 1) {
        return 1;
    }
    return Fibbo(n-1)+Fibbo(n-2);
}
int main() {

    res = new int[MaxThread];
    cout<< "Counting Fibbo("<<n<<")..."<<endl;
    cout<<"Threads = "<<MaxThread<<endl;

    auto start = chrono::high_resolution_clock::now();
    int parallel_res = Fibonacci(n);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_secs = end - start;
    cout<<"Parallel result is: "<<parallel_res<<"  Using time: "<<elapsed_secs.count()<<endl;

    auto start1 = chrono::high_resolution_clock::now();
    int seq_res = Fibbo(n);
    auto end1 = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_secs1 = end1 - start1;
    cout<<"Sequential result is: "<<seq_res<<"  Using time: "<<elapsed_secs1.count()<<endl;

    delete [] res;
    return 0;
}
//void buildNext(string P) {
//    size_t m = P.size(), j = 0; //“主”串指针
//    int* Next = new int[m]; //next表
//    int t = Next[0] = -1; //模式串指针
//    while (j < m - 1)
//        if (t < 0 || P[j] == P[t]) { //匹配
//            if(t >= 0)
//                cout<<"P["<<j<<"] = P["<<t<<"] = "<<P[t]<<endl;
//            j ++; t ++;
//            Next[j] = t;
//            cout<<"j = "<<j<<"  t = "<<t<<"   Next["<<j<<"] = " <<Next[j]<<endl;
//            cout<<endl;
//        } else {//失配
//            cout<<"P["<<j<<"] = "<<P[j]<<", P["<<t<<"] = "<<P[t]<<endl;
//            t = Next[t];
//            cout<<"back: t= "<< t <<endl;
//        }
//    delete [] Next;
//}
//int main(){
//    string P = "abcdaabcdabcg";
//    buildNext(P);
//    return 0;
//}