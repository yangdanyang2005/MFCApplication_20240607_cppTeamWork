#pragma once
#include "afxdialogex.h"


// CTeamWorkDialog 对话框

class CTeamWorkDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CTeamWorkDialog)

public:
	CTeamWorkDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CTeamWorkDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG23 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_staticText;
	afx_msg void OnStnClickedStatic1();
	CStatic m_Text2;
	CStatic Text3;
	CStatic Text4;
};
