#include <cstdlib>
#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <conio.h>

using namespace std;

const int widht = 10;
const int height = 12;
int block_freq = 25;
char field_mash[height][widht];

int dog_X{}, dog_Y{}, dX{}, dY{}, door_X{}, door_Y{};
const char dog = '@';

void field_gen() {

    srand(time(NULL));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < widht; j++) {
            int rand_num = rand() % 100;
            if (rand_num < block_freq)
                field_mash[i][j] = '#';
            else
                field_mash[i][j] = '_';
        }
    }
    door_X = rand() % (widht - 1);
    door_Y = rand() % (height - 1);
    field_mash[door_Y][door_X] = 'O';

}
void draw() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < widht; j++) {
            if (i == dog_Y && j == dog_X)
                cout << dog;
            else
                cout << field_mash[i][j];
        }
        cout << endl;
    }
}

void dog_place() {
    srand(time(NULL));
    dog_X = rand() % (widht - 1);
    dog_Y = rand() % (height - 1);
}

void generate() {
    field_gen();
    dog_place();
}

bool game_is_over() {

    if (dog_Y == door_Y && dog_X == door_X)
        return false;
    else
        return true;
}

void get_input() {
    dX = 0;
    dY = 0;
    char input_symbol;
    cin >> input_symbol;
    if (input_symbol == 'W' || input_symbol == 'w') {
        dY = -1;
    }
    else if (input_symbol == 'S' || input_symbol == 's') {
        dY = 1;
    }
    else if (input_symbol == 'A' || input_symbol == 'a') {
        dX = -1;
    }
    else if (input_symbol == 'D' || input_symbol == 'd') {
        dX = 1;
    }
    else {
        dX = 0;
        dY = 0;
    }
}

bool is_walkable(int X, int Y) {
    if (field_mash[Y][X] == '#')
        return false;
    else
        return true;
}

bool can_go_to(int newX, int newY) {
    if (newX < 0 || newX >= widht || newY < 0 || newY >= height)
        return false;
    if (!is_walkable(newX, newY))
        return false;
    else
        return true;
}

void go_to(int newX, int newY) {
    dog_X = newX;
    dog_Y = newY;

}

void try_to_go(int new_X, int new_Y) {
    if (can_go_to(new_X, new_Y))
        go_to(new_X, new_Y);
}

void logic() {
    try_to_go(dog_X + dX, dog_Y + dY);
}


int main() {
    generate();
    draw();
    while (game_is_over()) {
        get_input();
        logic();
        draw();

    }
    cout << "YOU WINNNNNNN!!!!";
    return 0;
}