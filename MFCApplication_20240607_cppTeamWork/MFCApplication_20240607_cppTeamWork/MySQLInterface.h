#pragma once
#include <winsock2.h>
#include "../include/mysql.h"
#include "pch.h"
#include <iostream>
#include "MFCApplication_20240607_cppTeamWorkDoc.h"
#pragma comment(lib,"..\\lib\\libmysql.lib")
#define SQL_MAX 1024//SQL语句最大长度

class MySQLInterface//这个类专门放各种MySQL操作的接口
{
public:
	MYSQL_RES* resultSet;//结果集
	MYSQL_ROW row;//行数据
	MYSQL mysqlConnection;//连接

	char sql[SQL_MAX];//SQL语句

	bool ConnectMySQL();//连接MySQL
	bool GetAllInfo();//获取所有信息
	bool AddInfoToMySQL(Point pt);//添加信息到数据库
	bool DelInfoToMySQL(Point pt, int n);//删除信息到数据库
	bool UpdateInfoToMySQL(int n, Point pt);//修改信息到数据库
	PointArr FindPointInMySQL(Point pt, int& nFind);//在数据库中查找控制点的相关信息
};

