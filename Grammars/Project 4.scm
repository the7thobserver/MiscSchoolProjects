;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname leungjm_leungjm_Leung_Project4) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ())))
;; Jared Leung
;; SID 66718450
;; CS 141 Formal Languages

;; Takes in a list L and returns the fourth element
(define fourth-element
  (lambda (L)
    (fourth-element-checker L 0)))

(define fourth-element-checker
  (lambda (L num)
    (cond ((empty? L) empty)
          ((= num 3) (first L))
          (else (fourth-element-checker (rest L) (+ num 1))))))

;; Given test cases
(check-expect (fourth-element '(a b c d e)) 'd)
(check-expect (fourth-element '(x (y z) w h j)) 'h)
(check-expect (fourth-element '((a b) (c d) (e f) (g h) (i j))) '(g h))
(check-expect (fourth-element '(a b c)) empty)
;; Additional test cases
(check-expect (fourth-element '(a b)) empty)
(check-expect (fourth-element '(a)) empty)
(check-expect (fourth-element '()) empty)
(check-expect (fourth-element '(1 2 3 4 5 6 7 8 9 0)) '4)
(check-expect (fourth-element '((a b) (c d e) () g h)) 'g)
(check-expect (fourth-element '(() () () ())) empty)


;; Takes in a list L and returns the number of elements
(define list-length
  (lambda (L)
    (list-length-helper L 0)))

(define list-length-helper
  (lambda (L num)
    (cond ((empty? L) num)
          (else (list-length-helper (rest L) (+ num 1))))))

;; Given test cases
(check-expect (list-length '(a b c)) 3)
(check-expect (list-length '(a (b c) d e f)) 5)
;; Additional test cases
(check-expect (list-length '()) 0)
(check-expect (list-length '((a b c) (1 2 3) (x y z))) 3)
(check-expect (list-length '(((a)) (b) c d (e f g ) (h (i j k)))) 6)
(check-expect (list-length '(a b c d e f g h i j k l m n o p q r s t u v w x y z)) 26)
(check-expect (list-length '(() ())) 2)
(check-expect (list-length '(())) 1)


;; Takes in a symbol S and a simple list L and returns the number of times S occurs in L
(define count-matches
  (lambda (S L)
    (count-matches-helper S L 0)))

(define count-matches-helper
  (lambda (S L num)
    (cond ((empty? L) num)
          ((equal? (first L) S) (count-matches-helper S (rest L) (+ num 1)))
          (else (count-matches-helper S (rest L) num)))))
    
;; Given test cases
(check-expect (count-matches 'f '(a b c d e f g)) 1)
(check-expect (count-matches 'b '(a b a b a b a)) 3)
(check-expect (count-matches 'x '(a b c)) 0)
;; Additional test cases
(check-expect (count-matches '(a b) '((a b) (a b) c d (a) (b) (b a))) 2)
(check-expect (count-matches '() '(1 2 3 4)) 0)
(check-expect (count-matches '((a)) '(((a)) b c)) 1)
(check-expect (count-matches '((a b) c) '(((a b) c))) 1)
(check-expect (count-matches '((a b) c) '((a b) c)) 0)

;; Takes in two lists L1 and L2 and concatinates L1 with L2
(define my-append
  (lambda (L1 L2)
    (cond ((empty? L1) L2)
          ((empty? L2) L1)
          (else (cons (first L1) (my-append (rest L1) L2))))))

;; Given test cases
(check-expect (my-append '(a b) '(c d)) (list 'a 'b 'c 'd))
(check-expect (my-append '() '(a b)) (list 'a 'b))
(check-expect (my-append '(a b) '())  (list 'a 'b))
;; Additional test cases
(check-expect (my-append '() '()) empty)
(check-expect (my-append '(a b) '((b))) (list 'a 'b '(b)))
(check-expect (my-append '(a b) '((b c) (d e) f)) (list 'a 'b '(b c) '(d e) 'f))
(check-expect (my-append '(()) '(a)) (list '() 'a))
(check-expect (my-append '(a) '(())) (list 'a '()))
(check-expect (my-append '(()) '(())) (list '() '()))

;; Takes in a simple list L and returns true if the numbers in the list are increasing and false if
;; there is any decrease
(define is-increasing?
  (lambda (L)
    (cond ((empty? L) true)
          ((empty? (rest L)) true)
          (else (cond ((<= (first L) (first (rest L))) (is-increasing? (rest L)))
                (else false))))))
       
;; Given test cases
(check-expect (is-increasing? '(1 2 3)) true)
(check-expect (is-increasing? '(3 2 1)) false)
(check-expect (is-increasing? '(1 2 2 3 4 4 5)) true)
(check-expect (is-increasing? '(1)) true)
(check-expect (is-increasing? '()) true)
;; Additional test cases
(check-expect (is-increasing? '(3 3 3)) true)
(check-expect (is-increasing? '(1 2 3 2)) false)
(check-expect (is-increasing? '(0)) true)
(check-expect (is-increasing? '(-1 -2 -3 -4)) false)
(check-expect (is-increasing? '(-1 -2 -3 0)) false)
(check-expect (is-increasing? '(-4 -3 -2 0)) true)


;; Takes in a simple list L and removes the duplicate objects in L
(define remove-duplicates
  (lambda (L)
    (remove-duplicates-helper L empty)))

(define remove-duplicates-helper
  (lambda (L1 L2)
    (cond ((empty? L1) L2)
          ((search? (first L1) L2) (remove-duplicates-helper (rest L1) L2))
          (else (remove-duplicates-helper (rest L1) (my-append L2 (list (first L1))))))))

(define search?
  (lambda (S L)
    (cond ((empty? L) false)
          ((equal? (first L) S) true)
          (else (search? S (rest L))))))
          
;; Given test cases
(check-expect (remove-duplicates '(1 2 3)) (list 1 2 3))
(check-expect (remove-duplicates '(1 2 1 4)) (list 1 2 4))
(check-expect (remove-duplicates '(3 3 3 3 3)) (list 3))
;; Additional test cases
(check-expect (remove-duplicates '()) empty)
(check-expect (remove-duplicates '(0 1 1 0)) (list 0 1))
(check-expect (remove-duplicates '(0 1 2 3 5 3 2 1 0)) (list 0 1 2 3 5))
(check-expect (remove-duplicates '(0)) (list 0))
(check-expect (remove-duplicates '(0 1 1 1 0 2 2 3)) (list 0 1 2 3))

;; Max
(define find-max
  (lambda (L)
    (cond ((empty? L) empty)
    (else (find-max-helper (rest L) (first L))))))

(define find-max-helper
  (lambda (L num)
    (cond ((empty? L) num)
          ((> (first L) num) (find-max-helper (rest L) (first L)))
          (else (find-max-helper (rest L) num)))))

(check-expect (find-max '()) empty)
(check-expect (find-max '(1 2 3)) 3)
(check-expect (find-max '(1 2 3 4 5 6)) 6)
(check-expect (find-max '(5 4 3 2 1)) 5)
(check-expect (find-max '(4 10 3 5 8 11)) 11)
(check-expect (find-max '(4 10 3 35 8 )) 35)
(check-expect (find-max '(-1 -2 -3 -2 -1)) -1)
(check-expect (find-max '(1 1 1 1 1)) 1)

;; All but max
(define find-max2
  (lambda (L)
    (cond ((empty? L) empty)
    (else (find-max-helper2 L empty (find-max L))))))

(define find-max-helper2
  (lambda (L1 L2 max)
    (cond ((empty? L1) L2)
          ((< (first L1) max) (find-max-helper2 (rest L1) (cons (first L1) L2) max))
          (else (find-max-helper2 (rest L1) L2 max)))))

(check-expect (find-max2 '()) empty)
(check-expect (find-max2 '(1 2 3)) '(2 1))
(check-expect (find-max2 '(1 2 3 4 5 6)) '(5 4 3 2 1))
(check-expect (find-max2 '(4 10 3 5 8 11)) '(8 5 3 10 4))

(define avg
  (lambda (L)
    (cond ((empty? L) empty)
          (else (avg-helper (rest L) (first L) 1)))))

(define avg-helper
  (lambda (L avg count)
    (cond ((empty? L) (/ avg count))
          (else (avg-helper (rest L) (+ avg (first L)) (+ count 1))))))


(check-expect (avg '()) empty)
(check-expect (avg '(1 3)) 2)
(check-expect (avg '(1 2)) 1.5)
(check-expect (avg '(1 2 3)) 2)
(check-expect (avg '(1 2 3 4 5)) 3)
(check-expect (avg '(10 10 10 10 10)) 10)
(check-expect (avg '(0 0 0)) 0)