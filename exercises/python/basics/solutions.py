"""
1. გაუცვალეთ ორ ცვლადს მნიშვნელობები
"""
a = 1
b = 2

a, b = b, a

"""
2. შეატრიალეთ ლისტი
"""
lst = [1, 2, 3, 4, 5, 6]

# result = []
# for i in range(len(lst) - 1, -1, -1):
#     result.append(lst[i])

result = lst[::-1]
"""
3. შეამოწმეთ არის თუ არა რიცხვი პალინდრომი
"""
number = 798

result = number == int(str(number)[::-1])

"""
4. მოცემულია n და k დაწერეთ ფუნცია რომელიც დააბრუნებს k-ს პირველ n ხარისხს
"""


def generate_powers(n, k):
    lst = list(range(1, n + 1))
    return list(map(lambda x: k ** x, lst))
    # return list(map(lambda x: k ** x, range(1, n + 1)))


"""
5. მოცემულია ლისტი და ელემენტი დაწერეთ ფუნქცია რომელიც დააბრუნებს ლისტში რომელ ინდექსებზე გვხვდება ეს ელემენტი
"""


def elem_indexes(lst, elem):

    # result = []
    # for index, value in enumerate(lst):
    #     if value == elem:
    #         result.append(index)
    # return result

    # filtered_lst = filter(lambda x: x[1] == elem, enumerate(lst))
    # return list(map(lambda x: x[0], filtered_lst))

    return [index for index in range(len(lst)) if lst[index] == elem]


"""
6. დაწერეთ ქუიქ სორტის ალგორითმი
"""


def quicksort(sequence):
    if len(sequence) == 0:
        return []

    first_elem = sequence[0]
    left = [value for value in sequence[1:] if value < first_elem]
    right = [value for value in sequence[1:] if value >= first_elem]
    return quicksort(left) + [first_elem] + quicksort(right)
