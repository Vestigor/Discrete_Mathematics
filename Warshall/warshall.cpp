/***********************************************************
* File:     DiscreteMathematics_3
* Author:   Xiaolong Ma(马小龙)
* E-mail:   2353814@tongji.edu.cn
* Function: Use the algorithm of Warshall to find transitive closure of relations
* Encoding: UTF-8
* Date:     2024.10.13
* Update:   2024.10.13
***********************************************************/

#include <conio.h>
#include <iostream>
#include <limits>
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
void OutputMatrix(const std::vector<std::vector<bool>>& matrix, const int n,const char *prompt)
{
	std::cout << prompt;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (j!=0)
				std::cout << ' ';
			std::cout << matrix[i][j];
		}

		std::cout << "\n";
	}
}

/***********************************************************
* Function Name:   Transitive
* Function:        实现Warshall算法，计算关系的传递闭包
* Input Parameter: t_matrix - 输入的关系矩阵, n - 矩阵的维度
* Returned Value:  无
***********************************************************/
void Transitive(std::vector<std::vector<bool>>& t_matrix, const int n)
{
	// 通过Warshall算法进行传递闭包计算
	for (int k = 0; k < n; k++)         // 遍历所有中间点k
		for (int i = 0; i < n; i++)     // 遍历起点i
			for (int j = 0; j < n; j++) // 遍历终点j
				// 如果i->k和k->j存在路径，则i->j也存在路径
				t_matrix[i][j] = ((t_matrix[i][j] || (t_matrix[i][k] && t_matrix[k][j])) ? 1 : 0);
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
	// 输入关系矩阵的维度
	double dN;
	while (true) {
		std::cout << "请输入非空集合A的元素个数：\n";
		std::cin >> dN;
		if (std::cin.fail() || dN <= 0||dN!=static_cast<int>(dN)) {
			std::cout << "输入有误，请重新输入！\n\n";
			ClearBuffer();
			continue;
		}
		ClearBuffer();
		break;
	}
	const int n=static_cast<int>(dN);


	// 输入关系矩阵的初始元素
	std::vector<std::vector<bool>> matrix(n, std::vector<bool>(n));//利用动态内存储存关系矩阵
	for (int i = 0; i < n; i++) {
		std::cout << "请输入矩阵的第" << i << "行元素（元素以空格分开,只能输入0或1）：\n";
		for (int j = 0; j < n; j++) {
			double temp;
			std::cin >> temp;
			if (std::cin.fail() || temp !=1 &&temp != 0) {
				std::cout << "第" << i << "行输入有误，请重新输入！\n";
				ClearBuffer();
				j = -1;
				continue;
			}
			matrix[i][j] = static_cast<bool>(temp);
		}
		ClearBuffer();
	}

	OutputMatrix(matrix, n, "\n输入的关系矩阵为：\n");

	// 计算传递闭包
	std::vector<std::vector<bool>> t_matrix = matrix;
	Transitive(t_matrix, n);

	// 输出传递闭包矩阵
	OutputMatrix(t_matrix, n,"\n所求传递闭包为：\n");
}

int main()
{
	while (true) {
		system("cls");//清屏
		TransitiveClosure();
		// 提示用户是否继续执行程序
		std::cout << "\n是否继续执行程序？[Y/n] ";
		char ch;
		do {
			ch = static_cast<char>(_getch());
		} while (ch != 'Y' && ch != 'y' && ch != 'N' && ch != 'n');
		std::cout << ch << '\n';

		// 如果用户输入 N 或 n，则退出循环，结束程序
		if (ch == 'N' || ch == 'n')
			break;
	}

	std::cout << "\n欢迎下次使用! \n";

	return 0;
}
