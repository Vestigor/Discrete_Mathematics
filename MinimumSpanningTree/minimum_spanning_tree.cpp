
/***********************************************************
* File:     my_graph_mst.cpp
* Author:   Xiaolong Ma(马小龙)
* E-mail:   2353814@tongji.edu.cn
* Function: Graph & MinSpanTree
* Encoding: UTF-8
* Date:     2024.11.23
* Update:   2024.11.23
***********************************************************/
#include <cassert>
#include <conio.h>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>

#define INF 1000000000

/***********************************************************
* Struct: MSTEdgeNode
* Function: 表示最小生成树中的一条边
***********************************************************/
template<typename T>
struct MSTEdgeNode {
    T tail, head; // 边的起点和终点
    double key; // 边的权重
    MSTEdgeNode(): tail(T()), head(T()), key(0) {}
    MSTEdgeNode(T src, T end, double key): tail(src), head(end), key(key) {}
};

/***********************************************************
* Class:    MinSpanTree
* Function: 管理最小生成树的边集合。
***********************************************************/
template<typename T>
class MinSpanTree {
public:
    MSTEdgeNode<T> *edge_value;
    MinSpanTree(){maxSize = n = 0;edge_value = nullptr;};
    MinSpanTree(int size);
    MinSpanTree(const MinSpanTree<T> &other);
    ~MinSpanTree() { delete[] edge_value; }
    void Initial(int size);
    void MakeEmpty();
    void Insert(const MSTEdgeNode<T> &item);
    bool BuildSuccess() { return n == maxSize; }
    int GetSize() const { return maxSize; }

private:
    int maxSize, n;
};

/***********************************************************
* Function Name:     MinSpanTree
* Function:         构造函数，存储内存
* Input Parameter:  size - 最小生成树可以存储的边数。
***********************************************************/
template<typename T>
MinSpanTree<T>::MinSpanTree(int size)
{
    maxSize = size - 1;
    n = 0;
    edge_value = new(std::nothrow) MSTEdgeNode<T>[size];
    assert(edge_value!=nullptr);
}

/***********************************************************
* Function Name:   MinSpanTree<T>::MinSpanTree
* Function:       拷贝构造函数，创建一个新的最小生成树对象，并复制另一个最小生成树的内容。
* Input Parameter: other - 需要复制的最小生成树对象。
***********************************************************/
template<typename T>
MinSpanTree<T>::MinSpanTree(const MinSpanTree<T> &other)
{
    if (this == &other)
        return;
    maxSize = other.maxSize;
    n = other.n;

    // 分配内存
    edge_value = new MSTEdgeNode<T>[maxSize];
    assert(edge_value != nullptr);

    // 复制数据
    for (int i = 0; i < n; i++) {
        edge_value[i] = other.edge_value[i];
    }
}

/***********************************************************
* Function Name:    Initial
* Function:        初始化最小生成树，设置边数组大小并分配内存。
* Input Parameter: size - 最小生成树可以存储的边数。
***********************************************************/
template<typename T>
void MinSpanTree<T>::Initial(int size)
{
    assert(maxSize==0);
    maxSize = size - 1;
    n = 0;
    edge_value = new(std::nothrow) MSTEdgeNode<T>[size];
    assert(edge_value!=nullptr);
}

/***********************************************************
* Function Name: MakeEmpty
* Function:     清空最小生成树的边集合，并释放内存。
***********************************************************/
template<typename T>
void MinSpanTree<T>::MakeEmpty()
{
    if (edge_value != nullptr) {
        delete[] edge_value;
        edge_value = nullptr;
    }
    maxSize = n = 0;
}

/***********************************************************
* Function Name:    Insert
* Function:         向最小生成树中插入一条边。
* Input Parameter:  item - 要插入的边。
***********************************************************/
template<typename T>
void MinSpanTree<T>::Insert(const MSTEdgeNode<T> &item)
{
    assert(n< maxSize);
    assert(edge_value!=nullptr);
    edge_value[n] = item;
    n++;
}

