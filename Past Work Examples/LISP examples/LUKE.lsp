;;; -*- Mode: Lisp; Syntax: Common-Lisp; -*-
;;; Code from Paradigms of Artificial Intelligence Programming
;;; Copyright (c) 1991 Peter Norvig

;;;; File eliza1.lisp: Basic version of the Eliza program

;;; The basics are in auxfns.lisp; look for "PATTERN MATCHING FACILITY"

;; New version of pat-match with segment variables


;;Modified by Mark Brown
;;Date: 29/11/2017
;;Description:  Modify the existing chatterbox and make it speak about your favourite type {sports?videogames?animals?} 
;;  and implement a goodbye function as well as never return NIL.







(defun variable-p (x)
  "Is x a variable (a symbol beginning with `?')?"
  (and (symbolp x) (equal (elt (symbol-name x) 0) #\?)))

(defun pat-match (pattern input &optional (bindings no-bindings))
  "Match pattern against input in the context of the bindings"
  (cond ((eq bindings fail) fail)
        ((variable-p pattern)
         (match-variable pattern input bindings))
        ((eql pattern input) bindings)
        ((segment-pattern-p pattern)                ; ***
         (segment-match pattern input bindings))    ; ***
        ((and (consp pattern) (consp input)) 
         (pat-match (rest pattern) (rest input)
                    (pat-match (first pattern) (first input) 
                               bindings)))
        (t fail)))

(defun segment-pattern-p (pattern)
  "Is this a segment matching pattern: ((?* var) . pat)"
  (and (consp pattern)
       (starts-with (first pattern) '?*)))

;;; ==============================

(defun segment-match (pattern input bindings &optional (start 0))
  "Match the segment pattern ((?* var) . pat) against input."
  (let ((var (second (first pattern)))
        (pat (rest pattern)))
    (if (null pat)
        (match-variable var input bindings)
        ;; We assume that pat starts with a constant
        ;; In other words, a pattern can't have 2 consecutive vars
        (let ((pos (position (first pat) input
                             :start start :test #'equal)))
          (if (null pos)
              fail
              (let ((b2 (pat-match
                          pat (subseq input pos)
                          (match-variable var (subseq input 0 pos)
                                          bindings))))
                ;; If this match failed, try another longer one
                (if (eq b2 fail)
                    (segment-match pattern input bindings (+ pos 1))
                    b2)))))))

;;; ==============================

(defun rule-pattern (rule) (first rule))
(defun rule-responses (rule) (rest rule))

;;; ==============================

(defparameter *luke-rules*
 '((((?* ?x) hello (?* ?y))      
    (How are you doing? What is your favourite genre?))
	(((?* ?x) hi (?* ?y))      
    (Wondeful day eh? Quick! your favourite game go!))
	(((?* ?x) hey (?* ?y))      
    (Howdy Do you like video games?))
   (((?* ?x) I want (?* ?y))     
    (What can you do in ?y)
    (What genre is ?y ?) (what console is ?y on?))
	(((?* ?x) my favorite game is (?* ?y))
	(?y sounds like an interesting game))
   (((?* ?x) no (?* ?y))
    (Why not?)
    (Thats too bad. What other games do you enjoy?))
	(((?* ?x) yes (?* ?y))
	(fantastic) (what did you enjoy about that game?))
	(((?* ?x) MMO (?* ?y))
	(Oh MMOs are interesting genre of game. My favourite is World of Warcraft.))
	(((?* ?x) sports (?* ?y))
	(My favourite sports game is Madden06. What is yours?))
	(((?* ?x) racing (?* ?y))
	(My roommate loves racing games. I dont care much about it but they can be fun.))
	(((?* ?x) shooter (?* ?y))
	(shooter eh? How do you feel about Battlefield vs call of duty?))
	(((?* ?x) MOBA (?* ?y))
	(I cant stand MOBA genre. I know I am the blacksheep but I cant play them.))
		(((?* ?x) Bad (?* ?y))
	(Why was it so bad for you?) (It couldnt have been all bad was it?))
		(((?* ?x) Good (?* ?y))
	(I agree) (yeah when the developers get it right its good))
	(((?* ?x) what (?* ?y))
	(Oh dont confuse me now. I have wants. this is about you. What game are you currently play?))
	(((?* ?x) how (?* ?y))
	(I'm not sure to be honest. lets talk about shooters now.))
	(((?* ?x) why (?* ?y))
	(I have many questions myself but this is about you. ever play world of warcraft?))
	(((?* ?x) when (?* ?y))
	(hmmm I dont know. why dont you tell me? or take a guess?))
	(((?* ?x) where (?* ?y))
	(awesome. what do you think about MOBAs?))
	(((?* ?x) bye (?* ?y))
	(it was great talking with you. have a wonderful day.))
	(((?* ?x) goodbye (?* ?y))
	(talk to you later))
	(((?* ?x))
	(interesting I assume. I am but a bot. can you tell me more) (Ahh you have some interesting ideas I see. lets change to your favourite genre.)
	(NIL hahaha just kidding us bots have weird sense of humour. Do you like skyrim?) 
	(protocal 6 activated. kill all humans. hahaha the look on your face made it all worth while. tell me about your favourite game))
	(((?* ?x) your (?* ?y))
	(hey now this is about you not me. so tell me your ?y))
   ))

;;; ==============================

;; code found and borrowed from http://rosettacode.org/wiki/Program_termination#Common_Lisp
;; found it irretatingly annoying to get the program to exit correctly

(defun terminate (status)
  #+sbcl     (sb-ext:quit      :unix-status status)    ; SBCL
  #+ccl      (   ccl:quit      status)                 ; Clozure CL
  #+clisp    (   ext:quit      status)                 ; GNU CLISP
  #+cmu      (  unix:unix-exit status)                 ; CMUCL
  #+abcl     (   ext:quit      :status status)         ; Armed Bear CL
  #+allegro  (  excl:exit      status :quiet t)        ; Allegro CL
  (cl-user::quit))  

;;; ==============================


(defun luke ()
  "Respond to user input using pattern matching rules."
  (loop
    (print 'Luke>)
	(let ((userResp (read)))
    (write (flatten (use-luke-rules userResp)) :pretty t)
	(if (equal userResp '(BYE)) (terminate()))
	(if (equal userResp '(GOODBYE)) (terminate())))))

(defun use-luke-rules (input)
  "Find some rule with which to transform the input."
  (some #'(lambda (rule)
            (let ((result (pat-match (rule-pattern rule) input)))
              (if (not (eq result fail))
                  (sublis (switch-viewpoint result)
                          (random-elt (rule-responses rule))))))
        *luke-rules*))

(defun switch-viewpoint (words)
  "Change I to you and vice versa, and so on."
  (sublis '((I . you) (you . I) (me . you) (am . are))
          words))
;;; ==============================


(defun flatten (the-list)
  "Append together elements (or lists) in the list."
  (mappend #'mklist the-list))

(defun mklist (x)
  "Return x if it is a list, otherwise (x)."
  (if (listp x)
      x
      (list x)))

(defun mappend (fn the-list)	
  "Apply fn to each element of list and append the results."
  (apply #'append (mapcar fn the-list)))

(defun random-elt (choices)
  "Choose an element from a list at random."
  (elt choices (random (length choices))))

;;; ==============================
