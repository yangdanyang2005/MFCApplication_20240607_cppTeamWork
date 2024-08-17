#pragma once
#include "afxdialogex.h"


// FindPointInMySQLDlg 对话框

class FindPointInMySQLDlg : public CDialogEx
{
	DECLARE_DYNAMIC(FindPointInMySQLDlg)

public:
	FindPointInMySQLDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~FindPointInMySQLDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG30 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	// 用户输入的用于在MySQL中查找点的点名
	CString findPointInMySQLname;
	// 用户输入的用于在MySQL中查找点的x坐标
	double findPointInMySQLx;
	// 用户输入的用于在MySQL中查找点的y坐标
	double findPointInMySQLy;
	// 用户输入的用于在MySQL中查找点的z坐标
	double findPointInMySQLz;
};
