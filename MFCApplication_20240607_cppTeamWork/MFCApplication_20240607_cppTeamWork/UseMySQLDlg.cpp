// UseMySQLDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication_20240607_cppTeamWork.h"
#include "MFCApplication_20240607_cppTeamWorkDoc.h"
#include "afxdialogex.h"
#include "UseMySQLDlg.h"
#include <sql.h>
#include "AddPointToMySQLDlg.h"
#include "MySQLInterface.h"
#include "UpdatePointToMySQLDlg.h"
#include "FindPointInMySQLDlg.h"
#include "PointArrAnalyzeDlg.h"

// UseMySQLDlg 对话框

IMPLEMENT_DYNAMIC(UseMySQLDlg, CDialogEx)

UseMySQLDlg::UseMySQLDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG27, pParent)
{

}

UseMySQLDlg::~UseMySQLDlg()
{
}

void UseMySQLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, CUseMySQLListCtrl);
	DDX_Control(pDX, IDC_COMBO2, m_CComboBoxSort);
	DDX_Control(pDX, IDC_COMBO3, m_CComboBoxSortOrder);
}


BEGIN_MESSAGE_MAP(UseMySQLDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &UseMySQLDlg::OnBnClickedButtonMySQLToArr)
	ON_BN_CLICKED(IDC_BUTTON2, &UseMySQLDlg::OnBnClickedButtonAddToMySQL)
	ON_BN_CLICKED(IDC_BUTTON9, &UseMySQLDlg::OnBnClickedButtonFileToMySQL)
	ON_BN_CLICKED(IDC_BUTTON3, &UseMySQLDlg::OnBnClickedButtonDelInMySQL)
	ON_BN_CLICKED(IDC_BUTTON4, &UseMySQLDlg::OnBnClickedButtonUpdateInMySQL)
	ON_BN_CLICKED(IDC_BUTTON5, &UseMySQLDlg::OnBnClickedButtonFindPointInMySQL)
	ON_BN_CLICKED(IDC_BUTTON12, &UseMySQLDlg::OnBnClickedButtonAnalyze)
	ON_BN_CLICKED(IDC_BUTTON13, &UseMySQLDlg::OnBnClickedButtonSort)
END_MESSAGE_MAP()


// UseMySQLDlg 消息处理程序

