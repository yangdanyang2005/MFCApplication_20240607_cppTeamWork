// CTeamWorkDialog.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication_20240607_cppTeamWork.h"
#include "afxdialogex.h"
#include "CTeamWorkDialog.h"


// CTeamWorkDialog 对话框

IMPLEMENT_DYNAMIC(CTeamWorkDialog, CDialogEx)

CTeamWorkDialog::CTeamWorkDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG23, pParent)
{

}

CTeamWorkDialog::~CTeamWorkDialog()
{
}

void CTeamWorkDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, m_staticText);
	DDX_Control(pDX, IDC_STATIC2, m_Text2);
	DDX_Control(pDX, IDC_STATIC3, Text3);
	DDX_Control(pDX, IDC_STATIC4, Text4);
}


BEGIN_MESSAGE_MAP(CTeamWorkDialog, CDialogEx)
	ON_STN_CLICKED(IDC_STATIC1, &CTeamWorkDialog::OnStnClickedStatic1)
END_MESSAGE_MAP()


// CTeamWorkDialog 消息处理程序


void CTeamWorkDialog::OnStnClickedStatic1()
{
	// TODO: 在此添加控件通知处理程序代码
}
