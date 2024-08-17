// UserSetRGBDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication_20240607_cppTeamWork.h"
#include "afxdialogex.h"
#include "UserSetRGBDlg.h"


// UserSetRGBDlg 对话框

IMPLEMENT_DYNAMIC(UserSetRGBDlg, CDialogEx)

UserSetRGBDlg::UserSetRGBDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG19, pParent)
	, setHighR(255)
	, setHighG(0)
	, setHighB(0)
	, setLowR(0)
	, setLowG(255)
	, setLowB(0)
{

}

UserSetRGBDlg::~UserSetRGBDlg()
{
}

void UserSetRGBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, setHighR);
	DDX_Text(pDX, IDC_EDIT2, setHighG);
	DDX_Text(pDX, IDC_EDIT3, setHighB);
	DDX_Text(pDX, IDC_EDIT4, setLowR);
	DDX_Text(pDX, IDC_EDIT5, setLowG);
	DDX_Text(pDX, IDC_EDIT6, setLowB);
}


BEGIN_MESSAGE_MAP(UserSetRGBDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT3, &UserSetRGBDlg::OnEnChangeEdit3)
END_MESSAGE_MAP()


// UserSetRGBDlg 消息处理程序


void UserSetRGBDlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
