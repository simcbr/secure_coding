/***************************************************
*  Author: Biru Cui 
*
***************************************************/


#ifndef _SAINT_H_
#define _SAINT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_NAME_LEN 64
#define MAX_NUM_LEN  64
#define MAX_DOMAIN_LEN 253

#define STR_LEN         16
#define MONTH_LEN       2
#define YEAR_LEN        4
#define CREDIT_CARD_LEN 16
#define SECURE_CODE_LEN 3
#define ZIP_LEN         5

#define ERR_INTERNAL      100

#define ERR_OVER_LETTERS  1
#define ERR_NON_LETTER    2
#define ERR_OVER_DIGITS   3
#define ERR_NON_DIGIT     4
#define ERR_LESS_DIGITS   5
#define ERR_OUT_OF_RANGE  6
#define ERR_NOTHING_INPUT 7

#define STATE_INTEGRAL    10
#define STATE_FRACTIONAL  20

#define ERR_LOCAL_START    10
#define ERR_LOCAL_MID      11
#define ERR_LOCAL_OVERSIZE 12
#define ERR_LOCAL_DOTAFT   13
#define ERR_LOCAL_QUOTAFT  14
#define ERR_LOCAL_PRE      15
#define ERR_INCOMPLETE     16

#define STATE_LOCAL_INIT       20
#define STATE_LOCAL_MID        21
#define STATE_LOCAL_DOT        22
#define STATE_LOCAL_LEFT_QUOT  23
#define STATE_LOCAL_RIGHT_QUOT 24
#define STATE_LOCAL_PRE        25


#define ERR_DOMAIN_START      30
#define ERR_DOMAIN_MID        31
#define ERR_DOMAIN_DOT        32
#define ERR_DOMAIN_OVERSIZE   33
#define ERR_DOMAIN_HYPHENAFT  34

#define STATE_DOMAIN_INIT     40
#define STATE_DOMAIN_MID      41
#define STATE_DOMAIN_DOT      42
#define STATE_DOMAIN_HYPHEN   43

#define EM_CH_NORMAL      1
#define EM_CH_SPECIAL     2
#define EM_CH_MID         3
#define EM_CH_DOT         4
#define EM_CH_QUOT        5
#define EM_CH_SLASH       6
#define EM_CH_HYPHEN      7
#define EM_CH_INVAL       8

unsigned int getEmailLname(char *lname, unsigned int lname_len);
unsigned int getEmailDname(char *dname, unsigned int dname_len);
unsigned int isLetter(unsigned int ch);
unsigned int getCString(char *string, unsigned char string_len);
unsigned int isDigit(unsigned int ch);
unsigned int getNString(char *num, unsigned char num_len);
unsigned int getDollarNum(unsigned int *amount_int, unsigned char integer_num,
                          unsigned int *amount_frac, unsigned char fractional_num);
void errorHandle(unsigned int err_code);

void transString(char *str);
void transNum(char *amount_int_str, unsigned int amount_int);

#endif
