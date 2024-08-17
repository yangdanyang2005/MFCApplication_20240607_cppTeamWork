// SelectSortDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication_20240607_cppTeamWork.h"
#include "afxdialogex.h"
#include "SelectSortDlg.h"


// SelectSortDlg 对话框

IMPLEMENT_DYNAMIC(SelectSortDlg, CDialogEx)

SelectSortDlg::SelectSortDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG7, pParent)
	, m_nChooseSort(0)
{

}

SelectSortDlg::~SelectSortDlg()
{
}

void SelectSortDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO1, m_nChooseSort);
}


BEGIN_MESSAGE_MAP(SelectSortDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &SelectSortDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// SelectSortDlg 消息处理程序
void SelectSortDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}
