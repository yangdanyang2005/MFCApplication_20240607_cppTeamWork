// AddPointToMySQLDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication_20240607_cppTeamWork.h"
#include "afxdialogex.h"
#include "AddPointToMySQLDlg.h"
#include "MySQLInterface.h"


// AddPointToMySQLDlg 对话框

IMPLEMENT_DYNAMIC(AddPointToMySQLDlg, CDialogEx)

AddPointToMySQLDlg::AddPointToMySQLDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG28, pParent)
	, OnAddToMySQLname(_T(""))
	, OnAddToMySQLX(0)
	, OnAddToMySQLY(0)
	, OnAddToMySQLZ(0)
{

}

AddPointToMySQLDlg::~AddPointToMySQLDlg()
{
}

void AddPointToMySQLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, OnAddToMySQLname);
	DDX_Text(pDX, IDC_EDIT2, OnAddToMySQLX);
	DDX_Text(pDX, IDC_EDIT3, OnAddToMySQLY);
	DDX_Text(pDX, IDC_EDIT4, OnAddToMySQLZ);
}


BEGIN_MESSAGE_MAP(AddPointToMySQLDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &AddPointToMySQLDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// AddPointToMySQLDlg 消息处理程序


void AddPointToMySQLDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(OnAddToMySQLname.IsEmpty() || OnAddToMySQLX == 0 || OnAddToMySQLY == 0 || OnAddToMySQLZ == 0)
	{
		AfxMessageBox(_T("请向编辑框中填写您想要添加的点的名称、x、y、z坐标！"));
		return;
	}
	CDialogEx::OnOK();
}
