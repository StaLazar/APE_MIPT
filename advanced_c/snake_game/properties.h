#pragma once

//! Клавиша завершения игры.
#define EXIT_KEY KEY_F(10)

//! Количество обновлений логики в секунду.
#define UPS 10U
//! Период обновления логики в секундах.
#define UPDATE_TIMEOUT_SEC (1.F / UPS)

//! Символ-заполнитель для головы змейки.
#define BODY_HEAD '0'
//! Символ-заполнитель для хвоста змейки.
#define BODY_TAIL 'O'
//! Символ-заполнитель для фрукта.
#define BODY_FRUIT '@'
//! Пустой символ-заполнитель.
#define BODY_IDLE ' '

//! Минимальный размер хвоста змейки.
#define MIN_TAIL_SIZE 3UL
//! Максимальный размер хвоста змейки.
#define MAX_TAIL_SIZE 10UL

//! Максимальное число фруктов, одновременно размещенных на поле.
#define MAX_FRUITS_AMOUNT 10UL
//! Период отображения фрукта на поле в секундах.
#define FRUIT_LIFE_TIMEOUT_SEC 5.F

//! Начальная координата Y головы змейки.
#define START_COORD_Y (getmaxy(stdscr) / 2)
//! Начальная координата X головы змейки.
#define START_COORD_X (getmaxx(stdscr) / 2)

//! Смещение по Y границ игровой арены относительно границ экрана в символах.
#define ARENA_OFFSET_Y 4
//! Смещение по X границ игровой арены относительно границ экрана в символах.
#define ARENA_OFFSET_X 4
//! Минимальная координата Y игровой арены.
#define ARENA_MIN_COORD_Y (getbegy(stdscr) + ARENA_OFFSET_Y)
//! Максимальная координата Y игровой арены.
#define ARENA_MAX_COORD_Y (getmaxy(stdscr) - ARENA_OFFSET_Y)
//! Минимальная координата X игровой арены.
#define ARENA_MIN_COORD_X (getbegx(stdscr) + ARENA_OFFSET_X)
//! Максимальная координата X игровой арены.
#define ARENA_MAX_COORD_X (getmaxx(stdscr) - ARENA_OFFSET_X)
