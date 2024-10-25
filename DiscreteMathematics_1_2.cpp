/***********************************************************
* File:     DiscreteMathematics_1_1.cpp
* Author:   Xiaolong Ma(马小龙)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Visual Studio 2022
* Function: question B of propositional logic connective, truth table, main normal form
* Date:     2024.9.23
* Update:   2024.9.23
***********************************************************/

#include <cctype>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <map>
#include <stack>
#include <string>

bool AND(bool a, bool b) { return a && b; } //否定
bool OR(bool a, bool b) { return a || b; } //合取
bool NOT(bool a) { return !a; } //析取
bool IMPLIES(bool a, bool b) { return !a || b; } //蕴涵
bool EQUIVALENT(bool a, bool b) { return IMPLIES(a, b) && IMPLIES(b, a); } //等价

/***********************************************************
* Function Name:   Evaluate
* Function:        按照运算优先级（不含括号）依次计算逻辑表达式的真值
* Input Parameter: expr: 逻辑表达式字符串
*                  values: 变量的真值映射
* Returned Value:  计算后的逻辑表达式的真值
***********************************************************/
bool Evaluate(std::string& expr, std::map<char, bool>& values) 
{
    // 计算否定式
    for (size_t i = 0; i < expr.length();i++)
        if (expr[i] == '!') {
            //计算，用结果替代表达式
            expr[i] = '0' + char(NOT(values[expr[i + 1]]));
            expr.erase(i + 1, 1);
        }

    // 计算合取式
    for (size_t i = 0; i < expr.length(); i++)
        if (expr[i] == '&') {
            //计算，用结果替代表达式
            expr[i - 1] = '0' + char(AND(values[expr[i - 1]], values[expr[i + 1]]));
            expr.erase(i, 2);
            i = i - 1; //修改索引，防止越界
        }

    // 计算析取式
    for (size_t i = 0; i < expr.length(); i++)
        if (expr[i] == '|') {
            //计算，用结果替代表达式
            expr[i - 1] = '0' + char(OR(values[expr[i - 1]], values[expr[i + 1]]));
            expr.erase(i, 2);
            i = i - 1;//修改索引，防止越界
        } 

    // 计算蕴涵式
    for (size_t i = 0; i < expr.length(); i++)
        if (expr[i] == '^') {
            //计算，用结果替代表达式
            expr[i - 1] = '0' + char(IMPLIES(values[expr[i - 1]], values[expr[i + 1]]));
            expr.erase(i, 2);
            i = i - 1;//修改索引，防止越界
        }

    // 计算等价式
    for (size_t i = 0; i < expr.length(); i++)
        if (expr[i] == '~') {
            //计算，用结果替代表达式
            expr[i - 1] = '0' + char(EQUIVALENT(values[expr[i - 1]], values[expr[i + 1]]));
            expr.erase(i, 2);
            i = i - 1;//修改索引，防止越界
        }

    //返回表达式真值
    if (expr.length() == 1)
        return values[expr[0]];
    std::cout << "未计算成功\n";
    exit(-10);
}

/***********************************************************
* Function Name:   FractionationEvaluate
* Function:       计算带括号的逻辑表达式的真值
* Input Parameter: expression: 逻辑表达式字符串
*                  values: 变量的真值映射
* Returned Value: 计算后的逻辑表达式的真值
***********************************************************/
bool FractionationEvaluate(std::string expression, std::map<char, bool>& values) 
{
    std::string position, type;
    // 查找括号位置及种类
    for(unsigned int i=0;i<expression.length();i++)
        if (expression[i] == '(' || expression[i] == ')') {
            position += char(i);
            type += expression[i];
        }
    // 如果没有括号，直接计算
    if (int(position.length()) == 0)
        return Evaluate(expression, values);
    else {
        unsigned int i = 0;
        std::string store;
        // 找到第一个右括号
        for (; i < type.length(); i++)
            if (type[i] == ')')
                break;
        // 提取括号内的表达式
        for (int j = int(position[i - 1]) + 1; j<int(position[i]); j++)
            store += expression[j];
        size_t temp = store.length() + 1;
        // 计算括号内的表达式并替换
        expression[static_cast<size_t>(position[i - 1])] = char(Evaluate(store, values)) + '0';
        expression.erase(static_cast<size_t>(position[i - 1] + 1), temp);
        return FractionationEvaluate(expression, values);
    }
}

