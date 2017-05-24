#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>
#include <hiredis/hiredis.h>

int main()
{
    redisContext *c = redisConnect("127.0.0.1", 6379);
    const char* command1 = "get inc";
    redisReply *r = (redisReply*)redisCommand(c, command1);

    printf("r type is %d\n", r->type);
    printf("r integer is %lld\n", r->integer);
    printf("r len is %d\n", r->len);
    printf("r str is %s\n", r->str);
    printf("r elements is %d\n", r->elements);
    freeReplyObject(r);
    redisFree(c);
    return 0;
}
