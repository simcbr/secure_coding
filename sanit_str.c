/***************************************************
*  Author: Biru Cui 
*
***************************************************/


#include <ctype.h>
#include "sanit.h"


/************************************************
This function checks whether the character is a 
letter.
*************************************************/
unsigned int isLetter(unsigned int ch)
{
    if ( ((ch >= 0x41) && (ch <= 0x5A)) ||
         ((ch >= 0x61) && (ch <= 0x7A)) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}



/************************************************
Read no more than string_len letters. 
If read a "CR", then return 0.
If no "CR" read after string_len-1 letters, return 
ERR_OVER_LETTERS. 
if read other characters, return ERR_NON_LETTER.
*************************************************/
unsigned int getCString(char *string, unsigned char string_len)
{
    unsigned int ind = 0, not_cont = 0, ch, ret = 0;

    while (ind < string_len && !not_cont)
    {
        ch = getchar();
        if ( (ch == 0x0D) || (ch == 0x0A) )
        {
            /*exit the loop*/
            not_cont = 1;

            /*nothing input*/
            if (ind == 0)
            {
                ret = ERR_NOTHING_INPUT;
            }
            break;
        }
        else
        {
            if (ind == string_len -1)
            {
                /*the 'string_len'th letter is not CR*/
                ret = ERR_OVER_LETTERS;
                not_cont = 1;
            }
            else
            {
                if (isLetter(ch))
                {
                    string[ind++] = ch;
                }
                else
                {
                    ret = ERR_NON_LETTER;
                    not_cont = 1;
                }
            }
        }
    }

    return ret;
}


/************************************************
This function transfers the string's format.
The first letter is transferred to upper case;
left letters are transferred to lower case.
*************************************************/
void transString(char *str)
{
    int len, i;

    str[0] = toupper(str[0]);
    len = strlen(str);
    for (i = 1; i<len; i++)
    {
        str[i] = tolower(str[i]);
    }
}

