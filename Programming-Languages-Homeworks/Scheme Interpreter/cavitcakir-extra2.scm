(define get-operator (lambda (op-symbol)
  (cond
    ((equal? op-symbol '+) +)
    ((equal? op-symbol '-) -)
    ((equal? op-symbol '*) *)
    ((equal? op-symbol '/) /)
    (else #f))))


(define last-else? (lambda (e)
(equal? (caar (reverse e)) 'else)))



(define only-else? (lambda (e)
(if(and (equal? (caar e) 'else ) (null? (cdr e)))
  #t
  (if(and (equal? (caar e) 'else ) (not(null? (cdr e))) )
    #f
    (only-else? (cdr e))
  )
  )))


(define cond? (lambda (e)
              (and (> (length e) 2) (equal? (car e) 'cond )  (list? (cadr e)) (last-else? e) (only-else? (cdr e)) )))

(define cond-else? (lambda (e)
                      (and (equal? (length e) 2) (list? (cadr e)) (equal? (caadr e) 'else ))))

(define if? (lambda (e)
              (and (list? e) (equal? (car e) 'if) (= (length e) 4))))


(define valid-list? (lambda (e)
    (and (list? e) (list? (car e)) (= (length (car e)) 2) (symbol? (caar e))
            (or (null? (cdr e)) (valid-list? (cdr e))))))

(define letstar? (lambda (e)
    ( and (list? e) (equal? (car e) 'let*) (= (length e) 3) )
    )
)

(define let? (lambda (e)
    (and (list? e)
            (equal? (car e) 'let) (or (equal? () (cadr e) ) (valid-list? (cadr e))) (= (length e) 3))))

(define define-stmt? (lambda (e)
    ;; An expression is a define statement
    ;; if it is a list, and the first element
    ;; is define, the second element is a symbol,
    ;; and the third element is an expression.
    (and (list? e) (= (length e) 3) (equal? (car e) 'define) (symbol? (cadr e)))))

(define get-value (lambda (var env)
    (cond
      ;; If the environment is empty, then we could not find
      ;; a binding in this environment.
      ((null? env) "ERROR")

      ;; Check if the first pair is a binding for the
      ;; variable that we are looking for, and if it is
      ;; return the current value of the variable.
      ((equal? (caar env) var) (cdar env))

      ((not(equal? (caar env) '()))
      (get-value var (cdr env)))
      )))

(define extend-env (lambda (var val old-env)
      ;; Add the new variable binding to the
      ;; beginning of the old environment.
      (cons (cons var val) old-env)))

(define repl (lambda (env)
  (let* (
         ; first print out some prompt
         (dummy1 (display "cs305> "))

         ; READ an expression
         (expr (read))

         ; Form the new environment
         (new-env (if (define-stmt? expr)
                      (extend-env (cadr expr) (s6-interpret (caddr expr) env) env)
                      env))

         ; EVALuate the expression read
         (val (if (define-stmt? expr)
                  (cadr expr)
                  (s6-interpret expr env)))

         ; PRINT the value evaluated together
         ; with a prompt as MIT interpreter does
         (dummy2 (display "cs305: "))
         (dummy3 (display val))

         ; get ready for the next prompt
         (dummy4 (newline))
         (dummy4 (newline)))
     (repl new-env))))

(define s6-interpret (lambda (e env)
  (cond
    ;; If the input expression is a number, then
    ;; the value of the expression is that number.

    ((null? e) "()")
    ((number? e) e)

    ;; If the input expression is a symbol, then
    ;; get the current value binding of this variable.
    ((symbol? e) (get-value e env))

    ((not (list? e))
          "ERROR")
    ;; if part
    ((if? e) (if (not(equal? (s6-interpret (cadr e) env) 0 ))
                             (s6-interpret (caddr e) env)
                             (s6-interpret (cadddr e) env)))


    ;; cond part
    ((cond? e)
      (if(not(equal? (s6-interpret (caadr e) env) 0 ))
                    (s6-interpret (cadadr e) env)
                    (s6-interpret(cons 'cond (cddr e)) env )))

    ;; cond else part
    ((cond-else? e)
    (s6-interpret(cadadr e) env ))


    ((let? e)
        (let*
             ((params (map s6-interpret (map cadr (cadr e)) (make-list (length (map cadr (cadr e))) env)))
             (newenv (append ( map cons (map car (cadr e)) params) env)))
             (s6-interpret (caddr e) newenv)))

     ((letstar? e)
            (cond
                 ((eq? (length (cadr e)) 0) (s6-interpret (list 'let '() (caddr e)) env))
                 ((eq? (length (cadr e)) 1) (s6-interpret (list 'let (cadr e) (caddr e)) env))
                 (else
                        (let*
                            ((par (s6-interpret (car (cdaadr e)) env))
                              (newenv (cons (cons (caaadr e) par) env)))
                              (s6-interpret (list 'let* (cdadr e) (caddr e)) newenv)))))

    ;; Otherwise, we must see a list.

    ((get-operator(car e))
      (let ((operands (map s6-interpret (cdr e) (make-list (length (cdr e)) env)))
            (operator (get-operator (car e))))

        ;; And finally apply the operator to the

        ;; values of the operands         cadr e
        (apply operator operands)))
    (else
      "ERROR"
       ))))
(define cs305 (lambda () (repl '())))
