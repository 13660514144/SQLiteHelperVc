#include "controller.h"
#include <sstream>

int SqlController::addDataMsg(string SQLstr)
{
    int rc;
    const char* sql;
    char* zErrMsg;
    string s;
    //判断数据库是否存在
    rc = sqlite3_open(dbname.data(), &db);
    if (rc) {       //数据库不存在
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }
    else {      //数据库存在
        fprintf(stderr, "Opened database successfully\n");
        //判断是否已经存在该手机号

        int nRow, nCol;
        
        sql = SQLstr.data();
         
        cout << sql << endl;
        // 开始插入数据
        rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
        if (rc != SQLITE_OK) {  //如果不成功
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            return 0;
        }
        else {      // 成功
            fprintf(stdout, "AddData successfully\n");
        }
    }
    sqlite3_close(db);
    return 1;
}
//增加数据
int SqlController::addData(string name, string telphone, string email, string type, string remark)
{
    int rc;
    const char* sql;
    char* zErrMsg;
    string s;
    //判断数据库是否存在
    rc = sqlite3_open(dbname.data(), &db);
    if (rc) {       //数据库不存在
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }
    else {      //数据库存在
        fprintf(stderr, "Opened database successfully\n");
        //判断是否已经存在该手机号
        char** pResult;
        int nRow, nCol;
        s = "SELECT * FROM '" + table + "' WHERE telphone= '" + telphone + "';";
        sql = s.data();
        rc = sqlite3_get_table(db, sql, &pResult, &nRow, &nCol, NULL);
        if (rc == SQLITE_OK)
        {
            if (nRow >= 1)
                return 2;       //表示该手机号已被登记
        }
        sqlite3_free_table(pResult);
        // 尝试插入数据
        s = "INSERT INTO '" + table + "' (NAME,TELPHONE,EMAIL,TYPE,REMARK) VALUES ('" + \
            name + "','" + telphone + "','" + email + "','" + type + "','" + remark + "' );";
        sql = s.data();
        cout << sql << endl;
        // 开始插入数据
        rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
        if (rc != SQLITE_OK) {  //如果不成功
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            return 0;
        }
        else {      // 成功
            fprintf(stdout, "AddData successfully\n");
        }
    }
    sqlite3_close(db);
    return 1;
}

//修改数据
int SqlController::changeData(int id, string name, string telphone, string email, string type, string remark)
{
    int rc;
    const char* sql;
    char* zErrMsg;
    string s, str;
    stringstream ss;
    ss << id;
    ss >> str;
    //判断数据库是否存在
    rc = sqlite3_open(dbname.data(), &db);
    if (rc) {       //数据库不存在
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }
    else {      //数据库存在
        fprintf(stderr, "Opened database successfully\n");
        s = "UPDATE '" + table + "' SET name='" + name + "',telphone='" + telphone + "', email ='" + email + "',type = '" + type + "',remark = '" + remark + "'  WHERE id = " + str + ";";
        sql = s.data();
        cout << sql << endl;
        // 开始插入数据
        rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
        if (rc != SQLITE_OK) {  //如果不成功
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            return 0;
        }
        else {      // 成功
            fprintf(stdout, "ChangeData successfully\n");
        }
    }
    sqlite3_close(db);
    return 1;
}

//删除数据
int SqlController::deleteData(int id)
{
    int rc;
    const char* sql;
    char* zErrMsg;
    string s, str;
    stringstream ss;
    ss << id;
    ss >> str;
    //判断数据库是否存在
    rc = sqlite3_open(dbname.data(), &db);
    if (rc) {       //数据库不存在
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }
    else {      //数据库存在
        fprintf(stderr, "Opened database successfully\n");
        //判断是否已经存在该手机号
        char** pResult;
        int nRow, nCol;
        s = "SELECT * FROM '" + table + "' WHERE id= '" + str + "';";
        sql = s.data();
        rc = sqlite3_get_table(db, sql, &pResult, &nRow, &nCol, NULL);
        if (rc == SQLITE_OK)
        {
            if (nRow < 1)
                return 2;       //表示该id不存在
        }
        sqlite3_free_table(pResult);
        s = "DELETE FROM '" + table + "'  WHERE id = " + str + ";";
        sql = s.data();
        cout << sql << endl;
        // 开始删除数据
        rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
        if (rc != SQLITE_OK) {  //如果不成功
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            return 0;
        }
        else {      // 成功
            fprintf(stdout, "DeleteData successfully\n");
        }
    }
    sqlite3_close(db);
    return 1;
}

