#include <iostream>
#include "cuckooHash.h"
#include "vector"
#include "chrono"
using namespace cuckoo;
const int Num_threads(20);
const int Test_size(50000);
const int Search_test_size(10000000);
//int Num_threads = 10;

void SequentialTest() {
    cuckooHash test;
    auto start = chrono::high_resolution_clock::now();
    for(int i = 1;i <= Test_size;i++) {
        test.put(i);
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_secs = end - start;
    printf("sequential execution, put time: %f\n",elapsed_secs.count());

    start = chrono::high_resolution_clock::now();
    for(int i = 1;i <= Search_test_size;i++) {
        if(test.get(i % Test_size + 1) == 0) {
            printf("error\n");
        }
    }
    end = chrono::high_resolution_clock::now();
    elapsed_secs = end - start;
    printf("sequential execution,get time: %f\n",elapsed_secs.count());
}

void ParallelTest() {
    cuckooHash test;
    int chunkSize = Test_size / Num_threads;
    vector<thread> threads;

    auto start = chrono::high_resolution_clock::now();

    threads.clear();
    // 插入操作
    for (int t = 0; t < Num_threads; ++t) {
        threads.emplace_back([&](int threadId) {
            int startIdx = threadId * chunkSize + 1;
            int endIdx = (threadId + 1) * chunkSize;

            for (int i = startIdx; i <= endIdx; ++i) {
                if(threadId == 23) printf("put %d,%d\n",i,threadId);
                test.put(i);
            }
        }, t);
    }

    for (auto& thread : threads) {
        thread.join();
    }
//
//    for(int i = 1;i <= Test_size;i++) {
//        test.put(i);
//    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_secs = end - start;
    cout << "parallel execution, put time: " << elapsed_secs.count()<<endl;


    start = chrono::high_resolution_clock::now();
    // 查找操作
    threads.clear();
    chunkSize = Search_test_size / Num_threads;
    for (int t = 0; t < Num_threads; ++t) {
        threads.emplace_back([&](int threadId) {
            int startIdx = threadId * chunkSize + 1;
            int endIdx = (threadId + 1) * chunkSize;

            for (int i = startIdx; i <= endIdx; ++i) {
                if (test.get(i % Test_size + 1) == 0) {
                    printf("Parallel:: Not found %d \n", i % Test_size + 1);
                }
            }
        }, t);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    end = chrono::high_resolution_clock::now();
    elapsed_secs = end - start;
    cout << "parallel execution, get time: " << elapsed_secs.count()<<endl;
}

int main() {
    printf("start test on sequential execution\n");
    SequentialTest();

    printf("start test on %d threads execution\n",Num_threads);
    ParallelTest();
    return 0;
}
