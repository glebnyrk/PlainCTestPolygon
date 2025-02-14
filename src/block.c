//
// Created by zenyt on 13.02.25.
//

#include <stdbool.h>
#include "../include/block.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "limits.h"
static char *hash(char *data);
char *block_hash(chain_block self){
    char *string = to_string(self);
    char *hash_result = hash(string);
    free(string);
    return hash_result;
}
char *hash(char *data) {
    char* hash = malloc(sizeof(char) * SHA512_DIGEST_LENGTH);
    SHA512(data, strlen(data), hash);
    return hash;
}
chain_block make_first(char *value){
    chain_block block = {0};
    block.value = value;
    return block;
}
chain_block init_block(chain_block last, char *value){
    unsigned long long last_hash = digit_hash(last);
    unsigned long long nonce = 0;
    while(true){
        chain_block test_block = {};
        test_block.value = value;
        test_block.last = last_hash;
        test_block.nonce = nonce;
        if (digit_hash(test_block) < PROBABILITY){
            return test_block;
        }
        nonce++;
    }
}
unsigned long long digit_hash(chain_block self){
    char *self_hash = block_hash(self);
    unsigned long long last_digit_hash = 0;
    for (int i = 0; i < SHA512_DIGEST_LENGTH; ++i) {
        last_digit_hash+= self_hash[i] << i;
    }
    free(self_hash);
    return last_digit_hash;
}
char *to_string(chain_block self){
    char *string;
    asprintf(&string, "block{\n\tChain:\"testchain\";\n\tLast:\"%llu\";\n\tNonce:\"%llu\";\n\tValue:\"%s\";\n}\n",self.last, self.nonce, self.value);
    return string;
}