BOOL UseMySQLDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	UpdateData(TRUE);
	CFrameWnd* pMainFrame = (CFrameWnd*)AfxGetMainWnd();
	CFrameWnd* pActiveFrame = pMainFrame->GetActiveFrame();
	CDocument* pActiveDocument = pActiveFrame->GetActiveDocument();
	CMFCApplication20240607cppTeamWorkDoc* pDoc = dynamic_cast<CMFCApplication20240607cppTeamWorkDoc*>(pActiveDocument);//从文档读取变量数据到对话框中
	pDoc->arrSQL.m_PointArr = new Point[1024];//分配内存空间

	// 获取下拉框控件的对象
	CComboBox* pComboBox1 = (CComboBox*)GetDlgItem(IDC_COMBO2);
	CComboBox* pComboBox2 = (CComboBox*)GetDlgItem(IDC_COMBO3);
	// 确保下拉框控件对象有效
	if (pComboBox1 != nullptr)
	{
		// 设置下拉框的项
		pComboBox1->AddString(_T("请选择排序项"));
		pComboBox1->AddString(_T("点名"));
		pComboBox1->AddString(_T("x坐标"));
		pComboBox1->AddString(_T("y坐标"));
		pComboBox1->AddString(_T("z坐标"));
		pComboBox1->AddString(_T("x坐标、z坐标"));
		pComboBox1->AddString(_T("y坐标、z坐标"));
		pComboBox1->AddString(_T("x坐标、y坐标"));
		pComboBox1->AddString(_T("y坐标、x坐标"));
		pComboBox1->AddString(_T("z坐标、x坐标"));
		pComboBox1->AddString(_T("z坐标、y坐标"));
		pComboBox1->AddString(_T("x坐标、y坐标、z坐标"));
		pComboBox1->AddString(_T("x坐标、z坐标、y坐标"));
		pComboBox1->AddString(_T("y坐标、x坐标、z坐标"));
		pComboBox1->AddString(_T("y坐标、z坐标、x坐标"));
		pComboBox1->AddString(_T("z坐标、x坐标、y坐标"));
		pComboBox1->AddString(_T("z坐标、y坐标、x坐标"));
		pComboBox1->AddString(_T("点名、x坐标"));
		pComboBox1->AddString(_T("点名、y坐标"));
		pComboBox1->AddString(_T("点名、z坐标"));
		pComboBox1->AddString(_T("点名、x坐标、z坐标"));
		pComboBox1->AddString(_T("点名、y坐标、z坐标"));
		pComboBox1->AddString(_T("点名、x坐标、y坐标"));
		pComboBox1->AddString(_T("点名、y坐标、x坐标"));
		pComboBox1->AddString(_T("点名、z坐标、x坐标"));
		pComboBox1->AddString(_T("点名、z坐标、y坐标"));
		pComboBox1->AddString(_T("点名、x坐标、y坐标、z坐标"));
		pComboBox1->AddString(_T("点名、x坐标、z坐标、y坐标"));
		pComboBox1->AddString(_T("点名、y坐标、x坐标、z坐标"));
		pComboBox1->AddString(_T("点名、x坐标、z坐标、y坐标"));
		pComboBox1->AddString(_T("点名、z坐标、x坐标、y坐标"));
		pComboBox1->AddString(_T("点名、z坐标、y坐标、x坐标"));

		// 设置默认选中的项
		pComboBox1->SetCurSel(0);  // 索引从0开始，1表示第二项
	}

	if (pComboBox2 != nullptr)
	{
		// 设置下拉框的项
		//pComboBox2->AddString(_T("请选择排序顺序"));
		//pComboBox2->AddString(_T("升序"));
		//pComboBox2->AddString(_T("降序"));

		// 设置默认选中的项
		pComboBox2->SetCurSel(0);  // 索引从0开始，1表示第二项
	}


	//在连接MySQL数据库之前，禁用其余所有控件
	GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON9)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON12)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON13)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO2)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO3)->EnableWindow(FALSE);
	GetDlgItem(IDC_LIST1)->EnableWindow(FALSE);

	//初始化表格控件的第一行
	/*大一下 《遥感信息处理C++基础》 P209
	列表内添加五列表头，每列宽度为列表控件的1/5*/
	CRect rc; CUseMySQLListCtrl.GetClientRect(&rc);
	CUseMySQLListCtrl.InsertColumn(0, _T("点的序号"), LVCFMT_CENTER);
	/*LVCFMT_LEFT 文本左对齐。LVCFMT_RIGHT 文本右对齐。LVCFMT_CENTER 文本居中。
	https://learn.microsoft.com/zh-cn/windows/win32/api/commctrl/ns-commctrl-lvcolumna */
	CUseMySQLListCtrl.InsertColumn(1, _T("点的名称"), LVCFMT_CENTER);
	CUseMySQLListCtrl.InsertColumn(2, _T("x坐标"), LVCFMT_CENTER);
	CUseMySQLListCtrl.InsertColumn(3, _T("y坐标"), LVCFMT_CENTER);
	CUseMySQLListCtrl.InsertColumn(4, _T("z坐标"), LVCFMT_CENTER);
	CUseMySQLListCtrl.SetColumnWidth(0, rc.Width() / 5);
	CUseMySQLListCtrl.SetColumnWidth(1, rc.Width() / 5);
	CUseMySQLListCtrl.SetColumnWidth(2, rc.Width() / 5);
	CUseMySQLListCtrl.SetColumnWidth(3, rc.Width() / 5);
	CUseMySQLListCtrl.SetColumnWidth(4, rc.Width() / 5);
	ListView_SetExtendedListViewStyle(CUseMySQLListCtrl.m_hWnd, LVS_EX_GRIDLINES);

	//https://blog.csdn.net/qq_40969467/article/details/103293191
	//设置行高
	CImageList m_l;
	m_l.Create(1, 25, TRUE | ILC_COLOR32, 1, 0);   //设置表格的高度 
	CUseMySQLListCtrl.SetImageList(&m_l, LVSIL_SMALL);
	//设置字体
	CFont m_font;
	m_font.CreatePointFont(140, "楷体"); //设置标题栏的高度及字体
	CUseMySQLListCtrl.SetFont(&m_font);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

