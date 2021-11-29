(load "PATH/solution.scm")

(display (if (equal? (k-th-element '(1 2 3) 2) 3) "1 SUCCESS" "1 FAILURE"))(newline)
(display (if (equal? (k-th-element '() 0) "None") "2 SUCCESS" "2 FAILURE"))(newline)


(display (if (equal? (filter-range '(1 2 3 4) 2 4) '(2 3 4)) "3 SUCCESS" "3 FAILURE"))(newline)
(display (if (equal? (filter-range '(1 2 3 4) 9 14) '()) "4 SUCCESS" "4 FAILURE"))(newline)

