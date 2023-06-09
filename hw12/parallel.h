#pragma once
#include<iostream>
#include<vector>
#include<thread>
#include<map>
#include<mutex>
#include<condition_variable>
#include<fstream>
#include <unistd.h>
#include <queue>
#include "windows.h"
using namespace std;

std::vector<std::vector<int>> kruskal_parallel(int n, int m, std::vector<edge>& edges, int& mst) {
    std::vector<std::vector<int>> result;
    std::priority_queue<edge, std::vector<edge>, std::function<bool(const edge&, const edge&)>> queue([](const edge& a, const edge& b) {
        return a.weight > b.weight;
    });

    int numThreads = std::thread::hardware_concurrency();
    std::cout << numThreads << std::endl;
    std::vector<Partition> partitions(numThreads);

    // Partition the edges
    for (int i = 0; i < m; ++i) {
        partitions[i % numThreads].edges.push_back(edges[i]);
    }

    // Start thread for each partition
    for (int i = 0; i < numThreads; ++i) {
        partitions[i].thread = std::thread([&partitions, i, &queue]() {
            Partition& partition = partitions[i];
            while (true) {
                std::unique_lock<std::mutex> lock(partition.mutex);
                partition.cv.wait(lock, [&partition]() {
                    return partition.finished || !partition.edges.empty();
                });

                if (partition.finished) {
                    break;
                }

                edge minEdge = partition.edges.back();
                partition.edges.pop_back();
                lock.unlock();
                partition.cv.notify_all();

                if (minEdge.weight < 0) {
                    queue.push(minEdge);
                }
            }
        });
    }

    // Global thread
    DisjointSet disjointSet(n);
    while (result.size() < n - 1 && !queue.empty()) {
        edge minEdge = queue.top();
        queue.pop();

        if (!disjointSet.connected(minEdge.from, minEdge.to)) {
            disjointSet.Union(minEdge.from, minEdge.to);
            result.push_back({ minEdge.from, minEdge.to, minEdge.weight });
            mst += minEdge.weight;
        }
    }

    // Notify partitions to finish
    for (int i = 0; i < numThreads; ++i) {
        Partition& partition = partitions[i];
        std::unique_lock<std::mutex> lock(partition.mutex);
        partition.finished = true;
        lock.unlock();
        partition.cv.notify_all();
        partition.thread.join();
    }

    if (result.size() != n - 1) {
        mst = 0;
        return {};
    }

    return result;
}
