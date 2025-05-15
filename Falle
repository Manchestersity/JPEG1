#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

int add_new_file(const char* fs_path, const char* filename, const char* content) {
    FILE* fs = fopen(fs_path, "a");
    if (!fs) return -1;

    fprintf(fs, "%s\n", filename);
    if (content && strlen(content) > 0) {
        fprintf(fs, "%s\n", content);
    }
    fclose(fs);
    return 0;
}

int edit_file_content(const char* fs_path, const char* filename, const char* new_content) {
    FILE* fs = fopen(fs_path, "r");
    if (!fs) return -1;

    char temp_path[] = "fs_temp.txt";
    FILE* temp = fopen(temp_path, "w");
    if (!temp) {
        fclose(fs);
        return -1;
    }

    char line[MAX_LINE];
    int file_found = 0;
    int skip_content = 0;

    while (fgets(line, sizeof(line), fs)) {
        line[strcspn(line, "\n")] = 0;

        if (strcmp(line, filename) == 0) {
            file_found = 1;
            skip_content = 1;
            fprintf(temp, "%s\n", filename);
            if (new_content && strlen(new_content) > 0) {
                fprintf(temp, "%s\n", new_content);
            }
            continue;
        }

        if (skip_content) {
            if (strlen(line) > 0 && strchr(line, '.') != NULL) {
                skip_content = 0;
                fprintf(temp, "%s\n", line);
            }
            continue;
        }

        fprintf(temp, "%s\n", line);
    }

    fclose(fs);
    fclose(temp);

    if (!file_found) {
        remove(temp_path);
        return -1;
    }

    remove(fs_path);
    rename(temp_path, fs_path);

    return 0;
}
