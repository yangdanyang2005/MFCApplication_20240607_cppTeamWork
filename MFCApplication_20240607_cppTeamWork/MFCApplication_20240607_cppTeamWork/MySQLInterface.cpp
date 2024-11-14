#include "MySQLInterface.h"

bool MySQLInterface::ConnectMySQL()
{
	// https://www.bilibili.com/video/BV1Lj411t78a?p=5&vd_source=057c21513e5e5504cbd6236251ad85fb

	mysql_init(&mysqlConnection);
	if (mysql_real_connect(&mysqlConnection, "localhost", "root", "2023302131", "cmfcapplication20240607cppteamworkinfo", 3306, NULL, 0) == NULL)
		/*"localhost" 是 MySQL 服务器的地址（主机名称，注意不是连接名称！）。
		"root" 是登录用户名。
		"2023302131" 是登录密码。
		"cmfcapplication20240607cppteamworkinfo" 是要连接的数据库名。
		port 是 MySQL 服务器的端口号，通常为 3306。
		最后两个参数通常可以设置为 NULL 和 0。*/
	{
		AfxMessageBox(_T("MySQL连接失败！失败原因：%s", mysql_error(&mysqlConnection)));
		return false;
	}
	else
	{
		mysql_query(&mysqlConnection, "set names 'GB2312'");//设置编码为GB2312，防止从数据库中读取数据后显示中文乱码
	}
	return true;
}

// 查询数据库中所有数据并将数据写入arrSQL数组中
bool MySQLInterface::GetAllInfo()
{
	ConnectMySQL();
	CFrameWnd* pMainFrame = (CFrameWnd*)AfxGetMainWnd();
	CFrameWnd* pActiveFrame = pMainFrame->GetActiveFrame();
	CDocument* pActiveDocument = pActiveFrame->GetActiveDocument();
	CMFCApplication20240607cppTeamWorkDoc* pDoc = dynamic_cast<CMFCApplication20240607cppTeamWorkDoc*>(pActiveDocument);//从文档读取变量数据到对话框中

	//https://blog.csdn.net/cpp_learner/article/details/116171955

	//MYSQL mysql;		// 数据库句柄
	//MYSQL_RES* res;		// 查询结果集
	//MYSQL_ROW row;		// 记录结构体
	//char sql[SQL_MAX];	// SQL语句
	//// 连接数据库
	//if (!connectDB(mysql)) {
	//	return false;
	//}

	// C语言组合字符串
	snprintf(sql, SQL_MAX, "SELECT * FROM gcpinfo20240815");// 构造SQL查询全部数据的语句
	//printf("查询sql语句：%s\n", sql);

	// 查询数据
	//int ret = mysql_query(&mysqlConnection, "select * from student;");		// 等效于下面一行代码
	//int ret = mysql_query(&mysqlConnection, sql);
	int ret = mysql_real_query(&mysqlConnection, sql, (unsigned long)strlen(sql));
	//printf("执行查询语句，查询返回结果：%d\n", ret);

	// 判断查询是否成功
	if (ret) {
		AfxMessageBox(_T("数据查询失败！失败原因：%s\n", mysql_error(&mysqlConnection)));
		return false;
	}

	//如果查询成功，则获取结果集
	//printf("数据查询成功！\n");
	resultSet = mysql_store_result(&mysqlConnection);
	int count = mysql_num_rows(resultSet);
	pDoc->arrSQL.m_Num = count;
	// 循环条件：获取查询到的一行（row）数据，判断row是否为空，不为空就向数组中写入数据
	for (int i = 0; row = mysql_fetch_row(resultSet); i++) {
		//将数据库中的数据存入pDoc->arrSQL.m_PointArr数组中
		pDoc->arrSQL.m_PointArr[i].setSerialNum(atoi(row[0]));
		pDoc->arrSQL.m_PointArr[i].setName(row[1]);
		pDoc->arrSQL.m_PointArr[i].setX(atof(row[2]));
		pDoc->arrSQL.m_PointArr[i].setY(atof(row[3]));
		pDoc->arrSQL.m_PointArr[i].setZ(atof(row[4]));
	}

	// 释放结果集
	mysql_free_result(resultSet);

	//// 关闭数据库
	//mysql_close(&mysqlConnection);

	return true;

}

bool MySQLInterface::AddInfoToMySQL(Point pt)
{
	//ConnectMySQL();
	//https://blog.csdn.net/cpp_learner/article/details/116171955

	// C语言字符串组合
	snprintf(sql, SQL_MAX, "INSERT INTO gcpinfo20240815 VALUES(%d, '%s', %lf, %lf, %lf);", pt.getSerialNum(), pt.getName().c_str(), pt.getX(), pt.getY(), pt.getZ());
	// 如果id字段用了auto_increment进行修饰，那么可以使用以下数据库语句：
	// snprintf(sql, SQL_MAX, "INSERT INTO gcpinfo20240815(name, age, sex) VALUES('%s', %d, '%s');", name, age, sex);

	// 执行SQL语句，查询数据，如果成功返回0
	int ret = mysql_real_query(&mysqlConnection, sql, (unsigned long)strlen(sql));
	//printf("执行插入语句，插入返回结果：%d\n", ret);

	if (ret) {
		return false;
	}

	return true;
}

