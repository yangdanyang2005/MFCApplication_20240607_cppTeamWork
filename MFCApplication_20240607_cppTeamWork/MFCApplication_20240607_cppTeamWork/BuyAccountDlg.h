#pragma once
#include "afxdialogex.h"


// BuyAccountDlg 对话框

class BuyAccountDlg : public CDialogEx
{
	DECLARE_DYNAMIC(BuyAccountDlg)

public:
	BuyAccountDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~BuyAccountDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG21 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
