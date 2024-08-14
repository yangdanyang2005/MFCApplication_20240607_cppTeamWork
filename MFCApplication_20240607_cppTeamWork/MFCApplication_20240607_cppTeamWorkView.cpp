
// MFCApplication_20240607_cppTeamWorkView.cpp: CMFCApplication20240607cppTeamWorkView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCApplication_20240607_cppTeamWork.h"
#endif

#include "MFCApplication_20240607_cppTeamWorkDoc.h"
#include "MFCApplication_20240607_cppTeamWorkView.h"
#include "FileReadDlg.h"
#include <fstream>
#include <vector>
#include <queue>
#include <cmath>
#include <map>
#include "AddPointDlg.h"
#include "InsertSortDlg.h"
#include "ShellSortzDig.h"
#include "BinInsertSortzDig.h"
#include "SelectSortDlg.h"
#include "heapSortDlg.h"
#include "bubbleSortDlg.h"
#include "quickSortDlg.h"
#include "radixSortDlg.h"
#include "mergeSortDig.h"
#include "deldlg.h"
#include "chaDlg.h"
#include "FindPointByName.h"
#include "FindPointByNumDlg.h"
#include "PointCalculateForTwoDlg.h"
#include "PointCalculateForThreeDlg.h"
#include "UserSetRGBDlg.h"
#include "SignInDlg.h"
#include "BuyVIPDlg.h"
#include"CTeamWorkDialog.h"
#include <ctime>
#include <Windows.h>


/* 视图更新标志flag说明：
* -2 白屏
* -1 文件当前数据显示
* 0  读取文件之后
* 1  按照x排序后
* 2  按照y排序后
* 3  按照z排序后
* 4  按照点名查找后
* 5  按照点的数据查找后
* 6  两点计算结果显示
* 7  三点计算结果显示
* 8  显示地形晕渲图
* 9  多关键字排序
*/
//P.S. gcp: gateway control point 控制点

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication20240607cppTeamWorkView

IMPLEMENT_DYNCREATE(CMFCApplication20240607cppTeamWorkView, CScrollView)

BEGIN_MESSAGE_MAP(CMFCApplication20240607cppTeamWorkView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_COMMAND(ID_32771, &CMFCApplication20240607cppTeamWorkView::OnReadFile)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_32772, &CMFCApplication20240607cppTeamWorkView::OnShowPoint)
	ON_COMMAND(ID_32773, &CMFCApplication20240607cppTeamWorkView::OnAdd)
	ON_COMMAND(ID_32783, &CMFCApplication20240607cppTeamWorkView::OnInsertSort)
	ON_COMMAND(ID_32784, &CMFCApplication20240607cppTeamWorkView::OnShellSortz)
	ON_COMMAND(ID_32792, &CMFCApplication20240607cppTeamWorkView::OnBinInsertSortz)
	ON_COMMAND(ID_32785, &CMFCApplication20240607cppTeamWorkView::OnSelectSort)
	ON_COMMAND(ID_32786, &CMFCApplication20240607cppTeamWorkView::OnheapSort)
	ON_COMMAND(ID_32787, &CMFCApplication20240607cppTeamWorkView::OnbubbleSort)
	ON_COMMAND(ID_32788, &CMFCApplication20240607cppTeamWorkView::OnquickSort)
	ON_COMMAND(ID_32781, &CMFCApplication20240607cppTeamWorkView::OnmergeSort)
	ON_COMMAND(ID_32782, &CMFCApplication20240607cppTeamWorkView::OnradixSort)
	ON_COMMAND(ID_32774, &CMFCApplication20240607cppTeamWorkView::Ondel)
	ON_COMMAND(ID_32775, &CMFCApplication20240607cppTeamWorkView::Oncha)
	ON_COMMAND(ID_32793, &CMFCApplication20240607cppTeamWorkView::OnFindPointByName)
	ON_COMMAND(ID_32794, &CMFCApplication20240607cppTeamWorkView::OnFindPointByNum)
	ON_COMMAND(ID_32790, &CMFCApplication20240607cppTeamWorkView::OnPointCalculateForTwo)
	ON_COMMAND(ID_32791, &CMFCApplication20240607cppTeamWorkView::OnPointCalculateForThree)
	ON_COMMAND(ID_32795, &CMFCApplication20240607cppTeamWorkView::OnPaintMap)
	ON_COMMAND(ID_32796, &CMFCApplication20240607cppTeamWorkView::OnSignIn)
	ON_COMMAND(ID_FILE_OPEN, &CMFCApplication20240607cppTeamWorkView::OnFileOpen)
	ON_COMMAND(ID_32797, &CMFCApplication20240607cppTeamWorkView::OnBuyVIPkey)
	ON_COMMAND(ID_32798, &CMFCApplication20240607cppTeamWorkView::OnTeamWork)
	ON_COMMAND(ID_32805, &CMFCApplication20240607cppTeamWorkView::OnMultiKeywordSort)
	ON_WM_TIMER()
	ON_COMMAND(ID_32806, &CMFCApplication20240607cppTeamWorkView::OnGoBackToHomePage)
END_MESSAGE_MAP()


/*****************************************所有需要用到的全局的函数往这里放*****************************************/

//-------------------------账号相关函数--------------------------
void checkAccount()
{
	if (isSignIn)
	{
		isSignInMsg = ("您已登录！欢迎您："+ mainUsername);
	}
	else
	{
		isSignInMsg = ("当前您还没有登录！请点击菜单栏中的【账户(I)】-【登录(L)】来登录！");
	}
	if(isBuyVIP)
	{
		isBuyVIPMsg = ("您已购买VIP！");
	}
	else
	{
		isBuyVIPMsg = ("当前您还没有购买VIP！欢迎点击菜单栏中的【账户(I)】-【获取高级功能(V)】购买VIP，享受更多功能！");
	}
	if (isOpenFile)
	{
		isOpenFileMsg = ("当前您已打开控制点坐标数据文件！");
	}
	else
	{
		isOpenFileMsg = ("当前您还没有打开控制点坐标数据文件！请点击菜单栏中的【文件(F)】-【打开(O)】/【打开(备用方式)】来打开数据文件！");
	}
}

//--------------------------文件相关函数--------------------------

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

	AfxMessageBox(_T("文件覆写成功！"));
}

bool checkOpenFile()
{
	if (!isSignIn)
	{
		AfxMessageBox(_T("您还没有登录，请先登录再来使用本软件！"));
		return false;
	}
	else if (!isOpenFile)
	{
		AfxMessageBox(_T("您还没有读取数据点文件，请先打开并读取数据点文件！"));
		return false;
	}
	else
	{
		return true;
	}
}

//--------------------------排序函数--------------------------

