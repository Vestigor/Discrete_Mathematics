/***********************************************************
* File:     DiscreteMathematics_3
* Author:   Xiaolong Ma(��С��)
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
* Function:        ������뻺��������ֹ��Ч����Ӱ���������
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
* Function:        �ṩ�û�ѡ�������ѡ��������ѡ��ͬ�㷨
* Input Parameter: None
* Returned Value:  �û�ѡ������
***********************************************************/
int Select()
{
	int select;
	while (true) {
		std::cout << "\n�����Ӧ���ѡ���㷨\n0:�˳�����\nl:�Է��հ�\n2:���ݱհ�\n3:�ԳƱհ�\n4:���¶����ϵ����\n";
		std::cin >> select;
		if (std::cin.fail() || select > 4 || select < 0) {
			std::cout << "�����������������룡\n\n";
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
* Function:        ���������
* Input Parameter: const std::vector<std::vector<int>>& matrix����ϵ����
*                  const int n������ά��
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
* Function:        ���㲢�����Է��հ�
* Input Parameter: std::vector<std::vector<int>>& rmatrix���Է��հ�
*                  const int n������ά��
* Returned Value:  None
***********************************************************/
void Reflexive(std::vector<std::vector<int>>& rmatrix, const int n)
{
	for (int i = 0; i < n; i++)
		rmatrix[i][i] = 1;
}

/***********************************************************
* Function Name:   Symmetric
* Function:        ���㲢���ɶԳƱհ�
* Input Parameter: std::vector<std::vector<int>>& smatrix���ԳƱհ�
*                  const int n������ά��
* Returned Value:  None
***********************************************************/
void Symmetric(std::vector<std::vector<int>>& smatrix, const int n)
{
	// ���ɾ����ת�þ���
	std::vector<std::vector<int>> transpose(n, std::vector<int>(n));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			transpose[j][i] = smatrix[i][j];
	// ��ԭ������ת�þ����󲢼�
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			smatrix[i][j] = smatrix[i][j] + transpose[i][j] >= 1 ? 1 : 0;
}

/***********************************************************
* Function Name:   Transitive
* Function:        ���㲢���ɴ��ݱհ�
* Input Parameter: std::vector<std::vector<int>>& tmatrix�����ݱհ�
*                  const int n������ά��
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
* Function:        �û�����;������뼰����ѡ������
* Input Parameter: None
* Returned Value:  None
***********************************************************/
void Relations()
{
	// ����������
	std::cout << ("*********************************************\n") //����
		      << ("**                                         **\n")
		      << ("**        ��ϵ���Է����Գơ����ݱհ�       **\n")
		      << ("**                                         **\n")
		      << ("*********************************************\n\n\n");
	// �����ϵ�����ά��
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

	// �����ϵ����ĳ�ʼԪ��
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

	// �����û�ѡ��ִ�в�ͬ�ıհ�����
	while (true) {
		std::vector<std::vector<int>> cmatrix = matrix;
		int select = Select();
		switch (select) {
			case 1:
				Reflexive(cmatrix, n);
				std::cout << "\n�����Է��հ�Ϊ��\n";
				OutputMatrix(cmatrix, n);
				break;
			case 2:
				Transitive(cmatrix, n);
				std::cout << "\n���󴫵ݱհ�Ϊ��\n";
				OutputMatrix(cmatrix, n);
				break;
			case 3:
				Symmetric(cmatrix, n);
				std::cout << "\n����ԳƱհ�Ϊ��\n";
				OutputMatrix(cmatrix, n);
				break;

			case 0:
				std::cout << "��ӭ�´��ٴ�ʹ��!\n";
				exit(1);
		}
		if (Select() == 4)
			break;
	}
	
}

/***********************************************************
* Function Name:   main
* Function:        ͨ������Relations������ʵ�����û��Ľ���
* Input Parameter: None
* Returned Value:  0
***********************************************************/
int main()
{
	while (true) {
			system("cls");//����
		Relations();
	}

	return 0;
}