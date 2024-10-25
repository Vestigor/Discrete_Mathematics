/***********************************************************
* File:     DiscreteMathematics_3
* Author:   Xiaolong Ma(��С��)
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
* Function:        ����������еĻ���������ֹ�Ƿ������Ӱ���������
* Input Parameter: ��
* Returned Value:  ��
***********************************************************/
void ClearBuffer()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/***********************************************************
* Function Name:   OutputMatrix
* Function:        �����ǰ�Ĺ�ϵ����
* Input Parameter: matrix - ��ϵ����, n - �����ά��
* Returned Value:  ��
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
* Function:        ʵ��Warshall�㷨�������ϵ�Ĵ��ݱհ�
* Input Parameter: tmatrix - ����Ĺ�ϵ����, n - �����ά��
* Returned Value:  ��
***********************************************************/
void Transitive(std::vector<std::vector<int>>& tmatrix, const int n)
{
	// ͨ��Warshall�㷨���д��ݱհ�����
	for (int k = 0; k < n; k++)         // ���������м��k
		for (int i = 0; i < n; i++)     // �������i
			for (int j = 0; j < n; j++) // �����յ�j
				// ���i->k��k->j����·������i->jҲ����·��
				tmatrix[i][j] = ((tmatrix[i][j] || (tmatrix[i][k] && tmatrix[k][j])) ? 1 : 0);
}

/***********************************************************
* Function Name:   TransitiveClosure
* Function:        ���������ϵ���󲢵��ô��ݱհ��㷨
* Input Parameter: ��
* Returned Value:  ��
***********************************************************/
void TransitiveClosure()
{
	// ����������
	std::cout << ("*****************************************\n") //����
		      << ("**                                     **\n")
		      << ("**        WarShall�㷨�󴫵ݱհ�       **\n")
		      << ("**                                     **\n")
		      << ("*****************************************\n\n\n");
	int n;
	while (true) {
		std::cout << "������ǿռ���A��Ԫ�ظ�����\n";
		std::cin >> n;
		if (std::cin.fail() || n < 0) {
			std::cout << "�����������������룡\n\n";
			ClearBuffer();
			continue;
		}
		ClearBuffer();
		break;
	}

	// ��ʼ����ϵ���󲢴��û�����
	std::vector<std::vector<int>> matrix(n, std::vector<int>(n));//���ö�̬�ڴ洢���ϵ����
	for (int i = 0; i < n; i++) {
		std::cout << "���������ĵ�" << i << "��Ԫ�أ�Ԫ���Կո�ֿ�,ֻ������0��1����\n";
		for (int j = 0; j < n; j++) {
			int temp;
			std::cin >> temp;
			if (std::cin.fail() || temp > 1 || temp < 0) {
				std::cout << "��" << i << "�������������������룡\n";
				ClearBuffer();
				j = -1;
				continue;
			}
			matrix[i][j] = temp;
		}
		ClearBuffer();
	}
	// ���㴫�ݱհ�
	std::vector<std::vector<int>> tmatrix = matrix;
	Transitive(tmatrix, n);

	// ������ݱհ�����
	std::cout << "\n���󴫵ݱհ�Ϊ��\n";
	OutputMatrix(tmatrix, n);
}

int main()
{
	char ret = 0;
	// ѭ��ѯ���û��Ƿ��������
	while (ret!='n') {
		system("cls");//����
		TransitiveClosure();
		while (1) {
			std::cout << "\n\n�Ƿ��������?��y/n��"; //ѯ���Ƿ��������
			std::cin >> ret;
			std::cout << "\n";
			if (std::cin.fail() || (ret != 'y' && ret != 'n')) {
				std::cout << "������������������\n";//����У��
				//���������
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
			//���������
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		}
	}
	std::cout << "\n��ӭ�´�ʹ��! \n";

	return 0;
}