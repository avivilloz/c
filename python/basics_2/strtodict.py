def str_to_dict(str):
    d = dict()
    for c in str:
        d.setdefault(c, 0)
        d[c] += 1
    return d

d = str_to_dict("helllllllllllllo")
print(d)