/***********************************************************
* Function Name:   CountAndStoreVariable
* Function:        统计并存储逻辑表达式中的变量的种类及个数
* Input Parameter: initial_logical_expression: 初始逻辑表达式
*                  number_of_variables: 变量个数的引用
*                  store_variable: 存储变量的字符串引用
* Returned Value:  
***********************************************************/
void CountAndStoreVariable(std::string initial_logical_expression,int& number_of_variables, std::string& store_variable) {
	for (size_t i = 0; i < initial_logical_expression.length(); i++) {
		if (initial_logical_expression[i] >= 'a' && initial_logical_expression[i] <= 'z' || initial_logical_expression[i] >= 'A' && initial_logical_expression[i] <= 'Z') {
			int ret = 0;
            // 检查变量是否已经存在
			for (int j = 0; j < number_of_variables; j++)
				if (initial_logical_expression[i] == store_variable[j])
					ret++;
			if (ret == 0) {
				store_variable += initial_logical_expression[i];
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
void TruthTableNormalForm(std::string initial_logical_expression)
{
	int number_of_variables = 0;
	std::string store_variable;
	CountAndStoreVariable(initial_logical_expression,number_of_variables, store_variable);
	std::cout << "\n该式子中的变量个数为: " << number_of_variables << "\n\n";
    int truth_table_rows = int(std::pow(2, number_of_variables)); //计算取值情况的个数

    std::string conjunction, disjunction;//标记取值对应的范式种类

    //输出真值表
    std::cout << "输出真值表如下：\n\n";
    for (char ch : store_variable)
        std::cout << " " << ch;
    std::cout << " " << initial_logical_expression << "\n\n";
    for (int i = 0; i < truth_table_rows; i++) {
        //采用映射的方式，方便计算
        std::map<char, bool>values;
        // 设置变量的真值
        for (int j = 0; j < number_of_variables; j++) 
            values[store_variable[j]] = (i >> (number_of_variables - j - 1)) & 1;
        values['1'] = 1;
        values['2'] = 0;
        // 输出变量的真值
        for (char ch : store_variable)
            std::cout << " " << values[ch];

        //计算逻辑表达式的真值
        bool result = FractionationEvaluate(initial_logical_expression, values);
        if (result)
            disjunction += '0' + i;
        else
            conjunction += '0' + i;
        // 输出逻辑表达式的真值
        std::cout << "    " << result << "\n";
    }

    // 输出主合取范式
    std::cout << "\n该命题公式中的主合取范式\n        ";
    if (conjunction.length() != 0) {
        for (size_t i = 0; i < conjunction.length(); i++) {
            if (i != 0)
                std::cout << "∨";
            std::cout << "M(" << conjunction[i] << ")";
        }
    }
    else
        std::cout << "该命题公式不存在主合取范式\n";

    // 输出主析取范式
    std::cout << "\n\n该命题公式中的主析取范式\n        ";
    if (disjunction.length() != 0) {
        for (size_t i = 0; i < disjunction.length(); i++) {
            if (i != 0)
                std::cout << "∧";
            std::cout << "m(" << disjunction[i] << ")";
        }
    }
    else
        std::cout << "该命题公式不存在主析取范式\n";
}

/***********************************************************
* Function Name:   LegalCharacter
* Function:        检查表达式中非字母和括号的字符是否合法
* Input Parameter: character: 需要检查的字符
* Returned Value:  如果字符合法，返回true；否则返回false
***********************************************************/
bool LegalCharacter(char ch)
{
    //判断是否为逻辑运算符
    if (ch == '!' || ch == '&' || ch == '|' || ch == '^' || ch == '~')
        return true;
    return false;
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
        if (!((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) && !LegalCharacter(ch) && ch != '(' && ch != ')') {
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
    if (LegalCharacter(previous)) {
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
	char ret = 0;
	while (ret != 'n') {
	    system("cls");//清屏
		int number_of_parentheses = 0, number_of_variables = 0;
		std::string initial_logical_expression, store_variable;
        std::cout << "***************************************\n"
            << "**                                   **\n"
            << "**         欢迎进入逻辑运算软件      **\n"
            << "**   (可运算真值表,主范式,支持括号)  **\n"
            << "**                                   **\n"
            << "**              用!表示非            **\n"
            << "**              用&表示与            **\n"
            << "**              用|表示或            **\n"
            << "**             用^表示蕴含           **\n"
            << "**             用~表示等值           **\n"
            << "**                                   **\n"
            << "***************************************\n\n";
        do {
            std::cout << "请输入一个合法的命题公式:\n";//输入式子
            std::getline(std::cin, initial_logical_expression);//读取式子
        } while (!LegalExpression(initial_logical_expression));//判断式子是否符合规范
        TruthTableNormalForm(initial_logical_expression);//调用真值表和主范式功能函数
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
	std::cout << "\n\n欢迎下次使用! \n";

	return 0;
}