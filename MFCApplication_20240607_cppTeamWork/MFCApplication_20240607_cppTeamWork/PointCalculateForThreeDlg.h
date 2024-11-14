#pragma once
#include "afxdialogex.h"
#include "MFCApplication_20240607_cppTeamWorkDoc.h"

#define PI acos(-1)

// PointCalculateForThreeDlg 对话框

class PointCalculateForThreeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(PointCalculateForThreeDlg)

public:
	PointCalculateForThreeDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~PointCalculateForThreeDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG18 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 顶点的点名
	CString vertexName;
	// 顶点的x坐标
	double vertexX;
	// 顶点的y坐标
	double vertexY;
	// 顶点的z坐标
	double vertexZ;

	// 角的第一条边上的点的点名
	CString aName;
	// 角的第一条边上的点的x坐标
	double aX;
	// 角的第一条边上的点的y坐标
	double aY;
	// 角的第一条边上的点的z坐标
	double aZ;
	// 角的第二条边上的点的点名

	CString bName;
	// 角的第二条边上的点的x坐标
	double bX;
	// 角的第二条边上的点的y坐标
	double bY;
	// 角的第二条边上的点z坐标
	double bZ;
	afx_msg void OnEnChangeEdit8();
	afx_msg void OnEnChangeEdit10();
	int degree1;//度
	int minute1;//分
	double second1;//秒
	int degree2;//度
	int minute2;//分
	double second2;//秒
	double horizontalDisDlg;//水平距离
	// 对话框中显示的空间角的弧度
	double angDlg;
	// 对话框中显示的空间角的度
	int angDlgDegree;
	// 对话框中显示的空间角的分
	int angDlgMinute;
	// 对话框中显示的空间角的秒
	double angDlgSecond;
	// 对话框中显示的水平投影角的弧度
	double prjangDlg;
	// 对话框中显示的水平投影角的度
	int prjangDlgDegree;
	// 对话框中显示的水平投影角的分
	int prjangDlgMinute;
	// 对话框中显示的水平投影角的秒
	double angprjDlgSecond;
	afx_msg void OnBnClickedButtonCalculateForThree();
	void radToDms1(double rad)
	{
		if (rad < 0)
		{
			rad += 2 * PI; // 将结果转换为0到2π之间的角度
		}
		double degrees = rad * 180.0 / PI;
		degree1 = int(degrees);
		minute1 = int((degrees - degree1) * 60.0);
		second1 = (double)(degrees - degree1 - minute1 / 60.0) * 3600.0;
	}
	void radToDms2(double rad)
	{
		if (rad < 0)
		{
			rad += 2 * PI; // 将结果转换为0到2π之间的角度
		}
		double degrees = rad * 180.0 / PI;
		degree2 = int(degrees);
		minute2 = int((degrees - degree2) * 60.0);
		second2 = (double)(degrees - degree2 - minute2 / 60.0) * 3600.0;
	}
	//求斜距
	double GetSlantDis(Point a, Point b)
	{
		double SlantDis = sqrt(pow(a.getX() - b.getX(), 2) +
			pow(a.getY() - b.getY(), 2) +
			pow(a.getZ() - b.getZ(), 2));
		return SlantDis;
	}
	//求水平距
	double GetHorizontalDis(Point a, Point b)
	{
		double funcHorizontalDis = 0.0;
		funcHorizontalDis = sqrt(pow(a.getX() - b.getX(), 2) + pow(a.getY() - b.getY(), 2));
		horizontalDisDlg = funcHorizontalDis;
		return funcHorizontalDis;
	}
	//求投影角
	void GetProjectAng(Point vertex, Point a, Point b)
	{
		double Side1 = GetHorizontalDis(vertex, a);
		double Side2 = GetHorizontalDis(vertex, b);
		double Side3 = GetHorizontalDis(a, b);
		prjangDlg = acos((pow(Side1, 2) + pow(Side2, 2) - pow(Side3, 2)) / (2 * Side1 * Side2));
		radToDms1(prjangDlg);
	}
	//求空间角
	void GetAng(Point vertex, Point a, Point b)
	{
		double Side1 = GetSlantDis(vertex, a);
		double Side2 = GetSlantDis(vertex, b);
		double Side3 = GetSlantDis(a, b);
		angDlg = acos((pow(Side1, 2) + pow(Side2, 2) - pow(Side3, 2)) / (2 * Side1 * Side2));
		radToDms2(angDlg);
	}
	afx_msg void OnBnClickedOk();
};
