f = open("C:\\Users\\Alessandro Vendrame\\Desktop\\Scuola\\IIoT-anno2\\Python-Mungherli\\PrintaFile\\vocaboularyFixed.txt", "r")

nlettere = int(input("Inserisci il numero di lettere che deve avere la parola: "))

v = []

lines = f.readlines()

for l in lines:
    if len(l) == nlettere:
        v.append(l)

for word in v: 
    if (word[1] == "e") and (word[3] == "s") and (word[4] == "t"):
        print(word)