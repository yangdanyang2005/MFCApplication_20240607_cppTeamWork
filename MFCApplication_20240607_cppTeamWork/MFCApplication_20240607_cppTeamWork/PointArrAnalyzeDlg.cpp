// PointArrAnalyzeDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication_20240607_cppTeamWork.h"
#include "MFCApplication_20240607_cppTeamWorkDoc.h"
#include "afxdialogex.h"
#include "PointArrAnalyzeDlg.h"
#include <numeric> // for std::accumulate

// PointArrAnalyzeDlg 对话框

IMPLEMENT_DYNAMIC(PointArrAnalyzeDlg, CDialogEx)

PointArrAnalyzeDlg::PointArrAnalyzeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG31, pParent)
    , maxAnalyze(0)
    , meanAnalyze(0)
    , minAnalyze(0)
    , medianAnalyze(0)
    , rangeAnalyze(0)
    , varianceAnalyze(0)
    , stddevAnalyze(0)
    , q3Analyze(0)
    , q1Analyze(0)
    , cvAnalyze(0)
    , numAnalyze(0)
    , skewnessAnalyze(0)
    , kurtosis(0)
{

}

PointArrAnalyzeDlg::~PointArrAnalyzeDlg()
{
}

void PointArrAnalyzeDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO2, m_comboChooseAnalyze);
    DDX_Text(pDX, IDC_EDIT_MAX, maxAnalyze);
    DDX_Text(pDX, IDC_EDIT_MEAN, meanAnalyze);
    DDX_Text(pDX, IDC_EDIT_MIN, minAnalyze);
    DDX_Text(pDX, IDC_EDIT_MEDIAN, medianAnalyze);
    DDX_Text(pDX, IDC_EDIT_RANGE, rangeAnalyze);
    DDX_Text(pDX, IDC_EDIT_VARIANCE, varianceAnalyze);
    DDX_Text(pDX, IDC_EDIT_STDDEV, stddevAnalyze);
    DDX_Text(pDX, IDC_EDIT_Q3, q3Analyze);
    DDX_Text(pDX, IDC_EDIT_Q1, q1Analyze);
    DDX_Text(pDX, IDC_EDIT_CV, cvAnalyze);
    DDX_Text(pDX, IDC_EDIT_NUM, numAnalyze);
    DDX_Text(pDX, IDC_EDIT_SKEWNESS, skewnessAnalyze);
    DDX_Text(pDX, IDC_EDIT_KURTOSIS, kurtosis);
}


BEGIN_MESSAGE_MAP(PointArrAnalyzeDlg, CDialogEx)
    ON_WM_MOUSEMOVE()
    ON_CBN_SELCHANGE(IDC_COMBO2, &PointArrAnalyzeDlg::OnCbnSelchangeComboChooseToAnalyze)
END_MESSAGE_MAP()


// PointArrAnalyzeDlg 消息处理程序