/***********************************************************
* Class:    Graph
* Function: 表示加权无向图，并提供构建最小生成树的功能。
***********************************************************/
template<typename T>
class Graph {
public:
    Graph(int sz);
    ~Graph() { MakeEmpty(); }
    void MakeEmpty();
    void SetEdgeValue(T start, T end, double value);
    void SetDot(const T &dot);
    bool FindDot(const T &dot);
    bool Prim(T start);
    MinSpanTree<T> GetMST()  { return min_span_tree; }
    void InitialEdgeValue();
private:
    int size, n;
    T *dots;
    double **edge_value;
    MinSpanTree<T> min_span_tree;
    std::unordered_map<T, int> hash_table;
};

/***********************************************************
* Function Name:    Graph<T>::Graph
* Function:         Graph 的构造函数，初始化图的结构。
* Input Parameter:  sz - 图中顶点的最大数量。
***********************************************************/
template<typename T>
Graph<T>::Graph(const int sz):size(sz),min_span_tree()
{
    assert(sz>1);
    n = 0;
    dots = new(std::nothrow) T[size];
    assert(dots!=nullptr);
    edge_value = new(std::nothrow) double *[size];
    assert(edge_value!=nullptr);
    for (int i = 0; i < size; i++) {
        edge_value[i] = new(std::nothrow) double[size];
        assert(edge_value[i]!=nullptr);
    }
    // Initialize adjacency matrix
    InitialEdgeValue();

    min_span_tree.Initial(size);
    hash_table=std::unordered_map<T, int>();
}

/***********************************************************
* Function Name: MakeEmpty
* Function:     清空图的所有数据并释放内存。
***********************************************************/
template<typename T>
void Graph<T>::MakeEmpty()
{
    if (dots != nullptr) {
        delete[] dots;
        dots = nullptr;
    }
    if (edge_value != nullptr) {
        for (int i = 0; i < size; i++)
            delete[] edge_value[i];
        delete[] edge_value;
        edge_value = nullptr;
    }
    size = n = 0;
}

/***********************************************************
* Function Name:    FindDot
* Function:         检查给定的顶点是否已存在于图中。
* Input Parameter: dot - 要检查的顶点。
* Returned Value:  如果顶点存在，返回 true；否则返回 false。
***********************************************************/
template<typename T>
bool Graph<T>::FindDot(const T &dot)
{
    for (int i = 0; i < n; i++)
        if (dots[i] == dot)
            return true;
    return false;
}

/***********************************************************
* Function Name:   SetDot
* Function:        向图中添加一个顶点。
* Input Parameter: dot - 要添加的顶点。
***********************************************************/
template<typename T>
void Graph<T>::SetDot(const T &dot)
{
    if (FindDot(dot))
        return;
    if (!hash_table.contains(dot))
        hash_table[dot] = n;
    dots[n] = dot;
    n++;
}

/***********************************************************
* Function Name:    SetEdgeValue
* Function:         设置图中两顶点之间的边权重。
* Input Parameters: start - 边的起点。
*                   end - 边的终点。
*                   value - 边的权重值。
***********************************************************/
template<typename T>
void Graph<T>::SetEdgeValue(T start, T end, double value)
{
    edge_value[hash_table[start]][hash_table[end]] = value;
    edge_value[hash_table[end]][hash_table[start]] = value;
}

