#pragma once
#include "afxdialogex.h"


// FileReadDlg 对话框

class FileReadDlg : public CDialogEx
{
	DECLARE_DYNAMIC(FileReadDlg)

public:
	FileReadDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~FileReadDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 打开文件对话框中用户输入的文件路径
	CString filePath;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedOk();
	bool isWantToOpenFile;
	afx_msg void OnBnClickedCancel();
};
