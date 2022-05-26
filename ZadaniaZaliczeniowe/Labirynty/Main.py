from tkinter import *
import tkinter.ttk as tk
from PIL import Image, ImageTk, ImageOps
import threading
import numpy
import time
from collections import deque

image_name = "Zdjecie_Labiryntu.png"


# Pomocnicze Funkcje do inicjalizacji slownika z funkcjonalnosciami

def Program():
    globals()["algorithm"] = algo.get()
    globals()["Flag"] = globals()["bstart"] & globals()["bend"]
    print("Flag: ", globals()["Flag"])
    main(image_name)                                                  # Wywolujemy Funkcje Main dla sciezki zdjecia labiryntu

def CheckStart():
    globals()["startno"] = (slidery.get(), sliderx.get())
    print(f"Start Node: {globals()['startno']}")
    globals()["sposvar"].set(f"Start Position= {globals()['startno']}")
    globals()["bstart"] = True
    ind = globals()["maze"].arpath.index((slidery.get(), sliderx.get()))
    globals()["maze"].start = globals()["maze"].arnode[ind]


def CheckEnd():
    globals()["endno"] = (slidery.get(), sliderx.get())
    print(f"End Node: {globals()['endno']}")
    globals()["eposvar"].set(f"End Position= {globals()['endno']}")
    globals()["bend"] = True
    ind = globals()["maze"].arpath.index((slidery.get(), sliderx.get()))
    globals()["maze"].end = globals()["maze"].arnode[ind]


# Definiujemy okienko w Tkinterze

r = Tk()
r.configure(background='gold')
r.geometry("800x800")
r.title('Przechodzenie Labiryntu')

# Dodawanie stylu i formatowanie komponentow
style = tk.Style()
style.configure("TLabel", foreground="white", background="black")
style.configure("TCombobox", foreground="black", background="white")
style.configure("TScale", foreground="white", background="black")

# Konfiguracja okna dialogowego do wyboru algorytmu (Combobox z algorytmami)

algo = tk.Combobox(r, state="readonly", style="TCombobox")
algo['values'] = ("Dijkstra", "A_Star", "BFS", "DFS")       # Wartosci w Boxie - Algorytmy
algo.current(0)                                             # Domyslny Algorytm - Dijkstra
algo.grid(column=0, row=0, padx=15, pady=5, sticky=W + E, columnspan=3)

# Konfiguracja przycisku Get_Start_Position
startbtn = tk.Button(r, text="Pozycja Startu", command=CheckStart)
startbtn.grid(column=1, row=1, padx=5, pady=5, sticky=W)

# Konfiguracja przycisku Get_End_Position
endbtn = tk.Button(r, text="Pozycja Konca", command=CheckEnd)
endbtn.grid(column=2, row=1, padx=5, pady=5, sticky=W)

# Przycisk Rozwiazywanie
solvebtn = tk.Button(r, text="Rozwiazanie", command=Program, width=30)
solvebtn.grid(column=0, row=2, padx=15, pady=5, sticky=W + E, columnspan=3)


# Flagi
bstart = False
bend = False
startno = (0, 0)
endno = (0, 0)
Flag = False

# Flag = bstart & bend

# Klasa Labiryntu - klasa grafu na ktorym bedziemy uruchamiac wszystkie algorytmy.
# Dla wygody zamiast wyrozniac klasy Vertex i Graph uzyjemy Klasy Maze z Klasa wewnetrzna Node


# Ta klasa jest opakowaniem dla naszego obrazka.
# Kazdy 'kwadrat' labiryntu wczytamy do obiektu klasy wewnetrznej Node - czyli komorki
# labiryntu ktora ma sasiadow czterach sasiadow.


