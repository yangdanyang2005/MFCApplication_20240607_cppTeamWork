// IsOverwriteFromMySQLToCsvDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication_20240607_cppTeamWork.h"
#include "afxdialogex.h"
#include "IsOverwriteFromMySQLToCsvDlg.h"


// IsOverwriteFromMySQLToCsvDlg 对话框

IMPLEMENT_DYNAMIC(IsOverwriteFromMySQLToCsvDlg, CDialogEx)

IsOverwriteFromMySQLToCsvDlg::IsOverwriteFromMySQLToCsvDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ISOVERWRITEDLG, pParent)
{

}

IsOverwriteFromMySQLToCsvDlg::~IsOverwriteFromMySQLToCsvDlg()
{
}

void IsOverwriteFromMySQLToCsvDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(IsOverwriteFromMySQLToCsvDlg, CDialogEx)
	ON_BN_CLICKED(IDOK2, &IsOverwriteFromMySQLToCsvDlg::OnBnClickedOk2)
	ON_BN_CLICKED(IDOK, &IsOverwriteFromMySQLToCsvDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &IsOverwriteFromMySQLToCsvDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// IsOverwriteFromMySQLToCsvDlg 消息处理程序


void IsOverwriteFromMySQLToCsvDlg::OnBnClickedOk2()
{
	// TODO: 在此添加控件通知处理程序代码
	isOverwriteFileFlag = 1;
}


void IsOverwriteFromMySQLToCsvDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	isOverwriteFileFlag = 2;
	CDialogEx::OnOK();
}


void IsOverwriteFromMySQLToCsvDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	isOverwriteFileFlag = 0;

	CDialogEx::OnCancel();
}
