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



void move(){
	gotoxy(Y+1,X+1);
	printf("%c" , map[X][Y].data);
	int newX = map[X][Y].cx;
	int newY = map[X][Y].cy;
	X += newX;
	Y += newY;
	gotoxy(Y+1,X+1);
	printf("%c\b" , cPlayer);
	
}

void findStar(int maxX,int maxY){
	for(int i = 0;i < maxX;i++)
	for(int j = 0;j < maxY;j++)
	{
		if(map[i][j].data == cFruit)
		{
			star.x = i;
			star.y = j;
			return;
		}
	}
	
	star.x = -1; //No Star?
	star.y = -1;
}

void clearWay(int maxX,int maxY){
	for(int i = 0;i < maxX;i++)
	for(int j = 0;j < maxY;j++)
	{
		map[i][j].cx = -1;
		map[i][j].cy = -1;
		map[i][j].visited = false;
	}
}

bool checkEnd(int maxX,int maxY){
	if(map[X][Y].data==cFruit)
		{
			map[X][Y].data= cEmpty;
			findStar(maxX,maxY);
			if(star.x == -1) return true;
			clearWay(maxX,maxY);
			findWay(star.x,star.y,maxX,maxY);

		}
		return false;
}

int getKey(){
	int ch1, ch2;
	ch1 = getch();
	if(ch1 == 13)return enter;
	if(ch1 == 27)return esc;
	ch2 = 0;
	if (ch1 == 0xE0) {
		ch2 = getch();
		switch(ch2)
		{
			case 72: return up;
			case 80: return down;
			case 75: return left;
			case 77: return right;
			default:
			return getKey();
		};
	}
	else
	{
		return getKey();
	}
}

int menu(){
	int choose = 0;
	while(1)
	{
		system("@cls||clear");
		printf("Menu: \n");
		printf("_________________________\n");
		printf("| %c Auto Play           |\n" , choose == 0?'>':' ');
		printf("|_______________________|\n");
		printf("| %c Self Play           |\n" , choose == 1?'>':' ');
		printf("|_______________________|\n");
		printf("| %c Settings            |\n" , choose == 2?'>':' ');
		printf("|_______________________|\n");
		printf("| %c Exit                |\n" , choose == 3?'>':' ');
		printf("|_______________________|\n");
		while(1)
		{
			char ch = getKey();
			if(ch == up && choose != 0)
			{
				choose--;
				break;
			}
			if(ch == down && choose != 3)
			{
				choose++;
				break;
			}
			if(ch == enter)
			{
				return choose;
			}
			if(ch == esc)
			{
				return quit;
			}
			
		}
	}
}

void options(){
	int choose = 0;
	while(1)
	{
		system("@cls||clear");
		printf("Settings: \n");
		printf("__________________________\n");
		printf("| %c PacMan Character : %c |\n", choose == 0?'>':' ' , cPlayer);
		printf("|________________________|\n");
		printf("| %c Fruit Character :  %c |\n" , choose == 1?'>':' ' , cFruit);
		printf("|________________________|\n");
		printf("| %c Solid Wall         %c |\n" , choose == 2?'>':' ' , wall?'Y':'N');
		printf("|________________________|\n");
		printf("| %c Quit                 |\n" , choose == 3?'>':' ');
		printf("|________________________|\n");
		while(1)
		{
			char ch = getKey();
			if(ch == up && choose != 0)
			{
				choose--;
				break;
			}
			if(ch == down && choose != 3)
			{
				choose++;
				break;
			}
			if(ch == enter)
			{
				if(choose == 0)
				{
					fflush(stdin);
					system("@cls||clear");
					printf("Enter new character: ");
					scanf("%c" , &cPlayer);
					if(cPlayer == cEmpty || cPlayer == cBlock || cPlayer == cFruit)
					{
						printf("Error! %c has taken.", cPlayer);
						cFruit = '*';
						cPlayer = 'O';
					}
					fflush(stdin);
					break;
				}
				if(choose == 1)
				{
					fflush(stdin);
					system("@cls||clear");
					printf("Enter new character: ");
					scanf("%c" , &cFruit);
					if(cFruit == cEmpty || cFruit == cBlock || cPlayer == cFruit)
					{
						printf("Error! %c has taken.", cFruit);
						cFruit = '*';
						cPlayer = 'O';
					}
					fflush(stdin);
					break;
				}
				if (choose == 2)
				{
					wall = !wall;
					break;
				}
				if(choose == 3)return;
			}
			if(ch == esc)
			{
				return;
			}
			
		}
	}
}

void gotoxy(int eex, int eey)
{
  COORD coord;
  coord.X = eex;
  coord.Y = eey;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


int main(){
	while(1)
	{
		int choose = menu();
		if(choose == aiplay)
		{
			init_map(4,4);
			system("@cls||clear");
			printMap(4,4);
			sleep(1);
			findStar(4,4);
			findWay(star.x,star.y,4,4);
			while(1)
			{
				if(checkEnd(4,4)) break;
				move();
				sleep(1);
			}
		}
		if(choose == selfplay)
		{
			init_map(5,10);
			system("@cls||clear");
			printMap(5,10);
			while(1)
			{
				if(checkEnd(5,10)) break;
				int key = getKey();
				if(key == up)
				{
					if(X == 0 && !wall && map[4][Y].data != cBlock)
						X = 4;
					else if(X != 0 && map[X-1][Y].data != cBlock) 
					{
						gotoxy(Y+1,X+1);
						printf("%c" , map[X][Y].data);
						X--;
						gotoxy(Y+1,X+1);
						printf("%c\b" , cPlayer);
					}
				}
				if(key == down)
				{
					if(X == 4 && !wall && map[0][Y].data != cBlock)
						X = 0;
					else if(X != 4 && map[X+1][Y].data != cBlock) 
					{
						gotoxy(Y+1,X+1);
						printf("%c" , map[X][Y].data);
						X++;
						gotoxy(Y+1,X+1);
						printf("%c\b" , cPlayer);
					}
				}
				if(key == right)
				{
					if(Y == 9 && !wall  && map[X][0].data != cBlock)
						Y = 0;
					else if(Y != 9 && map[X][Y+1].data != cBlock) 
					{
						gotoxy(Y+1,X+1);
						printf("%c" , map[X][Y].data);
						Y++;
						gotoxy(Y+1,X+1);
						printf("%c\b" , cPlayer);
					}
				}
				if(key == left)
				{
					if(Y == 0 && !wall && map[X][9].data != cBlock)
						Y = 9;
					else if(Y != 0 && map[X][Y-1].data != cBlock)
					{
						gotoxy(Y+1,X+1);
						printf("%c" , map[X][Y].data);
						Y--;
						gotoxy(Y+1,X+1);
						printf("%c\b" , cPlayer);
					}
				}
				if(key == esc)
				{
					break;
				}
				
			}
		}
		if(choose == settings)
		{
			options();
		}
		if(choose == quit)
		{
			exit(0);
		}
	}
	
}
