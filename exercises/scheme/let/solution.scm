;1 reverse duplicate
(define (reverseDup lst) 
    (let 
        ((reversed (reverse lst)))
        (append reversed reversed)
    )
)

;2. binpow
(define (binpow a b)
    (if 
        (zero? b) 1
        (let 
            ((c (binpow a (quotient b 2))))
            (if
                (zero? (remainder b 2))
                (* c c)
                (* a c c)
            )
        )
    )
)

;3. fibonacci
(define (fib n)
    (let loop
        ((a 0) (b 1) (count n))
        (if 
            (zero? count) a
            (loop b (+ a b) (- count 1))
        )
    )
)

; 4. list partition
(define (partition n lst)
    (if 
        (null? lst) '(()())
        (let 
            ((recResult (partition n (cdr lst))) (firstElem (car lst)))
            (if 
                (< firstElem n)
                (list 
                    (cons firstElem (car recResult))
                    (cadr recResult)
                )
                (list
                    (car recResult)
                    (cons firstElem (cadr recResult))
                )
            )
        )
    )
)

;4. list partition other version
; (define (partition n lst)
;     (let loop 
;         ((less '()) (other '()) (currLst lst))
;         (cond
;             ((null? currLst) (list less other))
;             (
;                 (< (car currLst) n) 
;                 (loop (append less (list (car currLst))) other (cdr currLst))
;             )
;             (else 
;                 (loop less (append other (list (car currLst))) (cdr currLst))
;             )
;         )
;     )
; )

;5. permutation?
(define (permutation? lst1 lst2)
    (cond 
        ((not (equal? (length lst1) (length lst2))) #f)
        ((null? lst1) #t)
        (else (permutation? (cdr lst1) (remove (car lst1) lst2)))
    )
)

(define (remove elem lst)
    (cond 
        ((null? lst) lst)
        ((equal? elem (car lst)) (cdr lst))
        (else (cons (car lst) (remove elem (cdr lst))))
    )
)
;6 isWay?
(define (isWay? graph start finish)
    #t
)