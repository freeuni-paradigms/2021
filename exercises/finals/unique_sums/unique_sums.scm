(define (merge a b)
    (cond
        ((null? a) b)
        ((null? b) a)
        ((< (car a) (car b)) (cons (car a) (merge (cdr a) b)))
        ((< (car b) (car a)) (cons (car b) (merge (cdr b) a)))
        (else (merge (cdr a) b))
    )
)

(define (unique-sums-helper curr_sum seq)
    (if (null? seq) (list curr_sum)
        (merge
            (unique-sums-helper curr_sum (cdr seq))
            (unique-sums-helper (+ (car seq) curr_sum) (cdr seq))
        )
    )
)

(define (unique-sums seq)
    (length (unique-sums-helper 0 seq))
)

