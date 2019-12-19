#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <math.h>

#define  MaxHeigh 53		//5+12*4
#define  MaxWidth 88		//(10*4+5)*2
#define	 BlockWidth 10		//一个Block宽度为10
#define	 BlockHeigh 12		//一个Block高度为12

void windowProgress();
void windowProgress2();

/**
定义隐藏光标函数
*/
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = FALSE;
	cursor.dwSize = sizeof(cursor);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &cursor);
}

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
设置红颜色
*/
void setRed() {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, FOREGROUND_RED + 7 * 0x10);//FOREGROUND_INTENSITY |
}


/**
设置颜色
*/
void setWhite() {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 0 + 7 * 0x10);
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

	for (j = 2; j < MaxWidth; j += 2)	//黄线区间：识别区
	{
		setRed();
		gotoxy(j, 26);
		printf("■");

		gotoxy(j,39);
		printf("■");

	}
	setWhite();
	printf("\n");

}


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
生成方块1
*/
void  paintBlock1(int x, int y) {
	int  i, j;
	int  rx = (x * BlockWidth + x + 1) * 2;//加上线和前面的块才是真正的x坐标，并且一个方块（线）占两个字符
	int  ry = y * 6 + y + 1;

	for (j = ry; j <= ry + 6 - 1; j++)
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
double readmaxScore(int mod) {
	double maxScore;
	FILE *fp=NULL;
	if (mod == 1) 
	{
		fopen_s(&fp, "score.txt", "r");//r+读写 ，如果不存在就创建		
	}
	else if(mod == 2)
	{
		fopen_s(&fp, "score2.txt", "r");//r+读写 ，如果不存在就创建		
	}
	fscanf_s(fp, "%lf", &maxScore);
	fclose(fp);
	return maxScore;
}

/**
绘制分数框
*/
void paintScoreBox(double result,int mod) {					//分数


	int heigh = 35, width = 60;
	int i;

	for (i = 100; i <= 100 + width; i = i + 2) {	//分数框上下
		gotoxy(i, 1);
		printf("☆");
		gotoxy(i, 35);
		printf("☆");
	}
	gotoxy(100, 20);
	for (i = 1; i <= 35; i++) {	//分数框左右
		gotoxy(100, i);
		printf("☆");
		gotoxy(100 + width, i);
		printf("☆");
	}
	if (mod == 1) {
		gotoxy(120, 10);
		printf("您的用时:%.4fs", result);	//显示当前分数
		gotoxy(120, 5);
		printf("最短用时:%.4fs", readmaxScore(mod));	//显示最高分数
		
	}
	else if(mod == 2) {
		gotoxy(120, 10);
		printf("您的命中率:%.2f%%", result*100);	//显示当前分数
		gotoxy(120, 5);
		printf("最好记录:%.2f%%", readmaxScore(mod)*100);	//显示最高分数
		
	}
	gotoxy(110, 18);
	printf("键位提示 D F J K 空格键暂停 ESC停止游戏");
	gotoxy(110, 19);
	printf("红色区间内为识别区");
	gotoxy(0, 53);
}

/**
保存最高分进文件
*/
void storeScore(double score,int mod)
{
	FILE* fp;
	if (mod == 1) {
		fopen_s(&fp, "score.txt", "w");//w写 ，如果不存在就创建
		fprintf(fp, "%lf\n", score);
		fclose(fp);
	}
	else if (mod == 2)
	{
		fopen_s(&fp, "score2.txt", "w");//w写 ，如果不存在就创建
		fprintf(fp, "%lf\n", score);
		fclose(fp);
	}
	
}

/**
欢迎界面
*/
void welcome() {
	//system("cls");
	int n, m, flag = 1;
	int i, j = 1;
	int k = 1;
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
		case 1:
			/*
			模式界面选择
			*/
			while (k==1) {
			system("cls");
				//printf("")
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
					gotoxy(43, 18);
					printf("模式选择");
					gotoxy(35, 22);
					printf("1.时间模式");
					gotoxy(50, 22);
					printf("2.无尽模式");
					gotoxy(35, 25);
					printf("3.返回主菜单");
					gotoxy(29, 27);
					printf("请选择[1,2,3]:[ ]\b\b");
					scanf_s("%d", &m);
			
					switch (m)
					{
						case 1:
							system("cls");
							createLine();
							windowProgress();
							k = 0;
							break;
						case 2:
							system("cls");
							createLine2();
							windowProgress2();
							k = 0;
							break;
						case 3:
							welcome();
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
			flag = 0;
			break;
		case 2:
			gotoxy(30, 30);
			printf("从左到右依次对应四个键位:D F J K \n");
			gotoxy(30, 33);
			printf("游戏模式分两种:\n");
			gotoxy(30, 34);
			printf("1.冲刺模式：完成一定数量后得出时间作为成绩。2.无尽模式：不限时间以数量作为成绩。");
			gotoxy(35, 40);
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

/**
重玩
*/
void rePlay(int mod) {
		int n;
		printf("重新开始游戏按“1”，结束游戏按“2”,返回主菜单按“3”！\n\n");
		Sleep(1000);
		scanf_s("%d", &n);
		if(mod==1)
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
				printf("输入有误,请重新输入");
				break;
		}
		else if (mod == 2) {
			switch (n) {
			case 1:
				system("cls");
				createLine2();
				windowProgress2();
				break;
			case 2:
				exit(0);
				break;
			case 3:
				system("cls");
				welcome();
				break;
			default:
				printf("输入有误,请重新输入");
				break;
			}
		}
	
}

/**
提示WRONG
*/
void printWrong() {
	setRed();
	gotoxy(100, 40);
	printf("                       XXXX              XXXX     \n");
	gotoxy(100, 41);
	printf("                         XXXX          XXXX            \n");
	gotoxy(100, 42);
	printf("                           XXXX      XXXX           \n");
	gotoxy(100, 43);
	printf("                             XXXX  XXXX          \n");
	gotoxy(100, 44);
	printf("                               XXXXXX                      \n");
	gotoxy(100, 45);
	printf("                             XXXX  XXXX			\n");
	gotoxy(100, 46);
	printf("                           XXXX      XXXX \n");
	gotoxy(100, 47);
	printf("                         XXXX          XXXX\n");
	gotoxy(100, 48);
	printf("                       XXXX              XXXX\n");
	setWhite();
}


/**
提示MISS
*/
void printMiss() {
	setRed();
	gotoxy(100, 40);
	printf("MMMMMMMMMMMMM	IIIIIIIIIII           SSSSSSS               SSSSSSS            \n");
	gotoxy(100, 41);
	printf("MM   MM    MM	    III             SSS      SSS          SSS      SSS         \n");
	gotoxy(100, 42);
	printf("MM   MM    MM	    III               SSS                   SSS                \n");
	gotoxy(100, 43);
	printf("MM   MM    MM	    III                 SSSS                  SSSS             \n");
	gotoxy(100, 44);
	printf("MM   MM    MM	    III                   SSSS                  SSSS           \n");
	gotoxy(100, 45);
	printf("MM   MM    MM	    III             SSSS       SSS        SSSS       SSS       \n");
	gotoxy(100, 46);
	printf("MM   MM    MM	    III              SSSS     SSSS         SSSS     SSSS       \n");
	gotoxy(100, 47);
	printf("MM   MM    MM	IIIIIIIIIII              SSSSSS                SSSSSS          \n");
	setWhite();
}

/**
清除提示信息
*/
void cleanTips() {
	gotoxy(100, 40);
	printf("                                                                                 \n");
	gotoxy(100, 41);																	     
	printf("                                                                                 \n");
	gotoxy(100, 42);																	     
	printf("                                                                                 \n");
	gotoxy(100, 43);																	     
	printf("                                                                                 \n");
	gotoxy(100, 44);																	     
	printf("                                                                                 \n");
	gotoxy(100, 45);																	     
	printf("                                                                                 \n");
	gotoxy(100, 46);																	     
	printf("                                                                                 \n");
	gotoxy(100, 47);																	     
	printf("                                                                                 \n");
	gotoxy(100, 48);
	printf("                                                                                 \n");
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

	paintScoreBox(0,1);
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
				if (time < readmaxScore(1))
				{	
					
					printf("恭喜你创新纪录了！\n");
					storeScore(time,1);									
				}
				printf("%f", time);
				paintScoreBox(time,1);
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
		{	
			int n;
			printf("叫你别踩白块啦！！\n\n");		
			rePlay(1);
		}
	}
	rePlay(1);
}

/*
窗口处理2（模式2） 	
*/
void windowProgress2(){
	int i, j;							//方块位置向下
	int tmp;
	int count = 0,score=0;						//计数器
	int key[4] = { 100,102,106,107 };
	int  bblock[4];						//四个黑块的位置
	int speed = 500;
	int	flag = 1;
	int ch;
	double persent;
	srand((unsigned int)time(NULL));    //时间种子，设置随机数用的	
	randCreateBlock(bblock);			//产生块
	clock_t start, finish = 0;
	double time;

	paintScoreBox(0,2);
	tmp = bblock[3];
	if (_getch() == key[tmp])	//触发开始游戏
	{			
		while (flag)
		{	
		if (score == 100)
					flag=0;
		   if (score>=10&&score % 10 == 0&&speed>150)		//速度控制
		   	speed =speed -50;
		   else if(score >= 10 && score % 10 == 0 && speed > 125)
			 speed = speed - 25;
		   Sleep(speed);	  
		   for (j = 0; j < 4; j++)
		   {
		   	cleanBlock(bblock[j], j);		//清除痕迹
		   }
		   
		   for (i = 3; i >= 1; i--)
		   {
		   	bblock[i] = bblock[i - 1];	   //数据交换
		   }
		   
		   bblock[0] = rand() % 4;
		   if (_kbhit())
		   {	
			   cleanTips();
			   ch = _getch();
			   if (  ch == key[bblock[3]])			//判断是否命中ch == key[bblock[2]]||
			   {
				   score++;
				   gotoxy(100, 50);
				   printf("%d %d", ch, score);
			   }
			   else 
			   {	
				   cleanTips();
				   printWrong();
			   }
			   if (ch == 27)
			   {	   				   
				  break;			//停止
			   }
			   if (ch == 32)		//暂停
			   {	
				   for (j = 0; j < 4; j++)		 //重新绘制
				   {
					   paintBlock(bblock[j], j);
				   }
				   gotoxy(0, 53);
				   printf("已 暂 停, 输 入 任 意 键 开 始......");		//暂停
				   _getch();
				   gotoxy(0, 53);
				   printf("                    ");				   
				}
		   }
		   else 
		   {	
			   cleanTips();
			   printMiss();//如果没有按下就会MISS
		   }
		   for (j = 0; j < 4; j++)		 //重新绘制
		   {
		   	paintBlock(bblock[j], j);
		   }
		   count++;
		   persent = score / (double)count;
		   paintScoreBox(persent, 2);
		}	
		gotoxy(0, 54);
		if( persent > readmaxScore(2))
		{
			storeScore(persent,2);//写入
			printf("恭喜你破纪录啦！！！");
		}	
		paintScoreBox(persent, 2);
		printf("游戏结束！\n");
		rePlay(2);
	}
	else
	{
		rePlay(2);
	}
	gotoxy(0, 53);
}


int main() {
	full_screen();
	HideCursor();
	system("color 70");		//设置背景，字颜色 
	welcome();
	return 0;
}


