// main.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
#include <shlwapi.h>
typedef int			(*LPDLLFUNC_OPERATOR)(int&, int&);		// 函数指针

int main()
{
	HMODULE  hDll = NULL;
	const wchar_t* szPath = L"..\\x64\\Release\\TestForDLL.dll";
	LPDLLFUNC_OPERATOR pFuncAdd = NULL;
	LPDLLFUNC_OPERATOR pFuncMulti = NULL;
	if (hDll == NULL) {
		hDll = LoadLibrary(szPath);
		if (hDll != NULL) {
			pFuncAdd = (LPDLLFUNC_OPERATOR)GetProcAddress(hDll, "_add");		//获取函数地址
			pFuncMulti = (LPDLLFUNC_OPERATOR)GetProcAddress(hDll, "_multi");
			// 判断从dll中加载函数是否成功
			if(pFuncAdd==NULL|| pFuncMulti==NULL){
				printf("Load func error:[%d]\n", GetLastError());

				FreeLibrary(hDll);
				hDll = NULL;
				pFuncAdd = NULL;
				pFuncMulti = NULL;	
				return NULL;
			}
		}
		else{
			printf("Load DLL error:[%d] %s\n", GetLastError(), szPath);
			return NULL;
		}
	}
	int a = 17;
	int b = 15;

	std::cout << pFuncAdd(a, b) << std::endl;		// 利用函数指针直接调用函数
	std::cout << pFuncMulti(a, b) << std::endl;

	FreeLibrary(hDll);
	return 0;
}