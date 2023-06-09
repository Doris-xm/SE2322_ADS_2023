#include <iostream>
#include "vector"
#include <climits>
#include <queue>
using namespace std;

/**
 * @brief 表示权重动态变化的边。
 *
 * @param to 边的终点。
 * @param lower 权重的下界。
 * @param upper 权重的上界。
 * @param step 每次变化的步长。
 * @param cycle 权重变化的周期。
 *
 * @note 输入有: 1 <= lower <= upper <= 2000
 * @note 输入有: (upper - lower) % step == 0
 */
struct Weight{
    int to;
    int lower;
    int upper;
    int step;
    int cycle;
    Weight(int t,int l,int u,int s):to(t),lower(l),upper(u),step(s){
        if(step)
            cycle = (upper - lower) / step ;
        else
            cycle = 0;
    }
};

/**
 * @brief 用于在Dijkstra算法中维护一个小顶堆。
 *
 * @param point 节点的编号。
 * @param t 到该节点时计时器的读数。
 */
struct Dist_heap{
    int point;
    int t;
    Dist_heap(int p,int time = 0):point(p),t(time){}
    Dist_heap(){}
};

/**
 * @brief 构建的小顶堆Dist_heap中用到的自定义比较函数，根据dist值比较。
 */
struct cmp{
    bool operator()(Dist_heap &a,Dist_heap &b){
        return a.t > b.t;
    }
};

/**
 * @brief 给定开始时间，确定每个变得weight，使用 Dijkstra 算法计算加权有向图的最短路径。
 *
 * @param graph 图的邻接表，只读。
 * @param N 节点数量，只读。
 * @param start_time 起始时间，只读。
 * @return 返回0到N-1的最短距离。
 *
 */
int Dijkstra( vector<Weight> *const * const graph,const int N, const int start_time) {

    //维护一个小顶堆，便于查找
    priority_queue<Dist_heap, vector<Dist_heap>, cmp> dist_heap;

    int res = INT_MAX;

    //dijkstra算法
    //由于是单源，只push起点
    dist_heap.push(Dist_heap(0,start_time));

    while(!dist_heap.empty()) {
        Dist_heap curr = dist_heap.top();//取出最小值
        dist_heap.pop();

        int num_of_edges = graph[curr.point]->size(); //遍历当前顶点可以到达的边
        for (int i = 0; i < num_of_edges; i++) {
            Weight w = graph[curr.point]->at(i);

            //计算当前时刻边的权重
            int curr_weight;
            if(w.cycle) {
                curr_weight = curr.t % (2 * w.cycle);
                if(curr_weight > w.cycle) //涨潮
                    curr_weight = (curr_weight - w.cycle) * w.step + w.lower;
                else  //退潮
                    curr_weight = w.upper - w.step * curr_weight;
            }
            else //不变
                curr_weight = w.upper;


            //计算渡过这条边后的时刻
            int next_time = curr.t + curr_weight;
            if(w.to == N-1) //到达终点,不入队，更新最小值
                res = (next_time < res) ? next_time : res;
            else if(next_time < res) //未到达终点，入队。如果当前的时间已经超过最小值，剪枝，不考虑。
                dist_heap.push(Dist_heap(w.to, next_time));
        }
    }
    return res;
}

/**
 * @brief 求两个数的最大公约数
 */
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}
/**
 * @brief 求两个数的最小公倍数
 */
int lcm(int a, int b) {
    if(b <= 0 && a > 0) return a;
    if(a <= 0 ) return b > 0 ? b : 1;
    return (a * b) / gcd(a, b);
}

int main() {
    int N,M,K;
    cin >> N >>M >> K;
//    int max_time = K;
    //创建邻接表，N个顶点，M条边
    vector<Weight> **graph;
    graph = new vector<Weight>*[N];
    for(int i=0;i<N;i++){
        graph[i] = new vector<Weight>;
    }

    for(int i=0;i<M;i++){
        int from,to,upper,lower,step;
        cin >> from >> to >> lower >> upper >> step;
        Weight w(to,lower,upper,step);
        graph[from]->push_back(w);
//        max_time = lcm(max_time,2 * w.cycle); //时间的上界定为所有周期的最小公倍数
    }

    int best_start = 0;
    int optimal_path = INT_MAX; //最优路径
    //当出发时间i大于最优路径时，不再计算
    for(int i = best_start; i < optimal_path; i += K) {
        int curr_time = Dijkstra(graph,N,i) ;
        if(curr_time < optimal_path) {
            optimal_path = curr_time;
            best_start = i;
        }
    }

    cout <<best_start<<' '<< optimal_path<< endl;

    //释放内存
    for(int i=0;i<N;i++){
        if(graph[i])
            delete graph[i];
    }
    delete []graph;
}