//连接MySQL数据库，并从数据库中读取数据到内存中的数组arrSQL中，显示在列表视图中
void UseMySQLDlg::OnBnClickedButtonMySQLToArr()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CFrameWnd* pMainFrame = (CFrameWnd*)AfxGetMainWnd();
	CFrameWnd* pActiveFrame = pMainFrame->GetActiveFrame();
	CDocument* pActiveDocument = pActiveFrame->GetActiveDocument();
	CMFCApplication20240607cppTeamWorkDoc* pDoc = dynamic_cast<CMFCApplication20240607cppTeamWorkDoc*>(pActiveDocument);//从文档读取变量数据到对话框中
	//连接MySQL数据库
	if (SQL.ConnectMySQL()) {

		//先清空列表视图
		CUseMySQLListCtrl.DeleteAllItems();

		//从MySQL数据库中读取数据到内存中的数组arrSQL中
		SQL.GetAllInfo();

		//再向列表视图中显示数据库中的数据
		CString str;
		int n = pDoc->arrSQL.m_Num;
		int item = CUseMySQLListCtrl.GetItemCount();
		/*item是插入的行号。
		GetItemCount()：这是CListCtrl类的另一个成员函数，用于获取当前列表视图中的项目数量。返回值是一个整数，表示列表中的项目总数。
		上面这一行操作往往用于向列表视图中续接式地添加新的项目。*/
		for (int i = 0; i < n; i++)
		{
			CUseMySQLListCtrl.InsertItem(item + i, str);

			str.Format(_T("%d"), pDoc->arrSQL.m_PointArr[i].getSerialNum());
			CUseMySQLListCtrl.SetItemText(item + i, 0, str);

			str = pDoc->arrSQL.m_PointArr[i].getName().c_str();
			CUseMySQLListCtrl.SetItemText(item + i, 1, str);

			str.Format(_T("%1f"), pDoc->arrSQL.m_PointArr[i].getX());
			CUseMySQLListCtrl.SetItemText(item + i, 2, str);

			str.Format(_T("%1f"), pDoc->arrSQL.m_PointArr[i].getY());
			CUseMySQLListCtrl.SetItemText(item + i, 3, str);

			str.Format(_T("%1f"), pDoc->arrSQL.m_PointArr[i].getZ());
			CUseMySQLListCtrl.SetItemText(item + i, 4, str);
		}
		UpdateData(FALSE);
		isConnectMySQL = true;
		MessageBox(TEXT("数据库MySQL连接成功！"), TEXT("连接数据库成功提示"));

		//启用其余所有控件
		GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON9)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON12)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON13)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO2)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO3)->EnableWindow(TRUE);
		GetDlgItem(IDC_LIST1)->EnableWindow(TRUE);
	}
	else {
		return;
	}
}

