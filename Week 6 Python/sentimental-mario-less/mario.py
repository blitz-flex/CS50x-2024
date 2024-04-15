from cs50 import get_int

while True:
    us_input = get_int("Height: ")
    if us_input > 0 and us_input < 9:
        break


for i in range(0, us_input, 1):
    for j in range(0, us_input, 1):
        if i + j < us_input - 1:
            print(" ", end="")
        else:
            print("#", end="")

    print()