//直接插入排序
void InsertSort(int m, PointArr arr)
{
	flag = -2;
	int n = arr.m_Num;
	switch (m)
	{
	case 1:
	{
		int i, j; Point t;
		for (i = 1; i < n; i++)
		{
			if (arr.m_PointArr[i].getX() < arr.m_PointArr[i - 1].getX()) //反序时
			{
				t = arr.m_PointArr[i];
				j = i - 1;
				do //找R[i]的插入位置
				{
					arr.m_PointArr[j + 1] = arr.m_PointArr[j]; //记录后移
					j--;
				} while (j >= 0 && arr.m_PointArr[j].getX() > t.getX());
				arr.m_PointArr[j + 1] = t; //在j+1处插入R[i]
			}
		}
		flag = 1;
		break;
	}
	case 2:
	{
		int i, j; Point t;
		for (i = 1; i < n; i++)
		{
			if (arr.m_PointArr[i].getY() < arr.m_PointArr[i - 1].getY()) //反序时
			{
				t = arr.m_PointArr[i];
				j = i - 1;
				do //找R[i]的插入位置
				{
					arr.m_PointArr[j + 1] = arr.m_PointArr[j]; //记录后移
					j--;
				} while (j >= 0 && arr.m_PointArr[j].getY() > t.getY());
				arr.m_PointArr[j + 1] = t; //在j+1处插入R[i]
			}
		}
		flag = 2;
		break;
	}
	case 3:
	{
		int i, j; Point t;
		for (i = 1; i < n; i++)
		{
			if (arr.m_PointArr[i].getZ() < arr.m_PointArr[i - 1].getZ()) //反序时
			{
				t = arr.m_PointArr[i];
				j = i - 1;
				do //找R[i]的插入位置
				{
					arr.m_PointArr[j + 1] = arr.m_PointArr[j]; //记录后移
					j--;
				} while (j >= 0 && arr.m_PointArr[j].getZ() > t.getZ());
				arr.m_PointArr[j + 1] = t; //在j+1处插入R[i]
			}
		}
		flag = 3;
		break;
	}
	}
}
//希尔排序
void ShellSortz(int m, PointArr R)
{
	flag = -2;
	int i, j, d;
	Point t;
	int n = R.m_Num;
	switch (m) {
	case 1: {
		d = n / 2; //增量置初值
		while (d > 0)
		{
			for (i = d; i < n; i++)
			{ //对相隔d位置的元素组直接插入排序
				t = R.m_PointArr[i];
				j = i - d;
				while (j >= 0 && t.getX() < R.m_PointArr[j].getX())
				{
					R.m_PointArr[j + d] = R.m_PointArr[j];
					j = j - d;
				}
				R.m_PointArr[j + d] = t;
			}
			d = d / 2; //减小增量
		}
		flag = 1;
		break;
	}
	case 2:
	{
		d = n / 2; //增量置初值
		while (d > 0)
		{
			for (i = d; i < n; i++)
			{ //对相隔d位置的元素组直接插入排序
				t = R.m_PointArr[i];
				j = i - d;
				while (j >= 0 && t.getY() < R.m_PointArr[j].getY())
				{
					R.m_PointArr[j + d] = R.m_PointArr[j];
					j = j - d;
				}
				R.m_PointArr[j + d] = t;
			}
			d = d / 2; //减小增量
		}
		flag = 2;
		break;
	}
	case 3:
	{
		d = n / 2; //增量置初值
		while (d > 0)
		{
			for (i = d; i < n; i++)
			{ //对相隔d位置的元素组直接插入排序
				t = R.m_PointArr[i];
				j = i - d;
				while (j >= 0 && t.getZ() < R.m_PointArr[j].getZ())
				{
					R.m_PointArr[j + d] = R.m_PointArr[j];
					j = j - d;
				}
				R.m_PointArr[j + d] = t;
			}
			d = d / 2; //减小增量
		}
		flag = 3;
		break;
	}
	}
}
//折半插入排序
void BinInsertSortz(int m, PointArr R)
{
	int i, j, low, high, mid;
	Point t;
	switch (m) {
	case 1:
		for (i = 1; i < R.m_Num; i++) {
			if (R.m_PointArr[i].getX() < R.m_PointArr[i - 1].getX()) //反序时
			{
				t = R.m_PointArr[i]; //将R[i]保存到tmp中
				low = 0; high = i - 1;
				while (low <= high) //在R[low..high]中查找插入的位置
				{
					mid = (low + high) / 2; //取中间位置
					if (t.getX() < R.m_PointArr[mid].getX())
						high = mid - 1; //插入点在左半区
					else
						low = mid + 1; //插入点在右半区
				} //找位置high+1
				for (j = i - 1; j >= high + 1; j--) //记录后移
					R.m_PointArr[j + 1] = R.m_PointArr[j];
				R.m_PointArr[high + 1] = t; //插入t
			}
		}
		flag = 1;
		break;
	case 2:
		for (i = 1; i < R.m_Num; i++) {
			if (R.m_PointArr[i].getY() < R.m_PointArr[i - 1].getY()) //反序时
			{
				t = R.m_PointArr[i]; //将R[i]保存到tmp中
				low = 0; high = i - 1;
				while (low <= high) //在R[low..high]中查找插入的位置
				{
					mid = (low + high) / 2; //取中间位置
					if (t.getY() < R.m_PointArr[mid].getY())
						high = mid - 1; //插入点在左半区
					else
						low = mid + 1; //插入点在右半区
				} //找位置high+1
				for (j = i - 1; j >= high + 1; j--) //记录后移
					R.m_PointArr[j + 1] = R.m_PointArr[j];
				R.m_PointArr[high + 1] = t; //插入t
			}
		}
		flag = 2;
		break;
	case 3:
		for (i = 1; i < R.m_Num; i++) {
			if (R.m_PointArr[i].getZ() < R.m_PointArr[i - 1].getZ()) //反序时
			{
				t = R.m_PointArr[i]; //将R[i]保存到tmp中
				low = 0; high = i - 1;
				while (low <= high) //在R[low..high]中查找插入的位置
				{
					mid = (low + high) / 2; //取中间位置
					if (t.getZ() < R.m_PointArr[mid].getZ())
						high = mid - 1; //插入点在左半区
					else
						low = mid + 1; //插入点在右半区
				} //找位置high+1
				for (j = i - 1; j >= high + 1; j--) //记录后移
					R.m_PointArr[j + 1] = R.m_PointArr[j];
				R.m_PointArr[high + 1] = t; //插入t
			}
		}
		flag = 3;
		break;
	}



}
//简单选择排序
void SelectSort(int m, PointArr& arr)
{
	int n = arr.m_Num;
	switch (m) {
	case 1:
		for (int i = 0; i < n - 1; i++)
		{
			int min = i;
			for (int j = i + 1; j < n; j++)
			{
				if (arr.m_PointArr[j].getX() < arr.m_PointArr[min].getX())min = j;

			}
			if (min != i)swap(arr.m_PointArr[i], arr.m_PointArr[min]);
		}
		flag = 1;
		break;
	case 2:
		for (int i = 0; i < n - 1; i++)
		{
			int min = i;
			for (int j = i + 1; j < n; j++)
			{
				if (arr.m_PointArr[j].getY() < arr.m_PointArr[min].getY())min = j;

			}
			if (min != i)swap(arr.m_PointArr[i], arr.m_PointArr[min]);
		}
		flag = 2;
		break;
	case 3:
		for (int i = 0; i < n - 1; i++)
		{
			int min = i;
			for (int j = i + 1; j < n; j++)
			{
				if (arr.m_PointArr[j].getZ() < arr.m_PointArr[min].getZ())min = j;

			}
			if (min != i)swap(arr.m_PointArr[i], arr.m_PointArr[min]);
		}
		flag = 3;
		break;
	}
}
//调整堆，使其满足堆的性质
void heapifyX(PointArr& arr, int n, int i) {
	int largest = i; // 初始化最大值为根节点
	int left = 2 * i + 1; // 左子节点
	int right = 2 * i + 2; // 右子节点

	// 如果左子节点大于根节点，则更新最大值
	if (left < n && arr.m_PointArr[left].getX() > arr.m_PointArr[largest].getX())
		largest = left;

	// 如果右子节点大于当前最大值，则更新最大值
	if (right < n && arr.m_PointArr[right].getX() > arr.m_PointArr[largest].getX())
		largest = right;

	// 如果最大值不是根节点，则交换并继续调整
	if (largest != i) {
		swap(arr.m_PointArr[i], arr.m_PointArr[largest]);
		heapifyX(arr, n, largest);
	}
}
void heapifyY(PointArr& arr, int n, int i) {
	int largest = i; // 初始化最大值为根节点
	int left = 2 * i + 1; // 左子节点
	int right = 2 * i + 2; // 右子节点

	// 如果左子节点大于根节点，则更新最大值
	if (left < n && arr.m_PointArr[left].getY() > arr.m_PointArr[largest].getY())
		largest = left;

	// 如果右子节点大于当前最大值，则更新最大值
	if (right < n && arr.m_PointArr[right].getY() > arr.m_PointArr[largest].getY())
		largest = right;

	// 如果最大值不是根节点，则交换并继续调整
	if (largest != i) {
		swap(arr.m_PointArr[i], arr.m_PointArr[largest]);
		heapifyY(arr, n, largest);
	}
}
void heapifyZ(PointArr& arr, int n, int i) {
	int largest = i; // 初始化最大值为根节点
	int left = 2 * i + 1; // 左子节点
	int right = 2 * i + 2; // 右子节点

	// 如果左子节点大于根节点，则更新最大值
	if (left < n && arr.m_PointArr[left].getZ() > arr.m_PointArr[largest].getZ())
		largest = left;

	// 如果右子节点大于当前最大值，则更新最大值
	if (right < n && arr.m_PointArr[right].getZ() > arr.m_PointArr[largest].getZ())
		largest = right;

	// 如果最大值不是根节点，则交换并继续调整
	if (largest != i) {
		swap(arr.m_PointArr[i], arr.m_PointArr[largest]);
		heapifyZ(arr, n, largest);
	}
}
// 堆排序函数
void heapSort(int m, PointArr& arr) {
	int n = arr.m_Num;
	switch (m) {
	case 1:
		// 建立最大堆
		for (int i = n / 2 - 1; i >= 0; i--)
			heapifyX(arr, n, i);
		// 一个个交换元素并调整堆
		for (int i = n - 1; i >= 0; i--) {
			swap(arr.m_PointArr[0], arr.m_PointArr[i]); // 交换堆顶元素和当前未排序堆中的最后一个元素
			heapifyX(arr, i, 0); // 重新调整堆
		}
		flag = 1;
		break;
	case 2:
		// 建立最大堆
		for (int i = n / 2 - 1; i >= 0; i--)
			heapifyY(arr, n, i);
		// 一个个交换元素并调整堆
		for (int i = n - 1; i >= 0; i--) {
			swap(arr.m_PointArr[0], arr.m_PointArr[i]); // 交换堆顶元素和当前未排序堆中的最后一个元素
			heapifyY(arr, i, 0); // 重新调整堆
		}
		flag = 2;
		break;
	case 3:
		// 建立最大堆
		for (int i = n / 2 - 1; i >= 0; i--)
			heapifyZ(arr, n, i);
		// 一个个交换元素并调整堆
		for (int i = n - 1; i >= 0; i--) {
			swap(arr.m_PointArr[0], arr.m_PointArr[i]); // 交换堆顶元素和当前未排序堆中的最后一个元素
			heapifyZ(arr, i, 0); // 重新调整堆
		}
		flag = 3;
		break;
	}
}
// 冒泡排序
void bubbleSort(int m, PointArr R)
{
	int n = R.m_Num;
	Point tem;
	switch (m) {
	case 1:
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < n - i - 1; j++) {
				if (R.m_PointArr[j].getX() > R.m_PointArr[j + 1].getX()) {
					swap(R.m_PointArr[j], R.m_PointArr[j + 1]);
				}
			}
		}
		flag = 1;
		break;
	case 2:
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < n - i - 1; j++) {
				if (R.m_PointArr[j].getY() > R.m_PointArr[j + 1].getY()) {
					swap(R.m_PointArr[j], R.m_PointArr[j + 1]);
				}
			}
		}
		flag = 2;
		break;
	case 3:
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < n - i - 1; j++) {
				if (R.m_PointArr[j].getZ() > R.m_PointArr[j + 1].getZ()) {
					swap(R.m_PointArr[j], R.m_PointArr[j + 1]);
				}
			}
		}
		flag = 3;
		break;
	}
}
// 快速排序的分区函数
int partitionX(Point arr[], int low, int high) {
	// 选择最右侧的元素作为基准
	Point pivot = arr[high];
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++) {
		// 如果当前元素小于或等于基准
		if (arr[j].getX() <= pivot.getX()) {
			i++;
			// 交换 arr[i] 和 arr[j]
			swap(arr[i], arr[j]);
		}
	}
	// 交换 pivot 到它最终的位置
	swap(arr[i + 1], arr[high]);
	return (i + 1);
}
int partitionY(Point arr[], int low, int high) {
	// 选择最右侧的元素作为基准
	Point pivot = arr[high];
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++) {
		// 如果当前元素小于或等于基准
		if (arr[j].getY() <= pivot.getY()) {
			i++;
			// 交换 arr[i] 和 arr[j]
			swap(arr[i], arr[j]);
		}
	}
	// 交换 pivot 到它最终的位置
	swap(arr[i + 1], arr[high]);
	return (i + 1);
}
int partitionZ(Point arr[], int low, int high) {
	// 选择最右侧的元素作为基准
	Point pivot = arr[high];
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++) {
		// 如果当前元素小于或等于基准
		if (arr[j].getZ() <= pivot.getZ()) {
			i++;
			// 交换 arr[i] 和 arr[j]
			swap(arr[i], arr[j]);
		}
	}
	// 交换 pivot 到它最终的位置
	swap(arr[i + 1], arr[high]);
	return (i + 1);
}
//快速排序
void quickSort(Point R[], int low, int high, int m) {
	int n = high + 1;
	switch (m) {
	case 1:
		if (low < high) {
			// pi 是分区索引，arr[pi] 现在处在正确的位置
			int pi = partitionX(R, low, high);

			// 分别对左右分区进行排序
			quickSort(R, low, pi - 1, m);
			quickSort(R, pi + 1, high, m);
		}
		flag = 1;
		break;
	case 2:
		if (low < high) {
			// pi 是分区索引，arr[pi] 现在处在正确的位置
			int pi = partitionY(R, low, high);

			// 分别对左右分区进行排序
			quickSort(R, low, pi - 1, m);
			quickSort(R, pi + 1, high, m);
		}
		flag = 2;
		break;
	case 3:
		if (low < high) {
			// pi 是分区索引，arr[pi] 现在处在正确的位置
			int pi = partitionZ(R, low, high);

			// 分别对左右分区进行排序
			quickSort(R, low, pi - 1, m);
			quickSort(R, pi + 1, high, m);
		}
		flag = 3;
		break;
	}
}
// 辅助函数，用于合并两个已排序的数组
void mergeX(PointArr& arr, int l, int m, int r, int kk) {
	int n1 = m - l + 1;
	int n2 = r - m;

	// 创建临时数组
	vector<Point> L(n1), R(n2);

	// 复制数据到临时数组
	for (int i = 0; i < n1; i++) {
		L[i] = arr.m_PointArr[l + i];
	}
	for (int j = 0; j < n2; j++) {
		R[j] = arr.m_PointArr[m + 1 + j];
	}

	// 合并临时数组
	int i = 0, j = 0;
	int k = l;
	while (i < n1 && j < n2) {
		if (L[i].getX() <= R[j].getX()) {
			arr.m_PointArr[k] = L[i];
			i++;
		}
		else {
			arr.m_PointArr[k] = R[j];
			j++;
		}
		k++;
	}

	// 复制剩余的元素
	while (i < n1) {
		arr.m_PointArr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2) {
		arr.m_PointArr[k] = R[j];
		j++;
		k++;
	}
}
void mergeY(PointArr& arr, int l, int m, int r, int kk) {
	int n1 = m - l + 1;
	int n2 = r - m;

	// 创建临时数组
	vector<Point> L(n1), R(n2);

	// 复制数据到临时数组
	for (int i = 0; i < n1; i++) {
		L[i] = arr.m_PointArr[l + i];
	}
	for (int j = 0; j < n2; j++) {
		R[j] = arr.m_PointArr[m + 1 + j];
	}

	// 合并临时数组
	int i = 0, j = 0;
	int k = l;
	while (i < n1 && j < n2) {
		if (L[i].getY() <= R[j].getY()) {
			arr.m_PointArr[k] = L[i];
			i++;
		}
		else {
			arr.m_PointArr[k] = R[j];
			j++;
		}
		k++;
	}

	// 复制剩余的元素
	while (i < n1) {
		arr.m_PointArr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2) {
		arr.m_PointArr[k] = R[j];
		j++;
		k++;
	}
}
void mergeZ(PointArr& arr, int l, int m, int r, int kk) {
	int n1 = m - l + 1;
	int n2 = r - m;

	// 创建临时数组
	vector<Point> L(n1), R(n2);

	// 复制数据到临时数组
	for (int i = 0; i < n1; i++) {
		L[i] = arr.m_PointArr[l + i];
	}
	for (int j = 0; j < n2; j++) {
		R[j] = arr.m_PointArr[m + 1 + j];
	}

	// 合并临时数组
	int i = 0, j = 0;
	int k = l;
	while (i < n1 && j < n2) {
		if (L[i].getZ() <= R[j].getZ()) {
			arr.m_PointArr[k] = L[i];
			i++;
		}
		else {
			arr.m_PointArr[k] = R[j];
			j++;
		}
		k++;
	}

	// 复制剩余的元素
	while (i < n1) {
		arr.m_PointArr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2) {
		arr.m_PointArr[k] = R[j];
		j++;
		k++;
	}
}
// 归并排序函数
void mergeSort(PointArr& arr, int l, int r, int k) {
	switch (k) {
	case 1:
		if (l < r) {
			int m = l + (r - l) / 2;

			// 分治
			mergeSort(arr, l, m, k);
			mergeSort(arr, m + 1, r, k);

			// 合并
			mergeX(arr, l, m, r, k);
		}
		flag = 1;
		break;
	case 2:
		if (l < r) {
			int m = l + (r - l) / 2;

			// 分治
			mergeSort(arr, l, m, k);
			mergeSort(arr, m + 1, r, k);

			// 合并
			mergeY(arr, l, m, r, k);
		}
		flag = 2;
		break;
	case 3:
		if (l < r) {
			int m = l + (r - l) / 2;

			// 分治
			mergeSort(arr, l, m, k);
			mergeSort(arr, m + 1, r, k);

			// 合并
			mergeZ(arr, l, m, r, k);
		}
		flag = 3;
		break;
	}
}
// 辅助函数，用于基数排序
void radixSort(int m, PointArr& arr) {

	vector<queue<Point>> buckets(10);
	double max = -1;
	int maxDigits = 0;
	switch (m) {
	case 1:
		for (int i = 0; i < arr.m_Num; ++i) {
			if (arr.m_PointArr[i].getX() > max) {
				max = arr.m_PointArr[i].getX();
			}
		}
		while (max >= 1) {
			max /= 10;
			++maxDigits;
		}
		// 对每一位进行排序
		for (int digit = 1; digit <= maxDigits; ++digit) {
			// 将点分配到桶中
			for (int i = 0; i < arr.m_Num; ++i) {
				int bucketIndex = static_cast<int>(arr.m_PointArr[i].getX() / pow(10, digit - 1)) % 10;
				buckets[bucketIndex].push(arr.m_PointArr[i]);
			}

			// 从桶中收集点
			int index = 0;
			for (int i = 0; i < 10; ++i) {
				while (!buckets[i].empty()) {
					arr.m_PointArr[index++] = buckets[i].front();
					buckets[i].pop();
				}
			}
		}
		flag = 1;
		break;
	case 2:
		for (int i = 0; i < arr.m_Num; ++i) {
			if (arr.m_PointArr[i].getY() > max) {
				max = arr.m_PointArr[i].getY();
			}
		}
		while (max >= 1) {
			max /= 10;
			++maxDigits;
		}
		// 对每一位进行排序
		for (int digit = 1; digit <= maxDigits; ++digit) {
			// 将点分配到桶中
			for (int i = 0; i < arr.m_Num; ++i) {
				int bucketIndex = static_cast<int>(arr.m_PointArr[i].getY() / pow(10, digit - 1)) % 10;
				buckets[bucketIndex].push(arr.m_PointArr[i]);
			}

			// 从桶中收集点
			int index = 0;
			for (int i = 0; i < 10; ++i) {
				while (!buckets[i].empty()) {
					arr.m_PointArr[index++] = buckets[i].front();
					buckets[i].pop();
				}
			}
		}
		flag = 2;
		break;
	case 3:
		for (int i = 0; i < arr.m_Num; ++i) {
			if (arr.m_PointArr[i].getZ() > max) {
				max = arr.m_PointArr[i].getZ();
			}
		}
		while (max >= 1) {
			max /= 10;
			++maxDigits;
		}
		// 对每一位进行排序
		for (int digit = 1; digit <= maxDigits; ++digit) {
			// 将点分配到桶中
			for (int i = 0; i < arr.m_Num; ++i) {
				int bucketIndex = static_cast<int>(arr.m_PointArr[i].getZ() / pow(10, digit - 1)) % 10;
				buckets[bucketIndex].push(arr.m_PointArr[i]);
			}

			// 从桶中收集点
			int index = 0;
			for (int i = 0; i < 10; ++i) {
				while (!buckets[i].empty()) {
					arr.m_PointArr[index++] = buckets[i].front();
					buckets[i].pop();
				}
			}
		}
		flag = 3;
		break;
	}
}
//辅助函数，用于把arrMultiSortRuleCode转换为arrMultiSortRuleName
string intToString(int number) {
	std::string result;
	while (number > 0) {
		int digit = number % 10;
		switch (digit) {
		case 1:
			result = "x" + result;
			break;
		case 2:
			result = "y" + result;
			break;
		case 3:
			result = "z" + result;
			break;
		default:
			// 如果输入了除了1, 2, 3之外的数字，则返回错误信息
			return "Error: Input contains digits other than 1, 2, or 3.";
		}
		number /= 10;
		if (number > 0) {
			result = "、" + result; // 在数字之间添加中文顿号
		}
	}
	return result;
}
//--------------------------查找函数--------------------------

