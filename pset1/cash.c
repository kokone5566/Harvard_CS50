#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float dollars;
    do
    {
        dollars = get_float("Change owed: ");
    }while(dollars <= 0);
    int cent = round( 100 * dollars );
    int counter = 0;
    int changes[] = {25, 10, 5, 1};
    for (int i = 0; i < 4; i++)
    {
        if ( cent/changes[i] >= 1)
        {
            counter += cent/changes[i];
            cent -= cent/changes[i]*changes[i];
        }
    }
    printf("%i\n", counter);
    
}
