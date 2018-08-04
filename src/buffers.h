#ifndef H_BUFFERS
#define H_BUFFERS

#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct _buff
{
    size_t len;
    size_t max_len;
} _buff;

#define buff_struct(x) ((_buff *)x)[-1]

#define buff_append(x, d)                 \
    _buff_extend((void **)&x, sizeof(d)); \
    x[buff_struct(x).len - 1] = d

#define buff_prepend(x, d)                                   \
    _buff_extend((void **)&x, sizeof(d));                    \
    memmove(x + 1, x, (buff_struct(x).len - 1) * sizeof(d)); \
    x[0] = d

#define buff_remove(x, i)                                 \
    memcpy(x + i, x + i + 1, buff_struct(x).len - i - 1); \
    buff_struct(x).len--

// iterate over buff where (x) is the index variable, and (b) is the buffer
#define buff_iter(x, b)     \
    size_t x = 0;           \
    x < buff_struct(b).len; \
    x++

void *buff_new(size_t dt_size, size_t max_len);

void buff_destroy(void *inbuff);

void _buff_extend(void **inbuff, size_t dt_size);

#define BUFFER(x) x *

#ifdef BUFFERS_IMPLEMENTATION

void *buff_new(size_t dt_size, size_t max_len)
{
    void *to_return = (_buff *)malloc(sizeof(_buff) + dt_size * max_len) + 1;
    buff_struct(to_return).len = 0;
    buff_struct(to_return).max_len = max_len;
    return to_return;
}

void buff_destroy(void *inbuff)
{
    free(((_buff *)inbuff) - 1);
}

void _buff_extend(void **inbuff, size_t dt_size)
{
    if (buff_struct(*inbuff).len >= buff_struct(*inbuff).max_len)
    {
        void *tmp = *inbuff;
        //*inbuff = buff_new(dt_size, buff_struct(tmp).max_len * 2);
        *inbuff = (_buff *)malloc(sizeof(_buff) + dt_size * buff_struct(tmp).max_len * 2) + 1;
        buff_struct(*inbuff).max_len = buff_struct(tmp).max_len * 2;
        buff_struct(*inbuff).len = buff_struct(tmp).len + 1;
        memcpy(*inbuff, tmp, buff_struct(tmp).len * dt_size);
        buff_destroy(tmp);
    }
    else
    {
        buff_struct(*inbuff).len += 1;
    }
}

#endif // BUFFERS_IMPLEMENTATION

#endif // H_BUFFERS
