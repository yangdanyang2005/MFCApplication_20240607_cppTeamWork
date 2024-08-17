// quickSortDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication_20240607_cppTeamWork.h"
#include "afxdialogex.h"
#include "quickSortDlg.h"


// quickSortDlg 对话框

IMPLEMENT_DYNAMIC(quickSortDlg, CDialogEx)

quickSortDlg::quickSortDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG10, pParent)
	, m_nChooseSort(0)
{

}

quickSortDlg::~quickSortDlg()
{
}

void quickSortDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO1, m_nChooseSort);
}


BEGIN_MESSAGE_MAP(quickSortDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &quickSortDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// quickSortDlg 消息处理程序
void quickSortDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}