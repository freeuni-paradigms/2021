; 1
(define (first-elem lst)
    (if
        (null? lst) "None"
        (car lst)
    )
)

; 2
(define (abs_ n)
    (if
        (negative? n) (- n)
        n
    )
)

; 3
(define (square n)
    (* n n)
)

(define (right-triangle lst)
    (equal?
        (+
            (square (car lst))
            (square (cadr lst))
        )
        (square (caddr lst))
    )
)

; 4
(define (last-elem lst)
    (cond
        ((null? lst) "None")
        ((null? (cdr lst)) (car lst))
        (else (last-elem (cdr lst)))
    )
)

; 5
(define (length_ lst)
    (if 
        (null? lst) 0
        (+ 1 (length_ (cdr lst)))
    )
)

; 6
(define (k-th-element lst k)
    (cond
        ((null? lst) "None")
        ((= k 0) (car lst))
        (else (k-th-element (cdr lst) (- k 1)))
    )
)

; 7
(define (filter-range lst a b)
    (cond
        ((> a b) (filter-range lst b a))
        ((null? lst) '())
        (   
            (and
                (>= (car lst) a)
                (<= (car lst) b)
            )
            (cons (car lst) (filter-range (cdr lst) a b))
        )
        (else (filter-range (cdr lst) a b))
    )
)