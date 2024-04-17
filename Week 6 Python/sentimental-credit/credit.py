from cs50 import get_string


def main():
    number = get_string("Number: ")

    # შეოწმება ბარათის ნომერის ლეგიტიმურობა
    if card_legit(number):
        if card_visa(number):
            print("VISA")
        elif card_amex(number):
            print("AMEX")
        elif card_mastercard(number):
            print("MASTERCARD")
        else:
            print("INVALID")
    else:
        print("INVALID")


def card_mastercard(number):
    if len(number) == 16:

        # Check card_number starts with 51, 52, 53, 54, 55
        prefixes = ["51", "52", "53", "54", "55"]
        for fix in prefixes:
            if number.startswith(fix):
                return True


def card_amex(number):
    if len(number) == 15 and (number.startswith("34") or number.startswith("37")):
        return True


def card_visa(number):
    if (len(number) == 13 or len(number) == 16) and number.startswith("4"):
        return True

# Function to check if the card number is legitimate using the Luhn's algorithm


def card_legit(number):
    sum = 0
    every_other_digit = number[-2::-2]

    # Iterate through every other digit, starting from the second-to-last digit
    for char in every_other_digit:
        in_card = int(char) * 2
        if in_card > 9:
            in_card -= 9

        sum += in_card

    not_multiplied_digits = number[-1::-2]

    # დარჩენილი ციფრის გამეორება

    for char in not_multiplied_digits:
        sum += int(char)

    # Check if the sum is a multiple of 10 (passes the Luhn's algorithm

    if sum % 10 == 0:
        return True


main()
