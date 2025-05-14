# touch.exe for Windows

> Unix-style `touch` command for windows
> Creates files if they don't exist, updates timestamps if they do.

---

## Description

This small program written in __C__ replicates the basic behavior of the Unix `touch` command but for __Windows systems__.

### ✅ Features

- If the file __does not exist__, it creates it.
- If the file __exists__, it updates its __last access__ and __modification__ timestamps.
- No external dependencies. Standalone binary.

---

### 🔧 Compilation

#### With MinGW (Code::Blocks)

```bash
gcc -O2 touch.c -o touch.exe
```

#### With Microsoft Visual C++ (MSVC)

```bash
cl touch.c /O2 /Fe:touch.exe
```

## 🚀 Installation

### Method 1: System installation (require administrator privileges)

Copy touch.exe to:

```bash
C:\Windows\System32
```

### Method 2: User-level (recommended)

Create a folder:

```bash
mkdir %USERPROFILE%\bin
```

Copy __touch.exe__ there.

Add %USERPROFILE%\bin to the PATH environment variable.

## ✅ Usage

### From terminal (cmd or PowerShell)

```bash
touch nomefile.txt
touch file1.txt file2.cpp file3.md
```
If the file __does not exist__, it will be created.
If the file __already exist__, its access and modification timestamps will be updated.

## Optional Flag: `--force`

You can add the `--force` flag __at the end__ of the command to automatically create any missing directories in the path:

```bash
touch path\to\new\folder\file.txt --force
```

🔧 Without `--force`, the program will fail if the folder does not exist.

✅ With `--force`, missing directories will be created automatically before touching the file.

---

### 🚨 **Administrator Privileges**

In some cases, especially when creating directories or writing files in system-protected folders (like `C:\Program Files`, `C:\Windows`, or other restricted locations), **administrator privileges** may be required.

To run the program with administrator rights:

1. **Right-click** on the Command Prompt (cmd) or PowerShell and select **Run as Administrator**.
2. Then, run the `touch` command as usual.

If you're working in user-specific directories (e.g., `C:\Users\<YourUsername>\Documents`), **administrator privileges are not necessary**.
