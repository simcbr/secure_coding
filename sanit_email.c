/***************************************************
*  Author: Biru Cui 
*
***************************************************/


#include "sanit.h"


/************************************************
This function checks the category of input character
in local name part.

There are mainly 4 types of characters.
1) NORMAL: the character can appear without being quoted.
2) SPECIAL: the character must be contained between
quotations.
3) ." : dot and quotation are functional characters
4) \: space, quotation and at must be preceded by 
a slash.
*************************************************/
unsigned int isEmLetter(unsigned char ch)
{
    unsigned int ret;

    if ( isLetter(ch) ||
         isDigit(ch)  ||
         (ch == 33)    ||        //'!'
         ((ch >= 35) && (ch <=39)) || //'#$%&''
         (ch == 42)   ||        //'*'
         (ch == 43)   ||        //'+'
         (ch == 45)   ||        //'-'
         (ch == 47)   ||        //'/'
         (ch == 61)   ||        //'='
         (ch == 63)   ||        //'?'
         ((ch >= 94) && (ch <=96)) ||  //'^_`'
         ((ch >= 123) && (ch <=126)) //'{|}~'
       )
    {
        ret = EM_CH_NORMAL;
    }
    /*DOT can not appear at the begining*/
    else if ( ch == '.' )
    {
        ret = EM_CH_DOT;
    }
    /*SPECIAL must be contained between quotations*/
    else if ( (ch == 40) || (ch == 41) || // '()'
              (ch == 44) || (ch == 58) || (ch == 59) || //',:;'
              (ch == 60) || (ch == 62) || //'<>'
              (ch == 64) ||  //'@'
              (ch == 91) || (ch == 93)  //'[]'

            )
    {
        ret = EM_CH_SPECIAL;
    }
    else if ( (ch == 34) )   //'"'
    {
        ret = EM_CH_QUOT;
    }
    else if ( ch == 92 )     //'\'
    {
        ret = EM_CH_SLASH;
    }

    return ret;
}



/************************************************
This function reads the localname part of a email
address.

It will keep on reading characters until it find an 
@ not be contained between quotations.

1) In the INIT state, it only accepts NORMAL charater
and quotation.
   if a quotation is read, it goes to QUOT state;
   if a NORMAL character is read, it goes to MID state.
2) In MID state:
   if a dot is read, it goes to DOT state;
   if an AT is read, exit;
3) In DOT state:
   if a NORMAL charater is read, goes to MID state;
   if a quotation is read, goes to QUOT state. 
4) In QUOT state, speical charaters is allowed. 
   if slash is read, goes to SLASH state.
5) In SLASH state, space, at and quotation are allowed
to be the next character.
*************************************************/
unsigned int getEmailLname(char *lname, unsigned int lname_len)
{
    unsigned int ind = 0, not_cont = 0, ch, ret_ch, ret, state;
    char temp[MAX_NAME_LEN+1];


    if (lname == NULL)
    {
        printf("NULL lname\n");
        return ERR_INTERNAL;
    }    

    state = STATE_LOCAL_INIT;
    ret = ERR_LOCAL_OVERSIZE;
    memset(temp, 0, MAX_NAME_LEN+1);
    while (ind < lname_len && !not_cont)
    {
        ch = getchar();
        if ( (ch == 0x0D) || (ch == 0x0A) )
        {
            ret = ERR_INCOMPLETE;
            not_cont = 1;
            break;
        }
        ret_ch = isEmLetter(ch);
        switch (state)
        {
            case STATE_LOCAL_INIT:
                if (ret_ch == EM_CH_QUOT)
                {
                    temp[ind++] = ch;
                    state = STATE_LOCAL_LEFT_QUOT;
                }
                else if (ret_ch == EM_CH_NORMAL)
                {
                    temp[ind++] = ch;
                    state = STATE_LOCAL_MID;
                }
                else
                {
                    ret = ERR_LOCAL_START;
                    not_cont = 1;
                }
                break;

            case STATE_LOCAL_MID:
                if (ret_ch == EM_CH_NORMAL)
                {
                    temp[ind++] = ch;
                }
                else if (ret_ch == EM_CH_DOT)
                {
                    temp[ind++] = ch;
                    state = STATE_LOCAL_DOT;
                }
                else if (ch == '@')
                {
                    /*go to check domain name*/
                    not_cont = 1;
                    ret = 0;
                }
                else
                {
                    ret = ERR_LOCAL_MID;
                    not_cont = 1;
                }
                break;

            case STATE_LOCAL_DOT:
                if (ret_ch == EM_CH_NORMAL)
                {
                    temp[ind++] = ch;
                    state = STATE_LOCAL_MID;
                }
                else if (ret_ch == EM_CH_QUOT)
                {
                    temp[ind++] = ch;
                    state = STATE_LOCAL_LEFT_QUOT;
                }
                else
                {
                    ret = ERR_LOCAL_DOTAFT;
                    not_cont = 1;
                }
                break;

            case STATE_LOCAL_LEFT_QUOT:
                if (ret_ch == EM_CH_SLASH)
                {
                    temp[ind++] = ch;
                    state = STATE_LOCAL_PRE;
                }
                else if ( (ret_ch == EM_CH_SPECIAL) ||
                          (ret_ch == EM_CH_NORMAL) )
                {
                    temp[ind++] = ch;
                }
                else if (ret_ch == EM_CH_QUOT)
                {
                    temp[ind++] = ch;
                    state = STATE_LOCAL_RIGHT_QUOT;
                }
                else
                {
                    ret = ERR_LOCAL_QUOTAFT;
                    not_cont = 1;
                }
                break;

            case STATE_LOCAL_RIGHT_QUOT:
                if (ret_ch == EM_CH_DOT)
                {
                    temp[ind++] = ch;
                    state = STATE_LOCAL_DOT;
                }
                else if (ch == '@')
                {
                    /*go to check domain name*/
                    not_cont = 1;
                    ret = 0;
                }
                else
                {
                    not_cont = 1;
                    ret = ERR_LOCAL_QUOTAFT;
                }
                break;

            case STATE_LOCAL_PRE:
                if ( (ch == ' ') || (ch == '"') || (ch == 92) || (ch == '@'))  //'\'
                {
                    temp[ind++] = ch;
                    state = STATE_LOCAL_LEFT_QUOT;
                }
                else
                {
                    not_cont = 1;
                    ret = ERR_LOCAL_PRE;
                }
                break;

            default:
                break;
        }
    }

    if (!ret)
    {
        memcpy(lname, temp, MAX_NAME_LEN+1);
    }

    return ret;
}