class Labirynt:
    #Klasa wewnetrzna reprezentujaca Wezel Labiryntu
    class Kwadrat:
        def __init__(self, position):
            self.Position = position
            self.Neighbours = [None, None, None, None] # Sasiedzi na planszy [ dol, prawo, gora, lewo ]
        def __repr__(self):
            return f"{self.Position}"
    def __init__(self, im):
        self.arpath = []
        self.arnode = []
        width = im.size[0]
        height = im.size[1]
        data = list(im.getdata(0))

        self.start = None
        self.end = None

        topnodes = [None] * width   #ilosc wezlow gornych
        count = 0
        # Wiersz Startowy
        if (Flag == False):
            for x in range(1, width - 1):
                if data[x] > 0:
                    self.start = Labirynt.Kwadrat((0, x))
                    topnodes[x] = self.start
                    count += 1
                    self.arpath.append(self.start.Position)
                    self.arnode.append(self.start)
                    break
        j = 0
        if (Flag == False):
            j = 1
        for y in range(j, height - 1):

            rowoffset = y * width
            rowaboveoffset = rowoffset - width
            rowbelowoffset = rowoffset + width

            prv = False
            cur = False
            nxt = data[rowoffset + 1] > 0
            leftnode = None

            for x in range(1, width):
                prv = cur
                cur = nxt
                nxt = data[rowoffset + x + 1] > 0

                n = None

                if cur == False:
                    # Dojscie do sciany - brak ruchu
                    continue

                if prv == True:
                    if nxt == True:
                        # PATH PATH PATH
                        if data[rowaboveoffset + x] > 0 or data[rowbelowoffset + x] > 0:
                            n = Labirynt.Kwadrat((y, x))
                            leftnode.Neighbours[1] = n
                            n.Neighbours[3] = leftnode
                            leftnode = n

                            if (y == startno[0] and x == startno[1] and Flag):
                                self.start = n
                    else:
                        # PATH PATH SCIANA
                        n = Labirynt.Kwadrat((y, x))
                        leftnode.Neighbours[1] = n
                        n.Neighbours[3] = leftnode
                        leftnode = None

                        if (y == startno[0] and x == startno[1] and Flag):
                            self.start = n
                else:
                    if nxt == True:
                        # SCIANA PATH PATH
                        n = Labirynt.Kwadrat((y, x))
                        leftnode = n

                        if (y == startno[0] and x == startno[1] and Flag):
                            self.start = n
                    else:
                        # SCIANA PATH SCIANA
                        if (data[rowaboveoffset + x] == 0) or (data[rowbelowoffset + x] == 0):
                            n = Labirynt.Kwadrat((y, x))

                            if (y == startno[0] and x == startno[1] and Flag):
                                self.start = n

                if n != None:
                    if (data[rowaboveoffset + x] > 0):
                        t = topnodes[x]
                        t.Neighbours[2] = n
                        n.Neighbours[0] = t
                    if (data[rowbelowoffset + x] > 0):
                        topnodes[x] = n
                    else:
                        topnodes[x] = None
                    count += 1
                    self.arpath.append(n.Position)
                    self.arnode.append(n)

        # Koniec Wiersza
        rowoffset = (height - 1) * width
        for x in range(1, width - 1):
            if data[rowoffset + x] > 0:
                self.end = Labirynt.Kwadrat((height - 1, x))
                t = topnodes[x]
                t.Neighbours[2] = self.end
                self.end.Neighbours[0] = t
                count += 1
                break

        if (Flag):
            self.end.Position = (endno)

        self.arpath.append(self.end.Position)
        self.arnode.append(self.end)
        self.count = count
        self.width = width
        self.height = height

# Otwieramy obrazek przez PIL i tworzymy obiekt labiryntu
imo = Image.open(image_name)
maze = Labirynt(imo)

# Dopasowywujemy Obrazek Labiryntu Do Rozdzielczosci Kontenera
imglabel = Label(r, height=500, width=500)
imglabel.configure(background='black')
imgtk = ImageTk.PhotoImage(ImageOps.fit(imo, (500, 500)))
imglabel.configure(image=imgtk)
imglabel.image = imgtk
imglabel.grid(column=1, row=3, columnspan=4, padx=0)

# Zmiana w listenerze pozycji (Wskaznika Osi), zeby zapisac wartosci wezla startowego oraz wezla koncowego
slider = StringVar()

