#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct treeNode {
    struct treeNode *p;
    struct treeNode *left;
    struct treeNode *right;
    char word[45];
} treeNode;

typedef struct Tree {
    treeNode *root;
} Tree;

Tree
init_tree(void) {
    Tree T;
    T.root = NULL;
    return T;
}

Tree
insert(Tree T, treeNode *z) {
    treeNode *y = NULL;
    treeNode *x = T.root;

    while (x != NULL) {
        y = x;
        if (strcmp(z->word, x->word) < 0)
            x = x->left;
        else
            x = x->right;
    }
    z->p = y;
    if (y == NULL)
        T.root = z;
    else if (strcmp(z->word, y->word) < 0)
        y->left = z;
    else
        y->right = z;

    return T;
}

treeNode*
new(char *word) {
    treeNode *node = malloc(sizeof(treeNode));
    node->p = node->left = node->right = NULL;
    strncpy(node->word, word, strlen(word) + 1);
    return node;
}

treeNode *
search(treeNode *x, char *word) {
    if (x == NULL || strcmp(word, x->word) == 0)
        return x;
    if (strcmp(word, x->word) < 0)
        return search(x->left, word);
    else
        return search(x->right, word);
}

treeNode *
minimum (treeNode *x) {
    while (x->left != NULL)
        x = x->left;
    return x;
}

treeNode *
maximum (treeNode *x) {
    while (x->right != NULL)
        x = x->right;
    return x;
}

treeNode *
successor(treeNode *x) {
    treeNode *y;

    if (x->right != NULL)
        return minimum(x->right);
    y = x->p;
    while (y != NULL && x == y->right) {
        x = y;
        y = y->p;
    }
    return y;
}

Tree
transplant(Tree T, treeNode *u, treeNode *v) {
    if (u->p == NULL)
        T.root = v;
    else if (u == u->p->left)
        u->p->left = v;
    else
        u->p->right = v;
    if (v != NULL)
        v->p = u->p;
    return T;
}


Tree
delete(Tree T, treeNode *z) {
    treeNode *y;

    if (z->left == NULL)
        T = transplant(T, z, z->right);
    else if (z->right == NULL)
        T = transplant(T, z, z->left);
    else {
        y = minimum(z->right);
        if (y->p != z) {
            T = transplant(T, y, y->right);
            y->right = z->right;
            y->right->p = y;
        }
        T = transplant(T, z, y);
        y->left = z->left;
        y->left->p = y;
    }
    return T;
}

void
walk(treeNode *x) {
    if (x != NULL) {
        walk(x->left);
        printf("%s\n", x->word);
        walk(x->right);
    }
}

void freeNode(treeNode *x) {
    if (x != NULL) {
        freeNode(x->left);
        freeNode(x->right);
        free(x);
    }
}

int main(void) {
    Tree T = init_tree();
    treeNode *node;
    FILE *file;
    size_t filelen;
    char *str;

    if ((file = fopen("words.txt", "r")) == NULL)
        exit(1);
    // 获取文件长度，然后将指针重置到开始位置
    fseek(file, 0, SEEK_END);
    filelen = ftell(file);
    fseek(file, 0, SEEK_SET);

    // 读取整个文件
    str = malloc(filelen + 1);
    fread(str, filelen, 1, file);
    fclose(file);
    
    // 获取当前行的单词
    int i, j = 0;
    char word[45];
    for (i = 0; i < strlen(str); i++) {
        if (str[i] == '\n') {
            strncpy(word, str + j, i - j);
            word[i-j] = '\0';

            node = new(word);
            T = insert(T, node);

            j = i + 1;
        }
    }

    char *key = "philanthropic";
    treeNode *result;

    walk(T.root);
    if ((result = search(T.root, key)) == NULL) {
        puts("Not found");
    } else {
        printf("\nAfter delete %s:\n", result->word);
        T = delete(T, result);
        walk(T.root);
    }

    freeNode(T.root);

    return 0;
}
