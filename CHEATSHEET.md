
# CLM\_LIBS CHEAT SHEET

```c
#define CLM_LIBS 20240815


#define IMPORT_CLM_TIME(prefix)

    double  time_elapsed(clock_t crono);
    void    time_pause(char* message);
    char   *time_stamp(int format);

#define IMPORT_CLM_RAND(prefix)

    int     rand_int(int n);
    size_t  rand_size_t(size_t n);
    double  rand_double(double n);
    double  rand_halton(size_t base, size_t n);
    void    rand_color(int *r, int *g, int *b);

#define IMPORT_CLM_PRINTF(prefix)

    void    printf_reset();
    void    printf_delete();
    void    printf_set_bold();
    void    printf_set_light();
    void    printf_set_strike();
    void    printf_set_underline();
    void    printf_move(int dx, int dy);
    void    printf_set_text_grey(int grey);
    void    printf_set_back_grey(int grey);
    void    printf_set_text_color(int r, int g, int b);
    void    printf_set_back_color(int r, int g, int b);

#define IMPORT_CLM_HASH(prefix)

    uint32_t hash_mix32(uint32_t h);
    uint32_t hash_unmix32(uint32_t h);
    uint64_t hash_mix64(uint64_t h);
    uint64_t hash_unmix64(uint64_t h);

#define IMPORT_CLM_DAMM(prefix)

    char    damm_dec(char *txt);
    char    damm_hex(char *txt);

#define IMPORT_CLM_ARC4(prefix)

    char   *arc4_hash(char *txt, size_t length, size_t drop);
    char   *arc4_encrypt(char *txt, char *key, size_t drop);
    char   *arc4_decrypt(char *txt, char *key, size_t drop);

#define IMPORT_CLM_ITER(prefix)

    void    iter_rand_prod(size_t **prod, size_t length, size_t *base);
    void    iter_next_prod(size_t **prod, size_t length, size_t *base);
    void    iter_rand_perm(size_t **perm, size_t length, size_t base, bool rep);
    void    iter_next_perm(size_t **perm, size_t length, size_t base, bool rep);
    void    iter_rand_comb(size_t **comb, size_t length, size_t base, bool rep);
    void    iter_next_comb(size_t **comb, size_t length, size_t base, bool rep);

#define IMPORT_CLM_FRACTAL(prefix)

    size_t  fractal_van_der_corput(size_t base, size_t digits, size_t n);
    void    fractal_lebesgue_coord(size_t dim, size_t bits, size_t *L);
    void    fractal_lebesgue_index(size_t dim, size_t bits, size_t *L);
    void    fractal_hilbert_coord(size_t dim, size_t bits, size_t *H);
    void    fractal_hilbert_index(size_t dim, size_t bits, size_t *H);

#define IMPORT_CLM_DISJOINT(prefix)

    size_t *disjoint_new(size_t max_size);
    size_t  disjoint_root(size_t *sets, size_t i);
    size_t  disjoint_merge(size_t *sets, size_t i, size_t j);

#define IMPORT_CLM_ARRAY(type, less, prefix)

    typedef type *array;

    array   array_new(size_t length);
    void    array_sort(array A, size_t length);
    void    array_shuffle(array A, size_t length);
    type    array_select(array A, size_t length, size_t rank);
    size_t  array_bisect(array A, size_t length, type data);

#define IMPORT_CLM_CLIST(type, prefix)

    typedef struct clist_s {
        struct clist_s *next;
        type            data;
    } clist_s, *clist;

    bool    clist_push_front(clist *list, type data);
    bool    clist_push_back(clist *list, type data);
    type    clist_pop_front(clist *list);
    type    clist_front(clist *list);
    type    clist_back(clist *list);

#define IMPORT_CLM_STREE(type, less, prefix)

    typedef struct stree_s {
        struct stree_s *left;
        struct stree_s *right;
        type            data;
    } stree_s, *stree;

    type    stree_root(stree *tree);
    type    stree_min(stree *tree);
    type    stree_max(stree *tree);
    type    stree_pop(stree *tree);
    bool    stree_next(stree *tree);
    bool    stree_prev(stree *tree);
    bool    stree_find(stree *tree, type data);
    bool    stree_insert(stree *tree, type data);

#define IMPORT_CLM_WTREE(type, less, prefix)

    typedef struct wtree_s {
      struct wtree_s *left;
      struct wtree_s *right;
      size_t          size;
      type            data;
    } wtree_s, *wtree;

    size_t  wtree_size(wtree *tree);
    size_t  wtree_find(wtree *tree, type data);
    size_t  wtree_insert(wtree *tree, type data);
    type    wtree_select(wtree *tree, size_t rank);
    type    wtree_remove(wtree *tree, size_t rank);
```

