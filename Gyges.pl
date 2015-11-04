/*Instituto Tecnológico de Costa Rica
;Escuela de Computación
;Ingeniería en Computación
;Lenguajes de Programacion
;Grupo 2
;Tarea: Gyges
;Adrian Lopez Quesada
;2014081634
;Kirstein Gätjens S.
;14/10/15

;Manual de Usuario:
  Solo tiene una relacion para el AI de Gyges, se utiliza 
  Gyges(TableroOriginal,TableroFinal,PosisicionActual,PosicionFinal,Turno).

  Para el tablero original se debe especificar todos los 36 campos del tablero a como estan en el juego,
  un ejemplo serian los siguientes:

  [f1,f2,f0,f1,f2,f1,f0,f0,f2,f0,f0,f0,f0,f0,f0,f0,f0,f0,f0,f0,f3,f0,f0,f0,f0,f0,f0,f0,f0,f0,f3,f3,f0,f1,f2,f1]

  [f3,f2,f0,f1,f2,f3,f0,f0,f0,f2,f0,f0,f0,f0,f0,f0,f0,f0,f0,f0,f0,f3,f0,f0,f0,f0,f0,f0,f0,f0,f3,f3,f1,f0,f2,f1] 

La variable solucion no se pone ningun valor, ya que aqui devuelve el tablero de solucion, la posicion actual y la final
tampoco se administran por las mismas razones, el turno si de debe administrar para decidir en que parte del tablero se va a jugar
en que parte se considera mas cercana al jugador. Se utiliza p1 para indicar turno del jugador superior (0) y p2 del inferior (37).

El tablero tiene la siguientes posiciones:

[1,2,3,4,5,6,
7,8,9,10,11,12,
13,14,15,16,17,18,
19,20,21,22,23,24,
25,26,27,28,29,30,
31,32,33,34,35,36].

Por lo que al regresar el resultado se utilizan estas posiciones, siendoe el 0 la posicion ganadora del p2 y 
37 la posicion ganadora de p1.

En caso de no haber jugada alguna para poder ganar entnces retorna falso, de lo contrario siempre devuelve una jugada


;Analisis de Resultados: Toda la AI funciona
Movimientos legales de cada jugador segun el turno: A
Movimiento ganador: A
Mejor movimiento para no darle el gane al enemigo: A
Se realizan puentes en los mivimientos: A
No se encicla el AI: A
Colocar todas las piezas antes de iniciar el juego: F No se implemento del todo
*/

%--------------------Valores de las fichas----------------------------------
fichaval(f0,0).
fichaval(f1,1).
fichaval(f2,2).
fichaval(f3,3).

%--------------------Relaciones dentro del tablero y en la misma fila----------------------------------

dentroV(Nuevo):- Nuevo<37,Nuevo>0.


dentroH(Nuevo,Viejo):- 0<Viejo,
					  7>Viejo,
					  0<Nuevo,
					  7>Nuevo.
dentroH(Nuevo,Viejo):- 6<Viejo,
					  13>Viejo,
					  6<Nuevo,
					  13>Nuevo.
dentroH(Nuevo,Viejo):- 12<Viejo,
					  19>Viejo,
					  12<Nuevo,
					  19>Nuevo.
dentroH(Nuevo,Viejo):- 18<Viejo,
					  25>Viejo,
					  18<Nuevo,
					  25>Nuevo.
dentroH(Nuevo,Viejo):- 24<Viejo,
					  31>Viejo,
					  24<Nuevo,
					  31>Nuevo.
dentroH(Nuevo,Viejo):- 30<Viejo,
					  37>Viejo,
					  30<Nuevo,
					  37>Nuevo. 

%--------------------Valores del tipo del arbol, valores para cortar profundidad del arbol----------------------------------
recursion(recursion).
find1(find1).

%-------------------Complemento para la tabla inversa del p2----------------------------------

complemento(Valor,Comp):- Comp is 37-Valor.

%--------------------Relacion de no pasar por el mismo espacio----------------------------------

nopasado(nopasado).

tablemoves([nopasado,nopasado,nopasado,nopasado,nopasado,nopasado,
		nopasado,nopasado,nopasado,nopasado,nopasado,nopasado,
		nopasado,nopasado,nopasado,nopasado,nopasado,nopasado,
		nopasado,nopasado,nopasado,nopasado,nopasado,nopasado,
		nopasado,nopasado,nopasado,nopasado,nopasado,nopasado,
		nopasado,nopasado,nopasado,nopasado,nopasado,nopasado]).