//按照点名进行查找的函数
void GetPt1(string ptName, PointArr arr, PointArr& arrFind)//一定要引用传入
{
	//输入点名进行查找
	int i = 0;
	int j = 0;
	int count = 0;
	int arrNum[1024];
	for (i = 0; i < arr.m_Num; i++)
	{
		if (ptName == arr.m_PointArr[i].getName())
		{
			count++;
			arrNum[j] = i; j++;
		}
	}
	arrFind.m_Num = count;
	if (count == 0)
	{
		AfxMessageBox(_T("没有查找到符合查找条件的点！"));
		return;
	}
	arrFind.m_PointArr = new Point[count];//一定要分配内存
	for (j = 0; j < count; j++)
	{
		arrFind.m_PointArr[j] = arr.m_PointArr[arrNum[j]];
	}
}
//按照点的数据进行排序的函数
void GetPt2(string ch, PointArr arr, PointArr& arrFind, double x, double y, double z)
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
			AfxMessageBox(_T("没有查找到符合查找条件的点！")); return;
		}
		arrFind.m_PointArr = new Point[t];//一定要分配内存
		for (j = 0; j < t; j++)
		{
			arrFind.m_PointArr[j] = arr.m_PointArr[arrNum[j]];
		}
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
			AfxMessageBox(_T("没有查找到符合查找条件的点！")); return;
		}
		arrFind.m_PointArr = new Point[t];//一定要分配内存
		for (j = 0; j < t; j++)
		{
			arrFind.m_PointArr[j] = arr.m_PointArr[arrNum[j]];
		}
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
			AfxMessageBox(_T("没有查找到符合查找条件的点！")); return;
		}
		arrFind.m_PointArr = new Point[t];//一定要分配内存
		for (j = 0; j < t; j++)
		{
			arrFind.m_PointArr[j] = arr.m_PointArr[arrNum[j]];
		}
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
			AfxMessageBox(_T("没有查找到符合查找条件的点！")); return;
		}
		arrFind.m_PointArr = new Point[t];//一定要分配内存
		for (j = 0; j < t; j++)
		{
			arrFind.m_PointArr[j] = arr.m_PointArr[arrNum[j]];
		}
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
			AfxMessageBox(_T("没有查找到符合查找条件的点！")); return;
		}
		arrFind.m_PointArr = new Point[t];//一定要分配内存
		for (j = 0; j < t; j++)
		{
			arrFind.m_PointArr[j] = arr.m_PointArr[arrNum[j]];
		}
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
			AfxMessageBox(_T("没有查找到符合查找条件的点！")); return;
		}
		arrFind.m_PointArr = new Point[t];//一定要分配内存
		for (j = 0; j < t; j++)
		{
			arrFind.m_PointArr[j] = arr.m_PointArr[arrNum[j]];
		}
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
			AfxMessageBox(_T("没有查找到符合查找条件的点！")); return;
		}
		arrFind.m_PointArr = new Point[t];//一定要分配内存
		for (j = 0; j < t; j++)
		{
			arrFind.m_PointArr[j] = arr.m_PointArr[arrNum[j]];
		}
	}
	else
	{
		AfxMessageBox(_T("查找条件选择异常！")); return;
	}
}
void GetDefalutPt(double x, double y, double z)
{
	defaultFindNumX = x;
	defaultFindNumY = y;
	defaultFindNumZ = z;
}
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
//角度换算函数,将弧度转换为度分秒，n作全局变量数组标志位
void radToDms(double rad, int n)
{
	if (rad < 0)
	{
		rad += 2 * PI; // 将结果转换为0到2π之间的角度
	}
	double degrees = rad * 180.0 / PI;
	degree[n] = int(degrees);
	minute[n] = int((degrees - degree[n]) * 60.0);
	second[n] = (double)(degrees - degree[n] - minute[n] / 60.0) * 3600.0;
}
//求高度角(含弧度制转换) n=0
void GetAltitude(Point a, Point b)
{
	double d = GetHorizontalDis(a, b);//水平距离
	double h = GetHeightDifference(a, b);//高差
	double funcAltitude = atan2(h, d);
	/*atan2是一个函数，在C语言里返回的是指方位角，
	C 语言中atan2的函数原型为 double atan2(double y, double x) ，
	返回以弧度表示的 y/x 的反正切。y 和 x 的值的符号决定了正确的象限。
	也可以理解为计算复数 x+yi 的辐角，计算时atan2 比 atan 稳定。*/
	if (funcAltitude > 2*PI)
	{
		altitude = funcAltitude - 2 * PI;
	}
	else if (funcAltitude > PI && funcAltitude <= 2 * PI)
	{
		altitude = 2 * PI - funcAltitude;
	}
	else if (funcAltitude < 0)
	{
		altitude += 2 * PI;
	}
	else
	{
		altitude = funcAltitude;
	}
	radToDms(altitude, 0);
}
//求天顶距(含弧度制转换) n=1
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
		zenithAngle = funcZenithAngle - 2 * PI;
	}
	else if (funcZenithAngle > PI && funcZenithAngle <= 2 * PI)
	{
		zenithAngle = 2 * PI - funcZenithAngle;
	}
	else if (funcZenithAngle < 0)
	{
		zenithAngle += 2 * PI;
	}
	else
	{
		zenithAngle = funcZenithAngle;
	}
	radToDms(zenithAngle, 1);
}

