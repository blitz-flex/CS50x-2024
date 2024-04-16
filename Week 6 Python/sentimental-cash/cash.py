from cs50 import get_float


def main():
    # Ask how many cents the customer is owed
    cents = get_cents()

    quarters = cal_quarters(cents)
    cents = cents - quarters * 25

    dimes = cal_dimes(cents)
    cents = cents - dimes * 10

    nickels = cal_nickels(cents)
    cents = cents - nickels * 5

    penniels = cal_penniels(cents)

    total = quarters + dimes + nickels + penniels

    print(total)


def get_cents():
    while True:
        change = get_float("Change owed: ")
        if change >= 0:
            break
    cents = round(change * 100)
    return cents


def cal_quarters(cents):
    count = 0
    while cents >= 25:
        cents = cents - 25
        count += 1
    return count


def cal_dimes(cents):
    count = 0
    while cents >= 10:
        cents = cents - 10
        count += 1
    return count


def cal_nickels(cents):
    count = 0
    while cents >= 5:
        cents = cents - 5
        count += 1
    return count


def cal_penniels(cents):
    count = 0
    while cents >= 1:
        cents = cents - 1
        count += 1
    return count


main()
