#include <iostream>
#include <cctype>
#include <stdlib.h>
#include <cstdio>
#include <stack>
#include <string>

using namespace std;

//Задания со * не реализованы

int priority(char o)
{
	switch (o)
	{
	case '(': return 1;
	case '+': case '-': return 2;
	case '*': case '/': return 3;
	}
}

bool sign(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/';
}

bool num(char c)
{
	return c >= '0' && c <= '9';
}

void RPN(char* a, char* out)
{
	stack <char> S;
	int i = 0, j = 0;
	for (; a[i] != '\0'; ++i)
	{
		if (num(a[i]))
		{
			out[j] = a[i];
			++j;
		}
		else
		{
			if (j != 0 && num(out[j - 1]))
			{
				out[j] = ' ';
				++j;
			}

			if (sign(a[i]))
			{
				if (S.empty() || priority(S.top()) < priority(a[i]))
				{
					S.push(a[i]);
				}
				else
				{
					while (!S.empty() && (priority(S.top()) >= priority(a[i])))
					{
						out[j++] = S.top();
						S.pop();
					}
					S.push(a[i]);
				}
			}
			else
			{
				if (a[i] == '(')
				{
					S.push(a[i]);
				}
				else if (a[i] == ')')
				{
					if (S.empty() || S.top() == '(')
					{
						cout << "Input error!";
						exit(1);
					}
					else
					{
						while (S.top() != '(')
						{
							out[j] = S.top();
							S.pop();
							j++;
						}
					}
					S.pop();
				}
				else if (a[i] != ' ')
				{
					cout << "Initialize the variable " << a[i] << ":  ";
					cin >> a[i];
					i--;
				}
			}
		}
	}
	while (!S.empty())
	{
		if (S.top() == '(')
		{
			cout << "Input error!";
			exit(1);
		}
		else
		{
			out[j] = S.top();
			S.pop();
			j++;
		}
	}
}

int calc(char* out)
{
	int j = 0, r1 = 0, r2 = 0;
	stack <double> S;
	stack <double> S1;
	char* pEnd = nullptr;
	while (out[j] != '\0')
	{
		if (out[j] == '_') {
			++j;
			continue;
		}
		if (out[j] >= '0' && out[j] <= '9')
		{
			long iNum = strtol(&out[j], &pEnd, 10);
			S.push(iNum);
			j += pEnd - &out[j];
		}
		else
		{
			if (sign(out[j]))
			{
				if (S.empty()) return false;
				else {
					r1 = S.top(); S.pop();
					if (S.empty()) return false;
					r2 = S.top(); S.pop();
					switch (out[j])
					{
					case '+': S.push(r2 + r1); break;
					case '-': S.push(r2 - r1); break;
					case '*': S.push(r2 * r1); break;
					case '/': S.push(r2 / r1); break;
					}
				}
			}
			++j;
		}
	}
	return (S.top());
}

bool check(char* a) {

	bool right = true;
	if (a[0] == '+' || a[0] == '*' || a[0] == '/') {
		right = false;
	}
	else if (a[strlen(a) - 1] == '+' || a[strlen(a) - 1] == '-' || a[strlen(a) - 1] == '*' || a[strlen(a) - 1] == '/') {
		right = false;
	}
	else {
		for (int i = 0; i < strlen(a); i++) {
			if ((a[i] == '+' || a[i] == '-' || a[i] == '*' || a[i] == '/') && (a[i + 1] == '+' || a[i + 1] == '*' || a[i + 1] == '/')) {
				right = false;
			}
			if ((a[i] == '/') && (a[i + 1] == '0')) {
				right = false;
			}
		}
	}
	return right;
}

void ex1() {
	cout << "1. Converting the entered expression: " << endl;

	char a[100] = { 0 };
	char out[100] = { 0 };

	cout << "Expression: ";
	gets_s(a);
	RPN(a, out);
	cout << "RPN: " << out << endl << endl;

}

void ex2_1() {
	cout << endl << "2.  1)Checking for the correctness of a simple expression: " << endl;

	char chek[100] = { 0 };

	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "Expression:  ";
	gets_s(chek);
	if (check(chek)) cout << "The expression is correct!" << endl;
	else cout << "The expression is incorrect!" << endl;

}

void ex2_2() {
	cout << endl << "    2)Checking the RPN" << endl;

	char chek[100] = { 0 };
	//char cheked[100] = { 0 };

	cout << "Expression:  ";
	gets_s(chek);
	//OPN(chek, cheked);
	if (calc(chek)) cout << "The expression is correct!" << endl;
	else cout << "The expression is incorrect!" << endl;

}

void ex3_1() {
	cout << endl << "3.  1)Evaluating a simple expression" << endl;

	char a[100] = { 0 };
	char out[100] = { 0 };

	cout << "Expression: ";
	gets_s(a);
	RPN(a, out);
	cout << "Answer:  " << calc(out) << endl << endl;

}

void ex3_2() {
	cout << endl << "    2)Evaluating a RPN" << endl;

	char a[100] = { 0 };

	cout << "Expression: ";
	gets_s(a);
	cout << "Answer:  " << calc(a) << endl << endl;
	system("pause");
}

int main()
{
	cout << "Expression input is implemented only from the keyboard" << endl << endl;

	ex1();
	ex2_1();
	ex2_2();
	ex3_1();
	ex3_2();
	system("cls");

	return 0;
}