#ifndef FILESYSTEM_H
#define FILESYSTEM_H

int create_file(const char *filename, const char *content);
int delete_file(const char *filename);
int modify_file(const char *filename, const char *new_content);
void view_file(const char *filename);
void exit_program();
#endif // FILESYSTEM_H
#include "filesystem.h"
#include <stdio.h>
#include <stdlib.h>

int create_file(const char *filename, const char *content) {
    FILE *file = fopen(filename, "w");
    if (!file) return -1;
    if (content) fprintf(file, "%s", content);
    fclose(file);
    return 0;
}

int delete_file(const char *filename) {
    return remove(filename) == 0 ? 0 : -1;
}

int modify_file(const char *filename, const char *new_content) {
    FILE *file = fopen(filename, "w");
    if (!file) return -1;
    if (new_content) fprintf(file, "%s", new_content);
    fclose(file);
    return 0;
}

void view_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Ошибка: не удалось открыть файл %s\n", filename);
        return;
    }
    char ch;
    while ((ch = fgetc(file)) != EOF) putchar(ch);
    fclose(file);
    putchar('\n');
}

void exit_program() {
    printf("Выход из программы...\n");
    exit(0);
}// main.c
#include <stdio.h>
#include "filesystem.h"

int main() {
    const char *filename = "example.txt";

    if (create_file(filename, "Это начальный текст в файле.\n") == 0) {
        printf("Файл '%s' успешно создан.\n", filename);
    } else {
        printf("Ошибка создания файла '%s'.\n", filename);
    }

    printf("Содержимое файла '%s':\n", filename);
    view_file(filename);

    exit_program();

    return 0;
}
