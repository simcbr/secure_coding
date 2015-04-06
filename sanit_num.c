/***************************************************
*  Author: Biru Cui 
*
***************************************************/

#include "sanit.h"


/************************************************
The function checks whether a character is a digit.
*************************************************/
unsigned int isDigit(unsigned int ch)
{
    if ( (ch >= 0x30) && (ch <= 0x39) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


/************************************************
The function reads num_len letters from stdio.
It only treats continue letters (upper or lower)
as a valid string input.
Other inputs are treated as invalid.
Less or more letters input than required num_len 
is also treated as invalid.
*************************************************/
unsigned int getNString(char *num, unsigned char num_len)
{
    unsigned int ind = 0, not_cont = 0, ch, ret = 0;
    char temp[MAX_NUM_LEN];


    memset(temp, 0, MAX_NUM_LEN);
    while (ind < num_len && !not_cont)
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
            if (ind == num_len -1)
            {
                /*the 'num_len'th letter is not CR*/
                ret = ERR_OVER_DIGITS;
                not_cont = 1;
            }
            else
            {
                if (isDigit(ch))
                {
                    temp[ind++] = ch;
                }
                else
                {
                    ret = ERR_NON_DIGIT;
                    not_cont = 1;
                }
            }

        }

    }

    if (!ret)
    {
        if (ind == num_len-1)
        {
            /* !!! if temp is long enough, num could overflow
            exceed the largest num unsigned int support.
            Let caller decide whether to transfer to num*/
            memcpy(num, temp, ind);
        }
        else
        {
            /*received digits less than num_len*/
            ret = ERR_LESS_DIGITS;
        }
    }

    return ret;
}



/************************************************
This function reads a real num with integer_num
digits in integer part and fractional_num digits
in fractional part.

The reason do not return string is to provide a 
uniform interface.
*************************************************/
unsigned int getDollarNum(unsigned int *amount_int, unsigned char integer_num,
                          unsigned int *amount_frac, unsigned char fractional_num)
{
    unsigned char ind = 0, ret = 0, not_cont = 0, ch, state, int_ind = 0;
    char temp[MAX_NUM_LEN];


    memset(temp, 0, MAX_NUM_LEN);
    state = STATE_INTEGRAL;
    while (ind < integer_num+fractional_num+1 && !not_cont)
    {
        ch = getchar();
        switch (state)
        {
            case STATE_INTEGRAL:
                if ( (ch == 0x0D) || (ch == 0x0A) )
                {
                    /*exit the loop*/ 
                    not_cont = 1;

                    /*!!!keep in mind, atoi could be overflow
                    if temp is very long.*/
                    *amount_int = atoi(temp);

                    if (ind == 0)
                    {
                        ret = ERR_NOTHING_INPUT;
                    }
                }
                else if (ch == '.')
                {
                    /*change state to STATE_FRACTIONAL*/
                    //temp[ind++] = ch;
                    state = STATE_FRACTIONAL;
                    *amount_int = atoi(temp);
                    memset(temp, 0, MAX_NUM_LEN);
                    int_ind = ind; 
                    ind = 0;
                    
                }
                else
                {
                    if (ind == integer_num)
                    {
                        not_cont = 1;
                        ret = ERR_OVER_DIGITS;
                    }
                    else
                    {
                        if (isDigit(ch))
                        {
                            temp[ind++] = ch;
                        }
                        else
                        {
                            not_cont = 1;
                            ret = ERR_NON_DIGIT;
                        }
                    }
                }

                break;

            case STATE_FRACTIONAL:
                if ( (ch == 0x0D) || (ch == 0x0A) )
                {
                    if ( (int_ind == 0) && (ind == 0) )
                    {
                        ret = ERR_NOTHING_INPUT;
                    }
                    else
                    {
                        *amount_frac = atoi(temp);
                        /*fill the frac part with 0 if input 
                          digits less than fractional_num*/
                        if (ind < fractional_num)
                        {
                            *amount_frac = (*amount_frac) * 10 * (fractional_num - ind);
                        }
                    }
                    not_cont = 1;
                }
                else
                {
                    if (ind == fractional_num)
                    {
                        not_cont = 1;
                        ret = ERR_OVER_DIGITS;
                    }
                    else
                    {
                        if (isDigit(ch))
                        {
                            temp[ind++] = ch;
                        }
                        else
                        {
                            not_cont = 1;
                            ret = ERR_NON_DIGIT;
                        }
                    }
                }
                break;

            default:
                break;
        }
    }


    return ret;
}




/************************************************
This function transfer the int to string format.
for example: int xxxxxxx
output str:  x,xxx,xxx
*************************************************/
void transNum(char *amount_int_str, unsigned int amount_int)
{
    char temp[STR_LEN];
    int len, addition, i, j, ind;

    if (amount_int_str == NULL)
    {
        printf("input num invalid.\n");
        return;
    }

    memset(temp, 0, STR_LEN);
    sprintf(temp, "%d", amount_int);
    len = strlen(temp);
    addition = (len-1)/3;
    j = 0;
    /*!!! be carefule of the ind, make sure
    it's less than STR_LEN*/
    ind = len+addition-1;
    for (i=len-1; i>=0; i--)
    {
        amount_int_str[ind--] = temp[i];
        j++;
        if ( (j == 3) && i)
        {
            amount_int_str[ind--] = ',';
            j = 0;
        }
    }

}

