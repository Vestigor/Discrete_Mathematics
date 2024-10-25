/***********************************************************
* File:     DiscreteMathematics_3
* Author:   Xiaolong Ma(马小龙)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Visual Studio 2022
* Function: Use the algorithm of Warshall to find transitive closure of relations
* Date:     2024.10.13
* Update:   2024.10.13
***********************************************************/

#include <iostream>
#include <limits>
#include <conio.h>
#include <vector>

/***********************************************************
* Function Name:   ClearBuffer
* Function:        清除输入流中的缓冲区，防止非法输入后影响后续输入
* Input Parameter: 无
* Returned Value:  无
***********************************************************/
void ClearBuffer()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/***********************************************************
* Function Name:   OutputMatrix
* Function:        输出当前的关系矩阵
* Input Parameter: matrix - 关系矩阵, n - 矩阵的维度
* Returned Value:  无
***********************************************************/
void OutputMatrix(const std::vector<std::vector<int>>& matrix, const int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			std::cout << matrix[i][j];
		std::cout << "\n";
	}
}

/***********************************************************
* Function Name:   Transitive
* Function:        实现Warshall算法，计算关系的传递闭包
* Input Parameter: tmatrix - 输入的关系矩阵, n - 矩阵的维度
* Returned Value:  无
***********************************************************/
void Transitive(std::vector<std::vector<int>>& tmatrix, const int n)
{
	// 通过Warshall算法进行传递闭包计算
	for (int k = 0; k < n; k++)         // 遍历所有中间点k
		for (int i = 0; i < n; i++)     // 遍历起点i
			for (int j = 0; j < n; j++) // 遍历终点j
				// 如果i->k和k->j存在路径，则i->j也存在路径
				tmatrix[i][j] = ((tmatrix[i][j] || (tmatrix[i][k] && tmatrix[k][j])) ? 1 : 0);
}

/***********************************************************
* Function Name:   TransitiveClosure
* Function:        负责输入关系矩阵并调用传递闭包算法
* Input Parameter: 无
* Returned Value:  无
***********************************************************/
void TransitiveClosure()
{
	// 输出程序标语
	std::cout << ("*****************************************\n") //标语
		      << ("**                                     **\n")
		      << ("**        WarShall算法求传递闭包       **\n")
		      << ("**                                     **\n")
		      << ("*****************************************\n\n\n");
	int n;
	while (true) {
		std::cout << "请输入非空集合A的元素个数：\n";
		std::cin >> n;
		if (std::cin.fail() || n < 0) {
			std::cout << "输入有误，请重新输入！\n\n";
			ClearBuffer();
			continue;
		}
		ClearBuffer();
		break;
	}

	// 初始化关系矩阵并从用户输入
	std::vector<std::vector<int>> matrix(n, std::vector<int>(n));//利用动态内存储存关系矩阵
	for (int i = 0; i < n; i++) {
		std::cout << "请输入矩阵的第" << i << "行元素（元素以空格分开,只能输入0或1）：\n";
		for (int j = 0; j < n; j++) {
			int temp;
			std::cin >> temp;
			if (std::cin.fail() || temp > 1 || temp < 0) {
				std::cout << "第" << i << "行输入有误，请重新输入！\n";
				ClearBuffer();
				j = -1;
				continue;
			}
			matrix[i][j] = temp;
		}
		ClearBuffer();
	}
	// 计算传递闭包
	std::vector<std::vector<int>> tmatrix = matrix;
	Transitive(tmatrix, n);

	// 输出传递闭包矩阵
	std::cout << "\n所求传递闭包为：\n";
	OutputMatrix(tmatrix, n);
}

int main()
{
	char ret = 0;
	// 循环询问用户是否继续运算
	while (ret!='n') {
		system("cls");//清屏
		TransitiveClosure();
		while (1) {
			std::cout << "\n\n是否继续运算?（y/n）"; //询问是否继续操作
			std::cin >> ret;
			std::cout << "\n";
			if (std::cin.fail() || (ret != 'y' && ret != 'n')) {
				std::cout << "输入有误，请重新输入\n";//错误校验
				//清除缓冲区
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
			//清除缓冲区
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		}
	}
	std::cout << "\n欢迎下次使用! \n";

	return 0;
}