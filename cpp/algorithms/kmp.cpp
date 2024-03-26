#include <vector>
#include <string>
#include <cassert>
#include <iostream>

std::vector<int> construct_lps(std::string needle)
{
    std::vector<int> lps(needle.length(),0);
    int i = 1, prev_lps = 0;
    while (i < needle.length())
    {
        if (needle[i] == needle[prev_lps])
        {
            lps[i] = prev_lps + 1;
            prev_lps += 1;
            i += 1;
        }
        else if (prev_lps == 0)
        {
            std::cout << i;
            lps[i] = 0;
            i += 1;
        }
        else
        {
            prev_lps = lps[prev_lps - 1];
        }
    }
    return lps;
}

int kmp(std::string haystack, std::string needle)
{
    int i = 0, j = 0;
    std::vector<int> lps = construct_lps(needle);
    while (i < haystack.length())
    {
        if (haystack[i] == needle[j])
        {
            i += 1;
            j += 1;
        }
        else
        {
            if (j == 0)
            {
                i += 1;
            }
            else
            {
                j = lps[j - 1];
            }
        }
        if (j == needle.length())
        {
            return i - (needle.length());
        }
    }
    return -1;
}

int main(int argc, char const *argv[])
{
    std::string haystack = "fireinthehole";
    std::string needle = "in";
    assert(kmp(haystack, needle) == 4);
    return 0;
}
