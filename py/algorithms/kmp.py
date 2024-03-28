def construct_lps(needle):
    # constructs an array of the longest prefix-suffix (lps)
    # lps can't be the whole string

    lps = [0] * len(needle)
    i = 1
    prev_lps = 0

    while i < len(needle):
        if needle[i] == needle[prev_lps]:
            lps[i] = prev_lps + 1
            prev_lps += 1
            i += 1

        elif prev_lps == 0:
            lps[i] = 0
            i += 1

        else:
            prev_lps = lps[prev_lps-1]
    return lps


def kmp(haystack,needle):
    i = 0
    j = 0
    lps = construct_lps(needle)
    while i < len(haystack):
        if haystack[i] == needle[j]:
            i += 1
            j += 1

        else:
            if j == 0:
                i += 1
            else:
                j = lps[j-1]

        if j == len(needle):
            return i - len(needle)
    return -1


# credits : https://youtu.be/JoF0Z7nVSrA?si=ImYrKV1vuO6lOQie
