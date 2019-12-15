#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define  MaxHeigh 53		//5+12*4
#define  MaxWidth 88		//(10*4+5)*2
#define	 BlockWidth 10	//一个Block宽度为10
#define	 BlockHeigh 12	//一个Block高度为12

void  windowProgress();
void windowProgress2();
void rollBlock(int x, int y);
/**
定位坐标
*/
void gotoxy(int x, int  y) {
	//调用win32api设置光标位置
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(handle, coord);
}

/**
窗口最大化
*/
void full_screen()
{
	HWND hwnd = GetForegroundWindow();
	int cx = GetSystemMetrics(SM_CXSCREEN);            /* 屏幕宽度 像素 */
	int cy = GetSystemMetrics(SM_CYSCREEN);            /* 屏幕高度 像素 */

	LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);   /* 获取窗口信息 */
	/* 设置窗口信息 最大化 取消标题栏及边框 */
	SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);

	SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);
}



/**
画边框
*/
void createLine()
{
	int i, j;
	for (i = 0; i < MaxHeigh; i++)	//左右边框+中间
	{
		gotoxy(0, i);
		printf("□");
		gotoxy((MaxWidth) / 4, i);
		printf("□");
		gotoxy((MaxWidth) / 4 * 2, i);
		printf("□");
		gotoxy((MaxWidth) / 4 * 3, i);
		printf("□");
		gotoxy(MaxWidth, i);
		printf("□");
		printf("%d", i);						//行数标识
	}
	printf("\n");

	for (j = 2; j <= MaxWidth; j += 2)	//上下边框+中间边框
	{
		gotoxy(j, 0);
		printf("□");
		gotoxy(j, (MaxHeigh - 1) / 4);
		printf("□");
		gotoxy(j, (MaxHeigh - 1) / 4 * 2);
		printf("□");
		gotoxy(j, (MaxHeigh - 1) / 4 * 3);
		printf("□");
		gotoxy(j, MaxHeigh - 1);
		printf("□");

	}
	printf("\n");

}
/*
模式2边框
*/
void createLine2()
{
	int i, j;
	for (i = 0; i < MaxHeigh; i++)	//左右边框+中间
	{
		gotoxy(0, i);
		printf("□");
		gotoxy((MaxWidth) / 4, i);
		printf("□");
		gotoxy((MaxWidth) / 4 * 2, i);
		printf("□");
		gotoxy((MaxWidth) / 4 * 3, i);
		printf("□");
		gotoxy(MaxWidth, i);
		printf("□");
		printf("%d", i);						//行数标识
	}
	printf("\n");

	for (j = 2; j <= MaxWidth; j += 2)	//上下边框+中间边框
	{
		gotoxy(j, 0);
		printf("□");
		
		gotoxy(j, MaxHeigh - 1);
		printf("□");

	}
	printf("\n");

}
/**
设置颜色
*/

/**
生成方块
*/
void  paintBlock(int x, int y) {
	int  i, j;
	int  rx = (x * BlockWidth + x + 1) * 2;//加上线和前面的块才是真正的x坐标，并且一个方块（线）占两个字符
	int  ry = y * BlockHeigh + y + 1;

	for (j = ry; j <= ry + BlockHeigh - 1; j++)
	{
		for (i = rx; i <= rx + BlockWidth * 2 - 1; i = i + 2)
		{

			gotoxy(i, j);
			printf("■");
		}
	}
	gotoxy(0, 52);
}
	/**
	生成方块2
	*/