//--------------------------三点计算函数--------------------------

//求投影角 n=2
void GetProjectAng(Point vertex, Point a, Point b)
{
	double Side1 = GetHorizontalDis(vertex, a);
	double Side2 = GetHorizontalDis(vertex, b);
	double Side3 = GetHorizontalDis(a, b);
	projectAng = acos((pow(Side1, 2) + pow(Side2, 2) - pow(Side3, 2)) / (2 * Side1 * Side2));
	radToDms(projectAng, 2);
}
//求空间角 n=3
void GetAng(Point vertex, Point a, Point b)
{
	double Side1 = GetSlantDis(vertex, a);
	double Side2 = GetSlantDis(vertex, b);
	double Side3 = GetSlantDis(a, b);
	ang = acos((pow(Side1, 2) + pow(Side2, 2) - pow(Side3, 2)) / (2 * Side1 * Side2));
	radToDms(ang, 3);
}

//--------------------------画地形晕渲图函数--------------------------

// 用于存储划分到 50*50 方格中的点数据
map<pair<int, int>, vector<Point>> gridPoints;
// 将点数据划分到 50*50 方格中
void classifyPoints(PointArr& arr)
{
	// 遍历所有点数据
	for (int i = 0; i < arr.m_Num; ++i)
	{
		// 将点的 x 坐标四舍五入到最近的整数
		int m = round(arr.m_PointArr[i].getX());
		// 将点的 y 坐标四舍五入到最近的整数
		int n = round(arr.m_PointArr[i].getY());
		// 将点添加到对应的方格中
		gridPoints[{m, n}].push_back(arr.m_PointArr[i]);
	}
}
// 使用反距离加权法 (IDW) 计算 z 值（使用高斯函数计算权重）
double calculateIDW(int x, int y)
{
	double numerator = 0.0; // 分子部分初始化
	double denominator = 0.0; // 分母部分初始化
	double sigma = 2.0; // 高斯函数的标准差，值可以根据需要调整

	// 遍历每个方格及其包含的点
	for (const auto& gridPoint : gridPoints)
	{
		int m = gridPoint.first.first; // 方格的 x 坐标
		int n = gridPoint.first.second; // 方格的 y 坐标
		// 遍历方格中的所有点
		for (const Point& point : gridPoint.second)
		{
			// 计算当前点到目标点的距离
			double distance = sqrt(pow(x - m, 2) + pow(y - n, 2));
			// 如果距离为 0，直接返回当前点的 z 值
			if (distance == 0)
			{
				return point.getZ();
			}
			if (distance <= 10)//太远了的点应该舍去
			{
				// 使用高斯函数计算当前点的权重
				double weight = exp(-pow(distance, 2) / (2 * pow(sigma, 2)));
				// 更新分子部分
				numerator += weight * point.getZ();
				// 更新分母部分
				denominator += weight;
			}
		}
	}
	// 返回加权平均后的 z 值
	return numerator / denominator;
}
// 填充方格中的 z 值
void fillGridZValues(double grid[51][51]) {
	// 遍历每个方格
	for (int i = 0; i <= 50; ++i) {
		for (int j = 0; j <= 50; ++j) {
			// 如果当前方格中没有点数据，使用 IDW 计算 z 值
			if (gridPoints.find({ i, j }) == gridPoints.end()) {
				grid[i][j] = calculateIDW(i, j);
			}
			// 如果当前方格中有点数据，使用第一个点的 z 值
			else {
				grid[i][j] = gridPoints[{i, j}][0].getZ();
			}
		}
	}
}
// 计算 RGB 值
void calculateRGB(double grid[51][51], COLORREF colors[51][51]) {
	// 找出 grid 中的最小值
	double minZ = *min_element(&grid[0][0], &grid[50][50] + 1);
	// 找出 grid 中的最大值
	double maxZ = *max_element(&grid[0][0], &grid[50][50] + 1);
	// 调用对话框，允许用户设置较高、低高程处的RGB值
	UserSetRGBDlg dlg;
	dlg.DoModal();
	// 遍历 grid 的每一个元素
	for (int i = 0; i <= 50; ++i) {
		for (int j = 0; j <= 50; ++j) {
			// 将当前的 grid 值标准化为 [0, 1] 区间
			double normalizedZ = (grid[i][j] - minZ) / (maxZ - minZ);
			// 计算红色分量
			int red = static_cast<int>(normalizedZ * (dlg.setHighR - dlg.setLowR));
			// 计算绿色分量
			int green = static_cast<int>(normalizedZ * (dlg.setHighG - dlg.setLowG));
			// 计算蓝色分量
			int blue = static_cast<int>(normalizedZ * (dlg.setHighB - dlg.setLowB));
			// 将 RGB 颜色存储在 colors 数组中
			colors[i][j] = RGB(red, green, blue);
		}
	}
}
// 使用 MFC 绘制方格
void drawGrid(CDC* pDC, COLORREF colors[51][51]) {
	for (int i = 0; i <= 50; ++i) {
		for (int j = 0; j <= 50; ++j) {
			CBrush brush(colors[i][j]);
			pDC->FillRect(CRect(i * 10, j * 10, (i + 1) * 10, (j + 1) * 10), &brush);
		}
	}
}


// CMFCApplication20240607cppTeamWorkView 构造/析构
CMFCApplication20240607cppTeamWorkView::CMFCApplication20240607cppTeamWorkView() noexcept
{
	// TODO: 在此处添加构造代码
	checkAccount();//检查账户信息
	//SetTimer(1, 1000, NULL);// 设置定时器，每隔1000毫秒（1秒）更新一次时间
	//SYSTEMTIME stm;
	//GetLocalTime(&stm);

	ifstream inFile("data/user_remember_find_point_name.dat", ios::in | ios::binary);
	getline(inFile, defaultPointName);
	inFile.close();

	ifstream inFile2("data/user_remember_find_point_num.dat", ios::in | ios::binary);
	inFile2 >> defaultFindNumX >> defaultFindNumY >> defaultFindNumZ;
	inFile2.close();

	ifstream inFile3("data/user_remember_file_path.dat", ios::in | ios::binary);
	string filePathStr = filePath;
	getline(inFile3, filePathStr);
	inFile3.close();
}
CMFCApplication20240607cppTeamWorkView::~CMFCApplication20240607cppTeamWorkView()
{
	//KillTimer(1);// 销毁定时器

	//保存用户输入的数据文件
	ofstream outFile("data/user_remember_find_point_num.dat", ios::out | ios::trunc | ios::binary);
	if (outFile.is_open())
	{
		outFile << defaultFindNumX << endl << defaultFindNumY << endl << defaultFindNumZ << endl;
		outFile.close();
	}
	ofstream outFile2("data/user_remember_find_point_name.dat", ios::out | ios::trunc | ios::binary);
	if (outFile2.is_open())
	{
		outFile2 << defaultPointName;
		outFile2.close();
	}
	ofstream outFile3("data/user_remember_file_path.dat", ios::out | ios::trunc | ios::binary);
	if (outFile3.is_open())
	{
		outFile3 << filePath;
		outFile3.close();
	}
}
BOOL CMFCApplication20240607cppTeamWorkView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	//cs.cx = 1000;//界面宽度
	//cs.cy = 1000;//界面高度
	//cs.style = WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;//窗口样式
	//cs.lpszName = _T("大一下 遥感应用软件设计 大作业");//窗口标题
	//cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW, ::LoadCursor(nullptr, IDC_ARROW), HBRUSH(COLOR_WINDOW + 1), nullptr);//窗口类名
	return CScrollView::PreCreateWindow(cs);
}