/************************************************
This function checks whether input charater is 
valid in domain name part.

only dot, dash, letters and digits are allowed.
*************************************************/
unsigned int isDmLetter(unsigned char ch)
{
    unsigned int ret;

    if ( isLetter(ch) ||
         isDigit(ch)  )
    {
        ret = EM_CH_NORMAL;
    }
    else if ( ch == '.')
    {
        ret = EM_CH_DOT;
    }
    else if ( ch == '-')
    {
        ret = EM_CH_HYPHEN;
    }
    else
    {
        ret = EM_CH_INVAL;
    }

    return ret;
}



/************************************************
This function reads the domainname part of a email
address.

The domain name starts and stops with digits or 
letters, hyphens and dots do not appear two or 
more times consecutively. 
*************************************************/
unsigned int getEmailDname(char *dname, unsigned int dname_len)
{
    unsigned int ind = 0, not_cont = 0, ch, ret_ch, ret, state;
    char temp[MAX_DOMAIN_LEN+1];

    if (dname == NULL)
    {
        printf("NULL dname\n");
        return ERR_INTERNAL;
    }

    state = STATE_DOMAIN_INIT;
    ret = ERR_DOMAIN_OVERSIZE;
    memset(temp, 0, MAX_DOMAIN_LEN+1);
    while (ind < dname_len && !not_cont)
    {
        ch = getchar();

        ret_ch = isDmLetter(ch);
        switch (state)
        {
            case STATE_DOMAIN_INIT:
                if (ret_ch == EM_CH_NORMAL)
                {
                    temp[ind++] = ch;
                    state = STATE_DOMAIN_MID;
                }
                else if ( (ch == 0x0D) || (ch == 0x0A) )
                {
                    ret = ERR_INCOMPLETE;
                    not_cont = 1; 
                }
                else
                {
                    ret = ERR_DOMAIN_START;
                    not_cont = 1;
                }
                break;

            case STATE_DOMAIN_MID:
                if (ret_ch == EM_CH_NORMAL)
                {
                    temp[ind++] = ch;
                }
                else if (ret_ch == EM_CH_HYPHEN)
                {
                    temp[ind++] = ch;
                    state = STATE_DOMAIN_HYPHEN;
                }
                else if (ret_ch == EM_CH_DOT)
                {
                    temp[ind++] = ch;
                    state = STATE_DOMAIN_DOT;
                }
                else if ( (ch == 0x0D) || (ch == 0x0A) )
                {
                    ret = 0;
                    not_cont = 1;
                }
                else
                {
                    ret = ERR_DOMAIN_MID;
                    not_cont = 1;
                }
                break;

            case STATE_DOMAIN_DOT:
                if (ret_ch == EM_CH_NORMAL)
                {
                    temp[ind++] = ch;
                    state = STATE_DOMAIN_MID;
                }
                else if ( (ch == 0x0D) || (ch == 0x0A) )
                {
                    ret = ERR_INCOMPLETE;
                    not_cont = 1;
                }
                else
                {
                    ret = ERR_DOMAIN_DOT;
                    not_cont = 1;
                }
                break;

            case STATE_DOMAIN_HYPHEN:
                if (ret_ch == EM_CH_NORMAL)
                {
                    temp[ind++] = ch;
                    state = STATE_DOMAIN_MID;
                }
                else if ( (ch == 0x0D) || (ch == 0x0A) )
                {
                    ret = ERR_INCOMPLETE;
                    not_cont = 1;
                }
                else
                {
                    ret = ERR_DOMAIN_HYPHENAFT;
                    not_cont = 1;
                }
                break;

            default:
                break;
        }
    }

    if (!ret)
    {
        memcpy(dname, temp, MAX_DOMAIN_LEN);
    }

    return ret;

}

