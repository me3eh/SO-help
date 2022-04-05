#przyklad
#print("Hello world")
#word = input("Podaj slowo:")
#number = input("Podaj liczbe:")
#print("Napisales slowo {}".format(word))
#print("Liczba + 10 = {}".format(int(number)+10))

#zadanie 1
# name = input("Podaj imie")
# last_name = input("Podaj nazwisko")
# print(last_name + ', ' + name)

#zadanie 2
#name = input("Podaj imie oraz nazwisko")
#names = name.split(" ")
#print(names[1] + ", " + names[0])

#zadanie3
# import math
# x = input("Podaj po spacji wspolrzedne pierwszego punktu")
# xy1 = x.split(" ")
# for i in range(len(xy1)):
    # xy1[i] = float(xy1[i])
# x = input("Podaj po spacji wspolrzedne drugiego punktu")
# xy2 = x.split(" ")
# for i in range(len(xy1)):
    # xy2[i] = float(xy2[i])
# print(round(math.sqrt((xy2[1]-xy1[1])**2 + (xy2[0]-xy1[0])**2),2))

# zadanie 4
# guests = input("Number of guests:")
# pizza_slices = 32
# print("Option 1: " , pizza_slices // int(guests),  "slices each, ",  pizza_slices % int(guests), "left over")
# print("Option 2: ", round(pizza_slices / int(guests), 1), "slices each")

# #zadanie 5
# for i in input("Podaj swoje zdanko:\n").split(" ")[::-1]:
#     print(i)

#zadanie 6
# length = input("Dlugosc weza: ")
# print("Wielkosc klatki: ", end="")
# print(((int(length) - 6) * 0.75 + 6 * 0.5) if int(length) >=6 else int(length) * 0.5)

#zadanie 7 a)
# arr = []
# for i in range(10):
#    arr.append(i**2) 
# for i in range(10):
    # print(arr[i])


# guests = int(input("Number of guests:"))
# print("Option 1: " , 32 // guests,  "slices each, ",  32 % guests, "left over\nOption 2: ", round(32 / guests, 1), "slices each")

length = input("Dlugosc weza: ")
print("Wielkosc klatki: ", ((int(length) - 6) * 0.75 + 6 * 0.5) if int(length) >=6 else int(length) * 0.5)