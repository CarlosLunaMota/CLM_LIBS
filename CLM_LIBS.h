/** *********************************************************************** **/
/**                                                                         **/
/** # CLM_LIBS                                                              **/
/**                                                                         **/
/** **CONTENT:** The CLM_LIBS code-generating macros                        **/
/**                                                                         **/
/** **AUTHOR:**  Carlos Luna-Mota                                           **/
/**                                                                         **/
/** **SOURCE:**  <https://github.com/CarlosLunaMota/CLM_LIBS>               **/
/**                                                                         **/
/** *********************************************************************** **/
/**                                                                         **/
/** ## INTRODUCTION                                                         **/
/**                                                                         **/
/** This is a collection of code-generating macros for the C preprocessor.  **/
/**                                                                         **/
/** The main motivation to write these macros is to put together all the    **/
/** functions that I frequently use in my C projects so I can test them     **/
/** properly, document them properly and trust them hereafter.              **/
/**                                                                         **/
/** I am using the code-generating macro approach for writting these        **/
/** libraries because I wanted to provide generic data structures without   **/
/** using `void` pointers.                                                  **/
/**                                                                         **/
/** Although this is a personal project, I am trying to document everything **/
/** so others can use this code too. For the same reason, I release the     **/
/** code into the Public Domain using the Unlicense (see LICENSE below).    **/
/**                                                                         **/
/** *********************************************************************** **/
/**                                                                         **/
/** ## CODE CONVENTIONS                                                     **/
/**                                                                         **/
/** Each library is just a code generating macro whose name starts with     **/
/** `IMPORT_CLM_`. The C preprocessor will substitute each macro call with  **/
/** a set of functions and type definitions before compiling the code, so   **/
/** you just get the same behavior that you would get if you coded these    **/
/** auxilary functions and data types by hand (including type-safety).      **/
/**                                                                         **/
/** The name of all types and functions starts with the name of the library **/
/** (macro) they belong to. The user can add an optional prefix to all the  **/
/** functions and data types when calling a macro to avoid conflicts with   **/
/** existing code or different calls to the same macro.                     **/
/**                                                                         **/
/** All `CLM_LIBS` functions are declared as `static inline` and are        **/
/** mutually independent (no `CLM_LIBS` function calls any other `CLM_LIBS` **/
/** function) although a few of them are recursive (they call themselves).  **/
/** This self-imposed constraint hurts modularity and readability but       **/
/** simplifies the task of versioning and reusing the code: You could erase **/
/** or substitute any function without worrying about dependencies.         **/
/**                                                                         **/
/** I am willing to sacrfice efficiency for practical reasons like safety,  **/
/** versatility or interface coherence. I will probably be the main user of **/
/** these libraries so I want them to be easy to use rather than fast or    **/
/** easy to code. If performance is your main concern, there might be       **/
/** better libraries out there (that will probably be WAY more difficult to **/
/** use). This being said, I will try to provide code that is efficient in  **/
/** terms of time and space. I just will not agonize about it.              **/
/**                                                                         **/
/** I am also not targeting outdated C compilers or embeded systems. I make **/
/** use of C99 features and manage the memory allocations with the standard **/
/** `malloc` and `free` functions. I am writing these libraries to be easy  **/
/** to read and modify so anyone can adapt them to their needs, though.     **/
/**                                                                         **/
/** Finally, regarding data types:                                          **/
/**                                                                         **/
/**  * `double` is the default floating point type                          **/
/**  * `size_t` is the default index and size type (transdichotomous model) **/
/**  * `char *` is the default `\0`-ended string type                       **/
/**  * `bool`   is the default boolean type (rather than `int`)             **/
/**  * All container types are named as the macro they belong to and are    **/
/**    pointers to the corresponding structs (same name with `_s` suffix).  **/
/**                                                                         **/
/** *********************************************************************** **/
/**                                                                         **/
/** ## CODE DEPENDENCIES                                                    **/
/**                                                                         **/
/** The file `CLM_LIBS.h` contains the code, the documentation and the      **/
/** license. The other files that you may find in the repository are used   **/
/** for the developement of `CLM_LIBS.h` and are not needed in practice:    **/
/**                                                                         **/
/**  * `README.md` - Contains the documentation in GitHub's MarkDown format **/
/**  * `CHEATSHEET.md` - Contains a quick-reference cheatsheet              **/
/**  * `UpdateDocs.py` - Contains a script for generating the documentation **/
/**  * `LICENSE` - Contains another copy of the same license (see below)    **/
/**  * `makefile` - Contains a script for automating the test process       **/
/**  * `test.c` - Contains a unit-test suite for each library               **/
/**                                                                         **/
/** `CLM_LIBS.h` relies only on the C standard library and compiles without **/
/** warnings using the GCC parameters `-std=c99 -Wall -Wextra -pedantic     **/
/** -Wformat-overflow=0`. More over, the code has been tested using         **/
/** `valgrind --leak-check=full` reporting no memory leaks.                 **/
/**                                                                         **/
/** The standard libraries used are (in alphabetical order):                **/
/**                                                                         **/
#include <assert.h>     /* Include assertions unless NDEBUG is defined.      */
#include <float.h>      /* Floating point limits.                            */
#include <limits.h>     /* Integer limits.                                   */
#include <stdbool.h>    /* Bool type and {true, false} values.               */
#include <stdint.h>     /* Fixed width integer types.                        */
#include <stdio.h>      /* Input and output functions.                       */
#include <stdlib.h>     /* Memory allocation and random functions.           */
#include <string.h>     /* The size_t type and string functions.             */
#include <time.h>       /* Time and calendar functions.                      */
/**                                                                         **/
/** *********************************************************************** **/
/**                                                                         **/
/** ## CODE LICENSE                                                         **/
/**                                                                         **/
/** This is free and unencumbered software released into the public domain. **/
/**                                                                         **/
/** Anyone is free to copy, modify, publish, use, compile, sell, or         **/
/** distribute this software, either in source code form or as a compiled   **/
/** binary, for any purpose, commercial or non-commercial, and by any       **/
/** means.                                                                  **/
/**                                                                         **/
/** In jurisdictions that recognize copyright laws, the author or authors   **/
/** of this software dedicate any and all copyright interest in the         **/
/** software to the public domain. We make this dedication for the benefit  **/
/** of the public at large and to the detriment of our heirs and            **/
/** successors. We intend this dedication to be an overt act of             **/
/** relinquishment in perpetuity of all present and future rights to this   **/
/** software under copyright law.                                           **/
/**                                                                         **/
/** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,         **/
/** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF      **/
/** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  **/
/** IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR       **/
/** OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,   **/
/** ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR   **/
/** OTHER DEALINGS IN THE SOFTWARE.                                         **/
/**                                                                         **/
/** For more information, please refer to <http://unlicense.org/>           **/
/**                                                                         **/
/** *********************************************************************** **/
/**                                                                         **/
/** ## THE MACROS                                                           **/
/**                                                                         **/
/** Each macro generates a collection of related functions and typedefs.    **/
/**                                                                         **/
/** All the macros have an optional parameter `prefix` that allows the      **/
/** user to change the name of the functions and data types so they don't   **/
/** crash with other user-defined functions/types or with different calls   **/
/** to the same macro.                                                      **/
/**                                                                         **/
/** Some of the macros require two mandatory parameters (`type` & `less`)   **/
/** that are used to build generic functions tailored to that data type.    **/
/**                                                                         **/
/** The `type` parameter could be any standard or user-defined data type.   **/
/**                                                                         **/
/** The `less` parameter should be the name (NOT A POINTER, JUST THE NAME)  **/
/** of a comparing function/macro for the corresponding data type.          **/
/**                                                                         **/
/** The `bool less(const type x, const type y)` function must accept two    **/
/** `const type` values and return:                                         **/
/**                                                                         **/
/**  * `less(x, y) == true`   if   `x <  y`                                 **/
/**  * `less(x, y) == false`  if   `x >= y`                                 **/
/**                                                                         **/
/** **Example:**                                                            **/
/**                                                                         **/
/**     #include "CLM_LIBS.h"                                               **/
/**                                                                         **/
/**     #define LESS_NUM(i, j) ((i) < (j))                                  **/
/**                                                                         **/
/**     typedef struct pair { int i; double d; } pair_t;                    **/
/**                                                                         **/
/**     bool less_pair(const pair_t p1, pair_t p2) {                        **/
/**         return (p1.i < p2.i || (p1.i == p2.i && p1.d < p2.d));          **/
/**     }                                                                   **/
/**                                                                         **/
/**     IMPORT_CLM_RAND()                                                   **/
/**     IMPORT_CLM_ARRAY(int,    LESS_NUM, int_)                            **/
/**     IMPORT_CLM_ARRAY(double, LESS_NUM, dbl_)                            **/
/**     IMPORT_CLM_STREE(pair_t, less_pair,    )                            **/
/**                                                                         **/
/**     int main(void) {                                                    **/
/**                                                                         **/
/**         pair_t    pair;                                                 **/
/**         size_t    i, N = 10;                                            **/
/**         stree     tree = NULL;                                          **/
/**         int_array A    = int_array_new(N);                              **/
/**         dbl_array B    = dbl_array_new(N);                              **/
/**                                                                         **/
/**         printf("\nRANDOM:\n");                                          **/
/**         for (i = 0; i < N; i++) {                                       **/
/**             A[i] = rand_int(100);                                       **/
/**             B[i] = rand_double(100);                                    **/
/**             printf("\t(%d, %f)\n", A[i], B[i]);                         **/
/**         }                                                               **/
/**                                                                         **/
/**         printf("\nLEXICOGRAPHICALLY SORTED:\n");                        **/
/**         for (i = 0; i < N; i++) {                                       **/
/**             pair.i = A[i];                                              **/
/**             pair.d = B[i];                                              **/
/**             stree_insert(&tree, pair);                                  **/
/**         }                                                               **/
/**         stree_min(&tree);                                               **/
/**         while (tree) {                                                  **/
/**             pair = stree_pop(&tree);                                    **/
/**             printf("\t(%d, %f)\n", pair.i, pair.d);                     **/
/**         }                                                               **/
/**                                                                         **/
/**         printf("\nINDEPENDENTLY SORTED:\n");                            **/
/**         int_array_sort(A, N);                                           **/
/**         dbl_array_sort(B, N);                                           **/
/**         for (i = 0; i < N; i++) { printf("\t(%d, %f)\n", A[i], B[i]); } **/
/**                                                                         **/
/**         free(A);                                                        **/
/**         free(B);                                                        **/
/**     }                                                                   **/
/**                                                                         **/