def callback(*args):
    slider.set(f"Position:: ( {slidery.get()}, {sliderx.get()} )")
    rgb_im = globals()["imo"].convert('RGB')
    impixels = (rgb_im.load())
    red = (255, 0, 0)
    black = (0, 0, 0)
    offwhite = (255, 201, 201)
    curpos = (sliderx.get(), slidery.get())
    if (impixels[curpos] != black):
        if ((slidery.get(), sliderx.get()) in maze.arpath):
            impixels[curpos[0], curpos[1]] = red
        else:
            impixels[curpos[0], curpos[1]] = offwhite

    img = rgb_im.resize((500, 500), Image.NEAREST)
    imgtk = ImageTk.PhotoImage(img)
    imglabel.configure(image=imgtk)
    imglabel.image = imgtk

# Konfiguracja wartosci x, y

sliderx = IntVar()
sliderx.set('1')
sliderx.trace("w", callback)
slidery = IntVar()
slidery.trace("w", callback)
slidery.set('1')
slider.set(f"Pozycja:: ({sliderx.get()}, {slidery.get()})")


# Konfiguracja labeli dla wyswietlanych informacji

nodec = StringVar()
nodee = StringVar()
pathl = StringVar()
timee = StringVar()
nc = tk.Label(r, textvariable=nodec, style="TLabel")
ne = tk.Label(r, textvariable=nodee, style="TLabel")
pl = tk.Label(r, textvariable=pathl, style="TLabel")
tep = tk.Label(r, textvariable=timee, style="TLabel")
nc.grid(column=3, row=0, padx=3, pady=3, sticky="w")
ne.grid(column=4, row=0, padx=3, pady=3, sticky="w")
pl.grid(column=3, row=1, padx=3, pady=3, sticky="w")
tep.grid(column=4, row=1, padx=3, pady=3, sticky="w")


# Przesuwanie Wzgledem Osi Y

yaxis = tk.Scale(r, from_=0, to_=(imo.size[1] - 1), orient=VERTICAL, style="TScale", command=lambda s: slidery.set('%d' % float(s)))
yaxis.set(1)
yaxis.grid(column=0, row=3, sticky=W + N + S, padx=5)

# Label Wymiaru Obrazka
dimen = tk.Label(r, text=f"Wymiar Obrazka: {imo.size[0]} x {imo.size[1]}", style="TLabel")
dimen.grid(column=4, row=2, padx=2, pady=3, sticky=W)

# Pozycja Label
positionlabel = tk.Label(r, textvariable=slider, style="TLabel")
positionlabel.grid(column=3, row=2, padx=2, pady=3, sticky=W)

# Konfiguracja przesuwania wzdluz osi X
xaxis = tk.Scale(r, from_=0, to_=(imo.size[0] - 1), orient=HORIZONTAL, style="TScale",
                  command=lambda s: sliderx.set('%d' % float(s)))
xaxis.grid(column=1, row=4, columnspan=6, sticky=W + E)
yaxis.set(1)

# Ustawianie wskaznika na pozycje Startowa
sposvar = StringVar()
sposvar.set("Pozycja Start= (1,1)")

# Ustawianie Wskaznika pozycji koncowej
eposvar = StringVar()
eposvar.set("Pozycja Koniec= (1,1)")

# Tworzenie Labeli Start oraz Koniec
spos = tk.Label(r, textvariable=sposvar, style="TLabel")
epos = tk.Label(r, textvariable=eposvar, style="TLabel")

spos.grid(column=2, row=5, sticky=W + N + S, padx=5, columnspan=2)
epos.grid(column=4, row=5, sticky=W + N + S, padx=5)

# Inicjalizacja Wartosci Flag dla algorytmow.


algorithm = "Dijkstra"
bstart = False
bend = False
startno = (0, 0)
endno = (0, 0)
Flag = False

