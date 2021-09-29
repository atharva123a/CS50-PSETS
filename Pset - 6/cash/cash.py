from sys import exit
from cs50 import get_float
import math

def main():

    #get a positive cash owned value converted to cents from dollars:
    change = get_change()
    coins = int()

    if change >= 25:
        if change % 25 == 0:
            coins += change / 25
            print("{:.0f}".format(coins))
            exit(0)

        else:
            coins += math.floor(change / 25)
            change -= (coins * 25)

    if change >= 10:
        if change % 10 == 0:
            coins += change / 10
            print("{:.0f}".format(coins))
            exit(0)

        else:
            coins += math.floor(change / 10)
            change -= math.floor(change / 10) * 10

    if change >= 5:
        if change % 5 == 0:
            coins += change / 5
            print("{:.0f}".format(coins))
            exit(0)

        else:
            coins += math.floor(change / 5)
            change -= math.floor(change / 5) * 5

    if change >= 1:
        if change  % 1 == 0:
            coins = coins + (change / 1)
            print("{:.0f}".format(coins))
            exit(0)

    print("{:.0f}".format(coins))

def get_change():

    # get's the change from the user
    while True:
        change = get_float("Change owned : ")

        if change > 0:
            break

    return change * 100

main()