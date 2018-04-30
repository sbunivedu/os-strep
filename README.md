# The Strep Program
A string find-and-replace program<sup>[1](#myfootnote1)</sup>.

## Introduction
The goal of this lab is for you to get familiar with system level programming
in C using low level interfaces and buffer manipulation. You will write a
program that will read the content of a file, perform a string replacement on
those contents, and print out the result. It will work similarly to Unix grep
except that it performs string replacement in addition to matching, and it does
not support regular expressions or reading from standard input. But because of
the similarities, our command will be called strep.

## Specifications
Here is how the strep command works. Imagine a file named test.txt contains the
following lines: `foo a b c d foo e A foo B 0 foo 1 2 foo`

We could replace all occurrences of foo with goo as follows (assume we are in
the same directory containing foo.txt):
```
$ ./strep foo goo test.txt
goo a b c d goo e A goo B 0 goo 1 2 goo
$
```

* The arguments to strep are passed via the command line and can be accessed
  through the variable `argv` in main. The user must enter three arguments
  after the command. The first argument is the string to match (e.g., `foo`),
  the second is the replacement string (e.g., `goo`), and the third is the file
  to read from (e.g., `test.txt`).

* Strep replaces all occurrences of foo with goo on a particular line, not just
  the first occurrence (although it will not replace a single string that spans
  multiple lines). In this lab, you will write the strep program in C. You will
  want to consult your C programming language textbook as well as the following
  resources:
  * [Intro to C for Java Programmers by Mark Handley (pdf)](http://www.site.uottawa.ca/~mgarz042/CSI3131/files/c-introHandley.pdf)
  * [C Programming Reference by Dave Marshall (html)](https://www.cs.cf.ac.uk/Dave/C/CE.html)

* You are allowed to use the `exit` function from `stdlib.h` (i.e. to use it you
  must put `#include <stdlib.h>` near the top of your program file) and `printf`
  (or `fprintf`) from `stdio.h`. To read from a file, you may use only the
  low-level I/O functions:
  * __int open(char * name, int flags, int perm)__: name is the name of the file to
    open, flags specifies how to open the file (e.g. for reading), and perm
    specifies the permissions to use for the file if creating a new file. open
    returns a handle (non-negative int) to the file or a negative number on an
    error. You should make flags `0` for reading and you can use any value for
    perm (which is ignored when reading). Note: don't confuse with `fopen`,
    which you may __NOT__ use.
  * __int read(int handle, char * buf, int length)__: `handle` is a handle to the
    file to read from, `buf` is an array pointer where the read characters
    should be placed, and length is the number of characters that should be read
    (`read` can read fewer characters if the end-of-file is reached or an error
    occurs). read returns the number of characters read. Note: don't confuse
    with `fread`, which you may __NOT__ use.
  * __lseek__: you are responsible for finding the interface for this function.
    Note: don't confuse with `fseek`, which you may __NOT__ use.

* You should include at most two interface files: `stdlib.h` and `stdio.h`.
  Moreover, you should only use the functions explicitly mentioned above from
  these two interfaces. If you need functions for manipulating character
  strings (e.g., finding out the length of the string), for instance, you will
  need to write these functions yourself.

Your program will need to be able to iterate over the command-line arguments
using `argc` and `argv`. There many
[resources](http://users.cs.cf.ac.uk/Dave.Marshall/C/node12.html#SECTION001220000000000000000)
on the subject.

## Good Programming Style
As in Java, remember to use good programming style when programming in C. It is
important to make sure that others can easily read and understand your programs
(perhaps more important in C). Your program should obey the following rules of
good programming style:
* Put a comment at the beginning of each C file that explains the purpose of
  the code within the file. Include your name and the assignment name in this
  comment.
* Use meaningful variable and function names which suggest the role of the
  variable or method in the program, while avoiding extremely long names.
  Single-letter names are rarely appropriate.
* Use lowercase for all the letters in a variable, function, or struct name.
  You can use `_` to combine multiple words into a single identifier (e.g.,
  `num_words`, `is_prime`, `linked_list_t`). Use `_t` at the end of a struct
  name to show that it is a type.
* Use all uppercase letters for a preprocessor constant (e.g., `DEBUG`,
  `MAX_CHARS`).
* Use indentation to show the structure of the program. This means that you
  should indent the statements inside the function and the functions within a
  block statement. In general, any statements that follow `{` should be indented.
* Do not have lines longer than 80 characters. (80 characters is the standard
  for how much text can be printed on one line of paper.) The easiest way to
  make sure your lines aren't too long is to set the width of your editor window
  to be 80 columns, and then hit return to split any line that wraps onto a
  second line. You can split a line almost anywhere other than in the middle of
  an identifier, operator, or string. Good places are typically right after
  operators or commas.
* Use comments to describe any complicated control flow used in your program.
* Put a comment above each function describing the functionality of the
  function, as well as its assumptions, parameters, and return value.
* Don't overuse preprocessor directives as they can over complicate your
  program. For now, just use them for constants.
* Don't use comments to explain how C works. Assume that anyone reading a C
  source code file knows C. A comment such as "declare a variable named
  interestRate" is useless. However, the comment "annual interest rate,
  expressed in decimal form" gives information that makes the program easier
  to understand.

## Setup
You will get two files: `strep.c` and `test.txt`. You can compile `strep.c` to
get an executable `strep`. Once you have compiled strep.c (assuming it was
successful), you can run it by executing the following:
```
$./strep foo goo test.txt
```

## Implementation Strategy
The following is a sample implementation strategy for creating the strep
program incrementally.

1. Compile the provided file and make sure `gcc` works.
2. Print out the number of arguments and the arguments received by the main
  function. Recompile and run the program using the following command (the
  sample output is from the instructor’s program):
```
$./strep foo bar x.y
number of arguments:4
command name:./strep
old string: foo
new string: bar
file name: x.y
```
3. Print the content of the `test.txt` file to standard output using the
  `fopen()` and `fgets()` library functions. Examples can be found in the C
  tutorial. You need a buffer for reading the file. See the man pages for
  `fopen()` and `fgets()` usage details.
4. Change `fopen()` and `fgets()` to `open()` and `read()` respectively. Please
  use the man pages to learn about these two system call functions: their
  parameters and return values. Note that the `open()` function takes mode
  flags, which are integers, and there are macros defined for commonly used
  flags. For example, `O_RDONLY` means opening the file for read only. Because
  `read()` will not add null terminators automatically to strings in buffers,
  you will need to deal with that yourself.
5. Find the occurrences of the old string in the read buffer and replace them
  with the new string before printing the modified string out. You can use the
  `strncmp()` and `strncpy()` library functions (see their man pages for usage
  details). strep.c includes a `string_length()`, which can be used to get the
  length of a string excluding the `null` terminator. You may need another
  buffer to store the modified string (after token replacement). One pointer
  can be used to scan through the read buffer one character at a time checking
  all possible matches. If there is no match, just copy the current character
  over to the new buffer. Otherwise, write the new string in the new buffer and
  skip the old string in the read buffer.
6. So far the program should work __correctly__ most of the time. What if there
  is a target string (to be replaced) straddling two reads? You will need to use
  `lseek()` function (system call) to address this issue.

## About Man Pages
<PRE>
UNIX man page is generally split into eight sections as follows:
(http://en.wikipedia.org/wiki/Man_page)
Section	Description
1		General commands
2		System calls
3		Library functions, covering in particular the C standard library
4		Special files (usually devices, those found in /dev) and drivers
5		File formats and conventions
6		Games and screensavers
7		Miscellanea
8		System administration commands and daemons

PRINTF(3)
NAME
       printf,   fprintf,  sprintf - formatted output conversion
SYNOPSIS
       #include <stdio.h>

       int printf(const char *format, ...);
       int fprintf(FILE *stream, const char *format, ...);
       int sprintf(char *str, const char *format, ...);
DESCRIPTION
       The functions in the printf() family produce output according to a for‐
       mat as described below.  The functions  printf() writes
       output  to stdout, the standard output stream; fprintf()
       writes  output  to  the  given  output  stream;  sprintf() writes to the
       character string str.

       These  functions  write the output under the control of a format
       string that specifies how subsequent arguments are converted
       for output.

OPEN(2)
NAME
       open, creat - open and possibly create a file or device

SYNOPSIS
       #include <fcntl.h>

       int open(const char *pathname, int flags);

DESCRIPTION
       Given a pathname for a file, open() returns a file descriptor, a small,
       nonnegative integer  for  use  in  subsequent  system  calls  (read(2),
       write(2), lseek(2), fcntl(2), etc.).  The file descriptor returned by a
       successful call will be the lowest-numbered file  descriptor  not  cur‐
       rently open for the process.

       By  default,  the  new  file descriptor is set to remain open across an
       execve(2).  The file offset  is  set  to  the
       beginning of the file (see lseek(2)).

       A  call  to open() creates a new open file description, an entry in the
       system-wide table of open files.  This entry records  the  file  offset
       and  the  file status flags.
       A file descriptor is a reference to one of these entries;  this
       reference is unaffected if pathname is subsequently removed or modified
       to refer to a different file.  The new open file  description  is  ini‐
       tially  not  shared  with  any other process, but sharing may arise via
       fork(2).

       The argument flags must include one  of  the  following  access  modes:
       O_RDONLY,  O_WRONLY,  or  O_RDWR.  These request opening the file read-
       only, write-only, or read/write, respectively.

READ(2)
NAME
       read - read from a file descriptor

SYNOPSIS
       #include <unistd.h>

       ssize_t read(int fd, void *buf, size_t count);

DESCRIPTION
       read()  attempts to read up to count bytes from file descriptor fd into
       the buffer starting at buf.

       If count is zero, read() returns zero and has  no  other  results.   If
       count is greater than SSIZE_MAX, the result is unspecified.

RETURN VALUE
       On success, the number of bytes read is returned (zero indicates end of
       file), and the file position is advanced by this number.  It is not  an
       error  if  this  number  is smaller than the number of bytes requested;
       this may happen for example because fewer bytes are actually  available
       right  now  (maybe  because we were close to end-of-file, or because we
       are reading from a pipe, or from a terminal),  or  because  read()  was
       interrupted  by  a  signal.  On error, -1 is returned, and errno is set
       appropriately.  In this case it is left unspecified  whether  the  file
       position (if any) changes.

ERRORS
       EAGAIN The  file descriptor fd refers to a file other than a socket and
              has been marked nonblocking (O_NONBLOCK),  and  the  read  would
              block.
       …

FGETS(3)
NAME
       fgets - input of strings

SYNOPSIS
       #include <stdio.h>

       char *fgets(char *s, int size, FILE *stream);

DESCRIPTION
       fgets() reads in at most one less than size characters from stream  and
       stores  them  into  the buffer pointed to by s.  <mark>Reading stops
       after an EOF or a newline</mark>.  If a newline is read, it is stored
       into the  buffer. A  terminating  null  byte ('\0') is stored after the
       last character in the buffer.

RETURN VALUE
       fgets() return s on success, and NULL on error or when end
       of file occurs while no characters have been read.

STRCMP(3)
NAME
       strcmp, strncmp - compare two strings

SYNOPSIS
       #include <string.h>

       int strcmp(const char *s1, const char *s2);

       int strncmp(const char *s1, const char *s2, size_t n);

DESCRIPTION
       The  strcmp()  function compares the two strings s1 and s2.  It returns
       an integer less than, equal to, or greater than zero if  s1  is  found,
       respectively, to be less than, to match, or be greater than s2.

       The  strncmp()  function  is similar, except it only compares the first
       (at most) n characters of s1 and s2.

RETURN VALUE
       The strcmp() and strncmp() functions return an integer less than, equal
       to, or greater than zero if s1 (or the first n bytes thereof) is found,
       respectively, to be less than, to match, or be greater than s2.
</PRE>
<a name="myfootnote1">1</a>: Modified from an assignment by by Marc Corliss
