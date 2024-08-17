// bubbleSortDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication_20240607_cppTeamWork.h"
#include "afxdialogex.h"
#include "bubbleSortDlg.h"


// bubbleSortDlg 对话框

IMPLEMENT_DYNAMIC(bubbleSortDlg, CDialogEx)

bubbleSortDlg::bubbleSortDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG9, pParent)
	, m_nChooseSort(0)
{

}

bubbleSortDlg::~bubbleSortDlg()
{
}

void bubbleSortDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO1, m_nChooseSort);
}


BEGIN_MESSAGE_MAP(bubbleSortDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &bubbleSortDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// bubbleSortDlg 消息处理程序
void bubbleSortDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}
