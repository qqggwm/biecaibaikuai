#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define  MaxHeigh 53		//5+12*4
#define  MaxWidth 88		//(10*4+5)*2
#define	 BlockWidth 10	//һ��Block���Ϊ10
#define	 BlockHeigh 12	//һ��Block�߶�Ϊ12

void  windowProgress();
void windowProgress2();
void rollBlock(int x, int y);
/**
��λ����
*/
void gotoxy(int x, int  y) {
	//����win32api���ù��λ��
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(handle, coord);
}

/**
�������
*/
void full_screen()
{
	HWND hwnd = GetForegroundWindow();
	int cx = GetSystemMetrics(SM_CXSCREEN);            /* ��Ļ��� ���� */
	int cy = GetSystemMetrics(SM_CYSCREEN);            /* ��Ļ�߶� ���� */

	LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);   /* ��ȡ������Ϣ */
	/* ���ô�����Ϣ ��� ȡ�����������߿� */
	SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);

	SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);
}



/**
���߿�
*/
void createLine()
{
	int i, j;
	for (i = 0; i < MaxHeigh; i++)	//���ұ߿�+�м�
	{
		gotoxy(0, i);
		printf("��");
		gotoxy((MaxWidth) / 4, i);
		printf("��");
		gotoxy((MaxWidth) / 4 * 2, i);
		printf("��");
		gotoxy((MaxWidth) / 4 * 3, i);
		printf("��");
		gotoxy(MaxWidth, i);
		printf("��");
		printf("%d", i);						//������ʶ
	}
	printf("\n");

	for (j = 2; j <= MaxWidth; j += 2)	//���±߿�+�м�߿�
	{
		gotoxy(j, 0);
		printf("��");
		gotoxy(j, (MaxHeigh - 1) / 4);
		printf("��");
		gotoxy(j, (MaxHeigh - 1) / 4 * 2);
		printf("��");
		gotoxy(j, (MaxHeigh - 1) / 4 * 3);
		printf("��");
		gotoxy(j, MaxHeigh - 1);
		printf("��");

	}
	printf("\n");

}
/*
ģʽ2�߿�
*/
void createLine2()
{
	int i, j;
	for (i = 0; i < MaxHeigh; i++)	//���ұ߿�+�м�
	{
		gotoxy(0, i);
		printf("��");
		gotoxy((MaxWidth) / 4, i);
		printf("��");
		gotoxy((MaxWidth) / 4 * 2, i);
		printf("��");
		gotoxy((MaxWidth) / 4 * 3, i);
		printf("��");
		gotoxy(MaxWidth, i);
		printf("��");
		printf("%d", i);						//������ʶ
	}
	printf("\n");

	for (j = 2; j <= MaxWidth; j += 2)	//���±߿�+�м�߿�
	{
		gotoxy(j, 0);
		printf("��");
		
		gotoxy(j, MaxHeigh - 1);
		printf("��");

	}
	printf("\n");

}
/**
������ɫ
*/

/**
���ɷ���
*/
void  paintBlock(int x, int y) {
	int  i, j;
	int  rx = (x * BlockWidth + x + 1) * 2;//�����ߺ�ǰ��Ŀ����������x���꣬����һ�����飨�ߣ�ռ�����ַ�
	int  ry = y * BlockHeigh + y + 1;

	for (j = ry; j <= ry + BlockHeigh - 1; j++)
	{
		for (i = rx; i <= rx + BlockWidth * 2 - 1; i = i + 2)
		{

			gotoxy(i, j);
			printf("��");
		}
	}
	gotoxy(0, 52);
}
	/**
	���ɷ���2
	*/