// CMFCApplication20240607cppTeamWorkView 绘图：在CMFCApplication20240607cppTeamWork文档上画图以显示各种结果
void CMFCApplication20240607cppTeamWorkView::OnDraw(CDC* pDC)
{
	CMFCApplication20240607cppTeamWorkDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	switch (flag)
	{

	//-2：空屏
	case -2:
	{
		CRect rect;             //创建一个矩形
		GetClientRect(rect);    //使矩形与客户窗口大小一致
		CBrush BkBrush;         //新建画刷
		BkBrush.CreateSolidBrush(RGB(255, 255, 255));  //设置画刷颜色
		pDC->FillRect(rect, &BkBrush);   //填充矩形
		break;
	}

	//-1：欢迎页
	case -1:
	{
		SetTimer(1, 1000, NULL);// 设置定时器，每隔1000毫秒（1秒）更新一次时间

		checkAccount();//检查账户信息

		CString str = _T("大一下 遥感应用软件设计 大作业");
		pDC->TextOut(420, 10, str);
		CString str1 = _T("指导老师：李爽");
		pDC->TextOut(500, 50, str1);
		CString str2 = _T("小组名单：   组长：杨丹阳   组员：梁宇康  易星辰  赵启睿");
		pDC->TextOut(320, 90, str2);

		CString namecarrier1(isSignInMsg.c_str());
		pDC->TextOut(100, 150, namecarrier1);
		CString namecarrier2(isBuyVIPMsg.c_str());
		pDC->TextOut(100, 190, namecarrier2);
		CString namecarrier3(isOpenFileMsg.c_str());
		pDC->TextOut(100, 230, namecarrier3);

		// 绘制欢迎页图片
		CImage image;
		image.Load(L"images/SouthMapHelloPicture.png");
		image.Draw(pDC->GetSafeHdc(), CRect(50, 360, 50 + 1080, 360 + 400));//1080*400像素的图
		/*CRect类依次包含以下四个成员变量：
		int left：矩形区域左上角的 x 坐标。
		int top：矩形区域左上角的 y 坐标。
		int right：矩形区域右下角的 x 坐标。
		int bottom：矩形区域右下角的 y 坐标。*/
		image.Destroy();

		// 绘制时钟与日期
		// 设置文本颜色和字体
		pDC->SetTextColor(RGB(0, 0, 255)); // 蓝色文本
		CFont font;
		font.CreatePointFont(100, _T("宋体")); // 创建字体
		CFont* pOldFont = pDC->SelectObject(&font);
		// 绘制时间字符串
		pDC->TextOut(340, 290, m_strTime);
		// 恢复旧字体
		pDC->SelectObject(pOldFont);

		break;
	}

	//0：文件数据显示
	case 0:
	{
		CString str = _T("当前所有控制点数据的列表为：");
		pDC->TextOut(10, 10, str);
		CString strpoint;
		for (int i = 0; i < pDoc->arr.m_Num; i++)
		{
			CString namecarrier((pDoc->arr.m_PointArr[i].getName()).c_str());
			strpoint.Format(_T("%d  %s  %lf  %lf  %lf"),
				pDoc->arr.m_PointArr[i].getSerialNum(),
				namecarrier,
				pDoc->arr.m_PointArr[i].getX(),
				pDoc->arr.m_PointArr[i].getY(),
				pDoc->arr.m_PointArr[i].getZ());
			pDC->TextOut(150, 50 + 40 * i, strpoint);
		}
		break;
	}

	//1-3：按照x、y或z排序后
	case 1:
	{
		CString str = _T("按照x坐标控制点数据的列表为：");
		pDC->TextOut(10, 10, str);
		CString strpoint;
		for (int i = 0; i < pDoc->arr.m_Num; i++)
		{
			CString namecarrier((pDoc->arr.m_PointArr[i].getName()).c_str());
			strpoint.Format(_T("%d  %s  %lf  %lf  %lf"),
				pDoc->arr.m_PointArr[i].getSerialNum(),
				namecarrier,
				pDoc->arr.m_PointArr[i].getX(),
				pDoc->arr.m_PointArr[i].getY(),
				pDoc->arr.m_PointArr[i].getZ());
			pDC->TextOut(150, 50 + 40 * i, strpoint);
		}
		break;
	}
	case 2:
	{
		CString str = _T("按照y坐标控制点数据的列表为：");
		pDC->TextOut(10, 10, str);
		CString strpoint;
		for (int i = 0; i < pDoc->arr.m_Num; i++)
		{
			CString namecarrier((pDoc->arr.m_PointArr[i].getName()).c_str());
			strpoint.Format(_T("%d  %s  %lf  %lf  %lf"),
				pDoc->arr.m_PointArr[i].getSerialNum(),
				namecarrier,
				pDoc->arr.m_PointArr[i].getX(),
				pDoc->arr.m_PointArr[i].getY(),
				pDoc->arr.m_PointArr[i].getZ());
			pDC->TextOut(150, 50 + 40 * i, strpoint);
		}
		break;
	}
	case 3:
	{
		CString str = _T("按照z坐标控制点数据的列表为：");
		pDC->TextOut(10, 10, str);
		CString strpoint;
		for (int i = 0; i < pDoc->arr.m_Num; i++)
		{
			CString namecarrier((pDoc->arr.m_PointArr[i].getName()).c_str());
			strpoint.Format(_T("%d  %s  %lf  %lf  %lf"),
				pDoc->arr.m_PointArr[i].getSerialNum(),
				namecarrier,
				pDoc->arr.m_PointArr[i].getX(),
				pDoc->arr.m_PointArr[i].getY(),
				pDoc->arr.m_PointArr[i].getZ());
			pDC->TextOut(150, 50 + 40 * i, strpoint);
		}
		break;
	}

	//4-5：显示查找结果
	case 4:
	{
		CString str = _T("按照点名查找到的所有控制点数据的列表为：");
		pDC->TextOut(10, 10, str);
		CString strpoint;
		for (int i = 0; i < pDoc->arrFind.m_Num; i++)
		{
			CString namecarrier((pDoc->arrFind.m_PointArr[i].getName()).c_str());
			strpoint.Format(_T("%d  %s  %lf  %lf  %lf"),
				pDoc->arrFind.m_PointArr[i].getSerialNum(),
				namecarrier,
				pDoc->arrFind.m_PointArr[i].getX(),
				pDoc->arrFind.m_PointArr[i].getY(),
				pDoc->arrFind.m_PointArr[i].getZ());
			pDC->TextOut(150, 50 + 40 * i, strpoint);
		}
		break;
	}
	case 5:
	{
		CString str = _T("按照点的坐标值查找到的所有控制点数据的列表为：");
		pDC->TextOut(10, 10, str);
		CString strpoint;
		for (int i = 0; i < pDoc->arrFind.m_Num; i++)
		{
			CString namecarrier((pDoc->arrFind.m_PointArr[i].getName()).c_str());
			strpoint.Format(_T("%d  %s  %lf  %lf  %lf"),
				pDoc->arrFind.m_PointArr[i].getSerialNum(),
				namecarrier,
				pDoc->arrFind.m_PointArr[i].getX(),
				pDoc->arrFind.m_PointArr[i].getY(),
				pDoc->arrFind.m_PointArr[i].getZ());
			pDC->TextOut(150, 50 + 40 * i, strpoint);
		}
		break;
	}

	//6-7：测绘工具计算结果显示
	case 6:
	{
		CString str = _T("查找到的最近点的数据：");
		pDC->TextOut(10, 10, str);

		CString str1 = _T("点的序号    点名        x坐标        y坐标        z坐标");
		pDC->TextOut(150, 50, str1);

		CString strpoint;
		CString namecarrier((pDoc->closePoint.getName()).c_str());

		strpoint.Format(_T("      %d     %s    %lf     %lf     %lf"),
			pDoc->closePoint.getSerialNum(),
			namecarrier,
			pDoc->closePoint.getX(),
			pDoc->closePoint.getY(),
			pDoc->closePoint.getZ());
		pDC->TextOut(150, 90, strpoint);

		CString str2 = _T("输入点与其最近点的相关数据：");
		pDC->TextOut(150, 200, str2);


		CString str3 = _T("倾斜距离  水平距离     高差");
		pDC->TextOut(200, 240, str3);
		CString strNum1;
		strNum1.Format(_T(" %lf    %lf    %lf"), minSlantDis, horizontalDis, heightDifference);
		pDC->TextOut(200, 280, strNum1);

		CString str4 = _T("高度角： 弧度制                  角度制");
		pDC->TextOut(200, 340, str4);
		CString strNum2;
		strNum2.Format(_T("                 %lf      %d °%d ′ %lf″"), altitude, degree[0], minute[0], second[0]);
		pDC->TextOut(200, 380, strNum2);

		CString str5 = _T("天顶距：弧度制                  角度制");
		pDC->TextOut(200, 440, str5);
		CString strNum3;
		strNum3.Format(_T("                 %lf      %d °%d ′ %lf″"), zenithAngle, degree[1], minute[1], second[1]);
		pDC->TextOut(200, 480, strNum3);

		break;
	}
	case 7:
	{
		CString str = _T("所构成的水平投影角： 弧度制                        角度制");
		pDC->TextOut(10, 10, str);
		CString strNum;
		strNum.Format(_T("                                        %lf      %d °%d ′ %lf″"), projectAng, degree[2], minute[2], second[2]);
		pDC->TextOut(40, 50, strNum);

		CString str1 = _T("所构成的空间角：弧度制                        角度制");
		pDC->TextOut(00, 100, str1);
		CString strNum1;
		strNum1.Format(_T("                            %lf      %d °%d ′ %lf″"), ang, degree[3], minute[3], second[3]);
		pDC->TextOut(40, 140, strNum1);

		break;
	}

	//8：绘制地形晕渲图
	case 8:
	{
		KillTimer(1);// 销毁定时器
		drawGrid(pDC, colors);
		break;
	}

	//9：绘制多关键字排序结果
	case 9:
	{
		CString str9;
		CString namecarrier9(pDoc->arrMultiSortRuleName.c_str());
		str9.Format(_T("按照多关键字%s排序后的控制点数据的列表为："), namecarrier9);

		pDC->TextOut(10, 10, str9);
		CString strpoint;
		for (int i = 0; i < pDoc->arr.m_Num; i++)
		{
			CString namecarrier((pDoc->arr.m_PointArr[i].getName()).c_str());
			strpoint.Format(_T("%d  %s  %lf  %lf  %lf"),
				pDoc->arr.m_PointArr[i].getSerialNum(),
				namecarrier,
				pDoc->arr.m_PointArr[i].getX(),
				pDoc->arr.m_PointArr[i].getY(),
				pDoc->arr.m_PointArr[i].getZ());
			pDC->TextOut(150, 50 + 40 * i, strpoint);
		}
		break;
	}
	}
}
void CMFCApplication20240607cppTeamWorkView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	SetTimer(1, 1000, NULL);// 设置定时器，每隔1000毫秒（1秒）更新一次时间
	CSize sizeTotal;

	// TODO: 计算此视图的合计大小
	sizeTotal.cx = 1000;
	sizeTotal.cy = 10000;//指定画布大小

	// 获取视图的客户区大小
	CRect clientRect;
	GetClientRect(&clientRect);
	// 更新文档大小
	CSize docSize(clientRect.Width(), clientRect.Height());
	SetScrollSizes(MM_TEXT, docSize);

	SetScrollSizes(MM_TEXT, sizeTotal);//使用滚动条
}
void CMFCApplication20240607cppTeamWorkView::UpdateSystemTime()
{
	// 获取当前系统时间
	m_timeSys = CTime::GetCurrentTime();
	// 格式化时间
	m_strTime = m_timeSys.Format(_T("日期：%Y-%m-%d    时间：%H:%M:%S"));
	// 重新绘制视图以显示时间
	Invalidate();
	UpdateWindow();
}
void CMFCApplication20240607cppTeamWorkView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 1)
	{
		UpdateSystemTime();
	}
	CView::OnTimer(nIDEvent);
}

