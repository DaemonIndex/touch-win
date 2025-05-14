# touch.exe per Windows

> Comando `touch` in stile Unix, compatibile con Windows.  
> Crea file se non esistono, aggiorna il timestamp se esistono già.

---

## Descrizione

Questo piccolo programma scritto in __C__ replica il comportamento base del comando `touch` di Linux, ma per __sistemi Windows__.

### Funzionalità

- Se il file __non esiste__, lo crea.
- Se il file __esiste__, ne aggiorna __data di accesso__ e __modifica__.
- Nessuna dipendenza esterna. Binario standalone.

---

### 🔧 Compilazione

#### Con MinGW (Code::Blocks)

```bash
gcc -O2 touch.c -o touch.exe
```

#### Con Microsoft Visual C++ (MSVC)

```bash
cl touch.c /O2 /Fe:touch.exe
```

## 🚀 Installazione

### Metodo 1: Installazione di sistema (richiede privilegi di amministratore)

Copia touch.exe in:

```bash
C:\Windows\System32
```

### Metodo 2: Cartella utente (consigliato)

Crea una cartella:

```bash
mkdir %USERPROFILE%\bin
```

Copia __touch.exe__ lì.

Aggiungi %USERPROFILE%\bin alla variabile d'ambiente PATH.

## ✅ Utilizzo

### Da terminale (cmd o PowerShell)

```bash
touch nomefile.txt
touch file1.txt file2.cpp file3.md
```

---
