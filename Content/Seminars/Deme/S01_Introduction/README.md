---
nav_order: 1
title: 1. შესავალი
parent: დემე
grand_parent: სემინარები
---

# შესავალი

ლინუქსის შელის ინსტრუქციები შეგიძლიათ იხილოთ [აქ](https://ubuntu.com/tutorials/command-line-for-beginners)

# გამოყენებული კოდები და მათი გაშვების ინსტრუქცია

## [gcd](https://github.com/freeuni-paradigms/2021/tree/master/Content/Seminars/Deme/S01_Introduction/gcd)

C კოდის დაკომპილირება და გაშვება

```sh
gcc gcd.c -o gcd
./gcd
```

C++ კოდის დაკომპილირება და გაშვება

```sh
g++ gcd.cpp -o gcd
./gcd
```

Java კოდის დაკომპილირება და გაშვება

```sh
javac GCD.java
java GCD
```

python კოდის გაშვება

```sh
python gcd.py
```

## [c_examples](https://github.com/freeuni-paradigms/2021/tree/master/Content/Seminars/Deme/S01_Introduction/c_examples)

კოდის დასაკომპილირებლად გამოიყენეთ ბრძანება

```sh
gcc <ფაილის სახელი>
./a.out
```

მაგალითად:

```sh
gcc strings.c
./a.out
```

თუ გინდათ რომ გამშვებ ფაილს 'a.out' არ ერქვას გამოიყენეთ -o ფლეგი კომპილაციისას მაგალითად:

```sh
gcc strings.c -o strings
./strings
```
