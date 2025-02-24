#pragma once

#include <stdbool.h>

/**
 * @ingroup tools
 * @{
 */

/**
 * @brief Вывести в консоль справку по приложению.
 * @details Справка по приложению представляет собой
 * описание функционала программы, а также список ключей,
 * их назначение и примеры использования.
 */
void printCmdHelp();

/**
 * @brief Обработать аргументы командной строки.
 * @param[in] argc Количество переданных аргументов командной строки.
 * @param[in] argv Массив строк, представляющий переданный набор аргументов.
 * @param[out] isHelpReceived Флаг запроса вывода в консоль справки по приложению.
 * @param[out] path Путь до файла с массивом данных с интересующего датчика.
 * @param[out] timeDate Временная метка в виде строки для дальнейшей обработки.
 */
void handleCmdCommands(int argc, char *argv[], bool *isHelpReceived, char **path, char **timeDate);

/**
 * @}
 */
