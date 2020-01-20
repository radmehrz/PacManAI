#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#define endl printf("\n");
#define forfor(X) for(int i = 0;i < X;i++)for(int j=0;j < X;j++)
#define fore(X) for(int i = 0;i < X;i++)

char cPlayer = 'O';
char cEmpty = ' ';
char cBlock = '#';
char cFruit = '*';
bool wall = true;


typedef struct point{
	int cx;
	int cy;
	bool visited;
	char data;
}point;

typedef struct star{
	int x;
	int y;
}Star;



enum key{up,down,left,right,enter,esc};
enum option{aiplay,selfplay,settings,quit};

point map[5][10];
int X;
int Y;
Star star; 

void init_map(int maxX, int maxY){
	char temp;
	FILE *fptr;
	char filedir[200];
	printf("Enter file directory: ");
	scanf("%s" , filedir);
	fptr = fopen(filedir,"r");
	while(fptr == NULL)
	{
		printf("Enter file directory: ");
		scanf("%s" , filedir);
		fptr = fopen(filedir,"r");
	}
	for(int i = 0;i < maxX;i++)
	for(int j = 0;j < maxY;j++)
	{
		while ((temp = getc(fptr)) != EOF)
		{
			if(temp == '0')
			{
				map[i][j].data=cEmpty;
				X = i;
				Y = j;
				break;
			}
			else if(temp == '1')
			{
				map[i][j].data= cEmpty;
				break;
			}
			else if(temp == '#')
			{
				map[i][j].data= cBlock;
				break;
			}
			else if(temp == '*')
			{
				map[i][j].data= cFruit;
				break;
			}
			else continue;
		}
		
		map[i][j].cx = -1;
		map[i][j].cy = -1;
		map[i][j].visited = false;
	}
	fclose(fptr);
}

void printMap(int x , int y){
	fore(y)printf("_");printf("__\n");
	for(int i = 0;i < x;i++)
	{
		printf("|");
		for(int j = 0;j < y;j++)
		{
			if(i == X && j == Y)printf("%c" , cPlayer);
			else
			printf("%c" , map[i][j].data);
			
		}
		printf("|");
		endl
	}
	printf("|");fore(y)printf("_");printf("|");
	endl
}

void findWay(int startX, int startY , int maxX , int maxY){
	if(map[startX+1][startY].data!=cBlock &&!map[startX+1][startY].visited && startX != maxX-1)
	{
		map[startX+1][startY].visited = true;
		map[startX+1][startY].cx = -1;
		map[startX+1][startY].cy = 0;
		findWay(startX+1,startY,maxX,maxY);
	}
	if(map[startX-1][startY].data != cBlock &&!map[startX-1][startY].visited && startX != 0)
	{
		map[startX-1][startY].visited = true;
		map[startX-1][startY].cx = 1;
		map[startX-1][startY].cy = 0;
		findWay(startX-1,startY,maxX,maxY);
	}
	if(map[startX][startY-1].data != cBlock &&!map[startX][startY-1].visited && startY != 0)
	{
		map[startX][startY-1].visited = true;
		map[startX][startY-1].cx = 0;
		map[startX][startY-1].cy = +1;
		findWay(startX,startY-1,maxX,maxY);
	}
	if(map[startX][startY+1].data != cBlock &&!map[startX][startY+1].visited && startY != maxY-1)
	{
		map[startX][startY+1].visited = true;
		map[startX][startY+1].cx = 0;
		map[startX][startY+1].cy = -1;
		findWay(startX,startY+1,maxX,maxY);
	}
}

