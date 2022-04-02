
#ifndef UTILS_HPP
# define UTILS_HPP

int ft_atoi(char* s)
{
    int n = 0;
    while( *s >= '0' && *s <= '9' ) {
        n *= 10;
        n += *s++;
        n -= '0';
    }
    return n;
}

#endif