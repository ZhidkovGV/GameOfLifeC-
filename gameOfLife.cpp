#include <iostream>
#include <cstdlib>
#include <unistd.h>
// include <windows.h>

using namespace std; 
int GLOBAL_LENGTH = 0;

int** init_matrix () {
    int** matrix;
    matrix = new int* [GLOBAL_LENGTH];
    for (int i = 0; i < GLOBAL_LENGTH; i++) {
        matrix[i] = new int [GLOBAL_LENGTH];
    }
    return matrix;
}

void delete_matrix (int** matrix_to_delete) {
    for (int i = 0; i < GLOBAL_LENGTH; i++) {
        delete[] matrix_to_delete[i];
    }
    delete[] matrix_to_delete;
}

void draw_field (int** matrix_to_draw) {
    system("clear");
    for (int i = 0; i < GLOBAL_LENGTH; i++) {
        for (int j = 0; j < GLOBAL_LENGTH; j++) {
            cout << matrix_to_draw[i][j] << " ";
        }
        cout << endl;
    }
}

void update_previous_state(int** matrix_to_update, int** current_state) {
    for (int i = 0; i < GLOBAL_LENGTH; i++) {
        for (int j = 0; j < GLOBAL_LENGTH; j++) {
            matrix_to_update[i][j] = current_state[i][j];
        }
    }
}

bool check_borders (int position, int difference) {
    return ((position + difference) >= 0) && ((position + difference) < GLOBAL_LENGTH);
}

int count_neighbours (int x_position, int y_position, int** current_state) {
    int neighbours = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (check_borders(x_position, i) && check_borders(y_position, j)) {
                if (!(i == 0 && j == 0)) {
                    neighbours += current_state[x_position + i][y_position + j];
                }
            }
        }
    }
    return neighbours;
}

void apply_rules(int** new_state, int** prev_state) {
    for (int i = 0; i < GLOBAL_LENGTH; i++) {
        for (int j = 0; j < GLOBAL_LENGTH; j++) {
            int neighbours = count_neighbours(i, j, prev_state);
            if (neighbours < 2 || neighbours > 3) {
                new_state[i][j] = 0;
            } else if (neighbours == 3) {
                new_state[i][j] = 1;
            } else {
                new_state[i][j] = prev_state[i][j];
            }
        }
    }
}

bool game_end(int** current_state, int** prev_state) {
    for (int i = 0; i < GLOBAL_LENGTH; i++) {
        for (int j = 0; j < GLOBAL_LENGTH; j++) {
            if (prev_state[i][j] != current_state[i][j]) {
                return false;
            }
        }
    }
    return true;
}

int** init_game() {
    int** matrix;
    cin >> GLOBAL_LENGTH;
    matrix = init_matrix();
    for (int i  = 0; i < GLOBAL_LENGTH; i++) {
        for (int j = 0; j < GLOBAL_LENGTH; j++) {
            cin >> matrix[i][j];
        }
    }
    return matrix;
}

void game_loop() {
    int** game_field = init_game();
    int** previous_state = init_matrix();
    while (!game_end(game_field, previous_state)) {
        update_previous_state(previous_state, game_field);
        apply_rules(game_field, previous_state);
        draw_field(game_field);
        sleep(1);
    }
    delete_matrix(game_field);
    delete_matrix(previous_state);
}

int main() {
    game_loop();
    return 0;
}
