#pragma once
#include "afxdialogex.h"


// BinInsertSortzDig 对话框

class BinInsertSortzDig : public CDialogEx
{
	DECLARE_DYNAMIC(BinInsertSortzDig)

public:
	BinInsertSortzDig(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~BinInsertSortzDig();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG6 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_nChooseSort;
	afx_msg void OnCbnSelchangeCombo1();
};
