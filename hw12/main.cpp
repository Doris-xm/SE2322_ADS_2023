//#include <fstream>
#include <iostream>
#include "Kruskal.h"
#include "Parallel_kruskal.h"
void run(const std::string& filename);
void runParallel(const std::string& filename);
int main() {
    std::string filename = "10000_8000000.txt"; // 替换为你实际使用的文件名
    auto start = chrono::high_resolution_clock::now();
    run(filename);
    auto end = chrono::high_resolution_clock::now();
    cout<< "time: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    start = chrono::high_resolution_clock::now();
    runParallel(filename);
    end = chrono::high_resolution_clock::now();
    cout<< "parallel time: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count()-1000000 << endl;
    return 0;
}
