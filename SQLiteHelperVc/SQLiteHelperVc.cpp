#include "controller.h"
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <string>
#include <direct.h>
void menu();
#define CP_ACP 0
#define CP_UTF8 65001
using namespace std;
//utf-8转换到GB3212
char* U2G(const char* utf8)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len + 1];
    memset(wstr, 0, len + 1);
    MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
    len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
    char* str = new char[len + 1];
    memset(str, 0, len + 1);
    WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
    if (wstr) delete[] wstr;
    return str;
}
//GB2312到UTF-8的转换
char* G2U(const char* gb2312)
{
    int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len + 1];
    memset(wstr, 0, len + 1);
    MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
    len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
    char* str = new char[len + 1];
    memset(str, 0, len + 1);
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
    if (wstr) delete[] wstr;
    return str;
}
string getDirectory()
{
    char buffer[256];
    char* val = getcwd(buffer, sizeof(buffer));
    string path = val;
    return path;
}

int main()
{
    int index, i, j;
    char  is;
    int re, id, row,col;
    char** reList;
    string runpath = getDirectory()+"\\msg.db";
    SqlController* sq = new  SqlController(runpath, "msg");
    string name, telphone, email, type, remark,chgstr;
    //弹出菜单
    menu();
    cout << "请输入您的选项："; cin >> index;
    while (1)
    {
        switch (index)
        {
        case 0:
            cout << "确认退出吗？(Y/N)  :";
            cin >> is;
            if (is == 'Y' || is == 'y')
                return 0;
            break;
        case 1:
            cout << "请输入姓名：";
            cin >> name;
            cout << "请输入手机：";
            cin >> telphone;
            cout << "请输入邮箱：";
            cin >> email;
            cout << "请输入类别：";
            cin >> type;
            cout << "请输入备注：";
            cin >> remark;
            
            name = G2U(name.c_str());
            remark = G2U(remark.c_str());
            telphone = G2U(telphone.c_str());
            email = G2U(email.c_str());
            type = G2U(type.c_str());
            cout << chgstr << endl;
            re = sq->addData(name, telphone, email, type, remark);
            if (re == 2)
                cout << "ERROR! 该手机号已经被录入，不能重新录入！" << endl;
            else if (re == 0)
                cout << "ERROR! 出现未知错误，数据库错误！" << endl;
            else
                cout << "添加信息成功！" << endl;
            break;
        case 2:
            cout << "请输入手机：";
            cin >> telphone;
            reList = sq->getInfoByTel(telphone);
            if (reList[0] == "no")
            {
                cout << "该手机号信息不存在！" << endl;
                break;
            }
            if (reList[0] == "error")
            {
                cout << "数据库发生错误！" << endl;
                break;
            }
            for (i = 0, j = 0; i < 12; i++)
            {
                cout << reList[i] << "\t";
                if (j == 5)
                {
                    j = 0;
                    cout << endl;
                }
                else
                    j++;
            }
            break;
        case 3:
            cout << "请输入您要修改的信息的id号：";
            cin >> id;
            cout << "请输入姓名：";
            cin >> name;
            cout << "请输入手机：";
            cin >> telphone;
            cout << "请输入邮箱：";
            cin >> email;
            cout << "请输入类别：";
            cin >> type;
            cout << "请输入备注：";
            cin >> remark;
            re = sq->changeData(1, name, telphone, email, type, remark);
            if (re == 0)
                cout << "ERROR!数据库发生错误！" << endl;
            else
                cout << "修改成功！" << endl;
            break;
        case 4:
            cout << "请输入您要删除的信息的id号：";
            cin >> id;
            cout << "您确认要删除这条信息吗？一旦删除不可以恢复！(Y/N) : ";
            cin >> is;
            if (is == 'Y' || is == 'y')
            {
                re = sq->deleteData(id);
                if (re == 0)
                    cout << "ERROR!数据库发生错误！" << endl;
                else
                    cout << "删除成功！" << endl;
            }
            else
                cout << "您已取消删除操作！" << endl;
            break;
        case 5:
            row = 0;
            reList = sq->getAll(row,col);
            if (row > 0)
            {
                string json = "";
                string strOut="[";
                int nIndex = col;
                for (int i = 0; i < row; i++)
                {
                    strOut += strOut.length() > 1 ? ",{" : "{";
                    for (int j = 0; j < col; j++)
                    {
                        json += json.length() > 0 ? "," : "";
                        json += "\""+(string)U2G(reList[j])+"\"";
                        json += ":";
                        json += "\"" + (string)U2G(reList[nIndex]) + "\"";
                        //strOut += "\t"; 
                        ++nIndex;
                    }
                    strOut += json+"}";
                    json = "";
                }
                strOut += "]";
                cout << strOut << endl;
            }
            else
            {
                cout << "没有数据！" << endl;
            }
            break;
        case 6:
            system("cls");
            menu();
            break;
        case 7:
            string sql = "insert into msg (info,memo,CARDTYPE) values ('aaa','BBB','')";
            re = sq->addDataMsg(sql);
                cout << "添加信息成功！" << endl;
            break;
        }
        cout << "请输入您的选项："; cin >> index;
    }
}

void menu()
{
    cout << "******通讯录菜单*****" << endl;
    cout << "*  1. 录入一条通讯信息" << endl;
    cout << "*  2. 通过手机号查询信息" << endl;
    cout << "*  3. 修改一条信息" << endl;
    cout << "*  4. 删除一条信息" << endl;
    cout << "*  5. 查看全部通讯录信息" << endl;
    cout << "*  6. 清屏并且弹出菜单" << endl;
    cout << "*  7. table Msg instert" << endl;
    cout << "*  0. 退出" << endl;
}