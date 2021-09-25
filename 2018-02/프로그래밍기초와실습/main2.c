#include <stdio.h>
#include <stdlib.h>

int main()
{
    int year, month, date;
    int leap_check = 0;
    int month_assign = 0;
    int anniv;

    do
    {
        printf("Input the year : ");
        scanf("%d", &year);

        if(((year%4==0)&&(year%100 != 0))||(year%400==0))
            leap_check = 1;
        else
            leap_check = 0;

        if(year == 0)
            break;
        else if(year < 0)
        {
            printf("Wrong Number!\n");
            continue;
        }

        printf("Input the month : ");
        scanf("%d", &month);

        if(month == 0)
            break;
        else if((month < 0)||(month > 12))
        {
            printf("Wrong Number!\n");
            continue;
        }

        printf("Input the date : ");
        scanf("%d", &date);

        switch(month)
        {
        case 2:
            if(leap_check == 0)
                month_assign = 28;
            else if(leap_check == 1)
                month_assign = 29;
            break;
        case 4:
            month_assign = 30;
            break;
        case 6:
            month_assign = 30;
            break;
        case 9:
            month_assign = 30;
            break;
        case 11:
            month_assign = 30;
            break;
        default:
            month_assign = 31;
            break;
        }

        if((date < 1)||(date > month_assign))
        {
            printf("Wrong Number!\n");
            continue;
        }

        printf("Input the anniversary : ");
        scanf("%d", &anniv);

        if(anniv < 0)
        {
            printf("Wrong Number!\n");
            continue;
        }

        for(int i = 0; i < anniv-1; i++)
        {
            date++;

            if(((year%4==0)&&(year%100 != 0))||(year%400==0))
                leap_check = 1;
            else
                leap_check = 0;

            switch(month)
            {
            case 2:
                if(leap_check == 0)
                    month_assign = 28;
                else if(leap_check == 1)
                    month_assign = 29;
                break;
            case 4:
                month_assign = 30;
                break;
            case 6:
                month_assign = 30;
                break;
            case 9:
                month_assign = 30;
                break;
            case 11:
                month_assign = 30;
                break;
            default:
                month_assign = 31;
                break;
            }

            if(date > month_assign)
            {
                month++;
                date = 1;
            }

            if(month > 12)
            {
                year++;
                month = 1;
            }
        }

        printf("%d %d %d\n", year, month, date);

    } while(1);

    return 0;
}
