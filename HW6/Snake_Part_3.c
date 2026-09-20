#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses/ncurses.h>
#include <inttypes.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define MIN_Y 2
#define CONTROLS 2
#define PLAYERS 2
enum {LEFT=1,UP,RIGHT,DOWN,STOP_GAME=KEY_F(10)};
enum {MAX_TAIL_SIZE=100,START_TAIL_SIZE=20, MAX_FOOD_SIZE=200 , FOOD_EXPIRE_SECONDS=10, SEED_NUMBER=5};

/*
 * Добавить блокировки движения назад (вхождение саму в себя) -changeDirection - DONE!
 * Добавить:
 * вторая змейка - DONE!
 * автопилот - DONE!
 * управление 2-й змейки автопилотом - DONE!
 * все функции перенести из main в update - DONE!
 */

struct control_buttons
{
	int up;
	int down;
	int left;
	int right;
};

//инициализация структуры, макросами ncurses
struct control_buttons default_controls[CONTROLS] = 
{
	{
		KEY_UP, 
		KEY_DOWN, 
		KEY_LEFT, 
		KEY_RIGHT
	},
	{
		'w',
		's',
		'a',
		'd'
	}
};






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

struct food
{
	int x;
	int y;
	time_t put_time;
	char point;
	uint8_t enable;
} food[MAX_FOOD_SIZE];


void initFood(struct food *f)
{
	struct food init = {0,MIN_Y,0,0,0};
	for (size_t i = 0; i < MAX_FOOD_SIZE; i++)
	{
		f[i] = init;
	}
	
}

void putSeed(struct food *f)
{
	int max_x=0, max_y=0;
	
	char sp[2] = {0};
	getmaxyx(stdscr, max_y, max_x);
	mvprintw(f->y,f->x," ");
	f->x = rand() % (max_x - 1);
	f->y = rand() % (max_y - MIN_Y)+1;
	f->put_time = time(NULL);
	f->point = 'O';
	f->enable = 1;
	sp[0] = f->point;
	mvprintw(f->y,f->x, "%s", sp);
}

void putFood(struct food *f)
{
	for (size_t i = 0; i < SEED_NUMBER; i++)
	{
		putSeed(&f[i]);
	}
}

void refreshFood(struct food *f)
{
	for (size_t i = 0; i < SEED_NUMBER; i++)
	{
		if ((f[i].put_time) != 0)
		{
			if (!f[i].enable || (time(NULL) - f[i].put_time) > FOOD_EXPIRE_SECONDS)
			{
				putSeed(&f[i]);
			}
		}
	}
}



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

void initSnake(snake_t *head[], size_t size, int x, int y, int i)
{
	head[i] = (snake_t*)malloc(sizeof(snake_t));
	tail_t *tail = (tail_t*)malloc(MAX_TAIL_SIZE * sizeof(tail_t));
	
	initTail(tail,MAX_TAIL_SIZE);
	initHead(head[i], x,y);
	head[i]->tail = tail; // прикрепляем хвост к голове
	head[i]->tsize = size+1;
	//head[i]->default_controls = controls;
	head[i]->controls = default_controls[i];
}

_Bool haveEat(struct snake_t *head, struct food *f)
{
	// написать
	if (f->x == head->tail->x && f->y == head->tail->y)
	{
			return 1;
	}
	else
	{
		return 0;
	}
}

