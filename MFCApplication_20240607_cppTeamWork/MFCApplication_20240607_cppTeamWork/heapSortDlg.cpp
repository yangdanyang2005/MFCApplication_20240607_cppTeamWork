// heapSortDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication_20240607_cppTeamWork.h"
#include "afxdialogex.h"
#include "heapSortDlg.h"


// heapSortDlg 对话框

IMPLEMENT_DYNAMIC(heapSortDlg, CDialogEx)

heapSortDlg::heapSortDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG8, pParent)
	, m_nChooseSort(0)
{

}

heapSortDlg::~heapSortDlg()
{
}

void heapSortDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO1, m_nChooseSort);
}


BEGIN_MESSAGE_MAP(heapSortDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &heapSortDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// heapSortDlg 消息处理程序
void heapSortDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}