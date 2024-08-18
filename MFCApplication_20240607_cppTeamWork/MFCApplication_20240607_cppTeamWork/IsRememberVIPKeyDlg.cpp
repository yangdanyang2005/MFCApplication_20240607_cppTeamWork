// IsRememberVIPKeyDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication_20240607_cppTeamWork.h"
#include "afxdialogex.h"
#include "IsRememberVIPKeyDlg.h"


// IsRememberVIPKeyDlg 对话框

IMPLEMENT_DYNAMIC(IsRememberVIPKeyDlg, CDialogEx)

IsRememberVIPKeyDlg::IsRememberVIPKeyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG26, pParent)
{

}

IsRememberVIPKeyDlg::~IsRememberVIPKeyDlg()
{
}

void IsRememberVIPKeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(IsRememberVIPKeyDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &IsRememberVIPKeyDlg::OnBnClickedOkToRememberVIPKey)
	ON_BN_CLICKED(IDCANCEL, &IsRememberVIPKeyDlg::OnBnClickedCancelToRememberVIPKey)
END_MESSAGE_MAP()


// IsRememberVIPKeyDlg 消息处理程序


void IsRememberVIPKeyDlg::OnBnClickedOkToRememberVIPKey()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	isRememberVIPKey = true;
	MessageBox(TEXT("您已经成功记住VIP密钥！下次登录时无需重新输入VIP密钥即可登录！"), TEXT("成功记住密钥提示"), MB_OK);
}


void IsRememberVIPKeyDlg::OnBnClickedCancelToRememberVIPKey()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
	isRememberVIPKey = false;
	MessageBox(TEXT("您已经取消记住VIP密钥！"), TEXT("取消记住密钥提示"), MB_OK);
}
