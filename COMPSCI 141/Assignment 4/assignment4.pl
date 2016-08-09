%%%

nonStopTrain(sandiego,oceanside).
nonStopTrain(lasvegas,sandiego).
nonStopTrain(sanfrancisco,bakersfield).
nonStopTrain(bakersfield,sandiego).
nonStopTrain(oceanside,losangeles).
nonStopTrain(portland,sanfrancisco).
nonStopTrain(seattle,portland).

% nonStopTrain(oceanside,seattle).

%%%

routeTrip(Origin, Destination, Trip) :-
  routeTrip(Origin, Destination, [Origin], Trip).

routeTrip(Origin, Destination, Visited, Trip) :-
  nonStopTrain(Origin, Destination),
  reverse([Destination|Visited], Trip).

routeTrip(Origin, Destination, Visited, Trip) :-
  nonStopTrain(Origin, Gateway),
  \+memberchk(Gateway, Visited),
  routeTrip(Gateway, Destination, [Gateway|Visited], Trip).

canTravel(A, B) :-
  routeTrip(A, B, _),
  routeTrip(B, A, _).

%%%

gender(sue, f).
gender(jim, m).
gender(tom, m).
gender(joe, m).
gender(cami, f).
gender(bob, m).
gender(fay, f).
gender(beth, f).

hobby(sue, yoga).
hobby(jim, chess).
hobby(tom, run).
hobby(tom, yoga).
hobby(joe, chess).
hobby(joe, run).
hobby(cami, yoga).
hobby(cami, chess).
hobby(cami, run).
hobby(bob, run).
hobby(fay, yoga).
hobby(fay, run).
hobby(fay, chess).
hobby(beth, chess).
hobby(beth, run).

% hobby(joe, yoga).

%%%

oppositeGender(Pa, Pb) :-
  gender(Pa, Ga),
  gender(Pb, Gb),
  \+Ga==Gb.

shareHobby(Pa, Pb) :-
  hobby(Pa, Ha),
  hobby(Pb, Hb),
  Ha==Hb.

neighbor(Pa, Pb) :-
  oppositeGender(Pa, Pb),
  shareHobby(Pa, Pb), !.

neighbors([P1, P2, P3, P4, P5, P6, P7, P8]) :-
  neighbor(P1, P2),
  neighbor(P2, P3),
  neighbor(P3, P4),
  neighbor(P4, P5),
  neighbor(P5, P6),
  neighbor(P6, P7),
  neighbor(P7, P8),
  neighbor(P8, P1).

seatingSolution([], _).

seatingSolution([P|Unseated], Seated) :-
  member(P, [sue, jim, tom, joe, cami, bob, fay, beth]),
  \+memberchk(P, Seated),
  seatingSolution(Unseated, [P|Seated]).

seatingChart(X) :-
  seatingSolution(X, []),
  neighbors(X).
