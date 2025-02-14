//
// Created by zenyt on 13.02.25.
//
#include <openssl/sha.h>
#include "limits.h"
#ifndef TEST_POLYGON_BLOCK_H
#define TEST_POLYGON_BLOCK_H
#define PROBABILITY (unsigned long long) 2 << (unsigned long long) 1
typedef struct{
    unsigned long long nonce;
    unsigned long long last;
    char *value;
} chain_block;
char *block_hash(chain_block self);
unsigned long long digit_hash(chain_block);
chain_block init_block(chain_block last, char *value);
chain_block make_first(char *value);
char *to_string(chain_block);
#endif //TEST_POLYGON_BLOCK_H
