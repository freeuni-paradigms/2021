(define (k-th-element lst k)
    (cond
        ((null? lst) "None")
        ((zero? k) (car lst))
        (else (k-th-element (cdr lst) (- k 1)))
    )
)

(define (filter-range-helper lst a b)
    (cond 
        ((null? lst) '())
        ((and (<= a (car lst)) (<= (car lst) b)) 
            (cons (car lst) (filter-range (cdr lst) a b)))
        (else (filter-range (cdr lst) a b))
    )
)

(define (filter-range lst a b)
    (if (> a b)
        (filter-range-helper lst b a)
        (filter-range-helper lst a b)
    )
)

(define (prime-helper n k)
    (cond 
        ((> k (sqrt n)) #t)
        ((zero? (remainder n k)) #f)
        (else (prime-helper n (+ k 1)))
    )
)

(define (prime? n)
    (if (= n 1) #f
        (prime-helper n 2)
    )
)

(define (primes? lst)
    (if (null? lst) '()
        (cons (prime? (car lst)) (primes? (cdr lst))) 
    )
)
