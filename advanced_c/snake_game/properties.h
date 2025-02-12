#pragma once

//! Количество обновлений логики в секунду.
#define UPS 10U
//! Период обновления логики в секундах.
#define UPDATE_TIMEOUT_SEC (1.F / UPS)

//! Минимальный размер хвоста змейки.
#define MIN_TAIL_SIZE 3UL
//! Максимальный размер хвоста змейки.
#define MAX_TAIL_SIZE 10UL
