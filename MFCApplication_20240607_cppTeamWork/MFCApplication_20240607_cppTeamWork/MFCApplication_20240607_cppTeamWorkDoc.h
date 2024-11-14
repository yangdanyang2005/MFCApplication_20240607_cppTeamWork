
// MFCApplication_20240607_cppTeamWorkDoc.h: CMFCApplication20240607cppTeamWorkDoc 类的接口
//


#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;

#define PI acos(-1)
static int flag = -1;//用于判断视图更新为什么的标志
static char* filePath = new char[1024];//用户打开文件的时候输入的文件路径

/**************************测绘相关的全局变量**************************/
static double heightDifference = 0.0;//高差
static double horizontalDis = 0.0;//水平距离
static double minSlantDis = 0.0;//最小斜距
static double altitude = 0.0;//高度角
static double zenithAngle = 0.0;//天顶距
static int* degree = new int[4];//度
static int* minute = new int[4];//分
static double* second = new double[4];//秒
static double projectAng = 0.0;//投影角
static double ang = 0.0;//空间角

COLORREF colors[51][51];

/**************************状态相关的全局变量**************************/
bool isOpenFile = false;
bool isSignIn = false;
bool isBuyVIP = false;
bool isConnectMySQL = false; 
bool isAfxMessageBoxOn = true;
bool isFirstSave = true;
string isOpenFileMsg;
string isSignInMsg;
string isBuyVIPMsg;
string isConnectMySQLMsg;
bool isRememberPassword = false;
bool isRememberVIPKey = false;
string rememberUsername;
string rememberPassword;
string rememberVIPKey;
int nEncryptUsername;
int nEncryptPassword;
int nEncryptVIPKey;
string mainUsername;
bool isAutoLogInGlobal;//是否自动登录的全局变量
bool isCheckAutoActivateVIPGlobal;//是否自动激活VIP的全局变量

int PointArrAnalyzeDataFlag = 0;//0-文档，1-数据库

int nSaveCount = 1;
int nSaveCsvCount = 1;

//初始化的默认数据，可以用来实现对用户输入的数据的记忆功能
double defaultFindNumX = 0.0;
double defaultFindNumY = 0.0;
double defaultFindNumZ = 0.0;
string defaultPointName = "";
string defaultFilePath = "";
string fileSaveName = "viewPrtSc/view_prtsc1.png";

/****************************************统计学相关全局函数****************************************/
// 计算最大值
double maxValue(const vector<double>& data) {
    return *max_element(data.begin(), data.end());
}
// 计算最小值
double minValue(const vector<double>& data) {
    return *min_element(data.begin(), data.end());
}
//计算样本大小
int sampleSize(const vector<double>& data) {
    return data.size();
}
// 计算平均值
double meanValue(const vector<double>& data) {
    return accumulate(data.begin(), data.end(), 0.0) / data.size();
}
// 计算中位数
double medianValue(vector<double>& data) {
    sort(data.begin(), data.end());
    size_t size = data.size();
    if (size % 2 == 0) {
        return (data[size / 2 - 1] + data[size / 2]) / 2;
    }
    else {
        return data[size / 2];
    }
}
// 计算方差
double varianceValue(const vector<double>& data) {
    double mean = meanValue(data);
    double temp = 0;
    for (double value : data) {
        temp += (value - mean) * (value - mean);
    }
    return temp / data.size();
}
// 计算标准差
double stdDeviationValue(const vector<double>& data) {
    return sqrt(varianceValue(data));
}
// 计算极差
double rangeValue(const vector<double>& data) {
    return maxValue(data) - minValue(data);
}
// 计算下四分位数（Q1）
double lowerQuartile(const vector<double>& data) {
    vector<double> sortedData = data;
    sort(sortedData.begin(), sortedData.end());
    size_t midIndex = sortedData.size() / 2;
    vector<double> lowerHalf(sortedData.begin(), sortedData.begin() + midIndex);
    return medianValue(lowerHalf);
}
// 计算上四分位数（Q3）
double upperQuartile(const vector<double>& data) {
    vector<double> sortedData = data;
    sort(sortedData.begin(), sortedData.end());
    size_t midIndex = sortedData.size() / 2;
    vector<double> upperHalf(sortedData.begin() + midIndex + (sortedData.size() % 2), sortedData.end());
    return medianValue(upperHalf);
}
// 计算变异系数
double coefficientOfVariation(const vector<double>& data) {
    double mean = meanValue(data);
    double stdDev = stdDeviationValue(data);
    return (stdDev / mean) * 100.0; // 以百分比形式表示
}
// 计算偏度
double calculateSkewness(const vector<double>& data) {
    double mean = meanValue(data);
    double stdDev = stdDeviationValue(data);
    double skewness = 0.0;

    for (double x : data) {
        skewness += pow(x - mean, 3);
    }
    skewness = (skewness / data.size()) / pow(stdDev, 3);
    skewness *= (data.size() * (data.size() - 1)) / ((data.size() - 2) * (data.size() - 2));

    return skewness;
}
// 计算峰度
double calculateKurtosis(const vector<double>& data) {
    double mean = meanValue(data);
    double stdDev = stdDeviationValue(data);
    double kurtosis = 0.0;

    for (double x : data) {
        kurtosis += pow(x - mean, 4);
    }
    kurtosis = (kurtosis / data.size()) / pow(stdDev, 4);
    kurtosis -= 3;

    return kurtosis;
}


