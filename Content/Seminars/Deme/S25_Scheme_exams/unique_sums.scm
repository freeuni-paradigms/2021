(define (merge-list l1 l2)
    (cond 
        ((null? l1) l2)
        ((null? l2) l1)
        ((equal? (car l1) (car l2)) (merge-list (cdr l1) l2))
        ((< (car l1) (car l2)) (cons (car l1) (merge-list (cdr l1) l2)))
        (else (cons (car l2) (merge-list l1 (cdr l2))))
    )
)


(define (possible-sums sum seq)
    (if 
        (null? seq) (list sum)
        (merge-list 
            (possible-sums sum (cdr seq))
            (possible-sums (+ (car seq) sum) (cdr seq))
        )
    )
)

(define (unique-sums seq)
    (length (possible-sums 0 seq))
)