// BinInsertSortzDig.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication_20240607_cppTeamWork.h"
#include "afxdialogex.h"
#include "BinInsertSortzDig.h"


// BinInsertSortzDig 对话框

IMPLEMENT_DYNAMIC(BinInsertSortzDig, CDialogEx)

BinInsertSortzDig::BinInsertSortzDig(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG6, pParent)
	, m_nChooseSort(0)
{

}

BinInsertSortzDig::~BinInsertSortzDig()
{
}

void BinInsertSortzDig::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO1, m_nChooseSort);
}


BEGIN_MESSAGE_MAP(BinInsertSortzDig, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &BinInsertSortzDig::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// BinInsertSortzDig 消息处理程序
void BinInsertSortzDig::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}