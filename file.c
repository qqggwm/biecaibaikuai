#include<stdio.h>
int main(){
	double maxScore; 
	FILE* fp;
	fopen("score.txt", "r");//r+��д ����������ھʹ���
	fscanf(fp, "%f", &maxScore);
	
	
	printf("%.4f",maxScore);
} 
	
