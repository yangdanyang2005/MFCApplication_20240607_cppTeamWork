// chaDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication_20240607_cppTeamWork.h"
#include "afxdialogex.h"
#include "chaDlg.h"


// chaDlg 对话框

IMPLEMENT_DYNAMIC(chaDlg, CDialogEx)

chaDlg::chaDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG14, pParent)
	, name1(_T(""))
	, name2(_T(""))
	, x(0)
	, y(0)
	, z(0)
{

}

chaDlg::~chaDlg()
{
}

void chaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT5, name1);
	DDX_Text(pDX, IDC_EDIT1, name2);
	DDX_Text(pDX, IDC_EDIT2, x);
	DDX_Text(pDX, IDC_EDIT3, y);
	DDX_Text(pDX, IDC_EDIT4, z);
}


BEGIN_MESSAGE_MAP(chaDlg, CDialogEx)
END_MESSAGE_MAP()


// chaDlg 消息处理程序
