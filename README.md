# Stretchy Buffers Implementation
I know that this was already implemented [here](https://github.com/nothings/stb/blob/master/stretchy_buffer.h), but I didn't understand it, so I didn't trust it

To remedy this issue, I recreated it from scratch only knowing to store the values of the buffer in the space before the pointer returned to the user

In your main.c file or wherever you'd like, make sure that you define `BUFFERS_IMPLEMENTATION`

## Functions

`buff_struct(buff)` - Returns a struct of type `_buff`, has `.len` and `.max_len`

`buff_append(buff, val)` - Append to the end of a buffer

`buff_prepend(buff, val)` - Use [memmove](https://www.geeksforgeeks.org/memmove-in-cc/) to prepend to the buffer

`buff_remove(buff, index)` - Removes item in `index`. If it's a pointer to something, you should free it before calling this

`buff_iter(x,b)` - Macro that expands to have `x` be the index and `b` be the buffer in looping for loop

`buff_new(dt_size, max_len)` - Returns a new buffer, used like `int * mybuff = buff_new(sizeof *mybuff, );`

`buff_destroy(buff)` - Frees the underlying `buff` pointer
