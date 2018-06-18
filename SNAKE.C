#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include <malloc.h>

typedef struct snake {
	struct snake *left;
	int x;
	int y;
	char dir;
	struct snake *right;
} snake;

void initlayout (void);
void initsnake (snake **head);
void updatedir (snake **head,  char dir);
void updatexy (snake **head);
void drawsnake (snake *head);
void increasesize (snake *head);
void getlastxy (snake *head, int *x, int *y);
char getoppheaddir (snake *head);
void move (snake **head, char dir);
int xar[210];	// Array to store x locations of walls for collision detection
int yar[210];	// Array to store y locations of walls for collision detection
static int pxy;	// counter for the above 2 arrays
static int score;
static int x = 0, y = 0;
void food (snake *head);
int checksnakexy (snake *head, int x, int y);
int checkborderxy (int x, int y);
int checkfoodcol (int hx, int hy);
int checkwallcol (int hx, int hy);

int main() {
	snake *head;
	char dir;
	int i = 0;
	clrscr ();
	initlayout ();
	initsnake (&head);
	while (1) {
		if (checkwallcol (head->x, head->y) == 1) {
			break;
		}
		if (i % 50 == 0) {
			food (head);
		}
		if (checkfoodcol (head->x, head->y) == 1) {
			score += 100;
			increasesize (head);
		}
		drawsnake (head);
		if (kbhit ()) {
			dir = getch ();
			if (dir == 'a' || dir == 's' || dir == 'w' || dir == 'd') {
				if (dir != getoppheaddir (head)) {
					move (&head, dir);
				}
			}
		}
		if (checkwallcol (head->x, head->y) == 1) {
			break;
		}
		updatexy (&head);
		i++;
	}
	getch ();
	clrscr ();
	gotoxy (30, 12);
	printf ("YOUR SCORE IS %d !!",score);
	getch ();
	return 0;
}
/*
	Fucntion used to check collision with walls.
*/
int checkwallcol (int hx, int hy) {
	int tr = 0, i;
	for (i = 0; i < pxy; i++) {
		if (xar[i] == hx && yar[i] == hy) {
			tr = 1;
			break;
		}
	}
	return tr;
}
/*
	Function used to check collision with food.
*/
int checkfoodcol (int hx, int hy) {
	int tr = 0;
	if (hx == x && hy == y) {
		tr = 1;
	}
	return tr;
}
/*
	Function to check snake' x and y locations with food' x and y locations. returns 1 if food' location is safe.
*/
int checksnakexy (snake *head, int x, int y) {
	int tr = 1;
	snake *ptr = head;
	while (ptr != NULL) {
		if (ptr->x == x+5 && ptr->y == y+5) {
			tr = 0;
			break;
		}
		if (ptr->x == x-5 && ptr->y == y-5) {
			tr = 0;
			break;
		}
		ptr = ptr->left;
	}
	return tr;
}
/*
	Function to check wall' x and y locations with food' x and y locations. returns 1 if food' location is safe.
*/
int checkborderxy (int x, int y) {
	int i, tr = 1;
	for (i = 0; i < pxy; i++) {
		if (xar[i] == x && yar[i] == y) {
			tr = 0;
			break;
		}
	}
	return tr;
}
/*
	Function used to generate food at a random location.
*/
void food (snake *head) {
	int tx, ty;
	if (x != 0 && y != 0) {
		gotoxy (x, y);
		printf (" ");
	}
	again:
	tx = rand () % 80;
	ty = rand () % 25;
	if (tx == 0) {
		tx = 4;
	}
	if (ty == 0) {
		ty = 7;
	}
	if (checkborderxy (tx, ty) == 0 || checksnakexy (head, tx, ty) == 0) {
		goto again;
	}
	gotoxy (tx, ty);
	printf ("o");
	x = tx;
	y = ty;
}
/*
	Function used to move snake as per player' input direction.
*/
void move (snake **head, char dir) {
	while (checkdir (*head, dir) != 1) {
		if (checkwallcol ((*head)->x, (*head)->y)==1) {
			break;
		}
		if (checkfoodcol ((*head)->x, (*head)->y) == 1) {
			score += 100;
			increasesize (*head);
			drawsnake (*head);
		}
		updatedir (&*head, dir);
		updatexy (&*head);
		drawsnake (*head);

	}
}
/*
	Function used to check if the player has entered a direction which is opposite to the direction of snake.
	returns opposite direction of head node if it is same as the input direction in main() no change takes
	place in movement since thats not how snake game works, snake cannot go in reverse direction.
*/
char getoppheaddir (snake *head) {
	char odir;
	switch (head->dir) {
		case 'a':   odir = 'd';
					break;
		case 'd':   odir = 'a';
					break;
		case 's':   odir = 'w';
					break;
		case 'w':   odir = 's';
					break;
	}
	return odir;
}
/*
	Function used to check if entire body of snake has achieved a uniform direction returns 1 only when every node in snake'
	body achieves a uniform direction.
*/
int checkdir (snake *head, char dir) {
	int tr = 1;
	snake *ptr = head;
	while (ptr != NULL) {
		if (ptr->dir != dir) {
			tr = 0;
			break;
		}
		ptr = ptr->left;
	}
	return tr;
}
/*
	Function used to increase size of snake' body.
*/
void increasesize (snake *head) {
	snake *ptr, *tempptr;
	ptr = (snake *) malloc (sizeof (snake));
	tempptr = head;
	while (tempptr->left != NULL) {
		tempptr = tempptr->left;
	}
	ptr->left = NULL;
	ptr->right = tempptr;
	switch (tempptr->dir) {
		case 'a':   ptr->x = tempptr->x + 1;
					ptr->y = tempptr->y;
					ptr->dir = tempptr->dir;
					break;
		case 's':   ptr->y = tempptr->y - 1;
					ptr->x = tempptr->x;
					ptr->dir = tempptr->dir;
					break;
		case 'd':   ptr->x = tempptr->x - 1;
					ptr->y = tempptr->y;
					ptr->dir = tempptr->dir;
					break;
		case 'w':   ptr->y = tempptr->y + 1;
					ptr->x = tempptr->x;
					ptr->dir = tempptr->dir;
					break;
	}
	tempptr->left = ptr;
}
/*
	Function used to get x and y location of snake' tail.
*/
void getlastxy (snake *head, int *x, int *y) {
	snake *ptr = head;
	while (ptr->left != NULL) {
		ptr = ptr->left;
	}
	*x = ptr->x;
	*y = ptr->y;
}
/*
	Function used to draw snake on user screen.
*/
void drawsnake (snake *head) {
	int x, y, i = 0;
	char dir;
	snake *ptr = head;
	while (ptr != NULL) {
		dir = ptr->dir;
		x = ptr->x;
		y = ptr->y;
		gotoxy (x, y);
		if (i == 0) {
			printf ("%c",254);
			i++;
		}
		else {
			printf ("*");
		}
		ptr = ptr->left;
	}
	delay (150);
	switch (dir) {
		case 'a': 	getlastxy (head, &x, &y);
					gotoxy (x, y);
					printf (" ");
					break;
		case 'd':   getlastxy (head, &x, &y);
					gotoxy (x, y);
					printf (" ");
					break;
		case 's':   getlastxy (head, &x, &y);
					gotoxy (x, y);
					printf (" ");
					break;
		case 'w':   getlastxy (head, &x, &y);
					gotoxy (x, y);
					printf (" ");
					break;
	}
}
/*
	Function used to update snake' direction, starts with head node and with each call changes direction of adjacent
	left node which has a different direction in it, till a uniform direction is achieved in all nodes.
*/
void updatedir (snake **head,  char dir) {
	snake *tempptr = *head;
	if ((*head)->dir != dir) {
		(*head)->dir = dir;
	}
	else {
		updatedir (&(*head)->left, dir);
	}
	*head = tempptr;
}
/*
	Function used to update x and y location of each node according to the direction of the node.
*/
void updatexy (snake **head) {
	snake *tempptr = *head;
	while (*head != NULL) {
		switch ((*head)->dir) {
			case 'd':   (*head)->x += 1;
						break;
			case 'a':   (*head)->x -= 1;
						break;
			case 's':   (*head)->y += 1;
						break;
			case 'w':   (*head)->y -= 1;
						break;
		}
		*head = (*head)->left;
	}
	*head = tempptr;
}
/*
	Function used to initialise snake' body with a single node.
*/
void initsnake (snake **head) {
	snake *ptr;
	ptr = (snake *) malloc (sizeof (snake));
	ptr->left = NULL;
	ptr->right = NULL;
	ptr->x = 40;
	ptr->y = 12;
	ptr->dir = 'd';
	*head = ptr;
}
/*
	Function used to draw walls.
*/
void initlayout (void) {
	int i;
	char c = 220;
	for (i = 1; i <= 80; i++) {
		gotoxy (i,1);
		printf ("%c",c);
		xar[pxy] = i;
		yar[pxy] = 1;
		pxy++;
	}
	c = 221;
	for (i = 2; i <= 24; i++) {
		gotoxy (1,i);
		printf ("%c",c);
		xar[pxy] = 1;
		yar[pxy] = i;
		pxy++;
	}
	c = 222;
	for (i = 2; i <= 24; i++) {
		gotoxy (80,i);
		printf ("%c",c);
		xar[pxy] = 80;
		yar[pxy] = i;
		pxy++;
	}
	c = 223;
	for (i = 1; i <= 80; i++) {
		gotoxy (i,24);
		printf ("%c",c);
		xar[pxy] = i;
		yar[pxy] = 24;
		pxy++;
	}
	gotoxy (40,12);
}
