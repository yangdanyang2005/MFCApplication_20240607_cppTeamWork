#pragma once
#include "afxdialogex.h"


// bubbleSortDlg 对话框

class bubbleSortDlg : public CDialogEx
{
	DECLARE_DYNAMIC(bubbleSortDlg)

public:
	bubbleSortDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~bubbleSortDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG9 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_nChooseSort;
	afx_msg void OnCbnSelchangeCombo1();
};
