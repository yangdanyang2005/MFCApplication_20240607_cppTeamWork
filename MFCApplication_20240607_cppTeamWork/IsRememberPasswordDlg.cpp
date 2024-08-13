// IsRememberPasswardDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication_20240607_cppTeamWork.h"
#include "afxdialogex.h"
#include "IsRememberPasswordDlg.h"


// IsRememberPasswordDlg 对话框

IMPLEMENT_DYNAMIC(IsRememberPasswordDlg, CDialogEx)

IsRememberPasswordDlg::IsRememberPasswordDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG25, pParent)
{

}

IsRememberPasswordDlg::~IsRememberPasswordDlg()
{
}

void IsRememberPasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(IsRememberPasswordDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &IsRememberPasswordDlg::OnBnClickedOkToRememberPassword)
	ON_BN_CLICKED(IDCANCEL, &IsRememberPasswordDlg::OnBnClickedCancelToRememberPassword)
END_MESSAGE_MAP()


// IsRememberPasswordDlg 消息处理程序


void IsRememberPasswordDlg::OnBnClickedOkToRememberPassword()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	isRememberPassword = true;
	MessageBox(TEXT("您已经成功记住密码！下次登录时无需再次输出用户名与密码即可登录！"), TEXT("成功记住密码提示"), MB_OK);
}


void IsRememberPasswordDlg::OnBnClickedCancelToRememberPassword()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
	isRememberPassword = false;
	MessageBox(TEXT("您已经取消记住密码！"), TEXT("取消记住密码提示"), MB_OK);
}