%--------------------Relaciones de los jugadores----------------------------------

player1(1).
player2(0).

%--------------------Relaciones de las filas ----------------------------------

row1([T11,T12,T13,T14,T15,T16,
		_,_,_,_,_,_,
		_,_,_,_,_,_,
		_,_,_,_,_,_,
		_,_,_,_,_,_,
		_,_,_,_,_,_],[T11, T12, T13, T14, T15, T16],1).
row1([_,_,_,_,_,_,
		T11,T12,T13,T14,T15,T16,
		_,_,_,_,_,_,
		_,_,_,_,_,_,
		_,_,_,_,_,_,
		_,_,_,_,_,_],[T11, T12, T13, T14, T15, T16],7).
row1([_,_,_,_,_,_,
		_,_,_,_,_,_,
		T11,T12,T13,T14,T15,T16,
		_,_,_,_,_,_,
		_,_,_,_,_,_,
		_,_,_,_,_,_],[T11, T12, T13, T14, T15, T16],13).

rowValues([]):-fail.
rowValues([f0|Tail]):-rowValues(Tail).
rowValues([f1|_]).
rowValues([f2|_]).
rowValues([f3|_]).

%--------------------Relaciones de victoria----------------------------------

win(31).
win(32).
win(33).
win(34).
win(35).
win(36).

%--------------------posicion de una valor en el tablero----------------------------------

tableval([Head|_],1,Head).
tableval([_|Tail],Number,Val):- Number2 is Number - 1,
								tableval(Tail,Number2,Val).


%--------------------Cambio de valores en el tablero----------------------------------

changeValues([_|Tail], 1, Val,[Val|Tail]).

changeValues([Head|Tail],Number, Val, [Head|Tail2]):- Number2 is Number - 1,
											changeValues(Tail,Number2, Val, Tail2).

%--------------------Auxiliar para encontrar 1's y 0's del AI----------------------------------

gygesAux(Values,Sol,PosActual,PosFinal,Row1,Number,ai):-
	tablemoves(Table),
	gygesmove1(Row1,Number,Values,Table,Sol,PosFinal,PosActual,find1,ai),!.

gygesAux(Values,Sol,PosActual,PosFinal,Row1,Number,ai):-
	tablemoves(Table),
	gygesmove1(Row1,Number,Values,Table,Sol,PosFinal,PosActual,recursion,ai),!.

gygesAux(Values,Sol,PosActual,PosFinal,Row1,Number,ai):-
	tablemoves(Table),
	gygesmove1(Row1,Number,Values,Table,Sol,PosFinal,PosActual,findany,ai),!.

gygesAux(Values,Sol,PosActual,PosFinal,Row1,Number,verify):-
	tablemoves(Table),
	gygesmove1(Row1,Number,Values,Table,Sol,PosFinal,PosActual,verify,ver).

gygesVerify(Values,PosActual,PosFinal,Turn,Value):-
		player1(Turn),!,
		row1(Values,Row1,Number),
		rowValues(Row1),!,
		gygesAux(Values,Sol,PosActualAux,PosFinalAux,Row1,Number,verify), 
		move(PosActualAux,PosActual), move(PosFinalAux,PosFinal),!,Value is 1.

gygesVerify(Values,PosActual,PosFinal,Turn,Value):-
		player2(Turn),!,
		reverse(Values,RevVal),
		row1(RevVal,Row1,Number),
		rowValues(Row1),!,
		gygesAux(RevVal,RevSol,RevPosActual,RevPosFinal,Row1,Number,verify),
		reverse(RevSol,Sol), complemento(RevPosActual,PosActualAux), complemento(RevPosFinal,PosFinalAux)
		,move(PosActualAux,PosActual), move(PosFinalAux,PosFinal),!,Value is 1.

gygesVerify(Values,PosActual,PosFinal,Turn,0).

gyges(Values,PosActual,PosFinal,Turn):-
		player1(Turn),!,
		row1(Values,Row1,Number),
		rowValues(Row1),!,
		gygesAux(Values,Sol,PosActualAux,PosFinalAux,Row1,Number,ai),!, 
		move(PosActualAux,PosActual), move(PosFinalAux,PosFinal),!.

