// UpdatePointToMySQLDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication_20240607_cppTeamWork.h"
#include "afxdialogex.h"
#include "UpdatePointToMySQLDlg.h"


// UpdatePointToMySQLDlg 对话框

IMPLEMENT_DYNAMIC(UpdatePointToMySQLDlg, CDialogEx)

UpdatePointToMySQLDlg::UpdatePointToMySQLDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG29, pParent)
	, OnUpdateToMySQLname(_T(""))
	, OnUpdateToMySQLX(0)
	, OnUpdateToMySQLY(0)
	, OnUpdateToMySQLZ(0)
{

}

UpdatePointToMySQLDlg::~UpdatePointToMySQLDlg()
{
}

void UpdatePointToMySQLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, OnUpdateToMySQLname);
	DDX_Text(pDX, IDC_EDIT2, OnUpdateToMySQLX);
	DDX_Text(pDX, IDC_EDIT3, OnUpdateToMySQLY);
	DDX_Text(pDX, IDC_EDIT4, OnUpdateToMySQLZ);
}


BEGIN_MESSAGE_MAP(UpdatePointToMySQLDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &UpdatePointToMySQLDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// UpdatePointToMySQLDlg 消息处理程序


void UpdatePointToMySQLDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (OnUpdateToMySQLname.IsEmpty() || OnUpdateToMySQLX == 0 || OnUpdateToMySQLY == 0 || OnUpdateToMySQLZ == 0)
	{
		AfxMessageBox(_T("请向编辑框中填写您想要的修改后的点的名称、x、y、z坐标！"));
		return;
	}
	CDialogEx::OnOK();
}
