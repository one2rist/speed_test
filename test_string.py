from datetime import datetime

#check count
g_cnt = 0
#unicode string
g_s = ''
#mutable byte array
byte_g_s = bytearray(g_s, 'utf-16')


if __name__ == "__main__":

    print('test constants:')
    print(g_s)
    print(byte_g_s)
    print(byte_g_s.decode('utf-16'))#back to unicode


    t1 = datetime.now()

    for i in range(3000000):
        byte_g_s.extend(bytearray('a', 'utf-16'))
        byte_g_s.extend(bytearray('sdfjkdhkJHKJHKKJHKJHKJHKJ', 'utf-16'))
        byte_g_s.extend(bytearray('A', 'utf-16'))

    g_s = byte_g_s.decode('utf-16')

    for i in range(0,len(g_s)):
        if g_s[i] == 'A':
            g_cnt+=1;

    t2 = datetime.now()

    print(t2-t1)
    print(len(g_s), g_cnt)