# Dijkstra
def Dijkstra(maze):
    # Width = indeksowanie, total = wielkosc tablicy
    width = maze.width
    total = maze.width * maze.height
    print("\nRozwiazywanie przez Dijkstra\n")

    # Wezel Startowy, wezel koncowy
    start = maze.start
    startpos = start.Position
    end = maze.end
    endpos = end.Position

    visited = [False] * total
    prev = [None] * total

    infinity = float("inf")
    distances = [infinity] * total

    unvisited = FibPQ()
    nodeindex = [None] * total

    # Ustawianie dystansu do startu na wartosc zero i dodanie do kolejki nieodwiedzonych
    distances[start.Position[0] * width + start.Position[1]] = 0
    startnode = FibHeap.Node(0, start)
    nodeindex[start.Position[0] * width + start.Position[1]] = startnode
    unvisited.insert(startnode)

    # Wezly zerowe odwiedzone, ale odwiedzanie nie jest zakonczone
    count = 0
    completed = False

    # Zacznij Dijkstre - kontynuuj dopoki sa wierzcholki nieodwiedzone w kolejce
    while len(unvisited) > 0:
        count += 1

        # Znajdz aktualny punkt najkrotszej sciezki do odwiedzenia
        n = unvisited.removeminimum()

        # Aktualny wezel u, wszyscy sasiedzi beda v
        u = n.value
        upos = u.Position
        uposindex = upos[0] * width + upos[1]

        if distances[uposindex] == infinity:
            break
        # Jezeli upos == endpos, skonczylismy
        if upos == endpos:
            completed = True
            break

        for v in u.Neighbours:
            if v != None:
                vpos = v.Position
                vposindex = vpos[0] * width + vpos[1]

                if visited[vposindex] == False:

                    # Modyfikacja Dijkstry- dodatkowa wartosc, gdzie jestesmy (upos) do sasiada (vpos) - dystans manhattan
                    d = abs(vpos[0] - upos[0]) + abs(vpos[1] - upos[1])

                    # Nowy koszt sciezki do v to dystans do u + extra

                    newdistance = distances[uposindex] + d

                    # Jezeli ten nowy dystans to nowa najkrotsza sciezka do v
                    if newdistance < distances[vposindex]:
                        vnode = nodeindex[vposindex]

                        # v nie jest aktualnie w kolejce priorytetowej - dodaj go
                        if vnode == None:
                            vnode = FibHeap.Node(newdistance, v)
                            unvisited.insert(vnode)
                            nodeindex[vposindex] = vnode
                            distances[vposindex] = newdistance
                            prev[vposindex] = u
                        # v jest juz w kolejce - zmniejsz jego klucz aby przywrocic priorytet
                        else:
                            unvisited.decreasekey(vnode, newdistance)
                            distances[vposindex] = newdistance
                            prev[vposindex] = u

        visited[uposindex] = True

    # Rekonstrukcja Sciezki. Zaczynamy od konca wykorzystujac tablice prev.
    # Tablica Prev zawiera wskazniki do posrednich wezlow na najkrotszej sciezce ze zrodla do danego wierzcholka
    # Zaczynamy end -> prev[end], -> prev[end_parent] -> ... prev[start]
    path = deque()
    current = end
    while (current != None):
        path.appendleft(current)
        current = prev[current.Position[0] * width + current.Position[1]]
    return [path, [count, len(path), completed]]

