def merge_lists_common_elements(l1, l2):
    l = []
    for i in l1:
        for j in l2:
            if i == j:
                l.append(i)
    return l

l1 = [1,2,3,4,5]
l2 = [1,2,3,4,5,6]

print(merge_lists_common_elements(l1, l2))