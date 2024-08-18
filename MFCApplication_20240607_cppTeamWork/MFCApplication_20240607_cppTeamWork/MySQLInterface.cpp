#include "MySQLInterface.h"

bool MySQLInterface::ConnectMySQL()
{
	// https://www.bilibili.com/video/BV1Lj411t78a?p=5&vd_source=057c21513e5e5504cbd6236251ad85fb

	mysql_init(&mysqlConnection);
	if (mysql_real_connect(&mysqlConnection, "localhost", "root", "2023302131", "cmfcapplication20240607cppteamworkinfo", 3306, NULL, 0) == NULL)
		/*"localhost" �� MySQL �������ĵ�ַ���������ƣ�ע�ⲻ���������ƣ�����
		"root" �ǵ�¼�û�����
		"2023302131" �ǵ�¼���롣
		"cmfcapplication20240607cppteamworkinfo" ��Ҫ���ӵ����ݿ�����
		port �� MySQL �������Ķ˿ںţ�ͨ��Ϊ 3306��
		�����������ͨ����������Ϊ NULL �� 0��*/
	{
		AfxMessageBox(_T("MySQL����ʧ�ܣ�ʧ��ԭ��%s", mysql_error(&mysqlConnection)));
		return false;
	}
	else
	{
		mysql_query(&mysqlConnection, "set names 'GB2312'");//���ñ���ΪGB2312����ֹ�����ݿ��ж�ȡ���ݺ���ʾ��������
	}
	return true;
}

// ��ѯ���ݿ����������ݲ�������д��arrSQL������
bool MySQLInterface::GetAllInfo()
{
	ConnectMySQL();
	CFrameWnd* pMainFrame = (CFrameWnd*)AfxGetMainWnd();
	CFrameWnd* pActiveFrame = pMainFrame->GetActiveFrame();
	CDocument* pActiveDocument = pActiveFrame->GetActiveDocument();
	CMFCApplication20240607cppTeamWorkDoc* pDoc = dynamic_cast<CMFCApplication20240607cppTeamWorkDoc*>(pActiveDocument);//���ĵ���ȡ�������ݵ��Ի�����

	//https://blog.csdn.net/cpp_learner/article/details/116171955

	//MYSQL mysql;		// ���ݿ���
	//MYSQL_RES* res;		// ��ѯ�����
	//MYSQL_ROW row;		// ��¼�ṹ��
	//char sql[SQL_MAX];	// SQL���
	//// �������ݿ�
	//if (!connectDB(mysql)) {
	//	return false;
	//}

	// C��������ַ���
	snprintf(sql, SQL_MAX, "SELECT * FROM gcpinfo20240815");// ����SQL��ѯȫ�����ݵ����
	//printf("��ѯsql��䣺%s\n", sql);

	// ��ѯ����
	//int ret = mysql_query(&mysqlConnection, "select * from student;");		// ��Ч������һ�д���
	//int ret = mysql_query(&mysqlConnection, sql);
	int ret = mysql_real_query(&mysqlConnection, sql, (unsigned long)strlen(sql));
	//printf("ִ�в�ѯ��䣬��ѯ���ؽ����%d\n", ret);

	// �жϲ�ѯ�Ƿ�ɹ�
	if (ret) {
		AfxMessageBox(_T("���ݲ�ѯʧ�ܣ�ʧ��ԭ��%s\n", mysql_error(&mysqlConnection)));
		return false;
	}

	//�����ѯ�ɹ������ȡ�����
	//printf("���ݲ�ѯ�ɹ���\n");
	resultSet = mysql_store_result(&mysqlConnection);
	int count = mysql_num_rows(resultSet);
	pDoc->arrSQL.m_Num = count;
	// ѭ����������ȡ��ѯ����һ�У�row�����ݣ��ж�row�Ƿ�Ϊ�գ���Ϊ�վ���������д������
	for (int i = 0; row = mysql_fetch_row(resultSet); i++) {
		//�����ݿ��е����ݴ���pDoc->arrSQL.m_PointArr������
		pDoc->arrSQL.m_PointArr[i].setSerialNum(atoi(row[0]));
		pDoc->arrSQL.m_PointArr[i].setName(row[1]);
		pDoc->arrSQL.m_PointArr[i].setX(atof(row[2]));
		pDoc->arrSQL.m_PointArr[i].setY(atof(row[3]));
		pDoc->arrSQL.m_PointArr[i].setZ(atof(row[4]));
	}

	// �ͷŽ����
	mysql_free_result(resultSet);

	//// �ر����ݿ�
	//mysql_close(&mysqlConnection);

	return true;

}

