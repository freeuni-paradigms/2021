"""
1.
დაწერეთ map-ის იმპლემენტაცია და მისი გამოყენებით დაწერეთ ორი ამოცანა
1. გადმოგეცემათ რიცხვების ლისტი და ამ ლისტებისთვის დააბრუნეთ სია სადაც ეწერება True თუ რიცხვი ლუწია და False თუ კენტია
2. გადმოგეცემათ რიცხვების ლისტი და ამ ლისტებისთვის დააბრუნეთ სია სადაც ეწერება False თუ რიცხვი ლუწია და True თუ კენტია
"""
print("####################### Problem 1 #######################")
def my_map(func, lst):
    new_list = []

    for elem in lst:
        new_list.append(func(elem))
    return new_list

def is_even(num):
    return num % 2 == 0

def is_odd(num):
    return num % 2 == 1

print(my_map(is_even, [1, 2, 3, 4, 5]))
print(my_map(is_odd, [1, 2, 3, 4, 5]))
print()
"""
2.
შიდა ფუნქციები.
რას დაბეჭდავს parent() ფუნქცია
"""
print("####################### Problem 2 #######################")

def parent():
    print("Printing from the parent() function")

    def first_child():
        print("Printing from the first_child() function")

    def second_child():
        print("Printing from the second_child() function")

    first_child()
    second_child()

parent()
print()

"""
3.
დაწერეთ ფუნქცია რომელიც დააბრუნებს ფუნქციას რომელიც ამოწმებს რიცხვის ლუწობას თუ გადავცემთ პარამეტრად "EVEN"-ს და
დააბრუნებს ფუნქციას რომელიც ამოწმებს რიცხვის კენტობას თუ გადავცემთ პარამეტრად "ODD"-ს
"""
print("####################### Problem 3 #######################")

def func_generator(func_name):
    def is_even(num):
        return num % 2 == 0

    def is_odd(num):
        return num % 2 == 1
    
    mapping = {
        "EVEN": is_even,
        "ODD": is_odd
    }

    return mapping[func_name]

print(func_generator("EVEN")(2))
print(func_generator("ODD")(2))
print()

"""
4.
დაწერეთ მარტივი დეკორატორი რომელიც ფუნქციის დაწყებისას დაბეჭდავს დაწყების დროს და დასრულებისასაც დაბეჭდავს დასრულების დროს და რამდენ ხანში დასრულდა
"""
print("####################### Problem 4 #######################")

from time import time, sleep

def time_decorator(func):

    def wrapper():
        start_time = time()
        print(f'Start: {start_time}')
        func()
        end_time = time()
        print(f'End: {end_time}')
        print(f'Elapsed time: {end_time - start_time}')

    return wrapper

@time_decorator
def just_sleep():
    sleep(3)

# just_sleep = time_decorator(just_sleep)
just_sleep()
print()

"""
5.
დაწერეთ დეკორატორი რომელიც ორჯერ გამოიძახებს ფუნქციას
"""
print("####################### Problem 5 #######################")

def do_twice(func):

    def wrapper():
        func()
        func()

    return wrapper

@do_twice
def hello_world():
    print("Hello World!")

hello_world()
print()

"""
6.
დაწერეთ ფუნქცია რომელსაც გადაეცემა n და აბრუნებს ფიბონაჩის მიმდევრობის n-ურ წევრს
"""
print("####################### Problem 6 #######################")

def memoize(func):
    memo = {}
    def wrapper(n):
        if n not in memo:
            memo[n] = func(n)
        return memo[n]
    return wrapper 

@memoize
def fib(n):
    if n < 2:
        return n
    
    return fib(n - 1) + fib(n - 2)

@time_decorator
def rame():
    fib(40)

rame()
print()


"""
7.
დაწერეთ გენერატორი რომელიც აბრუნებს ფიბონაჩის მიმდევრობის წევრებს
"""
print("####################### Problem 7 #######################")
def fib_generator(n):
    a, b = 0, 1

    for _ in range(n):
        yield a
        a, b = b, a + b

for fib_num in fib_generator(20):
    print(fib_num)

