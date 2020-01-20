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
