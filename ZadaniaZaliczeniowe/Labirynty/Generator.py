import random
import png

# Funkcja generujaca labirynt dla (wysokosc, szerokosc)
# Uproszczony generator na potrzeby programu

# Metoda pop.random - uproszczona implementacja dla losowego wyboru parametru pop.
# Funkcja uproszczona na potrzeby programu.
# W zeszycie opisujacym szczegoly stosowania drzew losowych sa ladne funkcje implementujace
# Tworzenie Labiryntow.

def Labirynt(wysokosc, szerokosc):
  points = [(i,j) for i in range(1,wysokosc-1) for j in range(1,szerokosc-1) if i%2 and j%2]   # punkty (x,y) macierzy
  matrix = [[0 for i in range(szerokosc)]for i in range(wysokosc)]                             # Zerujemy macierz
  i, j = random.choice(points)                                                                 # Losowy wybor punktow z listy
  points.remove((i, j))                                                                        #Usuwamy losowo wybrane punkty z listy
  tree = []                                                                                    # Lista uzytych juz wezlow ( Tworzacych Drzewo Labiryntu )
  while 1:
    matrix[i][j] = 1
    l = [(i+1, j, i+2, j), (i-1, j, i-2, j), (i, j+1, i, j+2), (i, j-1, i, j-2)]               # 4 mozliwosci dla parametru pop
    for x, y, i, j in [l.pop(random.randint(0,3-i)) for i in range(4)]:
      if (i, j) in points:
        points.remove((i, j))
        break
    else:
      i, j = tree.pop(random.randint(0, len(tree)-1))                             # zdejmujemy z drzewa
      if not tree:
        break
      continue
    tree.append((i, j))                                                          # Dodajemy krawedz do drzewa labiryntu
    matrix[x][y] = 1
  matrix[0][1] = 1                         # start
  matrix[szerokosc-1][szerokosc-2] = 1     # finisz
  obrazek = []                                 # Lista pikseli obrazka
  for values in matrix:                    # Z macierzy Labiryntu Tworzymy Obrazek
    row = []
    for value in values:                   #
      row.extend([value])                  #
    obrazek.extend([row])                      # Tworzymy obrazek z pikseli (kwadratow)
  with open('Zdjecie_Labiryntu.png', 'wb') as file:
    w = png.Writer(len(obrazek[0]), len(obrazek), bitdepth=1)
    w.write(file, obrazek)



Labirynt(21, 21)

