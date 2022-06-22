#include "controller.h"
#include <sstream>

int SqlController::addDataMsg(string SQLstr)
{
    int rc;
    const char* sql;
    char* zErrMsg;
    string s;
    //�ж����ݿ��Ƿ����
    rc = sqlite3_open(dbname.data(), &db);
    if (rc) {       //���ݿⲻ����
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }
    else {      //���ݿ����
        fprintf(stderr, "Opened database successfully\n");
        //�ж��Ƿ��Ѿ����ڸ��ֻ���

        int nRow, nCol;
        
        sql = SQLstr.data();
         
        cout << sql << endl;
        // ��ʼ��������
        rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
        if (rc != SQLITE_OK) {  //������ɹ�
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            return 0;
        }
        else {      // �ɹ�
            fprintf(stdout, "AddData successfully\n");
        }
    }
    sqlite3_close(db);
    return 1;
}
//��������
int SqlController::addData(string name, string telphone, string email, string type, string remark)
{
    int rc;
    const char* sql;
    char* zErrMsg;
    string s;
    //�ж����ݿ��Ƿ����
    rc = sqlite3_open(dbname.data(), &db);
    if (rc) {       //���ݿⲻ����
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }
    else {      //���ݿ����
        fprintf(stderr, "Opened database successfully\n");
        //�ж��Ƿ��Ѿ����ڸ��ֻ���
        char** pResult;
        int nRow, nCol;
        s = "SELECT * FROM '" + table + "' WHERE telphone= '" + telphone + "';";
        sql = s.data();
        rc = sqlite3_get_table(db, sql, &pResult, &nRow, &nCol, NULL);
        if (rc == SQLITE_OK)
        {
            if (nRow >= 1)
                return 2;       //��ʾ���ֻ����ѱ��Ǽ�
        }
        sqlite3_free_table(pResult);
        // ���Բ�������
        s = "INSERT INTO '" + table + "' (NAME,TELPHONE,EMAIL,TYPE,REMARK) VALUES ('" + \
            name + "','" + telphone + "','" + email + "','" + type + "','" + remark + "' );";
        sql = s.data();
        cout << sql << endl;
        // ��ʼ��������
        rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
        if (rc != SQLITE_OK) {  //������ɹ�
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            return 0;
        }
        else {      // �ɹ�
            fprintf(stdout, "AddData successfully\n");
        }
    }
    sqlite3_close(db);
    return 1;
}

//�޸�����
int SqlController::changeData(int id, string name, string telphone, string email, string type, string remark)
{
    int rc;
    const char* sql;
    char* zErrMsg;
    string s, str;
    stringstream ss;
    ss << id;
    ss >> str;
    //�ж����ݿ��Ƿ����
    rc = sqlite3_open(dbname.data(), &db);
    if (rc) {       //���ݿⲻ����
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }
    else {      //���ݿ����
        fprintf(stderr, "Opened database successfully\n");
        s = "UPDATE '" + table + "' SET name='" + name + "',telphone='" + telphone + "', email ='" + email + "',type = '" + type + "',remark = '" + remark + "'  WHERE id = " + str + ";";
        sql = s.data();
        cout << sql << endl;
        // ��ʼ��������
        rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
        if (rc != SQLITE_OK) {  //������ɹ�
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            return 0;
        }
        else {      // �ɹ�
            fprintf(stdout, "ChangeData successfully\n");
        }
    }
    sqlite3_close(db);
    return 1;
}

//ɾ������
int SqlController::deleteData(int id)
{
    int rc;
    const char* sql;
    char* zErrMsg;
    string s, str;
    stringstream ss;
    ss << id;
    ss >> str;
    //�ж����ݿ��Ƿ����
    rc = sqlite3_open(dbname.data(), &db);
    if (rc) {       //���ݿⲻ����
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }
    else {      //���ݿ����
        fprintf(stderr, "Opened database successfully\n");
        //�ж��Ƿ��Ѿ����ڸ��ֻ���
        char** pResult;
        int nRow, nCol;
        s = "SELECT * FROM '" + table + "' WHERE id= '" + str + "';";
        sql = s.data();
        rc = sqlite3_get_table(db, sql, &pResult, &nRow, &nCol, NULL);
        if (rc == SQLITE_OK)
        {
            if (nRow < 1)
                return 2;       //��ʾ��id������
        }
        sqlite3_free_table(pResult);
        s = "DELETE FROM '" + table + "'  WHERE id = " + str + ";";
        sql = s.data();
        cout << sql << endl;
        // ��ʼɾ������
        rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
        if (rc != SQLITE_OK) {  //������ɹ�
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            return 0;
        }
        else {      // �ɹ�
            fprintf(stdout, "DeleteData successfully\n");
        }
    }
    sqlite3_close(db);
    return 1;
}

