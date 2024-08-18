// IsConfirmOverwriteDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication_20240607_cppTeamWork.h"
#include "afxdialogex.h"
#include "IsConfirmOverwriteDlg.h"


// IsConfirmOverwriteDlg 对话框

IMPLEMENT_DYNAMIC(IsConfirmOverwriteDlg, CDialogEx)

IsConfirmOverwriteDlg::IsConfirmOverwriteDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CONFIRM_OVERWRITE, pParent)
{

}

IsConfirmOverwriteDlg::~IsConfirmOverwriteDlg()
{
}

void IsConfirmOverwriteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(IsConfirmOverwriteDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &IsConfirmOverwriteDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &IsConfirmOverwriteDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// IsConfirmOverwriteDlg 消息处理程序


void IsConfirmOverwriteDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	isConfirmOverwrite = true;
	CDialogEx::OnOK();
}


void IsConfirmOverwriteDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	isConfirmOverwrite = false;
	CDialogEx::OnCancel();
}
