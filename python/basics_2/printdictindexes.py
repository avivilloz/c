def print_dict_indexes(d):
    keys_list = list(d)
    for i in range(0, len(keys_list)):
        print("index: {}, key: {}, value: {}".format(i, keys_list[i], d[keys_list[i]]))

d = {'a': "hello", 'b': "hi", 'c': "oi"}
print_dict_indexes(d)