#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long num;
    do
    {
        num = get_long("Number: ");
    }
    while (num <= 0);

    int sum = 0;
    int digit = 0;
    int remain = 0;

    while (num > 0)
    {
        if ((digit + 1) % 2 == 1)
        {
            sum += num % 10;
        }
        else
        {
            int tmp = (num % 10) * 2;
            while (tmp > 0)
            {
                sum += tmp % 10;
                tmp /= 10;
            }
        }
        num /= 10;
        digit += 1;
        if (num < 100 && remain < num)
        {
            remain = num;
        }
    }

    //printf("%i, %ld, %i", digit, num, sum);
    //printf("%d", remain/10 ==4);
    //determine which card

    if (sum % 10 != 0)
    {
        printf("INVALID\n");
    }    
    else if (digit == 15 && (remain == 34 || remain == 37))
    {
        printf("AMEX\n");
    }
    else if ((digit == 13 || digit == 16) && remain / 10 == 4)
    {
        printf("VISA\n");
    }
    else if (digit == 16)
    {
        int prefix[] = {51, 52, 53, 54, 55};
        bool contain = false;
        for (int i = 0; i < 5; i++)
        {
            if (remain == prefix[i])
            {
                contain = true;
                break;
            }
        }
        if (contain == true)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }




}
