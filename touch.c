// touch.c - MIT License
// Copyright (c) 2025 Erwin Darani

#include <stdio.h>
#include <windows.h>
#include <string.h>

int create_directories(const char *filepath) {
    char path[MAX_PATH];
    strncpy(path, filepath, MAX_PATH - 1);
    path[MAX_PATH - 1] = '\0';

    // Estrai la parte della directory dal percorso
    char *lastSlash = strrchr(path, '\\');
    if (lastSlash) {
        *lastSlash = '\0';  // Rimuovi il nome del file per ottenere il percorso della directory
    }

    // Crea la directory se non esiste
    if (CreateDirectoryA(path, NULL) || GetLastError() == ERROR_ALREADY_EXISTS) {
        return 1;
    } else {
        return 0;
    }
}

int touch_file(const char *filename, int create_dirs) {
    // Se la directory non esiste, prova a crearla
    if (create_dirs && !create_directories(filename)) {
        fprintf(stderr, "Error: could not create directory for '%s'.\n", filename);
        return 1;
    }

    FILE *f = fopen(filename, "a");
    if (!f) {
        fprintf(stderr, "Error: could not create or open file '%s'.\n", filename);
        return 1;
    }
    fclose(f);

    HANDLE hFile = CreateFileA(
        filename,
        FILE_WRITE_ATTRIBUTES,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    if (hFile == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Error: could not access file '%s' to update timestamp.\n", filename);
        return 1;
    }

    SYSTEMTIME st;
    FILETIME ft;
    GetSystemTime(&st);
    SystemTimeToFileTime(&st, &ft);

    if (!SetFileTime(hFile, NULL, &ft, &ft)) {
        fprintf(stderr, "Error: could not update timestamp for '%s'.\n", filename);
        CloseHandle(hFile);
        return 1;
    }

    CloseHandle(hFile);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: touch <file1> [file2] [...] [--force]\n");
        return 1;
    }

    int force = 0;
    if (strcmp(argv[argc - 1], "--force") == 0) {
        force = 1;
        argc--;
    }

    int exit_code = 0;
    for (int i = 1; i < argc; ++i) {
        if (touch_file(argv[i], force) != 0) {
            exit_code = 1;
        }
    }

    return exit_code;
}