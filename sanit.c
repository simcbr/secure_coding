/***************************************************
*  Author: Biru Cui 
*
***************************************************/


#include "sanit.h"


const char *monthStr[] = {"January", "February", "March", "April", "May", 
                          "June", "July", "August",
                          "September", "October", "November", "December"};

int main(int argc, char* argv[])
{
    char first_name[MAX_NAME_LEN], last_name[MAX_NAME_LEN];
    char credit_str[MAX_NAME_LEN], amount_int_str[STR_LEN], temp[STR_LEN];
    unsigned int month, year, secure_code, zip;
    unsigned int amount_int, amount_frac;
    unsigned int ret;
    char local_name[MAX_NAME_LEN+1], domain_name[MAX_DOMAIN_LEN+1];

    if (argc != 1 )
    {
        printf("Usage: sainting\n");
        return -1;
    }


    //input first name
    do
    {
        memset(first_name, 0, MAX_NAME_LEN);
        printf("Please input your first name [continue letters, space is not supported, no more than 63], press ENTER when done:\n");
        ret = getCString(first_name, MAX_NAME_LEN);
        if (ret)
        {
            errorHandle(ret);
            //return -2;
        }
    }while(ret);
    //transfer string format
    transString(first_name); 

    //input last name
    do
    {
        memset(last_name, 0, MAX_NAME_LEN);
        printf("Please input your last name [continue letters, space is not supported, no more than 63], press ENTER when done:\n");
        ret = getCString(last_name, MAX_NAME_LEN);
        if (ret)
        {
            errorHandle(ret);
            //return -3;
        }
    }while(ret); 
    //transfer string format
    transString(last_name);

    //input credit card number
    do
    {
        memset(credit_str, 0, MAX_NAME_LEN);
        printf("Please input creadit card number (16 digits), press ENTER when done:\n");    
        ret = getNString(credit_str, CREDIT_CARD_LEN+1);
        if (ret)
        {
            errorHandle(ret);
            //return -4;
        }
    }while(ret);
 

    //input month
    do
    {
        month = 0;
        memset(temp, 0, STR_LEN);
        printf("Please input expiration month xx (2 digits 01~12), press ENTER when done:\n");
        ret = getNString(temp, MONTH_LEN+1);
        if (!ret)
        {
            month = atoi(temp);
            if ( (month>=1) && (month<=12) )
            {
                //do nothing
            }   
            else
            {
                ret = ERR_OUT_OF_RANGE;
            }
        }
        if (ret)
        {
            errorHandle(ret);
            //return -5;
        }
    }while(ret);


    //input year
    do
    {
        year = 0;
        memset(temp, 0, STR_LEN);
        printf("Please input expiration year xxxx (4 digits, 1985~2011), press ENTER when done:\n");
        ret = getNString(temp, YEAR_LEN+1);
        if (!ret)
        {
            year = atoi(temp);
            if ( (year>=1985) && (year<=2011) )
            {
                //do nothing
            }
            else
            {
                ret = ERR_OUT_OF_RANGE;
            }
        }
        if (ret)
        {
            errorHandle(ret);
            //return -6;
        }
    }while(ret);


    //input security code
    secure_code = 0;
    do
    {
        memset(temp, 0, STR_LEN);
        printf("Please input security code xxx (3 digits), press ENTER when done:\n");
        ret = getNString(temp, SECURE_CODE_LEN+1);
        if (ret)
        {
            errorHandle(ret);
            //return -7;
        }
    }while(ret);
    secure_code = atoi(temp);



    //input zip code
    zip = 0;
    do
    {
        memset(temp, 0, STR_LEN);
        printf("Please input zip code xxxxx (5 digits), press ENTER when done:\n");
        ret = getNString(temp, ZIP_LEN+1);
        if (ret)
        {
            errorHandle(ret);
            //return -8;
        }
    }while(ret);
    zip = atoi(temp);


    //input purchase amount
    do
    {
        amount_int = 0;
        amount_frac = 0;
        printf("Please input purchase amount A.B (A <= 9 digits, B <= 2 digits), press ENTER when done:\n");
        ret = getDollarNum(&amount_int, 9, &amount_frac, 2); 
        if (ret)
        {
            errorHandle(ret);
            //return -9;
        }
    }while(ret);

    memset(amount_int_str, 0, STR_LEN);
    transNum(amount_int_str, amount_int);

    //input email address
    do
    {
        memset(local_name, 0, MAX_NAME_LEN+1);
        memset(domain_name, 0, MAX_DOMAIN_LEN+1);
        printf("Please input email address A@B (A's len <= 64, B's len <= 253. '[]' is not support in domain name), press ENTER when done:\n");
        ret = getEmailLname(local_name, MAX_NAME_LEN+1);
        if (ret)
        {
            errorHandle(ret);
            //return -10;
        }
        else
        {
            ret = getEmailDname(domain_name, MAX_DOMAIN_LEN+1);
            if (ret)
            {
                errorHandle(ret);
                //return -11;
            }
        }
    }while(ret);

    // print result
    printf("\nSummary\n");
    printf("=================================================\n");
    printf("Name                       <%s %s>\n", first_name, last_name);
    printf("Credit card number         %c%c%c%c-%c%c%c%c-%c%c%c%c-%c%c%c%c\n",
            credit_str[0], credit_str[1], credit_str[2], credit_str[3],
            credit_str[4], credit_str[5], credit_str[6], credit_str[7],
            credit_str[8], credit_str[9], credit_str[10], credit_str[11],
            credit_str[12], credit_str[13], credit_str[14], credit_str[15]);
    printf("Expiration month and year  <%s %d>\n", monthStr[month-1], year);
    printf("Security code              %d\n", secure_code);
    printf("Zip code                   %d\n", zip);
    printf("Purchase amount            %s.%02d\n", amount_int_str, amount_frac);
    printf("Email address              <%s@%s>\n", local_name, domain_name);
    printf("\n");
    return 0;
}