//从文件中读取数据，并覆写MySQL数据库中的数据：先清空MySQL数据库中原有的数据，然后逐条添加文件中的数据到MySQL数据库中
void UseMySQLDlg::OnBnClickedButtonFileToMySQL()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CFrameWnd* pMainFrame = (CFrameWnd*)AfxGetMainWnd();
	CFrameWnd* pActiveFrame = pMainFrame->GetActiveFrame();
	CDocument* pActiveDocument = pActiveFrame->GetActiveDocument();
	CMFCApplication20240607cppTeamWorkDoc* pDoc = dynamic_cast<CMFCApplication20240607cppTeamWorkDoc*>(pActiveDocument);//从文档读取变量数据到对话框中

	snprintf(SQL.sql, SQL_MAX, "truncate table gcpinfo20240815;");//清空MySQL数据库中原有的数据
	// 执行SQL语句，查询数据，如果成功返回0
	int ret = mysql_real_query(&SQL.mysqlConnection, SQL.sql, (unsigned long)strlen(SQL.sql));
	if (ret) {
		AfxMessageBox(_T("清空MySQL数据库中原有的数据失败！失败原因： %s\n", mysql_error(&mysqlConnection)));
		return;
	}

	Point pt;

	for (int i = 0; i < pDoc->arr.m_Num; i++)
	{
		pt.setSerialNum(i + 1);
		pt.setName(pDoc->arr.m_PointArr[i].getName());
		pt.setX(pDoc->arr.m_PointArr[i].getX());
		pt.setY(pDoc->arr.m_PointArr[i].getY());
		pt.setZ(pDoc->arr.m_PointArr[i].getZ());
		if (!SQL.AddInfoToMySQL(pt))
		{
			AfxMessageBox(_T("添加数据到MySQL数据库失败！失败原因： %s\n", mysql_error(&mysqlConnection)));
			return;
		}
	}
	MessageBox(TEXT("文件数据添加到MySQL数据库成功！"), TEXT("添加数据到MySQL成功提示"));
	UpdateCControlList();
}

//更新列表控件中显示的数据
void UseMySQLDlg::UpdateCControlList()
{
	CFrameWnd* pMainFrame = (CFrameWnd*)AfxGetMainWnd();
	CFrameWnd* pActiveFrame = pMainFrame->GetActiveFrame();
	CDocument* pActiveDocument = pActiveFrame->GetActiveDocument();
	CMFCApplication20240607cppTeamWorkDoc* pDoc = dynamic_cast<CMFCApplication20240607cppTeamWorkDoc*>(pActiveDocument);//从文档读取变量数据到对话框中

	//先清空列表视图
	CUseMySQLListCtrl.DeleteAllItems();

	//从MySQL数据库中读取数据到内存中的数组arrSQL中
	SQL.GetAllInfo();

	//再向列表视图中显示数据库中的数据
	CString str;
	int n = pDoc->arrSQL.m_Num;
	/*n是一共要被插入的行数。
	P.S. GetItemCount()：这是CListCtrl类的另一个成员函数，用于获取当前列表视图中的项目数量。返回值是一个整数，表示列表中的项目总数。
	上面这一行操作往往用于向列表视图中续接式地添加新的项目。*/
	for (int i = 0; i < n; i++)
	{
		CUseMySQLListCtrl.InsertItem(i, str);

		str.Format(_T("%d"), pDoc->arrSQL.m_PointArr[i].getSerialNum());
		CUseMySQLListCtrl.SetItemText(i, 0, str);

		str = pDoc->arrSQL.m_PointArr[i].getName().c_str();
		CUseMySQLListCtrl.SetItemText(i, 1, str);

		str.Format(_T("%1f"), pDoc->arrSQL.m_PointArr[i].getX());
		CUseMySQLListCtrl.SetItemText(i, 2, str);

		str.Format(_T("%1f"), pDoc->arrSQL.m_PointArr[i].getY());
		CUseMySQLListCtrl.SetItemText(i, 3, str);

		str.Format(_T("%1f"), pDoc->arrSQL.m_PointArr[i].getZ());
		CUseMySQLListCtrl.SetItemText(i, 4, str);
	}
	UpdateData(FALSE);
}


