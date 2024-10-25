/***********************************************************
* File:     DiscreteMathematics_1_1.cpp
* Author:   Xiaolong Ma(��С��)
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

bool AND(bool a, bool b) { return a && b; } //��
bool OR(bool a, bool b) { return a || b; } //��ȡ
bool NOT(bool a) { return !a; } //��ȡ
bool IMPLIES(bool a, bool b) { return !a || b; } //�̺�
bool EQUIVALENT(bool a, bool b) { return IMPLIES(a, b) && IMPLIES(b, a); } //�ȼ�

/***********************************************************
* Function Name:   Evaluate
* Function:        �����������ȼ����������ţ����μ����߼����ʽ����ֵ
* Input Parameter: expr: �߼����ʽ�ַ���
*                  values: ��������ֵӳ��
* Returned Value:  �������߼����ʽ����ֵ
***********************************************************/
bool Evaluate(std::string& expr, std::map<char, bool>& values) 
{
    // �����ʽ
    for (size_t i = 0; i < expr.length();i++)
        if (expr[i] == '!') {
            //���㣬�ý��������ʽ
            expr[i] = '0' + char(NOT(values[expr[i + 1]]));
            expr.erase(i + 1, 1);
        }

    // �����ȡʽ
    for (size_t i = 0; i < expr.length(); i++)
        if (expr[i] == '&') {
            //���㣬�ý��������ʽ
            expr[i - 1] = '0' + char(AND(values[expr[i - 1]], values[expr[i + 1]]));
            expr.erase(i, 2);
            i = i - 1; //�޸���������ֹԽ��
        }

    // ������ȡʽ
    for (size_t i = 0; i < expr.length(); i++)
        if (expr[i] == '|') {
            //���㣬�ý��������ʽ
            expr[i - 1] = '0' + char(OR(values[expr[i - 1]], values[expr[i + 1]]));
            expr.erase(i, 2);
            i = i - 1;//�޸���������ֹԽ��
        } 

    // �����̺�ʽ
    for (size_t i = 0; i < expr.length(); i++)
        if (expr[i] == '^') {
            //���㣬�ý��������ʽ
            expr[i - 1] = '0' + char(IMPLIES(values[expr[i - 1]], values[expr[i + 1]]));
            expr.erase(i, 2);
            i = i - 1;//�޸���������ֹԽ��
        }

    // ����ȼ�ʽ
    for (size_t i = 0; i < expr.length(); i++)
        if (expr[i] == '~') {
            //���㣬�ý��������ʽ
            expr[i - 1] = '0' + char(EQUIVALENT(values[expr[i - 1]], values[expr[i + 1]]));
            expr.erase(i, 2);
            i = i - 1;//�޸���������ֹԽ��
        }

    //���ر��ʽ��ֵ
    if (expr.length() == 1)
        return values[expr[0]];
    std::cout << "δ����ɹ�\n";
    exit(-10);
}

/***********************************************************
* Function Name:   FractionationEvaluate
* Function:       ��������ŵ��߼����ʽ����ֵ
* Input Parameter: expression: �߼����ʽ�ַ���
*                  values: ��������ֵӳ��
* Returned Value: �������߼����ʽ����ֵ
***********************************************************/
bool FractionationEvaluate(std::string expression, std::map<char, bool>& values) 
{
    std::string position, type;
    // ��������λ�ü�����
    for(unsigned int i=0;i<expression.length();i++)
        if (expression[i] == '(' || expression[i] == ')') {
            position += char(i);
            type += expression[i];
        }
    // ���û�����ţ�ֱ�Ӽ���
    if (int(position.length()) == 0)
        return Evaluate(expression, values);
    else {
        unsigned int i = 0;
        std::string store;
        // �ҵ���һ��������
        for (; i < type.length(); i++)
            if (type[i] == ')')
                break;
        // ��ȡ�����ڵı��ʽ
        for (int j = int(position[i - 1]) + 1; j<int(position[i]); j++)
            store += expression[j];
        size_t temp = store.length() + 1;
        // ���������ڵı��ʽ���滻
        expression[static_cast<size_t>(position[i - 1])] = char(Evaluate(store, values)) + '0';
        expression.erase(static_cast<size_t>(position[i - 1] + 1), temp);
        return FractionationEvaluate(expression, values);
    }
}

