#include <iostream>
#include <string>
#include "sqlite3.h"
using namespace std;

#pragma comment(lib,"sqlite3.lib")

class SqlController
{
public:
    sqlite3* db;
    string table;
    string dbname;

    SqlController(string c_dbname, string c_tablename)
    {
        table = c_tablename;
        dbname = c_dbname;
    }

    int addDataMsg(string SQL);
    //增加数据，成功返回1
    int addData(string name, string telphone, string email, string type, string remark);
    //根据手机号查询数据, 根据表的结构，如果有数据那么有两行，有6列，返回的值是个一维字符串数组，re[0 - 5]是字段
    char** getInfoByTel(string telphone);
    //根据id获得信息
    char** getInfoById(int id);
    //获取全部数据
    char** getAll(int& row,int& col);
    //修改一条信息，成功返回1
    int changeData(int id, string name, string telphone, string email, string type, string remark);
    //删除一条信息，成功返回1
    int deleteData(int id);
};