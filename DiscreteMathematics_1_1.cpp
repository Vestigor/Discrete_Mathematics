/***********************************************************
* File:     DiscreteMathematics_1_1.cpp
* Author:   Xiaolong Ma(��С��)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Visual Studio 2022
* Function: question A of propositional logic connective, truth table, main normal form
* Date:     2024.9.17
* Update:   2024.9.17
***********************************************************/

#include <cstdlib>
#include <iostream>
#include <limits>

/***********************************************************
* Function Name:   main
* Function:        ���������������ֵ�����������롢���̺���˫�̺����ɵ��������ֵ
* Input Parameter:
* Returned Value:  0
***********************************************************/
int main()
{
    bool p, q;
    char ret = 0;
    while (ret != 'n') {
        if (ret == 'y')
            system("cls");//����
        std::cout << ("***************************************\n") //����
                  << ("**                                   **\n")
                  << ("**        ��ӭ�����߼��������       **\n")
                  << ("**                                   **\n")
                  << ("***************************************\n\n\n");
        while (1) {
            std::cout << "  ������p��ֵ��0��1�����Իس�������";
            std::cin >> p;//��ȡP��ֵ
            std::cout << "\n";
            if (std::cin.fail()) {
                std::cout << "  pֵ������������������\n";
                // ���������
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            // ���������
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        while (1) {
            std::cout << "  ������q��ֵ��0��1�����Իس�������";
            std::cin >> q;//��ȡQ��ֵ
            std::cout << "\n";
            if (std::cin.fail()) {
                std::cout << "  qֵ������������������\n";
                // ���������
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            // ���������
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        std::cout << "  �����㣺\n" << "        p��q=" << (p && q) << "\n";//������ͬʱ������
        std::cout << "  �����㣺\n" << "        p��q=" << (p || q) << "\n"; //������ͬʱ������
        std::cout << "  �̺����㣺\n" << "        p��q=" << (!p || q) << "\n"; //�̺����㣬����ת��Ϊ������ʽͬʱ������
        std::cout << "  ˫�̺����㣺\n" << "        p?q=" << ((!p || q) && (p || !q)) << "\n";//�ȼ����㣬����ת��Ϊ������ʽͬʱ������
        while (1) {
            std::cout << "  �Ƿ�������㣿(y/n)��"; //ѯ���Ƿ��������
            std::cin >> ret;
            std::cout << "\n";
            if (std::cin.fail() || (ret != 'y' && ret != 'n')) {
                std::cout << "  ������������������\n";//����У��
                // ���������
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            // ���������
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
    std::cout << "��ӭ�´��ٴ�ʹ��!\n";

    return 0;
}
