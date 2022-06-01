def rotate_list_left(l, n):
    l = l[n:] + l[:n]
    return l

l = [1,2,3,4,5,6]

print(rotate_list_left(l, 3))