#include <stdio.h>
#include <string.h>
#include <oqs/oqs.h>
#include <sodium.h>
int main(){
    if(sodium_init() < 0){
        printf("error during sodium init    :(\n");
        exit(-1);
    }
    printf("sodium init     :)\n");
    // Инициализация Kyber-1024
    OQS_KEM *kem = OQS_KEM_new(OQS_KEM_alg_kyber_1024);
    if (kem == NULL) {
        printf("Ошибка: Kyber-1024 не поддерживается\n");
        return 1;
    }
    //Память для публичного ключа
    uint8_t public_key[OQS_KEM_kyber_1024_length_public_key];
    //Память для приватного ключа
    uint8_t secret_key[OQS_KEM_kyber_1024_length_secret_key];
    //Память для результата шифрования
    uint8_t ciphertext[OQS_KEM_kyber_1024_length_ciphertext];
    //хз для чего это
    uint8_t shared_secret_enc[OQS_KEM_kyber_1024_length_shared_secret];
    uint8_t shared_secret_dec[OQS_KEM_kyber_1024_length_shared_secret];

    // Генерация ключей
    OQS_KEM_keypair(kem, public_key, secret_key);
    printf("Ключи сгенерированы\n");

    // Инкапсуляция
    OQS_KEM_encaps(kem, ciphertext, shared_secret_enc, public_key);
    printf("Инкапсуляция прошла\n");

    // Деинкапсуляция
    OQS_KEM_decaps(kem, shared_secret_dec, ciphertext, secret_key);
    printf("Деинкапсуляция прошла\n");

    // Проверка совпадения секретов
    if (memcmp(shared_secret_enc, shared_secret_dec, OQS_KEM_kyber_1024_length_shared_secret) == 0) {
        printf("Общие секреты совпадают\n");
    } else {
        printf("Ошибка: секреты не совпадают\n");
        return 1;
    }
    for(int i = 0; i < OQS_KEM_kyber_1024_length_shared_secret; i++){
        printf("%02x",shared_secret_enc[i]);
    }
    printf("\n%i\n",OQS_KEM_kyber_1024_length_shared_secret);
}
