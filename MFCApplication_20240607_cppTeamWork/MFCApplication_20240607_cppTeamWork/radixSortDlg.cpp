// radixSortDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication_20240607_cppTeamWork.h"
#include "afxdialogex.h"
#include "radixSortDlg.h"


// radixSortDlg 对话框

IMPLEMENT_DYNAMIC(radixSortDlg, CDialogEx)

radixSortDlg::radixSortDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG12, pParent)
	, m_nChooseSort(0)
{

}

radixSortDlg::~radixSortDlg()
{
}

void radixSortDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO1, m_nChooseSort);
}


BEGIN_MESSAGE_MAP(radixSortDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &radixSortDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// radixSortDlg 消息处理程序
void radixSortDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}