//根据手机号精确查找,返回数组的第一个值为no表示手机号不存在，返回error表示数据库错误
char** SqlController::getInfoByTel(string telphone)
{
    int rc, nRow, nCol;
    const char* sql;
    char** pResult;
    char* pErr[] = { "error" };           //char* a [] 等价于 char **, 是一个char的指针数组
    char* pNoTel[] = { "no" };
    char* zErrMsg;
    string s;
    //判断数据库是否存在
    rc = sqlite3_open(dbname.data(), &db);
    if (rc) {       //数据库不存在
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return pErr;
    }
    else {      //数据库存在
        fprintf(stderr, "Opened database successfully\n");

        //开始查找该手机号
        s = "SELECT * FROM '" + table + "'  WHERE telphone = '" + telphone + "';";
        sql = s.data();
        cout << sql << endl;
        rc = sqlite3_get_table(db, sql, &pResult, &nRow, &nCol, &zErrMsg);
        if (rc != SQLITE_OK) {  //如果不成功
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            return pErr;
        }
        else {      // 成功
            fprintf(stdout, "Select Info With Tel successfully\n");
            if (nRow < 1)   //该手机号信息不存在
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
    char* pErr[] = { "error" };           //char* a [] 等价于 char **, 是一个char的指针数组
    char* pNo[] = { "no" };
    char* zErrMsg;
    string s, str;
    stringstream ss;
    ss << id;
    ss >> str;
    //判断数据库是否存在
    rc = sqlite3_open(dbname.data(), &db);
    if (rc) {       //数据库不存在
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return pErr;
    }
    else {      //数据库存在
        fprintf(stderr, "Opened database successfully\n");
        //开始查找该id
        s = "SELECT * FROM '" + table + "'  WHERE id = " + str + ";";
        sql = s.data();
        cout << sql << endl;
        rc = sqlite3_get_table(db, sql, &pResult, &nRow, &nCol, &zErrMsg);
        if (rc != SQLITE_OK) {  //如果不成功
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            return pErr;
        }
        else {      // 成功
            fprintf(stdout, "Select Info With Tel successfully\n");
            if (nRow < 1)   //该id信息不存在
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
    char* pErr[] = { "error" };           //char* a [] 等价于 char **, 是一个char的指针数组
    char* pNo[] = { "no" };
    char* zErrMsg;
    string s;
    //判断数据库是否存在
    rc = sqlite3_open(dbname.data(), &db);
    if (rc) {       //数据库不存在
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return pErr;
    }
    else {      //数据库存在
        fprintf(stderr, "Opened database successfully\n");
        //开始查询数据
        s = "SELECT * FROM " + table + ";";
        sql = s.data();
        cout << sql << endl;
        rc = sqlite3_get_table(db, sql, &pResult, &nRow, &nCol, &zErrMsg);
        if (rc != SQLITE_OK) {  //如果不成功
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            return pErr;
        }
        else {      // 成功
            fprintf(stdout, "Select Info With Tel successfully\n");
            if (nRow < 1)   //没有任何信息
                return pNo;
            else {
                row = nRow;     //返回行数，那么一共有6*row个元素
                col = nCol;
                return pResult;
            }
        }
        sqlite3_free_table(pResult);
    }
    sqlite3_close(db);
    return pErr;
}