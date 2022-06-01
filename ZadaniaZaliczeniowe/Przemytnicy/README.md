Opis Uzytych Algorytmow
-----------------------

Nie Udalo Mi Sie Uzyskac Dokladnej Odpowiedzi
ze zwracana wartoscia.

Sprobowalem Uzycia Algorytmow Do Wykrywania Najkrotszych Sciezek oraz Cykli.

Wynik 60 dla grafu testowego otrzymalem jedynie Modyfikujac Algorytm Floyda Warshalla do znajdowania Cykli.


1.  Uruchom Floyd Warshall na naszym grafie

2.	min <- infinity
	vertex <- None
	for each pair of vertices u,v
    		if (dist(u,v) + dist(v,u) < min):
           		min <- dist(u,v) + dist(v,u)
           		pair <- (u,v)
	return path(u,v) + path(v,u)

3. path(u,v) + path(v,u) to najkrotsza sciezka z u do v, a potem z v do u, temu jest cyklem.




Wtedy jednak nie wliczamy cla.


Algorytm Hierholzera: 
====================
Algorytm znajdujacy Cykl/Sciezke Eulera w grafie.
Algorytm Hierholzera potrafi znalezc sciezke Eulera
w czasie liniowym O(E).

Szkic Dzialania: 
    Jesli losowo przechodzimy graf, bez powtarzania krawedzi mozemy przypadkowo
    skonczyc na tym samym wierzcholku, ale wzieta sciezka moze nie zawierac wszystkich
    krawedzi.(Cykl Eulera Zawiera Wszystkie Krawedzie).

    Mozemy sprobowac usuwac odwiedzone krawedzie. Po ich usunieciu
    graf jest podzielony na wiele komponentow.
    Wszystkie komponenty zawieraja Cykl Eulera. Poniewaz Jesli graf, jest eulerowski
    to zawiera wszystkie wierzcholki o parzystyh stopniach. Stopien kazdego wierzcholka
    w cyklu tez jest parzysty. Stopien wierzcholkow po usunieciu cyklu pozostaje parzysty.

    Po tym, znajdujemy nowy Cykl Eulera w komponentach z wiecej niz jednym wierzcholkiem.
    Nowy Cykl musi sie zaczynac od wierzcholka ktory byl czescia poprzedniego cyklu.

    Przyklad:
    Mamy z tego dwa cykle eulera:

    1-2-3-4-5-6-1
    6-7-2-6
    Laczac je mamy: 1-2-3-4-5-(6-7-2-6)-1

    W ten sposob, znajdujemy i laczymy wszystkie Cykle Eulera az usuniemy wszystkie krawedzie z grafu.

Kroki:
    1. Upewnij sie, ze graf G jest spojny i zawiera dokladnie 0 albo dwa wierzcholki
    o nieparzystych stopniach.
    2. Inicjalizuj 2 stosy. Pierwszy stos - current_path przechowuje tymczasowy Cykl Eulera. 
    Drugi stos - circuit path - przechowuje wynikowy Cykl Eulera.
    3. Niech startowy wierzcholek to v; Jezeli graf zawiera dokladnie 2 wierzcholki o nieparzystych
    stopniach, to jeden z nich powinien byc wierzcholkiem startowym. Jezeli graf zawiera dokladnie
    0 wierzcholkow o nieparzystych stopniach, wtedy dowolny wierzcholek moze byc startowy.
    4. Push v do current_path
    5. Niech u = current_path.top()
    6. Jesli wszystkie krawedzie z u sa odwiedzone, pop u z
    current_path oraz push do circuit_path
    7. Jezeli wszystkie krawedzie z u sa nie odwiedzone.
    Wybierz dowolna krawedz (u, x), push x do circuit_path oraz usun (u, x) z G.
    8. Powtarzaj Kroki 5 oraz 7 dopoki current_path nie jest pusta.

    Wynikowy Cykl Eulera to circuit_path


Algorytm DFS (Silnie Spojne Skladowe oraz Cyklicznosc):
========================================================

Zlozonosc to zwykla zlozonosc DFS'a: O( |V| + |E| )

Sprawdzenie Cyklicznosci Grafu Skierowanego: 
    DFS dla spojnego grafu tworzy drzewo. Cykl w grafie istnieje tylko gdy w grafie istnieje back-edge.
    Back Edge - to petla, ktora moze byc albo od wierzcholka do samego siebie.
    np. 1 -> 1, albo z wierzcholka do reszty drzewa.
    Dzieki temu graf ma cykl, poniewaz mozemy 'wracac' i krazyc po grafie.

    Dla grafow niespojnych bierzemy Las Dla kazdego wywolania DFS, ale to jest niepotrzebne w tym zadaniu.