enum class SortOrder {
    Ascending,//升序
    Descending//降序
};
class Point//对于每一个点的数据
{
private:
    int m_SerialNum;
    string m_Name;
    double m_X;
    double m_Y;
    double m_Z;
public:
    // 构造函数
    Point() {};
    Point(int serialNum, string name, double x, double y, double z)
        : m_SerialNum(serialNum), m_Name(name), m_X(x), m_Y(y), m_Z(z) {}
    
    void setSerialNum(int serialNum)
    {
        m_SerialNum = serialNum;
    }
    void setX(double x)
    {
        m_X = x;
    }
    void setY(double y)
    {
        m_Y = y;
    }
    void setZ(double z)
    {
        m_Z = z;
    }
    void setName(string name)
    {
        m_Name = name;
    }
    void setAllInfo(int serialNum, string name, double x, double y, double z)
    {
        m_SerialNum = serialNum;
        m_Name = name;
        m_X = x;
        m_Y = y;
        m_Z = z;
    }

    int getSerialNum()const
    {
        return m_SerialNum;
    }
    double getX()const
    {
        return m_X;
    }
    double getY()const
    {
        return m_Y;
    }
    double getZ()const
    {
        return m_Z;
    }
    string getName()const
    {
        return m_Name;
    }

    double sumXYZ() const { return m_X + m_Y + m_Z; }
    double euclideanNorm() const { return sqrt(m_X * m_X + m_Y * m_Y + m_Z * m_Z); }
    void printPoint()const
    {
        cout << m_SerialNum << "\t" << m_Name << "\t" << m_X << "\t" << m_Y << "\t" << m_Z << "\n";
    }
};
class PointArr//所有点的数据
{
public:
    int m_Num;//当前所有点的个数
    Point* m_PointArr;//所有“点”的数组
    SortOrder m_SortOrder; // 排序方向