void addTail(struct snake_t *head)
{
	//написать
	if (head->tsize != MAX_TAIL_SIZE)
	{
		(head->tsize)++;
	}
	
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

_Bool checkDirection(snake_t* head, int key_pressed)
{
		if(head->direction == RIGHT && 
		key_pressed == head->controls.left)
		{
			return 0;
		}
		else if(head->direction == UP && 
		key_pressed == head->controls.down)
		{
			return 0;
		}
		else if(head->direction == LEFT && 
		key_pressed == head->controls.right)
		{
			return 0;
		}
		else if(head->direction == DOWN && 
		key_pressed == head->controls.up)
		{
			return 0;
		}
	return 1;
}

void changeDirection(snake_t *head, int key_pressed) 
{ 
	
	if (key_pressed == head->controls.up)        
		{
			head->direction = UP; 
		}
	else if (key_pressed == head->controls.down)        
		{
			head->direction = DOWN;
		}
	else if (key_pressed == head->controls.left)        
		{
			head->direction = LEFT;
		}
	else if (key_pressed == head->controls.right)        
		{
			head->direction = RIGHT; 
		}
}


_Bool isCrush(snake_t *head)
{
	for (size_t i = head->tsize-1; i > 0; i--) 
	{
		if(head->tail[0].x == head->tail[i].x &&
		   head->tail[0].y == head->tail[i].y)
		   return 0; // return 1, чтобы игра заканчивалась, при пересечении головы с хвостом
		
	}
    return 0;
}

void repairSeed(struct food *f, struct snake_t *head)
{
	for (size_t i = 0; i < head->tsize; i++)
	{
		for (size_t j = 0; j < SEED_NUMBER; j++)
		{
			// Если хвост совпадает с зерном
			if (f[i].x == head->tail[j].x && f[i].y == head->tail[j].y)
			{
				addTail(head);
			}
		}
	}
	for (size_t i = 0; i < SEED_NUMBER; i++)
	{
		for (size_t j = 0; j < SEED_NUMBER; j++)
		{
			// Если два зерна на одной точке
			if(f[i].x == f[j].x && f[i].y == f[j].y)
			{
				f[j].enable = 0;
			}
		}
	}
}

int distance(const snake_t snake, const struct food f)
{
	return (abs(snake.x - f.x) + abs(snake.y - f.y));
}

void autoChangeDirection(snake_t *snake, struct food *f, int foodSize)
{
	int pointer = 0;
	for (int i = 1; i < foodSize; i++)
	{
			pointer = (distance(*snake, f[i]) < distance(*snake,f[pointer])) ? i :
		pointer;
	}
	if ((snake->direction == RIGHT || snake->direction == LEFT) &&
	   (snake->y != f[pointer].y)) 
	{
		snake->direction = (f[pointer].y > snake->y) ? DOWN : UP;
	}
	else if ((snake->direction == DOWN || snake->direction == UP) &&
	   (snake->x != f[pointer].x)) 
	{
		snake->direction = (f[pointer].x > snake->x) ? RIGHT : LEFT;
	}
}



void update(struct snake_t *head, struct food *f, int key_pressed, int apil)
{	
	if (apil)
	{
		autoChangeDirection(head, f, SEED_NUMBER);
	}
	else
	{
		if (checkDirection(head, key_pressed))
		{
		changeDirection(head,key_pressed);
		}
	}
	go(head);
	goTail(head);
	timeout(100);
	refreshFood(f);
	if (haveEat(head,f))
	{
		addTail(head);
	}

}

int main(int argc, char **argv)
{
	snake_t *snake[PLAYERS];
	 
	for (int i = 0; i < PLAYERS; i++)
	{
		initSnake(snake,START_TAIL_SIZE,10+i*10,10+i*10,i); 
	}
	
	
	struct food *f = 
	malloc(MAX_FOOD_SIZE *sizeof(*f));
	

	
	initscr(); 
	keypad(stdscr, TRUE); // Включаем F1, F2, стрелки и т.д. 
	raw();                // Отключаем line buffering 
	noecho();             // Отключаем echo() режим при вызове getch 
	curs_set(FALSE);      // Отключаем курсор 
	mvprintw(0, 0,"Use arrows for control. Press 'F10' for EXIT"); 
	timeout(0);           // Отключаем таймаут после нажатия клавиши в цикле
	
	initFood(f);
	putFood(f);
	
	int key_pressed=0;  
	while( key_pressed != STOP_GAME) 
	{ 
		key_pressed = getch();                 // Считываем клавишу 
		
		for (int i = 0; i < PLAYERS; i++)
		{
			int apil = (i == 0);
			update(snake[i], f, key_pressed, apil);
			if(isCrush(snake[i]))
				break;
			//repairSeed(f, snake[i]);
		}
		
	} 
	for (int i = 0; i < PLAYERS; i++)
	{
		//printExit(snake[i]);
		free(snake[i]->tail); 
		free(snake[i]);
	}
	 
	free(f);
	endwin(); // Завершаем режим curses mod

    return 0;
}

