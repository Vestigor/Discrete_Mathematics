/***********************************************************
* File:     proposition_1.cpp
* Author:   Xiaolong Ma(马小龙)
* E-mail:   2353814@tongji.edu.cn
* Function: question A of propositional logic connective, truth table, main normal form
* Encoding: UTF-8
* Date:     2024.9.17
* Update:   2024.11.27
***********************************************************/

#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <limits>


bool Input(const char ch)
{
    double input;
    while (true) {
        std::cout << "请输入"<<ch<<"的值（0或1），以回车结束：";
        std::cin >> input; //读取P的值
        std::cout << "\n";
        if (std::cin.fail()||input!=0&&input!=1) {
            std::cout <<ch<<"值输入有误，请重新输入\n";
            // 清除缓冲区
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        break;
    }

    return static_cast<bool>(input);
}

/***********************************************************
* Function Name:   main
* Function:        输入两个命题的真值，并计算由与、或、蕴涵和双蕴涵构成的命题的真值
* Input Parameter:
* Returned Value:  0
***********************************************************/
int main()
{
    while (true) {
        system("cls");//清屏
        std::cout << ("***************************************\n") //标语
                  << ("**                                   **\n")
                  << ("**        欢迎进入逻辑运算程序       **\n")
                  << ("**                                   **\n")
                  << ("***************************************\n\n");

        bool p = Input('p');
        bool q = Input('q');
        std::cout << "与运算    ：" << " p∧q =" << (p && q) << "\n";//与运算同时输出结果
        std::cout << "或运算    ：" << " p∨q =" << (p || q) << "\n"; //或运算同时输出结果
        std::cout << "条件运算  ：" << " p→q =" << (!p || q) << "\n"; //蕴涵运算，将其转化为与或非形式同时输出结果
        std::cout << "双条件运算：" << "p←→q=" << ((!p || q) && (p || !q)) << "\n\n\n";//等价运算，将其转化为与或非形式同时输出结果

        std::cout << "是否继续运算？[Y/n] ";
        char ch;
        do {
            ch = static_cast<char>(_getch());
        } while (ch != 'Y' && ch != 'y' && ch != 'N' && ch != 'n');
        std::cout << ch << '\n';

        // 如果用户输入 N 或 n，则退出循环，结束程序
        if (ch == 'N' || ch == 'n')
            break;
    }
    std::cout << "欢迎下次再次使用!\n";

    return 0;
}
