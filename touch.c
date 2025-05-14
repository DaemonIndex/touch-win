// touch.c - MIT License
// Copyright (c) 2025 Karmak

#include <stdio.h>
#include <windows.h>

int touch_file(const char *filename) {
    /* Crea o apre il file in append (non ne cancella il contenuto) */
    FILE *f = fopen(filename, "a");
    if (!f) {
        fprintf(stderr, "Errore: impossibile creare o aprire il file '%s'.\n", filename);
        return 1;
    }
    fclose(f);

    /* Ottieni un handle per modificare i timestamp */
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
        fprintf(stderr, "Errore: impossibile accedere al file '%s' per aggiornare il timestamp.\n", filename);
        return 1;
    }

    /* Prendi l'ora corrente e converti in FILETIME */
    SYSTEMTIME st;
    FILETIME ft;
    GetSystemTime(&st);
    SystemTimeToFileTime(&st, &ft);

    /* Applica la stessa ora per ultimo accesso e ultima modifica */
    if (!SetFileTime(hFile, NULL, &ft, &ft)) {
        fprintf(stderr, "Errore: impossibile aggiornare la data di modifica per '%s'.\n", filename);
        CloseHandle(hFile);
        return 1;
    }

    CloseHandle(hFile);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: touch <file1> [file2] [...]\n");
        return 1;
    }

    int exit_code = 0;
    for (int i = 1; i < argc; ++i) {
        if (touch_file(argv[i]) != 0) {
            exit_code = 1;
        }
    }
    return exit_code;
}
