% Exercise 4
combine_list([], Y, Y).
combine_list([Head |T1],L2,[Head|L3]):-combine_list(T1,L2,L3).

rev_filter([],_,[]).
rev_filter([E|Tail], E, Result) :-
    rev_filter(Tail,E,Result).
rev_filter([Head|Tail],E,Result) :-
    not(head = E),
    rev_filter(Tail,E,TailResult),
    combine_list(TailResult,[Head],Result).


% Exercise 5
halve(List, Result1, Result2):-
    split(List, List, Result1, Result2).

split(Result2, [], [], Result2).

split([Head|Tail], [_, _|Tail1], [Head|Tail2], Result2) :-
    split(Tail, Tail1, Tail2, Result2).

parent(bob, alice).
parent(joe, bob).
male(joe).
male(bob).

grandfather1(X, Y) :-
    parent(X, Z),
    male(X),
    parent(Z,Y).

grandfather2(X,Y) :-
    male(X),
    parent(X,Z),
    parent(Z,Y).