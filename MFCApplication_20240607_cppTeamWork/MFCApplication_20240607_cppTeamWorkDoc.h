
// MFCApplication_20240607_cppTeamWorkDoc.h: CMFCApplication20240607cppTeamWorkDoc 类的接口
//


#pragma once
#include <iostream>
#include <string>
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

/**************************账户相关的全局变量**************************/
bool isOpenFile = false;
bool isSignIn = false;
bool isBuyVIP = false;
string isOpenFileMsg;
string isSignInMsg;
string isBuyVIPMsg;
bool isRememberPassword = false;
bool isRememberVIPKey = false;
string rememberUsername;
string rememberPassword;
string rememberVIPKey;
int nEncryptUsername;
int nEncryptPassword;
int nEncryptVIPKey;
string mainUsername;


//初始化的默认数据，可以用来实现对用户输入的数据的记忆功能
double defaultFindNumX = 0.0;
double defaultFindNumY = 0.0;
double defaultFindNumZ = 0.0;
string defaultPointName = "";


bool isAfxMessageBoxOn = true;

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
    void printPointArr()const
    {
        cout << m_Num << endl;
        for (int i = 0; i < m_Num; i++)
        {
            m_PointArr[i].printPoint();
        }
    }
};
//static bool isFindFail = false;


class CMFCApplication20240607cppTeamWorkDoc : public CDocument
{
protected: // 仅从序列化创建
	CMFCApplication20240607cppTeamWorkDoc() noexcept;
	DECLARE_DYNCREATE(CMFCApplication20240607cppTeamWorkDoc)

// 特性
public:
    PointArr arr;
    PointArr arrFind;//查找找到的点的数组
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
