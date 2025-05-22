#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filesystem.h"

#define MAX_INPUT 256

// Вспомогательная функция для разбора команды и аргументов
int parse_input(char *input, char **argv) {
    int argc = 0;
    char *token = strtok(input, " \n");
    while (token && argc < 3) {
        argv[argc++] = token;
        token = strtok(NULL, " \n");
    }
    return argc;
}

int main() {
    FileSystem fs = {NULL, 0};
    char input[MAX_INPUT];
    char *argv[3]; // команда + максимум 2 аргумента
    int argc;

    printf("Простой файловый менеджер. Введите команду ('help' для справки)\n");

    while (1) {
        printf("> ");
        if (!fgets(input, sizeof(input), stdin)) {
            break;
        }

        argc = parse_input(input, argv);
        if (argc == 0) continue;

        if (strcmp(argv[0], "создать") == 0) {
            if (argc < 2) {
                printf("Использование: создать <путь>\n");
                continue;
            }
            if (fs_insert(&fs, argv[1]) == 0) {
                printf("Файл '%s' создан\n", argv[1]);
            } else {
                printf("Ошибка создания файла\n");
            }
        } else if (strcmp(argv[0], "удалить") == 0) {
            if (argc < 2) {
                printf("Использование: удалить <путь>\n");
                continue;
            }
            if (fs_delete(&fs, argv[1]) == 0) {
                printf("Файл '%s' удалён\n", argv[1]);
            } else {
                printf("Файл не найден\n");
            }
        } else if (strcmp(argv[0], "изменить") == 0) {
            if (argc < 2) {
                printf("Использование: изменить <путь>\n");
                continue;
            }
            printf("Введите новое содержимое файла:\n");
            char buffer[1024];
            if (!fgets(buffer, sizeof(buffer), stdin)) {
                printf("Ошибка ввода\n");
                continue;
            }
            // Удаляем перенос строки
            buffer[strcspn(buffer, "\n")] = '\0';

            if (fs_update(&fs, argv[1], buffer) == 0) {
                printf("Файл '%s' обновлён\n", argv[1]);
            } else {
                printf("Ошибка обновления файла\n");
            }
        } else if (strcmp(argv[0], "посмотреть") == 0) {
            if (argc < 2) {
                printf("Использование: посмотреть <путь>\n");
                continue;
            }
            char *content = NULL;
            if (fs_select(&fs, argv[1], &content) == 0 && content != NULL) {
                printf("< %s\n", content);
            } else {
                printf("Файл не найден или пуст\n");
            }
        } else if (strcmp(argv[0], "выход") == 0 ||
                   strcmp(argv[0], "exit") == 0) {
            break;
        } else if (strcmp(argv[0], "help") == 0) {
            printf("Команды:\n"
                   "создать <путь>   - создать новый файл\n"
                   "удалить <путь>   - удалить файл\n"
                   "изменить <путь>  - изменить содержимое файла\n"
                   "посмотреть <путь> - вывести содержимое файла\n"
                   "выход            - выйти из программы\n");
        } else {
            printf("Неизвестная команда. Введите 'help' для справки.\n");
        }
    }

    fs_free(&fs);
    printf("Выход из программы.\n");
    return 0;
}