Szkic:

    Tworzymy DFS'a - odwiedzamy aktualny wierzcholek, 'visited'.
    Dodajemy indeks do stosu rekursji.
    Dla kazdego nieodwiedzonego wierzcholka uruchom rekurencyjnego DFS'a,
    jesli funkcja rekurencyjne zwroci true, zwroc true.
    Jesli sasiedzi sa juz odwiedzeni w stosie rekurencji zwroc true.

    Jesli jakiekolwiek wywolanie DFS'a zwroci prawde zwroc prawde -> wykryto cykl.
    wpp. zwroc falsz.

Czy Graf Jest Eulerowski:
    Mozemy sprobowac uzycia algorytmy Kosaraju bazujacego na DFS dzialajacego jak DFS w O (|V| + |E|)

Wiemy, ze:
    Graf Skierowany Jest Eulerowski kiedy:
    
    1) Wszystkie Wierzcholki o stopniu niezerowym naleza do jednego Strongly Connected Component
    oraz
    2) InDegree oraz OutDegree sa rowne dla kazdego wierzcholka.

    Zeby porownywac indegree oraz outdegree musimy przechowywac stopnie wejsciowy i wyjciowy kazedego
    wierzcholka. Stopien OutDegree moze byc ustalony przez rozmiar listy sasiedztwa. 
    Dla stopnia wejsciowego InDegree mozemy stworzyc tablice pomocnicza o rozmiarze liczby wierzcholkow.



Podejscie Z Rozwiazaniem Jako Problem Drogi Chinskiego Listonosza:
=================================================================


"Moze sie zdarzyc, ze proces otrzymywania danego metalu ze zlota, bedzie przebiegac wielostopniowo
i ze na kazdym etapie uzyskiwany bedzie inny metal"

- Wierzcholki Grafu Moga Sie Roznic, ale nie musza.

Ciag Wierzcholkow "Metali":

m0, m1, m2, m3, m4, m5, m6, m7, mk

Wiemy ze: 

m0 = mk

=> 

m0 = mk
< m0, m1, m2, m3, m4, m5, m6, m7, mk >

To Cykl W Grafie poniewaz to sciezka zamknieta oraz nie ma warunku ze metale [m1 ... mk-1]
nie beda zlotem. (Choc mozna by tak zakladac, ale nie wiadomo czy musimy wykorzystac wszystkie przemiany oferowane przez Alchemikow).

Cykl Hamiltona – cykl prosty przebiegający przez wszystkie wierzchołki grafu i przechodzący przez nie dokładnie 1 raz.

Cykl Eulera – cykl zawierający wszystkie krawędzie grafu i przechodzący przez nie dokładnie 1 raz.

Jesli Nie musimy Wykorzystac Wszystkich Przemian Alchemikow (krawedzi naszego grafu) to szukamy poprostu cyklu Hamiltona.
Jesli kazda przemiana musi zostac uzyta to szukamy permutacji krawedzi, znowu nie wszystkie metale beda uzyte. Cykl Eulera.

Uwaga2:
---
Wyjscie: Na Wyjsciu mamy miec ciag k metali. Wiemy ze 1 <= k <= n . Masa Metali sie nie zmienia. Wiec mozna jej nie brac pod uwage.
Jednak z warunku { 1 <= k <= n } nie wynika ze ciag k metali musi byc permutacja n metali. k moze byc mniejsze.



Algorytm Dijkstry: 
=================
    Mozemy Naiwnie Szukac Rozwiazania Algorytmem Dijkstry Szukajac Najkrotszej Sciezki, ktora tez moze byc Cyklem. 
    Nie wiemy jednak czy Algorytm Da nam najlepsze rozwiazanie.
    
    
    Wyjscie: Na Wyjsciu mamy miec ciag k metali. Wiemy ze 1 <= k <= n . Masa Metali sie nie zmienia. Wiec mozna jej nie brac pod uwage.
    Jednak z warunku { 1 <= k <= n } nie wynika ze ciag k metali musi byc permutacja n metali. k moze byc mniejsze.
    
    Po wczytaniu listy sasiedztwa widzimy, ze graf jest Cykliczny. 
    Mozemy probowac modyfikowac algorytm Dijkstry usuwajac wszystkie liscie - nie moga byc czescia cyklu.( Tak samo jak wierzcholki z samymi wychodzacymi 
    krawedziami ).

     
    Obserwacja:
    -----------
    Uruchamiamy Algorytm Dijkstry z kazdego wierzcholka zeby znalezc najkrotsza sciezke do siebie samego.

    Jesli taka sciezka istnieje : najkrotsza sciezka z dowolnego wierzcholka do siebie samego to najtanszy cykl.
    Algorytm Dijkstry zajmie O(|E| log |V| ) wiec sumarycznie otrzymalibysmy O( |V||E| log |V| ).

    Gdyby to zadzialalo to to samo szybciej mozna by zrobic algorytmem Floyda-Warshalla, poniewaz graf moze miec O( |V| ^ 2 ) krawedzi.

