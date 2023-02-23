//Name: Matthew Stevens
//UIN: 924000693
//CSCE 420
//Due: March 26, 2018
//hw3pr4.pl

my_sorted([X|[]]).
my_sorted([Start|[Head|Tail]]):- (Start < Head; Start = Head), my_sorted([Head|Tail]).

my_length(List1,List2):- length(List1, Y), length(List2, Z), Y = Z.

my_perm1([],[]).
my_perm1([], X).
my_perm1([Head|Tail], [Head2|Tail2]):- member(Head, [Head2|Tail2]),
((Head = Head2, my_perm1(Tail, Tail2));(Head \== Head2, my_perm1([Head], Tail2))),
my_perm1(Tail, [Head2|Tail2]).

my_perm(List1, List2) :- my_length(List1, List2), my_perm1(List1, List2). 

my_sort(L, M):- my_perm(M, L), my_sorted(M).
