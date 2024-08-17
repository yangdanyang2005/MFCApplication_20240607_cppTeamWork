// FindPointInMySQLDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication_20240607_cppTeamWork.h"
#include "afxdialogex.h"
#include "FindPointInMySQLDlg.h"


// FindPointInMySQLDlg 对话框

IMPLEMENT_DYNAMIC(FindPointInMySQLDlg, CDialogEx)

FindPointInMySQLDlg::FindPointInMySQLDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG30, pParent)
	, findPointInMySQLname(_T(""))
	, findPointInMySQLx(0)
	, findPointInMySQLy(0)
	, findPointInMySQLz(0)
{

}

FindPointInMySQLDlg::~FindPointInMySQLDlg()
{
}

void FindPointInMySQLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, findPointInMySQLname);
	DDX_Text(pDX, IDC_EDIT2, findPointInMySQLx);
	DDX_Text(pDX, IDC_EDIT3, findPointInMySQLy);
	DDX_Text(pDX, IDC_EDIT4, findPointInMySQLz);
}


BEGIN_MESSAGE_MAP(FindPointInMySQLDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &FindPointInMySQLDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// FindPointInMySQLDlg 消息处理程序


void FindPointInMySQLDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if ((findPointInMySQLname.IsEmpty()) && (findPointInMySQLx == 0) && (findPointInMySQLy == 0) && (findPointInMySQLz == 0))
	{
		AfxMessageBox(_T("您的输入为空！请向编辑框中填写您想要添加的点名、x坐标、y坐标或z坐标！"));
		return;
	}
	CDialogEx::OnOK();
}
