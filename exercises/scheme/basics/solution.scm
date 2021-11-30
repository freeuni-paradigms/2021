(define (first-elem lst)
    (if (null? lst)
        "None"
        (car lst)
    )
)


(define (abs_ n)
    (if (positive? n)
        n
        (- 0 n)
    )
)


(define (right-triangle lst)
    (equal? (+ (expt (car lst) 2) (expt (cadr lst) 2))
        (expt (caddr lst) 2)
    )
)


(define (last-elem lst)
    (cond
        ((null? lst) "None")
        ((null? (cdr lst)) (car lst))
        (else (last-elem (cdr lst)))
    )
)


(define (length_ lst)
    (if (null? lst) 0
        (+ 1 (length_ (cdr lst)))
    )
)