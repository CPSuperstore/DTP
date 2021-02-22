//
// Created by Christopher on 2021-02-21.
//

#include <stdlib.h>
#include <math.h>
#include <string.h>

#ifndef DTP_CONVERSION_H
#define DTP_CONVERSION_H

#endif //DTP_CONVERSION_H

#define NULL_CHAR 'j'
#define DATA_ENCAPSULATOR '|'
#define DATA_ENCAPSULATOR_STR "|"

char *extract_data(const char *str) {
    const char *i1 = strstr(str, DATA_ENCAPSULATOR_STR);
    if (i1 != NULL) {
        const size_t pl1 = strlen(DATA_ENCAPSULATOR_STR);
        const char *i2 = strstr(i1 + pl1, DATA_ENCAPSULATOR_STR);

        const size_t mlen = i2 - (i1 + pl1);
        char *ret = malloc(mlen + 1);
        if (ret != NULL) {
            memcpy(ret, i1 + pl1, mlen);
            ret[mlen] = '\0';
            return ret;
        }
    }
    return NULL;
}

char *encapsulate_data(char *str){
    char *result = malloc(strlen(str + 2));
    sprintf(result, "%c%s%c", DATA_ENCAPSULATOR, str, DATA_ENCAPSULATOR);
    return result;
}

int bin_to_dec(const int bin[8]){
    int multiplier = 1;
    int result = 0;
    for (int i = 7; i >= 0; --i){
        result += multiplier * bin[i];
        multiplier *= 2;
    }

    return result;
}

char bin_to_ascii(const int bin[8]){
    return bin_to_dec(bin);
}

int * ascii_to_bin(int ascii){
    int *bin = (int*) calloc(8, sizeof(int));

    for(int i = 0; ascii > 0; i++){
        bin[7 - i] = ascii % 2;
        ascii = ascii / 2;
    }

    return bin;
}

int * char_to_nybble(char c){
    int *result;
    switch (c) {
        case '0':
            result = (int [4]) {0, 0, 0, 0};
            break;
        case '1':
            result = (int [4]) {0, 0, 0, 1};
            break;
        case '2':
            result = (int [4]) {0, 0, 1, 0};
            break;
        case '3':
            result = (int [4]) {0, 0, 1, 1};
            break;
        case '4':
            result = (int [4]) {0, 1, 0, 0};
            break;
        case '5':
            result = (int [4]) {0, 1, 0, 1};
            break;
        case '6':
            result = (int [4]) {0, 1, 1, 0};
            break;
        case '7':
            result = (int [4]) {0, 1, 1, 1};
            break;
        case '8':
            result = (int [4]) {1, 0, 0, 0};
            break;
        case '9':
            result = (int [4]) {1, 0, 0, 1};
            break;
        case ',':
            result = (int [4]) {1, 0, 1, 0};
            break;
        case '\n':
            result = (int [4]) {1, 0, 1, 1};
            break;
        case '.':
            result = (int [4]) {1, 1, 0, 0};
            break;
        case '-':
            result = (int [4]) {1, 1, 0, 1};
            break;
        case DATA_ENCAPSULATOR:
            result = (int [4]) {1, 1, 1, 0};
            break;
        default:
            result = (int [4]) {1, 1, 1, 1};
            break;
    }
    return result;
}

int compareArrays(const int *a, const int *b, int n) {
    for(int i = 0; i < n; i++) {
        if (a[i] != b[i])
            return 0;
    }
    return 1;
}

