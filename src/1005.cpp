#include <iostream>
#define PI 3.14159265358979323846
#include <stdio.h>
using namespace std;

int main()
{
    int year_num;
    float x, y, area; //area表示坐标(x,y)对应半圆的面积
    cin >> year_num;
    for (int i = 0; i < year_num; i++) {
        cin >> x >> y;
        area = PI * (x * x + y * y) / 2;
        printf("Property %d: This property will begin eroding in year %d.\n", i + 1, int(area / 50) + 1);
    }
    cout << "END OF OUTPUT.";
    return 0;
}