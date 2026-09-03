#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses/ncurses.h>
#include <inttypes.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define MIN_Y 2
enum {LEFT=1,UP,RIGHT,DOWN,STOP_GAME=KEY_F(10)};
enum {MAX_TAIL_SIZE=100,START_TAIL_SIZE=20};  // , MAX_FOOD_SIZE=200, FOOD_EXPIRE_SECONDS=10

struct control_buttons
{
	int down;
	int up;
	int left;
	int right;
} controls;

//инициализация структуры, макросами ncurses
struct control_buttons controls = {KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT};

/*
 Хвост это массив состоящий из координат x,y
 */ 
 typedef struct tail_t {
	 int x;
	 int y;
} tail_t;

/* Голова змейки содержит в себе:
  x,y - координаты текущей позиции
  direction - направление движения
  tsize - размер хвоста
  *tail - указатель на хвост
 */ 
 
typedef struct snake_t 
{
	int x;
	int y;
	int direction;
	size_t tsize; 
	tail_t *tail;
	struct control_buttons controls;
} snake_t;


void initTail(tail_t t[], size_t size)
{
	tail_t init_t = {0,0};
	for (size_t i = 0; i < size; i++)
	{
		t[i] = init_t;
	}
}

void initHead(snake_t *head,int x, int y)
{
	head->x = x;
	head->y = y;
	head->direction = RIGHT;
}

void initSnake(snake_t *head, size_t size, int x, int y)
{
	tail_t *tail = (tail_t*)malloc(MAX_TAIL_SIZE * sizeof(tail_t));
	
	initTail(tail,MAX_TAIL_SIZE);
	initHead(head, x,y);
	head->tail = tail; // прикрепляем хвост к голове
	head->tsize = size+1;
	head->controls = controls;
}

void go(snake_t *head)
{
	char ch = '@';
	int max_x = 0, max_y = 0;
	getmaxyx(stdscr, max_y,max_x);
	
	mvprintw(head->y, head->x, " "); //очищаем один символ
	
	switch(head->direction)
	{
		case LEFT:
			if(head->x <=0) // Циклическое движение, чтобы не уходить за границы
				head->x = max_x;
			mvprintw(head->y, --(head->x), "%c", ch);
		break;
		case RIGHT:
			if(head->x >= max_x)
				head->x = 0;
			mvprintw(head->y, ++(head->x), "%c", ch);
		break;
		case UP:
			if(head->y <= MIN_Y)
				head->y = max_y;
			mvprintw(--(head->y), head->x, "%c", ch);
		break;
		case DOWN:
			if(head->y >= max_y)
				head->y = MIN_Y;
			mvprintw(++(head->y), head->x, "%c", ch);
		break;
		default:
		break;
	}
}

void goTail(snake_t *head)
{
	char ch = '*';
	mvprintw(head->tail[head->tsize-1].y,
			 head->tail[head->tsize-1].x," ");
	
	for (size_t i = head->tsize-1; i > 0; i--)
	{
		head->tail[i] = head->tail[i-1];
		if (head->tail[i].y || head->tail[i].x)
				mvprintw(head->tail[i].y, head->tail[i].x, "%c", ch);
	}
	head->tail[0].x = head->x;
	head->tail[0].y = head->y;
}

void changeDirection(snake_t *head, int key_pressed) 
{ 
	if (key_pressed == head->controls.down)        
	head->direction = DOWN; 
	else if (key_pressed == head->controls.up)        
	head->direction = UP; 
	else if (key_pressed == head->controls.right)        
	head->direction = RIGHT; 
	else if (key_pressed == head->controls.left)        
	head->direction = LEFT; 
}

int check_self_collision(snake_t *head)
{
	for (size_t i = head->tsize-1; i > 0; i--) 
	{
		if(head->tail[0].x == head->tail[i].x &&
		   head->tail[0].y == head->tail[i].y)
		   return 1;
		
	}
    return 0;
}

int main(int argc, char **argv)
{
	snake_t *snake = 
	(snake_t*)malloc(sizeof(snake_t));
	 
	initSnake(snake,START_TAIL_SIZE,10,10); 
	
	initscr(); 
	keypad(stdscr, TRUE); // Включаем F1, F2, стрелки и т.д. 
	raw();                // Отключаем line buffering 
	noecho();             // Отключаем echo() режим при вызове getch 
	curs_set(FALSE);      // Отключаем курсор 
	mvprintw(0, 0,"Use arrows for control. Press 'F10' for EXIT"); 
	timeout(0);           // Отключаем таймаут после нажатия клавиши в цикле
	int key_pressed=0; 
	while( key_pressed != STOP_GAME) 
	{ 
		key_pressed = getch();                 // Считываем клавишу 
		go(snake); 
		goTail(snake); 
		timeout(100);                          // Задержка при отрисовке 
		changeDirection(snake, key_pressed); 
		if (check_self_collision(snake))      //проверка на столкновение
			{
				key_pressed = STOP_GAME;
			}
	} 
	free(snake->tail); 
	free(snake); 
	endwin(); // Завершаем режим curses mod

    return 0;
}

