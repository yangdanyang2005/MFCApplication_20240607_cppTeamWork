#pragma once
#include "afxdialogex.h"


// IsOverwriteFromMySQLToCsvDlg 对话框

class IsOverwriteFromMySQLToCsvDlg : public CDialogEx
{
	DECLARE_DYNAMIC(IsOverwriteFromMySQLToCsvDlg)

public:
	IsOverwriteFromMySQLToCsvDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~IsOverwriteFromMySQLToCsvDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ISOVERWRITEDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	int isOverwriteFileFlag = 0;//0-不执行任何操作，1-覆盖，2-另存为
};
