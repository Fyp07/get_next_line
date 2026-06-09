*This project has been created as part of the 42 curriculum by fbarrada.*

---

## Description

`get_next_line` is a C function that reads one line at a time from a given file descriptor. Each call picks up exactly where the last one left off, allowing a file (or stdin) to be consumed line by line without loading it fully into memory.

The mandatory part handles a single file descriptor using one static variable. The bonus extends support to up to 1024 simultaneous file descriptors, each tracked independently with a single static array.

---

## Files

| File | Description |
|------|-------------|
| `get_next_line.c` | Core function + `extract_line`, `clean_stash`, `check_line_break` |
| `get_next_line_utils.c` | `ft_strlen`, `ft_strncpy`, `ft_strjoin`, `read_file` |
| `get_next_line.h` | Header with prototype, `BUFFER_SIZE` default, and includes |
| `get_next_line_bonus.c` | Same logic, `stash` becomes `stash[1024]` for multi-fd |
| `get_next_line_utils_bonus.c` | Same helpers as mandatory |
| `get_next_line_bonus.h` | Bonus header |

---

## Instructions

### Compilation

`BUFFER_SIZE` controls how many bytes `read()` fetches per call. Set it at compile time:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

If `-D BUFFER_SIZE` is omitted, the header defaults to `42`.

### Usage example

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int   fd;
    char  *line;

    fd = open("file.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

### Prototype

```c
char *get_next_line(int fd);
```

Returns the next line including `\n`, or `NULL` on EOF or error. The caller must `free()` the returned string.

---

## Algorithm

### Overview

The function relies on a **persistent stash** — a heap-allocated string that survives between calls via a `static` variable. On each call, it reads from the fd only as much as needed to find a `\n`, returns the complete line, and saves whatever remains in the stash for the next call.

### Call flow

```
get_next_line(fd)
    │
    ├─ read_file(fd, stash)
    │       └─ loop: read(fd, buf, BUFFER_SIZE)
    │              → strjoin stash + buf
    │              → stop when '\n' found in stash or EOF
    │
    ├─ extract_line(stash)
    │       └─ copy stash[0..'\n'] into a new string → return as line
    │
    └─ clean_stash(stash)
            └─ copy stash[after '\n'..end] into a new string → new stash
               free old stash
               return NULL if nothing remains
```

### Function breakdown

**`check_line_break(stash)`** — scans the stash for `\n`. Used as the loop condition inside `read_file` to stop reading as soon as a full line is available.

**`read_file(fd, stash)`** — allocates a `BUFFER_SIZE + 1` buffer, reads in a loop, and appends each chunk to the stash via `ft_strjoin` (which always frees the old stash). Stops on EOF (`bytes_read == 0`), error (returns `NULL`, freeing both buf and stash), or when `\n` is detected in the stash.

**`extract_line(stash)`** — walks the stash until `\n` or `\0`, allocates exactly the right amount, copies that slice, and returns it. The `\n` is included in the returned string.

**`clean_stash(stash)`** — advances past the `\n` in the stash. If nothing follows (or there's no `\n` at all), frees stash and returns `NULL`. Otherwise allocates a new string from the remainder, frees the original, and returns the trimmed stash.

**`ft_strjoin(s1, s2)`** — concatenates s1 and s2 into a new allocation, always freeing s1. If s1 is `NULL`, it initialises an empty string before joining, so the very first call works without a pre-allocated stash.

### Bonus: multiple file descriptors

The only structural change is the static variable:

```c
// Mandatory
static char *stash;

// Bonus
static char *stash[1024];
```

Every `fd` gets its own stash slot (`stash[fd]`). Calls to different fds are fully independent — interleaving them doesn't corrupt any reading state. The guard `fd >= 1024` replaces the previous `fd > 1024` to correctly reject the boundary value.

### Design choices and trade-offs

- **`ft_strjoin` frees s1** — this avoids a separate `free(stash)` after every append and keeps `read_file` clean, but it means the caller must never use s1 after the call.
- **No `lseek`, no global variables** — as required by the subject.
- **`BUFFER_SIZE` agnostic** — because the stash accumulates partial reads, the function behaves correctly whether `BUFFER_SIZE` is `1`, `42`, or `10000000`. A very large buffer may over-read past the first `\n`, but that data is preserved in the stash and returned correctly on the next call.

---

## Resources

- [Memory Management in C: mallocs and frees](https://claude.ai/share/af9d74b1-a63c-47ab-8a8c-724fcf860c39)

**AI usage in this project:**

AI (Claude) was used exclusively for writing this `README.md` — structuring the document, describing the algorithm based on the submitted source code, and phrasing the explanations. AI (Claude) was also used to study and understand certain concepts that would aid in the project's implementation. No AI was used to write, generate, or modify any `.c` or `.h` file.
