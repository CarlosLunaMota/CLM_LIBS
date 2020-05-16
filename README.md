***********************************************************************

# CLM\_LIBS

***********************************************************************

**CONTENT:** The CLM_LIBS code-generating macros

**AUTHOR:**  Carlos Luna Mota

**SOURCE:**  [https://github.com/CarlosLunaMota/CLM_LIBS](https://github.com/CarlosLunaMota/CLM_LIBS)

**TABLE OF CONTENTS:**

* [INTRODUCTION](#INTRODUCTION-)
* [CODE CONVENTIONS](#CODE-CONVENTIONS-)
* [CODE DEPENDENCIES](#CODE-DEPENDENCIES-)
* [CODE LICENSE](#CODE-LICENSE-)
* [THE MACROS](#THE-MACROS-)
    * [CLM\_LIBS](#CLM_LIBS-1-)
    * [CLM\_TIME](#CLM_TIME-)
    * [CLM\_RAND](#CLM_RAND-)
    * [CLM\_PRINTF](#CLM_PRINTF-)
    * [CLM\_ARC4](#CLM_ARC4-)
    * [CLM\_ITER](#CLM_ITER-)
    * [CLM\_FRACTAL](#CLM_FRACTAL-)
    * [CLM\_ARRAY](#CLM_ARRAY-)
    * [CLM\_CLIST](#CLM_CLIST-)
    * [CLM\_STREE](#CLM_STREE-)
    * [CLM\_WTREE](#CLM_WTREE-)

***********************************************************************

## INTRODUCTION [:top:](#CLM_LIBS)

This is a collection of code-generating macros for the C preprocessor.

The main motivation to write these macros is to put together all the
functions that I frequently use in my C projects so I can test them
properly, document them properly and trust them hereafter.

I am using the code-generating macro approach for writting these
libraries because I wanted to provide generic data structures without
using `void` pointers.

Although this is a personal project, I am trying to document everything
so others can use this code too. For the same reason I release the code
into the Public Domain using the Unlicense (see LICENSE section below).

***********************************************************************

## CODE CONVENTIONS [:top:](#CLM_LIBS)

Each library is just a code generating macro whose name starts with
`IMPORT_CLM_`. The C preprocessor will substitute each macro call with
a set of functions and type definitions before compiling the code, so
you just get the same behavior that you would get if you coded these
auxilary functions and data types by hand (including type-safety).

The name of all types and functions starts with the name of the library
(macro) they belong to. The user can add an optional prefix to all the
functions and data types when calling a macro to avoid conflicts with
existing code or different calls to the same macro.

All `CLM_LIBS` functions are declared as `static inline` and are
mutually independent (no `CLM_LIBS` function calls any other `CLM_LIBS`
function) although some of them are recursive (they call themselves).
This self-imposed constraint hurts modularity and readability but
simplifies the task of versioning and reusing the code: You could erase
or substitute any function without worrying about dependencies.

I am willing to sacrfice efficiency for practical reasons like safety,
versatility or interface coherence. I will probably be the main user of
these libraries so I want them to be easy to use rather than fast or
easy to code. If performance is your main concern, there might be
better libraries out there (that will probably be WAY more difficult to
use). This being said, I will try to provide code that is efficient in
terms of time and space. I just will not agonize about it.

I am also not targeting outdated C compilers or embeded systems. I make
use of C99 features and manage the memory allocations with the standard
`malloc` and `free` functions. I am writing these libraries to be easy
to read and modify so anyone can adapt them to their needs, though.

Finally, regarding data types:

 * `double` is the default floating point type
 * `size_t` is the default index and size type (transdichotomous model)
 * `char *` is the default `\0`-ended string type
 * `bool`   is the default boolean type (rather than `int`)
 * All container types are named as the macro they belong to and are
   pointers to the corresponding structs (same name with `_s` suffix).

***********************************************************************

## CODE DEPENDENCIES [:top:](#CLM_LIBS)

`CLM_LIBS.h` relies only on the C standard library and compiles without
warnings using the GCC parameters `-std=c99 -Wall -Wextra -pedantic`.
More over, the code has been tested using `valgrind --leak-check=full`
reporting no memory leak.

The standard libraries used are (in alphabetical order):

```c
#include <assert.h>
#include <float.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
```

***********************************************************************

## CODE LICENSE [:top:](#CLM_LIBS)

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to [http://unlicense.org/](http://unlicense.org/)

***********************************************************************

## THE MACROS [:top:](#CLM_LIBS)

Each macro generates a collection of related functions and typedefs.

All the macros have an optional parameter `prefix` that allows the
user to change the name of the functions and data types so they don't
crash with other user-defined functions/types or with different calls
of the same macro.

Some of the macros require two mandatory parameters (`type` & `less`)
that are used to build generic functions tailored to that data type.

The `type` parameter could be any standard or user-defined data type.

The `less` parameter should be the name (NOT A POINTER, JUST THE NAME)
of a comparing function/macro for the corresponding data type.

The `bool less(const type x, const type y)` function must accept two
`const type` values and return:

 * `less(x, y) == true`     if   `x <  y`
 * `less(x, y) == false`    if   `x >= y`

**Example:**

```c
#include "CLM_LIBS.h"

#define LESS_NUM(i, j) ((i)<(j))

typedef struct pair { int i; double d; } pair_t;

bool less_pair(const pair_t p1, pair_t p2) {
    return (p1.i < p2.i || (p1.i == p2.i && p1.d < p2.d));
}

IMPORT_CLM_RAND()
IMPORT_CLM_ARRAY(int, LESS_NUM, int_)
IMPORT_CLM_ARRAY(double, LESS_NUM, dbl_)
IMPORT_CLM_STREE(pair_t, less_pair, )

int main(void) {

    pair_t    pair;
    size_t    i, N = 10;
    stree     tree = NULL;
    int_array A    = int_array_new(N);
    dbl_array B    = dbl_array_new(N);

    printf("\nRANDOM:\n");
    for (i = 0; i < N; i++) {
        A[i] = rand_int(100);
        B[i] = rand_double(100);
        printf("\t(%d, %f)\n", A[i], B[i]);
    }

    printf("\nLEXICOGRAPHICALLY SORTED:\n");
    for (i = 0; i < N; i++) {
        pair.i = A[i];
        pair.d = B[i];
        stree_insert(&tree, pair);
    }
    stree_min(&tree);
    while (tree) {
        pair = stree_pop(&tree);
        printf("\t(%d, %f)\n", pair.i, pair.d);
    }

    printf("\nINDEPENDENTLY SORTED:\n");
    int_array_sort(A, N);
    dbl_array_sort(B, N);
    for (i = 0; i < N; i++) { printf("\t(%d, %f)\n", A[i], B[i]); }

    free(A);
    free(B);
}
```

*********************************************************************

### CLM\_LIBS [:top:](#CLM_LIBS)

```c
#define CLM_LIBS 20200516
```

Contains the version number (= date) of this release of CLM_LIBS.

*********************************************************************

### CLM\_TIME [:top:](#CLM_LIBS)

```c
#define IMPORT_CLM_TIME(prefix)
```

A set of time-related and date-related functions.

*******************************************************************

#### time\_elapsed [:top:](#CLM_LIBS)

```c
static inline double time_elapsed(const clock_t crono);
```

Returns a `double` with the number of seconds elapsed since the
last time you executed: `crono = clock();`

**Example:** Compare the performance of two functions with:

```c
clock_t crono = clock();
Funtion_1();
printf("Function 1 = %.3f sec.\n", time_elapsed(crono));

crono = clock();
Function_2();
printf("Function 2 = %.3f sec.\n", time_elapsed(crono));
```

*******************************************************************

#### time\_pause [:top:](#CLM_LIBS)

```c
static inline void time_pause(const char* message);
```

Flushes the `stdin`, prints `message` in the `stdout` and then
reads the `stdin` until a `\n` or a `EOF` appears.

**Warning:** If `message == NULL` prints the default message:

```c
">> Press return to resume <<\n"
```

**Example:** Pause the program until the user hits return with:

```c
show_results();
time_pause("\t\tPAUSE: Press return to resume.\n");
show_more_results();
```

*******************************************************************

#### time\_stamp [:top:](#CLM_LIBS)

```c
static inline char *time_stamp(const int format);
```

Returns a `\0` ended string with a timestamp formated as follows:

 * The `Year  ` will be included if the 6th bit of `format` is 1.
 * The `Month ` will be included if the 5th bit of `format` is 1.
 * The `Day   ` will be included if the 4th bit of `format` is 1.
 * The `hour  ` will be included if the 3rd bit of `format` is 1.
 * The `minute` will be included if the 2nd bit of `format` is 1.
 * The `second` will be included if the 1st bit of `format` is 1.
 * The output will be "machine friendly" if `format >= 0`.
 * The output will be "human   friendly" if `format <  0`.

Some useful examples:

 * `get_timestamp( 32+16+8+4+2+1);` returns `"YYYYMMDDhhmmss"`
 * `get_timestamp( 32+16+8+4+2);  ` returns `"YYYYMMDDhhmm"`
 * `get_timestamp( 32+16+8);      ` returns `"YYYYMMDD"`
 * `get_timestamp(         4+2+1);` returns `"hhmmss"`
 * `get_timestamp(-32-16-8-4-2-1);` returns `"YYYY/MM/DD hh:mm:ss"`
 * `get_timestamp(-32-16-8-4-2);  ` returns `"YYYY/MM/DD hh:mm"`
 * `get_timestamp(-32-16-8);      ` returns `"YYYY/MM/DD"`
 * `get_timestamp(-32-16);        ` returns `"YYYY/MM"`
 * `get_timestamp(   -16-8-4-2-1);` returns `"MM/DD hh:mm:ss"`
 * `get_timestamp(   -16-8-4-2);  ` returns `"MM/DD hh:mm"`
 * `get_timestamp(   -16-8);      ` returns `"MM/DD"`
 * `get_timestamp(        -4-2-1);` returns `"hh:mm:ss"`
 * `get_timestamp(        -4-2);  ` returns `"hh:mm"`

**Warning:** The user should free the string after using it.

**Warning:** The case `format == 0` defaults to `format == 63`.

**Example:** Output `MyString` in a timestamped file with:

```c
char filename[36];
char *timestamp = time_stamp(0);

sprintf(filename, "output_%s.txt", timestamp);
FILE *MyOutput = fopen(filename, "a");
fprintf(MyOutput, MyString);

fclose(MyOutput);
free(timestamp);
```

*********************************************************************

### CLM\_RAND [:top:](#CLM_LIBS)

```c
#define IMPORT_CLM_RAND(prefix)
```

A set of random and quasi-random number generators.

*******************************************************************

#### rand\_int [:top:](#CLM_LIBS)

```c
static inline int rand_int(const int n);
```

Returns an uniformly random `int` in the range `[0, n)`.

**Warning:** Parameter `n` must satisfy `RAND_MAX >= n > 0`.

**Example:** Print 10 random `int` in the range `[A, B]` with:

```c
size_t i;
for (i = 0; i < 10; i++) { printf("%d ", A+rand_int(B-A+1)); }
```

*******************************************************************

#### rand\_size\_t [:top:](#CLM_LIBS)

```c
static inline size_t rand_size_t(const size_t n);
```

Returns an uniformly random `size_t` in the range `[0, n)`.

**Warning:** Parameter `n` must satisfy `RAND_MAX >= n > 0`.

**Example:** Select a random element from an array of size N with:

```c
type elem = MyArray[rand_size_t(N)];
```

*******************************************************************

#### rand\_double [:top:](#CLM_LIBS)

```c
static inline double rand_double(const double n);
```

Returns an uniformly random `int` in the range `[0.0, n)`.

**Warning:** Parameter `n` must satisfy `n > DLB_EPSILON`.

**Example:** Print 10 random `double` in the range `[A, B)` with:

```c
size_t i;
for (i = 0; i < 10; i++) { printf("%f ", A+rand_double(B-A)); }
```

*******************************************************************

#### rand\_halton [:top:](#CLM_LIBS)

```c
static inline double rand_halton(const size_t base, size_t n);
```

Returns a quasi-random number in the range `[0.0, 1.0)`.

More specifically, returns the `n`-th element of the Halton
low-discrepancy sequence that has the `base` as a base.

In general it is advisable to use small prime numbers as `base`.
In particular, if you need to produce quasi-random D-dimensional
points, you should use `D` coprime numbers as 'base', one for each
dimension (see example below).

**Warning:** Parameter `base` must satisfy `base > 1`.

**Warning:** The algorithm is deterministic, which means that for
a fixed `(base, n)` input, it will always provide the same output.

**Example:** Get 100 quasi-random 3D points with:

```c
double *X = (double *) malloc(100 * sizeof(double));
double *Y = (double *) malloc(100 * sizeof(double));
double *Z = (double *) malloc(100 * sizeof(double));
if (X && Y && Z) {
    for (size_t i = 0; i < 100; i++) {
        X[i] = x_min + (x_max-x_min)*quasi_rand(2, i);
        Y[i] = y_min + (y_max-y_min)*quasi_rand(3, i);
        Z[i] = z_min + (z_max-z_min)*quasi_rand(5, i);
    }
}
```

*******************************************************************

#### rand\_color [:top:](#CLM_LIBS)

```c
static inline void rand_color(int *r, int *g, int *b);
```

Returns a random RGB color with the same Saturation and Brightness
(but different Hue) than the RGB color provided.

More specifically, generates a low discrepancy sequence of colors
based on the additive recurrence:

```c
Hue[n] = (Hue[n-1] + (phi-1)) % 1.0
```

where Hue is taken in the [0.0, 1.0) range and:

```c
phi = (1.0 + sqrt(5.0)) / 2.0 = 1.61803398874989484820458683436
```

**Warning:** `r`, `g` and `b` must be integers in [0, 255].

**Warning:** The algorithm is deterministic, which means that for
a fixed input color, it will always provide the same output color.

**Example:** Generate 5 random colors with:

```c
int r = 255;
int g = 135;
int b =   0;
int R[5]; G[5]; B[5];
for (size_t i = 0; i < 5; i++) {
    rand_color(&r, &g, &b);
    R[i] = r; G[i] = g; B[i] = b;
}
```

*********************************************************************

### CLM\_PRINTF [:top:](#CLM_LIBS)

```c
#define IMPORT_CLM_PRINTF(prefix)
```

A set of formatting functions for the standard terminal output.

*******************************************************************

#### printf\_reset [:top:](#CLM_LIBS)

```c
static inline void printf_reset();
```

Resets all formating parameters of printf to their default values.

**Example:** Give your command line a "retro look" with:

```c
printf_reset();
printf_set_back_color(0x00, 0x00, 0x00);
printf_set_text_color(0x33, 0xFF, 0x00);
```

*******************************************************************

#### printf\_set\_bold [:top:](#CLM_LIBS)

```c
static inline void printf_set_bold();
```

Sets the printf function in boldface mode.

**Example:** Print the string `txt` in boldface with:

```c
printf_set_bold();
printf("%s", txt);
printf_reset();
```

*******************************************************************

#### printf\_set\_light [:top:](#CLM_LIBS)

```c
static inline void printf_set_light();
```

Sets the printf function in lightface mode.

**Example:** Print the string `txt` in lightface with:

```c
printf_set_light();
printf("%s", txt);
printf_reset();
```

*******************************************************************

#### printf\_set\_strike [:top:](#CLM_LIBS)

```c
static inline void printf_set_strike();
```

Sets the printf function in strikethrough mode.

**Example:** Print the string `txt` striked with:

```c
printf_set_strike();
printf("%s", txt);
printf_reset();
```

*******************************************************************

#### printf\_set\_underline [:top:](#CLM_LIBS)

```c
static inline void printf_set_underline();
```

Sets the printf function in underline mode.

**Example:** Print the string `txt` underlined with:

```c
printf_set_underline();
printf("%s", txt);
printf_reset();
```

*******************************************************************

#### printf\_set\_text\_grey [:top:](#CLM_LIBS)

```c
static inline void printf_set_text_grey(const int grey);
```

Sets a greyscale text color for the printf function.

The greyscale palette goes from black (`0`) to white (`23`).

**Warning:** `grey` must be a integer in the range [0, 23].

**Example:** Print the string `txt` in white with:

```c
printf_set_text_grey(23);
printf("%s", txt);
printf_reset();
```

*******************************************************************

#### printf\_set\_back\_grey [:top:](#CLM_LIBS)

```c
static inline void printf_set_back_grey(const int grey);
```

Sets a greyscale background color for the printf function.

The greyscale palette goes from black (`0`) to white (`23`).

**Warning:** `grey` must be a integer in the range [0, 23].

**Example:** Print the string `txt` on a white background with:

```c
printf_set_back_grey(23);
printf("%s", txt);
printf_reset();
```

*******************************************************************

#### printf\_set\_text\_color [:top:](#CLM_LIBS)

```c
static inline void printf_set_text_color(const int r, const int g, const int b);
```

Sets the color of the text for the printf function.

The actual color of the text will be the closest color to `(r,g,b)`
in the web-safe palette: `[0x00, 0x33, 0x66, 0x99, 0xCC, 0xFF]^3`

**Warning:** `r`, `g` and `b` must be integers in `[0, 255]`.

**Example:** Print the string `txt` in red with:

```c
printf_set_text_color(0xFF, 0x00, 0x00);
printf("%s", txt);
printf_reset();
```

*******************************************************************

#### printf\_set\_back\_color [:top:](#CLM_LIBS)

```c
static inline void printf_set_back_color(const int r, const int g, const int b);
```

Sets the color of the background for the printf function.

The actual background color will be the closest color to `(r,g,b)`
in the web-safe palette: `[0x00, 0x33, 0x66, 0x99, 0xCC, 0xFF]^3`

**Warning:** `r`, `g` and `b` must be integers in `[0, 255]`.

**Example:** Print the string `txt` on a blue background with:

```c
printf_set_back_color(0, 0, 255);
printf("%s", txt);
printf_reset();
```

*********************************************************************

### CLM\_ARC4 [:top:](#CLM_LIBS)

```c
#define IMPORT_CLM_ARC4(prefix)
```

A set of functions related to the ARC4 stream cypher.

All these functions assume (and enforce through assertions) that the
`char` type has a width of (exactly) 8 bits. This is quite common,
but not necessarily true in all systems. This macro cannot be used
in systems where that condition is not satisfied.

*******************************************************************

#### arc4\_hash [:top:](#CLM_LIBS)

```c
static inline char *arc4_hash(const char *txt, const size_t length, const size_t drop);
```

Returns a hash of the `txt` string.

The output is formated as a `\0` terminated array of `char` of
twice the specified `length`. Each character is in hexadecimal
format (i.e. all characters belong to `[0,...,9,A,...,F]`).

Parameter `drop` specifies how many pseudo-random bytes will be
discarded before computing the hash. It is recomended to select a
multiple of 256 as a `drop` (classic ARC4 defaults `drop` to 0).

**Warning:** ARC4 IS NO LONGER CONSIDERED CRYPTOGRAPHICALLY SAFE.

**Warning:** The `txt` parameter must be a `\0` terminated string.

**Example:** Get N pseudo-random bytes with:

```c
size_t i, ii;
char   c;
char  *seed   = "MySeed";
char  *hash   = arc4_hash(seed, N, 0);
char  *stream = (char *) malloc(N * sizeof(char));
assert(hash != NULL && stream != NULL);
for (i = ii = 0; i < N; i++) {
    c = hash[ii++];
    if ('0' <= c && c <= '9') { stream[i] = (c-'0')<<4; }
    else                      { stream[i] = (c-'A')<<4; }
    c = hash[ii++];
    if ('0' <= c && c <= '9') { stream[i] += (c-'0'); }
    else                      { stream[i] += (c-'A'); }
}
free(hash);
```

*******************************************************************

#### arc4\_encrypt [:top:](#CLM_LIBS)

```c
static inline char *arc4_encrypt(const char *txt, const char *key, const size_t drop);
```

Encrypts the `txt` string using the `key` string.

The output is formated as a `\0` terminated array of `char` that is
twice as long as `txt`. Each character is in hexadecimal format
(i.e. all characters belong to `[0,...,9,A,...,F]`).

Parameter `drop` specifies how many pseudo-random bytes will be
discarded before encrypting `txt`. It is recomended to select a
multiple of 256 as a `drop` (classic ARC4 defaults `drop` to 0).

Classic ARC4 requires `0 < strlen(key) <= 256`. This version
accepts smaller or larger `key` strings but is guaranteed to
produce the same output as the classic ARC4 if the `key` satisfies
the `0 < strlen(key) <= 256` condition.

**Warning:** ARC4 IS NO LONGER CONSIDERED CRYPTOGRAPHICALLY SAFE.

**Warning:** The `key` parameter must be a `\0` terminated string.

**Warning:** The `txt` parameter must be a `\0` terminated string.

**Example:** Encrypt "Attack at dawn" using "Secret" as key with:

```c
char *code = arc4_encrypt("Attack at dawn", "Secret", 0);
if (code != NULL) { printf("Encrypted: '%s'\n", code); }
free(code);
```

*******************************************************************

#### arc4\_decrypt [:top:](#CLM_LIBS)

```c
static inline char *arc4_decrypt(const char *txt, const char *key, const size_t drop);
```

Decrypts the `txt` string using the `key` string.

The `txt` must be formated as a `\0` terminated array of `char` in
hexadecimal format (all characters belong to `[0,...,9,A,...,F]`).

Parameter `drop` specifies how many pseudo-random bytes will be
discarded before encrypting `txt`. It is recomended to select a
multiple of 256 as a `drop` (classic ARC4 defaults `drop` to 0).

Classic ARC4 requires `0 < strlen(key) <= 256`. This version
accepts smaller or larger `key` strings but is guaranteed to
produce the same output as the classic ARC4 if the `key` satisfies
the `0 < strlen(key) <= 256` condition.

**Warning:** ARC4 IS NO LONGER CONSIDERED CRYPTOGRAPHICALLY SAFE.

**Warning:** The `key` parameter must be a `\0` terminated string.

**Warning:** The `txt` parameter must be a `\0` terminated string.

**Example:** Decrypt the coded message using "Secret" as key with:

```c
char *code = "45A01F645FC35B383552544B9BF5"
char *txt  = arc4_decrypt(code, "Secret", 0);
if (txt != NULL) { printf("Decrypted: '%s'\n", txt); }
free(txt);
```

*********************************************************************

### CLM\_ITER [:top:](#CLM_LIBS)

```c
#define IMPORT_CLM_ITER(prefix)
```

A set of functions to work with some generic combinatorial objects:

**Products:** all mixed-radix tuples of fixed `length`

```c
  Products(3, (2,3,4)) = {(0,0,0), (0,0,1), (0,0,2), (0,0,3),
                          (0,1,0), (0,1,1), (0,1,2), (0,1,3),
                          (0,2,0), (0,2,1), (0,2,2), (0,2,3),
                          (1,0,0), (1,0,1), (1,0,2), (1,0,3),
                          (1,1,0), (1,1,1), (1,1,2), (1,1,3),
                          (1,2,0), (1,2,1), (1,2,2), (1,2,3)}
```

**Permutations:** all unsorted tuples of fixed `length` whose
elements are all different and taken from a set of size `base`

```c
  Permutations(3, 4) = {(0,1,2), (0,2,1), (1,0,2), (1,2,0),
                        (2,0,1), (2,1,0), (0,1,3), (0,3,1),
                        (1,0,3), (1,3,0), (3,0,1), (3,1,0),
                        (0,2,3), (0,3,2), (2,0,3), (2,3,0),
                        (3,0,2), (3,2,0), (1,2,3), (1,3,2),
                        (2,1,3), (2,3,1), (3,1,2), (3,2,1)}
```

**Permutations with repetition:** all unsorted tuples of fixed
`length` whose elements are taken with replacement from a set of
size `base`

```c
  Perm_with_rep(3, 4) = {(0,0,0), (0,0,1), (0,0,2), (0,0,3),
                         (0,1,0), (0,1,1), (0,1,2), (0,1,3),
                         (0,2,0), (0,2,1), (0,2,2), (0,2,3),
                         (0,3,0), (0,3,1), (0,3,2), (0,3,3),
                         (1,0,0), (1,0,1), (1,0,2), (1,0,3),
                         (1,1,0), (1,1,1), (1,1,2), (1,1,3),
                         (1,2,0), (1,2,1), (1,2,2), (1,2,3),
                         (1,3,0), (1,3,1), (1,3,2), (1,3,3),
                         (2,0,0), (2,0,1), (2,0,2), (2,0,3),
                         (2,1,0), (2,1,1), (2,1,2), (2,1,3),
                         (2,2,0), (2,2,1), (2,2,2), (2,2,3),
                         (2,3,0), (2,3,1), (2,3,2), (2,3,3),
                         (3,0,0), (3,0,1), (3,0,2), (3,0,3),
                         (3,1,0), (3,1,1), (3,1,2), (3,1,3),
                         (3,2,0), (3,2,1), (3,2,2), (3,2,3),
                         (3,3,0), (3,3,1), (3,3,2), (3,3,3)}
```

**Combinations:** all sorted tuples of fixed `length` whose elements
are all different and taken from a set of size `base`:

```c
  Combinations(3, 4) = {(0,1,2), (0,1,3), (0,2,3), (1,2,3)}
```

**Combinations with repetition:** all sorted tuples of fixed `length`
whose elements are taken with replacement from a set of size `base`:

```c
  Comb_with_rep(3, 4) = {(0,0,0), (0,0,1), (0,0,2), (0,0,3),
                         (0,1,1), (0,1,2), (0,1,3), (0,2,2),
                         (0,2,3), (0,3,3), (1,1,1), (1,1,2),
                         (1,1,3), (1,2,2), (1,2,3), (1,3,3),
                         (2,2,2), (2,2,3), (2,3,3), (3,3,3)}
```

For each combinatorial object three functions are provided:

* `iter_num_`  returns the number of elements in the object.
* `iter_rand_` returns an uniformly random element of the object.
* `iter_next_` given an element of the object, returns the next one.

The elements of a combinatorial object are always represented as
`size_t` arrays that contain indexes of the corresponding base set
(i.e. `0 <= array[i] < base`) so you can use them to reference
arbitrary sets of `base` elements.

*******************************************************************

#### iter\_num\_prod [:top:](#CLM_LIBS)

```c
static inline size_t iter_num_prod(const size_t length, const size_t *base);
```

Returns the number of "length"-sized tuples such that the element
0 <= tuple[i] < base[i]   for i = 0...length-1.

**Warning:** Parameter `length` must satisfy `lenght > 0`.

**Warning:** Parameter `base` must satisfy `base != NULL` and also
`base[i] > 0` for al `i = 0...length-1`.

**Example:** Iterate throught all products of [0..4]x[0..2] with:

```c
size_t length  = 2;
size_t base[2] = {5, 3};
size_t *prod   = NULL;
iter_next_prod(&prod, length, base);
while (prod) {
    do_something(prod);
    iter_next_prod(&prod, length, base);
}
```

*******************************************************************

#### iter\_rand\_prod [:top:](#CLM_LIBS)

```c
static inline size_t *iter_rand_prod(const size_t length, const size_t *base);
```

*******************************************************************

#### iter\_next\_prod [:top:](#CLM_LIBS)

```c
static inline void iter_next_prod(size_t **prod, const size_t length, const size_t *base);
```

*******************************************************************

#### iter\_num\_perm [:top:](#CLM_LIBS)

```c
static inline size_t iter_num_perm(const size_t length, const size_t base);
```

*******************************************************************

#### iter\_rand\_perm [:top:](#CLM_LIBS)

```c
static inline size_t *iter_rand_perm(const size_t length, const size_t base);
```

*******************************************************************

#### iter\_next\_perm [:top:](#CLM_LIBS)

```c
static inline void iter_next_perm(size_t **perm, const size_t length, const size_t base);
```

*******************************************************************

#### iter\_num\_perm\_rep [:top:](#CLM_LIBS)

```c
static inline size_t iter_num_perm_rep(const size_t length, const size_t base);
```

*******************************************************************

#### iter\_rand\_perm\_rep [:top:](#CLM_LIBS)

```c
static inline size_t *iter_rand_perm_rep(const size_t length, const size_t base);
```

*******************************************************************

#### iter\_next\_perm\_rep [:top:](#CLM_LIBS)

```c
static inline void iter_next_perm_rep(size_t **perm, const size_t length, const size_t base);
```

*******************************************************************

#### iter\_num\_comb [:top:](#CLM_LIBS)

```c
static inline size_t iter_num_comb(const size_t length, const size_t base);
```

*******************************************************************

#### iter\_rand\_comb [:top:](#CLM_LIBS)

```c
static inline size_t *iter_rand_comb(const size_t length, const size_t base);
```

*******************************************************************

#### iter\_next\_comb [:top:](#CLM_LIBS)

```c
static inline void iter_next_comb(size_t **comb, const size_t length, const size_t base);
```

*******************************************************************

#### iter\_num\_comb\_rep [:top:](#CLM_LIBS)

```c
static inline size_t iter_num_comb_rep(const size_t length, const size_t base);
```

*******************************************************************

#### iter\_rand\_comb\_rep [:top:](#CLM_LIBS)

```c
static inline size_t *iter_rand_comb_rep(const size_t length, const size_t base);
```

*******************************************************************

#### iter\_next\_comb\_rep [:top:](#CLM_LIBS)

```c
static inline void iter_next_comb_rep(size_t **comb, const size_t length, const size_t base);
```

*********************************************************************

### CLM\_FRACTAL [:top:](#CLM_LIBS)

```c
#define IMPORT_CLM_FRACTAL(prefix)
```

A set of functions to work with some well known space-filling curves.

*******************************************************************

#### fractal\_van\_der\_corput [:top:](#CLM_LIBS)

```c
static inline size_t fractal_van_der_corput(const size_t base, size_t digits, size_t n);
```

Returns the `n`-th element of the Van der Corput sequence with the
specified `base` and number of `digits`.

**Warning:** Parameter `base` must satisfy `base > 1`.

**Warning:** Parameter `digits` must satisfy `digits > 0`.

**Warning:** `n` can be bigger, but only the last `digits` digits
of `n` will be used.

**Warning:** This operations is its own inverse.

**Example:** Print a permutation of the first K^D integers with:

```c
size_t pow = 1;
for (size_t i = 0; i < D; i++) { pow *= K; }
for (size_t N = 0; N < pow; N++) {
    printf("%zu ", fractal_van_der_corput(K, D, N));
}
```

*******************************************************************

#### fractal\_z\_to\_coord [:top:](#CLM_LIBS)

```c
static inline void fractal_z_to_coord(const size_t dim, const size_t bits, size_t *n, size_t *coord);
```

Returns the `dim` dimensional coordinates of the `n`-th point of
the Z-index space-filling curve of `bits` levels.

**Warning:** Parameter `dim` must satisfy `dim > 0`.

**Warning:** Parameter `bits` must satisfy `bits > 0`.

**Warning:** A `size_t` varible must have at least `dim*bits` bits.

*******************************************************************

#### fractal\_z\_to\_coord [:top:](#CLM_LIBS)

```c
static inline void fractal_coord_to_z(const size_t dim, const size_t bits, size_t *n, size_t *coord);
```

Returns the index of the `dim` dimensional point of the given
coordinates in the Z-index space-filling curve of `bits` levels.

**Warning:** Parameter `dim` must satisfy `dim > 0`.

**Warning:** Parameter `bits` must satisfy `bits > 0`.

**Warning:** A `size_t` varible must have at least `dim*bits` bits.

*******************************************************************

#### fractal\_h\_to\_coord [:top:](#CLM_LIBS)

```c
static inline void fractal_h_to_coord(const size_t dim, const size_t bits, size_t *n, size_t *coord);
```

Returns the `dim` dimensional coordinates of the `n`-th point of
the Hilbert space-filling curve of `bits` levels.

**Warning:** Parameter `dim` must satisfy `dim > 0`.

**Warning:** Parameter `bits` must satisfy `bits > 0`.

**Warning:** A `size_t` varible must have at least `dim*bits` bits.

*******************************************************************

#### fractal\_coord\_to\_h [:top:](#CLM_LIBS)

```c
static inline void fractal_coord_to_h(const size_t dim, const size_t bits, size_t *n, size_t *coord);
```

Returns the index of the `dim` dimensional point of the given
coordinates in the Hilbert space-filling curve of `bits` levels.

**Warning:** Parameter `dim` must satisfy `dim > 0`.

**Warning:** Parameter `bits` must satisfy `bits > 0`.

**Warning:** A `size_t` varible must have at least `dim*bits` bits.

*********************************************************************

### CLM\_ARRAY [:top:](#CLM_LIBS)

```c
#define IMPORT_CLM_ARRAY(type, less, prefix)
```

A set of functions to work with arrays.

*******************************************************************

#### array [:top:](#CLM_LIBS)

```c
typedef type *array;
```

Definition of the `array` data type.

*******************************************************************

#### array\_new [:top:](#CLM_LIBS)

```c
static inline array array_new(const size_t length);
```

Allocates an `array` of the given `length`.

**Warning:** Parameter `length` must satisfy `length > 0`.

**Warning:** It might return `NULL` if there is not enough memory.

**Example:** Allocate an `array` of length `N` with:

```c
array A = array_new(N);
```

*******************************************************************

#### array\_sort [:top:](#CLM_LIBS)

```c
static inline void array_sort(const array A, const size_t length);
```

Sorts the first `length` elements of the array `A` in-place.

This function is based on a rather obscure variant of QuickSort
called MedianSort:

```c
void MedianSort(const array A, const size_t length) {

    const size_t MIN_SIZE = 1<<7;

    size_t step, low, high, rank;

    for (step   = 1; step <  length;   step <<= 1);
    for (step >>= 1; step >= MIN_SIZE; step >>= 1) {
        for (rank = step; rank < length; rank += (step << 1)) {
            low  = (rank-step);
            high = (rank+step) > length ? length : (rank+step);
            QuickSelect(A+low, high-low, step);
        }
    }
    if (MIN_SIZE > 1) { InsertionSort(A, length); }
}
```

The implementation relies heavily on the properties of QuickSelect:

If we assume that `QuickSelect` is a non-recursive function that
runs in `O(high-low)` time and `O(1)` space, then `MedianSort` is
a non-recursive function that runs in `O(length*log(length))` time
and `O(1)` space.

This implementation uses a simple variant of `QuickSelect` that is
lightning fast in practice but may require a quadratic number of
steps to finish for some particular inputs (much like QuickSort).

These degenerate cases are VERY rare in practice and do NOT include
sorted arrays, reversely sorted arrays or arrays with many repeated
elements. Indeed, for these three particular cases, the algorithm
performs better than usual (again, much like QuickSort).

Finally, for efficiency reasons, it is advisable to stop the
algorithm early and perform a final `InsertionSort` step. The
constant `MIN_SIZE` controls the breaking point and may be tuned.

**Warning:** The parameter `A` must satisfy: `A != NULL`.

**Warning:** This sorting algorithm is NOT stable.

**Example:** Sort the first N elements of MyArray with:

```c
array_sort(MyArray, N);
```

**Example:** Sort the K smallest elements of MyArray with:

```c
array_select(MyArray, N, K);
array_sort(MyArray, K-1);
```

**Example:** Sort the K biggest elements of MyArray with:

```c
array_select(MyArray, N, N-K-1)
array_sort(MyArray+N-K, N-K);
```

*******************************************************************

#### array\_shuffle [:top:](#CLM_LIBS)

```c
static inline void array_shuffle(const array A, const size_t length);
```

Shuffles the first `length` elements of the array `A` in-place
in `O(length)` time.

**Warning:** The parameter `A` must satisfy: `A != NULL`.

**Example:** Shuffle the first N elements of MyArray with:

```c
array_shuffle(MyArray, N);
```

*******************************************************************

#### array\_select [:top:](#CLM_LIBS)

```c
static inline type array_select(const array A, const size_t length, const size_t rank);
```

Uses Quickselect to find and return the `rank`-th element of an
`array` of size `length` in `O(length)` expected time.

The algorithm is in-place, i.e. the original order of the `array`
can be disturbed during this operation.

In particular, the `k`-th element of the array will be in its
correct place after doing `array_select(A, N, k)`.

Moreover, `A[0:k-1]` will contain the `k-1` elements of `A` that
are smaller or equal than `A[k]` and `A[k+1:length-1]` will contain
the `length-k` elements of `A` that are bigger than `A[k]`.

**Warning:** The parameter `A` must satisfy: `A != NULL`.

**Warning:** The parameters must satisfy: `rank < length`.

**Example:** Find the median of an unsorted array of doubles with:

```c
double median = array_select(MyArray, N, N/2);
```

**Example:** Sort the K smallest elements of MyArray with:

```c
array_select(MyArray, N, K);
array_sort(MyArray, K-1);
```

**Example:** Sort the K biggest elements of MyArray with:

```c
array_select(MyArray, N, N-K-1)
array_sort(MyArray+N-K, N-K);
```

*******************************************************************

#### array\_bisect [:top:](#CLM_LIBS)

```c
static inline size_t array_bisect(const array A, const size_t length, const type data);
```

Returns the rightmost insertion point for `data` in the sorted
array `A` in `O(log(length))` time using binary search.

In particular:

* `data >= A[i]`    in the interval `[0, array_bisect(A, N, data))`
* `data <  A[i]`    in the interval `[array_bisect(A, N, data), N)`

**Warning:** The parameter `A` must satisfy: `A != NULL`.

**Warning:** If `A` is not sorted the behavior is undefined.

**Example:** Find `MyData` in `MyArray` with:

```c
size_t i = array_bisect(MyArray, N, MyData);
if (i > 0 && MyArray[i-1] == MyData) { printf("Found");     }
else                                 { printf("Not found"); }
```

**Example:** Insertion-sort `MyArray` with:

```c
for (size_t i = 1; i < length; ++i) {
     type   t = MyArray[i];
     size_t j = array_bisect(MyArray, N, t);
     memmove(A+j+1, A+j, (i-j)*sizeof(type));
     A[j] = t;
}
```

*********************************************************************

### CLM\_CLIST [:top:](#CLM_LIBS)

```c
#define IMPORT_CLM_CLIST(type, prefix)
```

A set of data types and functions related to the `clist` container.

The `clist` container is implemented as a circular singly-linked list
of dinamically allocated nodes.

The `clist` container can be used to implement either a stack or a
queue but is unable to perform the `pop_back` operation efficiently
so it is not a fully operational deque.

*******************************************************************

#### clist [:top:](#CLM_LIBS)

```c
typedef struct clist_s {
    struct clist_s *next;
    type            data;
} clist_s, *clist;
```

Definition of the basic `clist` container data type.

**Warning:** An empty `clist` is just a `NULL` pointer.

**Example:** Initialize an empty `clist` with:

```c
clist MyList = NULL;
```

**Example:** Test a `MyList` for non-emptyness with:

```c
if (MyList) { printf("MyList is not empty"); }
else        { printf("MyList is empty");     }
```

*******************************************************************

#### clist\_push\_front [:top:](#CLM_LIBS)

```c
static inline bool clist_push_front(clist *list, const type data);
```

Adds an elemenet at the beginning of `list` in O(1) time.

**Warning:** Returns `true` if successful, and `false` otherwise.

**Example:** Add data to the beginning of `MyList` with:

```c
int success = clist_push_front(&MyList, data);
if (success) { assert(clist_front(&MyList) == data); }
```

*******************************************************************

#### clist\_push\_back [:top:](#CLM_LIBS)

```c
static inline bool clist_push_back(clist *list, const type data);
```

Adds an elemenet at the end of `list` in O(1) time.

**Warning:** Returns `true` if successful, and `false` otherwise.

**Example:** Add data to the end of `MyList` with:

```c
int success = clist_push_back(&MyList, data);
if (success) { assert(clist_back(&MyList) == data); }
```

*******************************************************************

#### clist\_pop\_front [:top:](#CLM_LIBS)

```c
static inline type clist_pop_front(clist *list);
```

Removes & returns the first element of `list` in O(1) time.

Although you can add elements to either end of the list they will
always exit the list from the beginning.

The combination of `push_front` & `pop_front` behaves as a LIFO
queue whereas `push_back` & `pop_front` behaves as a FIFO queue.

**Warning:** The parameter `list` must satisfy `*list != NULL`.

**Example:** Empty `MyList` with:

```c
while (MyList) { free(clist_pop_front(&MyList)); }
```

*******************************************************************

#### clist\_front [:top:](#CLM_LIBS)

```c
static inline type clist_front(clist *list);
```

Returns the first element of a non-empty list in O(1) time.

**Warning:** The parameter `list` must satisfy `*list != NULL`.

**Example:** Retrieve the next element to exit `MyList` with:

```c
type next = clist_front(&MyList);
```

*******************************************************************

#### clist\_back [:top:](#CLM_LIBS)

```c
static inline type clist_back(clist *list);
```

Returns the last element of a non-empty list in O(1) time.

**Warning:** The parameter `list` must satisfy `*list != NULL`.

**Example:** Retrieve the last element to exit `MyList` with:

```c
type last = clist_back(&MyList);
```

*********************************************************************

### CLM\_STREE [:top:](#CLM_LIBS)

```c
#define IMPORT_CLM_STREE(type, less, prefix)
```

A set of data types and functions related to the `stree` container.

The `stree` container is implemented as a splay tree of dinamically
allocated nodes with top-down simple-splaying updates.

Splay trees were defined in the paper "Self-Adjusting Binary Search
Trees" by Daniel D. Sleator & Robert E. Tarjan published in 1985 in
the Journal of the ACM 32 (3): 652–686. doi:10.1145/3828.3835

Splay trees are quite different from other binary search trees so,
it is advisable to learn about them at Wikipedia or other sources
before using them.

All the stree operations (excluding `stree_root` & `stree_size` that
always take O(1) and O(size) time respectively) are efficient in an
amortized sense. This means that a sequence of N of these operations
is guaranteed to take O(N·log(N)) time to complete, with some of them
requiring as few as O(1) operations and some of them taking O(N) time
to complete depending on the particular sequence of operations and
the particular values inserted/searched/removed from the `stree`.

In practice, Splay trees are a little bit slower than the equivalent
AVL tree, Red-Black tree or Weight-Balanced tree implementation but
use less memory and show an adaptive behavior that might benefit the
user in many common applications (e.g. inserting N sorted elements
takes just O(N) time rather than O(N·log(N)) time).

Incidentaly, Splay Trees also solve the "failed quieries" problem of
type-safe search trees (i.e. what to return when a `find` or `delete`
query fails) in a very natural way:

* The usual `find` operation is broken in two steps: first ask if
  `data` is in the `stree` with a `stree_find` operation and then
  recover it with a `stree_root` operation. Since `stree_find` puts
  `data` in the `root` of the `stree` the second operation only takes
  O(1) and no time is wasted to gain safety.
* The `next` and `prev` operations are also broken in two steps:
  first move the next/prev element to the `root` and then retrieve it
  with a `stree_root` operation. Again, since we are moving the
  elements to the `root` it just takes O(1) time to retrieve them.
* All other data-retrieving operations (`pop`, `min` & `max`) also
  end up working with the `root` node of the `stree` and will not
  fail unless the `stree` is empty, which is a condition that can be
  checked easily in O(1) time with a `tree != NULL` test.

*******************************************************************

#### stree [:top:](#CLM_LIBS)

```c
typedef struct stree_s {
    struct stree_s *left;
    struct stree_s *right;
    type            data;
} stree_s, *stree;
```

Definition of the basic splay tree container type `stree`.

**Warning:** An empty `stree` is just a `NULL` pointer.

**Example:** Initialize an empty `stree` with:

```c
stree MyTree = NULL;
```

**Example:** Test for non-emptyness of `MyTree` with:

```c
if (MyTree) { printf("MyTree is not empty"); }
else        { printf("MyTree is empty");     }
```

*******************************************************************

#### stree\_root [:top:](#CLM_LIBS)

```c
static inline type stree_root(stree *tree);
```

Returns the element stored at the current root node of `tree` in
O(1) time.

**Warning:** The parameter `tree` must satisfy `*tree != NULL`.

**Example:** Retrieve the current root element of `MyTree` with:

```c
if (MyTree) { root = stree_root(&MyTree); }
```

*******************************************************************

#### stree\_min [:top:](#CLM_LIBS)

```c
static inline type stree_min(stree *tree);
```

Moves the smallest element to the root of `tree` and returns it.

**Warning:** The parameter `tree` must satisfy `*tree != NULL`.

**Example:** Find the smallest element of `MyTree` with:

```c
if (MyTree) { smallest = stree_min(&MyTree); }
```

*******************************************************************

#### stree\_max [:top:](#CLM_LIBS)

```c
static inline type stree_max(stree *tree);
```

Moves the biggest element to the root of `tree` and returns it.

**Warning:** The parameter `tree` must satisfy `*tree != NULL`.

**Example:** Find the biggest element of `MyTree` with:

```c
if (MyTree) { biggest = stree_max(&MyTree); }
```

*******************************************************************

#### stree\_pop [:top:](#CLM_LIBS)

```c
static inline type stree_pop(stree *tree);
```

Removes the current root node from `tree` and returns its content.

It guarantees that, if the current root-node element is either the
biggest or the smallest in the `tree`, then, after performing this
operation, the root node element will still be the biggest or the
smallest element in the resulting `tree` (respectively).

**Warning:** The parameter `tree` must satisfy `*tree != NULL`.

**Example:** Remove `data` from `MyTree` (if present) with:

```c
if (stree_find(&MyTree, data)) {
    free(stree_pop(&MyTree));
}
```

**Example:** Remove all elements from `MyTree` with:

```c
while (MyTree) { free(stree_pop(&MyTree)); }
```

**Example:** Consume `MyTree` forwards with:

```c
if (MyTree) {
    stree_min(&MyTree);
    while (MyTree) {
        do_something(stree_pop(&MyTree));
    }
}
```

**Example:** Consume `MyTree` backwards with:

```c
if (MyTree) {
    stree_max(&MyTree);
    while (MyTree) {
        do_something(stree_pop(&MyTree));
    }
}
```

*******************************************************************

#### stree\_next [:top:](#CLM_LIBS)

```c
static inline bool stree_next(stree *tree);
```

If `tree` is empty or the current root is the biggest element it
just returs `false`. Otherwise, it moves to the root the smallest
element that is bigger than the current root and returns `true`.

**Example:** Iterate forwards over the elements of `MyTree` with:

```c
if (MyTree) {
    do_something(stree_min(&MyTree));
    while (stree_next(&MyTree)) {
        do_something(stree_root(&MyTree));
    }
}
```

*******************************************************************

#### stree\_prev [:top:](#CLM_LIBS)

```c
static inline bool stree_prev(stree *tree);
```

If `tree` is empty or the current root is the smallest element it
just returs `false`. Otherwise, it moves to the root the biggest
element that is smaller than the current root and returns `true`.

**Example:** Iterate backwards over the elements of `MyTree` with:

```c
if (MyTree) {
    do_something(stree_max(&MyTree));
    while (stree_prev(&MyTree)) {
        do_something(stree_root(&MyTree));
    }
}
```

*******************************************************************

#### stree\_find [:top:](#CLM_LIBS)

```c
static inline bool stree_find(stree *tree, const type data);
```

Looks for `data` in the `tree`. If `data` is in the `tree` it moves
it to the root node and returns `true`. Otherwise returns `false`.

**Example:** Find whether `data` is in `MyTree` with:

```c
if (stree_find(&MyTree, data)) {
    printf("data is in MyTree.");
    do_something(stree_root(&MyTree));
} else {
    printf("data is not in MyTree.");
}
```

*******************************************************************

#### stree\_insert [:top:](#CLM_LIBS)

```c
static inline bool stree_insert(stree *tree, const type data);
```

Inserts `data` in `tree`.

If `tree` already contains `data`, it gets overwritten and the
function returns `true`. Otherwise the function insert `data` in
`tree` and returns `true` if possible and `false` otherwise.

**Example:** Insert `data` in `MyTree` (without overwriting) with:

```c
if (stree_find(&MyTree, data)) {
    printf("data was in MyTree already.");
} else {
    stree_insert(&MyTree, data);
}
```

*********************************************************************

### CLM\_WTREE [:top:](#CLM_LIBS)

```c
#define IMPORT_CLM_WTREE(type, less, prefix)
```

A set of data types and functions related to the `wtree` container.

The `wtree` container is implemented as a weight-balanced tree of
dinamically allocated nodes with rebalancing constants `(2.5, 1.5)`.

Weight-balanced trees were defined in the paper "Binary search trees
of bounded balance" by J. Nievergelt & E. M. Reingold in 1972 in the
Proceedings of the Fourth Annual ACM Symposium on Theory of Computing
137–142. doi:10.1145/800152.804906

Weight-balanced trees are among the easiest balanced trees to code,
specially if you allow yourself to implement the insert and delete
functions recursively. Using the constants `(1+sqrt(2), sqrt(2))` for
rebalancing operations guarantee a maximum tree height of, at most,
`2 log(size)`, which is the same upper bound that the more popular
Red-Black trees provide.

In practice, however, it is advisable to use integer or fractional
constants such as `(3, 2)` or `(2.5, 1.5)` to avoid "integer by
floating point" multiplications or squaring subtree sizes.

A wtree with rebalancing constants `(X, Y)` guarantees a maximum
height of `log(size)/log((X+1)/X)`. The constants `(2.5, 1.5)` used
in this implementation guarantee a maximum height of `2.06 log(size)`
but usually behave much better.

There is a really thorough study on how to select these constants
correctly that was published in the paper "Balancing weight-balanced
trees" by Yoichi Hirai & Kazuhiko Yamamoto in 2011 in the Journal of
Functional Programming 21 (3): 137–142. doi:10.1017/S0956796811000104

Another good reason to choose weight-balanced trees as the default
balanced tree container is that they use the `size` field to maintain
balance. This field is useful on its own because it allows us to
perform the order-statistic queries `rank` and `select` efficiently.
Given the effect of memory alignement of structs, a `size_t` field
like `size` often takes as much space as a simple `bool` field like
`color` so you better use the whole thing to gain functionality.

Finally, when you work with type-safe generic containers like this
one you have to decide what happens when a query fails. I.e. what
happens if the user ask you to recover an element that is not there.

Different libraries use different approaches to solve this problem:

* Make the user responsible of making queries that never fail. So the
  user should ask if the element is there before recovering it.
* Returning a pointer to a tree node instead of a value. Meaning
  that user should extract the value afterwards.
* Some default value (usually `0`) is hardcoded. Meaning that the
  user cannot store that value in the container.
* The container is not fully implemented. Allowing the user to define
  what happens when a query fails.

I want to provide a complete generic container implementation that is
able to hold any value of the selected type and I do not want the
user to work with individual tree nodes, iterators or extractor
functions for safety reasons. Therefore, the only remaining option
is to make sure that the user never makes a failing query and using
an order statistics tree as a generic container makes easy to enforce
the fail-proof queries approach:

* Making the `find` function return the `rank` of the element (or `0`
  if the element was not there) rather than the element itself.
  This allows the implementation to issue an error message (`0`) with
  reasonable semantics (`if (wtree_find(*tree, data)) {...}`) when
  the query fails and provides the reference number (`rank`) required
  to recover (`select`) or delete (`remove`) that element.
* Using the `select` function (which depends on `rank`) to recover
  information rather than `find`, `min`, `max`, `next` or `prev`
  functions (which depend on `data`) prevents many failed queries
  by encouraging the user to ask for the `rank` of `data` first.
* Make the `remove` function depend on the `rank` of the removed
  element rather than on the element itself. This makes the user ask
  for the `rank` of an element before trying to delete it, preventing
  failed deleting queries.
* Implementing a constant-time `wtree_size` function allows the user
  to ensure the validity of any query depending on `rank` values with
  just a simple `1 <= rank && rank <= wtree_size(&tree)` test.
* Making the `insert` function return the `rank` of the inserted data
  not only allow the user to know whether an insertion failed (`0`)
  but also to get for free the information that other operations over
  the same `data` might require.

*******************************************************************

#### wtree [:top:](#CLM_LIBS)

```c
typedef struct wtree_s {
  struct wtree_s *left;
  struct wtree_s *right;
  size_t          size;
  type            data;
} wtree_s, *wtree;
```

Definition of the weight-balanced tree container type `wtree`.

**Warning:** An empty `wtree` is just a `NULL` pointer.

**Example:** Initialize an empty `wtree` with:

```c
wtree MyTree = NULL;
```

**Example:** Test for non-emptyness of `MyTree` with:

```c
if (MyTree) { printf("MyTree is not empty"); }
else        { printf("MyTree is empty");     }
```

*******************************************************************

#### wtree\_size [:top:](#CLM_LIBS)

```c
static inline size_t wtree_size(const wtree *tree);
```

Returns the number of elements stored in `tree` in O(1) time.

**Example:** Put all the elements of `tree` in an array with:

```c
size_t N = wtree_size(&MyTree);
type  *A = NULL;
if (N) { A = (type *) malloc(N * sizeof(type)); }
if (A != NULL) {
    for (size_t i = 0; i < N; i++) {
        A[i] = wtree_select(&MyTree, i+1);
    }
}
```

*******************************************************************

#### wtree\_find [:top:](#CLM_LIBS)

```c
static inline size_t wtree_find(const wtree *tree, const type data);
```

Looks for `data` in the `tree` in O(log(size)) time. If `data` is
in the `tree` it returns its `rank`. Otherwise it returns `0`.

**Warning:** The returned `rank` is 1-based (`1 <= rank <= size`).

**Example:** Find whether `data` is in `MyTree` with:

```c
size_t rank = wtree_find(&MyTree, data);
if (rank) {
    printf("data is in MyTree.");
    do_something(wtree_select(&MyTree, rank));
} else {
    printf("data is not in MyTree.");
}
```

*******************************************************************

#### wtree\_insert [:top:](#CLM_LIBS)

```c
static inline size_t wtree_insert(wtree *tree, const type data);
```

Inserts `data` in `tree` in O(log(size)) time.

If `tree` already contains `data`, it gets overwritten and the
function returns the current `rank` of `data` in the `tree`.
Otherwise the function tries to insert `data` in `tree` and returns
its current `rank` if possible and `0` otherwise.

**Example:** Insert `data` in `MyTree` (without overwriting) with:

```c
if (wtree_find(&MyTree, data)) {
    printf("data was in MyTree already.");
} else {
    wtree_insert(&MyTree, data);
}
```

**Example:** Implement a `bisect` function for `wtrees` with:

```c
size_t wtree_bisect(wtree *tree, type data) {
    size_t rank = wtree_find(tree, data);
    if (rank == 0) {
        rank = wtree_insert(tree, data);
        wtree_remove(tree, rank);
    }
    return rank;
}
```

*******************************************************************

#### wtree\_select [:top:](#CLM_LIBS)

```c
static inline type wtree_select(const wtree *tree, const size_t rank);
```

Returns the element of the `tree` that has a given `rank` in
O(log(size)) time.

**Warning:** The parameter `rank` must satisfy `1 <= rank <= size`

**Example:** Find the smallest element of `MyTree` with:

```c
type smallest = wtree_select(&MyTree, 1);
```

**Example:** Find the biggest element of `MyTree` with:

```c
type biggest = wtree_select(&MyTree, wtree_size(&MyTree));
```

**Example:** Iterate over the elements of `MyTree` with:

```c
size_t size = wtree_size(&MyTree);
for (size_t i = 1; i <= size; i++) {
    do_something(wtree_select(&MyTree, i));
}
```

*******************************************************************

#### wtree\_remove [:top:](#CLM_LIBS)

```c
static inline type wtree_remove(wtree *tree, const size_t rank);
```

Removes and returns the element of the `tree` that has a given
`rank` in O(log(size)) time.

**Warning:** The parameter `tree` must satisfy `*tree != NULL`.

**Warning:** The parameter `rank` must satisfy `1 <= rank <= size`

**Example:** Remove `data` from `MyTree` (if present) with:

```c
size_t rank = wtree_find(&MyTree, data);
if (rank) { free(wtree_remove(&MyTree, rank)); }
```

**Example:** Remove all elements from `MyTree` with:

```c
while (MyTree) { free(wtree_remove(&MyTree, 1)); }
```

*********************************************************************
