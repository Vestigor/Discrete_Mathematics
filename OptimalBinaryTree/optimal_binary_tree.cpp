/***********************************************************
* File:     optimal_binary_tree.cpp
* Author:   Xiaolong Ma(马小龙)
* E-mail:   2353814@tongji.edu.cn
* Function: Construct the Huffman Tree (Optimal Binary Tree) and Generate Prefix Codes
* Encoding: UTF-8
* Date:     2024.11.27
* Update:   2024.11.30
***********************************************************/
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <conio.h>

/***********************************************************
* Struct: TreeNode
* Function: 表示哈夫曼树的节点，每个节点包含两个值和两个子节点指针。
***********************************************************/
struct TreeNode {
    std::string name;
    int value;// 节点的值
    TreeNode *left;// 左子节点指针
    TreeNode *right;// 右子节点指针
    TreeNode(std::string n,int x,TreeNode*l=nullptr,TreeNode *r=nullptr ) : name(n),value(x), left(l), right(r) {}
};

/***********************************************************
* Struct: Compare
* Function: 用于优先队列中比较两个节点的值，构建最小堆。
***********************************************************/
struct Compare {
    // 比较节点的值，值较小的优先
    bool operator()(const TreeNode * a, const TreeNode * b) const { return a->value > b->value; }
};

/***********************************************************
* Class: HuffmanTree
* Function: 管理哈夫曼树的构建及生成前缀编码。
***********************************************************/
class HuffmanTree {
public:
    HuffmanTree(){root=nullptr;}
    ~HuffmanTree(){Destroy(root);}// 析构函数，释放内存
    void BuildHuffmanTree(const std::vector<std::string>&names,const std::vector<int>& v);// 构建哈夫曼树
    void GeneratePrefixCode(){GeneratePrefixCodePrivate(root,"");} // 生成前缀编码
    std::unordered_map<std::string, std::string> GetPrefixCode(){return prefix_code;}
private:
    TreeNode *root; // 哈夫曼树的根节点
    std::unordered_map<std::string,std::string> prefix_code;// 存储前缀编码的映射
    void Destroy(TreeNode * subTree);
    void GeneratePrefixCodePrivate(TreeNode *subTree, const std::string& prefix);
};

/***********************************************************
* Function Name: Destroy
* Function: 销毁哈夫曼树的所有节点并释放内存。
* Input Parameter: subTree - 当前递归处理的子树根节点。
***********************************************************/
void HuffmanTree::Destroy(TreeNode *subTree)
{
    if(subTree==nullptr)
        return;
    Destroy(subTree->left);
    Destroy(subTree->right);
    delete subTree;
    subTree=nullptr;
}

/***********************************************************
* Function Name: BuildHuffmanTree
* Function: 根据节点权重构建哈夫曼树，使用最小堆来选择最小的两个节点。
* Input Parameter: names - 存储节点名称的数组。
*                  v - 存储节点权重的数组。
***********************************************************/
void HuffmanTree::BuildHuffmanTree(const std::vector<std::string> &names,const std::vector<int> &v)
{
    std::priority_queue<TreeNode*,std::vector<TreeNode *>,Compare> pq;

    // 将每个节点加入优先队列
    for(size_t i=0;i<names.size();i++) {
        auto *node = new(std::nothrow) TreeNode(names[i],v[i]); // 创建节点
        assert(node!=nullptr);
        assert(node!=nullptr);
        pq.push(node); // 将节点推入优先队列
    }
    // 合并两个最小节点直到队列中只剩下一个节点
    while(pq.size()>1) {
        auto left = pq.top();// 获取最小的节点
        pq.pop();
        auto right = pq.top();// 获取第二小的节点
        pq.pop();
        auto *node = new(std::nothrow) TreeNode("",left->value+right->value,left,right);
        assert(node!=nullptr);
        pq.push(node);// 将新节点加入队列
    }
    root=pq.top();// 根节点是队列中剩余的唯一节点
    pq.pop();
}

