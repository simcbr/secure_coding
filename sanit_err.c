/***************************************************
*  Author: Biru Cui 
*
***************************************************/


#include "sanit.h"


/************************************************
This function clears left characters (until a "CR") 
in stdio buffer.
*************************************************/
void cleanIOBuffer(void)
{
    unsigned char ret = 0;

    while (ret != 0x0A)
    {
        ret = getchar();
    }
}


/************************************************
This function handles the error cases.
If the error happens after read the "CR" out, then 
do not call the cleanIOBuffer; 
otherwise, call cleanIOBuffer to clear the stdio 
buffer. 
*************************************************/
void errorHandle(unsigned int err_code)
{

    switch (err_code)
    {
        case ERR_OVER_LETTERS:
            printf("letters input oversize");
            break;

        case ERR_NON_LETTER:
            printf("only english alphabet letter support");
            break;

        case ERR_OVER_DIGITS:
            printf("digits input oversize");
            break;

        case ERR_NON_DIGIT:
            printf("only digit support");
            break;

        case ERR_LESS_DIGITS:
            printf("less digits input");
            break;

        case ERR_OUT_OF_RANGE:
            printf("out of range");
            break;

        case ERR_NOTHING_INPUT:
            printf("nothing input");
            break;

        case ERR_INCOMPLETE:
            printf("incomplete email address");
            break;

        case ERR_LOCAL_START:
            printf("invalid character to start the local name");
            break;

        case ERR_LOCAL_MID:
            printf("invalid character appear in the local name");
            break;

        case ERR_LOCAL_OVERSIZE:
            printf("local name length oversize");
            break;

        case ERR_LOCAL_DOTAFT:
            printf("invalid character appear after dot in the local name");
            break;

        case ERR_LOCAL_QUOTAFT:
            printf("invalid character appear after quotation in the local name");
            break;

        case ERR_LOCAL_PRE:
            printf("invalid character appear after slash in the local name");
            break;

        case ERR_DOMAIN_START:
            printf("invalid character to start the domain name");
            break;

        case ERR_DOMAIN_MID:
            printf("invalid character appear in the domain name");
            break;

        case ERR_DOMAIN_DOT:
            printf("invalid character appear after dot in the domain name");
            break;

        case ERR_DOMAIN_HYPHENAFT:
            printf("invalid character appear after hyphen in the domain name");
            break;

        case ERR_DOMAIN_OVERSIZE:
            printf("domain name length oversize");
            break;

        default:
            break;
    }

    printf(". please try it again\n");

    if ( (err_code == ERR_NOTHING_INPUT) ||
         (err_code == ERR_LESS_DIGITS)   ||
         (err_code == ERR_INCOMPLETE)    ||
         (err_code == ERR_OUT_OF_RANGE) )
    {
        // do nothing
    }
    else
    {
        cleanIOBuffer();
    }
}



