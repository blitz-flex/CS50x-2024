from cs50 import get_int

while True:
    us_input = get_int("Height: ")
    if us_input > 0 and us_input < 9:
        break
    
for i in range(1, us_input + 1):
    j = us_input - i

    print(" " * j, end="")
    print("#" * i, end="")

    print("  ", end="")

    print("#" * i)