// CMFCApplication20240607cppTeamWorkView 打印
BOOL CMFCApplication20240607cppTeamWorkView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}
void CMFCApplication20240607cppTeamWorkView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}
void CMFCApplication20240607cppTeamWorkView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMFCApplication20240607cppTeamWorkView 诊断
#ifdef _DEBUG
void CMFCApplication20240607cppTeamWorkView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMFCApplication20240607cppTeamWorkView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMFCApplication20240607cppTeamWorkDoc* CMFCApplication20240607cppTeamWorkView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication20240607cppTeamWorkDoc)));
	return (CMFCApplication20240607cppTeamWorkDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication20240607cppTeamWorkView 消息处理程序

//读文件
void CMFCApplication20240607cppTeamWorkView::OnReadFile()
{
	// TODO: 在此添加命令处理程序代码
	if (!isSignIn)
	{
		AfxMessageBox(_T("您还没有登录，请先登录再来使用本软件！"));
		return;
	}
	flag = -2;

	FileReadDlg dlg;
	dlg.DoModal();

	/****************************读取文件数据****************************/
//通过对话框获取文件路径
	CMFCApplication20240607cppTeamWorkDoc* pDoc = GetDocument();//把数据存在Doc的类里面

	FILE* fp;
	int length = dlg.filePath.GetLength();
	//char* filePath = new char[length + 1]; // 需要多分配一个字节用来存放字符串结束符'\0'
	if (dlg.filePath == "")
	{
		filePath = "D://gcp.csv";
	}
	else
	{
		strcpy(filePath, CT2A(dlg.filePath.GetBuffer()));
	}

	// 检查文件是否能够成功打开
	ifstream file(filePath);
	if (!file.is_open())
	{
		CString strFileOpenErr;
		strFileOpenErr.Format(_T("文件打开失败！"), 400, 300);
		//消息框中会出现一个停止标志图标，后面的是宽和高
		AfxMessageBox(strFileOpenErr, MB_HELP | MB_ICONERROR, 0);
		return;
	}
	file.close(); // 检验完成后关闭文件

	//打开文件准备获取数据
	fp = fopen(filePath, "r");
	if (!fp)
	{
		CString strFileOpenErr;
		strFileOpenErr.Format(_T("文件打开失败！"), 400, 300);
		//消息框中会出现一个停止标志图标，后面的是宽和高
		AfxMessageBox(strFileOpenErr, MB_HELP | MB_ICONERROR, 0);
		return;
	}
	char ch = '\0';
	double f = 0.0;
	int d = 0;
	int i = 0;
	fscanf(fp, "%d\n", &d);
	pDoc->arr.m_Num = d;
	Point* point = new Point[pDoc->arr.m_Num];
	for (i = 0; !feof(fp); i++)
	{
		fscanf(fp, "%d,", &d);
		point[i].setSerialNum(d);//点的序号存入数组    
		string strName;
		for (ch = fgetc(fp); ch != ','; ch = fgetc(fp))
		{
			strName += ch;//获取点的名称
		}
		point[i].setName(strName);
		fscanf(fp, "%lf,", &f);//从文件指针fp指向的文件中，读取double型的坐标数据，储存在double型的变量f中。注意这里有一个“,”
		point[i].setX(f);//x坐标存入数组
		fscanf(fp, "%lf,", &f);
		point[i].setY(f);//y坐标存入数组    
		fscanf(fp, "%lf,", &f);
		point[i].setZ(f);//z坐标存入数组
		fgetc(fp);//读走每一行最后的换行符
	}
	pDoc->arr.m_PointArr = point;
	int finalSerialNum = pDoc->arr.m_PointArr[pDoc->arr.m_Num - 1].getSerialNum();
	flag = 0;
	fclose(fp);
	Invalidate();//至此，文件中的数据已经被读取到Doc类的arr中，再去OnDraw处输出显示
	MessageBox(_T("文件读取成功！"), _T("文件读取成功提示对话框"));
	isOpenFile = true;
}


void CMFCApplication20240607cppTeamWorkView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPoint curPt = point + GetScrollPosition();

	CScrollView::OnMouseMove(nFlags, point);
}


void CMFCApplication20240607cppTeamWorkView::OnShowPoint()
{
	// TODO: 在此添加命令处理程序代码
	if (!checkOpenFile())
	{
		return;
	}
	flag = -2;
	flag = 0;
	Invalidate();
}


void CMFCApplication20240607cppTeamWorkView::OnAdd()
{
	// TODO: 在此添加命令处理程序代码
	if (!checkOpenFile())
	{
		return;
	}
	flag = -2;

	CMFCApplication20240607cppTeamWorkDoc* pDoc = GetDocument();
	AddPointDlg dlg;
	dlg.DoModal();

	int k = pDoc->arr.m_Num;
	pDoc->arr.m_Num += 1;
	Point* point = new Point[pDoc->arr.m_Num];
	string name;
	double x, y, z;
	name = CT2A(dlg.name.GetBuffer());
	x = dlg.x;
	y = dlg.y;
	z = dlg.z;

	for (int i = 0; i < k; i++) {
		point[i].setSerialNum(i + 1);
		point[i].setName(pDoc->arr.m_PointArr[i].getName());
		point[i].setX(pDoc->arr.m_PointArr[i].getX());
		point[i].setY(pDoc->arr.m_PointArr[i].getY());
		point[i].setZ(pDoc->arr.m_PointArr[i].getZ());
	}
	point[k].setSerialNum(k + 1);
	point[k].setName(name);
	point[k].setX(x);
	point[k].setY(y);
	point[k].setZ(z);
	pDoc->arr.m_PointArr = point;
	pDoc->arr.printPointArr();
	writePointsToCSV(pDoc->arr, filePath);
	flag = 0;
	Invalidate();
}


void CMFCApplication20240607cppTeamWorkView::OnInsertSort()
{
	// TODO: 在此添加命令处理程序代码
	if (!checkOpenFile())
	{
		return;
	}
	flag = -2;
	CMFCApplication20240607cppTeamWorkDoc* pDoc = GetDocument();
	InsertSortDlg dlg;
	dlg.DoModal();
	if (dlg.m_nChooseSort == 0)
	{
		AfxMessageBox(_T("请先选择按照哪一个变量来进行排序！"));
	}
	else if (dlg.m_nChooseSort == 1)
	{
		InsertSort(1, pDoc->arr);
	}
	else if (dlg.m_nChooseSort == 2)
	{
		InsertSort(2, pDoc->arr);
	}
	else if (dlg.m_nChooseSort == 3)
	{
		InsertSort(3, pDoc->arr);
	}
	Invalidate();
}


void CMFCApplication20240607cppTeamWorkView::OnShellSortz()
{
	// TODO: 在此添加命令处理程序代码
	if (!checkOpenFile())
	{
		return;
	}
	flag = -2;
	CMFCApplication20240607cppTeamWorkDoc* pDoc = GetDocument();
	ShellSortzDig dlg;
	dlg.DoModal();
	if (dlg.m_nChooseSort == 0)
	{
		AfxMessageBox(_T("请先选择按照哪一个变量来进行排序！"));
	}
	else if (dlg.m_nChooseSort == 1)
	{
		ShellSortz(1, pDoc->arr);
	}
	else if (dlg.m_nChooseSort == 2)
	{
		ShellSortz(2, pDoc->arr);
	}
	else if (dlg.m_nChooseSort == 3)
	{
		ShellSortz(3, pDoc->arr);
	}
	Invalidate();
}


void CMFCApplication20240607cppTeamWorkView::OnBinInsertSortz()
{
	// TODO: 在此添加命令处理程序代码
	if (!checkOpenFile())
	{
		return;
	}
	flag = -2;
	CMFCApplication20240607cppTeamWorkDoc* pDoc = GetDocument();
	BinInsertSortzDig dlg;
	dlg.DoModal();
	if (dlg.m_nChooseSort == 0)
	{
		AfxMessageBox(_T("请先选择按照哪一个变量来进行排序！"));
	}
	else if (dlg.m_nChooseSort == 1)
	{
		BinInsertSortz(1, pDoc->arr);
	}
	else if (dlg.m_nChooseSort == 2)
	{
		BinInsertSortz(2, pDoc->arr);
	}
	else if (dlg.m_nChooseSort == 3)
	{
		BinInsertSortz(3, pDoc->arr);
	}
	Invalidate();
}


void CMFCApplication20240607cppTeamWorkView::OnSelectSort()
{
	// TODO: 在此添加命令处理程序代码
	if (!checkOpenFile())
	{
		return;
	}
	flag = -2;
	CMFCApplication20240607cppTeamWorkDoc* pDoc = GetDocument();
	SelectSortDlg dlg;
	dlg.DoModal();
	if (dlg.m_nChooseSort == 0)
	{
		AfxMessageBox(_T("请先选择按照哪一个变量来进行排序！"));
	}
	else if (dlg.m_nChooseSort == 1)
	{
		SelectSort(1, pDoc->arr);
	}
	else if (dlg.m_nChooseSort == 2)
	{
		SelectSort(2, pDoc->arr);
	}
	else if (dlg.m_nChooseSort == 3)
	{
		SelectSort(3, pDoc->arr);
	}
	Invalidate();
}


