(load "PATH/solution.scm")

(display (if (equal? (k-th-element '(1 2 3) 2) 3) "1 SUCCESS" "1 FAILURE"))(newline)
(display (if (equal? (k-th-element '() 0) "None") "2 SUCCESS" "2 FAILURE"))(newline)


(display (if (equal? (filter-range '(1 2 3 4) 2 4) '(2 3 4)) "3 SUCCESS" "3 FAILURE"))(newline)
(display (if (equal? (filter-range '(1 2 3 4) 9 14) '()) "4 SUCCESS" "4 FAILURE"))(newline)
(display (if (equal? (filter-range '(1 2 3 4) 4 1) '(1 2 3 4)) "5 SUCCESS" "5 FAILURE"))(newline)


(display (if (equal? (prime? 2) #t) "6 SUCCESS" "6 FAILURE"))(newline)
(display (if (equal? (prime? 12) #f) "7 SUCCESS" "7 FAILURE"))(newline)
(display (if (equal? (prime? 1) #f) "8 SUCCESS" "8 FAILURE"))(newline)


(display (if (equal? (primes? '(1 2 3 4)) '(#f #t #t #f)) "9 SUCCESS" "9 FAILURE"))(newline)
(display (if (equal? (primes? '()) '()) "10 SUCCESS" "10 FAILURE"))(newline)
(display (if (equal? (primes? '(10 12 23 33)) '(#f #f #t #f)) "11 SUCCESS" "11 FAILURE"))(newline)

