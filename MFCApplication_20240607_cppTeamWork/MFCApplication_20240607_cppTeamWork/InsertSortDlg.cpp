// InsertSortDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication_20240607_cppTeamWork.h"
#include "afxdialogex.h"
#include "InsertSortDlg.h"


// InsertSortDlg 对话框

IMPLEMENT_DYNAMIC(InsertSortDlg, CDialogEx)

InsertSortDlg::InsertSortDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
	, m_nChooseSort(0)
{

}

InsertSortDlg::~InsertSortDlg()
{
}

void InsertSortDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO1, m_nChooseSort);
}


BEGIN_MESSAGE_MAP(InsertSortDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &InsertSortDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// InsertSortDlg 消息处理程序


void InsertSortDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}
