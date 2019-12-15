#include<stdio.h>
int main(){
	double maxScore; 
	FILE* fp;
	fopen("score.txt", "r");//r+读写 ，如果不存在就创建
	fscanf(fp, "%f", &maxScore);
	
	
	printf("%.4f",maxScore);
} 
	
