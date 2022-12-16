# generate 1000 test files
# file containing two integers, separated by a space
# first integer is in range [1, 100]
# second integer is in range [1, 60]

import random
import os


def generate():
    for i in range(101, 121):
        with open(os.path.join('input', str(i) + '.in'), 'w') as f:
            f.write(str(random.randint(10, 50)) +
                    ' ' + str(random.randint(1, 5)))


if __name__ == '__main__':
    generate()
