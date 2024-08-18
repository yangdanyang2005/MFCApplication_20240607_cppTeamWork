#pragma once
#include "afxdialogex.h"


// SelectSortDlg 对话框

class SelectSortDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SelectSortDlg)

public:
	SelectSortDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~SelectSortDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG7 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_nChooseSort;
	afx_msg void OnCbnSelchangeCombo1();
};
