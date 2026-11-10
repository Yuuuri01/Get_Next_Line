*This project has been created as part of the 42 curriculum by hamossai.*

# Get Next Line

## Description

**Get Next Line (GNL)** is a project from the 42 curriculum focused on file handling, static variables, memory management, and reading data from file descriptors.

The goal is to develop a function that reads a file descriptor line by line, returning one line per function call, including the newline character (`\n`) when present.

The function must work with different file descriptors and handle different buffer sizes while managing memory correctly.

This project includes:
- **Mandatory part:** Basic line-by-line reading implementation.
- **Bonus part:** Support for multiple file descriptors simultaneously.

## Features

- Reads files line by line.
- Handles different `BUFFER_SIZE` values.
- Works with file descriptors.
- Preserves unread data between function calls.
- Handles the final line even when it does not end with `\n`.
- Manages dynamically allocated memory.
- Bonus: Supports multiple file descriptors independently.

## Instructions

### Compilation

Compile the mandatory implementation:

```bash
cc -Wall -Wextra -Werror \
get_next_line.c get_next_line_utils.c
```

Compile the bonus implementation:

```bash
cc -Wall -Wextra -Werror \
get_next_line_bonus.c get_next_line_utils_bonus.c
```

To specify a custom buffer size:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
get_next_line.c get_next_line_utils.c
```

### Usage

Include the appropriate header in your source file:

```c
#include "get_next_line.h"
```

Example:

```c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
    int     fd;
    char    *line;

    fd = open("file.txt", O_RDONLY);
    if (fd < 0)
        return (1);

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

Compile the program with your test file:

```bash
cc -Wall -Wextra -Werror \
-D BUFFER_SIZE=42 \
main.c get_next_line.c get_next_line_utils.c
```

## File Descriptor Architecture

![File descriptor, file table and inode table](https://upload.wikimedia.org/wikipedia/commons/f/f8/File_table_and_inode_table.svg)
## Algorithm

### 1. Reading Strategy

The implementation uses the `read()` system call to retrieve data from a file descriptor.

Instead of reading the entire file at once, it reads a limited number of bytes determined by `BUFFER_SIZE`.

The process continues until:
- A newline character (`\n`) is found.
- The end of the file is reached.
- An error occurs.

### 2. Static Variable

A static variable is used to preserve unread data between function calls.

Unlike an ordinary local variable, a static variable retains its value after the function returns.

This allows the function to remember previously read data and continue from where it stopped during the next call.

### 3. Line Extraction

Once a newline is found, the function separates the first complete line from the remaining data.

For example, suppose the buffer contains:

```text
Hello\nWorld\n42
```

The first call returns:

```text
Hello\n
```

The remaining data is preserved:

```text
World\n42
```

The next call processes the remaining content instead of reading it again from the file.

### 4. Memory Management

The implementation uses dynamic memory allocation to store and manipulate the data.

The algorithm must ensure that:
- Allocated memory is large enough for the stored data.
- Temporary buffers are properly freed.
- Unread data is preserved.
- Returned lines belong to the caller and must be freed by the caller.
- Memory is released when an error or EOF makes it unnecessary.

### 5. Bonus: Multiple File Descriptors

The bonus implementation extends the algorithm to support multiple file descriptors simultaneously.

Instead of maintaining one shared static storage area, it maintains independent storage for each file descriptor.

This prevents reading from one file descriptor from interfering with the unread data of another.

For example:

```c
line1 = get_next_line(fd1);
line2 = get_next_line(fd2);
line3 = get_next_line(fd1);
```

Each file descriptor maintains its own reading state.

## Technical Choices

| Concept | Purpose |
|---|---|
| `read()` | Reads data from file descriptors |
| `malloc()` | Allocates memory dynamically |
| `free()` | Releases allocated memory |
| Static storage | Preserves unread data |
| Buffer | Controls the amount of data read per operation |
| File descriptors | Identify open files and input streams |

The algorithm was selected to avoid loading the entire file into memory. It processes data incrementally, preserving only what is necessary for subsequent calls.

## Resources

### Documentation

- [read() — Linux Manual](https://man7.org/linux/man-pages/man2/read.2.html)
- [malloc() — Linux Manual](https://man7.org/linux/man-pages/man3/malloc.3.html)
- [free() — Linux Manual](https://man7.org/linux/man-pages/man3/free.3.html)
- [open() — Linux Manual](https://man7.org/linux/man-pages/man2/open.2.html)
- [Static Variables in C](https://en.cppreference.com/w/c/language/storage_duration.html)

### Learning Resources

- [Handling a File by Its Descriptor in C — CodeQuoi](https://www.codequoi.com/en/handling-a-file-by-its-descriptor-in-c/#the-systems-representation-of-open-files) — Understanding file descriptors and how the operating system represents open files.
- [File Descriptor — Wikipedia](https://en.wikipedia.org/wiki/File_descriptor) — An overview of file descriptors and their role in operating systems.
### AI Usage

AI tools were used as a learning and support resource during the development of this project.

Their usage included:
- Clarifying concepts related to static variables and file descriptors.
- Understanding memory allocation and memory management.
- Discussing possible algorithmic approaches.

The implementation, algorithmic decisions, and code development were handled by the project author. AI was used as an assistant for explanations and learning, not as a replacement for understanding or implementing the project.

---

**42 — Get Next Line**

*Read carefully. Manage memory. Understand every byte.*