/***********************************************************
* Function Name:   GeneratePrefixCodePrivate
* Function:        递归生成哈夫曼树的前缀编码。
* Input Parameter: subTree - 当前递归处理的子树根节点。
*                  prefix - 当前节点的前缀路径。
***********************************************************/
void HuffmanTree::GeneratePrefixCodePrivate(TreeNode* subTree,const std::string& prefix)
{
    if(subTree==nullptr)// 如果当前节点为空，返回
        return;
    // 叶子节点
    if(subTree->left==nullptr&&subTree->right==nullptr) {
        prefix_code[subTree->name]=prefix;// 将当前节点的前缀编码存入映射
        return;
    }
    // 递归处理左右子树，分别添加 '0' 和 '1' 到前缀中
    GeneratePrefixCodePrivate(subTree->left, prefix+"0");
    GeneratePrefixCodePrivate(subTree->right, prefix+"1");
}

/***********************************************************
* Function Name:    Input
* Function:        从用户输入获取节点的个数和权重。
* Input Parameter: names - 存储节点名称的数组。
*                  v - 存储节点权重的数组。
***********************************************************/
void Input (std::vector<std::string> &names,std::vector<int>&v)
{
    int N;
    while(true) {
        std::cout << "请输入节点的个数！\n";
        double dN;
        std::cin >> dN;
        if (std::cin.fail()|| dN != static_cast<int>(dN)||dN<=0) {
            std::cout<<"输入非法，请重新输入！\n";
            std::cin.clear();
            std::cin.ignore(INT_MAX,'\n');
            continue;
        }
        std::cin.ignore(INT_MAX,'\n');
        N=static_cast<int>(dN);
        break;
    }

    std::cout<<"请输入节点名称以及节点频率（用空格分离）\n";
    for(int i=0;i<N;i++) {
        std::string name;
        double element;
        std::cin >>name >> element;
        if (std::cin.fail() || element != static_cast<int>(element) || element <= 0) {
            std::cout << "输入非法，请从第"<<i+1<<"个元素开始继续输入！\n";
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            i--;
            continue;
        }
        bool is_continue=false;
        for (const auto& it:names)
            if (it==name) {
                std::cout << "符号名称重复，请从第" << i + 1 << "个元素开始继续输入！\n";
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                i--;
                is_continue=true;
            }
        if (is_continue)
            continue;
        names.push_back(name);
        v.push_back(static_cast<int>(element));
    }
}

/***********************************************************
* Function Name:   MaxElement
* Function:        获取数组中最大元素。
* Input Parameter: nums - 存储元素的数组。
* Returned Value:  返回数组中的最大元素。
***********************************************************/
int MaxElement(const std::vector<int> &nums)
{
    // 使用 std::max_element 获取最大元素的迭代器
    auto maxElementIt = std::max_element(nums.begin(), nums.end());
    return *maxElementIt; // 解引用迭代器获取最大元素的值
}

/***********************************************************
* Function Name:  countDigits
* Function:        计算数字的位数。
* Input Parameter:  num - 要计算位数的数字。
* Returned Value:  返回数字的位数。
***********************************************************/
int countDigits(const int num)
{
    // 将数字转换为字符串，然后返回字符串的长度（即位数）
    return static_cast<int>(std::to_string(num).length());
}

/***********************************************************
* Function Name:    MaxNameLength
* Function:        获取数组中的字符串的最大长度。
* Input Parameter: names - 存储元素的数组。
* Returned Value:  返回数组中的字符串的最大长度。
***********************************************************/
int MaxNameLength(const std::vector<std::string> &names)
{
    int max_length=0;
    for(const auto & name : names)
        max_length=static_cast<int>(name.size())>max_length?static_cast<int>(name.size()):max_length;
    return max_length;
}

