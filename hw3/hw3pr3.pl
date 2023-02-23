//Name: Matthew Stevens
//UIN: 924000693
//CSCE 420
//Due: March 26, 2018
//hw3pr3.pl

mother(mum, elizabeth).
mother(mum, margaret).
mother(elizabeth, charles).
mother(elizabeth, anne).
mother(elizabeth, andrew).
mother(elizabeth, edward).
mother(kydd, diana).
mother(diana, william).
mother(diana, harry).
mother(anne, peter).
mother(anne, zara).
mother(sarah, beatrice).
mother(sarah, eugenie).
mother(sophie, louise).
mother(sophie, james). 
mother(zara, mia).
mother(autumn, isla).
mother(autumn, savannah).
mother(kate, prince_george).
mother(kate, charlotte).

father(king_george, elizabeth).
father(king_george, margaret).
father(spencer, diana).
father(philip, charles).
father(philip, anne).
father(philip, andrew).
father(philip, edward).
father(charles, william).
father(charles, harry).
father(mark, peter).
father(mark, zara).
father(andrew, beatrice).
father(andrew, eugenie).
father(edward, louise).
father(edward, james).
father(mike, mia).
father(peter, isla).
father(peter, savannah).
father(william, prince_george).
father(william, charlotte).

parent(X, Y) :- father(X, Y) ; mother(X, Y).
parents(X, Y) :- father(X, Y), mother(Z, Y), X \== Z.
grandchild(X, Y) :- parent(Y, Z), parent(Z, X).
sibling(X, Y) :- parents(Z, X), parents(Z, Y), X \== Y.

male(king_george).
male(philip).
male(spencer).
male(charles).
male(mark).
male(andrew).
male(edward).
male(william).
male(harry).
male(peter).
male(james).
male(mike).
male(prince_george).
male(timothy).

female(mum).
female(elizabeth).
female(kydd).
female(diana).
female(anne).
female(sarah).
female(sophie).
female(margaret).
female(zara).
female(beatrice).
female(eugenie).
female(louise).
female(kate).
female(autumn).
female(mia).
female(isla).
female(savannah).
female(charlotte).
female(camilla).

married(king_george, mum).
married(philip, elizabeth).
married(charles, diana).
married(charles, camilla).
married(mark, anne).
married(timothy, anne).
married(andrew, sarah).
married(edward, sophie).
married(spencer, kydd).
married(william, kate).
married(peter, autumn).
married(mike, zara).

brother_in_law(X, Y) :- (married(X, Z), sibling(Z, Y), male(X)) ; 
(married(Z, Y), sibling(Z, X), male(X)).
sister_in_law(Y, X) :- (married(Z, Y), sibling(Z, X), female(Y)) ; 
(married(X, Z), sibling(Z, Y), female(Y)).

great_grandparent(Z, W) :- parent(X, W), parent(Y, X), parent(Z,Y).
ancestor(X, Y) :- parent(X, Y) ; parent(Z, Y), ancestor(X, Z).

first_cousin(W, Z) :- parent(X, W), parent(Y, Z), sibling(X, Y).