bool MySQLInterface::AddInfoToMySQL(Point pt)
{
	//ConnectMySQL();
	//https://blog.csdn.net/cpp_learner/article/details/116171955

	// C�����ַ������
	snprintf(sql, SQL_MAX, "INSERT INTO gcpinfo20240815 VALUES(%d, '%s', %lf, %lf, %lf);", pt.getSerialNum(), pt.getName().c_str(), pt.getX(), pt.getY(), pt.getZ());
	// ���id�ֶ�����auto_increment�������Σ���ô����ʹ���������ݿ���䣺
	// snprintf(sql, SQL_MAX, "INSERT INTO gcpinfo20240815(name, age, sex) VALUES('%s', %d, '%s');", name, age, sex);

	// ִ��SQL��䣬��ѯ���ݣ�����ɹ�����0
	int ret = mysql_real_query(&mysqlConnection, sql, (unsigned long)strlen(sql));
	//printf("ִ�в�����䣬���뷵�ؽ����%d\n", ret);

	if (ret) {
		return false;
	}

	return true;
}

bool MySQLInterface::DelInfoToMySQL(Point pt, int n)
{
	// C�����ַ������
	snprintf(sql, SQL_MAX, "DELETE FROM gcpinfo20240815 WHERE m_SerialNum = %d;", pt.getSerialNum());
	// ִ��SQL��䣬��ѯ���ݣ�����ɹ�����0
	int ret = mysql_real_query(&mysqlConnection, sql, (unsigned long)strlen(sql));
	// �жϲ�ѯ�Ƿ�ɹ�
	if (ret) {
		AfxMessageBox(_T("ɾ��������ʧ�ܣ�ʧ��ԭ��%s\n", mysql_error(&mysqlConnection)));
		return false;
	}
	else
	{
		for (int i = pt.getSerialNum(); i < n - 1; i++)//n��ԭ�е���������
		{
			snprintf(sql, SQL_MAX, "UPDATE gcpinfo20240815 SET m_SerialNum = %d WHERE m_SerialNum = %d;", i, i);
			if (ret)
			{
				AfxMessageBox(_T("�Ա����������±�д���ʧ�ܣ�ʧ��ԭ��%s\n", mysql_error(&mysqlConnection)));
				return false;
			}
		}
	}
	return true;
}

bool MySQLInterface::UpdateInfoToMySQL(int nIndex, Point pt)
{
	// C��������ַ���
	snprintf(sql, SQL_MAX, "UPDATE gcpinfo20240815 SET m_SerialNum = %d, m_Name = %s, m_X = %lf, m_Y = %lf, m_Z = %lf WHERE m_SerialNum = %d;", nIndex + 1, pt.getName().c_str(), pt.getX(), pt.getY(), pt.getZ(), nIndex + 1);
	// ִ��SQL��䣬��ѯ���ݣ�����ɹ�����0
	int ret = mysql_real_query(&mysqlConnection, sql, (unsigned long)strlen(sql));
	// �жϲ�ѯ�Ƿ�ɹ�
	if (ret)
	{
		AfxMessageBox(_T("�����޸�ʧ�ܣ�ʧ��ԭ��%s\n", mysql_error(&mysqlConnection)));
		return false;
	}
	return true;
}

PointArr MySQLInterface::FindPointInMySQL(Point pt, int& nFind)
{
	PointArr resultPoints;
	resultPoints.m_PointArr = new Point[1024];
	nFind = 0;

	//// C��������ַ���
	//snprintf(sql, SQL_MAX, "SELECT * FROM gcpinfo20240815 WHERE m_Name = '%s';");
	//// ��ѯ����
	////int ret = mysql_query(&mysql, "select * from student;");		// ��Ч������һ�д���
	////int ret = mysql_query(&mysql, sql);
	//int ret = mysql_real_query(&mysqlConnection, sql, (unsigned long)strlen(sql));
	//printf("ִ�в�ѯ��䣬��ѯ���ؽ����%d\n", ret);
	//if (ret) {
	//	printf("���ݲ�ѯʧ�ܣ�ʧ��ԭ��%s\n", mysql_error(&mysqlConnection));
	//}
	//printf("���ݲ�ѯ�ɹ���\n");
	//// ��ȡ�����
	//res = mysql_store_result(&mysqlConnection);
	//// ��ȡ��ѯ����һ������
	//// ��row��ֵ���ж�row�Ƿ�Ϊ�գ���Ϊ�վʹ�ӡ���ݡ�
	//while (row = mysql_fetch_row(res)) {
	//	printf("%d  ", atoi(row[0]));	// ת��Ϊint���ͣ���ӡid
	//	printf("%s  ", row[1]);			// ��ӡ����
	//	printf("%d  ", atoi(row[2]));	// ת��Ϊint���ͣ���ӡ����
	//	printf("%s  \n", row[3]);		// ��ӡ�Ա�
	//}
	//// �ͷŽ����
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
		AfxMessageBox(_T("�����ݿ���û�в��ҵ����������ĵ㣡"));
		return resultPoints;
	}

	snprintf(sql, SQL_MAX, "%s", query.c_str());

	if (mysql_query(&mysqlConnection, sql)) {
		AfxMessageBox(_T("��ѯʧ�ܣ�ʧ��ԭ��%s", mysql_error(&mysqlConnection)));
		return resultPoints;
	}

	resultSet = mysql_store_result(&mysqlConnection);
	if (!resultSet) {
		AfxMessageBox(_T("�����Ϊ�գ�����ԭ��%s", mysql_error(&mysqlConnection)));
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
