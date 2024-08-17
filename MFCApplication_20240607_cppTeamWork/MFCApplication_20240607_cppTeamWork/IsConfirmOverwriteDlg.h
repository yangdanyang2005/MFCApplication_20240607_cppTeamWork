#pragma once
#include "afxdialogex.h"


// IsConfirmOverwriteDlg 对话框

class IsConfirmOverwriteDlg : public CDialogEx
{
	DECLARE_DYNAMIC(IsConfirmOverwriteDlg)

public:
	IsConfirmOverwriteDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~IsConfirmOverwriteDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CONFIRM_OVERWRITE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	bool isConfirmOverwrite;
};