void  paintBlock2(int x){
	int  i,j;
	int haspaint = 0;
	int  rx = (x * BlockWidth + x + 1) * 2;//�����ߺ�ǰ��Ŀ����������x���꣬����һ�����飨�ߣ�ռ�����ַ�
	//int  ry = y * BlockHeigh + y + 1;	
	for (j = 1; j <= 12; j++) {
		Sleep(500);
		for (i = rx; i <= rx + BlockWidth * 2 - 1; i = i + 2)
			{
		
				gotoxy(i, j);
				printf("��");
				haspaint++;
				
			}
	}	
	
	rollBlock(x,j);//x��ˮƽ���룬y�ǵײ��������ڵ�����j=12
	gotoxy(0, 52);

}
/*
ģʽ2�ķ������䷽ʽ
*/
void rollBlock(int x, int y) {	//y=12
	int i;
	int  rx = (x * BlockWidth + x + 1) * 2;//�����ߺ�ǰ��Ŀ����������x���꣬����һ�����飨�ߣ�ռ�����ַ�
	int top = 1,bottom=y;

	while (bottom <= 51)
	{	
		Sleep(500);
		for (i = rx; i <= rx + BlockWidth * 2 - 1; i = i + 2)
			{
				gotoxy(i, top);
				printf("  ");
				
				gotoxy(i, bottom);
				printf("��");
				
			}
		top++; bottom++;
	}
			
		
}
/**
�����������
*/
void  randCreateBlock(int bblock[]) {

	int i;
	for (i = 3; i >= 0; i--)
	{

		bblock[i] = rand() % 4;
		paintBlock(bblock[i], i);
		
	}

}

/**
�����������2
*/
void  randCreateBlock2(int bblock[]) {

	int i;
	//int haspaint = 0;
	//while (1)
	//{
	//	Sleep(1000);
	///*for (i = 0; i < 5; i++)
	//	{	
	//	
	//		bblock[i] = rand() % 4;
	//	
	//		paintBlock2(bblock[i]);
	//		
	//	}*/
	//	
	//}
	bblock[0] = rand() % 4;
	paintBlock2(bblock[0]);
}

/**
����ϴεĺۼ�
*/
void cleanBlock(int x, int y) {

	int  i, j;

	int  rx = (x * BlockWidth + x + 1) * 2;//�����ߺ�ǰ��Ŀ����������x���꣬����һ�����飨�ߣ�ռ�����ַ�
	int  ry = y * BlockHeigh + y + 1;

	for (j = ry; j <= ry + BlockHeigh - 1; j++)
	{
		for (i = rx; i <= rx + BlockWidth * 2 - 1; i = i + 2)
		{
			gotoxy(i, j);
			printf("  ");
		}
	}
	gotoxy(0, 55);

}

/**
�������̰���
*/
void listenKeyBoard() {
	if (_kbhit()) {
		char ch = _getch();
		printf("%c", ch);
		printf("%d", ch);
	}
}

/**
��ȡ��߷���
*/
double readmaxScore() {
	double maxScore;
	FILE* fp;
	fopen_s(&fp, "score.txt", "r");//r+��д ����������ھʹ���
	fscanf_s(fp, "%lf", &maxScore);
	fclose(fp);
	return maxScore;
}

/**
���Ʒ�����
*/

void paintScoreBox(double time) {					//����


	int heigh = 15, width = 60;
	int i;
	//double duration;
	//duration = (double)(finish - first) / CLOCKS_PER_SEC;

	for (i = 100; i <= 100 + width; i = i + 2) {	//����������
		gotoxy(i, 20);
		printf("��");
		gotoxy(i, 35);
		printf("��");
	}
	gotoxy(100, 20);
	for (i = 20; i <= 35; i++) {	//����������
		gotoxy(100, i);
		printf("��");
		gotoxy(100 + width, i);
		printf("��");
	}
	gotoxy(125, 28);
	printf("������ʱ:%.4f",time);	//��ʾ��ǰ����
	gotoxy(125, 25);
	printf("�����ʱ:%.4f", readmaxScore());	//��ʾ��߷���
	gotoxy(0, 53);
	//printf("%f", duration);
}