void UseMySQLDlg::OnBnClickedButtonAddToMySQL()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CFrameWnd* pMainFrame = (CFrameWnd*)AfxGetMainWnd();
	CFrameWnd* pActiveFrame = pMainFrame->GetActiveFrame();
	CDocument* pActiveDocument = pActiveFrame->GetActiveDocument();
	CMFCApplication20240607cppTeamWorkDoc* pDoc = dynamic_cast<CMFCApplication20240607cppTeamWorkDoc*>(pActiveDocument);//从文档读取变量数据到对话框中

	AddPointToMySQLDlg dlg;
	Point pt;
	if (dlg.DoModal() == IDOK)
	{
		//将用户输入的需要添加的数据暂存在点pt当中
		string name = CT2A(dlg.OnAddToMySQLname.GetBuffer());
		pt.setSerialNum(pDoc->arrSQL.m_Num + 1);
		pt.setName(name);
		pt.setX(dlg.OnAddToMySQLX);
		pt.setY(dlg.OnAddToMySQLY);
		pt.setZ(dlg.OnAddToMySQLZ);
		//连接MySQL数据库
		if (SQL.AddInfoToMySQL(pt))
		{
			MessageBox(TEXT("添加点到MySQL数据库成功！"), TEXT("添加数据到MySQL成功提示"));
			UpdateCControlList();
		}
		else {
			return;
		}
	}
}


void UseMySQLDlg::OnBnClickedButtonDelInMySQL()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CFrameWnd* pMainFrame = (CFrameWnd*)AfxGetMainWnd();
	CFrameWnd* pActiveFrame = pMainFrame->GetActiveFrame();
	CDocument* pActiveDocument = pActiveFrame->GetActiveDocument();
	CMFCApplication20240607cppTeamWorkDoc* pDoc = dynamic_cast<CMFCApplication20240607cppTeamWorkDoc*>(pActiveDocument);//从文档读取变量数据到对话框中

	int nIndex = CUseMySQLListCtrl.GetSelectionMark();//获取当前选中行号
	if (nIndex == -1)
	{
		AfxMessageBox(TEXT("请先选择要删除的数据行！"));
		return;
	}
	else
	{
		UINT i;
		i = MessageBox(TEXT("确定要删除该行数据吗？"), TEXT("删除数据提示"), MB_YESNO | MB_ICONQUESTION);
		if (i == IDYES)
		{
			if (SQL.DelInfoToMySQL(pDoc->arrSQL.m_PointArr[nIndex], pDoc->arrSQL.m_Num))
			{
				MessageBox(TEXT("删除数据成功！"), TEXT("删除数据提示"));
				pDoc->arrSQL.m_Num--;//更新arrSQL数组长度
				UpdateCControlList();
			}
			else
			{
				return;
			}
		}
	}
}


void UseMySQLDlg::OnBnClickedButtonUpdateInMySQL()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CFrameWnd* pMainFrame = (CFrameWnd*)AfxGetMainWnd();
	CFrameWnd* pActiveFrame = pMainFrame->GetActiveFrame();
	CDocument* pActiveDocument = pActiveFrame->GetActiveDocument();
	CMFCApplication20240607cppTeamWorkDoc* pDoc = dynamic_cast<CMFCApplication20240607cppTeamWorkDoc*>(pActiveDocument);//从文档读取变量数据到对话框中

	int nIndex = CUseMySQLListCtrl.GetSelectionMark();//获取当前选中行号
	if (nIndex == -1)
	{
		AfxMessageBox(TEXT("请先选择要删除的数据行！"));
		return;
	}

	UpdatePointToMySQLDlg dlg;
	dlg.OnUpdateToMySQLname = pDoc->arrSQL.m_PointArr[nIndex].getName().c_str();
	dlg.OnUpdateToMySQLX = pDoc->arrSQL.m_PointArr[nIndex].getX();
	dlg.OnUpdateToMySQLY = pDoc->arrSQL.m_PointArr[nIndex].getY();
	dlg.OnUpdateToMySQLZ = pDoc->arrSQL.m_PointArr[nIndex].getZ();

	Point pt;
	if (dlg.DoModal() == IDOK)
	{
		//将用户输入的需要的修改后的数据暂存在点pt当中
		string name = CT2A(dlg.OnUpdateToMySQLname.GetBuffer());
		pt.setName(name);
		pt.setX(dlg.OnUpdateToMySQLX);
		pt.setY(dlg.OnUpdateToMySQLY);
		pt.setZ(dlg.OnUpdateToMySQLZ);
		//连接MySQL数据库
		if (SQL.UpdateInfoToMySQL(nIndex, pt))
		{
			MessageBox(TEXT("修改MySQL数据库中点的数据成功！"), TEXT("修改MySQL数据库中点的数据成功提示"));
			UpdateCControlList();
		}
		else {
			return;
		}
	}
}


