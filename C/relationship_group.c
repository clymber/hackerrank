#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define PERSON_CNT 6

static char* persons[PERSON_CNT] = {
    "101001",
    "010000",
    "101010",
    "000100",
    "001011",
    "100011"
};

static char* persons2[PERSON_CNT] = {
    "100000",
    "010000",
    "001000",
    "000100",
    "000010",
    "000001"
};

static void dump_persons(char* p[], int count) {
    int i = 0;
    for (i = 0; i < count; ++i) {
        if (p[i]) {
            printf("%s\n", p[i]);
        }
    }
    printf("\n");
}

static void mfree_groups(int count, char** groups) {
    assert(groups);

    int i = 0;
    for (i = 0; i < count; ++i) {
        if (groups[i] != NULL) {
            free(groups[i]);
            groups[i] = NULL;
        }
    }

    free(groups);
}

static char** malloc_groups(int count, char* p[]) {
    int i = 0;
    char** groups = (char**)calloc(count, sizeof(char*));
    if (groups == NULL) {
        perror("allocate memory for groups failed.\n");
        return NULL;
    }

    for (i = 0; i < count; ++i) {
        groups[i] = strndup(p[i], count);
        if (groups == NULL) {
            fprintf(stderr, "string duplication failed: %s\n", p[i]);
            mfree_groups(count, groups);
            return NULL;
        }
    }

    return groups;
}

static bool is_relative(char* lhs, char* rhs, int len) {
    int i = 0;

    for (i = 0; i < len; ++i) {
        if (lhs[i] == '1' && rhs[i] == '1') {
            return true;
        }
    }

    return false;
}

static int delete_group(char** groups, int idx) {
    if (groups[idx] != NULL) {
        free(groups[idx]);
        groups[idx] = NULL;
    }
    return 0;
}

static char* merge_2groups(char* lhs, const char* rhs, int len) {
    int i = 0;

    for (i = 0; i < len; ++i) {
        if (rhs[i] == '1') {
            lhs[i] = '1';
        }
    }

    return lhs;
}

static int merge_all_groups(char** groups, int count) {
    int i = 0;
    int j = 0;
    int cnt = 0;

    for (i = 0; i < count - 1; ++i) {
        if (!groups[i]) {
            continue;
        }

        for (j = i + 1; j < count; ++j) {
            if (!groups[j]) {
                continue;
            }
            if (!is_relative(groups[i], groups[j], count)) {
                continue;
            }
            merge_2groups(groups[i], groups[j], count);
            delete_group(groups, j);
            j = i; // try this round again
        }
    }

    for (i = 0; i < count; ++i) {
        if (groups[i]) {
            cnt += 1;
        }
    }
    return cnt;
}

int main(int argc, char* argv[])
{
    int cnt = 0;
    char** groups = NULL;

    if ((groups = malloc_groups(PERSON_CNT, persons)) == NULL) {
        return -1;
    }

    cnt = merge_all_groups(groups, PERSON_CNT);
    printf("number of groups: %d\n", cnt);
    dump_persons(groups, PERSON_CNT);
    mfree_groups(PERSON_CNT, groups);

    if ((groups = malloc_groups(PERSON_CNT, persons2)) == NULL) {
        return -1;
    }
    cnt = merge_all_groups(groups, PERSON_CNT);
    printf("number of groups: %d\n", cnt);
    dump_persons(groups, PERSON_CNT);

    mfree_groups(PERSON_CNT, groups);
    return 0;
}