#ifndef CLM_LIBS

  /** ********************************************************************* **/
  /**                                                                       **/
  /** ### CLM_LIBS                                                          **/
  /**                                                                       **/
  /** Contains the version number (= date) of this release of CLM_LIBS.     **/
  /**                                                                       **/
  #define CLM_LIBS 20240815

  /** ********************************************************************* **/
  /**                                                                       **/
  /** ### CLM_TIME                                                          **/
  /**                                                                       **/
  /** A set of time-related and date-related functions.                     **/
  /**                                                                       **/
  #define IMPORT_CLM_TIME(prefix)                                               \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### time_elapsed                                                   **/ \
    /**                                                                     **/ \
    /** Returns a `double` with the number of seconds elapsed since the     **/ \
    /** last time you executed: `crono = clock();`                          **/ \
    /**                                                                     **/ \
    /** **Example:** Compare the performance of two functions with:         **/ \
    /**                                                                     **/ \
    /**     clock_t crono = clock();                                        **/ \
    /**     Function_1();                                                   **/ \
    /**     printf("Function 1 = %.3f sec.\n", time_elapsed(crono));        **/ \
    /**                                                                     **/ \
    /**     crono = clock();                                                **/ \
    /**     Function_2();                                                   **/ \
    /**     printf("Function 2 = %.3f sec.\n", time_elapsed(crono));        **/ \
    /**                                                                     **/ \
    static inline double prefix##time_elapsed(const clock_t crono) {            \
                                                                                \
        return ((double) (clock() - crono)) / CLOCKS_PER_SEC;                   \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### time_pause                                                     **/ \
    /**                                                                     **/ \
    /** Flushes the `stdin`, prints `message` in the `stdout` and then      **/ \
    /** reads the `stdin` until a `\n` or a `EOF` appears.                  **/ \
    /**                                                                     **/ \
    /** **Warning:** If `message == NULL` prints the default message:       **/ \
    /**                                                                     **/ \
    /**     ">> Press return to resume <<\n"                                **/ \
    /**                                                                     **/ \
    /** **Example:** Pause the program until the user hits return with:     **/ \
    /**                                                                     **/ \
    /**     show_results();                                                 **/ \
    /**     time_pause("\t\tPAUSE: Press return to resume.\n");             **/ \
    /**     show_more_results();                                            **/ \
    /**                                                                     **/ \
    static inline void prefix##time_pause(const char* message) {                \
                                                                                \
        int c;                                                                  \
                                                                                \
        fflush(stdin);                                                          \
                                                                                \
        if (message) { fprintf(stdout, "%s", message); }                        \
        else { fprintf(stdout, ">> Press return to resume <<\n"); }             \
        fflush(stdout);                                                         \
                                                                                \
        do { c = getc(stdin); } while (c != '\n' && c != EOF);                  \
        clearerr(stdin);                                                        \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### time_stamp                                                     **/ \
    /**                                                                     **/ \
    /** Returns a `\0` ended string with a timestamp formated as follows:   **/ \
    /**                                                                     **/ \
    /**  * The `Year  ` will be included if the 6th bit of `format` is 1.   **/ \
    /**  * The `Month ` will be included if the 5th bit of `format` is 1.   **/ \
    /**  * The `Day   ` will be included if the 4th bit of `format` is 1.   **/ \
    /**  * The `hour  ` will be included if the 3rd bit of `format` is 1.   **/ \
    /**  * The `minute` will be included if the 2nd bit of `format` is 1.   **/ \
    /**  * The `second` will be included if the 1st bit of `format` is 1.   **/ \
    /**  * The output will be "machine friendly" if `format >= 0`.          **/ \
    /**  * The output will be "human   friendly" if `format <  0`.          **/ \
    /**                                                                     **/ \
    /** Some useful examples:                                               **/ \
    /**                                                                     **/ \
    /**  * `get_timestamp( 32+16+8+4+2+1);` returns `"YYYYMMDDhhmmss"`      **/ \
    /**  * `get_timestamp( 32+16+8+4+2);  ` returns `"YYYYMMDDhhmm"`        **/ \
    /**  * `get_timestamp( 32+16+8);      ` returns `"YYYYMMDD"`            **/ \
    /**  * `get_timestamp(         4+2+1);` returns `"hhmmss"`              **/ \
    /**  * `get_timestamp(-32-16-8-4-2-1);` returns `"YYYY/MM/DD hh:mm:ss"` **/ \
    /**  * `get_timestamp(-32-16-8-4-2);  ` returns `"YYYY/MM/DD hh:mm"`    **/ \
    /**  * `get_timestamp(-32-16-8);      ` returns `"YYYY/MM/DD"`          **/ \
    /**  * `get_timestamp(-32-16);        ` returns `"YYYY/MM"`             **/ \
    /**  * `get_timestamp(   -16-8-4-2-1);` returns `"MM/DD hh:mm:ss"`      **/ \
    /**  * `get_timestamp(   -16-8-4-2);  ` returns `"MM/DD hh:mm"`         **/ \
    /**  * `get_timestamp(   -16-8);      ` returns `"MM/DD"`               **/ \
    /**  * `get_timestamp(        -4-2-1);` returns `"hh:mm:ss"`            **/ \
    /**  * `get_timestamp(        -4-2);  ` returns `"hh:mm"`               **/ \
    /**                                                                     **/ \
    /** **Warning:** The user should free the string after using it.        **/ \
    /**                                                                     **/ \
    /** **Warning:** The case `format == 0` defaults to `format == 63`.     **/ \
    /**                                                                     **/ \
    /** **Example:** Output `MyString` in a timestamped file with:          **/ \
    /**                                                                     **/ \
    /**     char filename[36];                                              **/ \
    /**     char *timestamp = time_stamp(0);                                **/ \
    /**                                                                     **/ \
    /**     sprintf(filename, "output_%s.txt", timestamp);                  **/ \
    /**     FILE *MyOutput = fopen(filename, "a");                          **/ \
    /**     fprintf(MyOutput, MyString);                                    **/ \
    /**                                                                     **/ \
    /**     fclose(MyOutput);                                               **/ \
    /**     free(timestamp);                                                **/ \
    /**                                                                     **/ \
    static inline char *prefix##time_stamp(const int format) {                  \
                                                                                \
        time_t now = time(NULL);                                                \
        struct tm tm = *localtime(&now);                                        \
        char *timestamp = (char *) malloc(20 * sizeof(char));                   \
                                                                                \
        int  f = (!format) ? (1<<6)-1 : (format > 0) ? (format) : -(format);    \
                                                                                \
        char Y[5] = "", M[3] = "", D[3] = "", h[3] = "", m[3] = "", s[3] = "";  \
        char YM[2] = "", MD[2] = "", Dh[2] = "", hm[2] = "", ms[2] = "";        \
                                                                                \
        if (timestamp) {                                                        \
            if (f & 32) { sprintf(Y, "%04d",tm.tm_year+1900); }                 \
            if (f & 16) { sprintf(M, "%02d",tm.tm_mon+1);     }                 \
            if (f &  8) { sprintf(D, "%02d",tm.tm_mday);      }                 \
            if (f &  4) { sprintf(h, "%02d",tm.tm_hour);      }                 \
            if (f &  2) { sprintf(m, "%02d",tm.tm_min);       }                 \
            if (f &  1) { sprintf(s, "%02d",tm.tm_sec);       }                 \
                                                                                \
            if (format < 0) {                                                   \
                if ((f & 16) && (f & 32)) { sprintf(YM, "/"); }                 \
                if ((f &  8) && (f & 48)) { sprintf(MD, "/"); }                 \
                if ((f &  7) && (f >  7)) { sprintf(Dh, " "); }                 \
                if ((f &  2) && (f &  4)) { sprintf(hm, ":"); }                 \
                if ((f &  1) && (f &  6)) { sprintf(ms, ":"); }                 \
            }                                                                   \
                                                                                \
            sprintf(timestamp, "%s%s%s%s%s%s%s%s%s%s%s",                        \
                    Y, YM, M, MD, D, Dh, h, hm, m, ms, s);                      \
        }                                                                       \
                                                                                \
        return timestamp;                                                       \
    }                                                                           \
                                                                                \

  /** ********************************************************************* **/
  /**                                                                       **/
  /** ### CLM_RAND                                                          **/
  /**                                                                       **/
  /** A set of random and quasi-random number generators.                   **/
  /**                                                                       **/
  #define IMPORT_CLM_RAND(prefix)                                               \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### rand_int                                                       **/ \
    /**                                                                     **/ \
    /** Returns an uniformly random `int` in the range `[0, n)`.            **/ \
    /**                                                                     **/ \
    /** **Warning:** Parameter `n` must satisfy `RAND_MAX >= n > 0`.        **/ \
    /**                                                                     **/ \
    /** **Example:** Print 10 random `int` in the range `[A, B]` with:      **/ \
    /**                                                                     **/ \
    /**     size_t i;                                                       **/ \
    /**     for (i = 0; i < 10; i++) { printf("%d ", A+rand_int(B-A+1)); }  **/ \
    /**                                                                     **/ \
    static inline int prefix##rand_int(const int n) {                           \
                                                                                \
        /* Preconditions */                                                     \
        assert(n > 0);                                                          \
        assert(RAND_MAX >= n);                                                  \
                                                                                \
        /* Monte-Carlo uniformly random generator */                            \
        int r, range = RAND_MAX - (RAND_MAX % n);                               \
        do { r = rand(); } while (r >= range);                                  \
        return r % n;                                                           \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### rand_size_t                                                    **/ \
    /**                                                                     **/ \
    /** Returns an uniformly random `size_t` in the range `[0, n)`.         **/ \
    /**                                                                     **/ \
    /** **Warning:** Parameter `n` must satisfy `RAND_MAX >= n > 0`.        **/ \
    /**                                                                     **/ \
    /** **Example:** Select a random element from an array of size N with:  **/ \
    /**                                                                     **/ \
    /**     type elem = MyArray[rand_size_t(N)];                            **/ \
    /**                                                                     **/ \
    static inline size_t prefix##rand_size_t(const size_t n) {                  \
                                                                                \
        /* Preconditions */                                                     \
        assert(n > 0);                                                          \
        assert(RAND_MAX >= n);                                                  \
                                                                                \
        /* Monte-Carlo uniformly random generator */                            \
        size_t r, range = RAND_MAX - (RAND_MAX % n);                            \
        do { r = rand(); } while (r >= range);                                  \
        return r % n;                                                           \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### rand_double                                                    **/ \
    /**                                                                     **/ \
    /** Returns an uniformly random `int` in the range `[0.0, n)`.          **/ \
    /**                                                                     **/ \
    /** **Warning:** Parameter `n` must satisfy `n > DLB_EPSILON`.          **/ \
    /**                                                                     **/ \
    /** **Example:** Print 10 random `double` in the range `[A, B)` with:   **/ \
    /**                                                                     **/ \
    /**     size_t i;                                                       **/ \
    /**     for (i = 0; i < 10; i++) { printf("%f ", A+rand_double(B-A)); } **/ \
    /**                                                                     **/ \
    static inline double prefix##rand_double(const double n) {                  \
                                                                                \
        /* Preconditions */                                                     \
        assert(n > DBL_EPSILON);                                                \
                                                                                \
        /* Uniformly random generator */                                        \
        return n * ((double) rand() / (double) RAND_MAX);                       \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### rand_halton                                                    **/ \
    /**                                                                     **/ \
    /** Returns a quasi-random number in the range `[0.0, 1.0)`.            **/ \
    /**                                                                     **/ \
    /** More specifically, returns the `n`-th element of the Halton         **/ \
    /** low-discrepancy sequence that has the `base` as a base.             **/ \
    /**                                                                     **/ \
    /** In general it is advisable to use small prime numbers as `base`.    **/ \
    /** In particular, if you need to produce quasi-random D-dimensional    **/ \
    /** points, you should use `D` coprime numbers as 'base', one for each  **/ \
    /** dimension (see example below).                                      **/ \
    /**                                                                     **/ \
    /** **Warning:** Parameter `base` must satisfy `base > 1`.              **/ \
    /**                                                                     **/ \
    /** **Warning:** The algorithm is deterministic, which means that for   **/ \
    /** a fixed `(base, n)` input, it will always provide the same output.  **/ \
    /**                                                                     **/ \
    /** **Example:** Get 100 quasi-random 3D points with:                   **/ \
    /**                                                                     **/ \
    /**     double *X = (double *) malloc(100 * sizeof(double));            **/ \
    /**     double *Y = (double *) malloc(100 * sizeof(double));            **/ \
    /**     double *Z = (double *) malloc(100 * sizeof(double));            **/ \
    /**     if (X && Y && Z) {                                              **/ \
    /**         for (size_t i = 0; i < 100; i++) {                          **/ \
    /**             X[i] = x_min + (x_max-x_min)*rand_halton(2, i);         **/ \
    /**             Y[i] = y_min + (y_max-y_min)*rand_halton(3, i);         **/ \
    /**             Z[i] = z_min + (z_max-z_min)*rand_halton(5, i);         **/ \
    /**         }                                                           **/ \
    /**     }                                                               **/ \
    /**                                                                     **/ \
    static inline double prefix##rand_halton(const size_t base, size_t n) {     \
                                                                                \
        /* Precondition */                                                      \
        assert(base > 1);                                                       \
                                                                                \
        /* Get the `n`-th element of the Halton Sequence of base `base` */      \
        double den = 1.0;                                                       \
        double num = 0.0;                                                       \
        while (n) {                                                             \
            den  = den * base;                                                  \
            num  = num * base + (n % base);                                     \
            n   /= base;                                                        \
        }                                                                       \
        return num / den;                                                       \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### rand_color                                                     **/ \
    /**                                                                     **/ \
    /** Returns a random RGB color with the same Saturation and Brightness  **/ \
    /** (but different Hue) than the RGB color provided.                    **/ \
    /**                                                                     **/ \
    /** More specifically, generates a low discrepancy sequence of colors   **/ \
    /** based on the additive recurrence:                                   **/ \
    /**                                                                     **/ \
    /**     Hue[n] = (Hue[n-1] + (phi-1)) % 1.0                             **/ \
    /**                                                                     **/ \
    /** where Hue is taken in the [0.0, 1.0) range and:                     **/ \
    /**                                                                     **/ \
    /**     phi = (1.0 + sqrt(5.0)) / 2.0 = 1.61803398874989484820458683436 **/ \
    /**                                                                     **/ \
    /** **Warning:** `r`, `g` and `b` must be integers in [0, 255].         **/ \
    /**                                                                     **/ \
    /** **Warning:** The algorithm is deterministic, which means that for   **/ \
    /** a fixed input color, it will always provide the same output color.  **/ \
    /**                                                                     **/ \
    /** **Example:** Generate 5 random colors with:                         **/ \
    /**                                                                     **/ \
    /**     int r = 255;                                                    **/ \
    /**     int g = 135;                                                    **/ \
    /**     int b =   0;                                                    **/ \
    /**     int R[5]; G[5]; B[5];                                           **/ \
    /**     for (size_t i = 0; i < 5; i++) {                                **/ \
    /**         rand_color(&r, &g, &b);                                     **/ \
    /**         R[i] = r; G[i] = g; B[i] = b;                               **/ \
    /**     }                                                               **/ \
    /**                                                                     **/ \
    static inline void prefix##rand_color(int *r, int *g, int *b) {             \
                                                                                \
        /* Preconditions */                                                     \
        assert(0 <= *r && *r < 256);                                            \
        assert(0 <= *g && *g < 256);                                            \
        assert(0 <= *b && *b < 256);                                            \
                                                                                \
        double rr = ((double) *r) / 256.0;                                      \
        double gg = ((double) *g) / 256.0;                                      \
        double bb = ((double) *b) / 256.0;                                      \
        double h,s,v, f, phi = 0.61803398874989484820458683436;                 \
        double max, min, dif;                                                   \
        int    i;                                                               \
                                                                                \
        /*** RGB to HSV conversion *******************************************/ \
        /*                                                                   */ \
        /* from (r,g,b) in [0,1)x[0,1)x[0,1) to (h,s,v) in [0,1)x[0,1)x[0,1) */ \
        /*                                                                   */ \
        max = (gg > bb) ? ((rr > gg) ? rr : gg) : ((rr > bb) ? rr : bb);        \
        min = (gg < bb) ? ((rr < gg) ? rr : gg) : ((rr < bb) ? rr : bb);        \
        dif = max-min;                                                          \
        if (max > 0.0 && dif > 0.0) {                                           \
            v = max;                                                            \
            s = dif / max;                                                      \
            if      (rr == max) { h = (      (gg-bb)/(2.0*dif)) / 3.0; }        \
            else if (gg == max) { h = (1.0 + (bb-rr)/(2.0*dif)) / 3.0; }        \
            else                { h = (2.0 + (rr-gg)/(2.0*dif)) / 3.0; }        \
            if (h < 0.0) { h += 1.0; }                                          \
        } else { v = max; h = s = 0.0; }                                        \
                                                                                \
                                                                                \
        /* Get next quasi-random Hue value */                                   \
        h = (h + phi);                                                          \
        if (h >= 1.0) { h -= 1.0; }                                             \
                                                                                \
                                                                                \
        /*** HSV to RGB conversion *******************************************/ \
        /*                                                                   */ \
        /* from (h,s,v) in [0,1)x[0,1)x[0,1) to (r,g,b) in [0,1)x[0,1)x[0,1) */ \
        /*                                                                   */ \
        i = (int) (6.0*h);                                                      \
        f = 6.0*h - ((double) i);                                               \
        if      (i == 0) { rr = v;         gg = v*(1-s*(1-f)); bb = v*(1-s); }  \
        else if (i == 2) { gg = v;         bb = v*(1-s*(1-f)); rr = v*(1-s); }  \
        else if (i == 4) { bb = v;         rr = v*(1-s*(1-f)); gg = v*(1-s); }  \
        else if (i == 1) { rr = v*(1-s*f); gg = v;             bb = v*(1-s); }  \
        else if (i == 3) { gg = v*(1-s*f); bb = v;             rr = v*(1-s); }  \
        else if (i == 5) { bb = v*(1-s*f); rr = v;             gg = v*(1-s); }  \
                                                                                \
                                                                                \
        /* Store the new RGB values */                                          \
        *r = (int) (rr * 256);                                                  \
        *g = (int) (gg * 256);                                                  \
        *b = (int) (bb * 256);                                                  \
    }                                                                           \
                                                                                \

  /** ********************************************************************* **/
  /**                                                                       **/
  /** ### CLM_PRINTF                                                        **/
  /**                                                                       **/
  /** A set of formatting functions for the standard terminal output.       **/
  /**                                                                       **/
  #define IMPORT_CLM_PRINTF(prefix)                                             \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### printf_reset                                                   **/ \
    /**                                                                     **/ \
    /** Resets all formating parameters of printf to their default values.  **/ \
    /**                                                                     **/ \
    /** **Example:** Give your command line a "retro look" with:            **/ \
    /**                                                                     **/ \
    /**     printf_reset();                                                 **/ \
    /**     printf_set_back_color(0x00, 0x00, 0x00);                        **/ \
    /**     printf_set_text_color(0x33, 0xFF, 0x00);                        **/ \
    /**                                                                     **/ \
    static inline void prefix##printf_reset() { printf("\033[0m"); }            \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### printf_delete                                                  **/ \
    /**                                                                     **/ \
    /** Deletes everything from the cursor position to the end of the line. **/ \
    /**                                                                     **/ \
    /** **Example:** Remove the last 2 lines with:                          **/ \
    /**                                                                     **/ \
    /**     printf_move(0,-1);                                              **/ \
    /**     printf_delete();                                                **/ \
    /**     printf_move(0,-1);                                              **/ \
    /**     printf_delete();                                                **/ \
    /**                                                                     **/ \
    /** **Example:** Erase the last 5 characters with:                      **/ \
    /**                                                                     **/ \
    /**     printf_move(-5,0);                                              **/ \
    /**     printf_delete();                                                **/ \
    /**                                                                     **/ \
    static inline void prefix##printf_delete() { printf("\033[K"); }            \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### printf_set_bold                                                **/ \
    /**                                                                     **/ \
    /** Sets the printf function in boldface mode.                          **/ \
    /**                                                                     **/ \
    /** **Example:** Print the string `txt` in boldface with:               **/ \
    /**                                                                     **/ \
    /**     printf_set_bold();                                              **/ \
    /**     printf("%s", txt);                                              **/ \
    /**     printf_reset();                                                 **/ \
    /**                                                                     **/ \
    static inline void prefix##printf_set_bold() { printf("\033[1m"); }         \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### printf_set_light                                               **/ \
    /**                                                                     **/ \
    /** Sets the printf function in lightface mode.                         **/ \
    /**                                                                     **/ \
    /** **Example:** Print the string `txt` in lightface with:              **/ \
    /**                                                                     **/ \
    /**     printf_set_light();                                             **/ \
    /**     printf("%s", txt);                                              **/ \
    /**     printf_reset();                                                 **/ \
    /**                                                                     **/ \
    static inline void prefix##printf_set_light() { printf("\033[2m"); }        \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### printf_set_strike                                              **/ \
    /**                                                                     **/ \
    /** Sets the printf function in strikethrough mode.                     **/ \
    /**                                                                     **/ \
    /** **Example:** Print the string `txt` striked with:                   **/ \
    /**                                                                     **/ \
    /**     printf_set_strike();                                            **/ \
    /**     printf("%s", txt);                                              **/ \
    /**     printf_reset();                                                 **/ \
    /**                                                                     **/ \
    static inline void prefix##printf_set_strike() { printf("\033[9m"); }       \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### printf_set_underline                                           **/ \
    /**                                                                     **/ \
    /** Sets the printf function in underline mode.                         **/ \
    /**                                                                     **/ \
    /** **Example:** Print the string `txt` underlined with:                **/ \
    /**                                                                     **/ \
    /**     printf_set_underline();                                         **/ \
    /**     printf("%s", txt);                                              **/ \
    /**     printf_reset();                                                 **/ \
    /**                                                                     **/ \
    static inline void prefix##printf_set_underline() { printf("\033[4m"); }    \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### printf_move                                                    **/ \
    /**                                                                     **/ \
    /** Moves the cursor to the relative position defined by `(dx,dy)`.     **/ \
    /**                                                                     **/ \
    /** **Warning:** Text will be overwritten from that position.           **/ \
    /**                                                                     **/ \
    /** **Warning:** Negative movement goes towards the upper-left corner.  **/ \
    /**                                                                     **/ \
    /** **Example:** Remove the last 2 lines with:                          **/ \
    /**                                                                     **/ \
    /**     printf_move(0,-1);                                              **/ \
    /**     printf_delete();                                                **/ \
    /**     printf_move(0,-1);                                              **/ \
    /**     printf_delete();                                                **/ \
    /**                                                                     **/ \
    /** **Example:** Erase the last 5 characters with:                      **/ \
    /**                                                                     **/ \
    /**     printf_move(-5,0);                                              **/ \
    /**     printf_delete();                                                **/ \
    /**                                                                     **/ \
    static inline void prefix##printf_move(const int dx, const int dy) {        \
        if (dy < 0) { printf("\033[%dA", -dy); }                                \
        if (dy > 0) { printf("\033[%dB",  dy); }                                \
        if (dx > 0) { printf("\033[%dC",  dx); }                                \
        if (dx < 0) { printf("\033[%dD", -dx); }                                \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### printf_set_text_grey                                           **/ \
    /**                                                                     **/ \
    /** Sets a greyscale text color for the printf function.                **/ \
    /**                                                                     **/ \
    /** The greyscale palette goes from black (`0`) to white (`23`).        **/ \
    /**                                                                     **/ \
    /** **Warning:** `grey` must be a integer in the range [0, 23].         **/ \
    /**                                                                     **/ \
    /** **Example:** Print the string `txt` in white with:                  **/ \
    /**                                                                     **/ \
    /**     printf_set_text_grey(23);                                       **/ \
    /**     printf("%s", txt);                                              **/ \
    /**     printf_reset();                                                 **/ \
    /**                                                                     **/ \
    static inline void prefix##printf_set_text_grey(const int grey) {           \
                                                                                \
        /* Preconditions: */                                                    \
        assert(0 <= grey && grey < 24);                                         \
                                                                                \
        printf("\033[38;5;%dm", 232 + grey);                                    \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### printf_set_back_grey                                           **/ \
    /**                                                                     **/ \
    /** Sets a greyscale background color for the printf function.          **/ \
    /**                                                                     **/ \
    /** The greyscale palette goes from black (`0`) to white (`23`).        **/ \
    /**                                                                     **/ \
    /** **Warning:** `grey` must be a integer in the range [0, 23].         **/ \
    /**                                                                     **/ \
    /** **Example:** Print the string `txt` on a white background with:     **/ \
    /**                                                                     **/ \
    /**     printf_set_back_grey(23);                                       **/ \
    /**     printf("%s", txt);                                              **/ \
    /**     printf_reset();                                                 **/ \
    /**                                                                     **/ \
    static inline void prefix##printf_set_back_grey(const int grey) {           \
                                                                                \
        /* Preconditions: */                                                    \
        assert(0 <= grey && grey < 24);                                         \
                                                                                \
        printf("\033[48;5;%dm", 232 + grey);                                    \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### printf_set_text_color                                          **/ \
    /**                                                                     **/ \
    /** Sets the color of the text for the printf function.                 **/ \
    /**                                                                     **/ \
    /** The actual color of the text will be the closest color to `(r,g,b)` **/ \
    /** in the web-safe palette: `[0x00, 0x33, 0x66, 0x99, 0xCC, 0xFF]^3`   **/ \
    /**                                                                     **/ \
    /** **Warning:** `r`, `g` and `b` must be integers in `[0, 255]`.       **/ \
    /**                                                                     **/ \
    /** **Example:** Print the string `txt` in red with:                    **/ \
    /**                                                                     **/ \
    /**     printf_set_text_color(0xFF, 0x00, 0x00);                        **/ \
    /**     printf("%s", txt);                                              **/ \
    /**     printf_reset();                                                 **/ \
    /**                                                                     **/ \
    static inline void prefix##printf_set_text_color(const int r, const int g,  \
                                                     const int b) {             \
        /* Preconditions: */                                                    \
        assert(0 <= r && r < 256);                                              \
        assert(0 <= g && g < 256);                                              \
        assert(0 <= b && b < 256);                                              \
                                                                                \
        int rr = (r+25) / 51;                                                   \
        int gg = (g+25) / 51;                                                   \
        int bb = (b+25) / 51;                                                   \
        printf("\033[38;5;%dm", (rr*36) + (gg*6) + bb + 16);                    \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### printf_set_back_color                                          **/ \
    /**                                                                     **/ \
    /** Sets the color of the background for the printf function.           **/ \
    /**                                                                     **/ \
    /** The actual background color will be the closest color to `(r,g,b)`  **/ \
    /** in the web-safe palette: `[0x00, 0x33, 0x66, 0x99, 0xCC, 0xFF]^3`   **/ \
    /**                                                                     **/ \
    /** **Warning:** `r`, `g` and `b` must be integers in `[0, 255]`.       **/ \
    /**                                                                     **/ \
    /** **Example:** Print the string `txt` on a blue background with:      **/ \
    /**                                                                     **/ \
    /**     printf_set_back_color(0, 0, 255);                               **/ \
    /**     printf("%s", txt);                                              **/ \
    /**     printf_reset();                                                 **/ \
    /**                                                                     **/ \
    static inline void prefix##printf_set_back_color(const int r, const int g,  \
                                                     const int b) {             \
        /* Preconditions: */                                                    \
        assert(0 <= r && r < 256);                                              \
        assert(0 <= g && g < 256);                                              \
        assert(0 <= b && b < 256);                                              \
                                                                                \
        int rr = (r+25) / 51;                                                   \
        int gg = (g+25) / 51;                                                   \
        int bb = (b+25) / 51;                                                   \
        printf("\033[48;5;%dm", (rr*36) + (gg*6) + bb + 16);                    \
    }                                                                           \
                                                                                \

  /** ********************************************************************* **/
  /**                                                                       **/
  /** ### CLM_HASH                                                          **/
  /**                                                                       **/
  /** A set of reversible bit-mixer functions for unsigned integers.        **/
  /**                                                                       **/
  #define IMPORT_CLM_HASH(prefix)                                               \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### hash_mix32                                                     **/ \
    /**                                                                     **/ \
    /** Given a `uint32_t` value returns another `uint32_t` value that can  **/ \
    /** be used as a (non-cryptographic) hash of the first value.           **/ \
    /**                                                                     **/ \
    /** On average, changing a single bit in the input changes each bit of  **/ \
    /** the output with probability 1/2, so, this deterministic function    **/ \
    /** could be used as a non-cryptographic pseudorandom number generator. **/ \
    /**                                                                     **/ \
    /** This function is based on `triple32` by Chris Wellons, see:         **/ \
    /** https://nullprogram.com/blog/2018/07/31/                            **/ \
    /**                                                                     **/ \
    /** **Warning:** Zero is a fixed point by design.                       **/ \
    /**                                                                     **/ \
    /** **Warning:** This function is reversible by design.                 **/ \
    /**                                                                     **/ \
    /** **Example:** Find the index of `elem` in a `2^K` hash table with:   **/ \
    /**                                                                     **/ \
    /**     int index = hash_mix32(elem) & ((1 << K)-1);                    **/ \
    /**                                                                     **/ \
    /** **Example:** Generate 5 pseudorandom `uint32_t` numbers with:       **/ \
    /**                                                                     **/ \
    /**     uint32_t N[5];                                                  **/ \
    /**     uint32_t SEED   = (uint32_t) 314159285;         // change it!   **/ \
    /**     uint32_t PHI_32 = (uint32_t) 0x9e3779b9;        // 2^32 * Phi   **/ \
    /**     for (int i = 0; i < 5; i++) {                                   **/ \
    /**         N[i] = hash_mix32(SEED + (i+1) * PHI_32);                   **/ \
    /**     }                                                               **/ \
    /**                                                                     **/ \
    static inline uint32_t prefix##hash_mix32(uint32_t h) {                     \
                                                                                \
        h ^= (h >> 17);                                                         \
        h *= (uint32_t) 0xed5ad4bb;                                             \
        h ^= (h >> 11);                                                         \
        h *= (uint32_t) 0xac4c1b51;                                             \
        h ^= (h >> 15);                                                         \
        h *= (uint32_t) 0x31848bab;                                             \
        h ^= (h >> 14);                                                         \
                                                                                \
        return h;                                                               \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### hash_unmix32                                                   **/ \
    /**                                                                     **/ \
    /** Given a `uint32_t` value returns another `uint32_t` value that can  **/ \
    /** be used as a (non-cryptographic) hash of the first value.           **/ \
    /**                                                                     **/ \
    /** This function is the inverse of `hash_mix32` and has the very same  **/ \
    /** properties. See `hash_mix32` documentation for the details.         **/ \
    /**                                                                     **/ \
    /** **Warning:** Zero is a fixed point by design.                       **/ \
    /**                                                                     **/ \
    /** **Warning:** This function is reversible by design.                 **/ \
    /**                                                                     **/ \
    /** **Example:** Reverse a hash operation with:                         **/ \
    /**                                                                     **/ \
    /**     assert(hash_unmix32(hash_mix32(i)) == i);                       **/ \
    /**     assert(hash_mix32(hash_unmix32(i)) == i);                       **/ \
    /**                                                                     **/ \
    static inline uint32_t prefix##hash_unmix32(uint32_t h) {                   \
                                                                                \
        h ^= (h >> 14) ^ (h >> 28);                                             \
        h *= (uint32_t) 0x32b21703;                                             \
        h ^= (h >> 15) ^ (h >> 30);                                             \
        h *= (uint32_t) 0x469e0db1;                                             \
        h ^= (h >> 11) ^ (h >> 22);                                             \
        h *= (uint32_t) 0x79a85073;                                             \
        h ^= (h >> 17);                                                         \
                                                                                \
        return h;                                                               \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### hash_mix64                                                     **/ \
    /**                                                                     **/ \
    /** Given a `uint64_t` value returns another `uint64_t` value that can  **/ \
    /** be used as a (non-cryptographic) hash of the first value.           **/ \
    /**                                                                     **/ \
    /** On average, changing a single bit in the input changes each bit of  **/ \
    /** the output with probability 1/2, so, this deterministic function    **/ \
    /** could be used as a non-cryptographic pseudorandom number generator. **/ \
    /**                                                                     **/ \
    /** This function is based on `splitmix64` by Sebastiano Vigna, see:    **/ \
    /** http://xoshiro.di.unimi.it/splitmix64.c                             **/ \
    /**                                                                     **/ \
    /** **Warning:** Zero is a fixed point by design.                       **/ \
    /**                                                                     **/ \
    /** **Warning:** This function is reversible by design.                 **/ \
    /**                                                                     **/ \
    /** **Example:** Find the index of `elem` in a `2^K` hash table with:   **/ \
    /**                                                                     **/ \
    /**     size_t index = hash_mix64(elem) & ((1 << K)-1);                 **/ \
    /**                                                                     **/ \
    /** **Example:** Generate 5 pseudorandom `uint64_t` numbers with:       **/ \
    /**                                                                     **/ \
    /**     uint64_t N[5];                                                  **/ \
    /**     uint64_t SEED   = (uint64_t) 314159285;          // change it!  **/ \
    /**     uint64_t PHI_64 = (uint64_t) 0x9e3779b97f4a7c15; // 2^64 * Phi  **/ \
    /**     for (int i = 0; i < 5; i++) {                                   **/ \
    /**         N[i] = hash_mix64(SEED + (i+1) * PHI_64);                   **/ \
    /**     }                                                               **/ \
    /**                                                                     **/ \
    static inline uint64_t prefix##hash_mix64(uint64_t h) {                     \
                                                                                \
        h ^= (h >> 30);                                                         \
        h *= (uint64_t) 0xbf58476d1ce4e5b9;                                     \
        h ^= (h >> 27);                                                         \
        h *= (uint64_t) 0x94d049bb133111eb;                                     \
        h ^= (h >> 31);                                                         \
                                                                                \
        return h;                                                               \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### hash_unmix64                                                   **/ \
    /**                                                                     **/ \
    /** Given a `uint64_t` value returns another `uint64_t` value that can  **/ \
    /** be used as a (non-cryptographic) hash of the first value.           **/ \
    /**                                                                     **/ \
    /** This function is the inverse of `hash_mix64` and has the very same  **/ \
    /** properties. See `hash_mix64` documentation for the details.         **/ \
    /**                                                                     **/ \
    /** **Warning:** Zero is a fixed point by design.                       **/ \
    /**                                                                     **/ \
    /** **Warning:** This function is reversible by design.                 **/ \
    /**                                                                     **/ \
    /** **Example:** Reverse a hash operation with:                         **/ \
    /**                                                                     **/ \
    /**     assert(hash_unmix64(hash_mix64(i)) == i);                       **/ \
    /**     assert(hash_mix64(hash_unmix64(i)) == i);                       **/ \
    /**                                                                     **/ \
    static inline uint64_t prefix##hash_unmix64(uint64_t h) {                   \
                                                                                \
        h ^= (h >> 31) ^ (h >> 62);                                             \
        h *= (uint64_t) 0x319642b2d24d8ec3;                                     \
        h ^= (h >> 27) ^ (h >> 54);                                             \
        h *= (uint64_t) 0x96de1b173f119089;                                     \
        h ^= (h >> 30) ^ (h >> 60);                                             \
                                                                                \
        return h;                                                               \
    }                                                                           \
                                                                                \

  /** ********************************************************************* **/
  /**                                                                       **/
  /** ### CLM_DAMM                                                          **/
  /**                                                                       **/
  /** A set of check digit functions using the Damm algorithm.              **/
  /**                                                                       **/
  #define IMPORT_CLM_DAMM(prefix)                                               \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### damm_dec                                                       **/ \
    /**                                                                     **/ \
    /** Returns a the checksum character of the `\0`-terminated numeric     **/ \
    /** string `txt`.                                                       **/ \
    /**                                                                     **/ \
    /** The algorithm guarantees that:                                      **/ \
    /**                                                                     **/ \
    /**     damm_dec(txt ++ damm_dec(txt)) == '0'                           **/ \
    /**                                                                     **/ \
    /** where `txt ++ c` is the concatenation of `txt` and `c`.             **/ \
    /**                                                                     **/ \
    /** **Warning:** All non-numeric characters will be ignored.            **/ \
    /**                                                                     **/ \
    /** **Example:** Add a checksum character to the string `s` with:       **/ \
    /**                                                                     **/ \
    /**     size_t length    = strlen(s);                                   **/ \
    /**     char *s_checksum = (char *) malloc((length+2) * sizeof(char));  **/ \
    /**     sprintf(s_checksum, "%s%c", txt, damm_dec(txt));                **/ \
    /**     assert(damm_dec(s_checksum) == '0');                            **/ \
    /**                                                                     **/ \
    static inline char prefix##damm_dec(const char *txt) {                      \
                                                                                \
        /* Preconditions */                                                     \
        assert('9'-'0' == 9);                                                   \
                                                                                \
        /* Base 10 Tables for the Damm algorithm */                             \
        const char DEC[11]   = "0123456789";                                    \
        const char T[10][10] = {{0, 3, 1, 7, 5, 9, 8, 6, 4, 2},                 \
                                {7, 0, 9, 2, 1, 5, 4, 8, 6, 3},                 \
                                {4, 2, 0, 6, 8, 7, 1, 3, 5, 9},                 \
                                {1, 7, 5, 0, 9, 8, 3, 4, 2, 6},                 \
                                {6, 1, 2, 3, 0, 4, 5, 9, 7, 8},                 \
                                {3, 6, 7, 4, 2, 0, 9, 5, 8, 1},                 \
                                {5, 8, 6, 9, 7, 2, 0, 1, 3, 4},                 \
                                {8, 9, 4, 5, 3, 6, 2, 0, 1, 7},                 \
                                {9, 4, 3, 8, 6, 1, 7, 2, 0, 5},                 \
                                {2, 5, 8, 1, 4, 3, 6, 7, 9, 0}};                \
                                                                                \
        /* Compute the checksum character */                                    \
        char   number = 0;                                                      \
        size_t length = strlen(txt);                                            \
        for (size_t i = 0; i < length; i++) {                                   \
            if (txt[i] < '0' || txt[i] > '9') { continue; }                     \
            number = T[(size_t) number][(size_t) (txt[i] - '0')];               \
        }                                                                       \
                                                                                \
        /* Return the checksum character */                                     \
        return DEC[(size_t) number];                                            \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### damm_hex                                                       **/ \
    /**                                                                     **/ \
    /** Returns a the checksum character of the `\0`-terminated hexadecimal **/ \
    /** string `txt`.                                                       **/ \
    /**                                                                     **/ \
    /** The algorithm guarantees that:                                      **/ \
    /**                                                                     **/ \
    /**     damm_hex(txt ++ damm_hex(txt)) == '0'                           **/ \
    /**                                                                     **/ \
    /** where `txt ++ c` is the concatenation of `txt` and `c`.             **/ \
    /**                                                                     **/ \
    /** **Warning:** All non-hexadecimal characters will be ignored.        **/ \
    /**                                                                     **/ \
    /** **Warning:** The algorithm is case insensitive.                     **/ \
    /**                                                                     **/ \
    /** **Example:** Add a checksum character to the string `s` with:       **/ \
    /**                                                                     **/ \
    /**     size_t length    = strlen(s);                                   **/ \
    /**     char *s_checksum = (char *) malloc((length+2) * sizeof(char));  **/ \
    /**     sprintf(s_checksum, "%s%c", txt, damm_hex(txt));                **/ \
    /**     assert(damm_hex(s_checksum) == '0');                            **/ \
    /**                                                                     **/ \
    static inline char prefix##damm_hex(const char *txt) {                      \
                                                                                \
        /* Preconditions */                                                     \
        assert('9'-'0' == 9);                                                   \
        assert('f'-'a' == 5);                                                   \
        assert('F'-'A' == 5);                                                   \
                                                                                \
        /* Base 16 Tables for the Damm algorithm */                             \
        const char HEX[17]   = "0123456789ABCDEF";                              \
        const char T[16][16] = {                                                \
            { 0,  2,  4,  6,  8, 10, 12, 14,  3,  1,  7,  5, 11,  9, 15, 13},   \
            { 2,  0,  6,  4, 10,  8, 14, 12,  1,  3,  5,  7,  9, 11, 13, 15},   \
            { 4,  6,  0,  2, 12, 14,  8, 10,  7,  5,  3,  1, 15, 13, 11,  9},   \
            { 6,  4,  2,  0, 14, 12, 10,  8,  5,  7,  1,  3, 13, 15,  9, 11},   \
            { 8, 10, 12, 14,  0,  2,  4,  6, 11,  9, 15, 13,  3,  1,  7,  5},   \
            {10,  8, 14, 12,  2,  0,  6,  4,  9, 11, 13, 15,  1,  3,  5,  7},   \
            {12, 14,  8, 10,  4,  6,  0,  2, 15, 13, 11,  9,  7,  5,  3,  1},   \
            {14, 12, 10,  8,  6,  4,  2,  0, 13, 15,  9, 11,  5,  7,  1,  3},   \
            { 3,  1,  7,  5, 11,  9, 15, 13,  0,  2,  4,  6,  8, 10, 12, 14},   \
            { 1,  3,  5,  7,  9, 11, 13, 15,  2,  0,  6,  4, 10,  8, 14, 12},   \
            { 7,  5,  3,  1, 15, 13, 11,  9,  4,  6,  0,  2, 12, 14,  8, 10},   \
            { 5,  7,  1,  3, 13, 15,  9, 11,  6,  4,  2,  0, 14, 12, 10,  8},   \
            {11,  9, 15, 13,  3,  1,  7,  5,  8, 10, 12, 14,  0,  2,  4,  6},   \
            { 9, 11, 13, 15,  1,  3,  5,  7, 10,  8, 14, 12,  2,  0,  6,  4},   \
            {15, 13, 11,  9,  7,  5,  3,  1, 12, 14,  8, 10,  4,  6,  0,  2},   \
            {13, 15,  9, 11,  5,  7,  1,  3, 14, 12, 10,  8,  6,  4,  2,  0}};  \
                                                                                \
        /* Compute the checksum character */                                    \
        char   h, number = 0;                                                   \
        size_t i, length = strlen(txt);                                         \
        for (i = 0; i < length; i++) {                                          \
            if      ('0' <= txt[i] && txt[i] <= '9') { h = txt[i] - '0';      } \
            else if ('A' <= txt[i] && txt[i] <= 'F') { h = txt[i] - 'A' + 10; } \
            else if ('a' <= txt[i] && txt[i] <= 'f') { h = txt[i] - 'a' + 10; } \
            else { continue; }                                                  \
            number = T[(size_t) number][(size_t) h];                            \
        }                                                                       \
                                                                                \
        /* Return the checksum character */                                     \
        return HEX[(size_t) number];                                            \
    }                                                                           \

  /** ********************************************************************* **/
  /**                                                                       **/
  /** ### CLM_ARC4                                                          **/
  /**                                                                       **/
  /** A set of functions related to the ARC4 stream cypher.                 **/
  /**                                                                       **/
  /** All these functions assume (and enforce through assertions) that the  **/
  /** `char` type has a width of (exactly) 8 bits. This is quite common,    **/
  /** but not necessarily true in all systems. This macro cannot be used    **/
  /** in systems where that condition is not satisfied.                     **/
  /**                                                                       **/
  #define IMPORT_CLM_ARC4(prefix)                                               \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### arc4_hash                                                      **/ \
    /**                                                                     **/ \
    /** Returns a hash of the `txt` string.                                 **/ \
    /**                                                                     **/ \
    /** The output is formated as a `\0` terminated array of `char` of      **/ \
    /** twice the specified `length`. Each character is in hexadecimal      **/ \
    /** format (i.e. all characters belong to `[0,...,9,A,...,F]`).         **/ \
    /**                                                                     **/ \
    /** Parameter `drop` specifies how many pseudo-random bytes will be     **/ \
    /** discarded before computing the hash. It is recomended to select a   **/ \
    /** multiple of 256 as a `drop` (classic ARC4 defaults `drop` to 0).    **/ \
    /**                                                                     **/ \
    /** **Warning:** ARC4 IS NO LONGER CONSIDERED CRYPTOGRAPHICALLY SAFE.   **/ \
    /**                                                                     **/ \
    /** **Warning:** The `txt` parameter must be a `\0` terminated string.  **/ \
    /**                                                                     **/ \
    /** **Example:** Get `N` pseudo-random bytes with:                      **/ \
    /**                                                                     **/ \
    /**     size_t i, ii;                                                   **/ \
    /**     char   c;                                                       **/ \
    /**     char  *seed   = "MySeed";                                       **/ \
    /**     char  *hash   = arc4_hash(seed, N, 0);                          **/ \
    /**     char  *stream = (char *) malloc(N * sizeof(char));              **/ \
    /**     assert(hash != NULL && stream != NULL);                         **/ \
    /**     for (i = ii = 0; i < N; i++) {                                  **/ \
    /**         c = hash[ii++];                                             **/ \
    /**         if ('0' <= c && c <= '9') { stream[i] = (c-'0')<<4; }       **/ \
    /**         else                      { stream[i] = (c-'A')<<4; }       **/ \
    /**         c = hash[ii++];                                             **/ \
    /**         if ('0' <= c && c <= '9') { stream[i] += (c-'0'); }         **/ \
    /**         else                      { stream[i] += (c-'A'); }         **/ \
    /**     }                                                               **/ \
    /**     free(hash);                                                     **/ \
    /**                                                                     **/ \
    static inline char *prefix##arc4_hash(const char *txt, const size_t length, \
                                          const size_t drop) {                  \
        /* Preconditions */                                                     \
        assert(CHAR_BIT == 8);                                                  \
                                                                                \
        char   temp, S[256];                                                    \
        char  *hex     = "0123456789ABCDEF";                                    \
        size_t txt_len = (strlen(txt) == 0) ? (1) : (strlen(txt));              \
        size_t i, j, k, kk;                                                     \
                                                                                \
        /* Allocate output */                                                   \
        char *output = (char *) malloc((2*length)+1);                           \
        if (output == NULL) {                                                   \
            fprintf(stderr, "ERROR: Unable to allocate arc4 output.\n");        \
            return NULL;                                                        \
        }                                                                       \
                                                                                \
        /* Key-Scheduling Algorithm */                                          \
        for (i = 0; i < 256; i++) { S[i] = (char) i; }                          \
        for (j = k = 0; k < txt_len; k += 256) {                                \
            for (i = 0; i < 256; i++) {                                         \
                j    = (j + S[i] + txt[(i+k) % txt_len]) & 255;                 \
                temp = S[i];                                                    \
                S[i] = S[j];                                                    \
                S[j] = temp;                                                    \
            }                                                                   \
        }                                                                       \
                                                                                \
        /* Pseudo-Random Generation Algorithm: Drop Phase */                    \
        for (i = j = k = 0; k < drop; k++) {                                    \
            i    = (i + 1)    & 255;                                            \
            j    = (j + S[i]) & 255;                                            \
            temp = S[i];                                                        \
            S[i] = S[j];                                                        \
            S[j] = temp;                                                        \
        }                                                                       \
                                                                                \
        /* Pseudo-Random Generation Algorithm: Encoding Phase */                \
        for (k = kk = 0; k < length; k++) {                                     \
            i    = (i + 1)    & 255;                                            \
            j    = (j + S[i]) & 255;                                            \
            temp = S[i];                                                        \
            S[i] = S[j];                                                        \
            S[j] = temp;                                                        \
            temp = S[(S[i] + S[j]) & 255];                                      \
            output[kk++] = hex[(temp >> 4) & 15];                               \
            output[kk++] = hex[ temp       & 15];                               \
        }                                                                       \
        output[2*length] = '\0';                                                \
        return output;                                                          \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### arc4_encrypt                                                   **/ \
    /**                                                                     **/ \
    /** Encrypts the `txt` string using the `key` string.                   **/ \
    /**                                                                     **/ \
    /** The output is formated as a `\0` terminated array of `char` that is **/ \
    /** twice as long as `txt`. Each character is in hexadecimal format     **/ \
    /** (i.e. all characters belong to `[0,...,9,A,...,F]`).                **/ \
    /**                                                                     **/ \
    /** Parameter `drop` specifies how many pseudo-random bytes will be     **/ \
    /** discarded before encrypting `txt`. It is recomended to select a     **/ \
    /** multiple of 256 as a `drop` (classic ARC4 defaults `drop` to 0).    **/ \
    /**                                                                     **/ \
    /** Classic ARC4 requires `0 < strlen(key) <= 256`. This version        **/ \
    /** accepts smaller or larger `key` strings but is guaranteed to        **/ \
    /** produce the same output as the classic ARC4 if the `key` satisfies  **/ \
    /** the `0 < strlen(key) <= 256` condition.                             **/ \
    /**                                                                     **/ \
    /** **Warning:** ARC4 IS NO LONGER CONSIDERED CRYPTOGRAPHICALLY SAFE.   **/ \
    /**                                                                     **/ \
    /** **Warning:** The `key` parameter must be a `\0` terminated string.  **/ \
    /**                                                                     **/ \
    /** **Warning:** The `txt` parameter must be a `\0` terminated string.  **/ \
    /**                                                                     **/ \
    /** **Example:** Encrypt `Attack at dawn` using `Secret` as key with:   **/ \
    /**                                                                     **/ \
    /**     char *code = arc4_encrypt("Attack at dawn", "Secret", 0);       **/ \
    /**     if (code != NULL) { printf("Encrypted: '%s'\n", code); }        **/ \
    /**     free(code);                                                     **/ \
    /**                                                                     **/ \
    static inline char *prefix##arc4_encrypt(const char *txt, const char *key,  \
                                             const size_t drop) {               \
        /* Preconditions */                                                     \
        assert(CHAR_BIT == 8);                                                  \
                                                                                \
        char   temp, S[256];                                                    \
        char  *hex     = "0123456789ABCDEF";                                    \
        size_t txt_len =  strlen(txt);                                          \
        size_t key_len = (strlen(key) == 0) ? (1) : (strlen(key));              \
        size_t i, j, k, kk;                                                     \
                                                                                \
        /* Allocate output */                                                   \
        char *output = (char *) malloc((2*txt_len)+1);                          \
        if (output == NULL) {                                                   \
            fprintf(stderr, "ERROR: Unable to allocate arc4 output.\n");        \
            return NULL;                                                        \
        }                                                                       \
                                                                                \
        /* Key-Scheduling Algorithm */                                          \
        for (i = 0; i < 256; i++) { S[i] = (char) i; }                          \
        for (j = k = 0; k < key_len; k += 256) {                                \
            for (i = 0; i < 256; i++) {                                         \
                j    = (j + S[i] + key[(i+k) % key_len]) & 255;                 \
                temp = S[i];                                                    \
                S[i] = S[j];                                                    \
                S[j] = temp;                                                    \
            }                                                                   \
        }                                                                       \
                                                                                \
        /* Pseudo-Random Generation Algorithm: Drop Phase */                    \
        for (i = j = k = 0; k < drop; k++) {                                    \
            i    = (i + 1)    & 255;                                            \
            j    = (j + S[i]) & 255;                                            \
            temp = S[i];                                                        \
            S[i] = S[j];                                                        \
            S[j] = temp;                                                        \
        }                                                                       \
                                                                                \
        /* Pseudo-Random Generation Algorithm: Encoding Phase */                \
        for (k = kk = 0; k < txt_len; k++) {                                    \
            i    = (i + 1)    & 255;                                            \
            j    = (j + S[i]) & 255;                                            \
            temp = S[i];                                                        \
            S[i] = S[j];                                                        \
            S[j] = temp;                                                        \
            temp = txt[k] ^ S[(S[i] + S[j]) & 255];                             \
            output[kk++] = hex[(temp >> 4)  &  15];                             \
            output[kk++] = hex[ temp        &  15];                             \
        }                                                                       \
        output[2*txt_len] = '\0';                                               \
        return output;                                                          \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### arc4_decrypt                                                   **/ \
    /**                                                                     **/ \
    /** Decrypts the `txt` string using the `key` string.                   **/ \
    /**                                                                     **/ \
    /** The `txt` must be formated as a `\0` terminated array of `char` in  **/ \
    /** hexadecimal format (all characters belong to `[0,...,9,A,...,F]`).  **/ \
    /**                                                                     **/ \
    /** Parameter `drop` specifies how many pseudo-random bytes will be     **/ \
    /** discarded before encrypting `txt`. It is recomended to select a     **/ \
    /** multiple of 256 as a `drop` (classic ARC4 defaults `drop` to 0).    **/ \
    /**                                                                     **/ \
    /** Classic ARC4 requires `0 < strlen(key) <= 256`. This version        **/ \
    /** accepts smaller or larger `key` strings but is guaranteed to        **/ \
    /** produce the same output as the classic ARC4 if the `key` satisfies  **/ \
    /** the `0 < strlen(key) <= 256` condition.                             **/ \
    /**                                                                     **/ \
    /** **Warning:** ARC4 IS NO LONGER CONSIDERED CRYPTOGRAPHICALLY SAFE.   **/ \
    /**                                                                     **/ \
    /** **Warning:** The `key` parameter must be a `\0` terminated string.  **/ \
    /**                                                                     **/ \
    /** **Warning:** The `txt` parameter must be a `\0` terminated string.  **/ \
    /**                                                                     **/ \
    /** **Example:** Decrypt the coded message using `Secret` as key with:  **/ \
    /**                                                                     **/ \
    /**     char *code = "45A01F645FC35B383552544B9BF5"                     **/ \
    /**     char *txt  = arc4_decrypt(code, "Secret", 0);                   **/ \
    /**     if (txt != NULL) { printf("Decrypted: '%s'\n", txt); }          **/ \
    /**     free(txt);                                                      **/ \
    /**                                                                     **/ \
    static inline char *prefix##arc4_decrypt(const char *txt, const char *key,  \
                                             const size_t drop) {               \
        /* Preconditions */                                                     \
        assert(CHAR_BIT == 8);                                                  \
        for (size_t k = 0; k < strlen(txt); k++) {                              \
            assert(('0' <= txt[k] && txt[k] <= '9') ||                          \
                   ('A' <= txt[k] && txt[k] <= 'F') ||                          \
                   ('a' <= txt[k] && txt[k] <= 'f'));                           \
        }                                                                       \
                                                                                \
        char   aux, temp, S[256];                                               \
        size_t txt_len =  strlen(txt) / 2;                                      \
        size_t key_len = (strlen(key) == 0) ? (1) : (strlen(key));              \
        size_t i, j, k, kk;                                                     \
                                                                                \
        /* Allocate output */                                                   \
        char *output = (char *) malloc(txt_len+1);                              \
        if (output == NULL) {                                                   \
            fprintf(stderr, "ERROR: Unable to allocate arc4 output.\n");        \
            return NULL;                                                        \
        }                                                                       \
                                                                                \
        /* Key-Scheduling Algorithm */                                          \
        for (i = 0; i < 256; i++) { S[i] = (char) i; }                          \
        for (j = k = 0; k < key_len; k += 256) {                                \
            for (i = 0; i < 256; i++) {                                         \
                j    = (j + S[i] + key[(i+k) % key_len]) & 255;                 \
                temp = S[i];                                                    \
                S[i] = S[j];                                                    \
                S[j] = temp;                                                    \
            }                                                                   \
        }                                                                       \
                                                                                \
        /* Pseudo-Random Generation Algorithm: Drop Phase */                    \
        for (i = j = k = 0; k < drop; k++) {                                    \
            i    = (i + 1)    & 255;                                            \
            j    = (j + S[i]) & 255;                                            \
            temp = S[i];                                                        \
            S[i] = S[j];                                                        \
            S[j] = temp;                                                        \
        }                                                                       \
                                                                                \
        /* Pseudo-Random Generation Algorithm: Encoding Phase */                \
        for (k = kk = 0; k < txt_len; k++) {                                    \
            i    = (i + 1)    & 255;                                            \
            j    = (j + S[i]) & 255;                                            \
            temp = S[i];                                                        \
            S[i] = S[j];                                                        \
            S[j] = temp;                                                        \
            temp = txt[kk++];                                                   \
            if      ('0' <= temp && temp <= '9') { aux  = (temp-'0')   <<4; }   \
            else if ('A' <= temp && temp <= 'F') { aux  = (temp-'A'+10)<<4; }   \
            else                                 { aux  = (temp-'a'+10)<<4; }   \
            temp = txt[kk++];                                                   \
            if      ('0' <= temp && temp <= '9') { aux |= (temp-'0'); }         \
            else if ('A' <= temp && temp <= 'F') { aux |= (temp-'A'+10); }      \
            else                                 { aux |= (temp-'a'+10); }      \
            output[k] = aux ^ S[(S[i] + S[j]) & 255];                           \
        }                                                                       \
        output[txt_len] = '\0';                                                 \
        return output;                                                          \
    }                                                                           \
                                                                                \

  /** ********************************************************************* **/
  /**                                                                       **/
  /** ### CLM_ITER                                                          **/
  /**                                                                       **/
  /** A set of iterators to work with some generic combinatorial objects:   **/
  /**                                                                       **/
  /** **Products:** all mixed-radix tuples of fixed `length`                **/
  /**                                                                       **/
  /**       prod(3, (2,3,4)) = {(0,0,0), (0,0,1), (0,0,2), (0,0,3),         **/
  /**                           (0,1,0), (0,1,1), (0,1,2), (0,1,3),         **/
  /**                           (0,2,0), (0,2,1), (0,2,2), (0,2,3),         **/
  /**                           (1,0,0), (1,0,1), (1,0,2), (1,0,3),         **/
  /**                           (1,1,0), (1,1,1), (1,1,2), (1,1,3),         **/
  /**                           (1,2,0), (1,2,1), (1,2,2), (1,2,3)}         **/
  /**                                                                       **/
  /** **Permutations:** all tuples of fixed `length` whose elements are     **/
  /** all different and taken from a set of size `base`                     **/
  /**                                                                       **/
  /**       perm(3, 4, false) = {(0,1,2), (0,2,1), (1,0,2), (1,2,0),        **/
  /**                            (2,0,1), (2,1,0), (0,1,3), (0,3,1),        **/
  /**                            (1,0,3), (1,3,0), (3,0,1), (3,1,0),        **/
  /**                            (0,2,3), (0,3,2), (2,0,3), (2,3,0),        **/
  /**                            (3,0,2), (3,2,0), (1,2,3), (1,3,2),        **/
  /**                            (2,1,3), (2,3,1), (3,1,2), (3,2,1)}        **/
  /**                                                                       **/
  /** **Permutations with replacement:** all tuples of fixed `length`       **/
  /** whose elements are taken with replacement from a set of size `base`   **/
  /**                                                                       **/
  /**       perm(3, 4, true) = {(0,0,0), (0,0,1), (0,0,2), (0,0,3),         **/
  /**                           (0,1,0), (0,1,1), (0,1,2), (0,1,3),         **/
  /**                           (0,2,0), (0,2,1), (0,2,2), (0,2,3),         **/
  /**                           (0,3,0), (0,3,1), (0,3,2), (0,3,3),         **/
  /**                           (1,0,0), (1,0,1), (1,0,2), (1,0,3),         **/
  /**                           (1,1,0), (1,1,1), (1,1,2), (1,1,3),         **/
  /**                           (1,2,0), (1,2,1), (1,2,2), (1,2,3),         **/
  /**                           (1,3,0), (1,3,1), (1,3,2), (1,3,3),         **/
  /**                           (2,0,0), (2,0,1), (2,0,2), (2,0,3),         **/
  /**                           (2,1,0), (2,1,1), (2,1,2), (2,1,3),         **/
  /**                           (2,2,0), (2,2,1), (2,2,2), (2,2,3),         **/
  /**                           (2,3,0), (2,3,1), (2,3,2), (2,3,3),         **/
  /**                           (3,0,0), (3,0,1), (3,0,2), (3,0,3),         **/
  /**                           (3,1,0), (3,1,1), (3,1,2), (3,1,3),         **/
  /**                           (3,2,0), (3,2,1), (3,2,2), (3,2,3),         **/
  /**                           (3,3,0), (3,3,1), (3,3,2), (3,3,3)}         **/
  /**                                                                       **/
  /** **Combinations:** all sorted tuples of fixed `length` whose elements  **/
  /** are all different and taken from a set of size `base`                 **/
  /**                                                                       **/
  /**       comb(3, 4, false) = {(0,1,2), (0,1,3), (0,2,3), (1,2,3)}        **/
  /**                                                                       **/
  /** **Combinations with replacement:** all sorted tuples of fixed         **/
  /** `length` whose elements are taken with replacement from a set of      **/
  /** size `base`                                                           **/
  /**                                                                       **/
  /**       comb(3, 4, true) = {(0,0,0), (0,0,1), (0,0,2), (0,0,3),         **/
  /**                           (0,1,1), (0,1,2), (0,1,3), (0,2,2),         **/
  /**                           (0,2,3), (0,3,3), (1,1,1), (1,1,2),         **/
  /**                           (1,1,3), (1,2,2), (1,2,3), (1,3,3),         **/
  /**                           (2,2,2), (2,2,3), (2,3,3), (3,3,3)}         **/
  /**                                                                       **/
  /** For each combinatorial object two functions are provided:             **/
  /**                                                                       **/
  /** * `iter_rand_` returns an uniformly random element of the object.     **/
  /** * `iter_next_` given an element of the object, returns the next one.  **/
  /**                                                                       **/
  /** The elements of a combinatorial object are always represented as      **/
  /** `size_t` arrays that contain indexes of the corresponding base set    **/
  /** (i.e. `0 <= array[i] < base`) so you can use them to reference        **/
  /** arbitrary sets of `base` elements.                                    **/
  /**                                                                       **/
  #define IMPORT_CLM_ITER(prefix)                                               \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### iter_rand_prod                                                 **/ \
    /**                                                                     **/ \
    /** Generates an uniformly random `length`-sized tuple such that:       **/ \
    /**                                                                     **/ \
    /**     0 <= prod[i] < base[i]                                          **/ \
    /**                                                                     **/ \
    /** If `*prod == NULL` the function tries to allocate a new tuple.      **/ \
    /** Otherwise, it overwrites the information stored in `prod`.          **/ \
    /**                                                                     **/ \
    /** **Warning:** Parameter `length` must satisfy `lenght > 0`.          **/ \
    /**                                                                     **/ \
    /** **Warning:** Parameter `base` must satisfy `base != NULL` and also  **/ \
    /** `RAND_MAX >= base[i] > 0` for al `i = 0...length-1`.                **/ \
    /**                                                                     **/ \
    /** **Example:** Generate three random elements of `[0,5)x[0,3)` with:  **/ \
    /**                                                                     **/ \
    /**     size_t length  = 2;                                             **/ \
    /**     size_t base[2] = {5, 3};                                        **/ \
    /**     size_t *prod   = NULL;                                          **/ \
    /**     iter_rand_prod(&prod, length, base);                            **/ \
    /**     for (size_t i = 0; i < 3; i++) {                                **/ \
    /**         do_something(prod);                                         **/ \
    /**         iter_rand_prod(&prod, length, base);                        **/ \
    /**     }                                                               **/ \
    /**                                                                     **/ \
    static inline void prefix##iter_rand_prod(size_t **prod,                    \
                                              const size_t length,              \
                                              const size_t *base) {             \
        size_t i, *P = *prod;                                                   \
                                                                                \
        /* Preconditions */                                                     \
        assert(length > 0);                                                     \
        assert(base != NULL);                                                   \
        for (i = 0; i < length; i++) {                                          \
            assert(base[i] > 0);                                                \
            assert(RAND_MAX >= base[i]);                                        \
        }                                                                       \
                                                                                \
        /* Allocate memory */                                                   \
        if (P == NULL) { P = (size_t *) malloc(length * sizeof(size_t)); }      \
                                                                                \
        /* Check allocated memory */                                            \
        if (P == NULL) {                                                        \
            fprintf(stderr, "ERROR: Unable to allocate random product.\n");     \
        }                                                                       \
                                                                                \
        /* Get random product */                                                \
        else{                                                                   \
            size_t r, range;                                                    \
            for (i = 0; i < length; i++) {                                      \
                range = RAND_MAX - (RAND_MAX % base[i]);                        \
                do { r = rand(); } while (r >= range);                          \
                P[i] = r % base[i];                                             \
            }                                                                   \
        }                                                                       \
                                                                                \
        /* Store the current product */                                         \
        *prod = P;                                                              \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### iter_next_prod                                                 **/ \
    /**                                                                     **/ \
    /** Updates `*prod` to hold the next `length`-sized tuple such that:    **/ \
    /**                                                                     **/ \
    /**     0 <= prod[i] < base[i]                                          **/ \
    /**                                                                     **/ \
    /** If `*prod == NULL` the function tries to allocate the first tuple.  **/ \
    /** Once it reaches the last tuple, the function frees & nulls `*prod`. **/ \
    /**                                                                     **/ \
    /** **Warning:** Parameter `length` must satisfy `lenght > 0`.          **/ \
    /**                                                                     **/ \
    /** **Warning:** Parameter `base` must satisfy `base != NULL` and also  **/ \
    /** `base[i] > 0` for all `i = 0...length-1`.                           **/ \
    /**                                                                     **/ \
    /** **Example:** Iterate over all the elements of `[0,5)x[0,3)` with:   **/ \
    /**                                                                     **/ \
    /**     size_t length  = 2;                                             **/ \
    /**     size_t base[2] = {5, 3};                                        **/ \
    /**     size_t *prod   = NULL;                                          **/ \
    /**     iter_next_prod(&prod, length, base);                            **/ \
    /**     while (prod) {                                                  **/ \
    /**         do_something(prod);                                         **/ \
    /**         iter_next_prod(&prod, length, base);                        **/ \
    /**     }                                                               **/ \
    /**                                                                     **/ \
    static inline void prefix##iter_next_prod(size_t **prod,                    \
                                              const size_t length,              \
                                              const size_t *base) {             \
        size_t i, *P = *prod;                                                   \
                                                                                \
        /* Preconditions */                                                     \
        assert(length > 0);                                                     \
        assert(base != NULL);                                                   \
        for (i = 0; i < length; i++) { assert(base[i] > 0); }                   \
                                                                                \
        /* Allocate a new product... */                                         \
        if (P == NULL) {                                                        \
            P = (size_t *) malloc(length * sizeof(size_t));                     \
            if (P != NULL) { for (i = 0; i < length; i++) { P[i] = 0; } }       \
            else { fprintf(stderr, "ERROR: Unable to allocate product.\n"); }   \
        }                                                                       \
                                                                                \
        /* ...or update the current one */                                      \
        else {                                                                  \
            for (i = length; i > 0; i--) {                                      \
                P[i-1] += 1;                                                    \
                if (P[i-1] == base[i-1]) { P[i-1] = 0; } else { break; }        \
            }                                                                   \
            if (i == 0) { free(P); P = NULL; }                                  \
        }                                                                       \
                                                                                \
        /* Store the current product */                                         \
        *prod = P;                                                              \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### iter_rand_perm                                                 **/ \
    /**                                                                     **/ \
    /** Generates an uniformly random `length`-sized tuple such that:       **/ \
    /**                                                                     **/ \
    /**     0 <= perm[i] < base                                             **/ \
    /**                                                                     **/ \
    /** If `*perm == NULL` the function tries to allocate a new tuple.      **/ \
    /** Otherwise, it overwrites the information stored in `perm`.          **/ \
    /**                                                                     **/ \
    /** If `rep == false` all the elements of the tuple will be different.  **/ \
    /**                                                                     **/ \
    /** **Warning:** Parameter `length` must satisfy `lenght > 0`.          **/ \
    /**                                                                     **/ \
    /** **Warning:** Parameter `base` must satisfy `base <= RAND_MAX`.      **/ \
    /**                                                                     **/ \
    /** **Warning:** If `rep == true` then `base > 0` is required.          **/ \
    /**                                                                     **/ \
    /** **Warning:** If `rep == false` then `base >= length` is required.   **/ \
    /**                                                                     **/ \
    /** **Example:** Get a random element of `[0,5)^3` with:                **/ \
    /**                                                                     **/ \
    /**     size_t *perm = NULL;                                            **/ \
    /**     iter_rand_perm(&perm, 3, 5, true);                              **/ \
    /**                                                                     **/ \
    /** **Example:** Get a random 3-permutation of `[0,5)` with:            **/ \
    /**                                                                     **/ \
    /**     size_t *perm = NULL;                                            **/ \
    /**     iter_rand_perm(&perm, 3, 5, false);                             **/ \
    /**                                                                     **/ \
    static inline void prefix##iter_rand_perm(size_t **perm,                    \
                                              const size_t length,              \
                                              const size_t base,                \
                                              const bool rep) {                 \
        /* Preconditions */                                                     \
        assert(length > 0);                                                     \
        assert(RAND_MAX >= base);                                               \
        if (rep) { assert(base > 0);       }                                    \
        else     { assert(base >= length); }                                    \
                                                                                \
        size_t i, j, range, *P = *perm;                                         \
                                                                                \
        /* Allocate memory */                                                   \
        if (P == NULL) { P = (size_t *) malloc(length * sizeof(size_t)); }      \
                                                                                \
        /* Check allocated memory */                                            \
        if (P == NULL) {                                                        \
            fprintf(stderr, "ERROR: Unable to allocate random permutation.\n"); \
        }                                                                       \
                                                                                \
        /* Get random permutation with repetition */                            \
        else if (rep) {                                                         \
                                                                                \
            /* Fill it uniformly at random */                                   \
            range = RAND_MAX - (RAND_MAX % base);                               \
            for (i = 0; i < length; i++) {                                      \
                do { j = rand(); } while (j >= range);                          \
                P[i] = j % base;                                                \
            }                                                                   \
        }                                                                       \
                                                                                \
        /* Get a random permutation without repetition */                       \
        else {                                                                  \
                                                                                \
            /* Initialize it using the Inside-Out Fisher-Yates Shuffle */       \
            for (i = 0; i < length; i++) {                                      \
                range = RAND_MAX - (RAND_MAX % (i+1));                          \
                do { j = rand(); } while (j >= range);                          \
                j = j % (i+1);                                                  \
                if (i != j) { P[i] = P[j]; }                                    \
                P[j] = i;                                                       \
            }                                                                   \
                                                                                \
            /* Now use reservoir sampling for the rest of the elements */       \
            for (i = length; i < base; i++) {                                   \
                range = RAND_MAX - (RAND_MAX % (i+1));                          \
                do { j = rand(); } while (j >= range);                          \
                j = j % (i+1);                                                  \
                if (j < length) { P[j] = i; }                                   \
            }                                                                   \
        }                                                                       \
                                                                                \
        /* Store the current permutation */                                     \
        *perm = P;                                                              \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### iter_next_perm                                                 **/ \
    /**                                                                     **/ \
    /** Updates `*perm` to hold the next `length`-sized tuple such that:    **/ \
    /**                                                                     **/ \
    /**     0 <= perm[i] < base[i]                                          **/ \
    /**                                                                     **/ \
    /** If `*perm == NULL` the function tries to allocate the first tuple.  **/ \
    /** Once it reaches the last tuple, the function frees & nulls `*perm`. **/ \
    /**                                                                     **/ \
    /** If `rep == false` all the elements of the tuple will be different.  **/ \
    /**                                                                     **/ \
    /** **Warning:** Parameter `length` must satisfy `lenght > 0`.          **/ \
    /**                                                                     **/ \
    /** **Warning:** If `rep == true` then `base > 0` is required.          **/ \
    /**                                                                     **/ \
    /** **Warning:** If `rep == false` then `base >= length` is required.   **/ \
    /**                                                                     **/ \
    /** **Example:** Iterate over all the elements of `[0,5)^3` with:       **/ \
    /**                                                                     **/ \
    /**     size_t *perm = NULL;                                            **/ \
    /**     iter_next_perm(&perm, 3, 5, true);                              **/ \
    /**     while (perm) {                                                  **/ \
    /**         do_something(perm);                                         **/ \
    /**         iter_next_perm(&perm, 3, 5, true);                          **/ \
    /**     }                                                               **/ \
    /**                                                                     **/ \
    /** **Example:** Iterate over all the 3-permutations of `[0,5)` with:   **/ \
    /**                                                                     **/ \
    /**     size_t *perm = NULL;                                            **/ \
    /**     iter_next_perm(&perm, 3, 5, false);                             **/ \
    /**     while (perm) {                                                  **/ \
    /**         do_something(perm);                                         **/ \
    /**         iter_next_perm(&perm, 3, 5, false);                         **/ \
    /**     }                                                               **/ \
    /**                                                                     **/ \
    static inline void prefix##iter_next_perm(size_t **perm,                    \
                                              const size_t length,              \
                                              const size_t base,                \
                                              const bool rep) {                 \
        /* Preconditions */                                                     \
        assert(length > 0);                                                     \
        if (rep) { assert(base > 0);       }                                    \
        else     { assert(base >= length); }                                    \
                                                                                \
        size_t i, j, t, *P = *perm;                                             \
                                                                                \
        /* Allocate a new permutation... */                                     \
        if (P == NULL) {                                                        \
            P = (size_t *) malloc(length * sizeof(size_t));                     \
            if (P == NULL) {                                                    \
                fprintf(stderr, "ERROR: Unable to allocate permutation.\n");    \
            }                                                                   \
            else if (rep) { for (i = 0; i < length; i++) { P[i] = 0; } }        \
            else          { for (i = 0; i < length; i++) { P[i] = i; } }        \
        }                                                                       \
                                                                                \
        /* ...or update the current one */                                      \
        else if (rep) {                                                         \
                                                                                \
            /* Next permutation with repetition */                              \
            for (i = length; i > 0; i--) {                                      \
                P[i-1] += 1;                                                    \
                if (P[i-1] == base) { P[i-1] = 0; } else { break; }             \
            }                                                                   \
            if (i == 0) { free(P); P = NULL; }                                  \
                                                                                \
        } else {                                                                \
                                                                                \
            /* Next permutation without repetition */                           \
            for (i = length-1; i > 0 && P[i-1] >= P[i]; i--);                   \
            if (i == 0) {                                                       \
                for (i = 0, j = length-1; i < j; i++, j--) {                    \
                    t = P[i]; P[i] = P[j]; P[j] = t;                            \
                }                                                               \
                for (i = length; i > 0 && P[i-1] == base-length+i-1; i--);      \
                if (i == 0) { free(P); P = NULL; }                              \
                else { for (P[i-1]++; i < length; i++) { P[i] = P[i-1] + 1; } } \
            } else {                                                            \
                i = i-1;                                                        \
                for (j = length-1; j > i; j--) { if (P[i] < P[j]) { break; } }  \
                t = P[i]; P[i] = P[j]; P[j] = t;                                \
                i = i+1; j = length-1;                                          \
                while (i < j) { t = P[i]; P[i] = P[j]; P[j] = t; i++; j--; }    \
            }                                                                   \
        }                                                                       \
                                                                                \
        /* Store the current permutation */                                     \
        *perm = P;                                                              \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### iter_rand_comb                                                 **/ \
    /**                                                                     **/ \
    /** Generates an uniformly random `length`-sized tuple such that:       **/ \
    /**                                                                     **/ \
    /**     0 <= comb[i] < base    &&    comb[i] <= comb[i+1]               **/ \
    /**                                                                     **/ \
    /** If `*comb == NULL` the function tries to allocate a new tuple.      **/ \
    /** Otherwise, it overwrites the information stored in `comb`.          **/ \
    /**                                                                     **/ \
    /** If `rep == false` all the elements of the tuple will be different.  **/ \
    /**                                                                     **/ \
    /** **Warning:** Parameter `length` must satisfy `lenght > 0`.          **/ \
    /**                                                                     **/ \
    /** **Warning:** Parameter `base` must satisfy `base <= RAND_MAX`.      **/ \
    /**                                                                     **/ \
    /** **Warning:** If `rep == true` then `base > 0` is required.          **/ \
    /**                                                                     **/ \
    /** **Warning:** If `rep == false` then `base >= length` is required.   **/ \
    /**                                                                     **/ \
    /** **Example:** Get a random 3-combination of `[0,5)` with:            **/ \
    /**                                                                     **/ \
    /**     size_t *comb = NULL;                                            **/ \
    /**     iter_rand_comb(&comb, 3, 5, false);                             **/ \
    /**                                                                     **/ \
    /** **Example:** Get a random 3-comb-with-rep of `[0,5)` with:          **/ \
    /**                                                                     **/ \
    /**     size_t *comb = NULL;                                            **/ \
    /**     iter_rand_comb(&comb, 3, 5, true);                              **/ \
    /**                                                                     **/ \
    static inline void prefix##iter_rand_comb(size_t **comb,                    \
                                              const size_t length,              \
                                              const size_t base,                \
                                              const bool rep) {                 \
        /* Preconditions */                                                     \
        assert(length > 0);                                                     \
        assert(RAND_MAX >= base);                                               \
        if (rep) { assert(base > 0);       }                                    \
        else     { assert(base >= length); }                                    \
                                                                                \
        size_t i, j, k, n, range, *C = *comb;                                   \
                                                                                \
        /* Allocate memory */                                                   \
        if (C == NULL) { C = (size_t *) malloc(length * sizeof(size_t)); }      \
                                                                                \
        /* Check allocated memory */                                            \
        if (C == NULL) {                                                        \
            fprintf(stderr, "ERROR: Unable to allocate random combination.\n"); \
        }                                                                       \
                                                                                \
        /* Get random combination with repetition */                            \
        else if (rep) {                                                         \
            n = base + length - 1;                                              \
            for (i = k = 0; i < n; i++) {                                       \
                range = RAND_MAX - (RAND_MAX % (n-i));                          \
                do { j = rand(); } while (j >= range);                          \
                j = j % (n-i);                                                  \
                if (j < length-k) { C[k] = i-k; k++; }                          \
            }                                                                   \
        }                                                                       \
                                                                                \
        /* Get a random combination without repetition */                       \
        else {                                                                  \
            for (i = k = 0; i < base; i++) {                                    \
                range = RAND_MAX - (RAND_MAX % (base-i));                       \
                do { j = rand(); } while (j >= range);                          \
                j = j % (base-i);                                               \
                if (j < length-k) { C[k++] = i; }                               \
            }                                                                   \
        }                                                                       \
                                                                                \
        /* Store the current combination */                                     \
        *comb = C;                                                              \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### iter_next_comb                                                 **/ \
    /**                                                                     **/ \
    /** Updates `*comb` to hold the next `length`-sized tuple such that:    **/ \
    /**                                                                     **/ \
    /**     0 <= comb[i] < base    &&    comb[i] <= comb[i+1]               **/ \
    /**                                                                     **/ \
    /** If `*comb == NULL` the function tries to allocate the first tuple.  **/ \
    /** Once it reaches the last tuple, the function frees & nulls `*comb`. **/ \
    /**                                                                     **/ \
    /** If `rep == false` all the elements of the tuple will be different.  **/ \
    /**                                                                     **/ \
    /** **Warning:** Parameter `length` must satisfy `lenght > 0`.          **/ \
    /**                                                                     **/ \
    /** **Warning:** If `rep == true` then `base > 0` is required.          **/ \
    /**                                                                     **/ \
    /** **Warning:** If `rep == false` then `base >= length` is required.   **/ \
    /**                                                                     **/ \
    /** **Example:** Iterate over all the 3-combinations of `[0,5)` with:   **/ \
    /**                                                                     **/ \
    /**     size_t *comb  = NULL;                                           **/ \
    /**     iter_next_comb(&comb, 3, 5, false);                             **/ \
    /**     while (comb) {                                                  **/ \
    /**         do_something(comb);                                         **/ \
    /**         iter_next_comb(&comb, 3, 5, false);                         **/ \
    /**     }                                                               **/ \
    /**                                                                     **/ \
    /** **Example:** Iterate over all the 3-comb-with-rep of `[0,5)` with:  **/ \
    /**                                                                     **/ \
    /**     size_t *comb  = NULL;                                           **/ \
    /**     iter_next_comb(&comb, 3, 5, true);                              **/ \
    /**     while (comb) {                                                  **/ \
    /**         do_something(comb);                                         **/ \
    /**         iter_next_comb(&comb, 3, 5, true);                          **/ \
    /**     }                                                               **/ \
    /**                                                                     **/ \
    static inline void prefix##iter_next_comb(size_t **comb,                    \
                                              const size_t length,              \
                                              const size_t base,                \
                                              const bool rep) {                 \
        /* Preconditions */                                                     \
        assert(length > 0);                                                     \
        if (rep) { assert(base > 0);       }                                    \
        else     { assert(base >= length); }                                    \
                                                                                \
        size_t i, *C = *comb;                                                   \
                                                                                \
        /* Allocate a new combination... */                                     \
        if (C == NULL) {                                                        \
            C = (size_t *) malloc(length * sizeof(size_t));                     \
            if (C == NULL) {                                                    \
                fprintf(stderr, "ERROR: Unable to allocate combination.\n");    \
            }                                                                   \
            else if (rep) { for (i = 0; i < length; i++) { C[i] = 0; } }        \
            else          { for (i = 0; i < length; i++) { C[i] = i; } }        \
        }                                                                       \
                                                                                \
        /* ...or update the current one */                                      \
        else if (rep) {                                                         \
                                                                                \
            /* Get next combination with repetition */                          \
            for (i = length; i > 0 && C[i-1] == base-1; i--);                   \
            if (i == 0) { free(C); C = NULL; }                                  \
            else { for (C[i-1]++; i < length; i++) { C[i] = C[i-1]; } }         \
                                                                                \
        } else {                                                                \
                                                                                \
            /* Get next combination without repetition */                       \
            for (i = length; i > 0 && C[i-1] == base-length+i-1; i--);          \
            if (i == 0) { free(C); C = NULL; }                                  \
            else { for (C[i-1]++; i < length; i++) { C[i] = C[i-1] + 1; } }     \
        }                                                                       \
                                                                                \
        /* Store the current combination */                                     \
        *comb = C;                                                              \
    }                                                                           \
                                                                                \

  /** ********************************************************************* **/
  /**                                                                       **/
  /** ### CLM_FRACTAL                                                       **/
  /**                                                                       **/
  /** A set of functions to work with some well known space-filling curves. **/
  /**                                                                       **/
  #define IMPORT_CLM_FRACTAL(prefix)                                            \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### fractal_van_der_corput                                         **/ \
    /**                                                                     **/ \
    /** Returns the `n`-th element of the Van der Corput sequence with the  **/ \
    /** specified `base` and number of `digits`.                            **/ \
    /**                                                                     **/ \
    /** **Warning:** Parameter `base` must satisfy `base > 1`.              **/ \
    /**                                                                     **/ \
    /** **Warning:** Parameter `digits` must satisfy `digits > 0`.          **/ \
    /**                                                                     **/ \
    /** **Warning:** `n` can be bigger, but only the last `digits` digits   **/ \
    /** of `n` will be used.                                                **/ \
    /**                                                                     **/ \
    /** **Warning:** This operations is its own inverse.                    **/ \
    /**                                                                     **/ \
    /** **Example:** Print a permutation of the first K^D integers with:    **/ \
    /**                                                                     **/ \
    /**     size_t pow = 1;                                                 **/ \
    /**     for (size_t i = 0; i < D; i++) { pow *= K; }                    **/ \
    /**     for (size_t N = 0; N < pow; N++) {                              **/ \
    /**         printf("%zu ", fractal_van_der_corput(K, D, N));            **/ \
    /**     }                                                               **/ \
    /**                                                                     **/ \
    static inline size_t prefix##fractal_van_der_corput(const size_t base,      \
                                                        size_t digits,          \
                                                        size_t n) {             \
        /* Preconditions */                                                     \
        assert(digits > 0);                                                     \
        assert(base   > 1);                                                     \
                                                                                \
        size_t r = 0;                                                           \
        while (digits > 0) {                                                    \
            r *= base;                                                          \
            r += n % base;                                                      \
            n /= base;                                                          \
            digits--;                                                           \
        }                                                                       \
        return r;                                                               \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### fractal_lebesgue_coord                                         **/ \
    /**                                                                     **/ \
    /** Returns the `dim` dimensional coordinates of the `N`-th point of    **/ \
    /** the Lebesgue (Z-index) space-filling curve of `bits` levels.        **/ \
    /**                                                                     **/ \
    /** The 64 less significant bits of `N` should be stored in `L[0]`,     **/ \
    /** the next 64 less significant bits in `L[1]`, and so on.             **/ \
    /**                                                                     **/ \
    /** **Warning:** Parameter `dim` must satisfy `dim > 0`.                **/ \
    /**                                                                     **/ \
    /** **Warning:** Parameter `bits` must satisfy `bits > 0`.              **/ \
    /**                                                                     **/ \
    /** **Warning:** A `size_t` varible must have at least `bits` bits.     **/ \
    /**                                                                     **/ \
    /** **Example:** Visit the 4096 points of the `[0,16)^3` 3D cube with:  **/ \
    /**                                                                     **/ \
    /**     size_t coord[3];                                                **/ \
    /**     for (size_t i = 0; i < 4096; i++) {                             **/ \
    /**         coord[0] = i; coord[1] = coord[2] = 0;                      **/ \
    /**         fractal_lebesgue_coord(3, 4, coord);                        **/ \
    /**         do_something(coord);                                        **/ \
    /**     }                                                               **/ \
    /**                                                                     **/ \
    static inline void prefix##fractal_lebesgue_coord(const size_t dim,         \
                                                      const size_t bits,        \
                                                      size_t *L) {              \
        /* Preconditions */                                                     \
        assert(sizeof(size_t) * CHAR_BIT >= bits);                              \
        assert(bits > 0);                                                       \
        assert(dim  > 0);                                                       \
                                                                                \
        size_t b, d, dd, mask, bit, coord[dim];                                 \
                                                                                \
        /* Compute coordinates from Z-index */                                  \
        for (d = 0; d < dim; d++) { coord[d] = 0; }                             \
        bit  = 1;                                                               \
        mask = 1;                                                               \
        dd   = 0;                                                               \
        for (b = 0; b < bits; b++) {                                            \
            for (d = dim; d--> 0; ) {                                           \
                if (L[dd] & mask) { coord[d] += bit; }                          \
                mask <<= 1;                                                     \
                if (!mask) { mask = 1; dd++; }                                  \
            }                                                                   \
            bit <<= 1;                                                          \
        }                                                                       \
        for (d = 0; d < dim; d++) { L[d] = coord[d]; }                          \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### fractal_lebesgue_index                                         **/ \
    /**                                                                     **/ \
    /** Returns the index of the `dim` dimensional point of the given       **/ \
    /** coordinates in a Lebesgue (Z-index) space-filling curve of `bits`   **/ \
    /** levels.                                                             **/ \
    /**                                                                     **/ \
    /** The 64 less significant bits of the index will be stored in `L[0]`, **/ \
    /** the next 64 less significant bits in `L[1]`, and so on.             **/ \
    /**                                                                     **/ \
    /** **Warning:** Parameter `dim` must satisfy `dim > 0`.                **/ \
    /**                                                                     **/ \
    /** **Warning:** Parameter `bits` must satisfy `bits > 0`.              **/ \
    /**                                                                     **/ \
    /** **Warning:** A `size_t` varible must have at least `bits` bits.     **/ \
    /**                                                                     **/ \
    /** **Example:** Compare two points of the `[0,16)^3` 3D cube with:     **/ \
    /**                                                                     **/ \
    /**     size_t P[3] = {5, 3, 14};                                       **/ \
    /**     size_t Q[3] = {3, 5, 14};                                       **/ \
    /**     fractal_lebesgue_index(3, 4, P);                                **/ \
    /**     fractal_lebesgue_index(3, 4, Q);                                **/ \
    /**     if (P[0] < Q[0]) { printf("P goes before Q.\n"); }              **/ \
    /**     else             { printf("Q goes before P.\n"); }              **/ \
    /**                                                                     **/ \
    static inline void prefix##fractal_lebesgue_index(const size_t dim,         \
                                                      const size_t bits,        \
                                                      size_t *L) {              \
        /* Preconditions */                                                     \
        assert(sizeof(size_t) * CHAR_BIT >= bits);                              \
        assert(bits > 0);                                                       \
        assert(dim  > 0);                                                       \
                                                                                \
        size_t b, d, dd, mask, bit, index[dim];                                 \
                                                                                \
        /* Compute the Z-index from coordinates */                              \
        for (d = 0; d < dim; d++) { index[d] = 0; }                             \
        bit  = 1;                                                               \
        mask = 1;                                                               \
        dd   = 0;                                                               \
        for (b = 0; b < bits; b++) {                                            \
            for (d = dim; d-->0; ) {                                            \
                if (L[d] & mask) { index[dd] += bit; }                          \
                bit <<= 1;                                                      \
            }                                                                   \
            mask <<= 1;                                                         \
            if (!mask) { mask = 1; dd++; }                                      \
        }                                                                       \
        for (d = 0; d < dim; d++) { L[d] = index[d]; }                          \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### fractal_hilbert_coord                                          **/ \
    /**                                                                     **/ \
    /** Returns the `dim` dimensional coordinates of the `N`-th point of    **/ \
    /** the Hilbert space-filling curve of `bits` levels.                   **/ \
    /**                                                                     **/ \
    /** The 64 less significant bits of `N` should be stored in `L[0]`,     **/ \
    /** the next 64 less significant bits in `L[1]`, and so on.             **/ \
    /**                                                                     **/ \
    /** **Warning:** Parameter `dim` must satisfy `dim > 0`.                **/ \
    /**                                                                     **/ \
    /** **Warning:** Parameter `bits` must satisfy `bits > 0`.              **/ \
    /**                                                                     **/ \
    /** **Warning:** A `size_t` varible must have at least `bits` bits.     **/ \
    /**                                                                     **/ \
    /** **Example:** Visit the 4096 points of the `[0,16)^3` 3D cube with:  **/ \
    /**                                                                     **/ \
    /**     size_t coord[3];                                                **/ \
    /**     for (size_t i = 0; i < 4096; i++) {                             **/ \
    /**         coord[0] = i; coord[1] = coord[2] = 0;                      **/ \
    /**         fractal_hilbert_coord(3, 4, coord);                         **/ \
    /**         do_something(coord);                                        **/ \
    /**     }                                                               **/ \
    /**                                                                     **/ \
    static inline void prefix##fractal_hilbert_coord(const size_t dim,          \
                                                     const size_t bits,         \
                                                     size_t *H) {               \
        /* Preconditions */                                                     \
        assert(sizeof(size_t) * CHAR_BIT >= bits);                              \
        assert(bits > 0);                                                       \
        assert(dim  > 0);                                                       \
                                                                                \
        size_t b, d, dd, mask, bit, temp, aux[dim], max = 1 << bits;            \
                                                                                \
        /* Compute transposed representation of H-index */                      \
        for (d = 0; d < dim; d++) { aux[d] = 0; }                               \
        bit  = 1;                                                               \
        mask = 1;                                                               \
        dd   = 0;                                                               \
        for (b = 0; b < bits; b++) {                                            \
            for (d = dim; d--> 0; ) {                                           \
                if (H[dd] & mask) { aux[d] += bit; }                            \
                mask <<= 1;                                                     \
                if (!mask) { mask = 1; dd++; }                                  \
            }                                                                   \
            bit <<= 1;                                                          \
        }                                                                       \
        for (d = 0; d < dim; d++) { H[d] = aux[d]; }                            \
                                                                                \
        /* Gray decode */                                                       \
        temp = H[dim-1] >> 1;                                                   \
        for (d = dim; d--> 1; ) { H[d] ^= H[d-1]; }                             \
        H[0] ^= temp;                                                           \
                                                                                \
        /* Undo excess work */                                                  \
        for (bit = 2; bit != max; bit <<= 1) {                                  \
            mask = bit - 1;                                                     \
            for (d = dim; d--> 0; ) {                                           \
                if (H[d] & bit) { H[0] ^= mask; }                               \
                else {                                                          \
                    temp  = (H[0]^H[d]) & mask;                                 \
                    H[0] ^= temp;                                               \
                    H[d] ^= temp;                                               \
                }                                                               \
            }                                                                   \
        }                                                                       \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### fractal_coord_to_h                                             **/ \
    /**                                                                     **/ \
    /** Returns the index of the `dim` dimensional point of the given       **/ \
    /** coordinates in a Hilbert space-filling curve of `bits` levels.      **/ \
    /**                                                                     **/ \
    /** The 64 less significant bits of the index will be stored in `L[0]`, **/ \
    /** the next 64 less significant bits in `L[1]`, and so on.             **/ \
    /**                                                                     **/ \
    /** **Warning:** Parameter `dim` must satisfy `dim > 0`.                **/ \
    /**                                                                     **/ \
    /** **Warning:** Parameter `bits` must satisfy `bits > 0`.              **/ \
    /**                                                                     **/ \
    /** **Warning:** A `size_t` varible must have at least `bits` bits.     **/ \
    /**                                                                     **/ \
    /** **Example:** Compare two points of the `[0,16)^3` 3D cube with:     **/ \
    /**                                                                     **/ \
    /**     size_t P[3] = {5, 3, 14};                                       **/ \
    /**     size_t Q[3] = {3, 5, 14};                                       **/ \
    /**     fractal_hilbert_index(3, 4, P);                                 **/ \
    /**     fractal_hilbert_index(3, 4, Q);                                 **/ \
    /**     if (P[0] < Q[0]) { printf("P goes before Q.\n"); }              **/ \
    /**     else             { printf("Q goes before P.\n"); }              **/ \
    /**                                                                     **/ \
    static inline void prefix##fractal_hilbert_index(const size_t dim,          \
                                                     const size_t bits,         \
                                                     size_t *H) {               \
        /* Preconditions */                                                     \
        assert(sizeof(size_t) * CHAR_BIT >= bits);                              \
        assert(bits > 0);                                                       \
        assert(dim  > 0);                                                       \
                                                                                \
        size_t b, d, dd, mask, bit, temp, aux[dim], max = 1 << (bits-1);        \
                                                                                \
        /* Reverse undo excess work */                                          \
        for (bit = max; bit > 1; bit >>= 1 ) {                                  \
            mask = bit-1;                                                       \
            for (d = 0; d < dim; d++ ) {                                        \
                if (H[d] & bit) { H[0] ^= mask; }                               \
                else {                                                          \
                    temp  = (H[0]^H[d]) & mask;                                 \
                    H[0] ^= temp;                                               \
                    H[d] ^= temp;                                               \
                }                                                               \
            }                                                                   \
        }                                                                       \
                                                                                \
        /* Gray encode */                                                       \
        for (d = 1; d < dim; d++) { H[d] ^= H[d-1]; }                           \
        temp = 0;                                                               \
        for (bit = max; bit > 1; bit >>= 1) {                                   \
            if (H[dim-1] & bit) { temp ^= bit-1; }                              \
        }                                                                       \
        for (d = 0; d < dim; d++) { H[d] ^= temp; }                             \
                                                                                \
        /* Compute the H-index from its tranposed representation */             \
        for (d = 0; d < dim; d++) { aux[d] = 0; }                               \
        bit  = 1;                                                               \
        mask = 1;                                                               \
        dd   = 0;                                                               \
        for (b = 0; b < bits; b++) {                                            \
            for (d = dim; d-->0; ) {                                            \
                if (H[d] & mask) { aux[dd] += bit; }                            \
                bit <<= 1;                                                      \
            }                                                                   \
            mask <<= 1;                                                         \
            if (!mask) { mask = 1; dd++; }                                      \
        }                                                                       \
        for (d = 0; d < dim; d++) { H[d] = aux[d]; }                            \
    }                                                                           \
                                                                                \

  /** ********************************************************************* **/
  /**                                                                       **/
  /** ### CLM_DISJOINT                                                      **/
  /**                                                                       **/
  /** A disjoint-sets (union-find) data structure implemented as a `size_t` **/
  /** array of indices that represents a rooted forest (each element points **/
  /** to its parent, roots point to themselves).                            **/
  /**                                                                       **/
  /** Merging and root-finding trigger path compressions but the algorithm  **/
  /** does not keep track of sizes, heights or ranks and always merges by   **/
  /** pointing the root with the larger index to the root with the smallest **/
  /** index. This merging strategy is fast enough for pretty much all known **/
  /** applications and requires half of the space.                          **/
  /**                                                                       **/
  /** Path compressions are performed using a double leaf-to-root pass. The **/
  /** first pass is used to find the root of the set and the second one is  **/
  /** used to make all the elements in the path point directly to the root. **/
  /**                                                                       **/
  #define IMPORT_CLM_DISJOINT(prefix)                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### disjoint_new                                                   **/ \
    /**                                                                     **/ \
    /** Allocates `max_size` disjoint sets in a `size_t` array.             **/ \
    /**                                                                     **/ \
    /** **Warning:** Parameter `max_size` must satisfy `max_size > 0`.      **/ \
    /**                                                                     **/ \
    /** **Warning:** It might return `NULL` if there is not enough memory.  **/ \
    /**                                                                     **/ \
    /** **Example:** Allocate `N` disjoint sets with:                       **/ \
    /**                                                                     **/ \
    /**     size_t *sets = disjoint_new(N);                                 **/ \
    /**     do_something(sets);                                             **/ \
    /**     free(sets);                                                     **/ \
    /**                                                                     **/ \
    /** **Example:** Determine the number of disjoint sets with:            **/ \
    /**                                                                     **/ \
    /**     size_t i, num_sets = 0;                                         **/ \
    /**     for (i = 0; i < N; i++) { if (sets[i] == i) { num_sets++; } }   **/ \
    /**                                                                     **/ \
    static inline size_t *prefix##disjoint_new(const size_t max_size) {         \
                                                                                \
        /* Preconditions */                                                     \
        assert(max_size > 0);                                                   \
                                                                                \
        /* Allocate memory */                                                   \
        size_t *sets = (size_t *) malloc((max_size+1) * sizeof(size_t));        \
                                                                                \
        /* Initialize memory */                                                 \
        if (sets) { for (size_t i = 0; i < max_size; i++) { sets[i] = i; } }    \
        else { fprintf(stderr, "ERROR: Unable to allocate disjoint-sets.\n"); } \
                                                                                \
        /* Return the new disjoint-sets */                                      \
        return sets;                                                            \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### disjoint_root                                                  **/ \
    /**                                                                     **/ \
    /** Returns the root of the set that contains the element `i`.          **/ \
    /**                                                                     **/ \
    /** **Warning:** User must ensure that `i < max_size`.                  **/ \
    /**                                                                     **/ \
    /** **Example:** Determine if `i` and `j` belong to the same set with:  **/ \
    /**                                                                     **/ \
    /**     if (disjoint_root(sets, i) == disjoint_root(sets, j)) {         **/ \
    /**         printf("%zu and %zu belong to the same set!\n", i, j);      **/ \
    /**     } else {                                                        **/ \
    /**         printf("%zu and %zu belong to different sets!\n", i, j);    **/ \
    /**     }                                                               **/ \
    /**                                                                     **/ \
    static inline size_t prefix##disjoint_root(size_t *sets, size_t i) {        \
                                                                                \
        /* Find root */                                                         \
        size_t Ri = i;                                                          \
        while (Ri != sets[Ri]) { Ri = sets[Ri]; }                               \
                                                                                \
        /* Path compression */                                                  \
        size_t temp;                                                            \
        while (i != Ri) { temp = sets[i]; sets[i] = Ri; i = temp; }             \
                                                                                \
        /* Return the root of this component */                                 \
        return Ri;                                                              \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### disjoint_merge                                                 **/ \
    /**                                                                     **/ \
    /** Merges the sets that contain the elements `i` and `j`.              **/ \
    /**                                                                     **/ \
    /** Returns `0` if `i` and `j` belonged to the same set before calling  **/ \
    /** this function and `1` otherwise (so you can easily keep track of    **/ \
    /** the current number of sets).                                        **/ \
    /**                                                                     **/ \
    /** **Warning:** User must ensure that `i < max_size && j < max_size`.  **/ \
    /**                                                                     **/ \
    /** **Example:** Make `K` random merges with:                           **/ \
    /**                                                                     **/ \
    /**     size_t *sets = disjoint_new(N);                                 **/ \
    /**     size_t i, j, num_sets = N;                                      **/ \
    /**     while (num_sets > N-K) {                                        **/ \
    /**         i = rand_size_t(N);                                         **/ \
    /**         j = rand_size_t(N);                                         **/ \
    /**         num_sets -= disjoint_merge(sets, i, j);                     **/ \
    /**     }                                                               **/ \
    /**                                                                     **/ \
    static inline size_t prefix##disjoint_merge(size_t *sets, size_t i,         \
                                                              size_t j) {       \
        /* Find roots */                                                        \
        size_t Ri = i;                                                          \
        size_t Rj = j;                                                          \
        while (Ri != sets[Ri]) { Ri = sets[Ri]; }                               \
        while (Rj != sets[Rj]) { Rj = sets[Rj]; }                               \
                                                                                \
        /* Merge */                                                             \
        size_t merges = 1;                                                      \
        if      (Ri == Rj) { merges   = 0;           }                          \
        else if (Ri <  Rj) { sets[Rj] = Ri; Rj = Ri; }                          \
        else               { sets[Ri] = Rj; Ri = Rj; }                          \
                                                                                \
        /* Path compression */                                                  \
        size_t temp;                                                            \
        while (i != Ri) { temp = sets[i]; sets[i] = Ri; i = temp; }             \
        while (j != Rj) { temp = sets[j]; sets[j] = Ri; j = temp; }             \
                                                                                \
        /* Return the number of merges */                                       \
        return merges;                                                          \
    }                                                                           \
                                                                                \

  /** ********************************************************************* **/
  /**                                                                       **/
  /** ### CLM_ARRAY                                                         **/
  /**                                                                       **/
  /** A set of functions to work with arrays.                               **/
  /**                                                                       **/
  #define IMPORT_CLM_ARRAY(type, less, prefix)                                  \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### array                                                          **/ \
    /**                                                                     **/ \
    /** Definition of the `array` data type.                                **/ \
    /**                                                                     **/ \
    typedef type *prefix##array;                                                \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### array_new                                                      **/ \
    /**                                                                     **/ \
    /** Allocates an `array` of the given `length`.                         **/ \
    /**                                                                     **/ \
    /** **Warning:** Parameter `length` must satisfy `length > 0`.          **/ \
    /**                                                                     **/ \
    /** **Warning:** It might return `NULL` if there is not enough memory.  **/ \
    /**                                                                     **/ \
    /** **Example:** Allocate an `array` of length `N` with:                **/ \
    /**                                                                     **/ \
    /**     array A = array_new(N);                                         **/ \
    /**     do_something(A);                                                **/ \
    /**     free(A);                                                        **/ \
    /**                                                                     **/ \
    static inline prefix##array prefix##array_new(const size_t length) {        \
                                                                                \
        /* Preconditions */                                                     \
        assert(length > 0);                                                     \
                                                                                \
        /* Allocate memory */                                                   \
        prefix##array A = (prefix##array) malloc(length * sizeof(type));        \
        if (A == NULL) {                                                        \
            fprintf(stderr, "ERROR: Unable to allocate array.\n");              \
        }                                                                       \
                                                                                \
        /* Return the new array */                                              \
        return A;                                                               \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### array_sort                                                     **/ \
    /**                                                                     **/ \
    /** Sorts the first `length` elements of the array `A` in-place using   **/ \
    /** shellsort with a growing factor of 2.25.                            **/ \
    /**                                                                     **/ \
    /** **Warning:** The parameter `A` must satisfy: `A != NULL`.           **/ \
    /**                                                                     **/ \
    /** **Warning:** This sorting algorithm is NOT stable.                  **/ \
    /**                                                                     **/ \
    /** **Example:** Sort the first `N` elements of `MyArray` with:         **/ \
    /**                                                                     **/ \
    /**     array_sort(MyArray, N);                                         **/ \
    /**                                                                     **/ \
    /** **Example:** Sort the `K` smallest elements of `MyArray` with:      **/ \
    /**                                                                     **/ \
    /**     array_select(MyArray, N, K);                                    **/ \
    /**     array_sort(MyArray, K-1);                                       **/ \
    /**                                                                     **/ \
    /** **Example:** Sort the `K` biggest elements of `MyArray` with:       **/ \
    /**                                                                     **/ \
    /**     array_select(MyArray, N, N-K-1)                                 **/ \
    /**     array_sort(MyArray+N-K, N-K);                                   **/ \
    /**                                                                     **/ \
    static inline void prefix##array_sort(const prefix##array A,                \
                                          const size_t length) {                \
                                                                                \
        /* Preconditions */                                                     \
        assert(A != NULL);                                                      \
                                                                                \
        size_t i, j, gap;                                                       \
        type   temp;                                                            \
                                                                                \
        /* Shellsort(2.25) */                                                   \
        for (gap = 3; gap <= length/9; gap = gap*9/4 + 1);                      \
                                                                                \
        for (gap = gap*4/9; gap; gap = gap*4/9) {                               \
            for (i = gap; i < length; ++i) {                                    \
                temp = A[i];                                                    \
                for (j = i; gap <= j && less(temp, A[j-gap]); j -= gap) {       \
                    A[j] = A[j-gap];                                            \
                }                                                               \
                A[j] = temp;                                                    \
            }                                                                   \
        }                                                                       \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### array_shuffle                                                  **/ \
    /**                                                                     **/ \
    /** Shuffles the first `length` elements of the array `A` in-place      **/ \
    /** in `O(length)` time.                                                **/ \
    /**                                                                     **/ \
    /** **Warning:** The parameter `A` must satisfy: `A != NULL`.           **/ \
    /**                                                                     **/ \
    /** **Example:** Shuffle the first `N` elements of `MyArray` with:      **/ \
    /**                                                                     **/ \
    /**     array_shuffle(MyArray, N);                                      **/ \
    /**                                                                     **/ \
    static inline void prefix##array_shuffle(const prefix##array A,             \
                                             const size_t length) {             \
                                                                                \
        /* Preconditions */                                                     \
        assert(A != NULL);                                                      \
        assert(RAND_MAX >= length);                                             \
                                                                                \
        size_t i, j, range;                                                     \
        type   temp;                                                            \
                                                                                \
        /* Inside-Out Fisher-Yates Shuffle */                                   \
        for (i = 1; i < length; ++i) {                                          \
                                                                                \
            /* Get an unbiased random index in the interval [0, i] */           \
            range = RAND_MAX - (RAND_MAX % (i+1));                              \
            do { j = rand(); } while (j >= range);                              \
            j = j % (i+1);                                                      \
                                                                                \
            /* Swap A[i] and A[j]: */                                           \
            temp = A[i]; A[i] = A[j]; A[j] = temp;                              \
        }                                                                       \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### array_select                                                   **/ \
    /**                                                                     **/ \
    /** Uses Quickselect to find and return the `rank`-th element of an     **/ \
    /** `array` of size `length` in `O(length)` expected time.              **/ \
    /**                                                                     **/ \
    /** The algorithm is in-place, i.e. the original order of the `array`   **/ \
    /** can be disturbed during this operation.                             **/ \
    /**                                                                     **/ \
    /** In particular, the `k`-th element of the array will be in its       **/ \
    /** correct place after doing `array_select(A, N, k)`.                  **/ \
    /**                                                                     **/ \
    /** Moreover, `A[0:k-1]` will contain the `k-1` elements of `A` that    **/ \
    /** are smaller or equal than `A[k]` and `A[k+1:length-1]` will contain **/ \
    /** the `length-k` elements of `A` that are bigger than `A[k]`.         **/ \
    /**                                                                     **/ \
    /** **Warning:** The parameter `A` must satisfy: `A != NULL`.           **/ \
    /**                                                                     **/ \
    /** **Warning:** The parameters must satisfy: `rank < length`.          **/ \
    /**                                                                     **/ \
    /** **Example:** Find the median of an unsorted array of doubles with:  **/ \
    /**                                                                     **/ \
    /**     double median = array_select(MyArray, N, N/2);                  **/ \
    /**                                                                     **/ \
    /** **Example:** Sort the `K` smallest elements of `MyArray` with:      **/ \
    /**                                                                     **/ \
    /**     array_select(MyArray, N, K);                                    **/ \
    /**     array_sort(MyArray, K-1);                                       **/ \
    /**                                                                     **/ \
    /** **Example:** Sort the `K` biggest elements of `MyArray` with:       **/ \
    /**                                                                     **/ \
    /**     array_select(MyArray, N, N-K-1)                                 **/ \
    /**     array_sort(MyArray+N-K, N-K);                                   **/ \
    /**                                                                     **/ \
    static inline type prefix##array_select(const prefix##array A,              \
                                            const size_t length,                \
                                            const size_t rank) {                \
        /* Preconditions */                                                     \
        assert(A != NULL);                                                      \
        assert(rank < length);                                                  \
                                                                                \
        size_t l, left  = 0;                                                    \
        size_t r, right = length-1;                                             \
        type   pivot;                                                           \
        type   t;                                                               \
                                                                                \
        /* Apply Quickselect in place */                                        \
        do {pivot = A[rank];                                                    \
            l     = left;                                                       \
            r     = right;                                                      \
            do {while (less(A[l], pivot)) { ++l; }                              \
                while (less(pivot, A[r])) { --r; }                              \
                if  (l <= r) { t = A[l]; A[l] = A[r]; A[r] = t; ++l; --r; }     \
            } while (l <= r);                                                   \
            if (r < rank) { left  = l; }                                        \
            if (rank < l) { right = r; }                                        \
        } while (left < right);                                                 \
                                                                                \
        /* Return the requested element */                                      \
        return A[rank];                                                         \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### array_bisect                                                   **/ \
    /**                                                                     **/ \
    /** Returns the rightmost insertion point for `data` in the sorted      **/ \
    /** array `A` in `O(log(length))` time using binary search.             **/ \
    /**                                                                     **/ \
    /** In particular:                                                      **/ \
    /**                                                                     **/ \
    /** * `data >= A[i]`  in the interval `[0, array_bisect(A, N, data))`   **/ \
    /** * `data <  A[i]`  in the interval `[array_bisect(A, N, data), N)`   **/ \
    /**                                                                     **/ \
    /** **Warning:** The parameter `A` must satisfy: `A != NULL`.           **/ \
    /**                                                                     **/ \
    /** **Warning:** If `A` is not sorted, the behavior is undefined.       **/ \
    /**                                                                     **/ \
    /** **Example:** Find `MyData` in `MyArray` with:                       **/ \
    /**                                                                     **/ \
    /**     size_t i = array_bisect(MyArray, N, MyData);                    **/ \
    /**     if (i > 0 && MyArray[i-1] == MyData) { printf("Found");     }   **/ \
    /**     else                                 { printf("Not found"); }   **/ \
    /**                                                                     **/ \
    /** **Example:** Insertion-sort `MyArray` with:                         **/ \
    /**                                                                     **/ \
    /**     for (size_t i = 1; i < length; ++i) {                           **/ \
    /**          type   t = MyArray[i];                                     **/ \
    /**          size_t j = array_bisect(MyArray, N, t);                    **/ \
    /**          memmove(A+j+1, A+j, (i-j)*sizeof(type));                   **/ \
    /**          A[j] = t;                                                  **/ \
    /**     }                                                               **/ \
    /**                                                                     **/ \
    static inline size_t prefix##array_bisect(const prefix##array A,            \
                                              const size_t length,              \
                                              const type data) {                \
        /* Preconditions */                                                     \
        assert(A != NULL);                                                      \
                                                                                \
        size_t left  = 0;                                                       \
        size_t right = length;                                                  \
        size_t pivot = length >> 1;                                             \
                                                                                \
        while (left < right) {                                                  \
            if (less(data, A[pivot])) { right = pivot;   }                      \
            else                      { left  = pivot+1; }                      \
            pivot = left + ((right-left) >> 1);                                 \
        }                                                                       \
                                                                                \
        return pivot;                                                           \
    }                                                                           \
                                                                                \

  /** ********************************************************************* **/
  /**                                                                       **/
  /** ### CLM_CLIST                                                         **/
  /**                                                                       **/
  /** A set of data types and functions related to the `clist` container.   **/
  /**                                                                       **/
  /** The `clist` container is implemented as a circular singly-linked list **/
  /** of dinamically allocated nodes.                                       **/
  /**                                                                       **/
  /** The `clist` container can be used to implement either a stack or a    **/
  /** queue but is unable to perform the `pop_back` operation efficiently   **/
  /** so it is not a fully operational deque.                               **/
  /**                                                                       **/
  #define IMPORT_CLM_CLIST(type, prefix)                                        \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### clist                                                          **/ \
    /**                                                                     **/ \
    /** Definition of the basic `clist` container data type.                **/ \
    /**                                                                     **/ \
    /** **Warning:** An empty `clist` is just a `NULL` pointer.             **/ \
    /**                                                                     **/ \
    /** **Example:** Initialize an empty `clist` with:                      **/ \
    /**                                                                     **/ \
    /**     clist MyList = NULL;                                            **/ \
    /**                                                                     **/ \
    /** **Example:** Test a `MyList` for non-emptyness with:                **/ \
    /**                                                                     **/ \
    /**     if (MyList) { printf("MyList is not empty"); }                  **/ \
    /**     else        { printf("MyList is empty");     }                  **/ \
    /**                                                                     **/ \
    /** **Example:** Compute the length of `MyList` with:                   **/ \
    /**                                                                     **/ \
    /**     size_t size = 0;                                                **/ \
    /**     if (MyList) {                                                   **/ \
    /**         clist itr = MyList;                                         **/ \
    /**         do { itr = itr->next; size++; } while (itr != MyList);      **/ \
    /**     }                                                               **/ \
    /**                                                                     **/ \
    /** **Example:** Iterate over all the elements of `MyList` with:        **/ \
    /**                                                                     **/ \
    /**     if (MyList) {                                                   **/ \
    /**         clist itr = MyList;                                         **/ \
    /**         do {itr = itr->next;                                        **/ \
    /**             do_something(itr->data);                                **/ \
    /**         } while (itr != MyList);                                    **/ \
    /**     }                                                               **/ \
    /**                                                                     **/ \
    typedef struct prefix##clist_s {                                            \
        struct prefix##clist_s *next;                                           \
        type            data;                                                   \
    } prefix##clist_s, *prefix##clist;                                          \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### clist_push_front                                               **/ \
    /**                                                                     **/ \
    /** Adds an elemenet at the beginning of `list` in `O(1)` time.         **/ \
    /**                                                                     **/ \
    /** **Warning:** Returns `true` if successful, and `false` otherwise.   **/ \
    /**                                                                     **/ \
    /** **Example:** Add data to the beginning of `MyList` with:            **/ \
    /**                                                                     **/ \
    /**     bool success = clist_push_front(&MyList, data);                 **/ \
    /**     if (success) { assert(clist_front(&MyList) == data); }          **/ \
    /**                                                                     **/ \
    static inline bool prefix##clist_push_front(prefix##clist *list,            \
                                                const type data) {              \
                                                                                \
        prefix##clist node = (prefix##clist) malloc(sizeof(prefix##clist_s));   \
                                                                                \
        if (node) {                                                             \
                                                                                \
            if (*list) { node->next = (*list)->next; (*list)->next = node; }    \
            else       { node->next = node; *list = node;                  }    \
            node->data = data;                                                  \
            return true;                                                        \
                                                                                \
        } else {                                                                \
                                                                                \
            fprintf(stderr, "ERROR: Unable to push_front data into clist\n");   \
            return false;                                                       \
                                                                                \
        }                                                                       \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### clist_push_back                                                **/ \
    /**                                                                     **/ \
    /** Adds an elemenet at the end of `list` in `O(1)` time.               **/ \
    /**                                                                     **/ \
    /** **Warning:** Returns `true` if successful, and `false` otherwise.   **/ \
    /**                                                                     **/ \
    /** **Example:** Add data to the end of `MyList` with:                  **/ \
    /**                                                                     **/ \
    /**     bool success = clist_push_back(&MyList, data);                  **/ \
    /**     if (success) { assert(clist_back(&MyList) == data); }           **/ \
    /**                                                                     **/ \
    static inline bool prefix##clist_push_back(prefix##clist *list,             \
                                               const type data) {               \
                                                                                \
        prefix##clist node = (prefix##clist) malloc(sizeof(prefix##clist_s));   \
                                                                                \
        if (node) {                                                             \
                                                                                \
            if (*list) { node->next = (*list)->next; (*list)->next = node; }    \
            else       { node->next = node;                                }    \
            node->data = data;                                                  \
            *list      = node;                                                  \
            return true;                                                        \
                                                                                \
        } else {                                                                \
                                                                                \
            fprintf(stderr, "ERROR: Unable to push_back data into clist\n");    \
            return false;                                                       \
                                                                                \
        }                                                                       \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### clist_pop_front                                                **/ \
    /**                                                                     **/ \
    /** Removes and returns the first element of `list` in `O(1)` time.     **/ \
    /**                                                                     **/ \
    /** **Warning:** Although you can add elements to either end of the     **/ \
    /** list they will always exit the list from the beginning.             **/ \
    /**                                                                     **/ \
    /** The combination of `push_front` & `pop_front` behaves as a LIFO     **/ \
    /** stack whereas `push_back` & `pop_front` behaves as a FIFO queue.    **/ \
    /**                                                                     **/ \
    /** **Warning:** The parameter `list` must satisfy `*list != NULL`.     **/ \
    /**                                                                     **/ \
    /** **Example:** Empty `MyList` with:                                   **/ \
    /**                                                                     **/ \
    /**     while (MyList) { free(clist_pop_front(&MyList)); }              **/ \
    /**                                                                     **/ \
    static inline type prefix##clist_pop_front(prefix##clist *list) {           \
                                                                                \
        /* Precondition */                                                      \
        assert(*list != NULL);                                                  \
                                                                                \
        prefix##clist node = (*list)->next;                                     \
        type          data = node->data;                                        \
        if (node == *list) { *list = NULL; }                                    \
        else { (*list)->next = node->next; }                                    \
        free(node);                                                             \
        return data;                                                            \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### clist_front                                                    **/ \
    /**                                                                     **/ \
    /** Returns the first element of a non-empty list in `O(1)` time.       **/ \
    /**                                                                     **/ \
    /** **Warning:** The parameter `list` must satisfy `*list != NULL`.     **/ \
    /**                                                                     **/ \
    /** **Example:** Retrieve the next element to exit `MyList` with:       **/ \
    /**                                                                     **/ \
    /**     type next = clist_front(&MyList);                               **/ \
    /**                                                                     **/ \
    static inline type prefix##clist_front(prefix##clist *list) {               \
                                                                                \
        /* Sanity Check */                                                      \
        assert((*list) != NULL);                                                \
                                                                                \
        return (*list)->next->data;                                             \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### clist_back                                                     **/ \
    /**                                                                     **/ \
    /** Returns the last element of a non-empty list in `O(1)` time.        **/ \
    /**                                                                     **/ \
    /** **Warning:** The parameter `list` must satisfy `*list != NULL`.     **/ \
    /**                                                                     **/ \
    /** **Example:** Retrieve the last element to exit `MyList` with:       **/ \
    /**                                                                     **/ \
    /**     type last = clist_back(&MyList);                                **/ \
    /**                                                                     **/ \
    static inline type prefix##clist_back(prefix##clist *list) {                \
                                                                                \
        /* Sanity Check */                                                      \
        assert((*list) != NULL);                                                \
                                                                                \
        return (*list)->data;                                                   \
    }                                                                           \
                                                                                \

  /** ********************************************************************* **/
  /**                                                                       **/
  /** ### CLM_STREE                                                         **/
  /**                                                                       **/
  /** A set of data types and functions related to the `stree` container.   **/
  /**                                                                       **/
  /** The `stree` container is implemented as a splay tree of dinamically   **/
  /** allocated nodes with top-down simple-splaying updates.                **/
  /**                                                                       **/
  /** Splay trees were defined in the paper "Self-Adjusting Binary Search   **/
  /** Trees" by Daniel D. Sleator & Robert E. Tarjan published in 1985 in   **/
  /** the Journal of the ACM 32 (3): 652–686. doi:10.1145/3828.3835         **/
  /**                                                                       **/
  /** Splay trees are quite different from other binary search trees so,    **/
  /** it is advisable to learn about them at Wikipedia or other sources     **/
  /** before using them.                                                    **/
  /**                                                                       **/
  /** All the stree operations (except `stree_root` that always takes       **/
  /** `O(1)` time) are efficient in an amortized sense. This means that a   **/
  /** sequence of N of these operations is guaranteed to take `O(N*log(N))` **/
  /** time to complete, with some of them requiring as few as `O(1)`        **/
  /** operations and some of them taking `O(N)` time to complete depending  **/
  /** on the particular sequence of operations and the particular values    **/
  /** inserted/searched/removed from the `stree`.                           **/
  /**                                                                       **/
  /** In practice, Splay trees are a little bit slower than the equivalent  **/
  /** AVL tree, Red-Black tree or Weight-Balanced tree implementation but   **/
  /** use less memory and show an adaptive behavior that might benefit the  **/
  /** user in many common applications (e.g. inserting N sorted elements    **/
  /** takes just `O(N)` time rather than `O(N*log(N))` time).               **/
  /**                                                                       **/
  /** Incidentaly, Splay Trees also solve the "failed queries" problem of   **/
  /** type-safe search trees (i.e. what to return when a `find` or `delete` **/
  /** query fails) in a very natural way:                                   **/
  /**                                                                       **/
  /** * The usual `find` operation is broken in two steps: first ask if     **/
  /**   `data` is in the `stree` with a `stree_find` operation and then     **/
  /**   recover it with a `stree_root` operation. Since `stree_find` puts   **/
  /**   `data` in the `root` of the `stree` the second operation only takes **/
  /**   `O(1)` and no time is wasted to gain safety.                        **/
  /** * The `next` and `prev` operations are also broken in two steps:      **/
  /**   first move the next/prev element to the `root` and then retrieve it **/
  /**   with a `stree_root` operation. Again, since we are moving the       **/
  /**   elements to the `root` it just takes `O(1)` time to retrieve them.  **/
  /** * All other data-retrieving operations (`pop`, `min` & `max`) also    **/
  /**   end up working with the `root` node of the `stree` and will not     **/
  /**   fail unless the `stree` is empty, which is a condition that can be  **/
  /**   checked easily in `O(1)` time with a `tree != NULL` test.           **/
  /**                                                                       **/
  #define IMPORT_CLM_STREE(type, less, prefix)                                  \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### stree                                                          **/ \
    /**                                                                     **/ \
    /** Definition of the basic splay tree container type `stree`.          **/ \
    /**                                                                     **/ \
    /** **Warning:** An empty `stree` is just a `NULL` pointer.             **/ \
    /**                                                                     **/ \
    /** **Example:** Initialize an empty `stree` with:                      **/ \
    /**                                                                     **/ \
    /**     stree MyTree = NULL;                                            **/ \
    /**                                                                     **/ \
    /** **Example:** Test for non-emptyness of `MyTree` with:               **/ \
    /**                                                                     **/ \
    /**     if (MyTree) { printf("MyTree is not empty"); }                  **/ \
    /**     else        { printf("MyTree is empty");     }                  **/ \
    /**                                                                     **/ \
    typedef struct prefix##stree_s {                                            \
        struct prefix##stree_s *left;                                           \
        struct prefix##stree_s *right;                                          \
        type            data;                                                   \
    } prefix##stree_s, *prefix##stree;                                          \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### stree_root                                                     **/ \
    /**                                                                     **/ \
    /** Returns the element stored at the current root node of `tree` in    **/ \
    /** O(1) time.                                                          **/ \
    /**                                                                     **/ \
    /** **Warning:** The parameter `tree` must satisfy `*tree != NULL`.     **/ \
    /**                                                                     **/ \
    /** **Example:** Retrieve the current root element of `MyTree` with:    **/ \
    /**                                                                     **/ \
    /**     if (MyTree) { root = stree_root(&MyTree); }                     **/ \
    /**                                                                     **/ \
    static inline type prefix##stree_root(prefix##stree *tree) {                \
                                                                                \
        /* Precondition */                                                      \
        assert(*tree != NULL);                                                  \
                                                                                \
        return (*tree)->data;                                                   \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### stree_min                                                      **/ \
    /**                                                                     **/ \
    /** Moves the smallest element to the root of `tree` and returns it.    **/ \
    /**                                                                     **/ \
    /** **Warning:** The parameter `tree` must satisfy `*tree != NULL`.     **/ \
    /**                                                                     **/ \
    /** **Example:** Find the smallest element of `MyTree` with:            **/ \
    /**                                                                     **/ \
    /**     if (MyTree) { smallest = stree_min(&MyTree); }                  **/ \
    /**                                                                     **/ \
    static inline type prefix##stree_min(prefix##stree *tree) {                 \
                                                                                \
        /* Precondition */                                                      \
        assert(*tree != NULL);                                                  \
                                                                                \
        prefix##stree_s dummy, *right, *temp, *root = *tree;                    \
                                                                                \
        /* Top Down Splay-Min */                                                \
        dummy.left = NULL;                                                      \
        right      = &dummy;                                                    \
        for (;;) {                                                              \
                                                                                \
            /* Rotate Right */                                                  \
            if (root->left == NULL) { break; }                                  \
            temp        = root->left;                                           \
            root->left  = temp->right;                                          \
            temp->right = root;                                                 \
            root        = temp;                                                 \
                                                                                \
            /* Link Right */                                                    \
            if (root->left == NULL) { break; }                                  \
            right->left = root;                                                 \
            right       = root;                                                 \
            root        = root->left;                                           \
        }                                                                       \
                                                                                \
        /* Final assemble & return */                                           \
        right->left = root->right;                                              \
        root->right = dummy.left;                                               \
        *tree       = root;                                                     \
        return root->data;                                                      \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### stree_max                                                      **/ \
    /**                                                                     **/ \
    /** Moves the biggest element to the root of `tree` and returns it.     **/ \
    /**                                                                     **/ \
    /** **Warning:** The parameter `tree` must satisfy `*tree != NULL`.     **/ \
    /**                                                                     **/ \
    /** **Example:** Find the biggest element of `MyTree` with:             **/ \
    /**                                                                     **/ \
    /**     if (MyTree) { biggest = stree_max(&MyTree); }                   **/ \
    /**                                                                     **/ \
    static inline type prefix##stree_max(prefix##stree *tree) {                 \
                                                                                \
        /* Precondition */                                                      \
        assert(*tree != NULL);                                                  \
                                                                                \
        prefix##stree_s dummy, *left, *temp, *root = *tree;                     \
                                                                                \
        /* Top Down Splay-Max */                                                \
        dummy.right = NULL;                                                     \
        left        = &dummy;                                                   \
        for (;;) {                                                              \
                                                                                \
            /* Rotate Left */                                                   \
            if (root->right == NULL) { break; }                                 \
            temp        = root->right;                                          \
            root->right = temp->left;                                           \
            temp->left  = root;                                                 \
            root        = temp;                                                 \
                                                                                \
            /* Link Left */                                                     \
            if (root->right == NULL) { break; }                                 \
            left->right = root;                                                 \
            left        = root;                                                 \
            root        = root->right;                                          \
        }                                                                       \
                                                                                \
        /* Final assemble & return */                                           \
        left->right = root->left;                                               \
        root->left  = dummy.right;                                              \
        *tree       = root;                                                     \
        return root->data;                                                      \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### stree_pop                                                      **/ \
    /**                                                                     **/ \
    /** Removes the current root node from `tree` and returns its content.  **/ \
    /**                                                                     **/ \
    /** It guarantees that, if the current root-node element is either the  **/ \
    /** biggest or the smallest in the `tree`, then, after performing this  **/ \
    /** operation, the root node element will still be the biggest or the   **/ \
    /** smallest element in the resulting `tree` (respectively).            **/ \
    /**                                                                     **/ \
    /** **Warning:** The parameter `tree` must satisfy `*tree != NULL`.     **/ \
    /**                                                                     **/ \
    /** **Example:** Remove `data` from `MyTree` (if present) with:         **/ \
    /**                                                                     **/ \
    /**     if (stree_find(&MyTree, data)) {                                **/ \
    /**         free(stree_pop(&MyTree));                                   **/ \
    /**     }                                                               **/ \
    /**                                                                     **/ \
    /** **Example:** Remove all elements from `MyTree` with:                **/ \
    /**                                                                     **/ \
    /**     while (MyTree) { free(stree_pop(&MyTree)); }                    **/ \
    /**                                                                     **/ \
    /** **Example:** Consume `MyTree` forwards with:                        **/ \
    /**                                                                     **/ \
    /**     if (MyTree) {                                                   **/ \
    /**         stree_min(&MyTree);                                         **/ \
    /**         while (MyTree) {                                            **/ \
    /**             do_something(stree_pop(&MyTree));                       **/ \
    /**         }                                                           **/ \
    /**     }                                                               **/ \
    /**                                                                     **/ \
    /** **Example:** Consume `MyTree` backwards with:                       **/ \
    /**                                                                     **/ \
    /**     if (MyTree) {                                                   **/ \
    /**         stree_max(&MyTree);                                         **/ \
    /**         while (MyTree) {                                            **/ \
    /**             do_something(stree_pop(&MyTree));                       **/ \
    /**         }                                                           **/ \
    /**     }                                                               **/ \
    /**                                                                     **/ \
    static inline type prefix##stree_pop(prefix##stree *tree) {                 \
                                                                                \
        /* Precondition */                                                      \
        assert(*tree != NULL);                                                  \
                                                                                \
        prefix##stree_s dummy, *left, *right, *temp, *root, *old_root = *tree;  \
        type            data;                                                   \
                                                                                \
        /* Store data */                                                        \
        data = old_root->data;                                                  \
                                                                                \
        /* Particular case */                                                   \
        if (old_root->right == NULL && old_root->left == NULL) {                \
           *tree = NULL;                                                        \
            free(old_root);                                                     \
            return data;                                                        \
        }                                                                       \
                                                                                \
        /* General Case */                                                      \
        if (old_root->right == NULL) {                                          \
                                                                                \
            /* Top-down simple splay-max the old_root->left; */                 \
            root        = old_root->left;                                       \
            dummy.right = NULL;                                                 \
            left        = &dummy;                                               \
            for (;;) {                                                          \
                                                                                \
                /* Rotate Left */                                               \
                if (root->right == NULL) { break; }                             \
                temp        = root->right;                                      \
                root->right = temp->left;                                       \
                temp->left  = root;                                             \
                root        = temp;                                             \
                                                                                \
                /* Link Left */                                                 \
                if (root->right == NULL) { break; }                             \
                left->right = root;                                             \
                left        = root;                                             \
                root        = root->right;                                      \
            }                                                                   \
                                                                                \
            /* Final assemble */                                                \
            left->right = root->left;                                           \
            root->left  = dummy.right;                                          \
                                                                                \
        } else {                                                                \
                                                                                \
            /* Top-down simple splay-min the old_root->right; */                \
            root       = old_root->right;                                       \
            dummy.left = NULL;                                                  \
            right      = &dummy;                                                \
            for (;;) {                                                          \
                                                                                \
                /* Rotate Right */                                              \
                if (root->left == NULL) { break; }                              \
                temp        = root->left;                                       \
                root->left  = temp->right;                                      \
                temp->right = root;                                             \
                root        = temp;                                             \
                                                                                \
                /* Link Right */                                                \
                if (root->left == NULL) { break; }                              \
                right->left = root;                                             \
                right       = root;                                             \
                root        = root->left;                                       \
            }                                                                   \
                                                                                \
            /* Final assemble */                                                \
            right->left = root->right;                                          \
            root->right = dummy.left;                                           \
            root->left  = old_root->left;                                       \
        }                                                                       \
                                                                                \
        /* Store the new root, free the old root and return its content. */     \
        *tree = root;                                                           \
        free(old_root);                                                         \
        return data;                                                            \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### stree_next                                                     **/ \
    /**                                                                     **/ \
    /** If `tree` is empty or the current root is the biggest element it    **/ \
    /** just returs `false`. Otherwise, it moves to the root the smallest   **/ \
    /** element that is bigger than the current root and returns `true`.    **/ \
    /**                                                                     **/ \
    /** **Example:** Iterate forwards over the elements of `MyTree` with:   **/ \
    /**                                                                     **/ \
    /**     if (MyTree) {                                                   **/ \
    /**         do_something(stree_min(&MyTree));                           **/ \
    /**         while (stree_next(&MyTree)) {                               **/ \
    /**             do_something(stree_root(&MyTree));                      **/ \
    /**         }                                                           **/ \
    /**     }                                                               **/ \
    /**                                                                     **/ \
    static inline bool prefix##stree_next(prefix##stree *tree) {                \
                                                                                \
        prefix##stree_s dummy, *right, *temp, *root, *old_root = *tree;         \
                                                                                \
        /* Trivial case 1: Empty tree */                                        \
        if (old_root == NULL) { return false; }                                 \
                                                                                \
        /* Trivial case 2: There is not a bigger element */                     \
        if (old_root->right == NULL) { return false; }                          \
                                                                                \
        /* General case: Top-down simple splay-min of the old_root->right */    \
        root            = old_root->right;                                      \
        old_root->right = NULL;                                                 \
        dummy.left      = NULL;                                                 \
        right           = &dummy;                                               \
        for (;;) {                                                              \
                                                                                \
            /* Rotate Right */                                                  \
            if (root->left == NULL) { break; }                                  \
            temp        = root->left;                                           \
            root->left  = temp->right;                                          \
            temp->right = root;                                                 \
            root        = temp;                                                 \
                                                                                \
            /* Link Right */                                                    \
            if (root->left == NULL) { break; }                                  \
            right->left = root;                                                 \
            right       = root;                                                 \
            root        = root->left;                                           \
        }                                                                       \
                                                                                \
        /* Final assemble & return */                                           \
        right->left = root->right;                                              \
        root->right = dummy.left;                                               \
        root->left  = old_root;                                                 \
        *tree       = root;                                                     \
        return true;                                                            \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### stree_prev                                                     **/ \
    /**                                                                     **/ \
    /** If `tree` is empty or the current root is the smallest element it   **/ \
    /** just returs `false`. Otherwise, it moves to the root the biggest    **/ \
    /** element that is smaller than the current root and returns `true`.   **/ \
    /**                                                                     **/ \
    /** **Example:** Iterate backwards over the elements of `MyTree` with:  **/ \
    /**                                                                     **/ \
    /**     if (MyTree) {                                                   **/ \
    /**         do_something(stree_max(&MyTree));                           **/ \
    /**         while (stree_prev(&MyTree)) {                               **/ \
    /**             do_something(stree_root(&MyTree));                      **/ \
    /**         }                                                           **/ \
    /**     }                                                               **/ \
    /**                                                                     **/ \
    static inline bool prefix##stree_prev(prefix##stree *tree) {                \
                                                                                \
        prefix##stree_s dummy, *left, *temp, *root, *old_root = *tree;          \
                                                                                \
        /* Trivial case 1: Empty tree */                                        \
        if (old_root == NULL) { return false; }                                 \
                                                                                \
        /* Trivial case 2: There is not a smaller element */                    \
        if (old_root->left == NULL) { return false; }                           \
                                                                                \
        /* General case: Top-down splay-max of the root->left */                \
        root           = old_root->left;                                        \
        old_root->left = NULL;                                                  \
        dummy.right    = NULL;                                                  \
        left           = &dummy;                                                \
        for (;;) {                                                              \
                                                                                \
            /* Rotate Left */                                                   \
            if (root->right == NULL) { break; }                                 \
            temp        = root->right;                                          \
            root->right = temp->left;                                           \
            temp->left  = root;                                                 \
            root        = temp;                                                 \
                                                                                \
            /* Link Left */                                                     \
            if (root->right == NULL) { break; }                                 \
            left->right = root;                                                 \
            left        = root;                                                 \
            root        = root->right;                                          \
        }                                                                       \
                                                                                \
        /* Final assemble & return */                                           \
        left->right = root->left;                                               \
        root->left  = dummy.right;                                              \
        root->right = old_root;                                                 \
        *tree       = root;                                                     \
        return true;                                                            \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### stree_find                                                     **/ \
    /**                                                                     **/ \
    /** Looks for `data` in the `tree`. If `data` is in the `tree` it moves **/ \
    /** it to the root node and returns `true`. Otherwise returns `false`.  **/ \
    /**                                                                     **/ \
    /** **Example:** Find whether `data` is in `MyTree` with:               **/ \
    /**                                                                     **/ \
    /**     if (stree_find(&MyTree, data)) {                                **/ \
    /**         printf("data is in MyTree.");                               **/ \
    /**         do_something(stree_root(&MyTree));                          **/ \
    /**     } else {                                                        **/ \
    /**         printf("data is not in MyTree.");                           **/ \
    /**     }                                                               **/ \
    /**                                                                     **/ \
    static inline bool prefix##stree_find(prefix##stree *tree,                  \
                                          const type data) {                    \
                                                                                \
        prefix##stree_s dummy, *left, *right, *temp, *root = *tree;             \
        bool found = false;                                                     \
                                                                                \
        /* Trivial case: Empty tree */                                          \
        if (root == NULL) { return false; }                                     \
                                                                                \
        /* General case */                                                      \
        dummy.left = dummy.right = NULL;                                        \
        left       = right       = &dummy;                                      \
        for (;;) {                                                              \
                                                                                \
            /* Case 1: data < root->data */                                     \
            if (less(data, root->data)) {                                       \
                                                                                \
                /* Rotate Right */                                              \
                if (root->left == NULL) { break; }                              \
                if (less(data, root->left->data)) {                             \
                    temp        = root->left;                                   \
                    root->left  = temp->right;                                  \
                    temp->right = root;                                         \
                    root        = temp;                                         \
                    if (root->left == NULL) { break; }                          \
                }                                                               \
                                                                                \
                /* Link Right */                                                \
                right->left = root;                                             \
                right       = root;                                             \
                root        = root->left;                                       \
            }                                                                   \
                                                                                \
            /* Case 2: data > root->data */                                     \
            else if (less(root->data, data)) {                                  \
                                                                                \
                /* Rotate Left */                                               \
                if (root->right == NULL) { break; }                             \
                if (less(root->right->data, data)) {                            \
                    temp        = root->right;                                  \
                    root->right = temp->left;                                   \
                    temp->left  = root;                                         \
                    root        = temp;                                         \
                    if (root->right == NULL) { break; }                         \
                }                                                               \
                                                                                \
                /* Link Left */                                                 \
                left->right = root;                                             \
                left        = root;                                             \
                root        = root->right;                                      \
            }                                                                   \
                                                                                \
            /* Case 3: data == root->data */                                    \
            else { found = true; break; }                                       \
        }                                                                       \
                                                                                \
        /* Final assemble & return */                                           \
        left->right = root->left;                                               \
        right->left = root->right;                                              \
        root->left  = dummy.right;                                              \
        root->right = dummy.left;                                               \
        *tree       = root;                                                     \
        return found;                                                           \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### stree_insert                                                   **/ \
    /**                                                                     **/ \
    /** Inserts `data` in `tree`.                                           **/ \
    /**                                                                     **/ \
    /** If `tree` already contains `data`, it gets overwritten and the      **/ \
    /** function returns `true`. Otherwise the function insert `data` in    **/ \
    /** `tree` and returns `true` if possible and `false` otherwise.        **/ \
    /**                                                                     **/ \
    /** **Example:** Insert `data` in `MyTree` (without overwriting) with:  **/ \
    /**                                                                     **/ \
    /**     if (stree_find(&MyTree, data)) {                                **/ \
    /**         printf("data was in MyTree already.");                      **/ \
    /**     } else {                                                        **/ \
    /**         stree_insert(&MyTree, data);                                **/ \
    /**     }                                                               **/ \
    /**                                                                     **/ \
    static inline bool prefix##stree_insert(prefix##stree *tree,                \
                                            const type data) {                  \
                                                                                \
        prefix##stree_s dummy, *left, *right, *temp, *new_root, *root = *tree;  \
        bool found = false;                                                     \
                                                                                \
        /* Splay data to the root of the tree */                                \
        if (root != NULL) {                                                     \
            dummy.left = dummy.right = NULL;                                    \
            left       = right       = &dummy;                                  \
            for (;;) {                                                          \
                                                                                \
                /* Case 1: data < root->data */                                 \
                if (less(data, root->data)) {                                   \
                                                                                \
                    /* Rotate Right */                                          \
                    if (root->left == NULL) { break; }                          \
                    if (less(data, root->left->data)) {                         \
                        temp        = root->left;                               \
                        root->left  = temp->right;                              \
                        temp->right = root;                                     \
                        root        = temp;                                     \
                        if (root->left == NULL) { break; }                      \
                    }                                                           \
                                                                                \
                    /* Link Right */                                            \
                    right->left = root;                                         \
                    right       = root;                                         \
                    root        = root->left;                                   \
                }                                                               \
                                                                                \
                /* Case 2: data > root->data */                                 \
                else if (less(root->data, data)) {                              \
                                                                                \
                    /* Rotate Left */                                           \
                    if (root->right == NULL) { break; }                         \
                    if (less(root->right->data, data)) {                        \
                        temp        = root->right;                              \
                        root->right = temp->left;                               \
                        temp->left  = root;                                     \
                        root        = temp;                                     \
                        if (root->right == NULL) { break; }                     \
                    }                                                           \
                                                                                \
                    /* Link Left */                                             \
                    left->right = root;                                         \
                    left        = root;                                         \
                    root        = root->right;                                  \
                }                                                               \
                                                                                \
                /* Case 3: data == root->data */                                \
                else { found = true; break; }                                   \
            }                                                                   \
                                                                                \
            /* Final assemble & return */                                       \
            left->right = root->left;                                           \
            right->left = root->right;                                          \
            root->left  = dummy.right;                                          \
            root->right = dummy.left;                                           \
        }                                                                       \
                                                                                \
        /* Trivial case 1: Overwrite data */                                    \
        if (found) {                                                            \
            root->data = data;                                                  \
            *tree      = root;                                                  \
            return true;                                                        \
        }                                                                       \
                                                                                \
        /* Allocate a new root node */                                          \
        new_root = (prefix##stree) malloc(sizeof(prefix##stree_s));             \
        if (new_root == NULL) {                                                 \
            fprintf(stderr, "ERROR: Unable to insert data into stree\n");       \
            *tree = root;                                                       \
            return false;                                                       \
        }                                                                       \
                                                                                \
        /* Trivial case 2: Empty tree */                                        \
        if (root == NULL) { new_root->left = new_root->right = NULL; }          \
                                                                                \
        /* General case */                                                      \
        else if (less(data, root->data)) {                                      \
            new_root->right = root;                                             \
            new_root->left  = root->left;                                       \
            root->left      = NULL;                                             \
        } else {                                                                \
            new_root->left  = root;                                             \
            new_root->right = root->right;                                      \
            root->right = NULL;                                                 \
        }                                                                       \
                                                                                \
        /* Store data and return */                                             \
        new_root->data = data;                                                  \
        *tree          = new_root;                                              \
        return true;                                                            \
    }                                                                           \
                                                                                \

  /** ********************************************************************* **/
  /**                                                                       **/
  /** ### CLM_WTREE                                                         **/
  /**                                                                       **/
  /** A set of data types and functions related to the `wtree` container.   **/
  /**                                                                       **/
  /** The `wtree` container is implemented as a weight-balanced tree of     **/
  /** dinamically allocated nodes with rebalancing constants `(2.5, 1.5)`.  **/
  /**                                                                       **/
  /** Weight-balanced trees were defined in the paper "Binary search trees  **/
  /** of bounded balance" by J. Nievergelt & E. M. Reingold in 1972 in the  **/
  /** Proceedings of the Fourth Annual ACM Symposium on Theory of Computing **/
  /** 137–142. doi:10.1145/800152.804906                                    **/
  /**                                                                       **/
  /** Weight-balanced trees are among the easiest balanced trees to code,   **/
  /** specially if you allow yourself to implement the insert and delete    **/
  /** functions recursively. Using the constants `(1+sqrt(2), sqrt(2))` for **/
  /** rebalancing operations guarantee a maximum tree height of, at most,   **/
  /** `2 log(size)`, which is the same upper bound that the more popular    **/
  /** Red-Black trees provide.                                              **/
  /**                                                                       **/
  /** In practice, however, it is advisable to use integer or fractional    **/
  /** constants such as `(3, 2)` or `(2.5, 1.5)` to avoid "integer by       **/
  /** floating point" multiplications or squaring subtree sizes.            **/
  /**                                                                       **/
  /** A wtree with rebalancing constants `(X, Y)` guarantees a maximum      **/
  /** height of `log(size)/log((X+1)/X)`. The constants `(2.5, 1.5)` used   **/
  /** in this implementation guarantee a maximum height of `2.06 log(size)` **/
  /** but usually behave much better.                                       **/
  /**                                                                       **/
  /** There is a really thorough study on how to select these constants     **/
  /** correctly that was published in the paper "Balancing weight-balanced  **/
  /** trees" by Yoichi Hirai & Kazuhiko Yamamoto in 2011 in the Journal of  **/
  /** Functional Programming 21 (3): 137–142. doi:10.1017/S0956796811000104 **/
  /**                                                                       **/
  /** Another good reason to choose weight-balanced trees as the default    **/
  /** balanced tree container is that they use the `size` field to maintain **/
  /** balance. This field is useful on its own because it allows us to      **/
  /** perform the order-statistic queries `rank` and `select` efficiently.  **/
  /** Given the effect of memory alignement of structs, a `size_t` field    **/
  /** like `size` often takes as much space as a simple `bool` field like   **/
  /** `color` so you better use the whole thing to gain functionality.      **/
  /**                                                                       **/
  /** Finally, when you work with type-safe generic containers like this    **/
  /** one you have to decide what happens when a query fails. I.e. what     **/
  /** happens if the user ask you to recover an element that is not there.  **/
  /**                                                                       **/
  /** Different libraries use different approaches to solve this problem:   **/
  /**                                                                       **/
  /** * Make the user responsible of making queries that never fail. So the **/
  /**   user should ask if the element is there before recovering it.       **/
  /** * Returning a pointer to a tree node instead of a value. Meaning      **/
  /**   that user should extract the value afterwards.                      **/
  /** * Some default value (usually `0`) is hardcoded. Meaning that the     **/
  /**   user cannot store that value in the container.                      **/
  /** * The container is not fully implemented. Allowing the user to define **/
  /**   what happens when a query fails.                                    **/
  /**                                                                       **/
  /** I want to provide a complete generic container implementation that is **/
  /** able to hold any value of the selected type and I do not want the     **/
  /** user to work with individual tree nodes, iterators or extractor       **/
  /** functions for safety reasons. Therefore, the only remaining option    **/
  /** is to make sure that the user never makes a failing query and using   **/
  /** an order statistics tree as a generic container makes easy to enforce **/
  /** the fail-proof queries approach:                                      **/
  /**                                                                       **/
  /** * Making the `find` function return the `rank` of the element (or `0` **/
  /**   if the element was not there) rather than the element itself.       **/
  /**   This allows the implementation to issue an error message (`0`) with **/
  /**   reasonable semantics (`if (wtree_find(*tree, data)) {...}`) when    **/
  /**   the query fails and provides the reference number (`rank`) required **/
  /**   to recover (`select`) or delete (`remove`) that element.            **/
  /** * Using the `select` function (which depends on `rank`) to recover    **/
  /**   information rather than `find`, `min`, `max`, `next` or `prev`      **/
  /**   functions (which depend on `data`) prevents many failed queries     **/
  /**   by encouraging the user to ask for the `rank` of `data` first.      **/
  /** * Make the `remove` function depend on the `rank` of the removed      **/
  /**   element rather than on the element itself. This makes the user ask  **/
  /**   for the `rank` of an element before trying to delete it, preventing **/
  /**   failed deleting queries.                                            **/
  /** * Implementing a constant-time `wtree_size` function allows the user  **/
  /**   to ensure the validity of any query depending on `rank` values with **/
  /**   just a simple `1 <= rank && rank <= wtree_size(&tree)` test.        **/
  /** * Making the `insert` function return the `rank` of the inserted data **/
  /**   not only allow the user to know whether an insertion failed (`0`)   **/
  /**   but also to get for free the information that other operations over **/
  /**   the same `data` might require.                                      **/
  /**                                                                       **/
  #define IMPORT_CLM_WTREE(type, less, prefix)                                  \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### wtree                                                          **/ \
    /**                                                                     **/ \
    /** Definition of the weight-balanced tree container type `wtree`.      **/ \
    /**                                                                     **/ \
    /** **Warning:** An empty `wtree` is just a `NULL` pointer.             **/ \
    /**                                                                     **/ \
    /** **Example:** Initialize an empty `wtree` with:                      **/ \
    /**                                                                     **/ \
    /**     wtree MyTree = NULL;                                            **/ \
    /**                                                                     **/ \
    /** **Example:** Test for non-emptyness of `MyTree` with:               **/ \
    /**                                                                     **/ \
    /**     if (MyTree) { printf("MyTree is not empty"); }                  **/ \
    /**     else        { printf("MyTree is empty");     }                  **/ \
    /**                                                                     **/ \
    typedef struct prefix##wtree_s {                                            \
      struct prefix##wtree_s *left;                                             \
      struct prefix##wtree_s *right;                                            \
      size_t          size;                                                     \
      type            data;                                                     \
    } prefix##wtree_s, *prefix##wtree;                                          \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### wtree_size                                                     **/ \
    /**                                                                     **/ \
    /** Returns the number of elements stored in `tree` in `O(1)` time.     **/ \
    /**                                                                     **/ \
    /** **Example:** Copy all the elements of `tree` into an array with:    **/ \
    /**                                                                     **/ \
    /**     size_t N = wtree_size(&MyTree);                                 **/ \
    /**     type  *A = NULL;                                                **/ \
    /**     if (N) { A = (type *) malloc(N * sizeof(type)); }               **/ \
    /**     if (A != NULL) {                                                **/ \
    /**         for (size_t i = 0; i < N; i++) {                            **/ \
    /**             A[i] = wtree_select(&MyTree, i+1);                      **/ \
    /**         }                                                           **/ \
    /**     }                                                               **/ \
    /**                                                                     **/ \
    static inline size_t prefix##wtree_size(const prefix##wtree *tree) {        \
                                                                                \
        return ((*tree) ? ((*tree)->size) : (0));                               \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### wtree_find                                                     **/ \
    /**                                                                     **/ \
    /** Looks for `data` in the `tree` in `O(log(size))` time. If `data` is **/ \
    /** in the `tree` it returns its `rank`. Otherwise it returns `0`.      **/ \
    /**                                                                     **/ \
    /** **Warning:** The returned `rank` is 1-based (`1 <= rank <= size`).  **/ \
    /**                                                                     **/ \
    /** **Example:** Find whether `data` is in `MyTree` with:               **/ \
    /**                                                                     **/ \
    /**     size_t rank = wtree_find(&MyTree, data);                        **/ \
    /**     if (rank) {                                                     **/ \
    /**         printf("data is in MyTree.");                               **/ \
    /**         do_something(wtree_select(&MyTree, rank));                  **/ \
    /**     } else {                                                        **/ \
    /**         printf("data is not in MyTree.");                           **/ \
    /**     }                                                               **/ \
    /**                                                                     **/ \
    static inline size_t prefix##wtree_find(const prefix##wtree *tree,          \
                                            const type data) {                  \
                                                                                \
        prefix##wtree node = *tree;                                             \
        size_t        rank = 1;                                                 \
                                                                                \
        /* Find data in the tree */                                             \
        while (node) {                                                          \
            if (less(data, node->data)) { node = node->left; }                  \
            else {                                                              \
                if (node->left)             { rank += node->left->size;    }    \
                if (less(node->data, data)) { node  = node->right; rank++; }    \
                else                        { return rank;                 }    \
            }                                                                   \
        }                                                                       \
                                                                                \
        /* Data not found */                                                    \
        return 0;                                                               \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### wtree_insert                                                   **/ \
    /**                                                                     **/ \
    /** Inserts `data` in `tree` in `O(log(size))` time.                    **/ \
    /**                                                                     **/ \
    /** If `tree` already contains `data`, it gets overwritten and the      **/ \
    /** function returns the current `rank` of `data` in the `tree`.        **/ \
    /** Otherwise the function tries to insert `data` in `tree` and returns **/ \
    /** its current `rank` if possible and `0` otherwise.                   **/ \
    /**                                                                     **/ \
    /** **Example:** Insert `data` in `MyTree` (without overwriting) with:  **/ \
    /**                                                                     **/ \
    /**     if (wtree_find(&MyTree, data)) {                                **/ \
    /**         printf("data was in MyTree already.");                      **/ \
    /**     } else {                                                        **/ \
    /**         wtree_insert(&MyTree, data);                                **/ \
    /**     }                                                               **/ \
    /**                                                                     **/ \
    /** **Example:** Implement a `bisect` function for `wtrees` with:       **/ \
    /**                                                                     **/ \
    /**     size_t wtree_bisect(wtree *tree, type data) {                   **/ \
    /**         size_t rank = wtree_find(tree, data);                       **/ \
    /**         if (rank == 0) {                                            **/ \
    /**             rank = wtree_insert(tree, data);                        **/ \
    /**             wtree_remove(tree, rank);                               **/ \
    /**         }                                                           **/ \
    /**         return rank;                                                **/ \
    /**     }                                                               **/ \
    /**                                                                     **/ \
    static inline size_t prefix##wtree_insert(prefix##wtree *tree,              \
                                              const type data) {                \
                                                                                \
        /* Rebalancing constants (DELTA, GAMMA)                          */     \
        /* (5/2, 3/2) -> Worst case = O(2.06 log(size)) ~ Red-Black tree */     \
        /* (3/1, 2/1) -> Worst case = O(2.41 log(size))                  */     \
        /* (1/0, 1/0) -> Worst case = O(size) ~ Standrad Binary Tree     */     \
        const size_t DELTA_NUM = 5;                                             \
        const size_t DELTA_DEN = 2;                                             \
        const size_t GAMMA_NUM = 3;                                             \
        const size_t GAMMA_DEN = 2;                                             \
                                                                                \
        /* Variables */                                                         \
        prefix##wtree left, right, node = *tree;                                \
        size_t        rank, l_weight, r_weight;                                 \
        bool          is_right = false;                                         \
                                                                                \
        /* Trivial case: Insert data into empty tree */                         \
        if (node == NULL) {                                                     \
            node = (prefix##wtree) malloc(sizeof(prefix##wtree_s));             \
            if (node == NULL) {                                                 \
                fprintf(stderr, "ERROR: Unable to insert data into wtree.\n");  \
                return 0;                                                       \
            } else {                                                            \
                node->size = 1;                                                 \
                node->data = data;                                              \
                node->left = node->right = NULL;                                \
                *tree      = node;                                              \
                return 1;                                                       \
            }                                                                   \
        }                                                                       \
                                                                                \
        /* Case 1: Insert data into node->left */                               \
        if (less(data, node->data)) {                                           \
            rank = prefix##wtree_insert(&(node->left), data);                   \
        }                                                                       \
                                                                                \
        /* Case 2: Insert data into node->right */                              \
        else if (less(node->data, data)) {                                      \
            rank = prefix##wtree_insert(&(node->right), data);                  \
            is_right = true;                                                    \
        }                                                                       \
                                                                                \
        /* Case 3: Overwrite data */                                            \
        else {                                                                  \
            node->data = data;                                                  \
            return (node->left) ? (node->left->size + 1) : (1);                 \
        }                                                                       \
                                                                                \
        /*** REBALANCE (if something changed) ********************************/ \
        if (rank) {                                                             \
                                                                                \
            /* Update node->size */                                             \
            l_weight   = (node->left)  ? (node->left->size  + 1) : (1);         \
            r_weight   = (node->right) ? (node->right->size + 1) : (1);         \
            node->size = l_weight + r_weight - 1;                               \
                                                                                \
            /* Update rank */                                                   \
            if (is_right) { rank += l_weight; }                                 \
                                                                                \
            /* If node->left has become too big after insertion */              \
            if (DELTA_NUM*r_weight < DELTA_DEN*l_weight) {                      \
                                                                                \
                left     = node->left;                                          \
                l_weight = (left->left)  ? (left->left->size  + 1) : (1);       \
                r_weight = (left->right) ? (left->right->size + 1) : (1);       \
                                                                                \
                /* If node->left->right is small: make a single rotation */     \
                if (GAMMA_DEN*r_weight < GAMMA_NUM*l_weight) {                  \
                    node->left  = left->right;                                  \
                    left->right = node;                                         \
                    left->size  = node->size;                                   \
                    node->size  = 1;                                            \
                    node->size += (node->left)  ? (node->left->size)  : (0);    \
                    node->size += (node->right) ? (node->right->size) : (0);    \
                    *tree       = left;                                         \
                }                                                               \
                                                                                \
                /* If node->left->right is big: make a double rotation */       \
                else {                                                          \
                    right        = left->right;                                 \
                    left->right  = right->left;                                 \
                    right->left  = left;                                        \
                    node->left   = right->right;                                \
                    right->right = node;                                        \
                    right->size  = node->size;                                  \
                    node->size   = 1;                                           \
                    node->size  += (node->left)  ? (node->left->size)  : (0);   \
                    node->size  += (node->right) ? (node->right->size) : (0);   \
                    left->size   = 1;                                           \
                    left->size  += (left->left)  ? (left->left->size)  : (0);   \
                    left->size  += (left->right) ? (left->right->size) : (0);   \
                    *tree        = right;                                       \
                }                                                               \
            }                                                                   \
                                                                                \
            /* If node->right has become too big after insertion */             \
            else if (DELTA_NUM*l_weight < DELTA_DEN*r_weight) {                 \
                                                                                \
                right    = node->right;                                         \
                l_weight = (right->left)  ? (right->left->size  + 1) : (1);     \
                r_weight = (right->right) ? (right->right->size + 1) : (1);     \
                                                                                \
                /* If node->right->left is small: make a single rotation */     \
                if (GAMMA_DEN*l_weight < GAMMA_NUM*r_weight) {                  \
                    node->right = right->left;                                  \
                    right->left = node;                                         \
                    right->size = node->size;                                   \
                    node->size  = 1;                                            \
                    node->size += (node->left)  ? (node->left->size)  : (0);    \
                    node->size += (node->right) ? (node->right->size) : (0);    \
                    *tree       = right;                                        \
                }                                                               \
                                                                                \
                /* If node->right->left is big: make a double rotation */       \
                else {                                                          \
                    left         = right->left;                                 \
                    right->left  = left->right;                                 \
                    left->right  = right;                                       \
                    node->right  = left->left;                                  \
                    left->left   = node;                                        \
                    left->size   = node->size;                                  \
                    node->size   = 1;                                           \
                    node->size  += (node->left)  ? (node->left->size)  : (0);   \
                    node->size  += (node->right) ? (node->right->size) : (0);   \
                    right->size  = 1;                                           \
                    right->size += (right->left)  ? (right->left->size)  : (0); \
                    right->size += (right->right) ? (right->right->size) : (0); \
                    *tree        = left;                                        \
                }                                                               \
            }                                                                   \
        }                                                                       \
        /*** End of REBALANCE ************************************************/ \
                                                                                \
        /* Report rank of the inserted element */                               \
        return rank;                                                            \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### wtree_select                                                   **/ \
    /**                                                                     **/ \
    /** Returns the element of the `tree` that has a given `rank` in        **/ \
    /** O(log(size)) time.                                                  **/ \
    /**                                                                     **/ \
    /** **Warning:** The parameter `rank` must satisfy `1 <= rank <= size`  **/ \
    /**                                                                     **/ \
    /** **Example:** Find the smallest element of `MyTree` with:            **/ \
    /**                                                                     **/ \
    /**     type smallest = wtree_select(&MyTree, 1);                       **/ \
    /**                                                                     **/ \
    /** **Example:** Find the biggest element of `MyTree` with:             **/ \
    /**                                                                     **/ \
    /**     type biggest = wtree_select(&MyTree, wtree_size(&MyTree));      **/ \
    /**                                                                     **/ \
    /** **Example:** Iterate over the elements of `MyTree` with:            **/ \
    /**                                                                     **/ \
    /**     size_t size = wtree_size(&MyTree);                              **/ \
    /**     for (size_t i = 1; i <= size; i++) {                            **/ \
    /**         do_something(wtree_select(&MyTree, i));                     **/ \
    /**     }                                                               **/ \
    /**                                                                     **/ \
    static inline type prefix##wtree_select(const prefix##wtree *tree,          \
                                            const size_t rank) {                \
                                                                                \
        prefix##wtree node   = *tree;                                           \
        size_t        target =  rank;                                           \
        size_t        size   = (node) ? (node->size) : (0);                     \
                                                                                \
        /* Preconditions */                                                     \
        assert(1 <= rank && rank <= size);                                      \
                                                                                \
        /* Particular case: Get Min */                                          \
        if (rank == 1) { while (node->left) { node = node->left; } }            \
                                                                                \
        /* Particular case: Get Max */                                          \
        else if (rank == size) { while (node->right) { node = node->right; } }  \
                                                                                \
        /* General case: Perform a O(lg(size)) search */                        \
        else {                                                                  \
            for (;;) {                                                          \
                size = (node->left) ? (node->left->size + 1) : (1);             \
                if (target == size) { break; }                                  \
                else if (target < size) { node = node->left; }                  \
                else { target -= size; node = node->right; }                    \
            }                                                                   \
        }                                                                       \
                                                                                \
        return node->data;                                                      \
    }                                                                           \
                                                                                \
    /** ******************************************************************* **/ \
    /**                                                                     **/ \
    /** #### wtree_remove                                                   **/ \
    /**                                                                     **/ \
    /** Removes and returns the element of the `tree` that has a given      **/ \
    /** `rank` in O(log(size)) time.                                        **/ \
    /**                                                                     **/ \
    /** **Warning:** The parameter `tree` must satisfy `*tree != NULL`.     **/ \
    /**                                                                     **/ \
    /** **Warning:** The parameter `rank` must satisfy `1 <= rank <= size`  **/ \
    /**                                                                     **/ \
    /** **Example:** Remove `data` from `MyTree` (if present) with:         **/ \
    /**                                                                     **/ \
    /**     size_t rank = wtree_find(&MyTree, data);                        **/ \
    /**     if (rank) { free(wtree_remove(&MyTree, rank)); }                **/ \
    /**                                                                     **/ \
    /** **Example:** Remove all elements from `MyTree` with:                **/ \
    /**                                                                     **/ \
    /**     while (MyTree) { free(wtree_remove(&MyTree, 1)); }              **/ \
    /**                                                                     **/ \
    static inline type prefix##wtree_remove(prefix##wtree *tree,                \
                                            const size_t rank) {                \
                                                                                \
        /* Preconditions */                                                     \
        assert( *tree        != NULL);                                          \
        assert((*tree)->size >= rank);                                          \
        assert(            1 <= rank);                                          \
                                                                                \
        /* Rebalancing constants (DELTA, GAMMA)                          */     \
        /* (5/2, 3/2) -> Worst case = O(2.06 log(size)) ~ Red-Black tree */     \
        /* (3/1, 2/1) -> Worst case = O(2.41 log(size))                  */     \
        /* (1/0, 1/0) -> Worst case = O(size) ~ Standrad Binary Tree     */     \
        const size_t DELTA_NUM = 5;                                             \
        const size_t DELTA_DEN = 2;                                             \
        const size_t GAMMA_NUM = 3;                                             \
        const size_t GAMMA_DEN = 2;                                             \
                                                                                \
        /* Variables */                                                         \
        prefix##wtree next, left, right, node = *tree;                          \
        size_t r_weight, l_weight = (node->left) ? (node->left->size+1) : (1);  \
        type   data;                                                            \
                                                                                \
        /* Case 1: remove from node->left */                                    \
        if (l_weight > rank) {                                                  \
            data = prefix##wtree_remove(&(node->left), rank);                   \
        }                                                                       \
                                                                                \
        /* Case 2: remove from node->right */                                   \
        else if (l_weight < rank) {                                             \
            data = prefix##wtree_remove(&(node->right), rank-l_weight);         \
        }                                                                       \
                                                                                \
        /* Case 3: swap data with min(node->right) and then remove it */        \
        else if (node->left && node->right) {                                   \
            next = node->right;                                                 \
            while (next->left) { next = next->left; }                           \
            data       = node->data;                                            \
            node->data = next->data;                                            \
            next->data = data;                                                  \
            data       = prefix##wtree_remove(&(node->right), 1);               \
        }                                                                       \
                                                                                \
        /* Case 4: remove leaf */                                               \
        else {                                                                  \
            if (node->left) { *tree = node->left;  }                            \
            else            { *tree = node->right; }                            \
            data = node->data;                                                  \
            free(node);                                                         \
            return data;                                                        \
        }                                                                       \
                                                                                \
        /* Update node->size */                                                 \
        l_weight   = (node->left)  ? (node->left->size  + 1) : (1);             \
        r_weight   = (node->right) ? (node->right->size + 1) : (1);             \
        node->size = l_weight + r_weight - 1;                                   \
                                                                                \
        /*** REBALANCE *******************************************************/ \
                                                                                \
        /* If node->left has become too big */                                  \
        if (DELTA_NUM*r_weight < DELTA_DEN*l_weight) {                          \
                                                                                \
            left     = node->left;                                              \
            l_weight = (left->left)  ? (left->left->size  + 1) : (1);           \
            r_weight = (left->right) ? (left->right->size + 1) : (1);           \
                                                                                \
            /* If node->left->right is small: make a single rotation */         \
            if (GAMMA_DEN*r_weight < GAMMA_NUM*l_weight) {                      \
                node->left  = left->right;                                      \
                left->right = node;                                             \
                left->size  = node->size;                                       \
                node->size  = 1;                                                \
                node->size += (node->left)  ? (node->left->size)  : (0);        \
                node->size += (node->right) ? (node->right->size) : (0);        \
                *tree       = left;                                             \
            }                                                                   \
                                                                                \
            /* If node->left->right is big: make a double rotation */           \
            else {                                                              \
                right        = left->right;                                     \
                left->right  = right->left;                                     \
                right->left  = left;                                            \
                node->left   = right->right;                                    \
                right->right = node;                                            \
                right->size  = node->size;                                      \
                node->size   = 1;                                               \
                node->size  += (node->left)  ? (node->left->size)  : (0);       \
                node->size  += (node->right) ? (node->right->size) : (0);       \
                left->size   = 1;                                               \
                left->size  += (left->left)  ? (left->left->size)  : (0);       \
                left->size  += (left->right) ? (left->right->size) : (0);       \
                *tree        = right;                                           \
            }                                                                   \
        }                                                                       \
                                                                                \
        /* If node->left has become too big */                                  \
        else if (DELTA_NUM*l_weight < DELTA_DEN*r_weight) {                     \
                                                                                \
            right    = node->right;                                             \
            l_weight = (right->left)  ? (right->left->size  + 1) : (1);         \
            r_weight = (right->right) ? (right->right->size + 1) : (1);         \
                                                                                \
            /* If node->right->left is small: make a single rotation */         \
            if (GAMMA_DEN*l_weight < GAMMA_NUM*r_weight) {                      \
                node->right = right->left;                                      \
                right->left = node;                                             \
                right->size = node->size;                                       \
                node->size  = 1;                                                \
                node->size += (node->left)  ? (node->left->size)  : (0);        \
                node->size += (node->right) ? (node->right->size) : (0);        \
                *tree       = right;                                            \
            }                                                                   \
                                                                                \
            /* If node->right->left is big: make a double rotation */           \
            else {                                                              \
                left         = right->left;                                     \
                right->left  = left->right;                                     \
                left->right  = right;                                           \
                node->right  = left->left;                                      \
                left->left   = node;                                            \
                left->size   = node->size;                                      \
                node->size   = 1;                                               \
                node->size  += (node->left)  ? (node->left->size)  : (0);       \
                node->size  += (node->right) ? (node->right->size) : (0);       \
                right->size  = 1;                                               \
                right->size += (right->left)  ? (right->left->size)  : (0);     \
                right->size += (right->right) ? (right->right->size) : (0);     \
                *tree        = left;                                            \
            }                                                                   \
        }                                                                       \
        /*** End of REBALANCE ************************************************/ \
                                                                                \
        /* Return the data removed from the tree */                             \
        return data;                                                            \
    }                                                                           \
                                                                                \

  /** ********************************************************************* **/

#endif
