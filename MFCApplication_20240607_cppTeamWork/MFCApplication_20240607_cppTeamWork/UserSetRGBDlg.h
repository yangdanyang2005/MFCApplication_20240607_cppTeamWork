#pragma once
#include "afxdialogex.h"


// UserSetRGBDlg 对话框

class UserSetRGBDlg : public CDialogEx
{
	DECLARE_DYNAMIC(UserSetRGBDlg)

public:
	UserSetRGBDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~UserSetRGBDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG19 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 用户设置较高高程处的R值
	int setHighR;
	// 用户设置较高高程处的G值
	int setHighG;
	// 用户设置较高高程处的B值
	int setHighB;
	// 用户设置较低高程处的R值
	int setLowR;
	// 用户设置较低高程处的G值
	int setLowG;
	// 用户设置较低高程处的B值
	int setLowB;
	afx_msg void OnEnChangeEdit3();
};
