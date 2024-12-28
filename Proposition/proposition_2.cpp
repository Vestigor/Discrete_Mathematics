/***********************************************************
* File:     proposition_2.cpp
* Author:   Xiaolong Ma(马小龙)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Visual Studio 2022
* Function: question B of propositional logic connective, truth table, main normal form
* Date:     2024.9.23
* Update:   2024.11.29
***********************************************************/

#include <cctype>
#include <cmath>
#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
#include <cstdlib>
#include <stack>

bool AND(const bool a, const bool b) { return a && b; } //否定
bool OR(const bool a, const bool b) { return a || b; } //合取
bool NOT(const bool a) { return !a; } //析取
bool IMPLIES(const bool a, const bool b) { return !a || b; } //蕴涵
bool EQUIVALENT(const bool a, const bool b) { return IMPLIES(a, b) && IMPLIES(b, a); } //等价

/***********************************************************
* Function Name:   getPriority
* Function:        获取运算符的优先级
* Input Parameter: op - 运算符
* Returned Value:  运算符的优先级
***********************************************************/
int getPriority(char op)
{
    if (op == '!') return 5;
    if (op == '&') return 4;
    if (op == '|') return 3;
    if (op == '^') return 2;
    if (op == '~') return 1;

    return 0; // 无优先级
}

/***********************************************************
* Function Name:   LegalOperator
* Function:        检查表达式中非字母和括号的字符是否合法
* Input Parameter: character: 需要检查的字符
* Returned Value:  如果字符合法，返回true；否则返回false
***********************************************************/
bool LegalOperator(const char ch)
{
    //判断是否为逻辑运算符
    if (ch == '!' || ch == '&' || ch == '|' || ch == '^' || ch == '~')
        return true;
    return false;
}

/***********************************************************
* Function Name:   Calculate
* Function:        通过判断运算符类型，调用不同计算函数
* Input Parameter: a 第一个运算数
*                  op 运算符
*                  b 第二个运算数
* Returned Value:  运算值
***********************************************************/
bool Calculate(const bool a, const char op ,bool b)
{
    if (op == '^')
        return IMPLIES(a, b);
    if (op == '~')
        return EQUIVALENT(a, b);
    if (op == '&')
        return AND(a, b);
    if (op == '|')
        return OR(a, b);
    std::cerr << "Error! Operator '" << op << "' is not a valid binary connective." << std::endl;
    abort();
}


/***********************************************************
* Function Name:   Evaluate
* Function:        逻辑表达式的真值
* Input Parameter: expression: 逻辑表达式字符串
*                  values: 变量的真值映射
* Returned Value:  计算后的逻辑表达式的真值
***********************************************************/
void  ProcessStack(std::stack<char>& operators,std::stack<bool>& operands)
{
    //取出运算符
    const char op = operators.top();
    operators.pop();
    if (op == '!') {
        const bool operand = operands.top();
        operands.pop();
        const bool result = NOT(operand);
        //将运算结果放入栈中
        operands.push(result);
    }
    else {
        //取出栈中的两个运算数，后入栈作为第二个运算数（蕴含不满足交换律）
        const bool b = operands.top();
        operands.pop();
        const bool a = operands.top();
        operands.pop();
        const bool result = Calculate(a, op, b);
        //将运算结果放回运算数栈中
        operands.push(result);
    }
}

/***********************************************************
* Function Name:   Evaluate
* Function:        逻辑表达式的真值
* Input Parameter: expression: 逻辑表达式字符串
*                  values: 变量的真值映射
* Returned Value:  计算后的逻辑表达式的真值
***********************************************************/
bool Evaluate(const std::string& expression, std::unordered_map<char, bool>& values)
{
    std::stack<char> operators;
    std::stack<bool> operands;
    for (char ch : expression) {
        if (isalpha(ch))
            operands.push(values[ch]);
        else if (ch == '(')
            operators.push(ch);
        else if (ch == ')') {
            //处理括号中的内容，直到遇到左括号或运算符栈为空
            while (!operators.empty() && operators.top() != '(') {
                ProcessStack(operators, operands);
            }
            //取出左括号
            if (!operators.empty()) operators.pop();
        }
        else if (LegalOperator(ch)) {
            //取出比当前运算符优先级高或与当前运算符优先级相同（蕴含不满足结合律）的运算符进行计算
            while (!operators.empty() && getPriority(operators.top())>=getPriority(ch)) {
                ProcessStack(operators, operands);
            }
            operators.push(ch);
        }
    }

    while (!operators.empty()) {
        ProcessStack(operators, operands);
    }

    //当运算符栈为空时，运算数栈只剩一个数，即为结果
    const bool result = operands.top();
    operands.pop();
    return result;
}

