(define (reverse_ lst)
    (if (null? lst) '()
        (append (reverse_ (cdr lst)) (list (car lst)))
    )
)

(define (sorted? lst)
    (cond
        ((<= (length lst) 1) #t)
        ((> (car lst) (cadr lst)) #f)
        (else (sorted? (cdr lst)))
    )
)

(define (max_ lst)
    (cond
        ((null? lst) 0)
        ((< (car lst) (max_ (cdr lst))) (max_ (cdr lst)))
        (else (car lst))
    )
)

(define (filter_ func lst)
    (cond 
        ((null? lst) '())
        ((func (car lst)) (cons (car lst) (filter_ func (cdr lst))))
        ((filter_ func (cdr lst)))
    )
)

(define (divisible3 n)
    (zero? (remainder n 3))
)

(define (max_divisible3 lst)
    (max_ (filter_ divisible3 lst))
)

(define (range k)
    (if (zero? k) 
        '()
        (append (range (- k 1)) (list k))
    )
)

(define (pow a n)
    (if (zero? n)
        1
        (* a (pow a (- n 1)))
    )
)

(define (generate_powers_helper a k curr_pow)
    (if (zero? k) '()
        (cons curr_pow (generate_powers_helper a (- k 1) (* a curr_pow)))
    )
)

(define (generate_powers a k)
    (generate_powers_helper a k a)
)