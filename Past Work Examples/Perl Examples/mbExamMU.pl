/* 	Created by Mark Brown
	Date: 4/11/2017
	Description: A prolog homework assignment to make up for exam (at max 10 points) about my family and how to find my grandparents
		using prolog.
*/

/* NOTE:
	grandfather(X, mark). should return MY grandfathers => Dean SR. and Guy
	grandmother(X, mark). should return MY grandmothers => Karin and Bunny (bernice)
	cousin(X, mark). should return MY cousins => Anna, Morgan, and David
*/


%My mothers father and mother [my grandparents] and her brother
father(guy, linda).
mother(bunny, linda).
father(guy, wayne).
mother(bunny, wayne).

%My uncle's family
father(wayne, anna).
mother(denice, anna).

%MY fathers father and mother [my other grandparents] and his sister
father(deanSr, dean).
mother(karin, dean).
father(deanSr, tracy).
mother(karin, tracy).

%My aunt's family
father(bruce, morgan).
mother(tracy, morgan).
father(bruce, david).
mother(tracy, david).

%My parents
father(dean, mark).
mother(linda, mark).



%Link to find siblings
sibs(X, Y) :- father(A, X), father(A, Y), mother(B, X), mother(B, Y), not(X=Y).


%Links to find cousins
cousin(X, Y) :- father(Z, Y), sibs(A, Z), father(A, X), not(X=Y).
cousin(X, Y) :- father(Z, Y), sibs(A, Z), mother(A, X), not(X=Y).
cousin(X, Y) :- mother(Z, Y), sibs(A, Z), father(A, X), not(X=Y).
cousin(X, Y) :- mother(Z, Y), sibs(A, Z), mother(A, X), not(X=Y).


%Links to find my grandfather or grandmother
grandfather(X, Y) :- father(X, Z), father(Z, Y).
grandfather(X, Y) :- father(X, Z), mother(Z, Y).
grandmother(X, Y) :- mother(X, Z), mother(Z, Y).
grandmother(X, Y) :- mother(X, Z), father(Z, Y).