/***********************************************************
* Function Name:   CountAndStoreVariable
* Function:        统计并存储逻辑表达式中的变量的种类及个数
* Input Parameter: initial_logical_expression: 初始逻辑表达式
*                  number_of_variables: 变量个数的引用
*                  store_variable: 存储变量的字符串引用
* Returned Value:  
***********************************************************/
void CountAndStoreVariable(const std::string &initial_logical_expression,int& number_of_variables, std::string& store_variable) {
	for (const auto ch:initial_logical_expression) {
		if (isalpha(ch)) {
			if (store_variable.find(ch)==std::string::npos) {
				store_variable += ch;
				number_of_variables++;
			}
		}
	}
}

/***********************************************************
* Function Name:   TruthTableNormalForm
* Function:        输出逻辑表达式的真值表和主范式
* Input Parameter: initial_logical_expression: 初始逻辑表达式
* Returned Value:  无
***********************************************************/
void TruthTableNormalForm(const std::string& initial_logical_expression)
{
	int number_of_variables = 0;
	std::string store_variable;
	CountAndStoreVariable(initial_logical_expression,number_of_variables, store_variable);
	std::cout << "\n该式子中的变量个数为: " << number_of_variables << "\n\n";
    const int truth_table_rows = static_cast<int>(std::pow(2, number_of_variables)); //计算取值情况的个数
    std::vector<int> conjunction, disjunction;

    //输出真值表
    std::cout << "输出真值表如下：\n\n";
    for (const char ch : store_variable)
        std::cout << " " << ch;
    std::cout << "    " << initial_logical_expression << "\n\n";
    for (int i = 0; i < truth_table_rows; i++) {
        //采用映射的方式，方便计算
        std::unordered_map<char, bool>values;
        // 设置变量的真值
        for (int j = 0; j < number_of_variables; j++) 
            values[store_variable[j]] = (i >> (number_of_variables - j - 1)) & 1;//通过移位和按位与实现为变量赋值
        // 输出变量的真值
        for (char ch : store_variable)
            std::cout << " " << values[ch];

        //计算逻辑表达式的真值
        const bool result = Evaluate(initial_logical_expression, values);
        if (result)
            disjunction.push_back(i);
        else
            conjunction.push_back(i);
        // 输出逻辑表达式的真值
        std::cout << "    " << static_cast<int>(result) << "\n";
    }

    // 输出主合取范式
    std::cout << "\n该命题公式中的主合取范式\n        ";
    if (!conjunction.empty()) {
        for (size_t i = 0; i < conjunction.size(); i++) {
            if (i != 0)
                std::cout << "∨";
            std::cout << "M(" << conjunction[i] << ")";
        }
    }
    else
        std::cout << "该命题公式不存在主合取范式\n";

    // 输出主析取范式
    std::cout << "\n\n该命题公式中的主析取范式\n        ";
    if (!disjunction.empty()) {
        for (size_t i = 0; i < disjunction.size(); i++) {
            if (i != 0)
                std::cout << "∧";
            std::cout << "m(" << disjunction[i] << ")";
        }
    }
    else
        std::cout << "该命题公式不存在主析取范式\n";
}