void UseMySQLDlg::OnBnClickedButtonFindPointInMySQL()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CFrameWnd* pMainFrame = (CFrameWnd*)AfxGetMainWnd();
	CFrameWnd* pActiveFrame = pMainFrame->GetActiveFrame();
	CDocument* pActiveDocument = pActiveFrame->GetActiveDocument();
	CMFCApplication20240607cppTeamWorkDoc* pDoc = dynamic_cast<CMFCApplication20240607cppTeamWorkDoc*>(pActiveDocument);//从文档读取变量数据到对话框中
	pDoc->arrFindInMySQL.m_PointArr = new Point [1024];//创建存储查询结果的数组，并分配内存空间

	FindPointInMySQLDlg dlg;
	int nFind = 0;
	Point pt;

	if (dlg.DoModal() == IDOK)
	{
		//将用户输入的需要查找的数据暂存在点pt当中
		string name = CT2A(dlg.findPointInMySQLname.GetBuffer());
		pt.setName(name);
		pt.setX(dlg.findPointInMySQLx);
		pt.setY(dlg.findPointInMySQLy);
		pt.setZ(dlg.findPointInMySQLz);
		
		pDoc->arrFindInMySQL = SQL.FindPointInMySQL(pt, nFind);
	}

	//更新显示在列表视图中的查询结果——
	//先清空列表视图
	CUseMySQLListCtrl.DeleteAllItems();
	//再向列表视图中显示从数据库中查询到的数据
	CString str;
	pDoc->arrFindInMySQL.m_Num = nFind;
	/*n是一共要被插入的行数。
	P.S. GetItemCount()：这是CListCtrl类的另一个成员函数，用于获取当前列表视图中的项目数量。返回值是一个整数，表示列表中的项目总数。
	上面这一行操作往往用于向列表视图中续接式地添加新的项目。*/
	for (int i = 0; i < nFind; i++)
	{
		CUseMySQLListCtrl.InsertItem(i, str);

		str.Format(_T("%d"), pDoc->arrFindInMySQL.m_PointArr[i].getSerialNum());
		CUseMySQLListCtrl.SetItemText(i, 0, str);

		str = pDoc->arrFindInMySQL.m_PointArr[i].getName().c_str();
		CUseMySQLListCtrl.SetItemText(i, 1, str);

		str.Format(_T("%1f"), pDoc->arrFindInMySQL.m_PointArr[i].getX());
		CUseMySQLListCtrl.SetItemText(i, 2, str);

		str.Format(_T("%1f"), pDoc->arrFindInMySQL.m_PointArr[i].getY());
		CUseMySQLListCtrl.SetItemText(i, 3, str);

		str.Format(_T("%1f"), pDoc->arrFindInMySQL.m_PointArr[i].getZ());
		CUseMySQLListCtrl.SetItemText(i, 4, str);
	}
	UpdateData(FALSE);
}


void UseMySQLDlg::OnBnClickedButtonAnalyze()
{
	// TODO: 在此添加控件通知处理程序代码
	PointArrAnalyzeDataFlag = 1;
	PointArrAnalyzeDlg dlg;
	dlg.DoModal();
}


