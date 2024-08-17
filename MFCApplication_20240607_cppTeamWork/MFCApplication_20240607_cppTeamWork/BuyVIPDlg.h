#pragma once
#include "afxdialogex.h"


// BuyVIPDlg 对话框

class BuyVIPDlg : public CDialogEx
{
	DECLARE_DYNAMIC(BuyVIPDlg)

public:
	BuyVIPDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~BuyVIPDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG22 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonBuy();
	// 用户输入的VIP密钥
	CString vipkey;
	// 复选框变量
	CButton m_passwordcheck;
	afx_msg void OnBnClickedOk();
	bool isBeyVIPOk;
	afx_msg void OnBnClickedVIPkeystyle();
	virtual BOOL OnInitDialog();
	// 用户决定的是否记住VIP密钥的复选框
	CButton IsRememberVIPKeyCheckBox;
	afx_msg void OnBnClickedCheckIsRememberVIPKeyCheckBox();
	afx_msg void OnBnClickedCheckAutoActivateVIP();
	// 用户选择是否在启动软件时自动激活VIP的复选框变量
	CButton isCheckAutoActivateVIP;
};
