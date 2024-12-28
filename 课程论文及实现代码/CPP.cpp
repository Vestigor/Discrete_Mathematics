#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

const int INF = numeric_limits<int>::max(); // 定义无穷大常量
typedef long long ll;

class CPPSolution {
private:
    ll n; // 图中顶点数量
    vector<vector<ll> > edge; // 邻接矩阵，存储边的权重
    vector<vector<ll> > shortest_path; // 任意两点之间的最短路径矩阵
    vector<vector<ll> > edge_repeat_num; // 边的重复次数，用于Hierholzer算法
    vector<ll> degree; // 存储每个顶点的度数
    vector<ll> odd_vertices; // 存储奇度顶点
    unordered_map<ll, unordered_map<ll, string> > path; // 存储最短路径字符串表示
    string min_cost_path; // 最小成本路径
    ll min_cost; // 最小路径成本

    // Edmonds算法相关的私有函数
    int FindLowestCommonAncestor(int u, int v, const vector<int> &match, const vector<int> &parent,
                                 const vector<int> &base, int N);

    bool BFS(int start, vector<int> &match, vector<int> &parent, vector<int> &base, vector<bool> &inQueue,
             vector<bool> &blossom, const vector<vector<ll> > &graph, int N);

    void BlossomContract(int u, int v, int lca, vector<int> &base, vector<bool> &blossom, vector<int> &parent,
                         const vector<int> &match, int N, queue<int> &q, vector<bool> &inQueue);

public:
    // 初始化邻接矩阵，计算顶点度数，找出奇度顶点
    void Initialize(const vector<vector<ll> > &matrix);

    void ComputeDegrees(); // 计算每个顶点的度数

    void FindOddVertices(); // 查找图中所有奇度顶点

    bool FloydWarshall(); // 使用Floyd-Warshall算法计算任意两点最短路径

    void Edmonds(); // 使用Edmonds算法对奇度顶点进行匹配

    void Hierholzer(ll start); // Hierholzer算法，构建欧拉回路

    pair<ll, string> Solution(const vector<vector<ll> > &matrix, ll start); // 主要求解函数
};

// 初始化图
void CPPSolution::Initialize(const vector<vector<ll> > &matrix)
{
    min_cost = 0;
    n = matrix.size(); // 顶点数量
    edge = matrix;
    shortest_path = matrix; // 初始最短路径矩阵等于原邻接矩阵
    degree.resize(n, 0); // 顶点度数初始化为0
    edge_repeat_num.resize(n, vector<ll>(n, 0)); // 初始化边的重复次数为0
    ComputeDegrees(); // 计算每个顶点的度数
    FindOddVertices(); // 查找奇度顶点
}

// 计算顶点度数，存储顶点间路径
void CPPSolution::ComputeDegrees()
{
    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < n; ++j) {
            if (edge[i][j] != INF && i != j) {
                // 若存在边且非自环
                degree[i]++; // 增加顶点度数
                edge_repeat_num[i][j] = 1; // 初始化边计数
            }
        }
    }
}

// 找出所有奇度顶点
void CPPSolution::FindOddVertices()
{
    odd_vertices.clear();
    for (ll i = 0; i < n; ++i) {
        if (degree[i] % 2 != 0) {
            // 度数为奇数
            odd_vertices.push_back(i);
        }
    }
}

// 使用Floyd-Warshall算法计算最短路径
bool CPPSolution::FloydWarshall()
{
    vector<vector<ll> > last_nods(n, vector<ll>(n, -1)); // 记录路径上的最后一个节点
    for (ll i = 0; i < n; ++i)
        for (ll j = 0; j < n; ++j)
            if (i != j && shortest_path[i][j] != INF) {
                last_nods[i][j] = j;
            }

    for (ll k = 0; k < n; ++k) {
        for (ll i = 0; i < n; ++i) {
            for (ll j = 0; j < n; ++j) {
                if (shortest_path[i][k] != INF && shortest_path[k][j] != INF) {
                    if (shortest_path[i][j] > shortest_path[i][k] + shortest_path[k][j]) {
                        shortest_path[i][j] = shortest_path[i][k] + shortest_path[k][j];
                        last_nods[i][j] = last_nods[k][j]; // 更新路径
                    }
                }
            }
        }
    }

    // 判断图是否连通
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && shortest_path[i][j] == INF) {
                return false; // 图不连通
            }
        }
    }

    // 回溯路径并存储
    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < n; ++j) {
            if (last_nods[i][j] == -1)
                continue;
            ll u = i, v = j;
            string temp_path = "";
            bool found = true;
            while (u != v) {
                u = last_nods[u][v];
                if (u == -1) {
                    found = false;
                    break;
                }
                temp_path += "->" + to_string(u);
            }
            if (found && !temp_path.empty())
                path[i][j] = temp_path;
        }
    }
    return true;
}


