% Author: Fernando Payan, Andrew Richmond, John Skluzacek, Mitchell Misichia
% IT 327
% Date: 11/17/22

% Definition of facts
parent(pam, tom).
parent(bob, tom).
parent(bob, liz).
parent(tom, frank).
parent(tom, ann).
parent(liz, pat).
parent(liz, oliva).

male(bob).
male(tom).
male(frank).
male(pat).

female(pam).
female(liz).
female(ann).
female(oliva).


% Exercise 4:
% X represents the grandson, Y represents the grandparent, and M represents the parent
grandson(X, Y) :-
    male(X),
    parent(Y, M),
    parent(M, X).


% Exercise 5: 
firstCousin(X, Y) :-
    X \== Y, % Person cannot be his or her own cousin
    parent(P1, X),
    parent(P2, Y),
    P1 \== P2, % Brother and sister cannot be a cousin
    parent(C, P1),
    parent(C, P2).

% Exercise 7: 
% We check the first three elements and return the third item (i.e. X).
third([_, _, X | _], X).

% Exercise 8: 
% We check the first two elements, and it will only return true if the first two elements are = X (i.e. the same value)
firstPair([X, X | _]).

% Exercise 9: 
% We check if the first two elements are the same. Since we don't care about the third element, it's an anonymous variable.
% We also have to make sure the rest of the list (D) is the same.
del3([A, B, _ | D], [A, B | D]).