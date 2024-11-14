#pragma once
#include "afxdialogex.h"


// IsRememberPasswordDlg 对话框

class IsRememberPasswordDlg : public CDialogEx
{
	DECLARE_DYNAMIC(IsRememberPasswordDlg)

public:
	IsRememberPasswordDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~IsRememberPasswordDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG25 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOkToRememberPassword();
	afx_msg void OnBnClickedCancelToRememberPassword();
};