/***********************************************************
* Function Name:    Prim
* Function:        使用 Prim 算法构建图的最小生成树。
* Input Parameter: start - 最小生成树构建的起点。
* Returned Value:  如果最小生成树成功构建，返回 true；否则返回 false。
***********************************************************/
template<typename T>
bool Graph<T>::Prim(T start)
{
    assert(n==size); // 确保图中顶点数与声明的大小一致

    double *low_cost = new(std::nothrow) double[size]; // 存储当前前顶点到每个顶点的最小边权值
    assert(low_cost!=nullptr);
    int *near_vex = new(std::nothrow) int[size]; // 存储与当前顶点连接的最近顶点索引
    assert(near_vex!=nullptr);

    // 初始化辅助数组
    for (int i = 0; i < size; i++) {
        low_cost[i] = edge_value[hash_table[start]][i];
        near_vex[i] = hash_table[start];
    }

    near_vex[hash_table[start]] = -1; // 起点标记为已访问

    // Prim 算法的主循环
    for (int i = 1; i < size; i++) {
        double min = INF;
        int v = -1;

        // 找到当前未访问顶点中与已访问集合最近的顶点
        for (int j = 0; j < size; j++)
            if (near_vex[j] != -1 && low_cost[j] < min) {
                v = j;
                min = low_cost[j];
            }

        if (v == -1)
            break;
        // 如果找到有效的顶点，则将其加入最小生成树
        MSTEdgeNode<T> temp;
        temp.tail = dots[near_vex[v]];
        temp.head = dots[v];
        temp.key = low_cost[v];
        min_span_tree.Insert(temp);

        near_vex[v] = -1; // 标记顶点 v 为已访问

        // 更新与新加入顶点连接的边的权值
        for (int j = 0; j < size; j++)
            if (near_vex[j] != -1 && edge_value[v][j] < low_cost[j]) {
                low_cost[j] = edge_value[v][j];
                near_vex[j] = v;
            }
    }

    // 释放辅助数组内存
    delete[] low_cost;
    delete[] near_vex;
    return min_span_tree.BuildSuccess(); // 检查最小生成树是否构建完成
}

/***********************************************************
* Function Name:    InitialEdgeValue
* Function:        初始化邻接矩阵
* Input Parameter: None
* Returned Value:  None
***********************************************************/
template<typename T>
void Graph<T>::InitialEdgeValue()
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            edge_value[i][j] = (i == j) ? 0 : INF;
}


/***********************************************************
* Function Name: InputNum
* Function:        输入图的顶点数和边数。
*                  验证输入的合法性，确保用户输入的是正整数。
*                  输入 "0 0" 结束函数，返回 false。
* Parameters:      int& num_vertices - 图的顶点数目（输出参数）
*                  int& num_edges - 图的边数目（输出参数）
* Returned Value:  如果用户输入合法且非 "0 0"，返回 `true`；如果输入为 "0 0"，返回 `false`。
***********************************************************/
bool InputNum(int &num_vertices,int& num_edges)
{
    double temp_v, temp_e;
    while (true) {
        std::cout << "请输入所求图的顶点数目和边的数目(以空格分隔各个数，输入两个0结束):\n";
        std::cin >> temp_v >> temp_e;
        if (std::cin.fail()) {
            std::cout<<"输入非法字符，请重新输入！\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
            continue;
        }
        // 如果用户输入了 "0 0"，则结束输入并返回 false
        if (temp_v == 0 && temp_e == 0)
            return false;
        if ( temp_e <= 0 || temp_v <= 0 || temp_v != static_cast<int>(temp_v) || temp_e != static_cast<int>(temp_e)) {
            std::cout << "输入非法，请重新输入！\n";
            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
            continue;
        }
        if (temp_e >temp_v * (temp_v - 1) / 2) {
            std::cout<<"边数大于构成完全图需要的数目，请重新输入！\n";
            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<int>::max(), '\n');// 清除输入流中的无效数据
        break;
    }
    // 将临时变量的值转换为整数并存储到输出参数中
    num_vertices=static_cast<int>(temp_v);
    num_edges=static_cast<int>(temp_e);
    return true;
}

