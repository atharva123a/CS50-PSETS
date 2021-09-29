from cs50 import get_string

def main():
    # get user input:
    text = get_string("Text: ")

    letter_c = letter_count(text)
    print(f"Letter count: {letter_c}")

def letter_count(text):
    i = str()
    letter_count = 0
    word_count = 0
    for i in text:
        if i.isspace() == False and i.isalpha():
            letter_count += 1
    return letter_count

def word_count(text):
    
    #count the words in 
    word.
    
    for i in text:
        if i.isspace() == True:
            
main()