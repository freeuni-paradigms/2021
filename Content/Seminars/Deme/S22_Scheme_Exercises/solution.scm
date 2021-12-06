(define (reverse_ lst)    
    (if (null? lst) 
        '()
        (append (reverse_ (cdr lst)) (list (car lst)))
    )
)

(define (sorted? lst)
    (cond 
        ((< (length lst) 2) #t)
        ((> (car lst) (cadr lst)) #f)
        (else (sorted? (cdr lst)))
    )
)

(define (max_ lst)
    (cond 
        ((null? lst) 0)
        ((= (length lst) 1) (car lst))
        ((< (car lst) (cadr lst)) (max_ (cdr lst)))
        (else (max_ (cons (car lst) (cddr lst))))
    )
)

(define (filter_ func lst)
    (cond
        ((null? lst) '())
        ((func (car lst)) (cons (car lst) (filter_ func (cdr lst))))
        (else (filter_ func (cdr lst)))
    )
)

(define (isDivisible3 n)
    (= (remainder n 3) 0)
)

(define (max_divisible3 lst)
    (max_ (filter_ isDivisible3 lst))
)

(define (range k)
    (if
        (= k 0) '()
        (append (range (- k 1)) (list k))
    )
)

(define (pow a n)
    (if 
        (zero? n) 1
        (* a (pow a (- n 1)))
    )
)

(define (generate_powers a k)
    (map (lambda (x) (pow a x)) (range k))
)