void UseMySQLDlg::OnBnClickedButtonSort()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CFrameWnd* pMainFrame = (CFrameWnd*)AfxGetMainWnd();
	CFrameWnd* pActiveFrame = pMainFrame->GetActiveFrame();
	CDocument* pActiveDocument = pActiveFrame->GetActiveDocument();
	CMFCApplication20240607cppTeamWorkDoc* pDoc = dynamic_cast<CMFCApplication20240607cppTeamWorkDoc*>(pActiveDocument);//从文档读取变量数据到对话框中

	int selectedIndex = m_CComboBoxSort.GetCurSel();
	int sortOrderIndex = m_CComboBoxSortOrder.GetCurSel(); // 新增控件，用于选择排序顺序

	std::vector<int> priorityArray;

	// 根据下拉框的选择设置排序优先级
	switch (selectedIndex) {
	case 0: // “请选择排序项”
	{
		AfxMessageBox(TEXT("请选择排序项！"));
		CUseMySQLListCtrl.DeleteAllItems();//清空列表视图
		break;
	}
	case 1: // 例：按名称排序
	{
		priorityArray.push_back(1);
		break;
	}
	case 2: // 例：按 X	排序
	{
		priorityArray.push_back(2);
		break;
	}
	case 3: // 例：按 Y 排序
	{
		priorityArray.push_back(3);
		break;
	}
	case 4: // 例：按 Z 排序
	{
		priorityArray.push_back(4);
		break;
	}
	case 5: // 例：按 X 然后按 Y 排序
	{
		priorityArray.push_back(2);
		priorityArray.push_back(3);
		break;
	}
	case 6: // 例：按 Y 然后按 Z 排序
	{
		priorityArray.push_back(3);
		priorityArray.push_back(4);
		break;
	}
	case 7: // 例：按 X 然后按 Z 排序
	{
		priorityArray.push_back(2);
		priorityArray.push_back(4);
		break;
	}
	case 8: // 例：按 Y 然后按 X 排序
	{
		priorityArray.push_back(3);
		priorityArray.push_back(2);
		break;
	}
	case 9: // 例：按 Z 然后按 X 排序
	{
		priorityArray.push_back(4);
		priorityArray.push_back(2);
		break;
	}
	case 10: // 例：按 Z 然后按 Y 排序
	{
		priorityArray.push_back(4);
		priorityArray.push_back(3);
		break;
	}
	case 11: // 例：按 X 然后按 Y 然后按 Z 排序
	{
		priorityArray.push_back(2);
		priorityArray.push_back(3);
		priorityArray.push_back(4);
		break;
	}
	case 12: // 例：按 X 然后按 Z 然后按 Y 排序
	{
		priorityArray.push_back(2);
		priorityArray.push_back(4);
		priorityArray.push_back(3);
		break;
	}
	case 13: // 例：按 Y 然后按 X 然后按 Z 排序
	{
		priorityArray.push_back(3);
		priorityArray.push_back(2);
		priorityArray.push_back(4);
		break;
	}
	case 14: // 例：按 Y 然后按 Z 然后按 X 排序
	{
		priorityArray.push_back(3);
		priorityArray.push_back(4);
		priorityArray.push_back(2);
	}
	case 15: // 例：按 Z 然后按 X 然后按 Y 排序
	{
		priorityArray.push_back(4);
		priorityArray.push_back(2);
		priorityArray.push_back(3);
		break;
	}
	case 16: // 例：按 Z 然后按 Y 然后按 X 排序
	{
		priorityArray.push_back(4);
		priorityArray.push_back(3);
		priorityArray.push_back(2);
		break;
	}
	case 17: // 例：按名称排序，然后按 X 排序
	{
		priorityArray.push_back(1);
		priorityArray.push_back(2);
		break;
	}
	case 18: // 例：按名称排序，然后按 Y 排序
	{
		priorityArray.push_back(1);
		priorityArray.push_back(3);
		break;
	}
	case 19: // 例：按名称排序，然后按 Z 排序
	{
		priorityArray.push_back(1);
		priorityArray.push_back(4);
		break;
	}
	case 20: // 例：按名称排序，然后按 X 然后按 Y 排序
	{
		priorityArray.push_back(1);
		priorityArray.push_back(2);
		priorityArray.push_back(3);
		break;
	}
	case 21: // 例：按名称排序，然后按 Y 然后按 Z 排序
	{
		priorityArray.push_back(1);
		priorityArray.push_back(3);
		priorityArray.push_back(4);
		break;
	}
	case 22: // 例：按名称排序，然后按 X 然后按 Z 排序
	{
		priorityArray.push_back(1);
		priorityArray.push_back(2);
		priorityArray.push_back(4);
		break;
	}
	case 23: // 例：按名称排序，然后按 Z 然后按 X 排序
	{
		priorityArray.push_back(1);
		priorityArray.push_back(4);
		priorityArray.push_back(2);
		break;
	}
	case 24: // 例：按名称排序，然后按 Z 然后按 Y 排序
	{
		priorityArray.push_back(1);
		priorityArray.push_back(4);
		priorityArray.push_back(3);
		break;
	}
	case 25: // 例：按名称排序，然后按 X 然后按 Y 然后按 Z 排序
	{
		priorityArray.push_back(1);
		priorityArray.push_back(2);
		priorityArray.push_back(3);
		priorityArray.push_back(4);
		break;
	}
	case 26: // 例：按名称排序，然后按 Y 然后按 Z 然后按 X 排序
	{
		priorityArray.push_back(1);
		priorityArray.push_back(3);
		priorityArray.push_back(4);
		priorityArray.push_back(2);
		break;
	}
	case 27: // 例：按名称排序，然后按 Y 然后按 X 然后按 Z 排序
	{
		priorityArray.push_back(1);
		priorityArray.push_back(3);
		priorityArray.push_back(2);
		priorityArray.push_back(4);
		break;
	}
	case 28: // 例：按名称排序，然后按 Z 然后按 Y 然后按 X 排序
	{
		priorityArray.push_back(1);
		priorityArray.push_back(4);
		priorityArray.push_back(3);
		priorityArray.push_back(2);
		break;
	}
	case 29: // 例：按名称排序，然后按 Z 然后按 X 然后按 Y 排序
	{
		priorityArray.push_back(1);
		priorityArray.push_back(4);
		priorityArray.push_back(2);
		priorityArray.push_back(3);
		break;
	}
	case 30: // 例：按名称排序，然后按 Z 然后按 Y 然后按 X 排序
	{
		priorityArray.push_back(1);
		priorityArray.push_back(4);
		priorityArray.push_back(3);
		priorityArray.push_back(2);
		break;
	}
	}

	// 设置排序方向
	SortOrder order = (sortOrderIndex == 1) ? SortOrder::Ascending : SortOrder::Descending;
	pDoc->arrSQL.setSortOrder(order);

	// 使用相应的排序函数
	if (priorityArray.size() > 0) {
		pDoc->arrSQL.sortByMultipleCriteria(priorityArray);
	}

	//将排序后的结果覆写到数据库中
	snprintf(SQL.sql, SQL_MAX, "truncate table gcpinfo20240815;");//清空MySQL数据库中原有的数据
	// 执行SQL语句，查询数据，如果成功返回0
	int ret = mysql_real_query(&SQL.mysqlConnection, SQL.sql, (unsigned long)strlen(SQL.sql));
	if (ret) {
		AfxMessageBox(_T("清空MySQL数据库中原有的数据失败！失败原因： %s\n", mysql_error(&mysqlConnection)));
		return;
	}
	Point pt;
	for (int i = 0; i < pDoc->arrSQL.m_Num; i++)
	{
		pt.setSerialNum(i + 1);
		pt.setName(pDoc->arrSQL.m_PointArr[i].getName());
		pt.setX(pDoc->arrSQL.m_PointArr[i].getX());
		pt.setY(pDoc->arrSQL.m_PointArr[i].getY());
		pt.setZ(pDoc->arrSQL.m_PointArr[i].getZ());
		if (!SQL.AddInfoToMySQL(pt))
		{
			AfxMessageBox(_T("添加数据到MySQL数据库失败！失败原因： %s\n", mysql_error(&mysqlConnection)));
			return;
		}
	}
	//MessageBox(TEXT("排序后数据更新到MySQL数据库成功！"), TEXT("排序后数据更新到MySQL成功提示"));

	// 更新 UI 显示
	UpdateCControlList();
}
