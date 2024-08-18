#pragma once
#include "afxdialogex.h"


// IsRememberVIPKeyDlg 对话框

class IsRememberVIPKeyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(IsRememberVIPKeyDlg)

public:
	IsRememberVIPKeyDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~IsRememberVIPKeyDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG26 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOkToRememberVIPKey();
	afx_msg void OnBnClickedCancelToRememberVIPKey();
};
