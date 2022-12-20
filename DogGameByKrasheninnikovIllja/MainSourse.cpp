#include <windows.h>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <conio.h>

using namespace std;

enum chars {
	dogS = '@',
	borderS = '#',
	voidS = ' ',
	exitS = 'O'
};


const int FIELD_WIDTH = 10;
const int FIELD_HEIGHT = 12;
const int block_freq = 25;


struct Cords {
	int x;
	int y;

	Cords(int x, int y): x(x), y(y) {}
};


char field_mash[FIELD_HEIGHT][FIELD_WIDTH];

Cords dog(0, 0);
Cords door(0, 0);
Cords vectorMove(0, 0);

void field_gen() {
	for (int i = 0; i < FIELD_HEIGHT; i++) {
		for (int j = 0; j < FIELD_WIDTH; j++) {
			int rand_num = rand() % 100;
			if (rand_num < block_freq)
				field_mash[i][j] = borderS;
			else
				field_mash[i][j] = voidS;
		}
	}
	door.x = rand() % FIELD_WIDTH;
	door.y = rand() % FIELD_HEIGHT;
	field_mash[door.y][door.x] = exitS;

}
void draw() {
	//перенос курсора на початок сторінки
	//щоб текст заміняв свій минули
	//можна вважати це як очищення консоліі але не билимає
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos{ 0, 0 };
	SetConsoleCursorPosition(hStdOut, pos);

	//
	for (int i = 0; i < FIELD_HEIGHT; i++) {
		for (int j = 0; j < FIELD_WIDTH; j++) {
			if (i == dog.y && j == dog.x)
			{
				//змінення кольору щоб намалювати собаку
				SetConsoleTextAttribute(hStdOut, BACKGROUND_BLUE | FOREGROUND_GREEN);
				cout << (char) dogS;
				//повернення кольору
				SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			}
			else {
				cout << field_mash[i][j];
			}
		}
		cout << endl;
	}
}

void dog_place() {
	do {
		dog.x = rand() % FIELD_WIDTH;
		dog.y = rand() % FIELD_HEIGHT;
	} while ((field_mash[dog.y][dog.x]) == borderS); //щоб собака не з'являвся в решітці
}

void generate() {
	field_gen();
	dog_place();
}

bool game_is_over() {
	return (dog.y == door.y && dog.x == door.x);
}

void get_input() {
	vectorMove.x = 0;
	vectorMove.y = 0;
	//беремо значення що нажав користувач
	char input_symbol = _getche();

	if (input_symbol == 'H' || input_symbol == 'w') {
		vectorMove.y = -1;
	}
	else if (input_symbol == 'P' || input_symbol == 's') {
		vectorMove.y = 1;
	}
	else if (input_symbol == 'K' || input_symbol == 'a') {
		vectorMove.x = -1;
	}
	else if (input_symbol == 'M' || input_symbol == 'd') {
		vectorMove.x = 1;
	}
	else {
		vectorMove.x = 0;
		vectorMove.y = 0;
	}
}

bool is_walkable(int X, int Y) {
	return field_mash[Y][X] != borderS;
}

bool can_go_to(int newX, int newY) {
	if (newX < 0 || newX >= FIELD_WIDTH || newY < 0 || newY >= FIELD_HEIGHT)
		return false;
	if (!is_walkable(newX, newY))
		return false;
	else
		return true;
}

void go_to(int newX, int newY) {
	dog = Cords(newX,newY);
}

void try_to_go(int new_X, int new_Y) {
	if (can_go_to(new_X, new_Y))
		go_to(new_X, new_Y);
}

void logic() {
	try_to_go(dog.x + vectorMove.x, dog.y + vectorMove.y);
}


int main() {
	//srand((unsigned int) time(NULL));
	//тимчасово один сід для тестів
	srand(10000000);
	generate();
	draw();
	while (!game_is_over()) {
		get_input();
		logic();
		draw();
	}
	cout << "YOU WINNNNNNN!!!!";
	return 0;
}
