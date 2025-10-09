# coding: utf-8
def change(string):
    string =string.replace("!","~")
    string =string.replace("-","<=")
    string =string.replace("+","==")
    return string

def search(string):
    max_char = "a"
    min_char = "z"
    for i in string:
        if i.isalpha():
            if i > max_char:
                max_char = i
            if i < min_char:
                min_char = i
    return [min_char,max_char]

string = raw_input()
string = change(string)
min_char,max_char = search(string)
chars = [chr(i) for i in range(ord(min_char),ord(max_char)+1)]
n = len(chars)
ans = [[],[]]
for i in range(2**n):
    tmp = string
    for j in range(n):
        if (i >> (n - j - 1)) & 1:
            tmp = tmp.replace(chars[j],"1")
        else:
            tmp = tmp.replace(chars[j],"0")
    ans[eval(tmp)].append(i)
if len(ans[1]) == 0:
    print "0",
else:
    print ' ∨ '.join("m%s" % i for i in ans[1]),
print ";",
if len(ans[0]) == 0:
    print "1",
else:
    print ' ∧ '.join("M%s" % i for i in ans[0]),