#include "stringUtils.h"

uint16 strlength(string ch)
{
    uint16 i = 0;
    while(ch[++i]);
    return i;
}

bool strEql(string ch1,string ch2)                     
{
    /* Zero from strcmp means ch1 eq ch2 */
    return strcmp(ch1, ch2) == 0;
}

// Compare two strings. Should return -1 if 
// str1 < str2, 0 if they are equal or 1 otherwise.
uint8 strcmp(string str1, string str2)
{
    int i = 0;
    int failed = 0;
    while(str1[i] != '\0' && str2[i] != '\0')
    {
        if(str1[i] != str2[i])
        {
            failed = 1;
            break;
        }
        i++;
    }
    // why did the loop exit?
    if((str1[i] == '\0' && str2[i] != '\0') || (str1[i] != '\0' && str2[i] == '\0'))
        failed = 1;
    return failed;
}

// Copy the NULL-terminated string src into dest, and
// return dest.
string strcpy(string dest, string src)
{
    do
      *dest++ = *src++;
    while (*src != 0);
    return dest;
}

// Concatenate the NULL-terminated string src onto
// the end of dest, and return dest.
string strcat(string dest, string src)
{
    while (*dest != 0) {
        *dest = *dest;
        dest++;
    }

    do
        *dest++ = *src++;
    while (*src != 0);
    return dest;
}

bool isspace(char ch) {
    return (ch == ' ') || (ch == '\t') || (ch == '\r') || (ch == '\n') || (ch == '\f') || (ch == '\0');
}

bool isnum(char ch) {
    return (ch >= '0') && (ch <= '9');
}

string strTrim(string str)
{
    uint16 len = 0;
    string frontp = str;
    string endp = 0;

    if(str == 0)
        return 0;
    if(str[0] == '\0')
        return str;

    len = strlength(str);
    endp = str + len;

    /* Move the front and back pointers to address the first non-whitespace
     * characters from each end.
     */
    while(isspace(*frontp))
        ++frontp;
    if(endp != frontp)
    {
        while(isspace(*(--endp)) && endp != frontp) {}
    }

    if(str + len - 1 != endp)
        *(endp + 2) = '\0';
    else if(frontp != str && endp == frontp)
        *str = '\0';

    /* Shift the string so that it starts at str so that if it's dynamically
     * allocated, we can still free it on the returned pointer.  Note the reuse
     * of endp to mean the front of the string buffer now.
     */
    endp = str;
    if(frontp != str)
    {
        while(*frontp)
            *endp++ = *frontp++;
        *endp++ = '\0';
    }

    return str;
}

#define INT_DIGITS 19       /* enough for 64 bit integer */

/*
 * Copied from opensource apple com. I only modified a little...
 */
string itos(int i)
{
    /* Room for INT_DIGITS digits, - and '\0' */
    static char buf[INT_DIGITS + 2];
    string p = buf + INT_DIGITS + 1;  /* points to terminating '\0' */
    bool isNeg = false;
    if (i < 0) {
        isNeg = true;
        i = -i;
    }
    do {
        *--p = '0' + (i % 10);
        i /= 10;
    } while (i != 0);
    if (isNeg) {
        *--p = '-';
    }
    return p;
}

int ctoi(char c)
{
    switch(c) {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    default: return -1;
    }
}

int stoi(string s)
{
    int msg = 0;
    uint16 i = 0;
    while(s[i]) {
        if (isnum(s[i])) {
            msg *= 10;
            msg += ctoi(s[i]);
        } else break;
        i++;
    }
    return msg;
}