void CMFCApplication20240607cppTeamWorkView::OnheapSort()
{
	// TODO: 在此添加命令处理程序代码
	if (!checkOpenFile())
	{
		return;
	}
	flag = -2;
	CMFCApplication20240607cppTeamWorkDoc* pDoc = GetDocument();
	heapSortDlg dlg;
	dlg.DoModal();
	if (dlg.m_nChooseSort == 0)
	{
		AfxMessageBox(_T("请先选择按照哪一个变量来进行排序！"));
	}
	else if (dlg.m_nChooseSort == 1)
	{
		heapSort(1, pDoc->arr);
	}
	else if (dlg.m_nChooseSort == 2)
	{
		heapSort(2, pDoc->arr);
	}
	else if (dlg.m_nChooseSort == 3)
	{
		heapSort(3, pDoc->arr);
	}
	Invalidate();
}


void CMFCApplication20240607cppTeamWorkView::OnbubbleSort()
{
	// TODO: 在此添加命令处理程序代码
	if (!checkOpenFile())
	{
		return;
	}
	flag = -2;
	CMFCApplication20240607cppTeamWorkDoc* pDoc = GetDocument();
	bubbleSortDlg dlg;
	dlg.DoModal();
	if (dlg.m_nChooseSort == 0)
	{
		AfxMessageBox(_T("请先选择按照哪一个变量来进行排序！"));
	}
	else if (dlg.m_nChooseSort == 1)
	{
		bubbleSort(1, pDoc->arr);
	}
	else if (dlg.m_nChooseSort == 2)
	{
		bubbleSort(2, pDoc->arr);
	}
	else if (dlg.m_nChooseSort == 3)
	{
		bubbleSort(3, pDoc->arr);
	}
	Invalidate();
}


void CMFCApplication20240607cppTeamWorkView::OnquickSort()
{
	// TODO: 在此添加命令处理程序代码
	if (!checkOpenFile())
	{
		return;
	}
	flag = -2;
	CMFCApplication20240607cppTeamWorkDoc* pDoc = GetDocument();
	quickSortDlg dlg;
	dlg.DoModal();
	if (dlg.m_nChooseSort == 0)
	{
		AfxMessageBox(_T("请先选择按照哪一个变量来进行排序！"));
	}
	else if (dlg.m_nChooseSort == 1)
	{
		quickSort(pDoc->arr.m_PointArr, 0, pDoc->arr.m_Num - 1, 1);
	}
	else if (dlg.m_nChooseSort == 2)
	{
		quickSort(pDoc->arr.m_PointArr, 0, pDoc->arr.m_Num - 1, 2);
	}
	else if (dlg.m_nChooseSort == 3)
	{
		quickSort(pDoc->arr.m_PointArr, 0, pDoc->arr.m_Num - 1, 3);
	}
	Invalidate();
}


void CMFCApplication20240607cppTeamWorkView::OnmergeSort()
{
	// TODO: 在此添加命令处理程序代码
	if (!checkOpenFile())
	{
		return;
	}
	flag = -2;
	CMFCApplication20240607cppTeamWorkDoc* pDoc = GetDocument();
	mergeSortDig dlg;
	dlg.DoModal();
	if (dlg.m_nChooseSort == 0)
	{
		AfxMessageBox(_T("请先选择按照哪一个变量来进行排序！"));
	}
	else if (dlg.m_nChooseSort == 1)
	{
		mergeSort(pDoc->arr, 0, pDoc->arr.m_Num - 1, 1);
	}
	else if (dlg.m_nChooseSort == 2)
	{
		mergeSort(pDoc->arr, 0, pDoc->arr.m_Num - 1, 2);
	}
	else if (dlg.m_nChooseSort == 3)
	{
		mergeSort(pDoc->arr, 0, pDoc->arr.m_Num - 1, 3);
	}
	Invalidate();
}


void CMFCApplication20240607cppTeamWorkView::OnradixSort()
{
	// TODO: 在此添加命令处理程序代码
	if (!checkOpenFile())
	{
		return;
	}
	flag = -2;
	CMFCApplication20240607cppTeamWorkDoc* pDoc = GetDocument();
	radixSortDlg dlg;
	dlg.DoModal();
	if (dlg.m_nChooseSort == 0)
	{
		AfxMessageBox(_T("请先选择按照哪一个变量来进行排序！"));
	}
	else if (dlg.m_nChooseSort == 1)
	{
		radixSort(1, pDoc->arr);
	}
	else if (dlg.m_nChooseSort == 2)
	{
		radixSort(2, pDoc->arr);
	}
	else if (dlg.m_nChooseSort == 3)
	{
		radixSort(3, pDoc->arr);
	}
	Invalidate();
}

//删除点
void CMFCApplication20240607cppTeamWorkView::Ondel()
{
	// TODO: 在此添加命令处理程序代码
	if (!checkOpenFile())
	{
		return;
	}
	flag = -2;

	CMFCApplication20240607cppTeamWorkDoc* pDoc = GetDocument();
	deldlg dlg;
	dlg.DoModal();


	string name;
	name = CT2A(dlg.name.GetBuffer());
	int i;
	for (i = 0; i < pDoc->arr.m_Num; i++) {
		if (name == pDoc->arr.m_PointArr[i].getName()) {
			for (int j = i; j < pDoc->arr.m_Num - 1; j++) {
				pDoc->arr.m_PointArr[j] = pDoc->arr.m_PointArr[j + 1];
			}
			break;
		}
	}
	if (i == pDoc->arr.m_Num) {
		//AfxMessageBox(_T("未找到该点，请重新输入！"));
	}
	else {
		pDoc->arr.m_Num -= 1;
		Point* point = new Point[pDoc->arr.m_Num];
		for (i = 0; i < pDoc->arr.m_Num; i++) {
			point[i].setSerialNum(i + 1);
			point[i].setName(pDoc->arr.m_PointArr[i].getName());
			point[i].setX(pDoc->arr.m_PointArr[i].getX());
			point[i].setY(pDoc->arr.m_PointArr[i].getY());
			point[i].setZ(pDoc->arr.m_PointArr[i].getZ());
		}
		pDoc->arr.m_PointArr = point;

		writePointsToCSV(pDoc->arr, filePath);
		flag = 0;
		Invalidate();
	}

}

//修改点
void CMFCApplication20240607cppTeamWorkView::Oncha()//这个cha是change的缩写
{
	// TODO: 在此添加命令处理程序代码
	if (!checkOpenFile())
	{
		return;
	}
	flag = -2;

	CMFCApplication20240607cppTeamWorkDoc* pDoc = GetDocument();
	chaDlg dlg;
	dlg.DoModal();


	string na;
	na = CT2A(dlg.name1.GetBuffer());
	int i;
	for (i = 0; i < pDoc->arr.m_Num; i++) {
		if (na == pDoc->arr.m_PointArr[i].getName()) {
			break;
		}
	}
	if (i == pDoc->arr.m_Num) {
		//AfxMessageBox(_T("未找到该点，请重新输入！"));
	}
	else {
		string name;
		double x, y, z;
		name = CT2A(dlg.name2.GetBuffer());
		x = dlg.x;
		y = dlg.y;
		z = dlg.z;
		pDoc->arr.m_PointArr[i].setName(name);
		pDoc->arr.m_PointArr[i].setX(x);
		pDoc->arr.m_PointArr[i].setY(y);
		pDoc->arr.m_PointArr[i].setZ(z);

		writePointsToCSV(pDoc->arr, filePath);
		flag = 0;
		Invalidate();
	}

}

//按照点名查找点
void CMFCApplication20240607cppTeamWorkView::OnFindPointByName()
{
	// TODO: 在此添加命令处理程序代码
	if (!checkOpenFile())
	{
		return;
	}
	flag = -2;

	CMFCApplication20240607cppTeamWorkDoc* pDoc = GetDocument();
	FindPointByName dlg;
	dlg.DoModal();
	string ptName = CT2A(dlg.ptName.GetBuffer());
	GetPt1(ptName, pDoc->arr, pDoc->arrFind);

	flag = 4;//输出arrFind
	Invalidate();
}

//按照点的数据查找点
void CMFCApplication20240607cppTeamWorkView::OnFindPointByNum()
{
	// TODO: 在此添加命令处理程序代码
	if (!checkOpenFile())
	{
		return;
	}
	flag = -2;

	CMFCApplication20240607cppTeamWorkDoc* pDoc = GetDocument();
	FindPointByNumDlg dlg;
	dlg.DoModal();

	//使用ch标记按哪些数据的查找情况
	string ch;
	if (dlg.xFind != 0 && dlg.yFind == 0 && dlg.zFind == 0)
	{
		ch = "x";
	}
	else if (dlg.xFind == 0 && dlg.yFind != 0 && dlg.zFind == 0)
	{
		ch = "y";
	}
	else if (dlg.xFind == 0 && dlg.yFind == 0 && dlg.zFind != 0)
	{
		ch = "z";
	}
	else if (dlg.xFind != 0 && dlg.yFind != 0 && dlg.zFind == 0)
	{
		ch = "xy";
	}
	else if (dlg.xFind != 0 && dlg.yFind == 0 && dlg.zFind != 0)
	{
		ch = "xz";
	}
	else if (dlg.xFind == 0 && dlg.yFind != 0 && dlg.zFind != 0)
	{
		ch = "yz";
	}
	else if (dlg.xFind != 0 && dlg.yFind != 0 && dlg.zFind != 0)
	{
		ch = "xyz";
	}
	else
	{
		//AfxMessageBox(_T("请至少输入一项坐标数据进行查找！"));
		return;
	}

	GetPt2(ch, pDoc->arr, pDoc->arrFind, dlg.xFind, dlg.yFind, dlg.zFind);
	GetDefalutPt(dlg.xFind, dlg.yFind, dlg.zFind);
	flag = 5;//输出arrFind
	Invalidate();
}

//控制点的两点计算
void CMFCApplication20240607cppTeamWorkView::OnPointCalculateForTwo()
{
	// TODO: 在此添加命令处理程序代码
	if (!checkOpenFile())
	{
		return;
	}
	flag = -2;

	CMFCApplication20240607cppTeamWorkDoc* pDoc = GetDocument();
	PointCalculateForTwoDlg dlg;
	dlg.DoModal();

	Point a;
	a.setX(dlg.a_x); a.setY(dlg.a_y); a.setZ(dlg.a_z);

	GetMinDis(a, pDoc->arr, pDoc->closePoint);//最小斜距
	GetHeightDifference(a, pDoc->closePoint);//高差
	GetHorizontalDis(a, pDoc->closePoint);//水平距离
	GetAltitude(a, pDoc->closePoint);//高度角
	GetZenithAngle(a, pDoc->closePoint);//天顶距

	flag = 6;//输出两点计算结果
	Invalidate();
}

