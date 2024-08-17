
// MFCApplication_20240607_cppTeamWorkView.h: CMFCApplication20240607cppTeamWorkView 类的接口
//

#pragma once



class CMFCApplication20240607cppTeamWorkView : public CScrollView
{
protected: // 仅从序列化创建
	CMFCApplication20240607cppTeamWorkView() noexcept;
	DECLARE_DYNCREATE(CMFCApplication20240607cppTeamWorkView)

// 特性
public:
	CMFCApplication20240607cppTeamWorkDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	// 用于获取系统时间并显示在视图中——
	CTime m_timeSys; // 用于存储系统时间
	CString m_strTime; // 用于存储格式化的时间字符串
	void UpdateSystemTime(); // 更新系统时间并显示在视图中
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void DrawTime(CDC* pDC);//自定义绘制日期和时间的函数

protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMFCApplication20240607cppTeamWorkView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnReadFile();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnShowPoint();
	afx_msg void OnAdd();
	afx_msg void OnInsertSort();
	afx_msg void OnShellSortz();
	afx_msg void OnBinInsertSortz();
	afx_msg void OnSelectSort();
	afx_msg void OnheapSort();
	afx_msg void OnbubbleSort();
	afx_msg void OnquickSort();
	afx_msg void OnmergeSort();
	afx_msg void OnradixSort();
	afx_msg void Ondel();
	afx_msg void Oncha();
	afx_msg void OnFindPointByName();
	afx_msg void OnFindPointByNum();
	afx_msg void OnPointCalculateForTwo();
	afx_msg void OnPointCalculateForThree();
	afx_msg void OnPaintMap();
	afx_msg void OnSignIn();
	afx_msg void OnFileOpen();
	afx_msg void OnBuyVIPkey();
	afx_msg void OnTeamWork();
	afx_msg void OnMultiKeywordSort();
	afx_msg void OnTimer(UINT_PTR nIDEvent);// 处理定时器消息
	afx_msg void OnGoBackToHomePage();
	afx_msg void OnUseMySQL();
	afx_msg void OnAnalysePointData();
	afx_msg void OnDrawDEM();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
};

#ifndef _DEBUG  // MFCApplication_20240607_cppTeamWorkView.cpp 中的调试版本
inline CMFCApplication20240607cppTeamWorkDoc* CMFCApplication20240607cppTeamWorkView::GetDocument() const
   { return reinterpret_cast<CMFCApplication20240607cppTeamWorkDoc*>(m_pDocument); }
#endif

