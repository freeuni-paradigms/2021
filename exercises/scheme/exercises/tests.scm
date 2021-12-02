(load "solution.scm")

(display (if (equal? (reverse_ '()) '()) "1 SUCCESS" "1 FAILURE"))(newline)
(display (if (equal? (reverse_ '(1 2 3)) '(3 2 1)) "2 SUCCESS" "2 FAILURE"))(newline)


(display (if (equal? (max_ '()) 0) "3 SUCCESS" "3 FAILURE"))(newline)
(display (if (equal? (max_ '(4 5 3)) 5) "4 SUCCESS" "4 FAILURE"))(newline)

(display (if (equal? (filter_ positive? '(1 -2 45 -10 -20)) '(1 45)) "5 SUCCESS" "5 FAILURE"))(newline)
(display (if (equal? (filter_ odd? '(4 5 3)) '(5 3)) "6 SUCCESS" "6 FAILURE"))(newline)

(display (if (equal? (max_divisible3 '(4 9 3)) 9) "7 SUCCESS" "7 FAILURE"))(newline)
(display (if (equal? (max_divisible3 '(4 8)) 0) "8 SUCCESS" "8 FAILURE"))(newline)
(display (if (equal? (max_divisible3 '(33 48 22 102)) 102) "9 SUCCESS" "9 FAILURE"))(newline)

(display (if (equal? (range 5) '(1 2 3 4 5)) "10 SUCCESS" "10 FAILURE"))(newline)

(display (if (equal? (pow 5) 32) "11 SUCCESS" "11 FAILURE"))(newline)
(display (if (equal? (pow 1) 2) "12 SUCCESS" "12 FAILURE"))(newline)

(display (if (equal? (generate_powers 4) '(2 4 8 16)) "13 SUCCESS" "13 FAILURE"))(newline)