gyges(Values,PosActual,PosFinal,Turn):-
		player2(Turn),!,
		reverse(Values,RevVal),
		row1(RevVal,Row1,Number),
		rowValues(Row1),!,
		gygesAux(RevVal,RevSol,RevPosActual,RevPosFinal,Row1,Number,ai),!,
		reverse(RevSol,Sol), complemento(RevPosActual,PosActualAux), complemento(RevPosFinal,PosFinalAux),!
		,move(PosActualAux,PosActual), move(PosFinalAux,PosFinal),!.
	

%--------------------Relacion de control del movimiento del contrario en mi turno----------------------------------

gygesAdvAux(RevVal,Row1,Number):-
	tablemoves(Table),
	gygesmove1(Row1,Number,RevVal,Table,Sol,PosFinal,PosActual,find1,ai),!,fail.

gygesAdvAux(RevVal,Row1,Number):-!.

gygesAdversary(Values):-
		reverse(Values,RevVal),
		row1(RevVal,Row1,Number),
		rowValues(Row1),!,
		gygesAdvAux(RevVal,Row1,Number). 


gygesAdversary(_,_,0).

%--------------------Relacion que encuentra una posicion y valores en una fila, llama a todas ls jugadas de esa fila----------------------------------

gygesmove1([],_,_,_,_,_,_,_,_):- !,fail.

gygesmove1([f0|Tail],Number,Values,Table,Sol,PosFinal,PosInicial,Type,Type2):- Number2 is Number + 1, 								
								gygesmove1(Tail,Number2,Values,Table,Sol,PosFinal,PosInicial,Type,Type2).
																	
gygesmove1([f1|Tail],Number,Values,Table,Sol,PosFinal,PosInicial,Type,ai):- gygesplay(Values,Number,Table, 1, Sol,f1,Type,f0,PosFinal), PosInicial is Number,!.
gygesmove1([f1|Tail],Number,Values,Table,Sol,PosFinal,PosInicial,Type,ver):- gygesplay(Values,Number,Table, 1, Sol,f1,verify,f0,PosFinal), PosInicial is Number.
gygesmove1([f1|Tail],Number,Values,Table,Sol,PosFinal ,PosInicial,Type,Type2):- Number2 is Number + 1, gygesmove1(Tail,Number2,Values,Table,Sol,PosFinal,PosInicial,Type,Type2).

gygesmove1([f2|Tail],Number,Values,Table,Sol,PosFinal,PosInicial,Type,ai):- gygesplay(Values,Number,Table, 2, Sol,f2,Type,f0,PosFinal), PosInicial is Number,!.
gygesmove1([f2|Tail],Number,Values,Table,Sol,PosFinal,PosInicial,Type,ver):- gygesplay(Values,Number,Table, 2, Sol,f2,verify,f0,PosFinal), PosInicial is Number.
gygesmove1([f2|Tail],Number,Values,Table,Sol,PosFinal,PosInicial,Type,Type2):- Number2 is Number + 1, gygesmove1(Tail,Number2,Values,Table,Sol,PosFinal,PosInicial,Type,Type2).

gygesmove1([f3|Tail],Number,Values,Table,Sol,PosFinal,PosInicial,Type,ai):- gygesplay(Values,Number,Table, 3, Sol,f3,Type,f0,PosFinal), PosInicial is Number,!.
gygesmove1([f3|Tail],Number,Values,Table,Sol,PosFinal,PosInicial,Type,ver):- gygesplay(Values,Number,Table, 3, Sol,f3,verify,f0,PosFinal), PosInicial is Number.
gygesmove1([f3|Tail],Number,Values,Table,Sol,PosFinal,PosInicial,Type,Type2):- Number2 is Number + 1, gygesmove1(Tail,Number2,Values,Table,Sol,PosFinal,PosInicial,Type,Type2).


%--------------------Relacion que se encarga de todas las extensiones del arbol de una sola ficha----------------------------------

gygesplaychange(Values, PosActual, Moves, 1, WinnerTable, FindPos,InitVal,Type,SavedFicha,PosFinal):-
			tableval(Values,FindPos,Val), fichaval(Val,NewMoves), tableval(Moves, FindPos, Occupied), nopasado(Occupied), changeValues(Values, PosActual, SavedFicha, Values2),
			changeValues(Moves,PosActual,pasado,MovesFinal), gygesplay(Values2, FindPos, MovesFinal, NewMoves, WinnerTable,InitVal,Type,Val,PosFinal).