// 使用Edmonds算法进行最大匹配，解决奇度顶点匹配问题
void CPPSolution::Edmonds()
{
    ll N = odd_vertices.size(); // 奇度顶点数量
    if (N == 0) return; // 如果没有奇度顶点，则无需匹配

    vector<vector<ll> > odd_grap(N, vector<ll>(N, INF)); // 构建奇度顶点的完全图，初始化边权重为无穷大

    // 构建完全图的边权重，使用Floyd-Warshall计算出的最短路径作为权重
    for (ll i = 0; i < odd_vertices.size(); ++i)
        for (ll j = 0; j < odd_vertices.size(); ++j)
            odd_grap[i][j] = shortest_path[odd_vertices[i]][odd_vertices[j]];

    vector<int> match(N, -1); // 存储匹配关系，初始均为-1，表示未匹配
    vector<int> parent(N, -1), base(N); // parent用于回溯路径，base表示当前顶点的基底
    vector<bool> blossom(N); // 标记blossom收缩的顶点
    vector<bool> inQueue(N); // 标记顶点是否在队列中

    // 对每个未匹配的奇度顶点进行匹配尝试
    for (int i = 0; i < N; i++) {
        if (match[i] == -1) {
            BFS(i, match, parent, base, inQueue, blossom, odd_grap, N); // 进行BFS扩展路径
        }
    }

    // 将匹配结果合并到邻接矩阵中
    for (int i = 0; i < N; i++) {
        if (match[i] != -1) {
            edge[odd_vertices[i]][odd_vertices[match[i]]] = odd_grap[i][match[i]];
            edge_repeat_num[odd_vertices[i]][odd_vertices[match[i]]]++;
        }
    }
}

// 广度优先搜索（BFS）寻找增广路径
bool CPPSolution::BFS(int start, vector<int> &match, vector<int> &parent, vector<int> &base,
                      vector<bool> &inQueue, vector<bool> &blossom,
                      const vector<vector<ll> > &graph, int N)
{
    fill(parent.begin(), parent.end(), -1); // 初始化父节点
    fill(inQueue.begin(), inQueue.end(), false); // 队列标记初始化
    for (int i = 0; i < N; i++) base[i] = i; // 每个顶点的基底初始化为自身

    queue<int> q;
    q.push(start);
    inQueue[start] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < N; v++) {
            // 遍历图中所有可能的边，寻找增广路径
            if (graph[u][v] > 0 && base[u] != base[v] && match[u] != v) {
                if (v == start || (match[v] != -1 && parent[match[v]] != -1)) {
                    // 若找到花朵（blossom），收缩花朵，即处理奇数长度的环
                    int lca = FindLowestCommonAncestor(u, v, match, parent, base, N);
                    BlossomContract(u, v, lca, base, blossom, parent, match, N, q, inQueue);
                }
                else if (parent[v] == -1) {
                    // 未访问过的顶点，继续扩展路径
                    parent[v] = u;
                    if (match[v] == -1) {
                        // 找到增广路径，回溯更新匹配
                        while (v != -1) {
                            int pv = parent[v], nv = match[pv];
                            match[v] = pv;
                            match[pv] = v;
                            v = nv;
                        }
                        return true;
                    }
                    q.push(match[v]); // 扩展匹配路径
                    inQueue[match[v]] = true;
                }
            }
        }
    }
    return false;
}

// 收缩blossom花朵
void CPPSolution::BlossomContract(int u, int v, int lca, vector<int> &base, vector<bool> &blossom,
                                  vector<int> &parent, const vector<int> &match,
                                  int N, queue<int> &q, vector<bool> &inQueue)
{
    fill(blossom.begin(), blossom.end(), false);

    // 调整路径，收缩到最近公共祖先
    auto adjust = [&](int x) {
        while (base[x] != lca) {
            blossom[base[x]] = blossom[base[match[x]]] = true;
            x = parent[match[x]];
        }
    };

    adjust(u);
    adjust(v);

    // 更新基底为lca
    for (int i = 0; i < N; i++) {
        if (blossom[base[i]]) {
            base[i] = lca;
            if (!inQueue[i]) {
                q.push(i);
                inQueue[i] = true;
            }
        }
    }
}

// 寻找最近公共祖先
int CPPSolution::FindLowestCommonAncestor(int u, int v, const vector<int> &match,
                                          const vector<int> &parent,
                                          const vector<int> &base, int N)
{
    vector<bool> visited(N, false);

    while (true) {
        u = base[u];
        visited[u] = true;
        if (match[u] == -1) break;
        u = parent[match[u]];
    }

    while (true) {
        v = base[v];
        if (visited[v]) return v; // 第一个访问的共同祖先即为LCA
        v = parent[match[v]];
    }
    return -1;
}


