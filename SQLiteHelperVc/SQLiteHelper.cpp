#include "SQLiteHelper.h"
#include <iostream>
using namespace std;

//
// Construction/Destruction
//

SQLiteHelper::SQLiteHelper()
{

}

SQLiteHelper::~SQLiteHelper()
{

}
void SQLiteHelper::execSQL(char* sql)
{
	sqlite3_exec(db, sql, NULL, NULL, 0);
}
char** SQLiteHelper::rawQuery(char* sql, int* row, int* column, char** result)
{
	sqlite3_get_table(db, sql, &result, row, column, 0);
	return result;
}
void SQLiteHelper::openDB(char* path)
{
	int last = sqlite3_open(path, &db);
	if (SQLITE_OK != last)
	{
		cout << "打开数据库出错" << endl;
		return;
		PostQuitMessage(0);
	}
}
void SQLiteHelper::closeDB()
{
	sqlite3_close(db);
}
