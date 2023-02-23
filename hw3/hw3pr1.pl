//Name: Matthew Stevens
//UIN: 924000693
//CSCE 420
//Due: March 26, 2018
//hw3pr1.pl

unicorn(u).
unicorn(u1).

mythical(u) :- unicorn(u).
notMythical(u1) :- unicorn(u1).

immortal(u) :- mythical(u).
mammal(u1) :- notMythical(u1).

horned(X) :- immortal(X) ; mammal(X).
magical(X) :- horned(X).
