//Name: Matthew Stevens
//UIN: 924000693
//CSCE 420
//Due: March 26, 2018
//hw3pr2.pl

%Map rules
adjacent(a,t).
adjacent(a,s).
adjacent(a,z).
adjacent(o,s).
adjacent(o,z).
adjacent(s,f).
adjacent(s,r).
adjacent(f,b).
adjacent(r,p).
adjacent(r,c).
adjacent(r,b).
adjacent(p,b).
adjacent(p,c).
adjacent(t,l).
adjacent(l,m).
adjacent(d,m).
adjacent(d,c).
adjacent(b,g).
adjacent(b,u).
adjacent(u,v).
adjacent(u,h).
adjacent(v,i).
adjacent(i,n).
adjacent(h,e).

%acyclic function which compares characters in a list to see if there are duplicates
acyclic([]).
acyclic([Head|[]]).
acyclic([Head|Goal]) :- 
\+(member(Head,Goal)),
acyclic(Goal).

%path(Path,Start,Goal) means P is a path from Start to Goal
%reverse, list is the reverse of Path, because Head represents arriving at the achieved goal and List is the set of previous moves in stack form.
path(Path, List, Head, Head) :- reverse([Head|List], Path).
path(Path, List, Head, Goal) :- 
Head \== Goal,
acyclic([Head|List]),
(adjacent(Head,X);adjacent(X,Head)),
path(Path, [Head|List], X, Goal). 

%predefined rules
path([X,Y],X,Y):-adjacent(X,Y).
path([X,Y],X,Y):-adjacent(Y,X).
path([Goal],Goal,Goal).

%initialize Path with an empty list, this list is used as a stack (FILO) for comparison
path(Path,Head,Goal):-
path(Path,[],Head,Goal).