BOOL PointArrAnalyzeDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化
    UpdateData(TRUE);
    CFrameWnd* pMainFrame = (CFrameWnd*)AfxGetMainWnd();
    CFrameWnd* pActiveFrame = pMainFrame->GetActiveFrame();
    CDocument* pActiveDocument = pActiveFrame->GetActiveDocument();
    CMFCApplication20240607cppTeamWorkDoc* pDoc = dynamic_cast<CMFCApplication20240607cppTeamWorkDoc*>(pActiveDocument);//从文档读取变量数据到对话框中

    // 提取指定条目，并存入 vector 中
    switch (PointArrAnalyzeDataFlag)
    {
    case 0:
        for (int i = 0; i < pDoc->arr.m_Num; ++i) {
            xValues.push_back(pDoc->arr.m_PointArr[i].getX());
            yValues.push_back(pDoc->arr.m_PointArr[i].getY());
            zValues.push_back(pDoc->arr.m_PointArr[i].getZ());
            sumXYZValues.push_back(pDoc->arr.m_PointArr[i].sumXYZ());
            euclideanNormValues.push_back(pDoc->arr.m_PointArr[i].euclideanNorm());
        }
        break;

    case 1:
        for (int i = 0; i < pDoc->arrSQL.m_Num; ++i) {
            xValues.push_back(pDoc->arrSQL.m_PointArr[i].getX());
            yValues.push_back(pDoc->arrSQL.m_PointArr[i].getY());
            zValues.push_back(pDoc->arrSQL.m_PointArr[i].getZ());
            sumXYZValues.push_back(pDoc->arrSQL.m_PointArr[i].sumXYZ());
            euclideanNormValues.push_back(pDoc->arrSQL.m_PointArr[i].euclideanNorm());
        }
        break;
    }

    // 创建 ToolTip 控件
    m_ToolTip.Create(this);
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_MAX), _T("最大值（Max Value）：数据集中最大的数值。"));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_MIN), _T("最小值（Min Value）：数据集中最小的数值。"));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_MEAN), _T("平均值（Mean Value）：数据集所有数值的总和除以数据的个数。"));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_MEDIAN), _T("中位数（Median Value）：将数据按升序排列后，中间的数值。"));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_VARIANCE), _T("方差（Variance）：数据值与其平均值之间差异的平方的平均值。"));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_STDDEV), _T("标准差（Standard Deviation）：方差的平方根。"));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_RANGE), _T("极差（Range）：数据集中最大值与最小值之差。"));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_Q1), _T("下四分位数（Q1）：数据按升序排列后，处于第 25 百分位数的位置的数值。"));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_Q3), _T("上四分位数（Q3）：数据按升序排列后，处于第 75 百分位数的位置的数值。"));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_CV), _T("变异系数（Coefficient of Variation）：标准差与平均值的比率。"));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_NUM), _T("数据个数（Number of Data）：数据集中数据的个数。"));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_SKEWNESS), _T("偏度（Skewness）：描述数据分布的非对称性。正偏度表示数据在均值右侧分布较多，负偏度表示数据在均值左侧分布较多。偏度为零表示数据分布对称。"));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_KURTOSIS), _T("峰度（Kurtosis）：描述数据分布的陡峭程度。高峰度意味着数据分布有较高的峰值和重尾，低峰度意味着数据分布较为平坦。峰度为零表示数据分布的尖峭程度与正态分布相同。"));

    // 显示 ToolTip
    m_ToolTip.Activate(TRUE);

    // 获取下拉框控件的对象
    CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO2);
    // 确保下拉框控件对象有效
    if (pComboBox != nullptr)
    {
        // 设置下拉框的项
        //pComboBox->AddString(_T("选项1"));
        //pComboBox->AddString(_T("选项2"));
        //pComboBox->AddString(_T("选项3"));

        // 设置默认选中的项（例如，选择第一项）
        pComboBox->SetCurSel(0);  // 索引从0开始，1表示第二项
    }

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}

void PointArrAnalyzeDlg::OnMouseMove(UINT nFlags, CPoint point)
{
    CDialogEx::OnMouseMove(nFlags, point);

    // 获取当前消息
    MSG msg;
    ::PeekMessage(&msg, nullptr, 0, 0, PM_NOREMOVE);

    // 传递鼠标移动消息给 ToolTip 控件
    m_ToolTip.RelayEvent(&msg);
}

