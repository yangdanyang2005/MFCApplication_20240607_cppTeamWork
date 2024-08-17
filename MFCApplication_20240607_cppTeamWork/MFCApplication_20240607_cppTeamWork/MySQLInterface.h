#pragma once
#include <winsock2.h>
#include "../include/mysql.h"
#include "pch.h"
#include <iostream>
#include "MFCApplication_20240607_cppTeamWorkDoc.h"
#pragma comment(lib,"..\\lib\\libmysql.lib")
#define SQL_MAX 1024//SQL�����󳤶�

class MySQLInterface//�����ר�ŷŸ���MySQL�����Ľӿ�
{
public:
	MYSQL_RES* resultSet;//�����
	MYSQL_ROW row;//������
	MYSQL mysqlConnection;//����

	char sql[SQL_MAX];//SQL���

	bool ConnectMySQL();//����MySQL
	bool GetAllInfo();//��ȡ������Ϣ
	bool AddInfoToMySQL(Point pt);//�����Ϣ�����ݿ�
	bool DelInfoToMySQL(Point pt, int n);//ɾ����Ϣ�����ݿ�
	bool UpdateInfoToMySQL(int n, Point pt);//�޸���Ϣ�����ݿ�
	PointArr FindPointInMySQL(Point pt, int& nFind);//�����ݿ��в��ҿ��Ƶ�������Ϣ
};

