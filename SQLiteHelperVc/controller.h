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
    //�������ݣ��ɹ�����1
    int addData(string name, string telphone, string email, string type, string remark);
    //�����ֻ��Ų�ѯ����, ���ݱ�Ľṹ�������������ô�����У���6�У����ص�ֵ�Ǹ�һά�ַ������飬re[0 - 5]���ֶ�
    char** getInfoByTel(string telphone);
    //����id�����Ϣ
    char** getInfoById(int id);
    //��ȡȫ������
    char** getAll(int& row,int& col);
    //�޸�һ����Ϣ���ɹ�����1
    int changeData(int id, string name, string telphone, string email, string type, string remark);
    //ɾ��һ����Ϣ���ɹ�����1
    int deleteData(int id);
};