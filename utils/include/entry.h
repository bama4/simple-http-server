#ifndef ENTRY_H
#define ENTRY_H

typedef struct {
    unsigned char is_deleted;
    void *data;
} entry_t;
#endif /*ENTRY_H*/