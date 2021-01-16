# DATA LA STRINGA SCRITTA ALLA LAVAGNA, SCRIVERE UN CODICE
# CHE DECIFRI LA STRINGA E LA STAMPI A VIDEO

crypt_string = "VCZJCZIZJMZJLXYHMJYHEMCWSJM\WZNCXWJSYQXWZCOXJHMCJDVSOJ\HYHWWZOH@" #LA J EQUIVALE ALLO SPAZIO

dictionary = []
latin_phrase = []
word = []

#SEGNARSI QUANTE SONO LE LETTERE, CONFRONTI LA FREQUENZA DELLE LETTERE CON LA FREQUENZA DELLE LETTERE LATINE

for letter in crypt_string:
    if letter == "J" or letter == "@":
        latin_phrase.append(word)
        word = []
    else:
        word.append(letter)

dictionary = fr.readlines()

for cryp_word in latin_phrase:
    cmp_wrd = ""
    for crypt_letter in cryp_word:
        cmp_wrd += crypt_letter
    
    print(cmp_wrd + " Lunghezza: " + str(len(cmp_wrd)))

    print("Words like this: ")

    for dict_word in dictionary:
        wrd_len = len(dict_word)-1

        if  wrd_len== len(cmp_wrd):
            print(len(dict_word))
            print("      " + dict_word)

    ciao = input("STOP")
