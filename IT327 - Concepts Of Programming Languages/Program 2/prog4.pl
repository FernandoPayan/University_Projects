%program 4 for 327
% Fernando Payan And Andrew Richmond

%count_muliples(NumberList, Factor,Count)
% count_multiples
% ?- count_multiples([5,3,10,15,6,4,13],5,Count).
% C = 3.

% Base Case
count_multiples([],_, 0).

% Method to count the multiples in a list
count_multiples([Head|Tail], BASE, TOTAL):-
    
    % If head mod index = 0, then we know it's a multiple of the number
	0 =:= Head mod BASE, 
    
  % Recursively call the method to see which are multiples of BASE
  count_multiples(Tail, BASE, COUNTER),
    
  % If it's true, then we add to our total tracker + 1.
  TOTAL is COUNTER + 1;
  
	count_multiples(Tail, BASE, COUNTER), 
    
  % Update the final total
  TOTAL is COUNTER.

%count_muliples_tr(NumberList, Factor,Count)

% Base Case
count_multiples_tr([], _, 0).

% The predicate that gets called / driver function
count_multiples_tr(LIST, BASE, TOTAL) :-

  % Call our recursive function
  count_multiples_tr(LIST, BASE, 0, TOTAL).

% Return total when we reach an empty list
count_multiples_tr([], _, TOTAL, TOTAL).

% Recursive Function
count_multiples_tr([Head|Tail], BASE, I, J) :-

  % Before we move onto the second predicate, we must first 
  (
  % If head mod index = 0, then we know it's a multiple of the number
  0 =:= Head mod BASE,
    
  % We add to our counter + 1.
  K is I + 1,
        
  % Recurse with the newly updated K value
  count_multiples_tr(Tail, BASE, K, J)
  );
  
  % Call back with I and J if K was invalid
  count_multiples_tr(Tail, BASE, I, J).

%maxlist(List, Max) -- List will have at least one value in it. -- hint, you may need an additional predicate.
% Base Case
maxlist([], 0, 0).

maxlist([], Max, Max). %This is the end of the predicate

maxlist([Head|Tail], Carry, Max):- 
    Head > Carry, 
    maxlist(Tail, Head, Max).

maxlist([Head|Tail], Carry, Max):- %Carry values gets carried over to become the new max, if not the current max
    Head =< Carry, 
    maxlist(Tail, Carry, Max). 

maxlist([Head|Tail], Max):- %This is the start of the predicate
    maxlist(Tail, Head, Max).

%ordered(List)
% If we reach an empty list
ordered([]).

% If we only have one item left in the list
ordered([_]).

ordered([FirstHead, SecondHead|Tail]) :- 
    
  % If the first head in the list is >= the second head, return true.
  FirstHead >= SecondHead,

  % If true, we move on to do the next comparision in the list
  ordered([SecondHead|Tail]).

%subsetsum(List,Sum,Subset)
subsetsum(LIST, SUM, SUBSET) :-
  % We want to first find the subsets
  get_subsets(LIST, SUBSET),

  % After finding the subsets, we want to see which subsets add
  % up to the passed sum value
  calculate_sum(SUBSET, SUM).

% Get Subset

% Base Condition
get_subsets([], []).

get_subsets([Head|Tail], [Head|NewTail]) :-
  get_subsets(Tail, NewTail).

get_subsets([_|Tail], NewTail) :-
  get_subsets(Tail, NewTail).

% Calculate Sum

% Base Conditon
calculate_sum([], 0).

calculate_sum([VALUE | Tail], SUM) :-
  calculate_sum(Tail, CURRENTSUM),
  SUM is CURRENTSUM + VALUE.


first_names([George, Harry, Jeff, Lester, Martin]).
models([Hydra, Kratos, Nike, Pegasus, Sibyl]).
years([1947, 1949, 1951, 1953, 1955]).

%force the answer into the correct order And number of arguments And such -- feel free to add to this in appropriate ways
answer_form([(Anderson, _, _, _),  (Brooks, _, _, _),  (corwin, _, _, _),  (dent, _, _, _),  (easton, _, _, _)]).
all_members([H],L2) :- member(H,L2).
all_members([H|T],L2) :- member(H,L2), all_members(T, L2).
 
all_not([H]) :- not(H).
all_not([H|T]) :- not(H), all_not(T).
 
all_not_members([H],L2) :- not(member(H,L2)).
all_not_members([H|T],L2) :- not(member(H,L2)), all_not_members(T, L2).
 
and([H]) :- H.
and([H|T]) :- H, and(T).
or([H]) :- H,!.
or([H|_]) :- H,!.
or([_|T]) :- or(T).
 
solve(Anderson, Brooks, Corwin, Dent, Easton) :-
% all members
Anderson = [Anderson_first, Anderson_make, Anderson_year],
Brooks = [Brooks_first, Brooks_make, Brooks_year],
Corwin = [Corwin_first, Corwin_make, Corwin_year],
Dent = [Dent_first, Dent_make, Dent_year],
Easton = [Easton_first, Easton_make, Easton_year],

% grouping
All = [Anderson, Brooks, Corwin, Dent, Easton],

% ensure all values exist once
all_members([Hydra, Kratos, Nike, Pegasus, Sibyl], [Anderson_make, Brooks_make, Corwin_make, Dent_make, Easton_make]),
all_members([George, Harry, Jeff, Lester, Martin], [Anderson_first, Brooks_first, Corwin_first, Dent_first, Easton_first]),
all_members([1947,1949,1951,1953,1955], [Anderson_year, Brooks_year, Corwin_year, Dent_year, Easton_year]),

%Clue #1: The three oldest cars are owned by George and Mr. Brooks And Jeff, although not necessariliy in that order
member( George, years),
member( Brooks_year, years),
member( Jeff, years),

 %Clue #2: The Nike is older than Martin's car.
Martin_year > Nike_year,

% Clue #3: Mr. Corwin's car is older than the Kratos.
Kratos_year > Corwin_year,

% Clue #4: Harry's car is two years older than the Pegasus.
Harry_year is Pegasus_year + 2,

% Clue #5: Mr. Anderson's car is older than either the Sibyl or Mr. Dent's model.
Sibyl_year < Anderson_year,
Dent_year < Anderson_year,

% Clue #6: The Kratos is two years older than George's car and four years older than the Nike.
Kratos_year is George_year + 2,
Kratos_year is Nike_year + 4.

%solve_puzzle(AnswerList)
solve_puzzle(AnswerList) :-
    answer_form(AnswerList).