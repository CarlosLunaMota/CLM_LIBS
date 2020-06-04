/** *********************************************************************** **/
/**                                                                         **/
/**  test.c                                                                 **/
/**  ------                                                                 **/
/**                                                                         **/
/** Content: A set of tests for the CLM_LIBS code-generating macros         **/
/**                                                                         **/
/** Author:  Carlos Luna Mota                                               **/
/**                                                                         **/
/** Source:  <https://github.com/CarlosLunaMota/CLM_LIBS>                   **/
/**                                                                         **/
/** License: The Unlicense                                                  **/
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


/** MACROS **************************************************************** **/

#define LESS_THAN(i, j) ((i) < (j))

/** LIBRARIES ************************************************************* **/

#include "CLM_LIBS.h"

IMPORT_CLM_TIME()
IMPORT_CLM_RAND()
IMPORT_CLM_ARC4()
IMPORT_CLM_ITER()
IMPORT_CLM_PRINTF()
IMPORT_CLM_FRACTAL()
IMPORT_CLM_CLIST(size_t, )
IMPORT_CLM_ARRAY(size_t, LESS_THAN, )
IMPORT_CLM_STREE(size_t, LESS_THAN, )
IMPORT_CLM_WTREE(size_t, LESS_THAN, )

/** AUXILIARY FUNCTIONS *************************************************** **/

bool clist_verify(clist L) {

    clist fast = L;
    clist slow = L;

    if (L == NULL) { return true; }

    do {if (fast->next == NULL) { return false;      }
        else                    { fast = fast->next; }
        if (fast->next == NULL) { return false;      }
        else                    { fast = fast->next; }
        slow = slow->next;
    } while (fast != slow);

    do { slow = slow->next; } while (slow != L && slow != fast);

    if (slow == L) { return true;  }
    else           { return false; }
}

void clist_print(clist L, char *indent) {

    if (indent) { printf("%s", indent); }

    printf("[ ");

    if (L) {
        clist node = L;
        do { node = node->next; printf("%zu ", node->data); } while(node != L);
    }

    printf("]\n");
}

bool array_verify(array A, size_t length) {

    if (A         == NULL)                { return false; }
    if (length    == 0)                   { return false; }
    if (sizeof(A) != length*sizeof(A[0])) { return false; }
    return true;
}

void array_print(array A, size_t length, char *indent) {

    if (indent) { printf("%s", indent); }

    printf("[ ");
    if (A) { for (size_t i = 0; i < length; i++) { printf("%zu ", A[i]); } }
    printf("]\n");
}

bool stree_verify(stree T, stree less, stree more) {

    while (T != NULL) {

        if (less != NULL && T->data <= less->data) { return false; }

        if (more != NULL && T->data >= more->data) { return false; }

        if (T->right == NULL) { more = T; T = T->left;  continue; }

        if (T->left  == NULL) { less = T; T = T->right; continue; }

        return (stree_verify(T->left,  less, T) &&
                stree_verify(T->right, T, more));
    }

    return true;
}

void stree_print(stree T, const bool is_right, char *indent) {

    // Allocate memory:
    char *new_indent = (char *) malloc(((9+strlen(indent))*sizeof(char)));
    assert(new_indent != NULL);

    // Print right subtree recursively:
    if (T && T->right) {
        if (is_right) { sprintf(new_indent, "%s%s", indent, "        "); }
        else          { sprintf(new_indent, "%s%s", indent, "|       "); }
        stree_print(T->right, true, new_indent);
    }

    // Print current node:
    if (is_right) { fprintf(stdout, "%s,----", indent); }
    else          { fprintf(stdout, "%s`----", indent); }
    if (T) { fprintf(stdout, "(%zu)\n", T->data); }
    else   { fprintf(stdout, "()\n");             }

    // Print left subtree recursively:
    if (T && T->left) {
        if (is_right) { sprintf(new_indent, "%s%s", indent, "|       "); }
        else          { sprintf(new_indent, "%s%s", indent, "        "); }
        stree_print(T->left, false, new_indent);
    }

    // Free memory:
    free(new_indent);
}

size_t stree_height(stree T) {

    // Trivial case
    if (T == NULL) { return 0; }

    // General case
    size_t l_height = stree_height(T->left);
    size_t r_height = stree_height(T->right);

    if (l_height > r_height) { return l_height+1; }
    else                     { return r_height+1; }
}

bool wtree_verify(wtree T, wtree less, wtree more) {

    const size_t DELTA_NUM = 5;
    const size_t DELTA_DEN = 2;

    if (T == NULL) { return true; }

    if (less != NULL && less->data >= T->data) { return false; }
    if (more != NULL && T->data >= more->data) { return false; }

    size_t size   =  T->size;
    size_t l_size = (T->left)  ? (T->left->size)  : (0);
    size_t r_size = (T->right) ? (T->right->size) : (0);

    if (size != l_size + r_size + 1)       { return false; }
    if ((1+l_size)*DELTA_DEN > (1+r_size)*DELTA_NUM) { return false; }
    if ((1+l_size)*DELTA_NUM < (1+r_size)*DELTA_DEN) { return false; }

    if (!wtree_verify(T->left,  less, T)) { return false; }
    if (!wtree_verify(T->right, T, more)) { return false; }

    return true;
}

void wtree_print(wtree T, const bool is_right, char *indent) {

    // Allocate memory:
    char *new_indent = (char *) malloc(((9+strlen(indent))*sizeof(char)));
    assert(new_indent != NULL);

    // Print right subtree recursively:
    if (T && T->right) {
        if (is_right) { sprintf(new_indent, "%s%s", indent, "        "); }
        else          { sprintf(new_indent, "%s%s", indent, "|       "); }
        wtree_print(T->right, true, new_indent);
    }

    // Print current node:
    if (is_right) { fprintf(stdout, "%s,----", indent); }
    else          { fprintf(stdout, "%s`----", indent); }
    if (T) { fprintf(stdout, "(%zu)[%zu]\n", T->data, T->size); }
    else   { fprintf(stdout, "()[0]\n");                        }

    // Print left subtree recursively:
    if (T && T->left) {
        if (is_right) { sprintf(new_indent, "%s%s", indent, "|       "); }
        else          { sprintf(new_indent, "%s%s", indent, "        "); }
        wtree_print(T->left, false, new_indent);
    }

    // Free memory:
    free(new_indent);
}

size_t wtree_height(wtree T) {

    // Trivial case
    if (T == NULL) { return 0; }

    // General case
    size_t l_height = wtree_height(T->left);
    size_t r_height = wtree_height(T->right);

    if (l_height > r_height) { return l_height+1; }
    else                     { return r_height+1; }
}

/** TESTS ***************************************************************** **/

void CLM_TIME_TEST(bool verbose) {

    printf("\nTesting CLM_TIME...\n\n");

    if (verbose) {

        clock_t crono;
        char   *s;
        size_t  e = 30;
        int     format[16] = {32,16,8,4,2,1,0,-63,-62,-56,-48,-31,-30,-24,-7,-6};

        // Test time_elapsed(clock_t)
        crono = clock();
        for (size_t i = 1<<e; i-->0;) { assert(i == i); }
        printf("\tCounting to 2^%zu in %.3f seconds.\n\n", e, time_elapsed(crono));

        // Test time_stamp(int)
        for (int i = 0; i < 16; i++) {
            s = time_stamp(format[i]);
            printf("\tTimestamp(%d):\t'%s'\n", format[i], s);
            free(s);
        }

        // Test time_pause(char *)
        time_pause("\n\t>> Program paused. Press return to resume <<\n");

    }
}

void CLM_RAND_TEST(bool verbose) {

    int    r, g, b;
    double stats[10];
    double d;
    size_t i;
    size_t size = 1000;

    printf("\nTesting CLM_RANDOM...\n\n");

    /* Init Random Seed */
    srand(time(NULL));

    /* Test rand_int */
    for (i = 0; i < size; i++) { while (i != (size_t) rand_int(size)); }
    if (verbose) {
        for (i = 0; i < 10;   i++) { stats[i] = 0.0; }
        for (i = 0; i < size; i++) { stats[rand_int(10)] += 1.0; }
        for (i = 0; i < 10;   i++) { stats[i] *= 100.0/((double) size); }
        printf("\trand_int(10):        ");
        for (i = 0; i < 10;   i++) { printf("%4.1f%%  ", stats[i]); }
        printf("\n");
    }

    /* Test rand_size_t */
    for (i = 0; i < size; i++) { while (i != rand_size_t(size)); }
    if (verbose) {
        for (i = 0; i < 10;   i++) { stats[i] = 0.0; }
        for (i = 0; i < size; i++) { stats[rand_size_t(10)] += 1.0; }
        for (i = 0; i < 10;   i++) { stats[i] *= 100.0/((double) size); }
        printf("\trand_size_t(10):     ");
        for (i = 0; i < 10;   i++) { printf("%4.1f%%  ", stats[i]); }
        printf("\n");
    }

    /* Test rand_double */
    for (i = 0; i < size; i++) { while (i != (size_t) rand_double(size)); }
    if (verbose) {
        for (i = 0; i < 10;   i++) { stats[i] = 0.0; }
        for (i = 0; i < size; i++) {
            d = rand_double(1.0);
            if      (d < 0.1) { stats[0] += 1.0; }
            else if (d < 0.2) { stats[1] += 1.0; }
            else if (d < 0.3) { stats[2] += 1.0; }
            else if (d < 0.4) { stats[3] += 1.0; }
            else if (d < 0.5) { stats[4] += 1.0; }
            else if (d < 0.6) { stats[5] += 1.0; }
            else if (d < 0.7) { stats[6] += 1.0; }
            else if (d < 0.8) { stats[7] += 1.0; }
            else if (d < 0.9) { stats[8] += 1.0; }
            else              { stats[9] += 1.0; }
        }
        for (i = 0; i < 10;   i++) { stats[i] *= 100.0/((double) size); }
        printf("\trand_double(10):     ");
        for (i = 0; i < 10;   i++) { printf("%4.1f%%  ", stats[i]); }
        printf("\n");
    }

    /* Test rand_halton */
    for (i = 0; i < 16; i++) { assert(16*rand_halton(2,16*rand_halton(2,i)) == i); }
    for (i = 0; i < 27; i++) { assert(27*rand_halton(3,27*rand_halton(3,i)) == i); }
    if (verbose) {
        printf("\t16*rand_halton(b=2):  ");
        for (i = 0; i < 16; i++) { printf("%.0f  ", 16*rand_halton(2,i)); }
        printf("\n");
        printf("\t27*rand_halton(b=3):  ");
        for (i = 0; i < 27; i++) { printf("%.0f  ", 27*rand_halton(3,i)); }
        printf("\n");
    }

    /* Test rand_color */
    for (i = 0; i < size; i++) {
        r = rand_int(256);
        g = rand_int(256);
        b = rand_int(256);
        rand_color(&r, &g, &b);
        assert(0 <= r && r <= 255);
        assert(0 <= g && g <= 255);
        assert(0 <= b && b <= 255);
    }
    if (verbose) {
        r = 255; g = 135; b = 0;
        printf("\trand_color(8):       ");
        for (i = 0; i < 8; i++) {
            rand_color(&r, &g, &b);
            printf("#%02x%02x%02x  ", r,g,b);
        }
        printf("\n");
    }
}

