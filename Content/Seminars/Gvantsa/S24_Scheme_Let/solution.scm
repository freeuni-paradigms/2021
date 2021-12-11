;1 reverse duplicate
(define (reverseDup lst) 
    (let
        (
            (reversed (reverse lst))
        )
        (append reversed reversed)
    )
)

;2. binpow
(define (binpow a b)
    (if (zero? b) 1
        (let 
            (
                (currpow (binpow a (quotient b 2)))
            )
            (if (zero? (remainder b 2))
                (* currpow currpow)
                (* a currpow currpow)
            )
        )
    )
)

;3. fibonacci
(define (fib n)
    (let loop
        (
            (m 0)
            (k 1)
            (count n)
        )
        (if (= count 0)
            m
            (loop k (+ m k) (- count 1))
        )
    )
)

;4. list partition
(define (partition n lst)
    (if (null? lst) 
        '(()())
        (let 
            (
                (part (partition n (cdr lst)))
            )
            (if (< (car lst) n)
                (list
                    (cons (car lst) (car part))
                    (cadr part)
                )
                (list
                    (car part)
                    (cons (car lst) (cadr part))
                )
            )
        )
    )
)

(define (try_delete n lst)
    (cond
        ((null? lst) '())
        ((= n (car lst)) (try_delete n (cdr lst)))
        (else (cons (car lst) (try_delete n (cdr lst))))
    )
)

;5. permutation? V1
(define (permutation? lst1 lst2)
    (if (equal? lst1 lst2) 
        #t
        (if (not (= (length lst1) (length lst2))) 
            #f
            (let 
                (
                    (td1 (try_delete (car lst1) lst1))
                    (td2 (try_delete (car lst1) lst2))
                )
                (if (= (length td1) (length td2))
                    (permutation? td1 td2)
                    #f
                )
            )
        )
    )
)

;5. permutation? V2
(define (permutation? lst1 lst2)
    (if (equal? lst1 lst2) #t
        (if (not (= (length lst1) (length lst2)))
            #f
            (if (equal? lst2 (try_delete (car lst1) lst2)) #f
                (permutation? (cdr lst1) (try_delete (car lst1) lst2))
            )
        )
    )
)

;6 isWay?
(define (isWay? graph start finish)
    #t
)

(define (contains n lst)
    (cond
        ((null? lst) #f)
        ((= n (car lst)) #t)
        (else (contains n (cdr lst)))
    )
)

(define (single_neighbour v visited edge)
    (cond
        ((and (= (car edge) v) (not (contains (cadr edge) visited))) (list (cadr edge))) 
        ((and (= (cadr edge) v) (not (contains (car edge) visited))) (list (car edge))) 
        (else '())
    )
)

(define (all_neighbours graph v visited)
    (apply append (map (lambda (edge) (single_neighbour v visited edge)) graph))
)