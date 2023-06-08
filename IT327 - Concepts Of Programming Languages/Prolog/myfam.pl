%parent(Parent,Child) DEBUG: trace (func)
parent(pam, bob).
parent(tom, liz).
parent(bob, ann).
parent(bob, pat).
parent(pat, jim).
parent(tom, olivia).

%First Example consult(myfam).
% parent(bob, Y).
% ;

%Second Example parent(X, Y).
% ;
% ;

%Third Example parent(G,P),parent(P,GC).
% Outputs G = pam, P = bob, GC = ann
% If we undo it (use ;), we get
% Output: G = pam, P = bob, GC = pat
% Third time outputs GC = Jim
% Fourth time will return False.

% Indents are not required here, but needed for readability
offspring(Child, Parent) :-
    parent(Parent, Child).
% Restart the file: reconsult(myfam).
% offspring(ann,bob).
% Returns true
% offspring(bob, X).
% returns pam
% offspring(X, Y).
% returns all the offspring and their parent

%You can do parent(X, bob).
% Returns pam

% offspring(X, bob).
% returns ann
% ;
% returns pat.

%member(Element,List). Element is a member of the List
membermec(Item, [Item|_]).
membermec(Item, [_|Tail]) :-
    membermec(Item, Tail).

%append(List1, List2, List3). List1+List2 -> List3
appendmec([], List, List).
appendmec([Head|Tail], List2, [Head|Tail3]) :-
    appendmec(Tail, List2, Tail3).
%To run, do consult(myfam). (If you want to redo it, just do reconsult(myfam).)
% Then run the following commands: appendmec([a,b,c],[d,e,f],X).
% Output should be X = [a,b,c,d,e,f].
% appendmec([a,b,c],X,[a,b,c,d,e,f])
% Output should be: X = [d,e,f].
% appendmec(X,Y,[1,2,3,4,5])
% Press ; to see all the outputs here. Should be a bunch of lines

% trace - Lets us see our call step by step. Press enter to iterate through each call. Write abort to abort the calls. We can turn it off by doing notrace
% appendmec([a,b,c],[d,e,f],X).

% Other commands we can use: debug / nodebug, spy (essentially breakpoint)
% spy(membermec)
% appendmec([a,b,c],[7],X),membermec(Y,X)
% It will run the code and stop when we run membermec

%reverse(List,RevList).
reverse([], []).
reverse([Head|Tail], RevList) :-
    reverse(Tail, RevTail),
    append(RevTail, [Head], RevList). % Head = 1, Tail = [2, 3], and RevTail = [3, 2]. We can just simply append the head to the RevList.
%do reverse(X, [1,2,3]).

% evenlength()
evenlength([]).
evenlength([_,_|Tail]) :-
    evenlength(Tail).
%do evenlength[1,2,3,4]). If you did evenlength([1]). that should be false

oddlength([_|Tail]) :-
    evenLength(Tail).