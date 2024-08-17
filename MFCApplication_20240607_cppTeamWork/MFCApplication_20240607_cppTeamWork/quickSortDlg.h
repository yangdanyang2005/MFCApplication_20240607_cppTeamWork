#pragma once
#include "afxdialogex.h"


// quickSortDlg 对话框

class quickSortDlg : public CDialogEx
{
	DECLARE_DYNAMIC(quickSortDlg)

public:
	quickSortDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~quickSortDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG10 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_nChooseSort;
	afx_msg void OnCbnSelchangeCombo1();
};