//�����ֻ��ž�ȷ����,��������ĵ�һ��ֵΪno��ʾ�ֻ��Ų����ڣ�����error��ʾ���ݿ����
char** SqlController::getInfoByTel(string telphone)
{
    int rc, nRow, nCol;
    const char* sql;
    char** pResult;
    char* pErr[] = { "error" };           //char* a [] �ȼ��� char **, ��һ��char��ָ������
    char* pNoTel[] = { "no" };
    char* zErrMsg;
    string s;
    //�ж����ݿ��Ƿ����
    rc = sqlite3_open(dbname.data(), &db);
    if (rc) {       //���ݿⲻ����
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return pErr;
    }
    else {      //���ݿ����
        fprintf(stderr, "Opened database successfully\n");

        //��ʼ���Ҹ��ֻ���
        s = "SELECT * FROM '" + table + "'  WHERE telphone = '" + telphone + "';";
        sql = s.data();
        cout << sql << endl;
        rc = sqlite3_get_table(db, sql, &pResult, &nRow, &nCol, &zErrMsg);
        if (rc != SQLITE_OK) {  //������ɹ�
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            return pErr;
        }
        else {      // �ɹ�
            fprintf(stdout, "Select Info With Tel successfully\n");
            if (nRow < 1)   //���ֻ�����Ϣ������
                return pNoTel;
            else {
                return pResult;
            }
        }
        sqlite3_free_table(pResult);
    }
    sqlite3_close(db);
    return pErr;
}

char** SqlController::getInfoById(int id)
{
    int rc, nRow, nCol;
    const char* sql;
    char** pResult;
    char* pErr[] = { "error" };           //char* a [] �ȼ��� char **, ��һ��char��ָ������
    char* pNo[] = { "no" };
    char* zErrMsg;
    string s, str;
    stringstream ss;
    ss << id;
    ss >> str;
    //�ж����ݿ��Ƿ����
    rc = sqlite3_open(dbname.data(), &db);
    if (rc) {       //���ݿⲻ����
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return pErr;
    }
    else {      //���ݿ����
        fprintf(stderr, "Opened database successfully\n");
        //��ʼ���Ҹ�id
        s = "SELECT * FROM '" + table + "'  WHERE id = " + str + ";";
        sql = s.data();
        cout << sql << endl;
        rc = sqlite3_get_table(db, sql, &pResult, &nRow, &nCol, &zErrMsg);
        if (rc != SQLITE_OK) {  //������ɹ�
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            return pErr;
        }
        else {      // �ɹ�
            fprintf(stdout, "Select Info With Tel successfully\n");
            if (nRow < 1)   //��id��Ϣ������
                return pNo;
            else {
                return pResult;
            }
        }
        sqlite3_free_table(pResult);
    }
    sqlite3_close(db);
    return pErr;
}

char** SqlController::getAll(int& row,int& col)
{
    int rc, nRow, nCol;
    const char* sql;
    char** pResult;
    char* pErr[] = { "error" };           //char* a [] �ȼ��� char **, ��һ��char��ָ������
    char* pNo[] = { "no" };
    char* zErrMsg;
    string s;
    //�ж����ݿ��Ƿ����
    rc = sqlite3_open(dbname.data(), &db);
    if (rc) {       //���ݿⲻ����
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return pErr;
    }
    else {      //���ݿ����
        fprintf(stderr, "Opened database successfully\n");
        //��ʼ��ѯ����
        s = "SELECT * FROM " + table + ";";
        sql = s.data();
        cout << sql << endl;
        rc = sqlite3_get_table(db, sql, &pResult, &nRow, &nCol, &zErrMsg);
        if (rc != SQLITE_OK) {  //������ɹ�
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            return pErr;
        }
        else {      // �ɹ�
            fprintf(stdout, "Select Info With Tel successfully\n");
            if (nRow < 1)   //û���κ���Ϣ
                return pNo;
            else {
                row = nRow;     //������������ôһ����6*row��Ԫ��
                col = nCol;
                return pResult;
            }
        }
        sqlite3_free_table(pResult);
    }
    sqlite3_close(db);
    return pErr;
}