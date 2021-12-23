"""
1.
დაწერეთ map-ის იმპლემენტაცია და მისი გამოყენებით დაწერეთ ორი ამოცანა
    1. გადმოგეცემათ რიცხვების ლისტი და ამ ლისტებისთვის დააბრუნეთ სია სადაც ეწერება True თუ რიცხვი ლუწია და False თუ კენტია
    2. გადმოგეცემათ რიცხვების ლისტი და ამ ლისტებისთვის დააბრუნეთ სია სადაც ეწერება False თუ რიცხვი ლუწია და True თუ კენტია
"""


from time import time, sleep


def my_map(func, lst):
    result = []
    for elem in lst:
        result.append(func(elem))

    return result


def is_odd(n):
    return n % 2 == 1


def is_even(n):
    return n % 2 == 0


lst = [1, 2, 3, 4, 5, 6, 7]
# print(my_map(is_even, lst))
# print(my_map(is_odd, lst))


"""
2.
შიდა ფუნქციები.
რას დაბეჭდავს parent() ფუნქცია
"""


def parent():
    print("Printing from the parent() function")

    def first_child():
        print("Printing from the first_child() function")

    def second_child():
        print("Printing from the second_child() function")

    first_child()
    second_child()


# parent()

"""
3.
დაწერეთ ფუნქცია რომელიც დააბრუნებს ფუნქციას რომელიც ამოწმებს რიცხვის ლუწობას თუ გადავცემთ პარამეტრად "EVEN"-ს და
დააბრუნებს ფუნქციას რომელიც ამოწმებს რიცხვის კენტობას თუ გადავცემთ პარამეტრად "ODD"-ს
"""


def get_func(key):
    d = {
        "EVEN": is_even,
        "ODD": is_odd
    }
    return d[key]


"""
4.
დაწერეთ მარტივი დეკორატორი რომელიც ფუნქციის დაწყებისას დაბეჭდავს დაწყების დროს და დასრულებისასაც დაბეჭდავს დასრულების დროს და რამდენ ხანში დასრულდა
"""


def decorator(func):

    def wrapper():
        start = time()
        print(f"Start: {start}")
        func()
        end = time()
        print(f"End: {end}")
        print(f"Elapsed: {end - start}")

    return wrapper


@decorator
def just_sleep():
    sleep(1)


# just_sleep()
"""
5.
დაწერეთ დეკორატორი რომელიც ორჯერ გამოიძახებს ფუნქციას
"""


def do_twice(func):

    def wrapper():
        func()
        func()

    return wrapper


@do_twice
def print_hello():
    print("Hello!")


"""
6.
დაწერეთ ფუნქცია რომელსაც გადაეცემა n და აბრუნებს ფიბონაჩის მიმდევრობის n-ურ წევრს
"""


def memoize(func):
    cache = {}

    def wrapper(n):
        if n not in cache:
            cache[n] = func(n)
        return cache[n]

    return wrapper


@memoize
def fib(n):

    if n < 2:
        return n

    return fib(n - 1) + fib(n - 2)


# start = time()
# print(f"Start: {start}")
# fib(40)
# end = time()
# print(f"End: {end}")
# print(f"Elapsed: {end - start}")


"""
7.
დაწერეთ გენერატორი რომელიც აბრუნებს ფიბონაჩის მიმდევრობის წევრებს რომელიც limitზე ნაკლებია
"""


def gen_fib(limit):
    first, second = 0, 1
    while first < limit:
        yield first
        first, second = second, first + second


for i in fib:
    print(i)
