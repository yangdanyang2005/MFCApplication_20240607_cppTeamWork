#pragma once
#include "afxdialogex.h"


// PointArrAnalyzeDlg 对话框

class PointArrAnalyzeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(PointArrAnalyzeDlg)

public:
	PointArrAnalyzeDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~PointArrAnalyzeDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG31 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void OnMouseMove(UINT nFlags, CPoint point);
	CToolTipCtrl m_ToolTip;
	CComboBox m_comboChooseAnalyze;
	afx_msg void OnCbnSelchangeComboChooseToAnalyze();
	// 最大值
	double maxAnalyze;
	// 平均值
	double meanAnalyze;
	// 最小值
	double minAnalyze;
	// 中位数
	double medianAnalyze;
	// 极差
	double rangeAnalyze;
	// 方差
	double varianceAnalyze;
	// 标准差
	double stddevAnalyze;
	// 上四分位数
	double q3Analyze;
	// 下四分位数
	double q1Analyze;
	// 变异系数
	double cvAnalyze;
	// 峰度
	double skewAnalyze;
	// 偏度
	double kurtAnalyze;
	// 样本大小
	int sampleSizeAnalyze;
	//用于存储不同数据项的容器
	vector<double> xValues, yValues, zValues, sumXYZValues, euclideanNormValues;

	// 数据大小
	double numAnalyze;
	// 偏度
	double skewnessAnalyze;
	// 峰度
	double kurtosis;
};
