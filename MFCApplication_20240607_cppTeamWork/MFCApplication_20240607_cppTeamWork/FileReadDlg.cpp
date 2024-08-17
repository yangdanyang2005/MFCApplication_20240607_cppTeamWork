// FileReadDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication_20240607_cppTeamWork.h"
#include "afxdialogex.h"
#include "FileReadDlg.h"


// FileReadDlg 对话框

IMPLEMENT_DYNAMIC(FileReadDlg, CDialogEx)

FileReadDlg::FileReadDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, filePath(_T(defaultFilePath.c_str()))
{

}

FileReadDlg::~FileReadDlg()
{
}

void FileReadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, filePath);
}


BEGIN_MESSAGE_MAP(FileReadDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &FileReadDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// FileReadDlg 消息处理程序


void FileReadDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
