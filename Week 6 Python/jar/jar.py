class Jar:
    def __init__(self, capacity=12):
        if capacity < 1:
            raise ValueError ('Wrong capaciy Value')
        self._capacity = capacity
        self._n = 0

    def __str__(self):
        return "🍪" * self._n

    def deposit(self, n):
        if self._n + n > self._capacity:
            raise ValueError ('Exceed capaciy')
        self._n =+ n

    def withdraw(self, n):
        if self._n < n:
            raise ValueError ('Not enough cookies')
        self._n -= n

    @property
    def capacity(self):
        return self._capacity

    @property
    def size(self):
        return self._n

def main():
    jar = Jar()
    print("Capacity:", str(jar.capacity))

    jar.deposit(2)
    print("After depositing 2 cookies:", str(jar))

    jar.withdraw(1)
    print("After withdrawing 1 cookie:", str(jar))

    try:
        jar.deposit(2)
    except ValueError as e:
        print("Error:", str(e))

    try:
        jar.withdraw(5)
    except ValueError as e:
        print("Error:", str(e))

if __name__ == "__main__":
    main()