// 检查逻辑表达式是否为空
/***********************************************************
* Function Name:   LegalExpression
* Function:        检查逻辑表达式是否合法
* Input Parameter: initial_logical_expression: 逻辑表达式
* Returned Value:  如果合法返回true；否则返回false
***********************************************************/
bool LegalExpression(const std::string& initial_logical_expression)
{
    // 检查逻辑表达式是否为空
    if (initial_logical_expression.empty()) {
        std::cout << "命题公式为空，请重新输入！\n";
        return false;
    }
    
    std::stack<char> parentheses;// 用于存储括号
    char previous = '\0';// 存储前一个字符
    for (char ch : initial_logical_expression) {
        // 检查字符是否合法
        if (!(isalpha(ch)) && !LegalOperator(ch) && ch != '(' && ch != ')') {
            std::cout << "命题公式存在非法字符输入，请重新输入！\n";
            return false;
        }

        // 检查公式是否以二元运算符开始
        if (previous == '\0' && (ch == '&' || ch == '|' || ch == '~' || ch == '^')) {
            std::cout << "命题公式不能以二元运算符开始，请重新输入！\n";
            return false;
        }

        // 检查空括号
        if (previous == '(' && ch == ')') {
            std::cout << "命题公式存在空括号，请重新输入！\n";
            return false;
        }

        // 检查不合法的连续取非操作
        if (previous == '!' && ch == '!') {
            std::cout << "命题公式存在不合法的连续取非操作，请重新输入！\n";
            return false;
        }

        // 检查取非运算符前的字符是否合法
        if (ch == '!' && isalpha(previous)) {
            std::cout << "命题公式中取非运算符前不可连接变量，请重新输入！\n";
            return false;
        }

        // 检查变量与括号的连接
        if ((isalpha(ch) && previous == ')') || (ch == '(' && isalpha(previous))) {
            std::cout << "命题公式中变量与括号的连接不正确，请重新输入！\n";
            return false;
        }

        // 存储左括号
        if (ch == '(')
            parentheses.push(ch);

        // 处理右括号
        else if (ch == ')') {
            if (parentheses.empty()) {
                std::cout << "命题公式括号不匹配，请重新输入！\n";
                return false;// 右括号没有匹配的左括号
            }
            parentheses.pop();// 匹配到一对括号，弹出栈顶元素
        }

        // 检查多字符变量
        if (isalpha(ch) && isalpha(previous)) {
            std::cout << "命题公式仅适用于单字符变量，不适用于多字符变量，请重新输入！\n" ;
            return false;
        }

        // 检查运算符前后的连接
        if ((ch == '&' || ch == '|' || ch == '~' || ch == '^') && (!isalpha(previous) && previous != ')')) {
            std::cout << "命题公式中每个二元运算符前后必须连接变量，请重新输入！\n";
            return false;
        }
        previous = ch;
    }

    // 检查公式是否以运算符结尾
    if (LegalOperator(previous)) {
        std::cout << "命题公式不能以运算符结尾，请重新输入！\n";
        return false;
    }

    // 检查括号是否匹配
    if (!parentheses.empty()) {
        std::cout << "命题公式括号不匹配，请重新输入！\n";
        return false;
    }

    return true;// 表达式合法
}

int main()
{
	while (true) {
	    system("cls");//清屏
		std::string initial_logical_expression, store_variable;
        std::cout << "***************************************\n"
                  << "**                                   **\n"
                  << "**         欢迎进入逻辑运算软件      **\n"
	              << "**   (可运算真值表,主范式,支持括号)  **\n"
                  << "**                                   **\n"
                  << "**              用!表示非            **\n"
                  << "**              用&表示与            **\n"
                  << "**              用|表示或            **\n"
                  << "**             用^表示条件           **\n"
                  << "**           用~表示双向条件         **\n"
	              << "**            用( )表示括号          **\n"
                  << "**                                   **\n"
                  << "***************************************\n\n";
        do {
            std::cout << "请输入一个合法的命题公式:\n";//输入式子
            std::getline(std::cin, initial_logical_expression);//读取式子
        } while (!LegalExpression(initial_logical_expression));//判断式子是否符合规范
        TruthTableNormalForm(initial_logical_expression);//调用真值表和主范式功能函数
        std::cout << "\n\n是否继续运算？[Y/n] ";

        char ch;
        do {
            ch = static_cast<char>(_getch());
        } while (ch != 'Y' && ch != 'y' && ch != 'N' && ch != 'n');
        std::cout << ch << '\n';

        // 如果用户输入 N 或 n，则退出循环，结束程序
        if (ch == 'N' || ch == 'n')
            break;
    }
    std::cout << "\n\n欢迎下次使用! \n";

	return 0;
}