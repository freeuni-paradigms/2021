; (define (helper lst)
;   (if (null? (cdr lst)) '()
;     (cons (+ (car lst) (cadr lst)) (helper (cdr lst)))
;   )
; )

; (define (row index)
;   (if
;     (equal? index 1) '(1)
;     (append (list 1) (helper (row (- index 1))) (list 1))
;   )
; )

(define (find-next-row prev-row)
  (map + (cons 0 prev-row) (append prev-row (list 0)))
)

(define (row index)
  (if
    (equal? index 1) '(1)
    (find-next-row (row (- index 1)))
  )
)