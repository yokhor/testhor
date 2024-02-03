import os, sys

_, good, bad, gen, iters = sys.argv
#sys.stdout = open('log.txt', 'w')

for i in range(1, int(iters) + 1):
    print("Test", i, end=': ')
    os.system(f'./{gen} > input.txt ' + str(i))
    os.system(f'./{good} < input.txt > good.txt')
    os.system(f'./{bad} < input.txt > bad.txt')
    good_answer = open('good.txt').read()
    bad_answer = open('bad.txt').read()
    if good_answer != bad_answer:
        print("WA")
        print("___")
        print("input:")
        print(open('input.txt').read())
        print("___")
        print("correct answer:")
        print(good_answer)
        print("___")
        print("your answer:")
        print(bad_answer)
        print("___")
        break
    else:
        print("OK")

