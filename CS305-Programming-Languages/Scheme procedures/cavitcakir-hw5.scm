;- Procedure: symbol-length
;- Input : Takes only one parameter named inSym
;- Output : Returns the number of items in the symbol.
; If the input is not a symbol, then it returns 0.
;- Examples :
; (symbol-length 'a) ------> evaluates to 1
; (symbol-length 'abc) ----> evaluates to 3
; (symbol-length 123) -----> evaluates to 0
; (symbol-length '(a b)) --> evaluates to 0
(define symbol-length
  (lambda (inSym)
    (if (symbol? inSym)
      (string-length (symbol->string inSym))
      0
    )
  )
)

;- Procedure: sequence?
;- Input : Takes only one parameter named inSeq
;- Output : Returns true if inSeq is a list of symbols where each
; symbol is of length 1
;- Examples :
; (sequence? '(a b c)) ----> evaluates to true
; (sequence? '()) ---------> evaluates to true
; (sequence? '(aa b c)) ---> evaluates to false since aa has length 2
; (sequence? '(a 1 c)) ----> evaluates to false since 1 is not a symbol
; (sequence? '(a (b c))) --> evaluates to false since (b c) is not a symbol
(define sequence?
  (lambda (inSeq)
    (if(list? inSeq)
      (if (null? inSeq)
        #t
        (if (eq? 1 (symbol-length (car inSeq)))
          (sequence? (cdr inSeq))
          #f
        )
      )
      #f
    )
  )
)

(define sequence-length
  (lambda (inSeq n)
  (if (null? inSeq)
    n
    (sequence-length (cdr inSeq) (+ n 1) )
  )
)
)

;- Procedure: same-sequence?
;- Input : Takes two sequences inSeq1 inSeq2 as input
;- Output : Returns true if inSeq1 and inSeq2 are sequences and they are the
; same sequence.
; Returns false if inSeq1 and inSeq2 are sequences but they are
; not the same sequence.
; If inSeq1 is not a sequence and/or inSeq2 is not a sequence,
; it produces an error.
;- Examples :
; (same-sequence? '(a b c) '(a b c)) --> evaluates to true
; (same-sequence? '() '()) ------------> evaluates to true
; (same-sequence? '(a b c) '(b a c)) --> evaluates to false
; (same-sequence? '(a b c) '(a b)) ----> evaluates to false
; (same-sequence? '(aa b) '(a b c)) ---> produces an error
; (same-sequence? '(a b) '(a ba c)) ---> produces an error
(define same-sequence?
  (lambda (inSeq1 inSeq2)
    (if(and (sequence? inSeq1) (sequence? inSeq2))
      (if(eq? (sequence-length inSeq1 0) (sequence-length inSeq2 0))
        (if (null? inSeq1)
          #t
          (if(eq? (car inSeq1) (car inSeq2))
            (same-sequence? (cdr inSeq1) (cdr inSeq2))
            #f
          )
        )
        #f
      )
      (error "same-sequence?: input is not sequence")
    )
  )
)

;- Procedure: reverse-sequence
;- Input : Takes only one parameter named inSeq
;- Output : It returns the reverse of inSeq if inSeq is a sequence.
; Otherwise it produces an error.
;- Examples :
; (reverse-sequence '(a b c)) --> evaluates to (c b a)
; (reverse-sequence '()) -------> evaluates to ()
; (reverse-sequence '(aa b)) ---> produces an error
(define reverse-sequence
  (lambda (inSeq)
    (if(null? inSeq)
      inSeq
      (if(sequence? inSeq)
        (if (null? (cdr inSeq))
            inSeq
            (append (reverse-sequence (cdr inSeq)) (list (car inSeq)))
        )
        (error "reverse-sequence: input is not sequence")
      )
    )
  )
)


;- Procedure: palindrome?
;- Input : Takes only one parameter named inSeq
;- Output : It returns true if inSeq is a sequence and it is a palindrome.
; It returns false if inSeq is a sequence but not a palindrome.
; Otherwise it gives an error.
;- Examples :
; (palindrome? '(a b a)) --> evaluates to true
; (palindrome? '(a a a)) --> evaluates to true
; (palindrome? '()) -------> evaluates to true
; (palindrome? '(a a b)) --> evaluates to false
; (palindrome? '(a 1 a)) --> produces an error
(define palindrome?
  (lambda (inSeq)
    (if(null? inSeq)
      #t
      (if(sequence? inSeq)
        (if(equal? inSeq (reverse-sequence inSeq))
          #t
          #f
        )
        (error "palindrome: input is not sequence")
      )
    )
  )
)


;- Procedure: member?
;- Input : Takes a symbol named inSym and a sequence named inSeq
;- Output : It returns true if inSeq is a sequence and inSym is a symbol
; and inSym is one of the symbols in inSeq.
; It returns false if inSeq is a sequence and inSym is a symbol
; but inSym is not one of the symbols in inSeq.
; It produces an error if inSeq is not a sequence and/or if
; inSym is not a symbol.
;- Examples :
; (member? 'b '(a b c)) ---> evaluates to true
; (member? 'd '(a b c)) ---> evaluates to false
; (member? 'd '()) --------> evaluates to false
; (member? 5 '(a 5 c)) ----> produces an error
; (member? 'd '(aa b c)) --> produces an error
(define member?
  (lambda (inSym inSeq)
    (if(null? inSeq)
      #f
      (if(and (sequence? inSeq) (symbol? inSym))
        (if(eq? inSym (car inSeq))
          #t
          (member? inSym (cdr inSeq))
        )
        (error "member?: input is not sequence or symbol")
      )
    )
  )
)

;- Procedure: remove-member
;- Input : Takes a symbol named inSym and a sequence named inSeq
;- Output : If inSym is a symbol and inSeq is a sequence and inSym is one of
; the symbols in inSeq, then remove-member returns the sequence
; which is the same as the sequence inSeq, where the first
; occurrence of inSym is removed.
; For any other case, it produces an error.
; Examples :
; (remove-member 'b '(a b a b c b)) --> evaluates to (a a b c b)
; (remove-member 'd '(a b c)) --------> produces an error
; (remove-member 'b '()) -------------> produces an error
; (remove-member 'b '(a b 5 c)) ------> produces an error
; (remove-member 5 '(a b c)) ---------> produces an error
(define remove-member
  (lambda (inSym inSeq)
    (if(null? inSeq)
      (error "remove-member?: input is empty list")
      (if (and (sequence? inSeq) (symbol? inSym))
        (if(member? inSym inSeq)
          (cond
            ((equal? inSym (car inSeq)) (cdr inSeq))
            (else (cons (car inSeq) (remove-member inSym (cdr inSeq))))
          )
          (error "remove-member?: list not includes symbol")
        )
        (error "remove-member?: input is not sequence or symbol or list not includes symbol")
      )
    )
  )
)

;- Procedure: anagram?
;- Input : Takes two sequences inSeq1 and inSeq2 as paramaters.
;- Output : If inSeq1 and inSeq2 are both sequences and if inSeq1 is an
; anagram of inSeq2, then anagram? evaluates to true.
; If inSeq1 and inSeq2 are both sequences and but if inSeq1 is not an
; anagram of inSeq2, then anagram? evaluates to false.
; If inSeq1 is not a sequence or if inSeq2 is not a sequence
; then anagram? produces an error.
;- Examples :
; (anagram? '(m a r y) '(a r m y)) --> evaluates to true
; (anagram? '() '()) ----------------> evaluates to true
; (anagram? '(a b b) '(b a a)) ------> evaluates to false
; (anagram? '(a b b) '()) -----------> evaluates to false
; (anagram? '(a bb) '(a bb)) --------> produces an error
; (anagram? 5 '(a b b)) -------------> produces an error
(define anagram?
  (lambda (inSeq1 inSeq2)
    (if(and (sequence? inSeq1) (sequence? inSeq2))
      (if(eq? (sequence-length inSeq1 0) (sequence-length inSeq2 0))
        (if(null? inSeq1)
          #t
          (if(member? (car inSeq1) inSeq2)
            (anagram? (remove-member (car inSeq1) inSeq2) (cdr inSeq1) )
            #f
          )
        )
        #f
      )
      (error "anagram?: input is not sequence")
    )
  )
)

;- Procedure: anapoli?
;- Input : Takes two sequences inSeq1, inSeq2 as parameters.
;- Output : If inSeq1 and/or inSeq2 is not a sequence, it produces
; an error.
; When both inSeq1 and inSeq2 are sequences, it returns
; true if inSeq2 is a palindrome, and inSeq1 is an anagram of
; the palindrome given by inSeq2.
; Otherwise, it returns false.
;- Examples :
; (anapoli? '(a b b) '(b a b)) ----------> evaluates to true
; (anapoli? '() '()) --------------------> evaluates to true
; (anapoli? '(d a m a m) '(m a d a m)) --> evaluates to true
; (anapoli? '(a b b c) '(a b c b)) ------> evaluates to false
; (anapoli? '(a b b c) '(a bb bb)) ------> produces an error
; (anapoli? '(a bb) '()) ----------------> produces an error
; (anapoli? 5 '(a))----------------------> produces an error
(define anapoli?
  (lambda (inSeq1 inseq2)
    (if(and (sequence? inSeq1) (sequence? inSeq2))
      (if(and (palindrome? inSeq2) (anagram? inSeq1 inSeq2))
        #t
        #f
      )
      (error "anagram?: input is not sequence")
    )
  )
)
