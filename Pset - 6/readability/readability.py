from cs50 import get_string
import math

def main():
    # get user input:
    text = get_string("Text: ")

    letter_c = letter_count(text)

    word_c = word_count(text)

    sentence_c = sentence_count(text)

    #apply the coleman, lieu index:
    L = (100 * letter_c) / word_c
    S = (100 * sentence_c) / word_c

    index = int()
    index = (0.0588 * L - 0.296 * S - 15.8)

    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print("Grade {:.0f}".format(index))

def letter_count(text):
    i = str()
    letter_count = 0
    word_count = 0
    for i in text:
        if i.isspace() == False and i.isalpha():
            letter_count += 1
    return letter_count

def word_count(text):

    #count the words in word_count and return that to main:
    word_coun = 0
    i = str()
    for i in text:
        if i.isspace() == True:
            word_coun += 1
    return word_coun

def sentence_count(text):

    sentence_coun = 0

    i = str()
    for i in text:
        if i == "?" or i == "!" or i == ".":
            sentence_coun += 1

    return sentence_coun
main()