// 使用Hierholzer算法寻找欧拉回路
void CPPSolution::Hierholzer(ll start)
{
    stack<int> stk; // 栈用于存储当前路径中的顶点
    vector<int> circuit; // 存储最终的欧拉回路

    int current_vertex = start; // 从指定的起点开始寻找回路

    while (!stk.empty() || current_vertex != -1) {
        bool hasEdge = false; // 标志位，检查当前顶点是否还有未遍历的边
        for (int next_vertex = 0; next_vertex < n; ++next_vertex) {
            if (edge_repeat_num[current_vertex][next_vertex] > 0) {
                // 如果存在边，将当前顶点压入栈，表示该路径正在访问
                stk.push(current_vertex);

                // 遍历该边，减少计数表示边已使用
                edge_repeat_num[current_vertex][next_vertex]--;
                edge_repeat_num[next_vertex][current_vertex]--;

                // 移动到下一个顶点
                current_vertex = next_vertex;
                hasEdge = true;
                break;
            }
        }

        if (!hasEdge) {
            // 如果当前顶点没有未遍历的边，则加入到回路中
            circuit.push_back(current_vertex);

            // 弹出栈顶元素，继续遍历上一个顶点
            if (!stk.empty()) {
                current_vertex = stk.top();
                stk.pop();
            }
            else {
                // 若栈为空，则遍历完成
                current_vertex = -1;
            }
        }
    }

    // 构建最终路径字符串
    reverse(circuit.begin(), circuit.end()); // 反转得到正确路径
    min_cost_path = to_string(start); // 路径从起点开始
    for (ll i = 0; i < circuit.size(); ++i) {
        // 拼接路径，并计算路径总成本
        min_cost_path += path[circuit[i]][circuit[(i + 1) % circuit.size()]];
        min_cost += edge[circuit[i]][circuit[(i + 1) % circuit.size()]];
    }
}

// 解决中国邮递员问题的主函数，返回最小成本及路径
pair<ll, string> CPPSolution::Solution(const vector<vector<ll> > &matrix, ll start)
{
    Initialize(matrix); // 初始化图

    if (!FloydWarshall()) {
        // 如果图不连通，返回错误
        return make_pair(-1, "The graph is not connected.");
    }

    Edmonds(); // 进行最小匹配，解决奇度顶点问题
    Hierholzer(start); // 构建欧拉回路
    return pair<ll, string>(min_cost, min_cost_path); // 返回最小成本及路径
}

// 主函数，示例调用
int main()
{
    // 定义邻接矩阵表示的图
    vector<vector<ll> > W = {
        {0, 3, 5, 7, 2, 8},
        {3, 0, 4, 6, 1, 7},
        {5, 4, 0, 3, 6, 2},
        {7, 6, 3, 0, 4, 5},
        {2, 1, 6, 4, 0, 3},
        {8, 7, 2, 5, 3, 0}
    };

    CPPSolution solver; // 创建求解器实例
    pair<ll, string> result = solver.Solution(W, 0); // 调用解决函数，起点为0

    // 输出最小成本及路径
    cout << result.first << endl;
    cout << result.second;

    return 0;
}


/******************************************
 测试用例1
vector<vector<ll>> W = {
        {0, 4, INF, INF, INF},
        {4, 0, INF, INF, INF},
        {INF, INF, 0, 3, INF},
        {INF, INF, 3, 0, INF},
        {INF, INF, INF, INF, 0}
    };
 ******************************************/

/******************************************
 测试用例2
vector<vector<ll>> W = {
    {0, 2, 4, INF, INF},
    {2, 0, 1, 4, INF},
    {4, 1, 0, 3, 2},
    {INF, 4, 3, 0, 5},
    {INF, INF, 2, 5, 0}
};
 ******************************************/

/******************************************
 测试用例3
vector<vector<ll>> W = {
    {0, 2, 7, 4, 3},
    {2, 0, 6, 5, 8},
    {7, 6, 0, 3, 2},
    {4, 5, 3, 0, 9},
    {3, 8, 2, 9, 0}
};
 ******************************************/

/******************************************
 测试用例4
vector<vector<ll>> W = {
    {0, INF, 4, 2, 3},
    {INF, 0, INF, 4, INF},
    {4, INF, 0, 3, 2},
    {2, 4, 3, 0, 4},
    {3, INF, 2, 4, 0}
};

 ******************************************/

/******************************************
 测试用例5
vector<vector<ll>> W = {
    {0, 3, 5, 7, 2, 8},
    {3, 0, 4, 6, 1, 7},
    {5, 4, 0, 3, 6, 2},
    {7, 6, 3, 0, 4, 5},
    {2, 1, 6, 4, 0, 3},
    {8, 7, 2, 5, 3, 0}
};
 ******************************************/