/***********************************************************
* Function Name:   Print
* Function:        打印节点的频率和前缀编码。
* Input Parameter: names - 存储节点名称的数组
*                  nums - 存储节点频率的数组。
*                  prefix_code - 存储前缀编码的映射。
***********************************************************/
void Print(const std::vector<std::string>& names, const std::vector<int> &nums,std::unordered_map<std::string, std::string>& prefix_code)
{
    int max_length=MaxNameLength(names);
    int digit_count = countDigits(MaxElement(nums));
    int max_size = 0;
    for (const auto &it: prefix_code) {
        int size = static_cast<int>(it.second.size());
        max_size=size > max_size ? size : max_size;
    }
    const std::string symbol_name="Communication Symbol Name";
    const std::string fluency = "Usage Frequency";
    const std::string prefix = "Prefix Code";
    const int len0= max_length+2>static_cast<int>(symbol_name.size())?max_length+2:static_cast<int>(symbol_name.size());
    const int len1 = digit_count + 2 > static_cast<int>(fluency.size()) ? digit_count + 2 : static_cast<int>(fluency.size());
    const int len2 = max_size + 2 > static_cast<int>(prefix.size()) ? max_size + 2 : static_cast<int>(prefix.size());
    std::cout << std::setfill('-') << std::left;
    std::cout << "+" << std::setw(len0) << '-' << '+' << std::setw(len1) << '-' << '+' << std::setw(len2) << '-' << '+'<< '\n';
    std::cout << std::setfill(' ');
    std::cout << "|" << std::setw(len0) << symbol_name << '|'<< std::setw(len1) << fluency << '|' << std::setw(len2) << prefix<< "|\n";
    std::cout << std::setfill('-');
    std::cout << "+" << std::setw(len0) << '-'<< '+' << std::setw(len1) << '-' << '+' << std::setw(len2) << '-' << '+' <<'\n';

    for (size_t i =0;i<names.size();i++) {
        std::cout << std::setfill(' ');
        std::cout << '|' << std::setw(len0) << names[i] << '|'<<std::setw(len1) << nums[i] << '|' << std::setw(len2) << prefix_code[names[i]] << '|' << '\n';
        std::cout << std::setfill('-');
        std::cout << "+" << std::setw(len0) << '-' << '+' << std::setw(len1) << '-' << '+' << std::setw(len2) << '-' <<'+' << '\n';
    }
}

/***********************************************************
* Function Name: main
* Function: 主程序入口，控制哈夫曼树的构建和前缀编码生成过程。
*           提供用户交互界面，允许用户多次输入数据并查看结果。
***********************************************************/
int main()
{
    while (true) {
        system("cls");// 清屏，刷新界面
        std::cout << "*****************************\n" //标语
                  << "**                         **\n"
                  << "**        最优二元树       **\n"
                  << "**                         **\n"
                  << "*****************************\n\n";


        std::vector<int> v;
        std::vector<std::string> names;

        Input(names,v);
        // 创建一个 HuffmanTree 对象
        HuffmanTree huffmanTree;
        // 使用输入的节点数据构建哈夫曼树
        huffmanTree.BuildHuffmanTree(names,v);
        // 生成前缀编码
        huffmanTree.GeneratePrefixCode();
        // 获取生成的前缀编码
        std::unordered_map<std::string, std::string> prefix_code = huffmanTree.GetPrefixCode();
        // 打印节点的频率和对应的前缀编码
        Print(names,v, prefix_code);

        // 提示用户是否继续执行程序
        std::cout<<"是否继续执行程序？[Y/n] ";
        char ch;
        do {
            ch = static_cast<char>(_getch());
        }while (ch != 'Y' && ch != 'y' && ch != 'N' && ch != 'n');
        std::cout<<ch<<'\n';

        // 如果用户输入 N 或 n，则退出循环，结束程序
        if (ch == 'N' || ch == 'n')
            break;
    }

    std::cout << "\n欢迎下次使用! \n";
    return 0;
}