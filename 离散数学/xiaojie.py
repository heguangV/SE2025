def sep(string): 
    res = string.split('&') 
    return set(frozenset(item.replace("(","").replace(")","").split('|')) for item in res)  
 
def resolve(s1,s2): 
    for i in s1: 
        if i[0] == '!': 
            neg_i = i[1:] 
        else: 
            neg_i = '!' + i 
        if neg_i in s1: 
            return {1} 
        if neg_i in s2: 
            res = (s1 | s2) - {i, neg_i} 
            return res 
    return None 
 
def judge(s0,s1,s2,s_0,s_1): 
    for i in s_0: 
        for j in s_1: 
            res = resolve(i,j) 
            if res is not None: 
                if len(res) == 0: 
                    return "No" 
                if res == {1}: 
                    return "Yes" 
                if res not in s0 and res not in s1 and res not in s2: 
                    s2.add(frozenset(res)) 
    return None 
 
string = input() 
string = sep(string) 
s0 ,s1, s2= set(),string,set() 
while True: 
    res = judge(s0,s1,s2,s0,s1) 
    if res is not None: 
        print(res) 
        break 
    res = judge(s0,s1,s2,s1,s1) 
    if res is not None: 
        print(res) 
        break 
    if not s2: 
        print("Yes") 
        break 
    s0.update(s1) 
    s1 = s2.copy() 
    s2.clear()  