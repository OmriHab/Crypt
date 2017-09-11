#ifndef CRYPT_H
#define CRYPT_H
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define TMP_PATH "Encrypt_tmp.txt"
typedef long long unsigned int Key;

Key getKey();
Key scrambleKey(Key k);

/*Encrypt File: Encrypts and Unencrypts file (f^key^key == f)*/
void encryptFile(const char* inPath, const char* outPath, Key k);
void encryptSelf(const char* inPath, Key k);
int getch(void);

int is_in_args(int argc, const char* argv[], char* arg_short, char* arg_long);
int index_after_switches(int argc, const char* argv[]);
void print_help(const char* prog_name);

#endif
