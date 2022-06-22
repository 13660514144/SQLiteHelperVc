#if !defined(AFX_SQLITEHELPER_H__59F8C44E_0D98_4422_AEB1_2FD927EE8902__INCLUDED_)
#define AFX_SQLITEHELPER_H__59F8C44E_0D98_4422_AEB1_2FD927EE8902__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "sqlite3.h"
#include <windows.h>
class SQLiteHelper
{
public:
	SQLiteHelper();
	virtual ~SQLiteHelper();
	sqlite3* db;
	void execSQL(char* sql);
	char** rawQuery(char* sql, int* row, int* column, char** result);
	void openDB(char* path);
	void closeDB();

};
#endif // !defined(AFX_SQLITEHELPER_H__59F8C44E_0D98_4422_AEB1_2FD927EE8902__INCLUDED_)

