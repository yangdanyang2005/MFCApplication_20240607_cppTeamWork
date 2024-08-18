// AddPointDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication_20240607_cppTeamWork.h"
#include "afxdialogex.h"
#include "AddPointDlg.h"


// AddPointDlg 对话框

IMPLEMENT_DYNAMIC(AddPointDlg, CDialogEx)

AddPointDlg::AddPointDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, name(_T("gcp"))
	, x(0)
	, y(0)
	, z(0)
{

}

AddPointDlg::~AddPointDlg()
{
}

void AddPointDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, name);
	DDX_Text(pDX, IDC_EDIT2, x);
	DDX_Text(pDX, IDC_EDIT3, y);
	DDX_Text(pDX, IDC_EDIT4, z);
}


BEGIN_MESSAGE_MAP(AddPointDlg, CDialogEx)
	
	ON_EN_CHANGE(IDC_EDIT1, &AddPointDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// AddPointDlg 消息处理程序


void AddPointDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
