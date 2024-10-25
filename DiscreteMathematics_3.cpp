/***********************************************************
* File:     DiscreteMathematics_3
* Author:   Xiaolong Ma(马小龙)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Visual Studio 2022
* Function: Reflexive, symmetric and transitive closure of relations
* Date:     2024.10.13
* Update:   2024.10.19
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
	int select;
	while (true) {
		std::cout << "\n输入对应序号选择算法\n0:退出程序\nl:自反闭包\n2:传递闭包\n3:对称闭包\n4:重新定义关系矩阵\n";
		std::cin >> select;
		if (std::cin.fail() || select > 4 || select < 0) {
			std::cout << "输入有误，请重新输入！\n\n";
			ClearBuffer();
			continue;
		}
		ClearBuffer();
		break;
	}
	return select;
}

/***********************************************************
* Function Name:   OutputMatrix
* Function:        输出矩阵结果
* Input Parameter: const std::vector<std::vector<int>>& matrix：关系矩阵
*                  const int n：矩阵维数
* Returned Value:  None
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
* Function Name:   Reflexive
* Function:        计算并生成自反闭包
* Input Parameter: std::vector<std::vector<int>>& rmatrix：自反闭包
*                  const int n：矩阵维数
* Returned Value:  None
***********************************************************/
void Reflexive(std::vector<std::vector<int>>& rmatrix, const int n)
{
	for (int i = 0; i < n; i++)
		rmatrix[i][i] = 1;
}

/***********************************************************
* Function Name:   Symmetric
* Function:        计算并生成对称闭包
* Input Parameter: std::vector<std::vector<int>>& smatrix：对称闭包
*                  const int n：矩阵维数
* Returned Value:  None
***********************************************************/
void Symmetric(std::vector<std::vector<int>>& smatrix, const int n)
{
	// 生成矩阵的转置矩阵
	std::vector<std::vector<int>> transpose(n, std::vector<int>(n));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			transpose[j][i] = smatrix[i][j];
	// 将原矩阵与转置矩阵求并集
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			smatrix[i][j] = smatrix[i][j] + transpose[i][j] >= 1 ? 1 : 0;
}

/***********************************************************
* Function Name:   Transitive
* Function:        计算并生成传递闭包
* Input Parameter: std::vector<std::vector<int>>& tmatrix：传递闭包
*                  const int n：矩阵维数
* Returned Value:  None
***********************************************************/
void Transitive(std::vector<std::vector<int>>& tmatrix, const int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (tmatrix[j][i] != 0)
				for (int k = 0; k < n; k++)
					tmatrix[j][k] = tmatrix[j][k] + tmatrix[i][k] >= 1 ? 1 : 0;

}

/***********************************************************
* Function Name:   Relations
* Function:        用户界面和矩阵输入及操作选择流程
* Input Parameter: None
* Returned Value:  None
***********************************************************/
void Relations()
{
	// 输出程序标语
	std::cout << ("*********************************************\n") //标语
		      << ("**                                         **\n")
		      << ("**        关系的自反、对称、传递闭包       **\n")
		      << ("**                                         **\n")
		      << ("*********************************************\n\n\n");
	// 输入关系矩阵的维度
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

	// 输入关系矩阵的初始元素
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

	// 根据用户选择执行不同的闭包操作
	while (true) {
		std::vector<std::vector<int>> cmatrix = matrix;
		int select = Select();
		switch (select) {
			case 1:
				Reflexive(cmatrix, n);
				std::cout << "\n所求自反闭包为：\n";
				OutputMatrix(cmatrix, n);
				break;
			case 2:
				Transitive(cmatrix, n);
				std::cout << "\n所求传递闭包为：\n";
				OutputMatrix(cmatrix, n);
				break;
			case 3:
				Symmetric(cmatrix, n);
				std::cout << "\n所求对称闭包为：\n";
				OutputMatrix(cmatrix, n);
				break;

			case 0:
				std::cout << "欢迎下次再次使用!\n";
				exit(1);
		}
		if (Select() == 4)
			break;
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
	while (true) {
			system("cls");//清屏
		Relations();
	}

	return 0;
}