#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include <string.h>
#include <stdbool.h>
#include "limits.h"
#include "../include/block.h"

int main(void) {
    chain_block block = make_first("hello");
    chain_block last_block = block;
    for (int i = 0; i < 100; ++i) {
        last_block = init_block(last_block, "gleb");
        printf("Made block #%i:\n%s", i, to_string(last_block));
    }
}
