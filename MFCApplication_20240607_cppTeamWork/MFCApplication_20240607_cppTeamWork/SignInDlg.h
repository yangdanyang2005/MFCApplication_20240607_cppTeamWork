#pragma once
#include "afxdialogex.h"


// SignInDlg 对话框

class SignInDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SignInDlg)

public:
	SignInDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~SignInDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG20 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 用户在登录界面输入的用户名
	CString m_username;
	// 用户在登录界面输入的密码
	CString m_password;
	// 复选框“是否明文显示密码”的变量
	CButton m_passwordcheck;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedPasswordstyle();
	virtual BOOL OnInitDialog();
	bool isSignInOk;
	afx_msg void OnBnClickedButtonBuyAccount();
	// 用户选择是否记住密码的复选框
	CButton m_rememberPasswordCheck;
	afx_msg void OnBnClickedRememberPasswordStyle();
	// 用户选择的“下次自动登录”按钮的变量
	CButton isAutoLogIn;
	afx_msg void OnBnClickedCheckAutoLogIn();
};