void CLM_PRINTF_TEST(bool verbose) {


    printf("\nTesting CLM_PRINTF...\n\n");

    if (verbose) {

        printf_reset();
        printf("\tNormal text\n");
        printf_set_bold();
        printf("\tBold text\n");
        printf_reset();
        printf_set_light();
        printf("\tLight text\n");
        printf_reset();
        printf_set_strike();
        printf("\tStriked text\n");
        printf_reset();
        printf_set_underline();
        printf("\tUnderlined text\n");

        printf_reset();
        printf("\n\tColor Palette:\n");

        for (int r = 0x00; r <= 0xFF; r += 0x33) {
            printf_reset();
            printf("\n\t");
            for (int g = 0x00; g < 0x99; g += 0x33) {
                for (int b = 0x00; b <= 0xFF; b += 0x33) {
                    printf_set_text_color(0,0,0);
                    printf_set_back_color(r,g,b);
                    printf("  #%01X%01X%01X",r%16,g%16,b%16);
                }
            }
        }

        for (int r = 0x00; r <= 0xFF; r += 0x33) {
            printf_reset();
            printf("\n\t");
            for (int g = 0x99; g <= 0xFF; g += 0x33) {
                for (int b = 0x00; b <= 0xFF; b += 0x33) {
                    printf_set_text_color(0,0,0);
                    printf_set_back_color(r,g,b);
                    printf("  #%01X%01X%01X",r%16,g%16,b%16);
                }
            }
        }

        printf_reset();
        printf("\n");
        for (int r = 0x00; r <= 0xFF; r += 0x33) {
            printf_reset();
            printf("\n\t");
            for (int g = 0x00; g < 0x99; g += 0x33) {
                for (int b = 0x00; b <= 0xFF; b += 0x33) {
                    printf_set_text_color(r,g,b);
                    printf("  #%01X%01X%01X",r%16,g%16,b%16);
                }
            }
        }

        for (int r = 0x00; r <= 0xFF; r += 0x33) {
            printf_reset();
            printf("\n\t");
            for (int g = 0x99; g <= 0xFF; g += 0x33) {
                for (int b = 0x00; b <= 0xFF; b += 0x33) {
                    printf_set_text_color(r,g,b);
                    printf("  #%01X%01X%01X",r%16,g%16,b%16);
                }
            }
        }

        printf_reset();
        printf("\n\n\tGreyscale Palette:\n\n\t");

        for (int g = 0; g < 24; g++) {
            printf_set_text_grey(0);
            printf_set_back_grey(g);
            printf("  %02d",g);
        }

        printf_reset();
        printf("\n\n\t");

        for (int g = 0; g < 24; g++) {
            printf_set_text_grey(g);
            printf("  %02d",g);
        }

        printf_reset();
        printf("\n\n\tMario:\n\n\t");

        int R[7] = {0xFF, 0xFF, 0x66, 0xFF, 0x00, 0x00, 0xFF};
        int G[7] = {0xFF, 0x00, 0x33, 0x99, 0x00, 0x00, 0xFF};
        int B[7] = {0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00};
        int M[18][18] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0},
                         {0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0},
                         {0,0,0,0,0,2,2,2,3,3,4,3,0,0,0,0,0,0},
                         {0,0,0,0,2,3,2,3,3,3,4,3,3,3,0,0,0,0},
                         {0,0,0,0,2,3,2,2,3,3,3,4,3,3,3,0,0,0},
                         {0,0,0,0,0,2,3,3,3,3,4,4,4,4,0,0,0,0},
                         {0,0,0,0,0,0,3,3,3,3,3,3,0,0,0,0,0,0},
                         {0,0,0,0,0,1,1,5,1,1,5,1,1,0,0,0,0,0},
                         {0,0,0,0,1,1,1,5,1,1,5,1,1,1,0,0,0,0},
                         {0,0,0,1,1,1,1,5,5,5,5,1,1,1,1,0,0,0},
                         {0,0,0,3,3,1,5,6,5,5,6,5,1,3,3,0,0,0},
                         {0,0,0,3,3,3,5,5,5,5,5,5,3,3,3,0,0,0},
                         {0,0,0,3,3,5,5,5,5,5,5,5,5,3,3,0,0,0},
                         {0,0,0,0,0,5,5,5,0,0,5,5,5,0,0,0,0,0},
                         {0,0,0,0,2,2,2,0,0,0,0,2,2,2,0,0,0,0},
                         {0,0,0,2,2,2,2,0,0,0,0,2,2,2,2,0,0,0}};
        int N[18][18] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0},
                         {0,0,0,0,0,0,0,1,1,1,1,1,0,0,3,3,3,0},
                         {0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,3,3,0},
                         {0,0,0,0,0,0,2,2,2,3,3,4,3,0,1,1,1,0},
                         {0,0,0,0,0,2,3,2,3,3,3,4,3,3,1,1,1,0},
                         {0,0,0,0,0,2,3,2,2,3,3,3,4,3,3,3,1,0},
                         {0,0,0,0,0,0,2,3,3,3,3,4,4,4,4,1,0,0},
                         {0,0,0,0,0,0,0,3,3,3,3,3,3,1,1,0,0,0},
                         {0,0,0,1,1,1,1,1,5,1,1,1,5,1,0,0,0,0},
                         {0,0,1,1,1,1,1,1,1,5,1,1,1,5,0,0,2,0},
                         {0,3,3,1,1,1,1,1,1,5,5,5,5,5,0,0,2,0},
                         {0,3,3,3,0,5,5,1,5,5,6,5,5,6,5,2,2,0},
                         {0,0,3,0,2,5,5,5,5,5,5,5,5,5,5,2,2,0},
                         {0,0,0,2,2,2,5,5,5,5,5,5,5,5,5,2,2,0},
                         {0,0,2,2,2,5,5,5,5,5,0,0,0,0,0,0,0,0},
                         {0,0,2,0,0,5,5,5,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

        for (size_t i = 0; i < 18; i++) {
            for (size_t j = 0; j < 18; j++) {
                printf_set_back_color(R[M[i][j]], G[M[i][j]], B[M[i][j]]);
                printf("  ");
            }
            printf_reset(); printf("\t");
            for (size_t j = 0; j < 18; j++) {
                printf_set_back_color(R[N[i][j]], G[N[i][j]], B[N[i][j]]);
                printf("  ");
            }
            printf_reset(); printf("\n\t");
        }

        printf_reset();
        printf("\n");
    }
}

