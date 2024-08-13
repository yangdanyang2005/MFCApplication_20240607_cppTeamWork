// deldlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication_20240607_cppTeamWork.h"
#include "afxdialogex.h"
#include "deldlg.h"


// deldlg 对话框

IMPLEMENT_DYNAMIC(deldlg, CDialogEx)

deldlg::deldlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG13, pParent)
	, name(_T(""))
{

}

deldlg::~deldlg()
{
}

void deldlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, name);
}


BEGIN_MESSAGE_MAP(deldlg, CDialogEx)
END_MESSAGE_MAP()


// deldlg 消息处理程序