gygesplaychange(Values, PosActual, Moves, 2, WinnerTable, FindPos,InitVal,Type,SavedFicha,PosFinal):-
			tableval(Values,FindPos,Val), fichaval(Val,0), tableval(Moves, FindPos, Occupied), nopasado(Occupied), changeValues(Values, PosActual, SavedFicha, Values2),
			NewCount is 1, changeValues(Values2,FindPos, InitVal,ValuesFinal),
			changeValues(Moves,PosActual,pasado,MovesFinal), gygesplay(ValuesFinal, FindPos, MovesFinal, NewCount, WinnerTable,InitVal,Type,f0,PosFinal).

gygesplaychange(Values, PosActual, Moves, 3, WinnerTable, FindPos,InitVal,Type,SavedFicha,PosFinal):-
			tableval(Values,FindPos,Val), fichaval(Val,0), tableval(Moves, FindPos, Occupied), nopasado(Occupied), changeValues(Values, PosActual, SavedFicha, Values2),
			NewCount is 2, changeValues(Values2,FindPos, InitVal,ValuesFinal),
			changeValues(Moves,PosActual,pasado,MovesFinal), gygesplay(ValuesFinal, FindPos, MovesFinal, NewCount, WinnerTable,InitVal,Type,f0,PosFinal).  


gygesplay(Values,PosActual,Moves,0,ValuesFin,InitVal,recursion,SavedFicha,PosActual):- changeValues(Values,PosActual,InitVal,ValuesFin), 
gygesAdversary(ValuesFin),!.

gygesplay(Values, PosActual, Moves, Count, Values,InitVal,find1,SavedFicha,37):- Count = 1, win(PosActual),!.
gygesplay(Values, PosActual, Moves, 0, Values,InitVal,findany,SavedFicha,PosActual):-changeValues(Values,PosActual,InitVal,ValuesFin),!.
gygesplay(Values, PosActual, Moves, 0, Values,InitVal,verify,SavedFicha,PosActual):-changeValues(Values,PosActual,InitVal,ValuesFin).


%-----------------------------------------------------------------------------------------------------------------------------

gygesplay(Values, PosActual, Moves, Count, WinnerTable,InitVal,Type,SavedFicha,PosFinal):-  FindPos is PosActual + 6,
dentroV(FindPos),
gygesplaychange(Values,PosActual,Moves,Count,WinnerTable,FindPos,InitVal,Type,SavedFicha,PosFinal).

gygesplay(Values, PosActual, Moves, Count, WinnerTable,InitVal,Type,SavedFicha,PosFinal):-  FindPos is PosActual + 1,
dentroH(FindPos,PosActual),
gygesplaychange(Values,PosActual,Moves,Count,WinnerTable,FindPos,InitVal,Type,SavedFicha,PosFinal).


gygesplay(Values, PosActual, Moves, Count, WinnerTable,InitVal,Type,SavedFicha,PosFinal):-  FindPos is PosActual - 1,
dentroH(FindPos,PosActual),
gygesplaychange(Values,PosActual,Moves,Count,WinnerTable,FindPos,InitVal,Type,SavedFicha,PosFinal).


gygesplay(Values, PosActual, Moves, Count, WinnerTable,InitVal,Type,SavedFicha,PosFinal):-  FindPos is PosActual - 6,
dentroV(FindPos),
gygesplaychange(Values,PosActual,Moves,Count,WinnerTable,FindPos,InitVal,Type,SavedFicha,PosFinal).


%Disculpe por el siguiente codigo, debido a la entrega de resumenes esta misma fecha no tuve tiempo suficiente 
%para hacer esta parte correctamente...

move(0,w0).
move(1,a0).
move(2,a1).
move(3,a2).
move(4,a3).
move(5,a4).
move(6,a5).
move(7,b0).
move(8,b1).
move(9,b2).
move(10,b3).
move(11,b4).
move(12,b5).
move(13,c0).
move(14,c1).
move(15,c2).
move(16,c3).
move(17,c4).
move(18,c5).
move(19,d0).
move(20,d1).
move(21,d2).
move(22,d3).
move(23,d4).
move(24,d5).
move(25,e0).
move(26,e1).
move(27,e2).
move(28,e3).
move(29,e4).
move(30,e5).
move(31,f0).
move(32,f1).
move(33,f2).
move(34,f3).
move(35,f4).
move(36,f5).
move(37,w0).

%----------------------------------------------------------------------------------------------------------------

