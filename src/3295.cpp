//Hint：相当于前缀表达式(逆波兰)的计算，使用栈来计算
#include <iostream>
#include <map>
#include <stack>
#include <cctype>
#define _K(w, x) ((w) && (x))    //	K --> and:  w && x
#define _A(w, x) ((w) || (x))    //	A --> or:  w || x
#define _N(w) (!(w))             //	N --> not :  !w
#define _C(w, x) ((!(w)) || (x)) //	C --> implies :  (!w) || x
#define _E(w, x) ((w) == (x))    //	E --> equals :  w == x
using namespace std;

//每个位代表一个布尔变量的值，可以用掩码提取出对应变量的布尔值
struct Vbits
{
    unsigned short p : 1;
    unsigned short q : 1;
    unsigned short r : 1;
    unsigned short s : 1;
    unsigned short t : 1;
};
union Vars
{
    Vbits vbits;
    unsigned short vars;
};

int main()
{
    Vars v;
    string exp; //逻辑表达式字符串
    map<char, unsigned short> chToUs;
    chToUs['p'] = 1;
    chToUs['q'] = 1 << 1;
    chToUs['r'] = 1 << 2;
    chToUs['s'] = 1 << 3;
    chToUs['t'] = 1 << 4; //代表变量的字符到对应掩码的映射
    cin >> exp;
    const char *expArr = exp.c_str();
    while (expArr[0] != '0')
    {
        stack<bool> s;           //存放各子wwf的计算结果
        bool isTautology = true; //是否为Tautology
        //枚举所有真值组合
        for (v.vars = 0; v.vars < 32; v.vars++)
        {
            char ch;
            //将wff中的变量逆序压栈，如果遇到一个操作符则出栈对应数量的变量做运算，结果压栈，否则直接压栈
            for (int i = exp.size() - 1; i >= 0; i--)
            {
                ch = expArr[i];
                bool x, y; //两操作数
                if (islower(ch))
                {
                    s.push(chToUs[ch] & v.vars); //利用掩码取出真值
                }
                else
                {
                    x = s.top();
                    s.pop();
                    if (ch != 'N')
                    { //双目运算符要出栈两次
                        y = s.top();
                        s.pop();
                    }
                    switch (ch)
                    {
                    case 'A':
                        s.push(_A(x, y));
                        break;
                    case 'K':
                        s.push(_K(x, y));
                        break;
                    case 'N':
                        s.push(_N(x));
                        break;
                    case 'C':
                        s.push(_C(x, y));
                        break;
                    case 'E':
                        s.push(_E(x, y));
                        break;
                    }
                }
            }
            if (!s.empty() && !s.top())
            {
                isTautology = false; //如果该赋值下wwf为false说明wwf不永真
                break;
            }
            while (!s.empty())
            {
                s.pop(); //清空栈
            }
        }
        if (isTautology)
            cout << "tautology" << endl;
        else
            cout << "not" << endl;
        cin >> exp;
        expArr = exp.c_str();
    }
    return 0;
}