# Algorytm A-Star
def A_Star(maze):
    print("\nRozwiazywanie przez A Star\n")
    width = maze.width
    total = maze.width * maze.height

    start = maze.start
    startpos = start.Position
    end = maze.end
    endpos = end.Position

    visited = [False] * total
    prev = [None] * total

    infinity = float("inf")
    distances = [infinity] * total

    unvisited = FibPQ()

    nodeindex = [None] * total

    distances[start.Position[0] * width + start.Position[1]] = 0
    startnode = FibHeap.Node(0, start)
    nodeindex[start.Position[0] * width + start.Position[1]] = startnode
    unvisited.insert(startnode)

    count = 0
    completed = False

    while len(unvisited) > 0:
        count += 1

        n = unvisited.removeminimum()

        u = n.value
        upos = u.Position
        uposindex = upos[0] * width + upos[1]

        if distances[uposindex] == infinity:
            break

        if upos == endpos:
            completed = True
            break

        for v in u.Neighbours:
            if v != None:
                vpos = v.Position
                vposindex = vpos[0] * width + vpos[1]

                if visited[vposindex] == False:
                    d = abs(vpos[0] - upos[0]) + abs(vpos[1] - upos[1])

                    # Nowy koszt sciezki do v to dystans do u + extra(g cost)
                    # Nowy dystans to dystans sciezki od start, przez U, do V
                    newdistance = distances[uposindex] + d

                    # V do konca. Uzywamy dystansu manhattanskiego ponownie poniewaz A* dziala dobrze kiedy
                    # koszty g oraz koszty f sa zbalansowane.
                    remaining = abs(vpos[0] - endpos[0]) + abs(vpos[1] - endpos[1])  # Heurystyka

                    # Nie zawieramy kosztu f w pierwszym sprawdzeniu. Chcemy wiedziec ze sciezka "do" naszego wezla V jest najkrotsza.
                    if newdistance < distances[vposindex]:
                        vnode = nodeindex[vposindex]

                        if vnode == None:
                            # V trafia do kolejki priorytetowej z kosztem g + f. Dlatego jesli sie poruszamy blizej konca, dostanie wyzszy priorytet
                            # niz inne wezly
                            vnode = FibHeap.Node(newdistance + remaining, v)
                            unvisited.insert(vnode)
                            nodeindex[vposindex] = vnode
                            # Dystans "do" wezla zostaje tylko g, f nie jest zawarte
                            distances[vposindex] = newdistance
                            prev[vposindex] = u
                        else:
                            # Zmiejszam klucz wezla skoro znalezlismy nowa sciezke. Ale zawieramy koszt f oraz pozostaly dystans.
                            unvisited.decreasekey(vnode, newdistance + remaining)
                            # Dystans "do" zostaje tylko g, bez f
                            distances[vposindex] = newdistance
                            prev[vposindex] = u

        visited[uposindex] = True

    # Rekonstrukcja sciezki za pomoca tablicy prev[], analogiczne rozumowanie jak w Dijkstrze
    path = deque()
    current = end
    while (current != None):
        path.appendleft(current)
        current = prev[current.Position[0] * width + current.Position[1]]
    return [path, [count, len(path), completed]]

# Algorytm BFS
def BFS(maze):
    print("\nPrzechodzenie BFS\n")
    start = maze.start
    end = maze.end

    width = maze.width

    queue = deque([start])
    shape = (maze.height, maze.width)
    prev = [None] * (maze.width * maze.height)
    visited = [False] * (maze.width * maze.height)

    count = 0

    completed = False

    visited[start.Position[0] * width + start.Position[1]] = True

    while queue:
        count += 1
        current = queue.pop()

        if current == end:
            completed = True
            break

        for n in current.Neighbours:
            if n != None:
                npos = n.Position[0] * width + n.Position[1]
                if visited[npos] == False:
                    queue.appendleft(n)
                    visited[npos] = True
                    prev[npos] = current

    path = deque()
    current = end
    while (current != None):
        path.appendleft(current)
        current = prev[current.Position[0] * width + current.Position[1]]

    return [path, [count, len(path), completed]]

# DFS
def DFS(maze):
    start = maze.start
    end = maze.end

    width = maze.width

    stack = deque([start])
    shape = (maze.height, maze.width)
    prev = [None] * (maze.width * maze.height)
    visited = [False] * (maze.width * maze.height)

    count = 0

    completed = False

    while stack:
        count += 1
        current = stack.pop()
        if current == end:
            completed = True
            break

        visited[current.Position[0] * width + current.Position[1]] = True

        for n in current.Neighbours:
            if n != None:
                npos = n.Position[0] * width + n.Position[1]
                if visited[npos] == False:
                    stack.append(n)
                    visited[npos] = True
                    prev[npos] = current
    path = deque()
    current = end
    while (current != None):
        path.appendleft(current)
        current = prev[current.Position[0] * width + current.Position[1]]
    return [path, [count, len(path), completed]]


