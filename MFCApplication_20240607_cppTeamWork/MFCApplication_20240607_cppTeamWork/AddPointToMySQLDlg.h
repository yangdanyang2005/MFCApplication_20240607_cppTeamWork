#pragma once
#include "afxdialogex.h"


// AddPointToMySQLDlg 对话框

class AddPointToMySQLDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddPointToMySQLDlg)

public:
	AddPointToMySQLDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~AddPointToMySQLDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG28 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 用户向MySQL添加的点的点名
	CString OnAddToMySQLname;
	// 用户向MySQL添加的点的x坐标
	double OnAddToMySQLX;
	// 用户向MySQL添加的点的y坐标
	double OnAddToMySQLY;
	// 用户向MySQL添加的点的z坐标
	double OnAddToMySQLZ;
	afx_msg void OnBnClickedOk();
};
