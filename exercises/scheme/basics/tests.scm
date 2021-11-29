(load "PATH/solution.scm")

(display (if (equal? (first-elem '(1 2 3)) 1) "1 SUCCESS" "1 FAILURE"))(newline)
(display (if (equal? (first-elem '()) "None") "2 SUCCESS" "2 FAILURE"))(newline)