# Funkcja Przechodzaca Labirynt Wybranym Algorytmem
def Szukacz(input_file):
    maze = globals()["maze"]
    nodec.set(f"Licznik Wezlow: {maze.count}")
    ts = time.time()
    if (algorithm == "Dijkstra"):
        [result, stats] = Dijkstra(maze)
    elif (algorithm == "A_Star"):
        [result, stats] = A_Star(maze)
    elif (algorithm == "BFS"):
        [result, stats] = BFS(maze)
    elif (algorithm == "DFS"):
        [result, stats] = DFS(maze)
    te = time.time()

    total = round(te - ts, 6)               #zaokraglamy czasy przejscia

    # Wypisz dane rozwiazania
    nodee.set(f"Odwiedzone Wezly: {stats[0]}")
    print("\nWezly Odwiedzone: ", stats[0])
    if (stats[2]):
        pathl.set(f"Dlugosc Sciezki: {stats[1]}")
        print("Sciezka znaleziona, dlugosc=", stats[1])
    else:
        pathl.set(f"Sciezki Nie Znaleziono!")
    timee.set(f"Miniony Czas[s]: {total}")
    print("Czas [s]: ", total, "\n")
    pathx = [n.Position for n in result]
    return pathx

# Kopiec Fibonnaciego dla Kolejki Priorytetowej
class FibHeap:
    class Node:
        def __init__(self, key, value):
            #Klucz:Priorytet(Dystans} wartosc: Wezel

            self.key = key
            self.value = value
            self.degree = 0
            self.mark = False
            self.parent = self.child = None
            self.previous = self.next = self

        def issingle(self):
            return self == self.next

        def insert(self, node):
            if node == None:
                return

            self.next.previous = node.previous
            node.previous.next = self.next
            self.next = node
            node.previous = self

        def remove(self):
            self.previous.next = self.next
            self.next.previous = self.previous
            self.next = self.previous = self

        def addchild(self, node):
            if self.child == None:
                self.child = node
            else:
                self.child.insert(node)
            node.parent = self
            node.mark = False
            self.degree += 1

        def removechild(self, node):
            if node.parent != self:
                raise AssertionError("Wezel nie jest rodzicem tego dziecka!")
            if node.issingle():
                if self.child != node:
                    raise AssertionError("Nie mozna usunac wezla ktory nie jest dzieckiem!")
                self.child = None
            else:
                if self.child == node:
                    self.child = node.next
                node.remove()

            node.parent = None
            node.mark = False
            self.degree -= 1

    def __init__(self):
        self.minnode = None
        self.count = 0
        self.maxdegree = 0

    def isempty(self):
        return self.count == 0

    def insert(self, node):
        self.count += 1
        self._insertnode(node)

    def _insertnode(self, node):
        if self.minnode == None:
            self.minnode = node
        else:
            self.minnode.insert(node)
            if node.key < self.minnode.key:
                self.minnode = node

    def minimum(self):
        if self.minnode == None:
            raise AssertionError("Kopiec Pusty!")
        return self.minnode

    def merge(self, heap):
        self.minnode.insert(heap.minnode)
        if self.minnode == None or (heap.minnode != None and heap.minnode.key < self.minnode.key):
            self.minnode = heap.minnode
        self.count += heap.count

    def removeminimum(self):
        if self.minnode == None:
            raise AssertionError("Kopiec Pusty")

        removed_node = self.minnode
        self.count -= 1
        # 1: Ustaw dawne dzieci korzenia jako nowe korzenie
        if self.minnode.child != None:
            c = self.minnode.child

            while True:
                c.parent = None
                c = c.next
                if c == self.minnode.child:
                    break

            self.minnode.child = None
            self.minnode.insert(c)

        if self.minnode.next == self.minnode:
            if self.count != 0:
                raise AssertionError("Blad Kopca: Oczekiwane 0 kluczy, licznik= " + str(self.count))
            self.minnode = None
            return removed_node
        # Polacz korzenie o tym samym stopniu
        logsize = 100
        degreeroots = [None] * logsize
        self.maxdegree = 0
        currentpointer = self.minnode.next

        while True:
            currentdegree = currentpointer.degree
            current = currentpointer
            currentpointer = currentpointer.next
            while degreeroots[currentdegree] != None:
                other = degreeroots[currentdegree]
                # Swap jesli wymagany
                if current.key > other.key:
                    temp = other
                    other = current
                    current = temp

                other.remove()
                current.addchild(other)
                degreeroots[currentdegree] = None
                currentdegree += 1

            degreeroots[currentdegree] = current
            if currentpointer == self.minnode:
                break

        # Usun aktualny korzen i znajdz nowy wezel min
        self.minnode = None
        newmaxdegree = 0
        for d in range(0, logsize):
            if degreeroots[d] != None:
                degreeroots[d].next = degreeroots[d].previous = degreeroots[d]
                self._insertnode(degreeroots[d])
                if (d > newmaxdegree):
                    newmaxdegree = d

        maxdegree = newmaxdegree

        return removed_node

    def decreasekey(self, node, newkey):
        if newkey > node.key:
            raise AssertionError("Nie mozna zmniejszyc klucza do wiekszej wartosci")
        elif newkey == node.key:
            return

        node.key = newkey

        parent = node.parent

        if parent == None:
            if newkey < self.minnode.key:
                self.minnode = node
            return
        elif parent.key <= newkey:
            return

        while True:
            parent.removechild(node)
            self._insertnode(node)

            if parent.parent == None:
                break
            elif parent.mark == False:
                parent.mark
                break
            else:
                node = parent
                parent = parent.parent
                continue

