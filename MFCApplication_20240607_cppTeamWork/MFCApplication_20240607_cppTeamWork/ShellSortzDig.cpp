// ShellSortzDig.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication_20240607_cppTeamWork.h"
#include "afxdialogex.h"
#include "ShellSortzDig.h"


// ShellSortzDig 对话框

IMPLEMENT_DYNAMIC(ShellSortzDig, CDialogEx)

ShellSortzDig::ShellSortzDig(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG5, pParent)
	, m_nChooseSort(0)
{

}

ShellSortzDig::~ShellSortzDig()
{
}

void ShellSortzDig::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO1, m_nChooseSort);
}


BEGIN_MESSAGE_MAP(ShellSortzDig, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &ShellSortzDig::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// ShellSortzDig 消息处理程序


void ShellSortzDig::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}