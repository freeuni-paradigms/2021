(load "PATH/solution.scm")

(display (if (equal? (first-elem '(1 2 3)) 1) "1 SUCCESS" "1 FAILURE"))(newline)
(display (if (equal? (first-elem '()) "None") "2 SUCCESS" "2 FAILURE"))(newline)


(display (if (equal? (abs_ 0) 0) "3 SUCCESS" "3 FAILURE"))(newline)
(display (if (equal? (abs_ 10) 10) "4 SUCCESS" "4 FAILURE"))(newline)
(display (if (equal? (abs_ -8) 8) "5 SUCCESS" "5 FAILURE"))(newline)


(display (if (equal? (right-triangle '(1 2 3)) #f) "6 SUCCESS" "6 FAILURE"))(newline)
(display (if (equal? (right-triangle '(3 4 5)) #t) "7 SUCCESS" "7 FAILURE"))(newline)


(display (if (equal? (last-elem '(1 2 3)) 3) "8 SUCCESS" "8 FAILURE"))(newline)
(display (if (equal? (last-elem '(5)) 5) "9 SUCCESS" "9 FAILURE"))(newline)
(display (if (equal? (last-elem '()) "None") "10 SUCCESS" "10 FAILURE"))(newline)


(display (if (equal? (length_ '()) 0) "11 SUCCESS" "11 FAILURE"))(newline)
(display (if (equal? (length_ '(1 2 3 4 5)) 5) "12 SUCCESS" "12 FAILURE"))(newline)