//控制点的三点计算
void CMFCApplication20240607cppTeamWorkView::OnPointCalculateForThree()
{
	// TODO: 在此添加命令处理程序代码
	if (!checkOpenFile())
	{
		return;
	}
	flag = -2;

	CMFCApplication20240607cppTeamWorkDoc* pDoc = GetDocument();
	PointCalculateForThreeDlg dlg;
	dlg.DoModal();

	Point vertex, a, b;
	int i = 0; bool isFind = false;

	if (dlg.vertexName == "" && dlg.vertexX != 0 && dlg.vertexY != 0 && dlg.vertexZ != 0)
	{
		vertex.setX(dlg.vertexX); vertex.setY(dlg.vertexY); vertex.setZ(dlg.vertexZ);
	}
	else if (dlg.vertexName != "" && dlg.vertexX == 0 && dlg.vertexY == 0 && dlg.vertexZ == 0)
	{
		for (i = 0; i < pDoc->arr.m_Num; i++)
		{
			if (dlg.vertexName == pDoc->arr.m_PointArr[i].getName().c_str())
			{
				vertex = pDoc->arr.m_PointArr[i];
				isFind = true;
				break;
			}
		}
		if (!isFind)
		{
			CString strVertex;
			for (int i = 0; i < pDoc->arr.m_Num; i++)
			{
				strVertex.Format(_T("没有查找到您输入的点名对应的点“%s”！"), dlg.vertexName);
				if (isAfxMessageBoxOn)
				{
					AfxMessageBox(strVertex);
				}
				isAfxMessageBoxOn = false;
			}
		}
	}
	else
	{
		return;
	}

	if (dlg.aName == "" && dlg.aX != 0 && dlg.aY != 0 && dlg.aZ != 0)
	{
		a.setX(dlg.aX); a.setY(dlg.aY); a.setZ(dlg.aZ);
	}
	else if (dlg.aName != "" && dlg.aX == 0 && dlg.aY == 0 && dlg.aZ == 0)
	{
		for (i = 0; i < pDoc->arr.m_Num; i++)
		{
			if (dlg.aName == pDoc->arr.m_PointArr[i].getName().c_str())
			{
				a = pDoc->arr.m_PointArr[i];
				isFind = true;
				break;
			}
		}
		if (!isFind)
		{
			CString strA;
			for (int i = 0; i < pDoc->arr.m_Num; i++)
			{
				strA.Format(_T("没有查找到您输入的点名对应的点“%s”！"), dlg.aName);
				if (isAfxMessageBoxOn)
				{
					AfxMessageBox(strA);
				}
				isAfxMessageBoxOn = false;
			}
		}
	}
	else
	{
		return;
	}

	if (dlg.bName == "" && dlg.bX != 0 && dlg.bY != 0 && dlg.bZ != 0)
	{
		b.setX(dlg.bX); b.setY(dlg.bY); b.setZ(dlg.bZ);
	}
	else if (dlg.bName != "" && dlg.bX == 0 && dlg.bY == 0 && dlg.bZ == 0)
	{
		for (i = 0; i < pDoc->arr.m_Num; i++)
		{
			if (dlg.bName == pDoc->arr.m_PointArr[i].getName().c_str())
			{
				b = pDoc->arr.m_PointArr[i];
				isFind = true;
				break;
			}
		}
		if (!isFind)
		{
			CString strB;
			for (int i = 0; i < pDoc->arr.m_Num; i++)
			{
				strB.Format(_T("没有查找到您输入的点名对应的点“%s”！"), dlg.bName);
					if (isAfxMessageBoxOn)
					{
						AfxMessageBox(strB);
					}
					isAfxMessageBoxOn = false;
			}
		}
	}
	else
	{
		return;
	}

	GetProjectAng(vertex, a, b);
	GetAng(vertex, a, b);

	flag = 7;//输出三点计算结果
	Invalidate();
}

//地形晕渲图绘制
void CMFCApplication20240607cppTeamWorkView::OnPaintMap()
{
	// TODO: 在此添加命令处理程序代码
	if (!checkOpenFile())
	{
		return;
	}
	if (!isBuyVIP)
	{
		AfxMessageBox(_T("“地形晕渲图绘制”属于高级功能，您还激活VIP，请先输入VIP密钥激活VIP，再来使用本功能！"));
		return;
	}
	flag = -2;

	CMFCApplication20240607cppTeamWorkDoc* pDoc = GetDocument();
	classifyPoints(pDoc->arr);
	double grid[51][51] = { 0 };
	fillGridZValues(grid);
	calculateRGB(grid, colors);

	flag = 8;
	Invalidate();
}

//登录界面
void CMFCApplication20240607cppTeamWorkView::OnSignIn()
{
	// TODO: 在此添加命令处理程序代码
	flag = -2;

	CMFCApplication20240607cppTeamWorkDoc* pDoc = GetDocument();
	SignInDlg dlg;
	dlg.DoModal();
	if (dlg.isSignInOk)
	{
		isSignIn = true;
	}
	flag = -1;
	Invalidate();
}

//系统“打开”方式对应事件处理函数
void CMFCApplication20240607cppTeamWorkView::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	if (!isSignIn)
	{
		AfxMessageBox(_T("您还没有登录，请先登录再来使用本软件！"));
		return;
	}
	flag = -2;

	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT);

	/****************************读取文件数据****************************/

	if (fileDlg.DoModal() == IDOK)
	{
		//通过对话框获取文件路径
		CString strFileName = fileDlg.GetPathName();// 获取用户选择的文件路径

		CMFCApplication20240607cppTeamWorkDoc* pDoc = GetDocument();//把数据存在Doc的类里面

		FILE* fp;
		//int length = dlg.filePath.GetLength();
		//char* filePath = new char[length + 1]; // 需要多分配一个字节用来存放字符串结束符'\0'
		if (strFileName == "")
		{
			filePath = "D://gcp.csv";
		}
		else
		{
			strcpy(filePath, CT2A(strFileName));
		}

		// 检查文件是否能够成功打开
		ifstream file(filePath);
		if (!file.is_open())
		{
			CString strFileOpenErr;
			strFileOpenErr.Format(_T("文件打开失败！"), 400, 300);
			//消息框中会出现一个停止标志图标，后面的是宽和高
			AfxMessageBox(strFileOpenErr, MB_HELP | MB_ICONERROR, 0);
			return;
		}
		file.close(); // 检验完成后关闭文件

		//打开文件准备获取数据
		fp = fopen(filePath, "r");
		if (!fp)
		{
			CString strFileOpenErr;
			strFileOpenErr.Format(_T("文件打开失败！"), 400, 300);
			//消息框中会出现一个停止标志图标，后面的是宽和高
			AfxMessageBox(strFileOpenErr, MB_HELP | MB_ICONERROR, 0);
			return;
		}
		char ch = '\0';
		double f = 0.0;
		int d = 0;
		int i = 0;
		fscanf(fp, "%d\n", &d);
		pDoc->arr.m_Num = d;
		Point* point = new Point[pDoc->arr.m_Num];
		for (i = 0; !feof(fp); i++)
		{
			fscanf(fp, "%d,", &d);
			point[i].setSerialNum(d);//点的序号存入数组    
			string strName;
			for (ch = fgetc(fp); ch != ','; ch = fgetc(fp))
			{
				strName += ch;//获取点的名称
			}
			point[i].setName(strName);
			fscanf(fp, "%lf,", &f);//从文件指针fp指向的文件中，读取double型的坐标数据，储存在double型的变量f中。注意这里有一个“,”
			point[i].setX(f);//x坐标存入数组
			fscanf(fp, "%lf,", &f);
			point[i].setY(f);//y坐标存入数组    
			fscanf(fp, "%lf,", &f);
			point[i].setZ(f);//z坐标存入数组
			fgetc(fp);//读走每一行最后的换行符
		}
		pDoc->arr.m_PointArr = point;
		int finalSerialNum = pDoc->arr.m_PointArr[pDoc->arr.m_Num - 1].getSerialNum();
		flag = 0;
		fclose(fp);
		Invalidate();//至此，文件中的数据已经被读取到Doc类的arr中，再去OnDraw处输出显示
		MessageBox(_T("文件读取成功！"), _T("文件读取成功提示对话框"));
		isOpenFile = true;
	}
	else
	{
		CString strFileOpenErr;
		strFileOpenErr.Format(_T("文件打开失败！"), 400, 300);
		//消息框中会出现一个停止标志图标，后面的是宽和高
		AfxMessageBox(strFileOpenErr, MB_HELP | MB_ICONERROR, 0);
		return;
	}
}

//VIP密钥界面
void CMFCApplication20240607cppTeamWorkView::OnBuyVIPkey()
{
	// TODO: 在此添加命令处理程序代码
	flag = -2;

	CMFCApplication20240607cppTeamWorkDoc* pDoc = GetDocument();
	BuyVIPDlg dlg;
	dlg.DoModal();
	if (dlg.isBeyVIPOk)
	{
		isBuyVIP = true;
	}
	flag = -1;
	Invalidate();
}

//小组分工介绍界面
void CMFCApplication20240607cppTeamWorkView::OnTeamWork()
{
	// TODO: 在此添加命令处理程序代码
	CTeamWorkDialog dlg;
	dlg.DoModal();
}

//多关键字排序
void CMFCApplication20240607cppTeamWorkView::OnMultiKeywordSort()
{
	// TODO: 在此添加命令处理程序代码
	if (!checkOpenFile())
	{
		return;
	}
	flag = -2;
	

	CMFCApplication20240607cppTeamWorkDoc* pDoc = GetDocument();
	MultiKeywordSortDlg dlg;
	dlg.DoModal();

	pDoc->arrMultiSortRuleName = intToString(pDoc->arrMultiSortRuleCode);

	flag = 9;//输出按照多关键字排序后的结果
	Invalidate();
}

//回到主页
void CMFCApplication20240607cppTeamWorkView::OnGoBackToHomePage()
{
	// TODO: 在此添加命令处理程序代码
	flag = -2;
	flag = -1;//输出按照多关键字排序后的结果
	Invalidate();
}