char nybble_to_char(const int * c){
    char result;
    if (compareArrays(c, (int[4]){0, 0, 0, 0}, 4)){
        result = '0';
    }
    else if (compareArrays(c, (int[4]){0, 0, 0, 1}, 4)){
        result = '1';
    }
    else if (compareArrays(c, (int[4]){0, 0, 1, 0}, 4)){
        result = '2';
    }
    else if (compareArrays(c, (int[4]){0, 0, 1, 1}, 4)){
        result = '3';
    }
    else if (compareArrays(c, (int[4]){0, 1, 0, 0}, 4)){
        result = '4';
    }
    else if (compareArrays(c, (int[4]){0, 1, 0, 1}, 4)){
        result = '5';
    }
    else if (compareArrays(c, (int[4]){0, 1, 1, 0}, 4)){
        result = '6';
    }
    else if (compareArrays(c, (int[4]){0, 1, 1, 1}, 4)){
        result = '7';
    }
    else if (compareArrays(c, (int[4]){1, 0, 0, 0}, 4)){
        result = '8';
    }
    else if (compareArrays(c, (int[4]){1, 0, 0, 1}, 4)){
        result = '9';
    }
    else if (compareArrays(c, (int[4]){1, 0, 1, 0}, 4)){
        result = ',';
    }
    else if (compareArrays(c, (int[4]){1, 0, 1, 1}, 4)){
        result = '\n';
    }
    else if (compareArrays(c, (int[4]){1, 1, 0, 0}, 4)){
        result = '.';
    }
    else if (compareArrays(c, (int[4]){1, 1, 0, 1}, 4)){
        result = '-';
    }
    else if (compareArrays(c, (int[4]){1, 1, 1, 0}, 4)){
        result = DATA_ENCAPSULATOR;
    }
    else {
        result = NULL_CHAR;
    }

    return result;
}

unsigned int divide_up(unsigned int numerator, unsigned int denominator){
    return (numerator + (denominator / 2)) / denominator;
}

void print_array(int* arr, int n){
    printf("[");
    for (int i = 0; i < n; ++i) {
        printf("%i, ", arr[i]);
    }
    printf("]\n");
}

int *twos_compliment(int data){
    const size_t BITS = 8;
    int *bin = malloc(BITS);;

    for(unsigned int i=0; i<BITS; i++)
    {
        unsigned int mask = 1u << (BITS - 1 - i);
        bin[i] = (data & mask) ? 1 : 0;
    }

    return bin;
}

char* encode_message(char* input){
    input = encapsulate_data(input);
    int adder;
    int i;
    int *buff = (int[8]) {1, 1, 1, 1, 1, 1, 1, 1};
    unsigned int input_length = strlen(input);
    unsigned int message_length = divide_up(input_length, 2);
    char *message = malloc(message_length);
    int message_index = 0;

    for (i = 0; i < input_length; i++) {
        adder = i % 2 == 0 ? 0 : 4;

        int* nybble = char_to_nybble(input[i]);
        buff[adder + 0] = nybble[0];
        buff[adder + 1] = nybble[1];
        buff[adder + 2] = nybble[2];
        buff[adder + 3] = nybble[3];

        if (i % 2 == 1){
            message[message_index++] = bin_to_ascii(buff);
            buff = (int[8]) {1, 1, 1, 1, 1, 1, 1, 1};
        }
    }

    if (i % 2 == 1){
        message[message_index] = bin_to_ascii(buff);
    }

    return message;
}

char* decode_message(char* input){
    unsigned int input_length = strlen(input);
    unsigned int message_length = input_length * 2;

    char *message = malloc(message_length);
    int message_index = 0;

    for (int i = 0; i < input_length; i++) {
        int *bin;

        if (input[i] < 0){
            bin = twos_compliment(input[i]);
        } else {
            bin = ascii_to_bin(input[i]);
        }

        message[message_index++] = nybble_to_char((int[4]) {bin[0], bin[1], bin[2], bin[3]});
        message[message_index++] = nybble_to_char((int[4]) {bin[4], bin[5], bin[6], bin[7]});
    }
    message[strlen(message) - 2] = '\0';

    if(message[strlen(message) - 1] == NULL_CHAR){
        message[strlen(message) - 1] = '\0';
    }

    return extract_data(message);
}