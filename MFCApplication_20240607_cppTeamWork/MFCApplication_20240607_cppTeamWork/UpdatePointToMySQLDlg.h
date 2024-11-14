#pragma once
#include "afxdialogex.h"


// UpdatePointToMySQLDlg 对话框

class UpdatePointToMySQLDlg : public CDialogEx
{
	DECLARE_DYNAMIC(UpdatePointToMySQLDlg)

public:
	UpdatePointToMySQLDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~UpdatePointToMySQLDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG29 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 用户在MySQL数据库中修改后的点的点名
	CString OnUpdateToMySQLname;
	// 用户在MySQL数据库中修改的点的x坐标
	double OnUpdateToMySQLX;
	// 用户在MySQL数据库中修改的点的y坐标
	double OnUpdateToMySQLY;
	// 用户在MySQL数据库中修改的点的z坐标
	double OnUpdateToMySQLZ;
	afx_msg void OnBnClickedOk();
};
