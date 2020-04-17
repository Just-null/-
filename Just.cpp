#include <stdio.h>
#include <windows.h>
DWORD Size = 832;
//雷区的最大值 24*30 = 832
DWORD Addr = 0x01005340;
int columns = 0, rows = 0,leicount = 0;;
void UI(HANDLE hProcess,HWND hwindows);
void UI1(HANDLE hProcess,HWND hwindows);
int bs(HANDLE hProcess,HWND hwindows);
int pj(HANDLE hProcess,HWND hwindows);
void MainUI();
int main() 
{
	MainUI();
	DWORD mineID = 0;
	HANDLE hProcess = 0;
	HWND hwindows = FindWindow(NULL, "扫雷");
	// 获取扫雷游戏对应的窗口句柄
	if (hwindows != 0){
		//获取到了才继续，否则直接退出 
		GetWindowThreadProcessId(hwindows, &mineID);
		//通过程序的名称获取程序的ID号
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, mineID);
		//打开扫雷游戏的内存读功能 ，为0则未打开
			// 读取雷区的长和宽,保存在 columns和rows里面 
		ReadProcessMemory(hProcess, (LPVOID)0x1005334, &columns, sizeof(BYTE), NULL);
		//0x1005334是保存雷区的宽的地址 
		ReadProcessMemory(hProcess, (LPVOID)0x1005338, &rows, sizeof(BYTE), NULL);
		//0x1005338是保存雷区高度的地址 
		ReadProcessMemory(hProcess, (LPVOID)0x1005330, &leicount, sizeof(BYTE), NULL);
		UI(hProcess,hwindows);  
			 
	}	
	else {
		printf("没有得到雷区的数据！！,请打开扫雷程序重试");
	}
	CloseHandle(hProcess);
	//关闭之前打开的内存读功能 
	return 0;
}
void MainUI()
{
	printf("-----------------------------------------\n");
	printf("|\t扫雷游戏破解    by Just\t\t|\n");
	printf("-----------------------------------------\n");
	printf("|\t  1.自动标识雷区\t\t|\n");
	printf("|\t  2.一键破解\t\t\t|\n");
	printf("|\t  3.使用说明\t\t\t|\n");
	printf("|\t  0.退出\t\t\t|\n");
	printf("-----------------------------------------\n");
}
void UI(HANDLE hProcess,HWND hwindows){
	if (hProcess == 0){
		printf("ERROR:未获取到句柄，请确保扫雷程序已经打开");
		return;
		}
		if(columns == 9 && rows == 9){
		printf("您当前的游戏难度为==>初级，雷的数量==>%d颗\n",leicount);
	}else if(columns == 16 && rows == 16){
		printf("您当前的游戏难度为==>中级，雷的数量==>%d颗\n",leicount);
	}else if(columns == 16 && rows == 30){
		printf("您当前的游戏难度为==>高级，雷的数量==>%d颗\n",leicount);
	}else{
		printf("您当前的游戏难度为==>自定义，雷的数量==>%d颗\n",leicount);
	} 
	printf("*******************************************\n");
	int choose;
	printf("=======>:");
	scanf("%d",&choose);
	int flag = 1;
	while(flag){
		switch(choose){
		case 1:
			flag = 0;
			if(bs(hProcess,hwindows)==0){
				printf("扫雷程序没有打开！！请打开后再运行程序\n");
			    return;
			}else {
				printf("雷区标注成功\n");
				UI1(hProcess,hwindows); 
			}
			break;
		case 2:
			flag = 0;
			if(pj(hProcess,hwindows)==0){
				printf("扫雷程序没有打开！！请打开后再运行程序\n");
			    return;
			}else{
				printf("扫雷程序已破解\n");
			}
			break; 
		case 3:
		printf("运行该程序之前，请把扫雷程序打开，否则会破解失败！！！\n"); 
		UI1(hProcess,hwindows);
		case 0:
			flag = 0;
			return;
		default:
			printf("输入错误，请重新输入\n");
			printf("======>:");	
			scanf("%d",&choose);	
		}
	}
	 
}
void UI1(HANDLE hProcess,HWND hwindows){
	int choose1;
	int flag1 = 1;
	printf("1.返回\n");
	printf("2.退出\n");
	printf("=======>:");
	scanf("%d",&choose1);
	system("cls");
	while(flag1){
		switch(choose1){
			case 1:
				flag1 = 0;
				MainUI(); 
				UI(hProcess,hwindows);
				break;
			case 2:
				flag1 = 0;
			    return;
			default:
			printf("输入错误，请重新输入\n");
			printf("======>:");	
			scanf("%d",&choose1);	
		}
	} 
	 
}
int bs(HANDLE hProcess,HWND hwindows){
	PBYTE lpBuffer = NULL;
	lpBuffer = (PBYTE)malloc(Size);
	if (hProcess == 0){
			return 0;
		}
		ReadProcessMemory(hProcess, (LPVOID)Addr, lpBuffer, Size, NULL);
		// 读取整个雷区的数据
		BYTE qj = 0x8E;
		//旗子 
		int i = 0;
		while (i < Size) {
			if (lpBuffer[i] == 0x8F) {
				Addr = 0x01005340 + i; 
				WriteProcessMemory(hProcess, (LPVOID)Addr, &qj, sizeof(BYTE), 0);
				//写到内存中去 
			}
			i++;
		}
    
		//刷新扫雷的客户区
		RECT rt;
		GetClientRect(hwindows, &rt);
		InvalidateRect(hwindows, &rt, TRUE);
		free(lpBuffer);
		return 1; 
}
int pj(HANDLE hProcess,HWND hwindows){
	if (hProcess == 0){
			return 0;
		}
	    PBYTE lpBuffer1 = NULL;
		lpBuffer1 = (PBYTE)malloc(Size);
		//动态分配 lpBuffer的大小 
	
	    ReadProcessMemory(hProcess, (LPVOID)0x01005340, lpBuffer1, Size, NULL);
		// 读取整个雷区的数据
		//hProcess 进程句柄， 0x01005340 雷区的起始地址，lpBuffer存放数据 ,Size读取的字节数 
		int i = 0;
		int n = Size;
		int h = rows;
		int count = 0;
 
		//雷区转换，去掉雷区多余的数据
		PBYTE lpBuffer2 = NULL;
		lpBuffer2 = (PBYTE)malloc(rows*columns);
		//动态分配内存 
		while (i < Size) {
			if (lpBuffer1[i] == 0x10 && lpBuffer1[i + 1] == 0x10) {
				//此时 在边界上，直接转入下一行（跳过） 
				i = i + columns + 2;
				continue;
			}
			else if (lpBuffer1[i] == 0x10) {
				for (int j = 1; j <= columns; j++) {
					lpBuffer2[count] = lpBuffer1[i + j];
					//i+j ，i是第一个10，直接跳过 
					//pTmpByte[count]用来保存读取到的雷区数据 
					count++;					
				}
				i = i + columns + 2;
				//+2是为了跳过边界 
				continue;
				h--;
				//雷区的高度减一 
				if (h == 0)
				{
					break;
				} 
				//高度为0(读取完毕)，退出循环				
			}
			i++;
		}
 
		// 取雷区方块的坐标，然后模拟鼠标进行点击
		int x = 0, y = 0;
		//x表示第几列，y表示第几行 
		int dx = 0, dy = 0;
		for (i = 0; i < rows*columns; i++){
			if (lpBuffer2[i] != 0x8F) {
				//如果不是地雷，则点击（地雷是0x8F表示） 
				x = i % columns; 
				//将一维数组的下标转换为对应二维数组的列下标 
				y = i / columns;
				//将一维数组的下标转换为对应二维数组的行下标 
				dx = x * 16 + 19;
				dy = y * 16 + 61;
				//每一块雷区的大小为16x16，而第一个雷区相对于扫雷窗口的位置为（19，61） 
				SendMessage(hwindows, WM_LBUTTONDOWN, MK_LBUTTON, MAKELONG(dx, dy));
				//通过获取到的扫雷游戏对应的窗口句柄，和非雷区的坐标，按下鼠标左键 
				SendMessage(hwindows, WM_LBUTTONUP, MK_LBUTTON, MAKELONG(dx, dy));
				//通过获取到的扫雷游戏对应的窗口句柄，和非雷区的坐标，抬起鼠标左键 
			}
		}
		free(lpBuffer1);
		free(lpBuffer2);
		//释放 
	return 1;
	
}

	