void CLM_ARC4_TEST(bool verbose) {

    printf("\nTesting CLM_ARC4...\n\n");

    char *output;

    /* Three test cases from Wikipedia: */

    output = arc4_hash("Key", 10, 0);
    if (verbose) { printf("\tarc4_hash(Key)                                     = %s...\n", output); }
    assert(strcmp("EB9F7781B734CA72A719", output) == 0);
    free(output);

    output = arc4_encrypt("Plaintext", "Key", 0);
    if (verbose) { printf("\tarc4_encrypt(Plaintext, Key)                       = %s\n", output); }
    assert(strcmp("BBF316E8D940AF0AD3", output) == 0);
    free(output);

    output = arc4_decrypt("BBF316E8D940AF0AD3", "Key", 0);
    if (verbose) { printf("\tarc4_decrypt(BBF316E8D940AF0AD3, Key)              = %s\n", output); }
    assert(strcmp("Plaintext", output) == 0);
    free(output);

    if (verbose) { printf("\n"); }

    output = arc4_hash("Wiki", 6, 0);
    if (verbose) { printf("\tarc4_hash(Wiki)                                    = %s...\n", output); }
    assert(strcmp("6044DB6D41B7", output) == 0);
    free(output);

    output = arc4_encrypt("pedia", "Wiki", 0);
    if (verbose) { printf("\tarc4_encrypt(pedia, Wiki)                          = %s\n", output); }
    assert(strcmp("1021BF0420", output) == 0);
    free(output);

    output = arc4_decrypt("1021BF0420", "Wiki", 0);
    if (verbose) { printf("\tarc4_decrypt(1021BF0420, Wiki)                     = %s\n", output); }
    assert(strcmp("pedia", output) == 0);
    free(output);

    if (verbose) { printf("\n"); }

    output = arc4_hash("Secret", 8, 0);
    if (verbose) { printf("\tarc4_hash(Secret)                                  = %s...\n", output); }
    assert(strcmp("04D46B053CA87B59", output) == 0);
    free(output);

    output = arc4_encrypt("Attack at dawn", "Secret", 0);
    if (verbose) { printf("\tarc4_encrypt(Attack at dawn, Secret)               = %s\n", output); }
    assert(strcmp("45A01F645FC35B383552544B9BF5", output) == 0);
    free(output);

    output = arc4_decrypt("45A01F645FC35B383552544B9BF5", "Secret", 0);
    if (verbose) { printf("\tarc4_decrypt(45A01F645FC35B383552544B9BF5, Secret) = %s\n", output); }
    assert(strcmp("Attack at dawn", output) == 0);
    free(output);

    /* Test Vectors for the Stream Cipher RC4 (RFC 6229) */

    output = arc4_hash("\x01\x02\x03\x04\x05", 16,    0);
    assert(strcmp("B2396305F03DC027CCC3524A0A1118A8", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05", 16,   16);
    assert(strcmp("6982944F18FC82D589C403A47A0D0919", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05", 16,  240);
    assert(strcmp("28CB1132C96CE286421DCAADB8B69EAE", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05", 16,  256);
    assert(strcmp("1CFCF62B03EDDB641D77DFCF7F8D8C93", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05", 16,  496);
    assert(strcmp("42B7D0CDD918A8A33DD51781C81F4041", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05", 16,  512);
    assert(strcmp("6459844432A7DA923CFB3EB4980661F6", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05", 16,  752);
    assert(strcmp("EC10327BDE2BEEFD18F9277680457E22", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05", 16,  768);
    assert(strcmp("EB62638D4F0BA1FE9FCA20E05BF8FF2B", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05", 16, 1008);
    assert(strcmp("45129048E6A0ED0B56B490338F078DA5", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05", 16, 1024);
    assert(strcmp("30ABBCC7C20B01609F23EE2D5F6BB7DF", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05", 16, 1520);
    assert(strcmp("3294F744D8F9790507E70F62E5BBCEEA", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05", 16, 1536);
    assert(strcmp("D8729DB41882259BEE4F825325F5A130", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05", 16, 2032);
    assert(strcmp("1EB14A0C13B3BF47FA2A0BA93AD45B8B", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05", 16, 2048);
    assert(strcmp("CC582F8BA9F265E2B1BE9112E975D2D7", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05", 16, 3056);
    assert(strcmp("F2E30F9BD102ECBF75AAADE9BC35C43C", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05", 16, 3072);
    assert(strcmp("EC0E11C479DC329DC8DA7968FE965681", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05", 16, 4080);
    assert(strcmp("068326A2118416D21F9D04B2CD1CA050", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05", 16, 4096);
    assert(strcmp("FF25B58995996707E51FBDF08B34D875", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07", 16,    0);
    assert(strcmp("293F02D47F37C9B633F2AF5285FEB46B", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07", 16,   16);
    assert(strcmp("E620F1390D19BD84E2E0FD752031AFC1", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07", 16,  240);
    assert(strcmp("914F02531C9218810DF60F67E338154C", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07", 16,  256);
    assert(strcmp("D0FDB583073CE85AB83917740EC011D5", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07", 16,  496);
    assert(strcmp("75F81411E871CFFA70B90C74C592E454", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07", 16,  512);
    assert(strcmp("0BB87202938DAD609E87A5A1B079E5E4", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07", 16,  752);
    assert(strcmp("C2911246B612E7E7B903DFEDA1DAD866", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07", 16,  768);
    assert(strcmp("32828F91502B6291368DE8081DE36FC2", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07", 16, 1008);
    assert(strcmp("F3B9A7E3B297BF9AD804512F9063EFF1", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07", 16, 1024);
    assert(strcmp("8ECB67A9BA1F55A5A067E2B026A3676F", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07", 16, 1520);
    assert(strcmp("D2AA902BD42D0D7CFD340CD45810529F", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07", 16, 1536);
    assert(strcmp("78B272C96E42EAB4C60BD914E39D06E3", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07", 16, 2032);
    assert(strcmp("F4332FD31A079396EE3CEE3F2A4FF049", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07", 16, 2048);
    assert(strcmp("05459781D41FDA7F30C1BE7E1246C623", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07", 16, 3056);
    assert(strcmp("ADFD3868B8E51485D5E610017E3DD609", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07", 16, 3072);
    assert(strcmp("AD26581C0C5BE45F4CEA01DB2F3805D5", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07", 16, 4080);
    assert(strcmp("F3172CEFFC3B3D997C85CCD5AF1A950C", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07", 16, 4096);
    assert(strcmp("E74B0B9731227FD37C0EC08A47DDD8B8", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08", 16,    0);
    assert(strcmp("97AB8A1BF0AFB96132F2F67258DA15A8", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08", 16,   16);
    assert(strcmp("8263EFDB45C4A18684EF87E6B19E5B09", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08", 16,  240);
    assert(strcmp("9636EBC9841926F4F7D1F362BDDF6E18", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08", 16,  256);
    assert(strcmp("D0A990FF2C05FEF5B90373C9FF4B870A", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08", 16,  496);
    assert(strcmp("73239F1DB7F41D80B643C0C52518EC63", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08", 16,  512);
    assert(strcmp("163B319923A6BDB4527C626126703C0F", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08", 16,  752);
    assert(strcmp("49D6C8AF0F97144A87DF21D91472F966", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08", 16,  768);
    assert(strcmp("44173A103B6616C5D5AD1CEE40C863D0", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08", 16, 1008);
    assert(strcmp("273C9C4B27F322E4E716EF53A47DE7A4", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08", 16, 1024);
    assert(strcmp("C6D0E7B226259FA9023490B26167AD1D", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08", 16, 1520);
    assert(strcmp("1FE8986713F07C3D9AE1C163FF8CF9D3", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08", 16, 1536);
    assert(strcmp("8369E1A965610BE887FBD0C79162AAFB", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08", 16, 2032);
    assert(strcmp("0A0127ABB44484B9FBEF5ABCAE1B579F", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08", 16, 2048);
    assert(strcmp("C2CDADC6402E8EE866E1F37BDB47E42C", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08", 16, 3056);
    assert(strcmp("26B51EA37DF8E1D6F76FC3B66A7429B3", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08", 16, 3072);
    assert(strcmp("BC7683205D4F443DC1F29DDA3315C87B", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08", 16, 4080);
    assert(strcmp("D5FA5A3469D29AAAF83D23589DB8C85B", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08", 16, 4096);
    assert(strcmp("3FB46E2C8F0F068EDCE8CDCD7DFC5862", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a", 16,    0);
    assert(strcmp("EDE3B04643E586CC907DC21851709902", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a", 16,   16);
    assert(strcmp("03516BA78F413BEB223AA5D4D2DF6711", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a", 16,  240);
    assert(strcmp("3CFD6CB58EE0FDDE640176AD0000044D", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a", 16,  256);
    assert(strcmp("48532B21FB6079C9114C0FFD9C04A1AD", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a", 16,  496);
    assert(strcmp("3E8CEA98017109979084B1EF92F99D86", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a", 16,  512);
    assert(strcmp("E20FB49BDB337EE48B8D8DC0F4AFEFFE", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a", 16,  752);
    assert(strcmp("5C2521EACD7966F15E056544BEA0D315", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a", 16,  768);
    assert(strcmp("E067A7031931A246A6C3875D2F678ACB", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a", 16, 1008);
    assert(strcmp("A64F70AF88AE56B6F87581C0E23E6B08", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a", 16, 1024);
    assert(strcmp("F449031DE312814EC6F319291F4A0516", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a", 16, 1520);
    assert(strcmp("BDAE85924B3CB1D0A2E33A30C6D79599", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a", 16, 1536);
    assert(strcmp("8A0FEDDBAC865A09BCD127FB562ED60A", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a", 16, 2032);
    assert(strcmp("B55A0A5B51A12A8BE34899C3E047511A", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a", 16, 2048);
    assert(strcmp("D9A09CEA3CE75FE39698070317A71339", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a", 16, 3056);
    assert(strcmp("552225ED1177F44584AC8CFA6C4EB5FC", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a", 16, 3072);
    assert(strcmp("7E82CBABFC95381B080998442129C2F8", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a", 16, 4080);
    assert(strcmp("1F135ED14CE60A91369D2322BEF25E3C", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a", 16, 4096);
    assert(strcmp("08B6BE45124A43E2EB77953F84DC8553", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10", 16,    0);
    assert(strcmp("9AC7CC9A609D1EF7B2932899CDE41B97", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10", 16,   16);
    assert(strcmp("5248C4959014126A6E8A84F11D1A9E1C", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10", 16,  240);
    assert(strcmp("065902E4B620F6CC36C8589F66432F2B", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10", 16,  256);
    assert(strcmp("D39D566BC6BCE3010768151549F3873F", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10", 16,  496);
    assert(strcmp("B6D1E6C4A5E4771CAD79538DF295FB11", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10", 16,  512);
    assert(strcmp("C68C1D5C559A974123DF1DBC52A43B89", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10", 16,  752);
    assert(strcmp("C5ECF88DE897FD57FED301701B82A259", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10", 16,  768);
    assert(strcmp("ECCBE13DE1FCC91C11A0B26C0BC8FA4D", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10", 16, 1008);
    assert(strcmp("E7A72574F8782AE26AABCF9EBCD66065", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10", 16, 1024);
    assert(strcmp("BDF0324E6083DCC6D3CEDD3CA8C53C16", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10", 16, 1520);
    assert(strcmp("B40110C4190B5622A96116B0017ED297", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10", 16, 1536);
    assert(strcmp("FFA0B514647EC04F6306B892AE661181", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10", 16, 2032);
    assert(strcmp("D03D1BC03CD33D70DFF9FA5D71963EBD", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10", 16, 2048);
    assert(strcmp("8A44126411EAA78BD51E8D87A8879BF5", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10", 16, 3056);
    assert(strcmp("FABEB76028ADE2D0E48722E46C4615A3", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10", 16, 3072);
    assert(strcmp("C05D88ABD50357F935A63C59EE537623", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10", 16, 4080);
    assert(strcmp("FF38265C1642C1ABE8D3C2FE5E572BF8", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10", 16, 4096);
    assert(strcmp("A36A4C301AE8AC13610CCBC12256CACC", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18", 16,    0);
    assert(strcmp("0595E57FE5F0BB3C706EDAC8A4B2DB11", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18", 16,   16);
    assert(strcmp("DFDE31344A1AF769C74F070AEE9E2326", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18", 16,  240);
    assert(strcmp("B06B9B1E195D13D8F4A7995C4553AC05", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18", 16,  256);
    assert(strcmp("6BD2378EC341C9A42F37BA79F88A32FF", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18", 16,  496);
    assert(strcmp("E70BCE1DF7645ADB5D2C4130215C3522", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18", 16,  512);
    assert(strcmp("9A5730C7FCB4C9AF51FFDA89C7F1AD22", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18", 16,  752);
    assert(strcmp("0485055FD4F6F0D963EF5AB9A5476982", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18", 16,  768);
    assert(strcmp("591FC66BCDA10E452B03D4551F6B62AC", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18", 16, 1008);
    assert(strcmp("2753CC83988AFA3E1688A1D3B42C9A02", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18", 16, 1024);
    assert(strcmp("93610D523D1D3F0062B3C2A3BBC7C7F0", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18", 16, 1520);
    assert(strcmp("96C248610AADEDFEAF8978C03DE8205A", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18", 16, 1536);
    assert(strcmp("0E317B3D1C73B9E9A4688F296D133A19", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18", 16, 2032);
    assert(strcmp("BDF0E6C3CCA5B5B9D533B69C56ADA120", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18", 16, 2048);
    assert(strcmp("88A218B6E2ECE1E6246D44C759D19B10", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18", 16, 3056);
    assert(strcmp("6866397E95C140534F94263421006E40", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18", 16, 3072);
    assert(strcmp("32CB0A1E9542C6B3B8B398ABC3B0F1D5", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18", 16, 4080);
    assert(strcmp("29A0B8AED54A132324C62E423F54B4C8", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18", 16, 4096);
    assert(strcmp("3CB0F3B5020A98B82AF9FE154484A168", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20", 16,    0);
    assert(strcmp("EAA6BD25880BF93D3F5D1E4CA2611D91", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20", 16,   16);
    assert(strcmp("CFA45C9F7E714B54BDFA80027CB14380", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20", 16,  240);
    assert(strcmp("114AE344DED71B35F2E60FEBAD727FD8", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20", 16,  256);
    assert(strcmp("02E1E7056B0F623900496422943E97B6", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20", 16,  496);
    assert(strcmp("91CB93C787964E10D9527D999C6F936B", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20", 16,  512);
    assert(strcmp("49B18B42F8E8367CBEB5EF104BA1C7CD", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20", 16,  752);
    assert(strcmp("87084B3BA700BADE955610672745B374", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20", 16,  768);
    assert(strcmp("E7A7B9E9EC540D5FF43BDB12792D1B35", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20", 16, 1008);
    assert(strcmp("C799B596738F6B018C76C74B1759BD90", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20", 16, 1024);
    assert(strcmp("7FEC5BFD9F9B89CE6548309092D7E958", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20", 16, 1520);
    assert(strcmp("40F250B26D1F096A4AFD4C340A588815", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20", 16, 1536);
    assert(strcmp("3E34135C79DB010200767651CF263073", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20", 16, 2032);
    assert(strcmp("F656ABCCF88DD827027B2CE917D464EC", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20", 16, 2048);
    assert(strcmp("18B62503BFBC077FBABB98F20D98AB34", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20", 16, 3056);
    assert(strcmp("8AED95EE5B0DCBFBEF4EB21D3A3F52F9", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20", 16, 3072);
    assert(strcmp("625A1AB00EE39A5327346BDDB01A9C18", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20", 16, 4080);
    assert(strcmp("A13A7C79C7E119B5AB0296AB28C300B9", output) == 0);
    free(output);

    output = arc4_hash("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20", 16, 4096);
    assert(strcmp("F3E4C0A2E02D1D01F7F0A74618AF2B48", output) == 0);
    free(output);

    output = arc4_hash("\x83\x32\x22\x77\x2a", 16,    0);
    assert(strcmp("80AD97BDC973DF8A2E879E92A497EFDA", output) == 0);
    free(output);

    output = arc4_hash("\x83\x32\x22\x77\x2a", 16,   16);
    assert(strcmp("20F060C2F2E5126501D3D4FEA10D5FC0", output) == 0);
    free(output);

    output = arc4_hash("\x83\x32\x22\x77\x2a", 16,  240);
    assert(strcmp("FAA148E99046181FEC6B2085F3B20ED9", output) == 0);
    free(output);

    output = arc4_hash("\x83\x32\x22\x77\x2a", 16,  256);
    assert(strcmp("F0DAF5BAB3D596839857846F73FBFE5A", output) == 0);
    free(output);

    output = arc4_hash("\x83\x32\x22\x77\x2a", 16,  496);
    assert(strcmp("1C7E2FC4639232FE297584B296996BC8", output) == 0);
    free(output);

    output = arc4_hash("\x83\x32\x22\x77\x2a", 16,  512);
    assert(strcmp("3DB9B249406CC8EDFFAC55CCD322BA12", output) == 0);
    free(output);

    output = arc4_hash("\x83\x32\x22\x77\x2a", 16,  752);
    assert(strcmp("E4F9F7E0066154BBD125B745569BC897", output) == 0);
    free(output);

    output = arc4_hash("\x83\x32\x22\x77\x2a", 16,  768);
    assert(strcmp("75D5EF262B44C41A9CF63AE14568E1B9", output) == 0);
    free(output);

    output = arc4_hash("\x83\x32\x22\x77\x2a", 16, 1008);
    assert(strcmp("6DA453DBF81E82334A3D8866CB50A1E3", output) == 0);
    free(output);

    output = arc4_hash("\x83\x32\x22\x77\x2a", 16, 1024);
    assert(strcmp("7828D074119CAB5C22B294D7A9BFA0BB", output) == 0);
    free(output);

    output = arc4_hash("\x83\x32\x22\x77\x2a", 16, 1520);
    assert(strcmp("ADB89CEA9A15FBE617295BD04B8CA05C", output) == 0);
    free(output);

    output = arc4_hash("\x83\x32\x22\x77\x2a", 16, 1536);
    assert(strcmp("6251D87FD4AAAE9A7E4AD5C217D3F300", output) == 0);
    free(output);

    output = arc4_hash("\x83\x32\x22\x77\x2a", 16, 2032);
    assert(strcmp("E7119BD6DD9B22AFE8F89585432881E2", output) == 0);
    free(output);

    output = arc4_hash("\x83\x32\x22\x77\x2a", 16, 2048);
    assert(strcmp("785B60FD7EC4E9FCB6545F350D660FAB", output) == 0);
    free(output);

    output = arc4_hash("\x83\x32\x22\x77\x2a", 16, 3056);
    assert(strcmp("AFECC037FDB7B0838EB3D70BCD268382", output) == 0);
    free(output);

    output = arc4_hash("\x83\x32\x22\x77\x2a", 16, 3072);
    assert(strcmp("DBC1A7B49D57358CC9FA6D61D73B7CF0", output) == 0);
    free(output);

    output = arc4_hash("\x83\x32\x22\x77\x2a", 16, 4080);
    assert(strcmp("6349D126A37AFCBA89794F9804914FDC", output) == 0);
    free(output);

    output = arc4_hash("\x83\x32\x22\x77\x2a", 16, 4096);
    assert(strcmp("BF42C3018C2F7C66BFDE524975768115", output) == 0);
    free(output);

    output = arc4_hash("\x19\x10\x83\x32\x22\x77\x2a", 16,    0);
    assert(strcmp("BC9222DBD3274D8FC66D14CCBDA6690B", output) == 0);
    free(output);

    output = arc4_hash("\x19\x10\x83\x32\x22\x77\x2a", 16,   16);
    assert(strcmp("7AE627410C9A2BE693DF5BB7485A63E3", output) == 0);
    free(output);

    output = arc4_hash("\x19\x10\x83\x32\x22\x77\x2a", 16,  240);
    assert(strcmp("3F0931AA03DEFB300F060103826F2A64", output) == 0);
    free(output);

    output = arc4_hash("\x19\x10\x83\x32\x22\x77\x2a", 16,  256);
    assert(strcmp("BEAA9EC8D59BB68129F3027C96361181", output) == 0);
    free(output);

    output = arc4_hash("\x19\x10\x83\x32\x22\x77\x2a", 16,  496);
    assert(strcmp("74E04DB46D28648D7DEE8A0064B06CFE", output) == 0);
    free(output);

    output = arc4_hash("\x19\x10\x83\x32\x22\x77\x2a", 16,  512);
    assert(strcmp("9B5E81C62FE023C55BE42F87BBF932B8", output) == 0);
    free(output);

    output = arc4_hash("\x19\x10\x83\x32\x22\x77\x2a", 16,  752);
    assert(strcmp("CE178FC1826EFECBC182F57999A46140", output) == 0);
    free(output);

    output = arc4_hash("\x19\x10\x83\x32\x22\x77\x2a", 16,  768);
    assert(strcmp("8BDF55CD55061C06DBA6BE11DE4A578A", output) == 0);
    free(output);

    output = arc4_hash("\x19\x10\x83\x32\x22\x77\x2a", 16, 1008);
    assert(strcmp("626F5F4DCE652501F3087D39C92CC349", output) == 0);
    free(output);

    output = arc4_hash("\x19\x10\x83\x32\x22\x77\x2a", 16, 1024);
    assert(strcmp("42DAAC6A8F9AB9A7FD137C6037825682", output) == 0);
    free(output);

    output = arc4_hash("\x19\x10\x83\x32\x22\x77\x2a", 16, 1520);
    assert(strcmp("CC03FDB79192A207312F53F5D4DC33D9", output) == 0);
    free(output);

    output = arc4_hash("\x19\x10\x83\x32\x22\x77\x2a", 16, 1536);
    assert(strcmp("F70F14122A1C98A3155D28B8A0A8A41D", output) == 0);
    free(output);

    output = arc4_hash("\x19\x10\x83\x32\x22\x77\x2a", 16, 2032);
    assert(strcmp("2A3A307AB2708A9C00FE0B42F9C2D6A1", output) == 0);
    free(output);

    output = arc4_hash("\x19\x10\x83\x32\x22\x77\x2a", 16, 2048);
    assert(strcmp("862617627D2261EAB0B1246597CA0AE9", output) == 0);
    free(output);

    output = arc4_hash("\x19\x10\x83\x32\x22\x77\x2a", 16, 3056);
    assert(strcmp("55F877CE4F2E1DDBBF8E13E2CDE0FDC8", output) == 0);
    free(output);

    output = arc4_hash("\x19\x10\x83\x32\x22\x77\x2a", 16, 3072);
    assert(strcmp("1B1556CB935F173337705FBB5D501FC1", output) == 0);
    free(output);

    output = arc4_hash("\x19\x10\x83\x32\x22\x77\x2a", 16, 4080);
    assert(strcmp("ECD0E96602BE7F8D5092816CCCF2C2E9", output) == 0);
    free(output);

    output = arc4_hash("\x19\x10\x83\x32\x22\x77\x2a", 16, 4096);
    assert(strcmp("027881FAB4993A1C262024A94FFF3F61", output) == 0);
    free(output);

    output = arc4_hash("\x64\x19\x10\x83\x32\x22\x77\x2a", 16,    0);
    assert(strcmp("BBF609DE9413172D07660CB680716926", output) == 0);
    free(output);

    output = arc4_hash("\x64\x19\x10\x83\x32\x22\x77\x2a", 16,   16);
    assert(strcmp("46101A6DAB43115D6C522B4FE93604A9", output) == 0);
    free(output);

    output = arc4_hash("\x64\x19\x10\x83\x32\x22\x77\x2a", 16,  240);
    assert(strcmp("CBE1FFF21C96F3EEF61E8FE0542CBDF0", output) == 0);
    free(output);

    output = arc4_hash("\x64\x19\x10\x83\x32\x22\x77\x2a", 16,  256);
    assert(strcmp("347938BFFA4009C512CFB4034B0DD1A7", output) == 0);
    free(output);

    output = arc4_hash("\x64\x19\x10\x83\x32\x22\x77\x2a", 16,  496);
    assert(strcmp("7867A786D00A7147904D76DDF1E520E3", output) == 0);
    free(output);

    output = arc4_hash("\x64\x19\x10\x83\x32\x22\x77\x2a", 16,  512);
    assert(strcmp("8D3E9E1CAEFCCCB3FBF8D18F64120B32", output) == 0);
    free(output);

    output = arc4_hash("\x64\x19\x10\x83\x32\x22\x77\x2a", 16,  752);
    assert(strcmp("942337F8FD76F0FAE8C52D7954810672", output) == 0);
    free(output);

    output = arc4_hash("\x64\x19\x10\x83\x32\x22\x77\x2a", 16,  768);
    assert(strcmp("B8548C10F51667F6E60E182FA19B30F7", output) == 0);
    free(output);

    output = arc4_hash("\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 1008);
    assert(strcmp("0211C7C6190C9EFD1237C34C8F2E06C4", output) == 0);
    free(output);

    output = arc4_hash("\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 1024);
    assert(strcmp("BDA64F65276D2AACB8F90212203A808E", output) == 0);
    free(output);

    output = arc4_hash("\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 1520);
    assert(strcmp("BD3820F732FFB53EC193E79D33E27C73", output) == 0);
    free(output);

    output = arc4_hash("\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 1536);
    assert(strcmp("D0168616861907D482E36CDAC8CF5749", output) == 0);
    free(output);

    output = arc4_hash("\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 2032);
    assert(strcmp("97B0F0F224B2D2317114808FB03AF7A0", output) == 0);
    free(output);

    output = arc4_hash("\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 2048);
    assert(strcmp("E59616E469787939A063CEEA9AF956D1", output) == 0);
    free(output);

    output = arc4_hash("\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 3056);
    assert(strcmp("C47E0DC1660919C11101208F9E69AA1F", output) == 0);
    free(output);

    output = arc4_hash("\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 3072);
    assert(strcmp("5AE4F12896B8379A2AAD89B5B553D6B0", output) == 0);
    free(output);

    output = arc4_hash("\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 4080);
    assert(strcmp("6B6B098D0C293BC2993D80BF0518B6D9", output) == 0);
    free(output);

    output = arc4_hash("\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 4096);
    assert(strcmp("8170CC3CCD92A698621B939DD38FE7B9", output) == 0);
    free(output);

    output = arc4_hash("\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16,    0);
    assert(strcmp("AB65C26EDDB287600DB2FDA10D1E605C", output) == 0);
    free(output);

    output = arc4_hash("\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16,   16);
    assert(strcmp("BB759010C29658F2C72D93A2D16D2930", output) == 0);
    free(output);

    output = arc4_hash("\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16,  240);
    assert(strcmp("B901E8036ED1C383CD3C4C4DD0A6AB05", output) == 0);
    free(output);

    output = arc4_hash("\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16,  256);
    assert(strcmp("3D25CE4922924C55F064943353D78A6C", output) == 0);
    free(output);

    output = arc4_hash("\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16,  496);
    assert(strcmp("12C1AA44BBF87E75E611F69B2C38F49B", output) == 0);
    free(output);

    output = arc4_hash("\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16,  512);
    assert(strcmp("28F2B3434B65C09877470044C6EA170D", output) == 0);
    free(output);

    output = arc4_hash("\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16,  752);
    assert(strcmp("BD9EF822DE5288196134CF8AF7839304", output) == 0);
    free(output);

    output = arc4_hash("\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16,  768);
    assert(strcmp("67559C23F052158470A296F725735A32", output) == 0);
    free(output);

    output = arc4_hash("\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 1008);
    assert(strcmp("8BAB26FBC2C12B0F13E2AB185EABF241", output) == 0);
    free(output);

    output = arc4_hash("\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 1024);
    assert(strcmp("31185A6D696F0CFA9B42808B38E132A2", output) == 0);
    free(output);

    output = arc4_hash("\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 1520);
    assert(strcmp("564D3DAE183C5234C8AF1E51061C44B5", output) == 0);
    free(output);

    output = arc4_hash("\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 1536);
    assert(strcmp("3C0778A7B5F72D3C23A3135C7D67B9F4", output) == 0);
    free(output);

    output = arc4_hash("\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 2032);
    assert(strcmp("F34369890FCF16FB517DCAAE4463B2DD", output) == 0);
    free(output);

    output = arc4_hash("\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 2048);
    assert(strcmp("02F31C81E8200731B899B028E791BFA7", output) == 0);
    free(output);

    output = arc4_hash("\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 3056);
    assert(strcmp("72DA646283228C14300853701795616F", output) == 0);
    free(output);

    output = arc4_hash("\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 3072);
    assert(strcmp("4E0A8C6F7934A788E2265E81D6D0C8F4", output) == 0);
    free(output);

    output = arc4_hash("\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 4080);
    assert(strcmp("438DD5EAFEA0111B6F36B4B938DA2A68", output) == 0);
    free(output);

    output = arc4_hash("\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 4096);
    assert(strcmp("5F6BFC73815874D97100F086979357D8", output) == 0);
    free(output);

    output = arc4_hash("\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16,    0);
    assert(strcmp("720C94B63EDF44E131D950CA211A5A30", output) == 0);
    free(output);

    output = arc4_hash("\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16,   16);
    assert(strcmp("C366FDEACF9CA80436BE7C358424D20B", output) == 0);
    free(output);

    output = arc4_hash("\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16,  240);
    assert(strcmp("B3394A40AABF75CBA42282EF25A0059F", output) == 0);
    free(output);

    output = arc4_hash("\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16,  256);
    assert(strcmp("4847D81DA4942DBC249DEFC48C922B9F", output) == 0);
    free(output);

    output = arc4_hash("\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16,  496);
    assert(strcmp("08128C469F275342ADDA202B2B58DA95", output) == 0);
    free(output);

    output = arc4_hash("\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16,  512);
    assert(strcmp("970DACEF40AD98723BAC5D6955B81761", output) == 0);
    free(output);

    output = arc4_hash("\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16,  752);
    assert(strcmp("3CB89993B07B0CED93DE13D2A11013AC", output) == 0);
    free(output);

    output = arc4_hash("\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16,  768);
    assert(strcmp("EF2D676F1545C2C13DC680A02F4ADBFE", output) == 0);
    free(output);

    output = arc4_hash("\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 1008);
    assert(strcmp("B60595514F24BC9FE522A6CAD7393644", output) == 0);
    free(output);

    output = arc4_hash("\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 1024);
    assert(strcmp("B515A8C5011754F59003058BDB81514E", output) == 0);
    free(output);

    output = arc4_hash("\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 1520);
    assert(strcmp("3C70047E8CBC038E3B9820DB601DA495", output) == 0);
    free(output);

    output = arc4_hash("\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 1536);
    assert(strcmp("1175DA6EE756DE46A53E2B075660B770", output) == 0);
    free(output);

    output = arc4_hash("\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 2032);
    assert(strcmp("00A542BBA02111CC2C65B38EBDBA587E", output) == 0);
    free(output);

    output = arc4_hash("\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 2048);
    assert(strcmp("5865FDBB5B48064104E830B380F2AEDE", output) == 0);
    free(output);

    output = arc4_hash("\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 3056);
    assert(strcmp("34B21AD2AD44E999DB2D7F0863F0D9B6", output) == 0);
    free(output);

    output = arc4_hash("\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 3072);
    assert(strcmp("84A9218FC36E8A5F2CCFBEAE53A27D25", output) == 0);
    free(output);

    output = arc4_hash("\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 4080);
    assert(strcmp("A2221A11B833CCB498A59540F0545F4A", output) == 0);
    free(output);

    output = arc4_hash("\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 4096);
    assert(strcmp("5BBEB4787D59E5373FDBEA6C6F75C29B", output) == 0);
    free(output);

    output = arc4_hash("\xc1\x09\x16\x39\x08\xeb\xe5\x1d\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16,    0);
    assert(strcmp("54B64E6B5A20B5E2EC84593DC7989DA7", output) == 0);
    free(output);

    output = arc4_hash("\xc1\x09\x16\x39\x08\xeb\xe5\x1d\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16,   16);
    assert(strcmp("C135EEE237A85465FF97DC03924F45CE", output) == 0);
    free(output);

    output = arc4_hash("\xc1\x09\x16\x39\x08\xeb\xe5\x1d\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16,  240);
    assert(strcmp("CFCC922FB4A14AB45D6175AABBF2D201", output) == 0);
    free(output);

    output = arc4_hash("\xc1\x09\x16\x39\x08\xeb\xe5\x1d\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16,  256);
    assert(strcmp("837B87E2A446AD0EF798ACD02B94124F", output) == 0);
    free(output);

    output = arc4_hash("\xc1\x09\x16\x39\x08\xeb\xe5\x1d\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16,  496);
    assert(strcmp("17A6DBD664926A0636B3F4C37A4F4694", output) == 0);
    free(output);

    output = arc4_hash("\xc1\x09\x16\x39\x08\xeb\xe5\x1d\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16,  512);
    assert(strcmp("4A5F9F26AEEED4D4A25F632D305233D9", output) == 0);
    free(output);

    output = arc4_hash("\xc1\x09\x16\x39\x08\xeb\xe5\x1d\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16,  752);
    assert(strcmp("80A3D01EF00C8E9A4209C17F4EEB358C", output) == 0);
    free(output);

    output = arc4_hash("\xc1\x09\x16\x39\x08\xeb\xe5\x1d\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16,  768);
    assert(strcmp("D15E7D5FFAAABC0207BF200A117793A2", output) == 0);
    free(output);

    output = arc4_hash("\xc1\x09\x16\x39\x08\xeb\xe5\x1d\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 1008);
    assert(strcmp("349682BF588EAA52D0AA1560346AEAFA", output) == 0);
    free(output);

    output = arc4_hash("\xc1\x09\x16\x39\x08\xeb\xe5\x1d\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 1024);
    assert(strcmp("F5854CDB76C889E3AD63354E5F7275E3", output) == 0);
    free(output);

    output = arc4_hash("\xc1\x09\x16\x39\x08\xeb\xe5\x1d\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 1520);
    assert(strcmp("532C7CECCB39DF3236318405A4B1279C", output) == 0);
    free(output);

    output = arc4_hash("\xc1\x09\x16\x39\x08\xeb\xe5\x1d\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 1536);
    assert(strcmp("BAEFE6D9CEB651842260E0D1E05E3B90", output) == 0);
    free(output);

    output = arc4_hash("\xc1\x09\x16\x39\x08\xeb\xe5\x1d\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 2032);
    assert(strcmp("E82D8C6DB54E3C633F581C952BA04207", output) == 0);
    free(output);

    output = arc4_hash("\xc1\x09\x16\x39\x08\xeb\xe5\x1d\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 2048);
    assert(strcmp("4B16E50ABD381BD70900A9CD9A62CB23", output) == 0);
    free(output);

    output = arc4_hash("\xc1\x09\x16\x39\x08\xeb\xe5\x1d\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 3056);
    assert(strcmp("3682EE33BD148BD9F58656CD8F30D9FB", output) == 0);
    free(output);

    output = arc4_hash("\xc1\x09\x16\x39\x08\xeb\xe5\x1d\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 3072);
    assert(strcmp("1E5A0B8475045D9B20B2628624EDFD9E", output) == 0);
    free(output);

    output = arc4_hash("\xc1\x09\x16\x39\x08\xeb\xe5\x1d\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 4080);
    assert(strcmp("63EDD684FB826282FE528F9C0E9237BC", output) == 0);
    free(output);

    output = arc4_hash("\xc1\x09\x16\x39\x08\xeb\xe5\x1d\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 4096);
    assert(strcmp("E4DD2E98D6960FAE0B43545456743391", output) == 0);
    free(output);

    output = arc4_hash("\x1a\xda\x31\xd5\xcf\x68\x82\x21\xc1\x09\x16\x39\x08\xeb\xe5\x1d\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16,    0);
    assert(strcmp("DD5BCB0018E922D494759D7C395D02D3", output) == 0);
    free(output);

    output = arc4_hash("\x1a\xda\x31\xd5\xcf\x68\x82\x21\xc1\x09\x16\x39\x08\xeb\xe5\x1d\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16,   16);
    assert(strcmp("C8446F8F77ABF737685353EB89A1C9EB", output) == 0);
    free(output);

    output = arc4_hash("\x1a\xda\x31\xd5\xcf\x68\x82\x21\xc1\x09\x16\x39\x08\xeb\xe5\x1d\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16,  240);
    assert(strcmp("AF3E30F9C095045938151575C3FB9098", output) == 0);
    free(output);

    output = arc4_hash("\x1a\xda\x31\xd5\xcf\x68\x82\x21\xc1\x09\x16\x39\x08\xeb\xe5\x1d\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16,  256);
    assert(strcmp("F8CB6274DB99B80B1D2012A98ED48F0E", output) == 0);
    free(output);

    output = arc4_hash("\x1a\xda\x31\xd5\xcf\x68\x82\x21\xc1\x09\x16\x39\x08\xeb\xe5\x1d\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16,  496);
    assert(strcmp("25C3005A1CB85DE076259839AB7198AB", output) == 0);
    free(output);

    output = arc4_hash("\x1a\xda\x31\xd5\xcf\x68\x82\x21\xc1\x09\x16\x39\x08\xeb\xe5\x1d\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16,  512);
    assert(strcmp("9DCBC183E8CB994B727B75BE3180769C", output) == 0);
    free(output);

    output = arc4_hash("\x1a\xda\x31\xd5\xcf\x68\x82\x21\xc1\x09\x16\x39\x08\xeb\xe5\x1d\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16,  752);
    assert(strcmp("A1D3078DFA9169503ED9D4491DEE4EB2", output) == 0);
    free(output);

    output = arc4_hash("\x1a\xda\x31\xd5\xcf\x68\x82\x21\xc1\x09\x16\x39\x08\xeb\xe5\x1d\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16,  768);
    assert(strcmp("8514A5495858096F596E4BCD66B10665", output) == 0);
    free(output);

    output = arc4_hash("\x1a\xda\x31\xd5\xcf\x68\x82\x21\xc1\x09\x16\x39\x08\xeb\xe5\x1d\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 1008);
    assert(strcmp("5F40D59EC1B03B33738EFA60B2255D31", output) == 0);
    free(output);

    output = arc4_hash("\x1a\xda\x31\xd5\xcf\x68\x82\x21\xc1\x09\x16\x39\x08\xeb\xe5\x1d\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 1024);
    assert(strcmp("3477C7F764A41BACEFF90BF14F92B7CC", output) == 0);
    free(output);

    output = arc4_hash("\x1a\xda\x31\xd5\xcf\x68\x82\x21\xc1\x09\x16\x39\x08\xeb\xe5\x1d\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 1520);
    assert(strcmp("AC4E95368D99B9EB78B8DA8F81FFA795", output) == 0);
    free(output);

    output = arc4_hash("\x1a\xda\x31\xd5\xcf\x68\x82\x21\xc1\x09\x16\x39\x08\xeb\xe5\x1d\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 1536);
    assert(strcmp("8C3C13F8C2388BB73F38576E65B7C446", output) == 0);
    free(output);

    output = arc4_hash("\x1a\xda\x31\xd5\xcf\x68\x82\x21\xc1\x09\x16\x39\x08\xeb\xe5\x1d\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 2032);
    assert(strcmp("13C4B9C1DFB66579EDDD8A280B9F7316", output) == 0);
    free(output);

    output = arc4_hash("\x1a\xda\x31\xd5\xcf\x68\x82\x21\xc1\x09\x16\x39\x08\xeb\xe5\x1d\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 2048);
    assert(strcmp("DDD27820550126698EFAADC64B64F66E", output) == 0);
    free(output);

    output = arc4_hash("\x1a\xda\x31\xd5\xcf\x68\x82\x21\xc1\x09\x16\x39\x08\xeb\xe5\x1d\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 3056);
    assert(strcmp("F08F2E66D28ED143F3A237CF9DE73559", output) == 0);
    free(output);

    output = arc4_hash("\x1a\xda\x31\xd5\xcf\x68\x82\x21\xc1\x09\x16\x39\x08\xeb\xe5\x1d\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 3072);
    assert(strcmp("9EA36C525531B880BA124334F57B0B70", output) == 0);
    free(output);

    output = arc4_hash("\x1a\xda\x31\xd5\xcf\x68\x82\x21\xc1\x09\x16\x39\x08\xeb\xe5\x1d\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 4080);
    assert(strcmp("D5A39E3DFCC50280BAC4A6B5AA0DCA7D", output) == 0);
    free(output);

    output = arc4_hash("\x1a\xda\x31\xd5\xcf\x68\x82\x21\xc1\x09\x16\x39\x08\xeb\xe5\x1d\xeb\xb4\x62\x27\xc6\xcc\x8b\x37\x64\x19\x10\x83\x32\x22\x77\x2a", 16, 4096);
    assert(strcmp("370B1C1FE655916D97FD0D47CA1D72B8", output) == 0);
    free(output);
}

void CLM_ITER_TEST(bool verbose) {

    printf("\nTesting CLM_ITER...\n\n");

    size_t *tuple   = NULL;
    size_t  base    = 4;
    size_t  length  = 3;
    size_t  BASE[4] = {2, 3, 4};
    size_t  sample  = 1000000;
    size_t  i, j, k;

    /* Products */
    if (verbose) {
        printf("\n\tProducts(%zu, { ", length);
        for (j = 0; j < length; j++) { printf("%zu ", BASE[j]); }
        printf("}):\n");
    }
    iter_next_prod(&tuple, length, BASE);
    for (i = 0; tuple; i++) {
        for (j = 0; j < length; j++) { assert(tuple[j] < BASE[j]); }
        if (verbose) {
            printf("\t\t%2zu: [ ", i+1);
            for (j = 0; j < length; j++) { printf("%zu ", tuple[j]); }
            printf("]\n");
        }
        iter_next_prod(&tuple, length, BASE);
    }
    
    /* Permutations */
    if (verbose) { printf("\n\tPermutations(%zu, %zu):\n", length, base); }
    iter_next_perm(&tuple, length, base, false);
    for (i = 0; tuple; i++) {
        for (j = 0; j < length; j++) { assert(tuple[j] < base); }
        for (j = 0; j < length-1; j++) {
            for (k = j+1; k < length; k++) { assert(tuple[j] != tuple[k]); }
        }
        if (verbose) {
            printf("\t\t%2zu: [ ", i+1);
            for (j = 0; j < length; j++) { printf("%zu ", tuple[j]); }
            printf("]\n");
        }
        iter_next_perm(&tuple, length, base, false);
    }

    /* Permutations with replacement */
    if (verbose) { printf("\n\tPermutations_Replacement(%zu, %zu):\n", length, base); }
    iter_next_perm(&tuple, length, base, true);
    for (i = 0; tuple; i++) {
        for (j = 0; j < length; j++) { assert(tuple[j] < base); }
        if (verbose) {
            printf("\t\t%2zu: [ ", i+1);
            for (j = 0; j < length; j++) { printf("%zu ", tuple[j]); }
            printf("]\n");
        }
        iter_next_perm(&tuple, length, base, true);
    }

    /* Combinations */
    if (verbose) { printf("\n\tCombinations(%zu, %zu):\n", length, base); }
    iter_next_comb(&tuple, length, base, false);
    for (i = 0; tuple; i++) {
        for (j = 0; j < length; j++) { assert(tuple[j]   < base);     }
        for (j = 1; j < length; j++) { assert(tuple[j-1] < tuple[j]); }
        if (verbose) {
            printf("\t\t%2zu: [ ", i+1);
            for (j = 0; j < length; j++) { printf("%zu ", tuple[j]); }
            printf("]\n");
        }
        iter_next_comb(&tuple, length, base, false);
    }

    /* Combinations with replacement */
    if (verbose) { printf("\n\tCombinations_Replacement(%zu, %zu):\n", length, base); }
    iter_next_comb(&tuple, length, base, true);
    for (i = 0; tuple; i++) {
        for (j = 0; j < length; j++) { assert(tuple[j]   <  base);     }
        for (j = 1; j < length; j++) { assert(tuple[j-1] <= tuple[j]); }
        if (verbose) {
            printf("\t\t%2zu: [ ", i+1);
            for (j = 0; j < length; j++) { printf("%zu ", tuple[j]); }
            printf("]\n");
        }
        iter_next_comb(&tuple, length, base, true);
    }


    srand(time(NULL));

    /* Random Products */
    if (verbose) {
        printf("\n\tRandom Products(%zu, { ", length);
        for (j = 0; j < length; j++) { printf("%zu ", BASE[j]); }
        printf("}):\n");
    }
    for (i = 0; i < sample; i++) {
        iter_rand_prod(&tuple, length, BASE);
        assert(tuple != NULL);
        for (j = 0; j < length; j++) { assert(tuple[j] < BASE[j]); }
        if (verbose && i < 10) {
            printf("\t\t%2zu/%zu: [ ", i+1, sample);
            for (j = 0; j < length; j++) { printf("%zu ", tuple[j]); }
            printf("]\n");
        }
        free(tuple);
        tuple = NULL;
    }
    if (verbose && sample > 10) { printf("\t\t...\n"); }

    /* Random Permutations */
    if (verbose) { printf("\n\tRandom Permutations(%zu, %zu):\n", length, base); }
    for (i = 0; i < sample; i++) {
        iter_rand_perm(&tuple, length, base, false);
        assert(tuple != NULL);
        for (j = 0; j < length; j++) { assert(tuple[j] < base); }
        for (j = 0; j < length-1; j++) {
            for (k = j+1; k < length; k++) { assert(tuple[j] != tuple[k]); }
        }
        if (verbose && i < 10) {
            printf("\t\t%2zu/%zu: [ ", i+1, sample);
            for (j = 0; j < length; j++) { printf("%zu ", tuple[j]); }
            printf("]\n");
        }
        free(tuple);
        tuple = NULL;
    }
    if (verbose && sample > 10) { printf("\t\t...\n"); }

    /* Random Permutations with replacement */
    if (verbose) { printf("\n\tRandom Permutations_Replacement(%zu, %zu):\n", length, base); }
    for (i = 0; i < sample; i++) {
        iter_rand_perm(&tuple, length, base, true);
        assert(tuple != NULL);
        for (j = 0; j < length; j++) { assert(tuple[j] < base); }
        if (verbose && i < 10) {
            printf("\t\t%2zu/%zu: [ ", i+1, sample);
            for (j = 0; j < length; j++) { printf("%zu ", tuple[j]); }
            printf("]\n");
        }
        free(tuple);
        tuple = NULL;
    }
    if (verbose && sample > 10) { printf("\t\t...\n"); }

    /* Random Combinations */
    if (verbose) { printf("\n\tRandom Combinations(%zu, %zu):\n", length, base); }
    for (i = 0; i < sample; i++) {
        iter_rand_comb(&tuple, length, base, false);
        assert(tuple != NULL);
        for (j = 0; j < length; j++) { assert(tuple[j]   < base);     }
        for (j = 1; j < length; j++) { assert(tuple[j-1] < tuple[j]); }
        if (verbose && i < 10) {
            printf("\t\t%2zu/%zu: [ ", i+1, sample);
            for (j = 0; j < length; j++) { printf("%zu ", tuple[j]); }
            printf("]\n");
        }
        free(tuple);
        tuple = NULL;
    }
    if (verbose && sample > 10) { printf("\t\t...\n"); }

    /* Random Combinations with replacement */
    if (verbose) { printf("\n\tRandom Combinations_Replacement(%zu, %zu):\n", length, base); }
    for (i = 0; i < sample; i++) {
        iter_rand_comb(&tuple, length, base, true);
        assert(tuple != NULL);
        for (j = 0; j < length; j++) { assert(tuple[j]   <  base);     }
        for (j = 1; j < length; j++) { assert(tuple[j-1] <= tuple[j]); }
        if (verbose && i < 10) {
            printf("\t\t%2zu/%zu: [ ", i+1, sample);
            for (j = 0; j < length; j++) { printf("%zu ", tuple[j]); }
            printf("]\n");
        }
        free(tuple);
        tuple = NULL;
    }
    if (verbose && sample > 10) { printf("\t\t...\n"); }
}

void CLM_FRACTAL_TEST(bool verbose) {

    printf("\nTesting CLM_ITER...\n\n");

    if (verbose) { printf(" "); }

    size_t dim  = 3;
    size_t bits = 2;
    size_t max_coord = 1<<bits;
    size_t max_H = 1<<(bits*dim);
    size_t H, HH, coord[dim];

    for (size_t i = 0; i < max_coord; i++) {
        for (size_t j = 0; j < max_coord; j++) {
            for (size_t k = 0; k < max_coord; k++) {
                coord[0] = i;
                coord[1] = j;
                coord[2] = k;
                fractal_coord_to_h(dim, bits, &H, coord);
                //printf("(%zu, %zu, %zu) -> H(%zu)\n", coord[0], coord[1], coord[2], H);
                fractal_h_to_coord(dim, bits, &H, coord);
                assert(i == coord[0]);
                assert(j == coord[1]);
                assert(k == coord[2]);
            }
        }
    }

    for (size_t i = 0; i < max_coord; i++) {
        for (size_t j = 0; j < max_coord; j++) {
            for (size_t k = 0; k < max_coord; k++) {
                coord[0] = i;
                coord[1] = j;
                coord[2] = k;
                fractal_coord_to_z(dim, bits, &H, coord);
                //printf("(%zu, %zu, %zu) -> H(%zu)\n", coord[0], coord[1], coord[2], H);
                fractal_z_to_coord(dim, bits, &H, coord);
                assert(i == coord[0]);
                assert(j == coord[1]);
                assert(k == coord[2]);
            }
        }
    }

    for (size_t H = 0; H < max_H; H++) {
        fractal_h_to_coord(dim, bits, &H, coord);
        //printf("H(%zu) -> (%zu, %zu, %zu)\n", H, coord[0], coord[1], coord[2]);
        fractal_coord_to_h(dim, bits, &HH, coord);
        assert(H == HH);
    }

    for (size_t H = 0; H < max_H; H++) {
        fractal_z_to_coord(dim, bits, &H, coord);
        //printf("H(%zu) -> (%zu, %zu, %zu)\n", H, coord[0], coord[1], coord[2]);
        fractal_coord_to_z(dim, bits, &HH, coord);
        assert(H == HH);
    }

    /*printf("\n\n");

    dim = 2;
    bits = 3;
    max_coord = 1u<<bits;
    for (size_t i = 0; i < max_coord; i++) {
        for (size_t j = 0; j < max_coord; j++) {
            coord[0] = j;
            coord[1] = max_coord-i-1;
            fractal_coord_to_z(dim, bits, &H, coord);
            printf("%3zu ", H);
        }
        printf("\n");
    }

    printf("\n\n"); */

    dim = 2;
    bits = 3;
    max_coord = 1u<<bits;
    for (size_t i = 0; i < max_coord; i++) {
        for (size_t j = 0; j < max_coord; j++) {
            coord[0] = j;
            coord[1] = max_coord-i-1;
            fractal_coord_to_h(dim, bits, &H, coord);
            printf("%3zu ", H);
        }
        printf("\n");
    }

    /*printf("\n\n");
    bits = 4;
    max_coord = 1u<<bits;
    for (size_t i = 0; i < max_coord; i++) {
        printf("%3zu ", fractal_van_der_corput(2, bits, fractal_van_der_corput(2, bits, i)));
        assert(i == fractal_van_der_corput(2, bits, fractal_van_der_corput(2, bits, i)));
    }
    printf("\n");
    for (size_t i = 0; i < max_coord; i++) {
        printf("%3zu ", fractal_van_der_corput(2, bits, i));
    }
    printf("\n\n");


    bits = 4;
    max_coord = 1u<<bits;
    for (size_t i = 0; i < max_coord; i++) {
        fractal_z_to_coord(1, bits, &i, &H);
        printf("%3zu ", H);
    }
    printf("\n");*/


}

void CLM_ARRAY_TEST(bool verbose) {

    printf("\nTesting CLM_ARRAY...\n\n");

    size_t size = 100000;

    size_t i,j;
    array A = array_new(size);
    assert(A);
    assert(size > 20);

    for (i = 0; i < size; i++) { A[i] = i; }
    if (verbose) {
        printf("\tA = [ ");
        for (i = 0; i < 20; i++) { printf("%zu, ",A[i]); }
        printf("...]\n");
    }

    /* Test Shuffle */
    array_shuffle(A, size);
    if (verbose) {
        printf("\tA = [ ");
        for (i = 0; i < 20; i++) { printf("%zu, ",A[i]); }
        printf("...]\n");
    }

    /* Test Select */
    for (i = 0; i < 100; i++) {
        array_shuffle(A, size);
        j = rand_size_t(size);
        assert(array_select(A, size, j) == j);
    }

    /* Test sort */
    for (j = 0; j < 100; j++) {
        array_shuffle(A, size);
        array_sort(A, size);
        for (i = 0; i < size-1; i++) { assert(A[i] <= A[i+1]); }
    }

    /* Test Binary Search */
    assert(size % 4 == 0);
    for (i = 0, j = 1; i+3 < size; i += 4) { A[i]=A[i+1]=A[i+2]=A[i+3]=j++;}
    for (i = 0; i < A[size-1]; i++) {
        assert(array_bisect(A, size, i) % 4 == 0);
    }

    free(A);
}

void CLM_CLIST_TEST(bool verbose) {

    printf("\nTesting CLM_CLIST...\n\n");

    size_t MAX_SIZE = 1000;
    size_t i;
    clist L = NULL;

    if (verbose) {
        for (i = 0; i < 20; i++) {
            clist_push_back(&L, i);
            assert(clist_verify(L));
        }
        clist_print(L, "\tRegular:  ");
        assert(clist_front(&L) == 0);
        assert(clist_back(&L) == 19);

        i = 0;
        while (L) {
            assert(clist_pop_front(&L) == i++);
            assert(clist_verify(L));
        }
        assert(L == NULL);
        assert(i == 20);
    }

    for (i = 0; i < MAX_SIZE; i++) {
        clist_push_front(&L, i);
        assert(L);
        assert(clist_verify(L));
        assert(clist_front(&L) == i);
        assert(clist_back(&L)  == 0);
    }

    for (i = 0; i < MAX_SIZE; i++) {
        assert(clist_front(&L) == MAX_SIZE-i-1);
        assert(clist_back(&L)  == 0);
        assert(clist_pop_front(&L) == MAX_SIZE-i-1);
        assert(clist_verify(L));
    }

    assert(L == NULL);
}

void CLM_STREE_TEST(bool verbose) {

    printf("\nTesting CLM_STREE...\n\n");

    size_t MAX_SIZE = 1000000;
    size_t MAX_KEY  = 64;
    size_t i, j;
    stree T = NULL;

    for (i = 0; i < MAX_SIZE; i++) {
        j = rand_size_t(MAX_KEY);
        if (stree_find(&T, j)) {
            assert(j == stree_root(&T));
            assert(j == stree_pop(&T));
            assert(stree_verify(T, NULL, NULL));
            assert(stree_find(&T, j) == false);
        } else {
            if (stree_insert(&T, j)) {
                assert(stree_verify(T, NULL, NULL));
                assert(stree_find(&T, j) == true);
            }
        }
        if (verbose && (i%(MAX_SIZE/10) == 0)) {
            printf("\n");
            stree_print(T, false, "\t");
            printf("\n");
        }
    }

    while (T) { stree_pop(&T); }
    assert(T == NULL);


    for (i = 1; i <= MAX_KEY; i++) { stree_insert(&T, i); }
    assert(stree_verify(T, NULL, NULL));
    assert(--i == stree_max(&T));
    assert(stree_verify(T, NULL, NULL));
    while (stree_prev(&T)) {
        assert(--i == stree_root(&T));
        assert(stree_verify(T, NULL, NULL));
    }
    assert(i++ == stree_min(&T));
    assert(stree_verify(T, NULL, NULL));
    while (stree_next(&T)) {
        assert(i++ == stree_root(&T));
        assert(stree_verify(T, NULL, NULL));
    }

    while (T) { stree_pop(&T); }
    assert(T == NULL);
}

void CLM_WTREE_TEST(bool verbose) {

    printf("\nTesting CLM_WTREE...\n\n");

    size_t MAX_SIZE = 1000000;
    size_t MAX_KEY  = 1<<8;
    size_t i, j, rank, size = 0;
    wtree T = NULL;

    for (i = 0; i < MAX_SIZE; i++) {
        j    = rand_size_t(MAX_KEY);
        rank = wtree_find(&T, j);
        if (rank) {
            assert(j == wtree_select(&T, rank));
            assert(j == wtree_remove(&T, rank));
            assert(wtree_verify(T, NULL, NULL));
            assert(wtree_find(&T, j) == 0);
            assert(wtree_size(&T) == --size);
        } else {
            rank = wtree_insert(&T, j);
            assert(wtree_find(&T, j) == rank);
            if (rank) {
                assert(wtree_verify(T, NULL, NULL));
                assert(wtree_size(&T) == ++size);
            }
        }
        if (verbose && (i%(MAX_SIZE/10) == 0)) {
            printf("\n");
            wtree_print(T, false, "\t");
            printf("\n");
        }
    }

    while (T) { wtree_remove(&T, 1); }
    assert(T == NULL);
}

/** MAIN ****************************************************************** **/

int main (void) {

    const bool verbose = true;

    CLM_TIME_TEST(verbose);
    CLM_RAND_TEST(verbose);
    CLM_PRINTF_TEST(verbose);
    CLM_ARC4_TEST(verbose);
    CLM_ITER_TEST(verbose);
    //CLM_FRACTAL_TEST(verbose);
    CLM_ARRAY_TEST(verbose);
    CLM_CLIST_TEST(verbose);
    CLM_STREE_TEST(verbose);
    CLM_WTREE_TEST(verbose);

    printf("\nAll tests passing!\n\n");

    return 0;
}
