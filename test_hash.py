from datetime import datetime
import random
import string


KEY_SIZE=5
MAP_SIZE=100000
TEST_LOOP=100

if __name__ == "__main__":

    #set of keys to find in hash table
    test_keys = set()
    for i in range(MAP_SIZE):
        test_keys.add(''.join(random.choice(string.ascii_letters) for _ in range(KEY_SIZE)))

    #create hash table
    hash_map  = {}
    for i in range(MAP_SIZE):
        hash_map[''.join(random.choice(string.ascii_letters) for _ in range(KEY_SIZE))] = 0

    print('Test set size: ', len(test_keys), MAP_SIZE)
    #print(test_keys)
    print('Test map size: ', len(hash_map),  MAP_SIZE)
    #print(hash_map)

    t1 = datetime.now()

    found_count = 0;
    for i in range(TEST_LOOP):
        for key in test_keys:
            if key in hash_map:
                found_count += 1;

    t2 = datetime.now()
    print('Loops        : ', TEST_LOOP)
    print('Found        : ', found_count // TEST_LOOP)
    print('Time         : ', t2-t1)
