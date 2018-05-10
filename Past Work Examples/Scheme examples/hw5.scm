; Mark Brown
; 11/4/2017
; Homework designed to help become comfortable with Scheme


;Question 1 - return all lists within a list
(define (extract-list lst) 
	(filter list? lst))

;Question 2 - counts all the even numbers
(define (evens lst)
  (length (filter even? lst)))

;Question 3 - pairs each n position between two lists/return empty otherwise
(define (comb lst1 lst2) 
	(if (= (length lst1) (length lst2))
		(map list lst1 lst2)
	'()))

;Question 4 - basically 'FOILs' the two lists
(define (product x y)
  (let ((f (lambda (i) (map (lambda (j) (list i j)) y))))
    (concatenate (map f x))))

;Question 5 - remove all duplicates from the list
(define (removeDup lst)
  (reverse 
   (fold-left 
    (lambda (i j)
      (if (not (member j i))
          (cons j i)
          i))
    '()
    lst)))

;Question 6 - linear version of the fibonacci number
(define (fibNum n)
    (let loop
      ((i 0)
       (j 1)
       (count n))
      (if (= count 0)
        i
        (loop j (+ i j) (- count 1)))))

