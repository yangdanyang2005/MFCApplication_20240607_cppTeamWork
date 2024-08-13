// mergeSortDig.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication_20240607_cppTeamWork.h"
#include "afxdialogex.h"
#include "mergeSortDig.h"


// mergeSortDig 对话框

IMPLEMENT_DYNAMIC(mergeSortDig, CDialogEx)

mergeSortDig::mergeSortDig(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG11, pParent)
	, m_nChooseSort(0)
{

}

mergeSortDig::~mergeSortDig()
{
}

void mergeSortDig::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO1, m_nChooseSort);
}


BEGIN_MESSAGE_MAP(mergeSortDig, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &mergeSortDig::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// mergeSortDig 消息处理程序
void mergeSortDig::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}
