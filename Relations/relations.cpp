/***********************************************************
* File:     relations.cpp
* Author:   Xiaolong Ma(马小龙)
* E-mail:   2353814@tongji.edu.cn
* Function: Reflexive, symmetric and transitive closure of relations
* Encoding: UTF-8
* Date:     2024.10.13
* Update:   2024.11.27
***********************************************************/

#include <iostream>
#include <limits>
#include <vector>
#include <conio.h>

/***********************************************************
* Function Name:   ClearBuffer
* Function:        清除输入缓冲区，防止无效输入影响后续操作
* Input Parameter: None
* Returned Value:  None
***********************************************************/
void ClearBuffer()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/***********************************************************
* Function Name:   Select
* Function:        提供用户选择操作的选项，输入序号选择不同算法
* Input Parameter: None
* Returned Value:  用户选择的序号
***********************************************************/
int Select()
{
	double select;
	while (true) {
		std::cout << "\n输入对应序号选择算法 [0]:退出程序 [l]:自反闭包 [2]:传递闭包 [3]:对称闭包 [4]:重新定义关系矩阵\n";
		std::cin >> select;
		if (std::cin.fail() || select > 4 || select < 0||select!=static_cast<int>(select)) {
			std::cout << "输入有误，请重新输入！\n\n";
			ClearBuffer();
			continue;
		}
		ClearBuffer();
		break;
	}
	return static_cast<int>(select);
}

/***********************************************************
* Function Name:   OutputMatrix
* Function:        输出矩阵结果
* Input Parameter: const std::vector<std::vector<int>>& matrix：关系矩阵
*                  const int n：矩阵维数
* Returned Value:  None
***********************************************************/
void OutputMatrix(const std::vector<std::vector<int>>& matrix, const int n,const char* prompt)
{
	std::cout << prompt;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (j!=0)
				std::cout << " ";
			std::cout << matrix[i][j];
		}

		std::cout << "\n";
	}	
}

/***********************************************************
* Function Name:   Reflexive
* Function:        计算并生成自反闭包
* Input Parameter: std::vector<std::vector<int>>& r_matrix：自反闭包
*                  const int n：矩阵维数
* Returned Value:  None
***********************************************************/
void Reflexive(std::vector<std::vector<int>>& r_matrix, const int n)
{
	for (int i = 0; i < n; i++)
		r_matrix[i][i] = 1;
}

/***********************************************************
* Function Name:   Symmetric
* Function:        计算并生成对称闭包
* Input Parameter: std::vector<std::vector<int>>& s_matrix：对称闭包
*                  const int n：矩阵维数
* Returned Value:  None
***********************************************************/
void Symmetric(std::vector<std::vector<int>>& s_matrix, const int n)
{
	// 生成矩阵的转置矩阵
	std::vector<std::vector<int>> transpose(n, std::vector<int>(n));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			transpose[j][i] = s_matrix[i][j];
	// 将原矩阵与转置矩阵求并集
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			s_matrix[i][j] = s_matrix[i][j] + transpose[i][j] >= 1 ? 1 : 0;
}

/***********************************************************
* Function Name:   Transitive
* Function:        计算并生成传递闭包
* Input Parameter: std::vector<std::vector<int>>& t_matrix：传递闭包
*                  const int n：矩阵维数
* Returned Value:  None
***********************************************************/
void Transitive(std::vector<std::vector<int>>& t_matrix, const int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (t_matrix[j][i] != 0)
				for (int k = 0; k < n; k++)
					t_matrix[j][k] = t_matrix[j][k] + t_matrix[i][k] >= 1 ? 1 : 0;

}

/***********************************************************
* Function Name:   Relations
* Function:        用户界面和矩阵输入及操作选择流程
* Input Parameter: None
* Returned Value:  None
***********************************************************/
bool Relations()
{
	// 输出程序标语
	std::cout << ("*********************************************\n") //标语
		      << ("**                                         **\n")
		      << ("**        关系的自反、对称、传递闭包       **\n")
		      << ("**                                         **\n")
		      << ("*********************************************\n\n\n");
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
	std::vector<std::vector<int>> matrix(n, std::vector<int>(n));//利用动态内存储存关系矩阵
	for (int i = 0; i < n; i++) {
		std::cout << "请输入矩阵的第" << i << "行元素（元素以空格分开,只能输入0或1）：\n";
		for (int j = 0; j < n; j++) {
			double temp;
			std::cin >> temp;
			if (std::cin.fail() || temp !=1 &&temp != 0) {
				std::cout << "第" << i << "行输入有误，请重新输入这一行！\n";
				ClearBuffer();
				j = -1;
				continue;
			}
			matrix[i][j] = static_cast<int>(temp);
		}
		ClearBuffer();
	}

	OutputMatrix(matrix, n, "\n输入的关系矩阵为：\n");

	// 根据用户选择执行不同的闭包操作
	while (true) {
		std::vector<std::vector<int>> c_matrix = matrix;
		int select = Select();
		switch (select) {
			case 1:
				Reflexive(c_matrix, n);
			    OutputMatrix(c_matrix,n,"\n所求自反闭包为：\n");
			break;
			case 2:
				Transitive(c_matrix, n);
			    OutputMatrix(c_matrix, n,"\n所求传递闭包为：\n");
			break;
			case 3:
				Symmetric(c_matrix, n);
			    OutputMatrix(c_matrix, n,"\n所求对称闭包为：\n");
			break;
			case 4:
				return true;
			case 0:
				default:
					std::cout << "欢迎下次再次使用!\n";
			return false;
		}
	}
	
}

/***********************************************************
* Function Name:   main
* Function:        通过调用Relations函数，实现与用户的交互
* Input Parameter: None
* Returned Value:  0
***********************************************************/
int main()
{
	do {
		system("cls"); //清屏
	}while (Relations());

	return 0;
}