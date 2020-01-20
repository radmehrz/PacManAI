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
