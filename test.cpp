/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-08-20 16:45:13
 * @LastEditors: lovechen 1156841766@qq.com
 * @LastEditTime: 2022-08-20 23:43:03
 * @FilePath: /undefined/Users/chiyi/c++练习/未命名文件夹/test.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <string>


using namespace std;
void swap(int *x,int *y);

int main()
{
    int x,y;

    cout << "shuruzhi: ";
    cin >> x >> y;

    swap(&x,&y);
    cout << x << y << endl;

    return 0;
}

void swap(int *x,int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}