# Kolejka na Kopcu Fibonacciego
class FibPQ():
    def __init__(self):
        self.heap = FibHeap()

    def __len__(self):
        return self.heap.count

    def insert(self, node):
        self.heap.insert(node)

    def minimum(self):
        return self.heap.minimum()

    def removeminimum(self):
        return self.heap.removeminimum()

    def decreasekey(self, node, new_priority):
        self.heap.decreasekey(node, new_priority)


# Sciezka Wypelniona Gradientem
def Gradient(img, result):
    arr = numpy.array(img)
    resultpath = result
    length = len(resultpath)
    for i in range(0, length - 1):
        a = resultpath[i]
        b = resultpath[i + 1]
        # ustawienia kolorystyki dla gradientu
        r = int((i / length) * 250)
        px = (r, 50, 150 - r)
        if a[0] == b[0]:
            # Ys - linia horyzontalnie
            for x in range(min(a[1], b[1]), max(a[1], b[1])):
                arr[a[0], x] = px
        elif a[1] == b[1]:
            # Xs - linia pionowa
            for y in range(min(a[0], b[0]), max(a[0], b[0]) + 1):
                arr[y, a[1]] = px

        time.sleep(0.1)
        img = Image.fromarray(arr)
        img = img.resize((500, 500), Image.NEAREST)
        imgtk = ImageTk.PhotoImage(img)
        imglabel.configure(image=imgtk)
        imglabel.image = imgtk


def main(image_name):
    # Konfiguracja Okienka w Tkinterze
    imgx = Image.open(image_name)                               # Otwieramy obrazek ze zrodla
    imgn = ImageOps.fit(imgx, (500, 500), Image.ANTIALIAS)      # ImageOps to gotowy modul do przetwarzania obrazow, ANTIALIAS - high quality filter Based On Convolutions
    imgtk = ImageTk.PhotoImage(imgn)                            # ImageTk.PhotoImage tworzy nowy obiekt Photo Image
    imglabel.configure(image=imgtk)
    imglabel.image = imgtk
    imglabel.grid(column=1, row=3, columnspan=4, padx=0)
    imgx = imgx.convert('RGB')
    result = Szukacz(image_name)                                            # uruchamiamy funkcje solve dla wygenerowanego obrazka
    t1 = threading.Thread(target=Gradient, args=(imgx, result,))            # Glowny watek programu
    t1.start()                                                              # target is the callable object to be invoked by the run() method.
                                                                            # args is the argument tuple for the target invocation

#Petla Programu
r.mainloop()
