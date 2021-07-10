#ifndef ENTRY_H
#define ENTRY_H

typedef struct {
    unsigned char is_deleted;
    void *key;
    void *data;
    unsigned int len;
} entry_t;
#endif /*ENTRY_H*/