    void setSortOrder(SortOrder order) {
        m_SortOrder = order;
    }
    void push_back(const Point& point) {
        // 创建一个新的数组，其大小是原数组大小加1
        Point* newPointArr = new Point[m_Num + 1];

        // 如果原数组不为空，复制原数组内容到新数组
        if (m_Num > 0) {
            for (int i = 0; i < m_Num; ++i) {
                newPointArr[i] = m_PointArr[i];
            }
            // 删除原数组
            delete[] m_PointArr;
        }
        // 添加新的点
        newPointArr[m_Num] = point;
        // 更新数组指针和数量
        m_PointArr = newPointArr;
        m_Num++;
    }
    void sortByCriteria(int criteria) {
        auto compareFunc = [criteria, this](const Point& a, const Point& b) {
            bool result = false;
            switch (criteria) {
            case 1: // 按名称排序
                result = a.getName() < b.getName();
                break;
            case 2: // 按 X 排序
                result = a.getX() < b.getX();
                break;
            case 3: // 按 Y 排序
                result = a.getY() < b.getY();
                break;
            case 4: // 按 Z 排序
                result = a.getZ() < b.getZ();
                break;
            default:
                break;
            }
            return (m_SortOrder == SortOrder::Ascending) ? result : !result;
            };

        std::sort(m_PointArr, m_PointArr + m_Num, compareFunc);
    }
    void sortByMultipleCriteria(const std::vector<int>& priorityArray)
    {
        auto compareFunc = [priorityArray, this](const Point& a, const Point& b)//这个函数指出了sort函数的比较函数（即比较规则）
            /*这一行代码定义了一个 lambda 表达式，并将其赋值给 compareFunc 变量。下面是对这段代码的详细解释：
            auto：使用 auto 关键字可以让编译器自动推断 compareFunc 的类型，而不需要显式地指定。
            compareFunc：这是 lambda 表达式的名称，可以像普通函数一样调用它。
            [priorityArray, this]：这是 lambda 表达式的捕获列表。它指定了 lambda 表达式可以访问的外部变量。
            priorityArray：捕获 priorityArray 变量，使得在 lambda 表达式内部可以使用这个变量。
            this：捕获当前对象的指针，使得在 lambda 表达式内部可以访问当前对象的成员变量和成员函数。
            (const Point& a, const Point& b)：这是 lambda 表达式的参数列表。它定义了两个参数 a 和 b，类型都是 const Point&，表示对 Point 对象的常量引用。
            { ... }：这是 lambda 表达式的函数体。在这个大括号内，你可以编写任何有效的 C++ 代码，这些代码将在 lambda 表达式被调用时执行。
            总结：这段代码定义了一个 lambda 表达式 compareFunc，它可以访问外部变量 priorityArray 和当前对象的成员，并且接受两个 Point 对象作为参数。这个 lambda 表达式通常用于排序函数中，例如 std::sort，以定义排序的规则。*/
        {
            for (int criterion : priorityArray) 
                /*for (int criterion : priorityArray) { ... } 这一行代码是 C++11 引入的范围 for 循环（range-based for loop），用于遍历容器（如 std::vector、std::array、std::list 等）中的每一个元素。下面是对这段代码的详细解释：
                for：这是循环的关键字。
                (int criterion : priorityArray)：这是范围 for 循环的语法。
                int criterion：定义了一个名为 criterion 的变量，类型为 int。这个变量在每次循环迭代时都会被赋值为 priorityArray 中的一个元素。
                priorityArray：这是一个容器（在这个例子中是一个 std::vector<int>），循环将遍历这个容器中的每一个元素。
                { ... }：这是循环体。在大括号内，你可以编写任何有效的 C++ 代码，这些代码将在每次循环迭代时执行。
                总结来说，这段代码的作用是遍历 priorityArray 容器中的每一个元素，并将每个元素赋值给 criterion 变量。在循环体内，你可以使用 criterion 变量来执行相应的操作。
                例如，在给定的代码片段中，循环遍历 priorityArray 中的每一个整数，并根据这些整数来决定如何比较两个 Point 对象。具体来说，它会根据 criterion 的值（1、2 或 3）来决定是按名称、X 坐标还是 Y 坐标进行比较。
                */
            {
                bool result = false;
                switch (criterion)
                {
                case 1: // 按名称排序
                    if (a.getName() != b.getName()) result = a.getName() < b.getName();
                    break;
                case 2: // 按 X 排序
                    if (a.getX() != b.getX()) result = a.getX() < b.getX();
                    break;
                case 3: // 按 Y 排序
                    if (a.getY() != b.getY()) result = a.getY() < b.getY();
                    break;
                case 4: // 按 Z 排序
                    if (a.getZ() != b.getZ()) result = a.getZ() < b.getZ();
                    break;
                default:
                    break;
                }
                if (result || a.getName() != b.getName() || a.getX() != b.getX() || a.getY() != b.getY() || a.getZ() != b.getZ()) // 如果有任何标准不相等，则返回结果
                {
                    return (m_SortOrder == SortOrder::Ascending) ? result : !result;//根据升序或降序返回结果
                }
            }
            return false; // 如果所有标准都相等，则保持原始顺序
        };
        sort(this->m_PointArr, this->m_PointArr + m_Num, compareFunc);
    }
    void printPointArr()const
    {
        cout << m_Num << endl;
        for (int i = 0; i < m_Num; i++)
        {
            m_PointArr[i].printPoint();
        }
    }
};


//写文件函数
void writePointsToCSV(PointArr R, string strFileName) {
    ofstream file(strFileName, ios::out);
    if (!file.is_open()) {
        CString strFileOpenErr;
        strFileOpenErr.Format(_T("文件打开失败！"), 400, 300);
        //消息框中会出现一个停止标志图标，后面的是宽和高
        AfxMessageBox(strFileOpenErr, MB_HELP | MB_ICONERROR, 0);
        return;
    }
    file << to_string(R.m_Num) << endl;
    // 写入数据行
    int i;
    for (i = 0; i < R.m_Num - 1; ++i) {
        file << to_string(R.m_PointArr[i].getSerialNum()) + "," + R.m_PointArr[i].getName() + "," + to_string(R.m_PointArr[i].getX()) + "," + to_string(R.m_PointArr[i].getY()) + "," + to_string(R.m_PointArr[i].getZ()) << endl;
    }
    file << to_string(R.m_PointArr[i].getSerialNum()) + "," + R.m_PointArr[i].getName() + "," + to_string(R.m_PointArr[i].getX()) + "," + to_string(R.m_PointArr[i].getY()) + "," + to_string(R.m_PointArr[i].getZ());
    file.close();

    AfxMessageBox(_T("文件写入成功！"));
    // https://learn.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-messagebox
}


class CMFCApplication20240607cppTeamWorkDoc : public CDocument
{
protected: // 仅从序列化创建
	CMFCApplication20240607cppTeamWorkDoc() noexcept;
	DECLARE_DYNCREATE(CMFCApplication20240607cppTeamWorkDoc)

// 特性
public:
    PointArr arr;
    PointArr arrFind;//查找找到的点的数组
    PointArr arrFindInMySQL;//在MySQL数据库中查找找到的点的数组
    PointArr arrSQL;//用于对接数据库的数组
    PointArr arrAnalyze;//用于进行统计学分析的点的数组
    int arrMultiSortRuleCode;//多关键字排序的规则名称代号
    string arrMultiSortRuleName;//多关键字排序的规则名称名称
    Point closePoint;//最近点
// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CMFCApplication20240607cppTeamWorkDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
};
