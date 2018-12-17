import sys

def     print_doubles(setted, mylist, line_nb, room_end):
    error = 0
    for room in setted:
        if (mylist.count(room) > 1 and room != room_end):
            print("At line " + str(line_nb) + ' room named ' + room + ' is duplicated')
            error += 1
    return (error)

def   checkdouble(line, line_nb, room_end):
    list = []
    i = 0
    for char in line:
        i += 1
        if (char == '-'):
            j = -1
            for char in line[i:]:
                j += 1
                if char == ' ':
                    break
            list.append(line[i:i+j]) 
    setted = set(list)
    if len(setted) != len(list):
        return print_doubles(setted, list, line_nb, room_end);
    return 0

line_nb = 0
std = []
for line in sys.stdin:
    std.append(line)
last = std[-1]
j = 0
for char in last:
    j += 1
    if (char == '-'):
        k = -1
        for char in line[j:]:
            k += 1
            if char == ' ':
                break
        room_end = last[j:j+k]
error = 0
for line in std:
    line_nb += 1
    error += checkdouble(line, line_nb, room_end)
if error:
    print("\033[31mThere are " + str(error) + " errors in your lemin output.\033[0m")
else:
    print("\033[32mYour lemin output is perfect! Well done!\033[0m")
