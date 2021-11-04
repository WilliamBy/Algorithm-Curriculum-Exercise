//暴力枚举，反转可通过xor位运算表示
#include <iostream>
#include <stdio.h>
#include <map>
using namespace std;

union Board {
    struct {
        unsigned short r1 : 4;
        unsigned short r2 : 4;
        unsigned short r3 : 4;
        unsigned short r4 : 4;
    };
    unsigned int num;
};

int main()
{
    Board origin, board, scheme;   //原始棋盘，当前棋盘，反转方案
    map<char, unsigned short> mapper;   //代表棋子的字符到二进制的映射
    mapper['b'] = 1;
    mapper['w'] = 0;
    string line;
    unsigned short buf[4];
    //预处理，将外界输入棋盘转化为Board结构存储在origin中
    for (int i = 0; i < 4; i++) {
        cin >> line;
        const char * strBuf = line.c_str();
        buf[i] = mapper[strBuf[0]] << 3  | mapper[strBuf[1]] << 2 | mapper[strBuf[2]] << 1 | mapper[strBuf[3]];
    }
    origin.r1 = buf[0];
    origin.r2 = buf[1];
    origin.r3 = buf[2];
    origin.r4 = buf[3];

    if (origin.num == 0x0000 || origin.num == 0xffff) { //初始已经满足
        cout << 0;
        return 0;
    }
    board.num = origin.num;
    int min = 17;   //反转最小数
    //4x4棋局，每个点被选中或不选中的情况的组合共有0xffff种，刚好可以用一个16位长的整型树表示各个点选中与否
    for (scheme.num = 0x0000; scheme.num <= 0xffff; scheme.num++) {
        board.r1 = board.r1 ^ scheme.r1 ^ (scheme.r1 << 1) ^ (scheme.r1 >> 1) ^ (scheme.r2);
        board.r2 = board.r2 ^ scheme.r2 ^ (scheme.r2 << 1) ^ (scheme.r2 >> 1) ^ (scheme.r3) ^ (scheme.r1);
        board.r3 = board.r3 ^ scheme.r3 ^ (scheme.r3 << 1) ^ (scheme.r3 >> 1) ^ (scheme.r4) ^ (scheme.r2);
        board.r4 = board.r4 ^ scheme.r4 ^ (scheme.r4 << 1) ^ (scheme.r4 >> 1) ^ (scheme.r3);
        board.num &= 0xffff;
        if (board.num == 0x0000 || board.num == 0xffff)
        {
            int nOf1 = 0;   //1的个数
            int snum = scheme.num;
            for (int i = 0; i < 16; i++) {
                if ((snum & 0x1) == 0x1) {
                    nOf1++;
                }
                snum = snum >> 1;
            }
            min = (nOf1 < min) ? nOf1 : min;
        }
        board.num = origin.num; //还原
    }
    if (min < 17) {
        cout << min;
    } else {    //没有找到任何解
        cout << "Impossible";
    }
    return 0;
}