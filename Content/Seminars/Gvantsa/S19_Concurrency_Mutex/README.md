---
nav_order: 19
title: 19. სრედები - მუტექსი / ქონდიშენები
parent: გვანცა
grand_parent: სემინარები
---

# გარჩეული ამოცანები

## სემაფორის დაწერა მუტექსის გამოყენებით

დაწერეთ სემაფორის ფუნქციების იმპლემენტაცია მუტექსის გამოყენებით

## [ამოხსნა](../../../../exercises/concurrency/sem_using_mutex/sem_using_mutex.cc)

## ბანკის ანგარიშები

მოცემული გაქვთ ანგარიშები გარკვეული რაოდენობის საწყისი თანხით. უნდა დაწეროთ ორი მეთოდის იმპლემენტაცია AmountIn და AmountOut.

### tryTransfer

fromAccountდან უნდა გადავრიცხოთ amount რაოდენობის თანხა toAccountზე. თუ fromAccountზე საკმარისი რაოდენობის თანხა არ იქნა არაფერი არ უნდა ვქნათ.

### transfer

fromAccountდან უნდა გადავრიცხოთ amount რაოდენობის თანხა toAccountზე. თუ საკმარისი თანხა არ არის ანგარიშზე მაშინ ოპერაცია უნდა დაპაუზდეს სანამ ვინმე არ ჩარიცხავს თანხას toAccountზე

> გაითვალისწინეთ რომ, tryTransfer-ის შესრულებისას გადარიცხვა უნდა განხორციელდეს ატომურად თითოეული ექაუნთის წყვილისთვის, ხოლო transfer-ისას შეგიძლიათ amount ჯერ დაარეზერვოთ fromAccount-დან და შემდეგ გადარიცხოთ toAccount-ში.

## [ამოხსნა](../../../../exercises/concurrency/accounts/main.c)