/***********************************************************
* Function Name: Input
* Function:        从用户输入图的边数据并存储到图中。
*                  验证输入的合法性，确保每条边的节点编号和权值都符合要求。
* Parameters:      Graph<int>& graph - 图对象，存储边的数据。
*                  const int num_vertices - 图的顶点数。
*                  const int num_edges - 图的边数。
***********************************************************/
void Input(Graph<int>& graph, const int num_vertices,const int num_edges)
{
    double start,end;
    double value;
    std::vector<std::vector<bool>> has_set(num_vertices+1, std::vector<bool>(num_vertices+1, false));// 存储边是否已设置
    bool true_input=true;;// 标记输入是否合法，默认为合法
    std::cout<<"请输入边的两个节点序号[1-"<< num_vertices <<"]以及它们的权值(0~"<<INF <<") (以空格分隔各个数)\n";
    for (int i = 0; i < num_edges; i++) {
        std::cin >> start >> end >> value;

        // 检查是否输入非法字符
        if (std::cin.fail()) {
            std::cout << "第" << i + 1 << "行输入非法字符!\n";
            true_input=false;
        }
        else if (start <=0||start>num_vertices||start!=static_cast<int>(start)) {
            std::cout << "第" << i + 1 << "行第一个顶点输入不符合要求!\n";
            true_input = false;
        }
        else if (end <=0||end>num_vertices||end!=static_cast<int>(end)) {
            std::cout<< "第" << i + 1 << "行第二个顶点输入不符合要求!\n";
            true_input = false;
        }
        // 检查两个顶点是否相同，即图中不能有环
        else if (start == end) {
            std::cout<<"第" << i + 1 << "行两个顶点相同!\n";
            true_input = false;
        }
        // 检查边是否已经存在
        else if (has_set[static_cast<int>(start)][static_cast<int>(end)]) {
            std::cout<<"第" << i + 1 << "行中，顶点"<< static_cast<int>(start)<<"与顶点"<<static_cast<int>(end) <<"之间已经存在边!\n";
            true_input = false;
        }
        else if (value>=INF||value<=0) {
            std::cout<<"第" << i + 1 << "行边的权值不在规定范围!\n";
            true_input = false;
        }
        if (!true_input) {
            std::cout<<"请从第" << i + 1 << "行开始重新输入!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
            true_input=true;
            i--;
            continue;
        }

        // 如果输入合法，则将边的数值设置到图中，并标记这条边已经存在
        graph.SetEdgeValue(static_cast<int>(start), static_cast<int>(end), value);
        has_set[static_cast<int>(start)][static_cast<int>(end)] = true;
        has_set[static_cast<int>(end)][static_cast<int>(start)] = true;

    }
    std::cin.ignore(std::numeric_limits<int>::max(), '\n');
}

/***********************************************************
* Function Name:  Print
* Function:        打印最小生成树中的所有边及其总耗费。
* Parameters:      const MinSpanTree<int>& result - 传入的最小生成树对象。
***********************************************************/
void Print(const MinSpanTree<int>&result)
{
    double total_cost=0;
    for (int i=0;i<result.GetSize();i++) {
        std::cout<<"最小耗费是："<<result.edge_value[i].tail<<"和"<<result.edge_value[i].head<<"\n";
        total_cost+=result.edge_value[i].key;
    }
    std::cout<<"总耗费为："<<total_cost<<"(万元)\n";
}

/***********************************************************
* Function Name:   main
* Function:        主函数，程序入口，负责执行最小生成树的构建和展示。
* Description:     该函数是程序的主入口，负责循环执行以下功能：
*                  1. 用户输入图的顶点数和边数
*                  2. 输入图的边信息
*                  3. 使用 Prim 算法构建最小生成树（MST）
*                  4. 打印最小生成树的边信息和总耗费
*                  5. 如果图不连通，输出错误信息
*                  6. 提供用户选择是否继续运行程序的功能
***********************************************************/
int main()
{
    // 输出程序标语
    while (true) {
        system("cls");
        std::cout << "*****************************\n" //标语
                  << "**                         **\n"
                  << "**        最小生成树       **\n"
                  << "**                         **\n"
                  << "*****************************\n\n\n";

        int num_vertices, num_edges;
        const bool if_continue = InputNum(num_vertices, num_edges);
        if (!if_continue)
            break;;

        // 创建图对象，初始化顶点
        Graph<int> graph(num_vertices);
        for (int i = 1; i <= num_vertices; i++)
            graph.SetDot(i);

        // 输入图的边的信息（节点序号和权值）
        Input(graph, num_vertices, num_edges);

        std::cout<<"开始构建最小生成树...\n\n";
        if (graph.Prim(1)) {
            std::cout<<"最小生成树构建成功！\n\n开始打印最小生成树...\n";

            // 获取最小生成树结果并打印
            MinSpanTree<int> result= graph.GetMST();
            Print(result);
        }
        else {
            std::cout << "最小生成树构建失败，请确保图连通!\n\n";
        }
        std::cout<<"\n\nPress any key to continue...\n";
        _getch();// 等待用户输入，按任意键继续
    }

    std::cout << "\n欢迎下次使用! \n";
    return 0;

}