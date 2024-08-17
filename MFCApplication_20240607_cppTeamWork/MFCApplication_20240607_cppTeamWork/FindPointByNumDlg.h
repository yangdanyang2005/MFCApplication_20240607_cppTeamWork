#pragma once
#include "afxdialogex.h"
#include "MFCApplication_20240607_cppTeamWorkDoc.h"

// FindPointByNumDlg 对话框

class FindPointByNumDlg : public CDialogEx
{
	DECLARE_DYNAMIC(FindPointByNumDlg)

public:
	FindPointByNumDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~FindPointByNumDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG16 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 用户输入的用于查找的x坐标
	double xFind;
	// 用户输入的用于查找的y坐标
	double yFind;
	// 用户输入的用于查找的z坐标
	double zFind;

	//初始化的默认数据，可以用来做查询记忆
	//double defaultFindNumX = 0.0;
	//double defaultFindNumY = 0.0;
	//double defaultFindNumZ = 0.0;

	// 按照点的数据进行查找的对话框中用于显示查找到的点的数据的表格
	CListCtrl m_listCtrl;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonFindPointByNum();
	bool GetPt2(string ch, PointArr arr, PointArr& arrFind, double x, double y, double z)
	{
		//输入1、2或3个坐标值查找
		int i = 0; int j = 0; double m1, m2, m3; int t = 0;
		int n = arr.m_Num; int arrNum[1024];

		//ch用于情况判断，类似于switch case的逻辑
		if (ch == "x")
		{
			m1 = x;
			for (i = 0; i < arr.m_Num; i++)
			{
				if (arr.m_PointArr[i].getX() == m1)
				{
					t++;
					arrNum[j] = i; j++;
				}
			}
			arrFind.m_Num = t;
			if (t == 0)
			{
				AfxMessageBox(_T("没有查找到符合查找条件的点！")); return false;
			}
			arrFind.m_PointArr = new Point[t];//一定要分配内存
			for (j = 0; j < t; j++)
			{
				arrFind.m_PointArr[j] = arr.m_PointArr[arrNum[j]];
			}
			return true;
		}
		else if (ch == "y")
		{
			m1 = y;
			for (i = 0; i < arr.m_Num; i++)
			{
				if (arr.m_PointArr[i].getY() == m1)
				{
					t++;
					arrNum[j] = i; j++;
				}
			}
			arrFind.m_Num = t;
			if (t == 0)
			{
				AfxMessageBox(_T("没有查找到符合查找条件的点！")); return false;
			}
			arrFind.m_PointArr = new Point[t];//一定要分配内存
			for (j = 0; j < t; j++)
			{
				arrFind.m_PointArr[j] = arr.m_PointArr[arrNum[j]];
			}
			return true;
		}
		else if (ch == "z")
		{
			m1 = z;
			for (i = 0; i < arr.m_Num; i++)
			{
				if (arr.m_PointArr[i].getZ() == m1)
				{
					t++;
					arrNum[j] = i; j++;
				}
			}
			arrFind.m_Num = t;
			if (t == 0)
			{
				AfxMessageBox(_T("没有查找到符合查找条件的点！")); return false;
			}
			arrFind.m_PointArr = new Point[t];//一定要分配内存
			for (j = 0; j < t; j++)
			{
				arrFind.m_PointArr[j] = arr.m_PointArr[arrNum[j]];
			}
			return true;
		}
		else if (ch == "xy")
		{
			m1 = x; m2 = y;
			for (i = 0; i < arr.m_Num; i++)
			{
				if (arr.m_PointArr[i].getX() == m1 && arr.m_PointArr[i].getY() == m2)
				{
					t++;
					arrNum[j] = i; j++;
				}
			}
			arrFind.m_Num = t;
			if (t == 0)
			{
				AfxMessageBox(_T("没有查找到符合查找条件的点！")); return false;
			}
			arrFind.m_PointArr = new Point[t];//一定要分配内存
			for (j = 0; j < t; j++)
			{
				arrFind.m_PointArr[j] = arr.m_PointArr[arrNum[j]];
			}
			return true;
		}
		else if (ch == "xz")
		{
			m1 = x; m3 = z;
			for (i = 0; i < arr.m_Num; i++)
			{
				if (arr.m_PointArr[i].getX() == m1 && arr.m_PointArr[i].getZ() == m3)
				{
					t++;
					arrNum[j] = i; j++;
				}
			}
			arrFind.m_Num = t;
			if (t == 0)
			{
				AfxMessageBox(_T("没有查找到符合查找条件的点！")); return false;
			}
			arrFind.m_PointArr = new Point[t];//一定要分配内存
			for (j = 0; j < t; j++)
			{
				arrFind.m_PointArr[j] = arr.m_PointArr[arrNum[j]];
			}
			return true;
		}
		else if (ch == "yz")
		{
			m2 = y; m3 = z;
			for (i = 0; i < arr.m_Num; i++)
			{
				if (arr.m_PointArr[i].getY() == m2 && arr.m_PointArr[i].getZ() == m3)
				{
					t++;
					arrNum[j] = i; j++;
				}
			}
			arrFind.m_Num = t;
			if (t == 0)
			{
				AfxMessageBox(_T("没有查找到符合查找条件的点！")); return false;
			}
			arrFind.m_PointArr = new Point[t];//一定要分配内存
			for (j = 0; j < t; j++)
			{
				arrFind.m_PointArr[j] = arr.m_PointArr[arrNum[j]];
			}
			return true;
		}
		else if (ch == "xyz")
		{
			m1 = x; m2 = y; m3 = z;
			for (i = 0; i < arr.m_Num; i++)
			{
				if (arr.m_PointArr[i].getX() == m1 && arr.m_PointArr[i].getY() == m2 && arr.m_PointArr[i].getZ() == m3)
				{
					t++;
					arrNum[j] = i; j++;
				}
			}
			arrFind.m_Num = t;
			if (t == 0)
			{
				AfxMessageBox(_T("没有查找到符合查找条件的点！")); return false;
			}
			arrFind.m_PointArr = new Point[t];//一定要分配内存
			for (j = 0; j < t; j++)
			{
				arrFind.m_PointArr[j] = arr.m_PointArr[arrNum[j]];
			}
			return true;
		}
		else
		{
			AfxMessageBox(_T("查找条件选择异常！")); return false;
		}
	}

};
