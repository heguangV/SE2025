def change(string): 
    string =string.replace("!","~") 
    string =string.replace("-","<=") 
    string =string.replace("+","==") 
    return string 
 
def search(string): 
    max = "a" 
    min = "z" 
    for i in string: 
        if i.isalpha(): 
            if i > max: 
                max = i 
            if i < min: 
                min = i 
    return [min,max] 
 
string = input() 
string = change(string) 
min,max = search(string) 
chars = [chr(i) for i in range(ord(min),ord(max)+1)] 
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
    print("0",end="") 
else: 
    print(' ∨ '.join(f"m{i}" for i in ans[1]),end="") 
print(" ; ",end="") 
if len(ans[0]) == 0: 
    print("1",end="") 
else: 
    print(' ∧ '.join(f"M{i}" for i in ans[0]),end="")  