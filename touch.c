// touch.c - MIT License
// Copyright (c) 2025 Erwin Darani

#include <stdio.h>
#include <windows.h>
#include <shlwapi.h>  // Required for PathRemoveFileSpec

// Function to create parent directories (if needed) using the Windows API
int create_directories(const char *filepath) {
    char path[MAX_PATH];
    strncpy(path, filepath, MAX_PATH - 1);
    path[MAX_PATH - 1] = '\0';

    // Remove file name to get the directory path
    if (!PathRemoveFileSpecA(path)) {
        return 0; // No directory to create
    }

    // Recursively create directories (SHCreateDirectoryEx would be safer)
    return SHCreateDirectoryExA(NULL, path, NULL) == ERROR_SUCCESS;
}

// Function to mimic the Unix "touch" behavior
int touch_file(const char *filename, int create_dirs) {
    // Try creating/opening the file in append mode (does not erase content)
    FILE *f = fopen(filename, "a");
    if (!f) {
        if (create_dirs && create_directories(filename)) {
            // Retry after creating directories
            f = fopen(filename, "a");
        }

        if (!f) {
            fprintf(stderr, "Error: could not create or open file '%s'.\n", filename);
            return 1;
        }
    }
    fclose(f);

    // Open a file handle with attribute write access to change timestamps
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

    // Get current system time and convert it to FILETIME
    SYSTEMTIME st;
    FILETIME ft;
    GetSystemTime(&st);
    SystemTimeToFileTime(&st, &ft);

    // Set the current time as both last access and last modification time
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
        argc--; // Exclude --force from file list
    }

    int exit_code = 0;
    for (int i = 1; i < argc; ++i) {
        if (touch_file(argv[i], force) != 0) {
            exit_code = 1;
        }
    }

    return exit_code;
}
