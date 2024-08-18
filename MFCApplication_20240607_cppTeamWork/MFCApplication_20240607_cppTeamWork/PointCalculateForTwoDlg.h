#pragma once
#include "afxdialogex.h"
#include "MFCApplication_20240607_cppTeamWorkDoc.h"

#define PI acos(-1)

// PointCalculateForTwoDlg 对话框

class PointCalculateForTwoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(PointCalculateForTwoDlg)

public:
	PointCalculateForTwoDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~PointCalculateForTwoDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG17 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 用户输入的用来进行两点计算的x坐标
	double a_x;
	// 用户输入的用来进行两点计算的y坐标
	double a_y;
	// 用户输入的用来进行两点计算的z坐标
	double a_z;
	// 最近点点名
	CString closeName;
	// 最近点x坐标
	double closeX;
	// 最近点y坐标
	double closeY;
	// 最近点z坐标
	double closeZ;
	// 所求的最小斜距
	double closeSlantDis;
	// 水平距离
	double prjDis;
	// 高差
	double hDiff;
	// 高度角的弧度
	double altitudeAng;
	// 天顶距的弧度
	double zenithAng;
	// 高度角的度
	int aDegree;
	// 高度角的分
	int aMinute;
	// 高度角的秒
	double aSecond;
	// 天顶距的度
	int zDegree;
	// 天顶距的分
	int zMinute;
	// 天顶距的秒
	double zSecond;
	double heightDifference;//高差
	double horizontalDis;//水平距离
	double minSlantDis;//最小斜距
	double altitude;//高度角
	double zenithAngle;//天顶距
	int degree1;//度
	int minute1;//分
	double second1;//秒
	int degree2;//度
	int minute2;//分
	double second2;//秒
	afx_msg void OnBnClickedButtonPointCalculateForTwo();
	//--------------------------两点计算函数--------------------------
	//求斜距
	double GetSlantDis(Point a, Point b)
	{
		double SlantDis = sqrt(pow(a.getX() - b.getX(), 2) +
			pow(a.getY() - b.getY(), 2) +
			pow(a.getZ() - b.getZ(), 2));
		return SlantDis;
	}
	//求高差 
	double GetHeightDifference(Point a, Point b)
	{
		double funcHeightDifference = 0.0;
		funcHeightDifference = a.getZ() - b.getZ();
		heightDifference = funcHeightDifference;
		return funcHeightDifference;
	}
	//求水平距
	double GetHorizontalDis(Point a, Point b)
	{
		double funcHorizontalDis = 0.0;
		funcHorizontalDis = sqrt(pow(a.getX() - b.getX(), 2) + pow(a.getY() - b.getY(), 2));
		horizontalDis = funcHorizontalDis;
		return funcHorizontalDis;
	}
	//求最小斜距
	void GetMinDis(Point a, PointArr arr, Point& closePoint)
	{
		double MinDis = GetSlantDis(a, arr.m_PointArr[0]);
		int j = 0;
		for (int i = 0; i < arr.m_Num; ++i)
		{
			if (GetSlantDis(a, arr.m_PointArr[i]) < MinDis)
			{
				MinDis = GetSlantDis(a, arr.m_PointArr[i]);
				j = i;
			}
		}
		closePoint = arr.m_PointArr[j];
		minSlantDis = MinDis;
	}
	//角度换算函数,将弧度转换为度分秒
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
	//求高度角(含弧度制转换)
	void GetAltitude(Point a, Point b)
	{
		double d = GetHorizontalDis(a, b);//水平距离
		double h = GetHeightDifference(a, b);//高差
		double funcAltitude = atan2(h, d);
		/*atan2是一个函数，在C语言里返回的是指方位角，
		C 语言中atan2的函数原型为 double atan2(double y, double x) ，
		返回以弧度表示的 y/x 的反正切。y 和 x 的值的符号决定了正确的象限。
		也可以理解为计算复数 x+yi 的辐角，计算时atan2 比 atan 稳定。*/
		if (funcAltitude > 2 * PI)
		{
			altitudeAng = funcAltitude - 2 * PI;
		}
		else if (funcAltitude > PI && funcAltitude <= 2 * PI)
		{
			altitudeAng = 2 * PI - funcAltitude;
		}
		else if (funcAltitude < 0)
		{
			altitudeAng += 2 * PI;
		}
		else
		{
			altitudeAng = funcAltitude;
		}
		radToDms1(altitudeAng);
	}
	//求天顶距(含弧度制转换)
	void GetZenithAngle(Point a, Point b)
	{
		double d = GetHorizontalDis(a, b);//水平距离
		double h = GetHeightDifference(a, b);//高差
		double funcZenithAngle = atan2(h, d);
		/*atan2是一个函数，在C语言里返回的是指方位角，
		C 语言中atan2的函数原型为 double atan2(double y, double x) ，
		返回以弧度表示的 y/x 的反正切。y 和 x 的值的符号决定了正确的象限。
		也可以理解为计算复数 x+yi 的辐角，计算时atan2 比 atan 稳定。*/
		if (funcZenithAngle > 2 * PI)
		{
			zenithAng = funcZenithAngle - 2 * PI;
		}
		else if (funcZenithAngle > PI && funcZenithAngle <= 2 * PI)
		{
			zenithAng = 2 * PI - funcZenithAngle;
		}
		else if (funcZenithAngle < 0)
		{
			zenithAng += 2 * PI;
		}
		else
		{
			zenithAng = funcZenithAngle;
		}
		radToDms2(zenithAng);
	}
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnEnChangeEdit3();
};
