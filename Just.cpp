#include <stdio.h>
#include <windows.h>
DWORD Size = 832;
//���������ֵ 24*30 = 832
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
	HWND hwindows = FindWindow(NULL, "ɨ��");
	// ��ȡɨ����Ϸ��Ӧ�Ĵ��ھ��
	if (hwindows != 0){
		//��ȡ���˲ż���������ֱ���˳� 
		GetWindowThreadProcessId(hwindows, &mineID);
		//ͨ����������ƻ�ȡ�����ID��
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, mineID);
		//��ɨ����Ϸ���ڴ������ ��Ϊ0��δ��
			// ��ȡ�����ĳ��Ϳ�,������ columns��rows���� 
		ReadProcessMemory(hProcess, (LPVOID)0x1005334, &columns, sizeof(BYTE), NULL);
		//0x1005334�Ǳ��������Ŀ�ĵ�ַ 
		ReadProcessMemory(hProcess, (LPVOID)0x1005338, &rows, sizeof(BYTE), NULL);
		//0x1005338�Ǳ��������߶ȵĵ�ַ 
		ReadProcessMemory(hProcess, (LPVOID)0x1005330, &leicount, sizeof(BYTE), NULL);
		UI(hProcess,hwindows);  
			 
	}	
	else {
		printf("û�еõ����������ݣ���,���ɨ�׳�������");
	}
	CloseHandle(hProcess);
	//�ر�֮ǰ�򿪵��ڴ������ 
	return 0;
}
void MainUI()
{
	printf("-----------------------------------------\n");
	printf("|\tɨ����Ϸ�ƽ�    by Just\t\t|\n");
	printf("-----------------------------------------\n");
	printf("|\t  1.�Զ���ʶ����\t\t|\n");
	printf("|\t  2.һ���ƽ�\t\t\t|\n");
	printf("|\t  3.ʹ��˵��\t\t\t|\n");
	printf("|\t  0.�˳�\t\t\t|\n");
	printf("-----------------------------------------\n");
}
void UI(HANDLE hProcess,HWND hwindows){
	if (hProcess == 0){
		printf("ERROR:δ��ȡ���������ȷ��ɨ�׳����Ѿ���");
		return;
		}
		if(columns == 9 && rows == 9){
		printf("����ǰ����Ϸ�Ѷ�Ϊ==>�������׵�����==>%d��\n",leicount);
	}else if(columns == 16 && rows == 16){
		printf("����ǰ����Ϸ�Ѷ�Ϊ==>�м����׵�����==>%d��\n",leicount);
	}else if(columns == 16 && rows == 30){
		printf("����ǰ����Ϸ�Ѷ�Ϊ==>�߼����׵�����==>%d��\n",leicount);
	}else{
		printf("����ǰ����Ϸ�Ѷ�Ϊ==>�Զ��壬�׵�����==>%d��\n",leicount);
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
				printf("ɨ�׳���û�д򿪣�����򿪺������г���\n");
			    return;
			}else {
				printf("������ע�ɹ�\n");
				UI1(hProcess,hwindows); 
			}
			break;
		case 2:
			flag = 0;
			if(pj(hProcess,hwindows)==0){
				printf("ɨ�׳���û�д򿪣�����򿪺������г���\n");
			    return;
			}else{
				printf("ɨ�׳������ƽ�\n");
			}
			break; 
		case 3:
		printf("���иó���֮ǰ�����ɨ�׳���򿪣�������ƽ�ʧ�ܣ�����\n"); 
		UI1(hProcess,hwindows);
		case 0:
			flag = 0;
			return;
		default:
			printf("�����������������\n");
			printf("======>:");	
			scanf("%d",&choose);	
		}
	}
	 
}
void UI1(HANDLE hProcess,HWND hwindows){
	int choose1;
	int flag1 = 1;
	printf("1.����\n");
	printf("2.�˳�\n");
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
			printf("�����������������\n");
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
		// ��ȡ��������������
		BYTE qj = 0x8E;
		//���� 
		int i = 0;
		while (i < Size) {
			if (lpBuffer[i] == 0x8F) {
				Addr = 0x01005340 + i; 
				WriteProcessMemory(hProcess, (LPVOID)Addr, &qj, sizeof(BYTE), 0);
				//д���ڴ���ȥ 
			}
			i++;
		}
    
		//ˢ��ɨ�׵Ŀͻ���
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
		//��̬���� lpBuffer�Ĵ�С 
	
	    ReadProcessMemory(hProcess, (LPVOID)0x01005340, lpBuffer1, Size, NULL);
		// ��ȡ��������������
		//hProcess ���̾���� 0x01005340 ��������ʼ��ַ��lpBuffer������� ,Size��ȡ���ֽ��� 
		int i = 0;
		int n = Size;
		int h = rows;
		int count = 0;
 
		//����ת����ȥ���������������
		PBYTE lpBuffer2 = NULL;
		lpBuffer2 = (PBYTE)malloc(rows*columns);
		//��̬�����ڴ� 
		while (i < Size) {
			if (lpBuffer1[i] == 0x10 && lpBuffer1[i + 1] == 0x10) {
				//��ʱ �ڱ߽��ϣ�ֱ��ת����һ�У������� 
				i = i + columns + 2;
				continue;
			}
			else if (lpBuffer1[i] == 0x10) {
				for (int j = 1; j <= columns; j++) {
					lpBuffer2[count] = lpBuffer1[i + j];
					//i+j ��i�ǵ�һ��10��ֱ������ 
					//pTmpByte[count]���������ȡ������������ 
					count++;					
				}
				i = i + columns + 2;
				//+2��Ϊ�������߽� 
				continue;
				h--;
				//�����ĸ߶ȼ�һ 
				if (h == 0)
				{
					break;
				} 
				//�߶�Ϊ0(��ȡ���)���˳�ѭ��				
			}
			i++;
		}
 
		// ȡ������������꣬Ȼ��ģ�������е��
		int x = 0, y = 0;
		//x��ʾ�ڼ��У�y��ʾ�ڼ��� 
		int dx = 0, dy = 0;
		for (i = 0; i < rows*columns; i++){
			if (lpBuffer2[i] != 0x8F) {
				//������ǵ��ף�������������0x8F��ʾ�� 
				x = i % columns; 
				//��һά������±�ת��Ϊ��Ӧ��ά��������±� 
				y = i / columns;
				//��һά������±�ת��Ϊ��Ӧ��ά��������±� 
				dx = x * 16 + 19;
				dy = y * 16 + 61;
				//ÿһ�������Ĵ�СΪ16x16������һ�����������ɨ�״��ڵ�λ��Ϊ��19��61�� 
				SendMessage(hwindows, WM_LBUTTONDOWN, MK_LBUTTON, MAKELONG(dx, dy));
				//ͨ����ȡ����ɨ����Ϸ��Ӧ�Ĵ��ھ�����ͷ����������꣬���������� 
				SendMessage(hwindows, WM_LBUTTONUP, MK_LBUTTON, MAKELONG(dx, dy));
				//ͨ����ȡ����ɨ����Ϸ��Ӧ�Ĵ��ھ�����ͷ����������̧꣬�������� 
			}
		}
		free(lpBuffer1);
		free(lpBuffer2);
		//�ͷ� 
	return 1;
	
}

	

