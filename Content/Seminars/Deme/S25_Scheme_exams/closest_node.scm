(define (closest-node node)
    (cond 
        ((null? node) 0)
        ((null? (cadr node)) (car node))
        (else 
            (+
                (car node)
                (apply min
                    (map (lambda (x) (closest-node x)) (cadr node))
                )
            )
        )
    )
)
