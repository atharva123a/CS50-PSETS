from cs50 import get_int

def main():
    #main function:
    size = get_positive_int()

    for i in range(size):

        # printing empty spaces:
        k = size - i - 1

        while k > 0:
            print(" ", end = "")
            k -= 1

        # first set of hashes:
        for hashes  in range(i + 1):
            print("#", end  = "")

        print("  ", end = "")
        # next set of hashes:
        for n_hashes in range(i + 1):
            print("#", end = "")

        #new line
        print()


def get_positive_int():

    while True:
        size = get_int("Size: ")

        if size >= 1 and size <= 8:
            break

    return size

main()