void  paintBlock2(int x){
	int  i,j;
	int haspaint = 0;
	int  rx = (x * BlockWidth + x + 1) * 2;//加上线和前面的块才是真正的x坐标，并且一个方块（线）占两个字符
	//int  ry = y * BlockHeigh + y + 1;	
	for (j = 1; j <= 12; j++) {
		Sleep(500);
		for (i = rx; i <= rx + BlockWidth * 2 - 1; i = i + 2)
			{
		
				gotoxy(i, j);
				printf("■");
				haspaint++;
				
			}
	}	
	
	rollBlock(x,j);//x是水平距离，y是底部方块所在的行数j=12
	gotoxy(0, 52);

}
/*
模式2的方块下落方式
*/
void rollBlock(int x, int y) {	//y=12
	int i;
	int  rx = (x * BlockWidth + x + 1) * 2;//加上线和前面的块才是真正的x坐标，并且一个方块（线）占两个字符
	int top = 1,bottom=y;

	while (bottom <= 51)
	{	
		Sleep(500);
		for (i = rx; i <= rx + BlockWidth * 2 - 1; i = i + 2)
			{
				gotoxy(i, top);
				printf("  ");
				
				gotoxy(i, bottom);
				printf("■");
				
			}
		top++; bottom++;
	}
			
		
}
/**
随机产生方块
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
随机产生方块2
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
清除上次的痕迹
*/
void cleanBlock(int x, int y) {

	int  i, j;

	int  rx = (x * BlockWidth + x + 1) * 2;//加上线和前面的块才是真正的x坐标，并且一个方块（线）占两个字符
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
监听键盘按键
*/
void listenKeyBoard() {
	if (_kbhit()) {
		char ch = _getch();
		printf("%c", ch);
		printf("%d", ch);
	}
}

/**
读取最高分数
*/
double readmaxScore() {
	double maxScore;
	FILE* fp;
	fopen_s(&fp, "score.txt", "r");//r+读写 ，如果不存在就创建
	fscanf_s(fp, "%lf", &maxScore);
	fclose(fp);
	return maxScore;
}

/**
绘制分数框
*/

void paintScoreBox(double time) {					//分数


	int heigh = 15, width = 60;
	int i;
	//double duration;
	//duration = (double)(finish - first) / CLOCKS_PER_SEC;

	for (i = 100; i <= 100 + width; i = i + 2) {	//分数框上下
		gotoxy(i, 20);
		printf("☆");
		gotoxy(i, 35);
		printf("☆");
	}
	gotoxy(100, 20);
	for (i = 20; i <= 35; i++) {	//分数框左右
		gotoxy(100, i);
		printf("☆");
		gotoxy(100 + width, i);
		printf("☆");
	}
	gotoxy(125, 28);
	printf("您的用时:%.4f",time);	//显示当前分数
	gotoxy(125, 25);
	printf("最短用时:%.4f", readmaxScore());	//显示最高分数
	gotoxy(0, 53);
	//printf("%f", duration);
}

/**
保存最高分进文件
*/
void storeScore(double score)
{
	FILE* fp;
	fopen_s(&fp, "score.txt", "w");//w写 ，如果不存在就创建
	fprintf(fp, "%lf\n", score);
	fclose(fp);
}
/**
欢迎界面
*/
void welcome() {
	//system("cls");
	int n, flag = 1;
	int i, j = 1;
	while (flag == 1) {
		gotoxy(43, 18);
		printf("别 踩 白 块");
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
		printf("1.开始游戏");
		gotoxy(50, 22);
		printf("2.游戏说明");
		gotoxy(35, 25);
		printf("3.退出游戏");

		gotoxy(29, 27);
		printf("请选择[1,2,3]:[ ]\b\b");
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
			printf("从左到右依次对应四个键位:D F J K \n");
			gotoxy(35, 35);
			printf("输入任意键退出");
			if (_getch()) {
				system("cls");
				break;
			}

		case 3:
			exit(0);
			break;
		default:
			gotoxy(30, 30);
			printf("输入数据不符合条件");
			gotoxy(35, 35);
			printf("	输入任意键退出!   ");
			if (_getch()) {
				system("cls");
				break;
			}

		}

	}

}

void rePlay() {
	int n;
	printf("重新开始游戏按“1”，结束游戏按“2”,返回主菜单按“3”！\n\n");
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
		printf("输入有误");
		break;
	}
}
/**
窗口处理		1.清除痕迹 2.交换数据 3.重新绘制块 4.按键下移
*/
void  windowProgress() {
	int i, j;							//方块位置向下
	int tmp;
	int score = 0;						//分数
	int key[4] = { 100,102,106,107 };
	int  bblock[4];						//四个黑块的位置


	srand((unsigned int)time(NULL));    //时间种子，设置随机数用的	

	randCreateBlock(bblock);			//产生块
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
					printf("恭喜你创新纪录了！\n");
					storeScore(time);									
				}
				printf("%f", time);
				paintScoreBox(time);
				break;
			}
			for (j = 0; j < 4; j++)
			{
				cleanBlock(bblock[j], j);		//清除痕迹
			}

			for (i = 3; i >= 1; i--)
			{
				bblock[i] = bblock[i - 1];	   //数据交换
			}
			bblock[0] = rand() % 4;

			for (j = 0; j < 4; j++)		      //重新绘制
			{
				paintBlock(bblock[j], j);
			}
			gotoxy(0, 53);
		}
		else
		{	int n;
			printf("叫你别踩白块啦！！\n\n");		
			rePlay();
		}
	}
	rePlay();


}


/*
窗口处理2（模式2） 
*/
void windowProgress2(){
	int i, j;							//方块位置向下
	int tmp;
	int score = 0;						//分数
	int key[4] = { 100,102,106,107 };
	int  bblock[5];						//四个黑块的位置


	srand((unsigned int)time(NULL));    //时间种子，设置随机数用的	

	randCreateBlock2(bblock);			//产生块



}
int main() {
	full_screen();
	system("color 70");		//设置背景，字颜色 
	welcome();
	return 0;
}