/***********************************************************
* Function Name:   CountAndStoreVariable
* Function:        ͳ�Ʋ��洢�߼����ʽ�еı��������༰����
* Input Parameter: initial_logical_expression: ��ʼ�߼����ʽ
*                  number_of_variables: ��������������
*                  store_variable: �洢�������ַ�������
* Returned Value:  
***********************************************************/
void CountAndStoreVariable(std::string initial_logical_expression,int& number_of_variables, std::string& store_variable) {
	for (size_t i = 0; i < initial_logical_expression.length(); i++) {
		if (initial_logical_expression[i] >= 'a' && initial_logical_expression[i] <= 'z' || initial_logical_expression[i] >= 'A' && initial_logical_expression[i] <= 'Z') {
			int ret = 0;
            // �������Ƿ��Ѿ�����
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
* Function:        ����߼����ʽ����ֵ�������ʽ
* Input Parameter: initial_logical_expression: ��ʼ�߼����ʽ
* Returned Value:  ��
***********************************************************/
void TruthTableNormalForm(std::string initial_logical_expression)
{
	int number_of_variables = 0;
	std::string store_variable;
	CountAndStoreVariable(initial_logical_expression,number_of_variables, store_variable);
	std::cout << "\n��ʽ���еı�������Ϊ: " << number_of_variables << "\n\n";
    int truth_table_rows = int(std::pow(2, number_of_variables)); //����ȡֵ����ĸ���

    std::string conjunction, disjunction;//���ȡֵ��Ӧ�ķ�ʽ����

    //�����ֵ��
    std::cout << "�����ֵ�����£�\n\n";
    for (char ch : store_variable)
        std::cout << " " << ch;
    std::cout << " " << initial_logical_expression << "\n\n";
    for (int i = 0; i < truth_table_rows; i++) {
        //����ӳ��ķ�ʽ���������
        std::map<char, bool>values;
        // ���ñ�������ֵ
        for (int j = 0; j < number_of_variables; j++) 
            values[store_variable[j]] = (i >> (number_of_variables - j - 1)) & 1;
        values['1'] = 1;
        values['2'] = 0;
        // �����������ֵ
        for (char ch : store_variable)
            std::cout << " " << values[ch];

        //�����߼����ʽ����ֵ
        bool result = FractionationEvaluate(initial_logical_expression, values);
        if (result)
            disjunction += '0' + i;
        else
            conjunction += '0' + i;
        // ����߼����ʽ����ֵ
        std::cout << "    " << result << "\n";
    }

    // �������ȡ��ʽ
    std::cout << "\n�����⹫ʽ�е�����ȡ��ʽ\n        ";
    if (conjunction.length() != 0) {
        for (size_t i = 0; i < conjunction.length(); i++) {
            if (i != 0)
                std::cout << "��";
            std::cout << "M(" << conjunction[i] << ")";
        }
    }
    else
        std::cout << "�����⹫ʽ����������ȡ��ʽ\n";

    // �������ȡ��ʽ
    std::cout << "\n\n�����⹫ʽ�е�����ȡ��ʽ\n        ";
    if (disjunction.length() != 0) {
        for (size_t i = 0; i < disjunction.length(); i++) {
            if (i != 0)
                std::cout << "��";
            std::cout << "m(" << disjunction[i] << ")";
        }
    }
    else
        std::cout << "�����⹫ʽ����������ȡ��ʽ\n";
}

/***********************************************************
* Function Name:   LegalCharacter
* Function:        �����ʽ�з���ĸ�����ŵ��ַ��Ƿ�Ϸ�
* Input Parameter: character: ��Ҫ�����ַ�
* Returned Value:  ����ַ��Ϸ�������true�����򷵻�false
***********************************************************/
bool LegalCharacter(char ch)
{
    //�ж��Ƿ�Ϊ�߼������
    if (ch == '!' || ch == '&' || ch == '|' || ch == '^' || ch == '~')
        return true;
    return false;
}
// ����߼����ʽ�Ƿ�Ϊ��
/***********************************************************
* Function Name:   LegalExpression
* Function:        ����߼����ʽ�Ƿ�Ϸ�
* Input Parameter: initial_logical_expression: �߼����ʽ
* Returned Value:  ����Ϸ�����true�����򷵻�false
***********************************************************/
bool LegalExpression(const std::string& initial_logical_expression)
{
    // ����߼����ʽ�Ƿ�Ϊ��
    if (initial_logical_expression.empty()) {
        std::cout << "���⹫ʽΪ�գ����������룡\n";
        return false;
    }
    
    std::stack<char> parentheses;// ���ڴ洢����
    char previous = '\0';// �洢ǰһ���ַ�
    for (char ch : initial_logical_expression) {
        // ����ַ��Ƿ�Ϸ�
        if (!((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) && !LegalCharacter(ch) && ch != '(' && ch != ')') {
            std::cout << "���⹫ʽ���ڷǷ��ַ����룬���������룡\n";
            return false;
        }

        // ��鹫ʽ�Ƿ��Զ�Ԫ�������ʼ
        if (previous == '\0' && (ch == '&' || ch == '|' || ch == '~' || ch == '^')) {
            std::cout << "���⹫ʽ�����Զ�Ԫ�������ʼ�����������룡\n";
            return false;
        }

        // ��������
        if (previous == '(' && ch == ')') {
            std::cout << "���⹫ʽ���ڿ����ţ����������룡\n";
            return false;
        }

        // ��鲻�Ϸ�������ȡ�ǲ���
        if (previous == '!' && ch == '!') {
            std::cout << "���⹫ʽ���ڲ��Ϸ�������ȡ�ǲ��������������룡\n";
            return false;
        }

        // ���ȡ�������ǰ���ַ��Ƿ�Ϸ�
        if (ch == '!' && isalpha(previous)) {
            std::cout << "���⹫ʽ��ȡ�������ǰ�������ӱ��������������룡\n";
            return false;
        }

        // �����������ŵ�����
        if ((isalpha(ch) && previous == ')') || (ch == '(' && isalpha(previous))) {
            std::cout << "���⹫ʽ�б��������ŵ����Ӳ���ȷ�����������룡\n";
            return false;
        }

        // �洢������
        if (ch == '(')
            parentheses.push(ch);

        // ����������
        else if (ch == ')') {
            if (parentheses.empty()) {
                std::cout << "���⹫ʽ���Ų�ƥ�䣬���������룡\n";
                return false;// ������û��ƥ���������
            }
            parentheses.pop();// ƥ�䵽һ�����ţ�����ջ��Ԫ��
        }

        // �����ַ�����
        if (isalpha(ch) && isalpha(previous)) {
            std::cout << "���⹫ʽ�������ڵ��ַ��������������ڶ��ַ����������������룡\n" ;
            return false;
        }

        // ��������ǰ�������
        if ((ch == '&' || ch == '|' || ch == '~' || ch == '^') && (!isalpha(previous) && previous != ')')) {
            std::cout << "���⹫ʽ��ÿ����Ԫ�����ǰ��������ӱ��������������룡\n";
            return false;
        }
        previous = ch;
    }

    // ��鹫ʽ�Ƿ����������β
    if (LegalCharacter(previous)) {
        std::cout << "���⹫ʽ�������������β�����������룡\n";
        return false;
    }

    // ��������Ƿ�ƥ��
    if (!parentheses.empty()) {
        std::cout << "���⹫ʽ���Ų�ƥ�䣬���������룡\n";
        return false;
    }

    return true;// ���ʽ�Ϸ�
}

int main()
{
	char ret = 0;
	while (ret != 'n') {
	    system("cls");//����
		int number_of_parentheses = 0, number_of_variables = 0;
		std::string initial_logical_expression, store_variable;
        std::cout << "***************************************\n"
            << "**                                   **\n"
            << "**         ��ӭ�����߼��������      **\n"
            << "**   (��������ֵ��,����ʽ,֧������)  **\n"
            << "**                                   **\n"
            << "**              ��!��ʾ��            **\n"
            << "**              ��&��ʾ��            **\n"
            << "**              ��|��ʾ��            **\n"
            << "**             ��^��ʾ�̺�           **\n"
            << "**             ��~��ʾ��ֵ           **\n"
            << "**                                   **\n"
            << "***************************************\n\n";
        do {
            std::cout << "������һ���Ϸ������⹫ʽ:\n";//����ʽ��
            std::getline(std::cin, initial_logical_expression);//��ȡʽ��
        } while (!LegalExpression(initial_logical_expression));//�ж�ʽ���Ƿ���Ϲ淶
        TruthTableNormalForm(initial_logical_expression);//������ֵ�������ʽ���ܺ���
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
	std::cout << "\n\n��ӭ�´�ʹ��! \n";

	return 0;
}