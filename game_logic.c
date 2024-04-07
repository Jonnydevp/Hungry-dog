#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // Библиотека для функции getch().

#include "game_logic.h"

void main_loop(){
    char field[10][21]; // Игровое поле размером 10 строк на 21 символ в строке.
    int tail[100][2]; // Массив для хранения координат хвоста змейки.
    int length = 1; // Длина змейки.
    tail[0][0] = 5; // Начальное положение головы змейки по оси Y.
    tail[0][1] = 5; // Начальное положение головы змейки по оси X.
    int apple_x = 5, apple_y = 3; // Положение яблока.
    char key = '\0'; // Переменная для хранения символа клавиши.
    srand(time(NULL)); // Инициализация генератора случайных чисел.

    while(key != 'h'){ // Цикл игры, который продолжается до тех пор, пока не будет нажата клавиша 'h'.
        system("cls"); // Очистка экрана консоли.
        sprintf(field[0], "####################"); // Заполнение верхней границы игрового поля.
        for(int i = 1; i < 9; i++)
            sprintf(field[i], "#                  #"); // Заполнение боковых границ игрового поля.
        sprintf(field[9], "####################"); // Заполнение нижней границы игрового поля.

        field[apple_y][apple_x] = '*'; // Размещение яблока на игровом поле.
        for(int i = 0; i < length; i++){
            if(i == 0)
                field[tail[0][0]][tail[0][1]] = '@'; // Установка головы змейки на поле.
            else
                field[tail[i][0]][tail[i][1]] = '.'; // Установка элементов хвоста змейки на поле.
        }

        for(int i = 0; i < 10; i++)
            printf("%s\n", field[i]); // Вывод игрового поля на экран.
        printf("your length - %d", length+1); // Вывод длины змейки на экран.
        key = getch(); // Получение нажатой клавиши.

        // Логика движения змейки в зависимости от нажатой клавиши.
        int ox = tail[0][1], oy = tail[0][0];
        if(key == 'w') tail[0][0]--;
        if(key == 's') tail[0][0]++;
        if(key == 'd') tail[0][1]++;
        if(key == 'a') tail[0][1]--;

        // Проверка на столкновение змейки со стеной или самой собой.
        if(field[tail[0][0]][tail[0][1]] == '#' || field[tail[0][0]][tail[0][1]] == '.'){
            tail[0][1] = ox;
            tail[0][0] = oy;
            printf("\nGame over........................");
        }
        else{
            // Обновление координат хвоста змейки при движении.
            for(int i = 1; i < length; i++){
                int temp = tail[i][1];
                tail[i][1] = ox;
                ox = temp;

                temp = tail[i][0];
                tail[i][0] = oy;
                oy = temp;
            }
        }

        // Генерация нового положения яблока и увеличение длины змейки при его съедении.
        if(tail[0][0] == apple_y && tail[0][1] == apple_x){
            while(tail[0][0] == apple_y && tail[0][1] == apple_x || field[apple_y][apple_x] == '.'){
                apple_y = rand() * 1.0 / RAND_MAX * 8 + 1;
                apple_x = rand() * 1.0 / RAND_MAX * 17 + 1;
            }
            tail[length][0] = oy;
            tail[length][1] = ox;
            length++;
        }
    }
}