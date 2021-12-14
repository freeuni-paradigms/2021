(define (is-greater-or-equal? l1 l2) 
    (cond
        ((null? l1) #t)
        ((> (car l1) (car l2)) #t)
        ((< (car l1) (car l2)) #f)
        (else (is-greater-or-equal? (cdr l1) (cdr l2)))
    )
)

(define (max-list l1 l2)
    (cond
        ((> (length l1) (length l2)) l1)
        ((< (length l1) (length l2)) l2)
        ((is-greater-or-equal? (reverse l1) (reverse l2)) l1)
        (else l2)
    )
)

(define (helper left right)
    (cond 
        ((null? right) left)
        ((null? left) 
            (helper (cons (car right) left) (cdr right))
        )
        ((> (car left) (car right)) (helper (cons (car right) left) (cdr right)))
        (else 
            (max-list
                left
                (helper (list (car right)) (cdr right))
            )
        )
    )
)


(define (max-decreasing-subsegment sequence)
  (reverse (helper '() sequence))
)

