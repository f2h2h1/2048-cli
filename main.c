/**
 * 
 */
#include<stdio.h>
#include<time.h>//获取随机数种子函数
#include<stdlib.h>
#include<WINDOWS.H>//引用控制台变量，获取系统时间等函数
int array[4][4]={{0},{0}};//游戏主界面变量数组
int randNum(int num);//生成一个随机数，参数指定随机数范围（<num）
int randDete();//在行列式的空白区域添加一个随机数（2或4）
int randChange();//随机产生2或4的随机数（可以改变生成2或者4的概率）
void printf_array();//输出游戏主界面
int repeat_judge();//判断行列式位置是否还有空白，判断游戏结束
void right_move();//向右移动操作
void right_move_compare();//判断右移时相同数字是否相邻
void right_move_zero();//右移操作中移动零位，是有效数据居于行列式同侧
void left_move();//向左移动操作
void left_move_compare();//判断左移时相同数字是否相邻
void left_move_zero();//左移操作中移动零位，是有效数据居于行列式同侧
void down_move();//向下移动操作，相当于转置行列式后向右移动
void up_move();//向上移动操作，相当于转置行列式后向左移动
/*
定义上下左右方向常量
 */
#define UP 72  
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ESC 27
SYSTEMTIME sys;//获取系统时间
int is_moved;//标志变量，指示是否移动过
int main(){
	//
/*	int m;
	m=getch();
    while(m){
	m=getch();
	printf("%d\n",m);

	}*/
	int temp=0, i,j;//以下所有代码，I表示行，j表示列
	/*获取控制台光标，并隐藏*/
	CONSOLE_CURSOR_INFO cci;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;

	system("color 5F");//改变控制台窗口背景色和文字颜色
	system("mode con cols=30 lines=11");//定义控制台窗口大小

	randDete();
	randDete();
    cci.bVisible = FALSE;//隐藏输入光标
	cci.dwSize = sizeof(cci);	
    SetConsoleCursorInfo(handle, &cci);
	printf_array();
	/*游戏主要消息循环*/
	while(1){
		temp=getch();//等待用户按下键操作
		system("cls");
		printf_array();
		is_moved=0;
		/*判断输入是或否合法*/
		if(temp!=UP&&temp!=DOWN&&temp!=LEFT&&temp!=RIGHT&&temp!=ESC)
			//printf_array();
			continue;
		else{
		/*方向键主要操作*/
		if(temp==RIGHT){
		
					right_move();
				if(is_moved==1){
						randDete();
					}
					
					printf_array();
					printf("\n");

		}
		if(temp==DOWN){
		
					down_move();
					if(is_moved==1){
						randDete();
					}
					printf_array();
					printf("\n");
		}
		if(temp==LEFT){
			left_move();
			if(is_moved==1){
				randDete();
					}
			printf_array();
			printf("\n");
		}
		if(temp==UP){
			up_move();
			if(is_moved==1){
				randDete();
			}
			printf_array();
			printf("\n");
		}
	/*使用ESC键重置游戏*/
		if(temp==ESC){
			for (i=0;i<4;i++)
			{
				for (j=0;j<4;j++)
				{
					array[i][j]=0;
				}
			}
			randDete();
			randDete();
			printf_array();
			printf("\n");
		}
	}
	}
	return 0;
}
void printf_array(){
	int i,j;
	printf("\t瞎写的2048Ver0.2\t\n");
	for(i=0;i<4;i++){
	    for(j=0;j<4;j++){
		   if (array[i][j]==0)
		   {
			   printf("¡ö\t",array[i][j]);
		   }
		   else
				printf("%d\t",array[i][j]);
		}
		printf("\n");
	}
}
int randNum(int num){
    int randfing;
	//Sleep(100);
	///*
	//这里有问题，由于使用的随机数表并不随机，毫秒单位的时间种子也不能保证每个位置均匀出现，空格较少时无法命中导致游戏卡顿
	//srand((unsigned int)time(NULL));可以考虑使用这个获取时间种子，相对均匀，但是效率很低，需要用sleep矫正
	//*/
	GetLocalTime(&sys);//获取系统时间
	srand(sys.wMilliseconds);//使用毫秒单位的时间种子生成随机数表
    randfing=rand()%num;
	return randfing;
}
int randDete(){
	int randRow=0,randCol=0,mak=0;
	randRow=randNum(4);
    randCol=randNum(4);
	while(array[randRow][randCol]!=0){
       	randRow=randNum(4);
        randCol=randNum(4);
		if(repeat_judge()==1){ 
			printf("game over!!\n");
			exit(0);
	}
		
	}
	array[randRow][randCol]=randChange();
	return 0;
}
int randChange(){
    int randC;
	randC=randNum(5);
	if(randC==0||randC==2||randC==4)
		return 2;
	else
		return 4;
}
int repeat_judge(){
	int i,j;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(array[i][j]==0)
				return 0;
		}
	}
	return 1;
}
//ÏòÓÒÒÆ
void right_move(){
	right_move_zero();
	right_move_compare();
	right_move_zero();
}
void right_move_zero(){
	int i,j,k,array_s=0;
	for(k=0;k<3;k++){
		for(i=0;i<4;i++){
			for(j=3;j!=0;j--){
				if(array[i][j]==0){
					if(array[i][j-1]==0)
						continue;
					else{
						array_s=array[i][j];
						array[i][j]=array[i][j-1];
						array[i][j-1]=array_s;
						is_moved=1;
					}
				} 
				else
					continue;
			}
		}
	}
}

void right_move_compare(){
	int i,j;
	for(i=0;i<4;i++){
		for(j=3;j!=0;j--){
			if(array[i][j]==array[i][j-1]){
				array[i][j]=2*array[i][j];
				array[i][j-1]=0;
				is_moved=1;
			}
			else
				continue;
		}
	}
}
//ÏòÏÂÒÆ
void down_move(){
	int i,j,array_s=0;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(i==j)
				break;
			else{
			array_s=array[i][j];
			array[i][j]=array[j][i];
			array[j][i]=array_s;}
		}
	}
	right_move_zero();
	right_move_compare();
	right_move_zero();
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(i==j)
				break;
			else{
			array_s=array[i][j];
			array[i][j]=array[j][i];
			array[j][i]=array_s;}
		}
	}
}
//Ïò×óÒÆ
void left_move(){
	left_move_zero();
	left_move_compare();
	left_move_zero();
}
void left_move_compare(){
	int i,j;
	for(i=0;i<4;i++){
		for(j=0;j<3;j++){
			if(array[i][j]==array[i][j+1]){
				array[i][j]=2*array[i][j];
				array[i][j+1]=0;
				is_moved=1;
			}
			else
				continue;
		}
	}
}
void left_move_zero(){
	int i,j,k,array_s=0;
	for(k=0;k<3;k++){
		for(i=0;i<4;i++){
			for(j=0;j<3;j++){
				if(array[i][j]==0){
					if(array[i][j+1]==0)
						continue;
					else{
						array_s=array[i][j];
						array[i][j]=array[i][j+1];
						array[i][j+1]=array_s;
						is_moved=1;
					}
				} 
				else
					continue;
			}
		}
	}
}
//ÏòÉÏÒÆ
void up_move(){
	int i,j,array_s=0;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(i==j)
				break;
			else{
			array_s=array[i][j];
			array[i][j]=array[j][i];
			array[j][i]=array_s;}
		}
	}
	left_move_zero();
	left_move_compare();
	left_move_zero();
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(i==j)
				break;
			else{
			array_s=array[i][j];
			array[i][j]=array[j][i];
			array[j][i]=array_s;}
		}
	}
}

