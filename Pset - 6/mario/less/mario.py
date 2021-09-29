from sys import exit
from cs50 import get_int

def main():

    # prompt the user for a size:
    size = get_positive_int()
    for i in range(size):
        k = size - i - 1
        while (k > 0):
            print(" ", end = '')
            k -= 1

        for j in range(i + 1):
            print("#", end = '')

        print()

def get_positive_int():

    while True:
        size = get_int("Size: ")

        if size >= 1 and size <= 8:
            break

    return size

main()

