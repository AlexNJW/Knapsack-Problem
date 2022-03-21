#define _CRT_SECURE_NO_WARNINGS 1;
#include <iostream>
#include <fstream>
#include <io.h>
#include<cstdlib>
#include<algorithm>
#include<cstring>

using namespace std;

int bestValue1;
int x[100], cx[100];
int cv;
int cw;
int knapstackTanXin(int i, int n, int c, int resCapacity[100], int resValue[100]);
int f[100];
int knapstackDongGui(int dataNum, int bagCapasity, int v[100], int w[100],int f[100]);
int result = 0;
void KnapsackHuiSu(int i, int max, int value, int rescapacity2[100], int resvalue2[100], int n);

int main()
{

	int n = 0;									//控制循环
	int tempN;
	string name[20];
	char isContinue = 'c';
	int fileNum;								//选择的文件序号
	int resolveNum;								//解决方法序号：1为贪心算法，2为动态规划法，3为回溯算法

	int bagCapacity;							//背包容量
	int numOfData;								//数据数量
	int resCapacity[100];						//物品大小
	int resValue[100];							//物品价值
	int bestValue;								//最大价值
	
	while (isContinue == 'c')
	{
		#pragma region 遍历输入文件夹下的输入文件将文件名字存入name中，n为文件个数

		string inPath = "..\\InFile\\*.in";
									
		_int64 handle;
		struct _finddata_t fileinfo;
		//第一次查找
		handle = _findfirst(inPath.c_str(), &fileinfo);
		if (handle == -1)
			return -1;
		cout << "文件目录：" << endl << endl;
		do
		{
			name[n] = fileinfo.name;
			n += 1;
			//找到的文件的文件名
			cout << "序号：" << n << " 文件名：" << fileinfo.name << endl;
		} while (!_findnext(handle, &fileinfo));
		
		_findclose(handle);

		#pragma endregion

		cout << endl << "输入文件序号:";
		cin >> fileNum;

		#pragma region 将对应文件中数据读入
		tempN = 0;
		handle = _findfirst(inPath.c_str(), &fileinfo);
		if (handle == -1)
			return -1;
		do
		{
			//找到的文件的文件名
			
			if (tempN == fileNum - 1) {
				cout << "序号：" << tempN << " 文件名：" << fileinfo.name << endl;
				string s = "..\\InFile\\";
				s.append(fileinfo.name);
				char asd[20];
				strcpy(asd, s.c_str());
				FILE* f = fopen(asd, "r");
				fscanf(f, "%d %d", &bagCapacity, &numOfData);
				for (int i = 0; i < numOfData; i++) {
					fscanf(f, "\n%d %d", &resCapacity[i], &resValue[i]);
				}
			}
			tempN += 1;
		} while (!_findnext(handle, &fileinfo) && tempN < fileNum);
		_findclose(handle);
		#pragma endregion

		cout << endl << "输入所选方法(1:贪心算法 2:动态规划法 3:回溯算法):";
		cin >> resolveNum;

		if (resolveNum == 1) {
			bestValue =  knapstackTanXin(0,numOfData,bagCapacity, resCapacity, resValue);
			cout << "所能装入物品的最大价值为：" << bestValue << endl;
		}
		else if(resolveNum == 2)
		{
			bestValue = knapstackDongGui(numOfData,bagCapacity,resCapacity,resValue,f);
			cout << "所能装入物品的最大价值为：" << bestValue << endl;
		}
		else if (resolveNum == 3) 
		{
			KnapsackHuiSu(0, bagCapacity, 0, resCapacity, resValue, numOfData);
			cout << "所能装入物品的最大价值为：" << result << endl;
		}

		cout << endl << "输入c继续执行，停止程序请输入s:";
		cin >> isContinue ;
		cout << endl;
		n = 0;
		result = 0;
	}

	return 0;
}

//贪心算法
int knapstackTanXin(int i,int n,int c,int resCapacity[100],int resValue[100])
{

	if (i > n - 1)
	{
		if ( bestValue1 < cv && cw <= c)
		{
			for (int k = 0; k < n; k++)
				x[k] = cx[k];//存储最优路径
			bestValue1 = cv;
		}
		return bestValue1;
	}
	cw = cw + resCapacity[i];
	cv = cv + resValue[i];
	cx[i] = 1;
	knapstackTanXin(i + 1, n, c, resCapacity, resValue);
	cw = cw - resCapacity[i];
	cv = cv - resValue[i];
	cx[i] = 0;
	knapstackTanXin(i + 1, n, c, resCapacity, resValue);
	return bestValue1;
}

//动态规划法
int knapstackDongGui(int dataNum1, int bagCapasity1,int v[100],int w1[100],int f1[100]) {
	for (int i1 = 0; i1 < dataNum1; i1++)
	{
		for (int j = bagCapasity1; j >= v[i1]; j--) {
			f1[j] = max(f1[j], f1[j - v[i1]] + w1[i1]);
		}

	}
	int temp = f1[bagCapasity1];
	return temp;
}

//回溯法
void KnapsackHuiSu(int i3, int max3, int value3, int rescapacity23[100], int resvalue23[100], int n3)
{
	
	for (int k = i3; k < n3; k++) {
		if (max3 > 0) {
			if (rescapacity23[k] <= max3) {
				if (value3 + resvalue23[k] >= result) {
					result = value3 + resvalue23[k];
				}
			}
			if ((k + 1) < n3) {
				KnapsackHuiSu(k + 1, max3 - rescapacity23[k], value3 + resvalue23[k], rescapacity23, resvalue23, n3);
			}
		}
	}
}