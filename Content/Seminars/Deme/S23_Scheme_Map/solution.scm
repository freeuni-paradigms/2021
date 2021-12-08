(define (digits n)
    (if 
        (< n 10) (list n)
        (append (digits (quotient n 10)) (list (remainder n 10)))
    )
)

(define (list_power lst)
    (map (lambda (x) (expt x (length lst))) lst)
)

(define (sum lst)
    (apply + lst)
)

(define (narcisisstic? n)
    (equal? n (sum (list_power (digits n))))
)

(define (count n lst)
    (apply +
        (map (lambda (x) (if (equal? x n) 1 0)) lst)
    )
)

(define (set lst)
    (cond
        ((null? lst) '())
        ((= 1 (count (car lst) lst)) (cons (car lst) (set (cdr lst))))
        (else (set (cdr lst)))
    )
)

(define (frequency lst)
    (map (lambda (x) (list x (count x lst))) (set lst))
)

(define (multiply-helper n elem)
    (if 
        (zero? n) '()
        (cons elem (multiply-helper (- n 1) elem))
    )
)

(define (multiply n lst)
    (apply append
        (map (lambda (x) (multiply-helper n x)) lst)
    )
)

(define (k-subset lst k)
    (cond 
        ((> k (length lst)) '())
        ((= k 0) '(()))
        (else 
            (append
                (map (lambda (x) (cons (car lst) x)) (k-subset (cdr lst) (- k 1)))
                (k-subset (cdr lst) k)
            )
        )
    )
)