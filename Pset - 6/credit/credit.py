from cs50 import get_string
from sys import exit

credit = []
credit = get_string("Number: ")
sum_2 = 0 # twice the numbers are added;
sum_1 = 0 # only sum of the numbers themselves:


if len(credit) % 2 == 0:
    # the number of digits is an even number:
    for i in range(0, len(credit) ,2):
        num_2 = int(credit[i]) * 2

        if num_2 >= 10:
            sum_2 += (num_2 % 10) + 1
        else:
            sum_2 += num_2

    for l in range(1, len(credit), 2):
        sum_1 += int(credit[l])

    check_sum = sum_1 + sum_2

else:
    # the number of digits are odd:
    for i in range(1, len(credit), 2):
        num_2 = int(credit[i]) * 2

        if num_2 >= 10:
            sum_2 += (num_2 % 10) + 1
        else:
            sum_2 += num_2

    for l in range(0, len(credit), 2):
        sum_1 += int(credit[l])

    check_sum = sum_1 + sum_2

if check_sum % 10 == 0:
    # valid credit card:
    if len(credit) == 15 and credit[0] == "3":
        print("AMEX")
        exit(0)

    elif len(credit) == 16 and credit[0] == "5":
        print("MASTERCARD")
        exit(0)

    elif len(credit) == 13 or 16 and credit[0] == "4":
        print("VISA")
        exit(0)

print("INVALID")
exit(1)