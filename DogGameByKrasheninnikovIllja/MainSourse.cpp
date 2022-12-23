#include <windows.h>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <conio.h>
#include <map>

using namespace std;

enum chars {
	dogS = '@',
	borderS = '#',
	voidS = '.',
	exitS = 'O'
};


const int FIELD_WIDTH = 24;
const int FIELD_HEIGHT = 12;
const int block_freq = 25;


struct Cords {
	int x;
	int y;

	Cords(int x, int y) : x(x), y(y) {}

	Cords operator + (Cords b) {
		return Cords(this->x + b.x, this->y + b.y);
	}
};

 char field_mash[FIELD_HEIGHT][FIELD_WIDTH];
//char field_mash[FIELD_HEIGHT][FIELD_WIDTH];

Cords dog(0, 0);
Cords vectorMove(0, 0);

void field_gen() {
	for (int i = 0; i < FIELD_HEIGHT; i++) {
		for (int j = 0; j < FIELD_WIDTH; j++) {
			int rand_num = rand() % 100;
			if (rand_num < block_freq) {
				field_mash[i][j] = borderS;
			}
			else
			{
				field_mash[i][j] = voidS;
			}
		}
	}
	int x, y;
	do {
		x = rand() % FIELD_WIDTH;
		y = rand() % FIELD_HEIGHT;
	} while (field_mash[y][x] == borderS);
	//field_mash[door.y][door.x] = exitS;
	//додаю вихід в map
	field_mash[y][x]= exitS;
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
				SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN);
				cout << (char)dogS;
				//повернення кольору
				SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			}
			else {
				char s = field_mash[i][j];
				switch (s)
				{
				case borderS:
					SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
					break;
				case exitS:
					SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE| FOREGROUND_INTENSITY);
					break;
				default:
					SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
					break;
				}
				cout << s;
			}
		}
		SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		cout << endl;
	}
}

void dog_place() {
	do {
		dog.x = rand() % FIELD_WIDTH;
		dog.y = rand() % FIELD_HEIGHT;
	} while (field_mash[dog.y][dog.x] == borderS); //щоб собака не з'являвся в решітці
}

void generate() {
	field_gen();
	dog_place();
}

bool game_is_over() {
	return (field_mash[dog.y][dog.x] == exitS);
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

bool is_walkable(Cords newCord) {
	return field_mash[newCord.y][newCord.x] != borderS;
	//return field_mash[Y][X] != borderS;
}

bool is_dont_end_pole(Cords cord) {
	return (cord.x >= 0 && cord.x < FIELD_WIDTH&& cord.y >= 0 && cord.y < FIELD_HEIGHT);
}

bool can_go_to(Cords newCord) {
	return (is_walkable(newCord) && is_dont_end_pole(newCord));
}

void go_to(Cords newCord) {
	dog = newCord;
}

void try_to_go(Cords newCord) {
	if (can_go_to(newCord))
		go_to(newCord);
}

void logic() {
	try_to_go(dog + vectorMove);
}


int main() {
	srand((unsigned int) time(NULL));
	//тимчасово один сід для тестів
	//srand(10000000);
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