void PointArrAnalyzeDlg::OnCbnSelchangeComboChooseToAnalyze()
{
    // TODO: 在此添加控件通知处理程序代码

    //https://blog.csdn.net/qq_27524749/article/details/124654405

    //获得下拉框选中的序号
    int index = m_comboChooseAnalyze.GetCurSel();

    switch (index)
    {
    case 0:
    {
        AfxMessageBox(_T("请选择您想要进行统计分析的数据项！"));

        // 清空之前选择的数据
        maxAnalyze = 0;
        meanAnalyze = 0;
        minAnalyze = 0;
        medianAnalyze = 0;
        rangeAnalyze = 0;
        varianceAnalyze = 0;
        stddevAnalyze = 0;
        q3Analyze = 0;
        q1Analyze = 0;
        cvAnalyze = 0;
        numAnalyze = 0;
        skewnessAnalyze = 0;
        kurtosis = 0;
        
        // 更新显示
        UpdateData(FALSE);
        break;
    }

    //x坐标
    case 1:
    {
        // 计算统计学数据
        maxAnalyze = maxValue(xValues);
        meanAnalyze = meanValue(xValues);
        minAnalyze = minValue(xValues);
        medianAnalyze = medianValue(xValues);
        rangeAnalyze = rangeValue(xValues);
        varianceAnalyze = varianceValue(xValues);
        stddevAnalyze = stdDeviationValue(xValues);
        q3Analyze = upperQuartile(xValues);
        q1Analyze = lowerQuartile(xValues);
        cvAnalyze = coefficientOfVariation(xValues);
        numAnalyze = xValues.size();
        skewnessAnalyze = calculateSkewness(xValues);
        kurtosis = calculateKurtosis(xValues);

        // 更新显示
        UpdateData(FALSE);
        break;
    }

    //y坐标
    case 2:
    {
        // 计算统计学数据
        maxAnalyze = maxValue(yValues);
        meanAnalyze = meanValue(yValues);
        minAnalyze = minValue(yValues);
        medianAnalyze = medianValue(yValues);
        rangeAnalyze = rangeValue(yValues);
        varianceAnalyze = varianceValue(yValues);
        stddevAnalyze = stdDeviationValue(yValues);
        q3Analyze = upperQuartile(yValues);
        q1Analyze = lowerQuartile(yValues);
        cvAnalyze = coefficientOfVariation(yValues);
        numAnalyze = yValues.size();
        skewnessAnalyze = calculateSkewness(yValues);
        kurtosis = calculateKurtosis(yValues);

        // 更新显示
        UpdateData(FALSE);
        break;
    }

    //z坐标
    case 3:
    {
        // 计算统计学数据
        maxAnalyze = maxValue(zValues);
        meanAnalyze = meanValue(zValues);
        minAnalyze = minValue(zValues);
        medianAnalyze = medianValue(zValues);
        rangeAnalyze = rangeValue(zValues);
        varianceAnalyze = varianceValue(zValues);
        stddevAnalyze = stdDeviationValue(zValues);
        q3Analyze = upperQuartile(zValues);
        q1Analyze = lowerQuartile(zValues);
        cvAnalyze = coefficientOfVariation(zValues);
        numAnalyze = zValues.size();
        skewnessAnalyze = calculateSkewness(zValues);
        kurtosis = calculateKurtosis(zValues);

        // 更新显示
        UpdateData(FALSE);
        break;
    }

    //三维坐标的曼哈顿距离
    case 4:
    {
        // 计算统计学数据
        maxAnalyze = maxValue(sumXYZValues);
        meanAnalyze = meanValue(sumXYZValues);
        minAnalyze = minValue(sumXYZValues);
        medianAnalyze = medianValue(sumXYZValues);
        rangeAnalyze = rangeValue(sumXYZValues);
        varianceAnalyze = varianceValue(sumXYZValues);
        stddevAnalyze = stdDeviationValue(sumXYZValues);
        q3Analyze = upperQuartile(sumXYZValues);
        q1Analyze = lowerQuartile(sumXYZValues);
        cvAnalyze = coefficientOfVariation(sumXYZValues);
        numAnalyze = sumXYZValues.size();
        skewnessAnalyze = calculateSkewness(sumXYZValues);
        kurtosis = calculateKurtosis(sumXYZValues);

        // 更新显示
        UpdateData(FALSE);
        break;
    }

    //三维坐标的欧氏距离
    case 5:
    {
        // 计算统计学数据
        maxAnalyze = maxValue(euclideanNormValues);
        meanAnalyze = meanValue(euclideanNormValues);
        minAnalyze = minValue(euclideanNormValues);
        medianAnalyze = medianValue(euclideanNormValues);
        rangeAnalyze = rangeValue(euclideanNormValues);
        varianceAnalyze = varianceValue(euclideanNormValues);
        stddevAnalyze = stdDeviationValue(euclideanNormValues);
        q3Analyze = upperQuartile(euclideanNormValues);
        q1Analyze = lowerQuartile(euclideanNormValues);
        cvAnalyze = coefficientOfVariation(euclideanNormValues);
        numAnalyze = euclideanNormValues.size();
        skewnessAnalyze = calculateSkewness(euclideanNormValues);
        kurtosis = calculateKurtosis(euclideanNormValues);

        // 更新显示
        UpdateData(FALSE);
        break;
    }

    default:
    {
        AfxMessageBox(_T("程序发生异常！"));
        break;
    }
    }
}