bool MySQLInterface::DelInfoToMySQL(Point pt, int n)
{
	// C语言字符串组合
	snprintf(sql, SQL_MAX, "DELETE FROM gcpinfo20240815 WHERE m_SerialNum = %d;", pt.getSerialNum());
	// 执行SQL语句，查询数据，如果成功返回0
	int ret = mysql_real_query(&mysqlConnection, sql, (unsigned long)strlen(sql));
	// 判断查询是否成功
	if (ret) {
		AfxMessageBox(_T("删除表数据失败！失败原因：%s\n", mysql_error(&mysqlConnection)));
		return false;
	}
	else
	{
		for (int i = pt.getSerialNum(); i < n - 1; i++)//n是原有的数据总数
		{
			snprintf(sql, SQL_MAX, "UPDATE gcpinfo20240815 SET m_SerialNum = %d WHERE m_SerialNum = %d;", i, i);
			if (ret)
			{
				AfxMessageBox(_T("对表中数据重新编写序号失败！失败原因：%s\n", mysql_error(&mysqlConnection)));
				return false;
			}
		}
	}
	return true;
}

bool MySQLInterface::UpdateInfoToMySQL(int nIndex, Point pt)
{
	// C语言组合字符串
	snprintf(sql, SQL_MAX, "UPDATE gcpinfo20240815 SET m_SerialNum = %d, m_Name = %s, m_X = %lf, m_Y = %lf, m_Z = %lf WHERE m_SerialNum = %d;", nIndex + 1, pt.getName().c_str(), pt.getX(), pt.getY(), pt.getZ(), nIndex + 1);
	// 执行SQL语句，查询数据，如果成功返回0
	int ret = mysql_real_query(&mysqlConnection, sql, (unsigned long)strlen(sql));
	// 判断查询是否成功
	if (ret)
	{
		AfxMessageBox(_T("数据修改失败！失败原因：%s\n", mysql_error(&mysqlConnection)));
		return false;
	}
	return true;
}

PointArr MySQLInterface::FindPointInMySQL(Point pt, int& nFind)
{
	PointArr resultPoints;
	resultPoints.m_PointArr = new Point[1024];
	nFind = 0;

	//// C语言组合字符串
	//snprintf(sql, SQL_MAX, "SELECT * FROM gcpinfo20240815 WHERE m_Name = '%s';");
	//// 查询数据
	////int ret = mysql_query(&mysql, "select * from student;");		// 等效于下面一行代码
	////int ret = mysql_query(&mysql, sql);
	//int ret = mysql_real_query(&mysqlConnection, sql, (unsigned long)strlen(sql));
	//printf("执行查询语句，查询返回结果：%d\n", ret);
	//if (ret) {
	//	printf("数据查询失败！失败原因：%s\n", mysql_error(&mysqlConnection));
	//}
	//printf("数据查询成功！\n");
	//// 获取结果集
	//res = mysql_store_result(&mysqlConnection);
	//// 获取查询到的一行数据
	//// 给row赋值，判断row是否为空，不为空就打印数据。
	//while (row = mysql_fetch_row(res)) {
	//	printf("%d  ", atoi(row[0]));	// 转换为int类型，打印id
	//	printf("%s  ", row[1]);			// 打印姓名
	//	printf("%d  ", atoi(row[2]));	// 转换为int类型，打印年龄
	//	printf("%s  \n", row[3]);		// 打印性别
	//}
	//// 释放结果集
	//mysql_free_result(res);
	//mysql_close(&mysql);

	string query = "SELECT * FROM gcpinfo20240815 WHERE";
	bool hasCondition = false;

	if (!pt.getName().empty()) {
		query += " m_Name = '" + pt.getName() + "'";
		hasCondition = true;
	}
	if (pt.getX() != 0) {
		if (hasCondition) query += " AND";
		query += " m_X = " + to_string(pt.getX());
		hasCondition = true;
	}
	if (pt.getY() != 0) {
		if (hasCondition) query += " AND";
		query += " m_Y = " + to_string(pt.getY());
		hasCondition = true;
	}
	if (pt.getZ() != 0) {
		if (hasCondition) query += " AND";
		query += " m_Z = " +to_string(pt.getZ());
		hasCondition = true;
	}

	query += ";";

	if (!hasCondition) {
		AfxMessageBox(_T("在数据库中没有查找到符合条件的点！"));
		return resultPoints;
	}

	snprintf(sql, SQL_MAX, "%s", query.c_str());

	if (mysql_query(&mysqlConnection, sql)) {
		AfxMessageBox(_T("查询失败！失败原因：%s", mysql_error(&mysqlConnection)));
		return resultPoints;
	}

	resultSet = mysql_store_result(&mysqlConnection);
	if (!resultSet) {
		AfxMessageBox(_T("结果集为空！错误原因：%s", mysql_error(&mysqlConnection)));
		return resultPoints;
	}

	while ((row = mysql_fetch_row(resultSet))) {
		Point foundPoint;
		foundPoint.setSerialNum(atoi(row[0]));
		foundPoint.setName(row[1]);
		foundPoint.setX(atof(row[2]));
		foundPoint.setY(atof(row[3]));
		foundPoint.setZ(atof(row[4]));
		resultPoints.push_back(foundPoint);
	}

	nFind = resultPoints.m_Num;
	mysql_free_result(resultSet);

	return resultPoints;
}