/**
������߷ֽ��ļ�
*/
void storeScore(double score)
{
	FILE* fp;
	fopen_s(&fp, "score.txt", "w");//wд ����������ھʹ���
	fprintf(fp, "%lf\n", score);
	fclose(fp);
}
/**
��ӭ����
*/
void welcome() {
	//system("cls");
	int n, flag = 1;
	int i, j = 1;
	while (flag == 1) {
		gotoxy(43, 18);
		printf("�� �� �� ��");
		for (i = 20; i <= 26; i++)
		{
			for (j = 27; j <= 74; j++)
			{
				gotoxy(j, i);
				if (i == 20 || i == 26)
					printf("-");
				else if (j == 27 || j == 74)
					printf("|");
			}
		}
		gotoxy(35, 22);
		printf("1.��ʼ��Ϸ");
		gotoxy(50, 22);
		printf("2.��Ϸ˵��");
		gotoxy(35, 25);
		printf("3.�˳���Ϸ");

		gotoxy(29, 27);
		printf("��ѡ��[1,2,3]:[ ]\b\b");
		scanf_s("%d", &n);
		switch (n) {
		case 0:
			system("cls");
			createLine2();
			windowProgress2();
			flag = 0;
			break;
		case 1:
			system("cls");
			createLine();
			windowProgress();
			flag = 0;
			break;
		case 2:
			gotoxy(30, 30);
			printf("���������ζ�Ӧ�ĸ���λ:D F J K \n");
			gotoxy(35, 35);
			printf("����������˳�");
			if (_getch()) {
				system("cls");
				break;
			}

		case 3:
			exit(0);
			break;
		default:
			gotoxy(30, 30);
			printf("�������ݲ���������");
			gotoxy(35, 35);
			printf("	����������˳�!   ");
			if (_getch()) {
				system("cls");
				break;
			}

		}

	}

}

void rePlay() {
	int n;
	printf("���¿�ʼ��Ϸ����1����������Ϸ����2��,�������˵�����3����\n\n");
	scanf_s("%d", &n);
	switch (n) {
	case 1:
		system("cls");
		createLine();
		windowProgress();
		break;
	case 2:
		exit(0);
		break;
	case 3:
		system("cls");
		welcome();
		break;
	default:
		printf("��������");
		break;
	}
}
/**
���ڴ���		1.����ۼ� 2.�������� 3.���»��ƿ� 4.��������
*/
void  windowProgress() {
	int i, j;							//����λ������
	int tmp;
	int score = 0;						//����
	int key[4] = { 100,102,106,107 };
	int  bblock[4];						//�ĸ��ڿ��λ��


	srand((unsigned int)time(NULL));    //ʱ�����ӣ�����������õ�	

	randCreateBlock(bblock);			//������
	clock_t start,finish=0;
	double time;

	paintScoreBox(0);
	while (1)
	{
		
		tmp = bblock[3];
		if (_getch() == key[tmp])
		{
			score++;
			if (score == 1){
				start = clock();
			}
			if (score == 5) {
				finish = clock();
				time = (double)(finish - start) / CLK_TCK;
				gotoxy(0, 53);
			
				if (time < readmaxScore())
				{
					printf("��ϲ�㴴�¼�¼�ˣ�\n");
					storeScore(time);									
				}
				printf("%f", time);
				paintScoreBox(time);
				break;
			}
			for (j = 0; j < 4; j++)
			{
				cleanBlock(bblock[j], j);		//����ۼ�
			}

			for (i = 3; i >= 1; i--)
			{
				bblock[i] = bblock[i - 1];	   //���ݽ���
			}
			bblock[0] = rand() % 4;

			for (j = 0; j < 4; j++)		      //���»���
			{
				paintBlock(bblock[j], j);
			}
			gotoxy(0, 53);
		}
		else
		{	int n;
			printf("�����Ȱ׿�������\n\n");		
			rePlay();
		}
	}
	rePlay();


}


/*
���ڴ���2��ģʽ2�� 
*/
void windowProgress2(){
	int i, j;							//����λ������
	int tmp;
	int score = 0;						//����
	int key[4] = { 100,102,106,107 };
	int  bblock[5];						//�ĸ��ڿ��λ��


	srand((unsigned int)time(NULL));    //ʱ�����ӣ�����������õ�	

	randCreateBlock2(bblock);			//������



}
int main() {
	full_screen();
	system("color 70");		//���ñ���������ɫ 
	welcome();
	return 0;
}


