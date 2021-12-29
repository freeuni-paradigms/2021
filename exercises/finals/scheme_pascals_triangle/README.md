---
nav_order: 6
title: Scheme - pascal triangle
parent: ფინალური გამოცდის საკითხების მაგალითები
grand_parent: სავარჯიშოები
---


# პასკალის სამკუთხედის სტრიქონის პოვნა - სქემა
გადმოგეცემათ ნატურალური რიცხვი i და უნდა იპოვოთ პასკალის სამკუთხედში i-ური სტრიქონი.

<img src="https://cdn.mos.cms.futurecdn.net/LH5vimYVrei3iDU2sgDM2G-1200-80.jpg" width=500 height=300>

პასკალის სამკუთხედში სტრიქონის იწყება და მთავრდება 1-ით ხოლო ყოველი სხვა წევრი მიიღება წინა ხაზზე მარცხენა და მარჯვენა წევრის ჯამით.

ინდექსები იწყება 1-დან ანუ პირველი სტრიქონი არის '(1), მეორე სტრიქონი არის '(1 1) და ა.შ.

ამოხსნა დაწერეთ triangle.scm ფაილში ხოლო სამაგალითო ტესტები მოცემულია tests.scm ფაილში. ტესტის გამოტანილ პასუხში პირველი რიცხვი აღნიშნავს რომელი ინდექსისთვის იყო გაშვებული ტესტი.

**Kawa-ს გამოყენება**
ტერმინალში გაუშვით შემდეგი ბრძანება: **kawa tests.scm**