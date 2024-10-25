/***********************************************************
* File:     DiscreteMathematics_1_1.cpp
* Author:   Xiaolong Ma(马小龙)
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
* Function:        输入两个命题的真值，并计算由与、或、蕴涵和双蕴涵构成的命题的真值
* Input Parameter:
* Returned Value:  0
***********************************************************/
int main()
{
    bool p, q;
    char ret = 0;
    while (ret != 'n') {
        if (ret == 'y')
            system("cls");//清屏
        std::cout << ("***************************************\n") //标语
                  << ("**                                   **\n")
                  << ("**        欢迎进入逻辑运算程序       **\n")
                  << ("**                                   **\n")
                  << ("***************************************\n\n\n");
        while (1) {
            std::cout << "  请输入p的值（0或1），以回车结束：";
            std::cin >> p;//读取P的值
            std::cout << "\n";
            if (std::cin.fail()) {
                std::cout << "  p值输入有误，请重新输入\n";
                // 清除缓冲区
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            // 清除缓冲区
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        while (1) {
            std::cout << "  请输入q的值（0或1），以回车结束：";
            std::cin >> q;//读取Q的值
            std::cout << "\n";
            if (std::cin.fail()) {
                std::cout << "  q值输入有误，请重新输入\n";
                // 清除缓冲区
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            // 清除缓冲区
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        std::cout << "  与运算：\n" << "        p∧q=" << (p && q) << "\n";//与运算同时输出结果
        std::cout << "  或运算：\n" << "        p∨q=" << (p || q) << "\n"; //或运算同时输出结果
        std::cout << "  蕴涵运算：\n" << "        p→q=" << (!p || q) << "\n"; //蕴涵运算，将其转化为与或非形式同时输出结果
        std::cout << "  双蕴涵运算：\n" << "        p?q=" << ((!p || q) && (p || !q)) << "\n";//等价运算，将其转化为与或非形式同时输出结果
        while (1) {
            std::cout << "  是否继续计算？(y/n)："; //询问是否继续操作
            std::cin >> ret;
            std::cout << "\n";
            if (std::cin.fail() || (ret != 'y' && ret != 'n')) {
                std::cout << "  输入有误，请重新输入\n";//错误校验
                // 清除缓冲区
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            // 清除缓冲区
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
    std::cout << "欢迎下次再次使用!\n";

    return 0;
}
