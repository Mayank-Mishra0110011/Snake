#include <iostream.h>
#include <conio.h>
#include <stdlib.h>
#include <dos.h>

typedef struct snake {
	int x;
	int y;
	snake *front;
	snake *back;
} snake;

typedef struct fruit {
	int x;
	int y;
} fruit;

void layout();
int wallcollision();
void drawsnake();
void drawfruit(fruit&);
void changedir(char);
void update();
void gameloop();
void setfruit(fruit&);
int fruitcollision(fruit&);
void increasesnake();
snake *head = NULL;
snake *tail = NULL;
int xvel = 1, timer = 0, yvel = 0;

int main() {
	clrscr();
	layout();
	gameloop();
	clrscr();
	gotoxy(35, 12);
	cout << "YOU LOOSE!!";
	getch();
	return 0;
}

void gameloop() {
	snake *ptr = new snake;
	fruit f;
	ptr->x = 40;
	ptr->y = 12;
	ptr->front = NULL;
	ptr->back = NULL;
	head = ptr;
	tail = ptr;
	setfruit(f);
	char key;
	while (wallcollision() == 0) {
		clrscr();
		layout();
		drawfruit(f);
		drawsnake();
		update();
		if (kbhit()) {
			key = getch();
			changedir(key);
		}
		if (fruitcollision(f) == 1) {
			increasesnake();
			setfruit(f);
			timer = 0;
		}
		timer++;
		if (timer == 200) {
			gotoxy(f.x, f.y);
			cout << " ";
			setfruit(f);
			timer = 0;
		}
	}
}

int fruitcollision(fruit& fruit) {
	if (fruit.x == head->x && fruit.y == head->y) {
		return 1;
	}
	return 0;
}

void increasesnake() {
	snake *newnode = new snake;
	newnode->x = tail->x - xvel;
	newnode->y = tail->y - yvel;
	newnode->back = NULL;
	newnode->front = tail;
	tail->back = newnode;
	tail = newnode;
}

void drawfruit(fruit& fruit) {
	gotoxy(fruit.x, fruit.y);
	cout << "O";
}

void changedir(char key) {
	switch (key) {
		case 'a':   xvel = -1;
					yvel = 0;
					break;
		case 'w':   xvel = 0;
					yvel = -1;
					break;
		case 'd':   xvel = 1;
					yvel = 0;
					break;
		case 's':   xvel = 0;
					yvel = 1;
					break;
	}
}

void setfruit(fruit& fruit) {
	fruit.x = rand() % 78;
	fruit.y = rand() % 22;
	if (fruit.x == 0 || fruit.x == 1) {
		fruit.x += 2;
	}
	if (fruit.y == 0 || fruit.y == 1) {
		fruit.y += 2;
	}
}

void drawsnake() {
	char c = 254;
	snake *ptr = head;
	while (ptr != NULL) {
		gotoxy(ptr->x, ptr->y);
		if (ptr == head) {
			cout << c;
		}
		else {
			cout << "*";
		}
		ptr = ptr->back;
	}
	delay(150);
}

void clear() {
	gotoxy(tail->x - xvel, tail->y - yvel);
	cout << " ";
}

void update() {
	snake *newnode = new snake;
	newnode->x = head->x + xvel;
	newnode->y = head->y + yvel;
	newnode->front = NULL;
	newnode->back = head;
	head->front = newnode;
	head = newnode;
	snake *ptr = tail;
	tail = tail->front;
	tail->back = NULL;
	delete ptr;
}

int wallcollision() {
	if (head->x == 1 || head -> x == 80) {
		return 1;
	}
	if (head->y == 1 || head->y == 24) {
		return 1;
	}
	return 0;
}

void layout() {
	int i;
	char c = 220;
	for (i = 1; i <= 80; i++) {
		gotoxy (i,1);
		cout << c;
	}
	c = 221;
	for (i = 2; i <= 24; i++) {
		gotoxy (1,i);
		cout << c;
	}
	c = 222;
	for (i = 2; i <= 24; i++) {
		gotoxy (80,i);
		cout << c;
	}
	c = 223;
	for (i = 1; i <= 80; i++) {
		gotoxy (i,24);
		cout << c;
	}
	gotoxy (40,12);
}
