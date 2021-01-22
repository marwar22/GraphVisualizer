# Projekt GraphVisualizer

[![Project Status: Active – The project has reached a stable, usable state and is being actively developed.](http://www.repostatus.org/badges/latest/active.svg)](http://www.repostatus.org/#active) [![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0) [![Lines of Code](https://tokei.rs/b1/github/marwar22/GraphVisualizer)](https://github.com/marwar22/GraphVisualizer) [![GitHub contributors](https://img.shields.io/github/contributors/marwar22/GraphVisualizer)](https://GitHub.com/marwar22/GraphVisualizer/graphs/contributors/) [![Open Source Love svg1](https://badges.frapsoft.com/os/v1/open-source.svg?v=103)](https://github.com/ellerbrock/open-source-badges/)

<img alt="C++" src="https://img.shields.io/badge/c++%20-%2300599C.svg?&style=for-the-badge&logo=c%2B%2B&ogoColor=white"/>


## Wstęp
Program oferuje możliwość tworzenia, edycji, wczytywania oraz zapisu grafu. Pozwala na wizualizację krok po kroku działania szeregu algorytmów takich jak DFS, BFS, algorytm Dijkstry, wyświetlanie wierzchołków w kolejności postorder, podział grafu na silnie spójne składowe. Rozbudowany silnik fizyczny umożliwia w zautomatyzowany sposób estetycznie rozmieścić wierzchołki i krawędzie w polu edycji grafu. Zapis oraz odczyt do pliku pozwalają na kontynuację pracy nawet po przerwaniu wykonywania programu. Zmiany kolorów zarówno wierzchołków jak i krawędzi podczas wykonywania kolejnych kroków algorytmów pozwalają na przejrzystą obserwację sposobu działania algorytmu. Interaktywne poruszanie się po liście kroków algorytmu, ze szczególnym uzwględnieniem w pełni działającej możliwości cofania tych dotychczasowo wykonanych, pozwala na dogłębną analizę i pełne zrozumienie podstaw algorytmiki. Program może być świetnym dopełnieniem klasycznej formy nauczania algorytmów, w szczególności dla zawodników oraz potencjalnych zawodników Olimpiady Informatycznej, Olimpiady Informatycznej Juniorów oraz innych osób zaczynających swoją przygodę w świecie algorytmiki konkursowej. 


## Instalacja niezbędnych zależności
Zalecane jest uruchomienie programu na systemach z rodziny Linux. Pozwala on na łatwą instalację potrzebnych pakietów:

* `libsfml-dev`
* `build-essential`

#### Instalacja pakietów dla Debian/Ubuntu:
`sudo apt-get install libsfml-dev`
`sudo apt-get install build-essential`

## Uruchomienie programu
Dzięki utworzonemu plikowi `makefile` kompilacja jest prosta i intuicyjna. Polega na wejściu w lokalizację pobranego repozytorium oraz wpisaniu polecenia:
`make`
Powstanie wtedy plik wykonywalny `GraphVisualizer`, który należy wykonać poleceniem
`./GraphVisualizer`

Jednak w przypadku, gdy powyższy sposób okaże się nieskuteczny, przewidziana jest również druga, zastępcza metoda kompilacji i uruchomienia. Po wejściu do katalogu repozytorium w terminalu należy wpisać:
`g++ -c src/*.cpp src/algorithms/*.cpp src/graphics/*.cpp`
`g++ *.o -o GraphVisualizer -lsfml-graphics -lsfml-window -lsfml-system`

Ponadto powyższa metoda pozwala na dodanie flagi kompilacji `-DDEBUG`, która umożliwia ułatwioną analizę stanu grafu, tj. informacje dotyczące wierzchołków i krawędzi.

## Wykorzystane narzędzia
`C++ 17`
`SFML 2.5.1`

## Zaimplementowane algorytmy
Użytkownikowi końcowemu udostępniamy do dyspozycji kilka wartościowych dydaktycznie algorytmów. Są to: 
* BFS
* DFS
* sprawdzenie dwudzielności grafu
* algorytm Dijkstry
* algorytm Prim'a (wyznaczanie najmniejszego drzewa rozpinającego)
* algorytm numerujący wierzchołki w kolejności DFS-postorder
* algorytm podziału na silnie spójne składowe (SCC)
* zagadkowy algorytm "Kolory"

## Instrukcja użytkowania
Aby użytkownik końcowy mógł w pełni korzystać z możliwości prezentowanego programu poniżej przedstawiamy wskazówki dotyczące jego użytkowania.

### Odczyt grafu z pliku
Zapisane projekty korzystają z własnego rozrzerzenia `*.gv`. Aby odczytać własne, jak i uprzednio dodane przez autorów przykładowe grafy, należy kliknąć przycisk "Odczyt z pliku", a następnie w polu które pojawi się na środku ekranu należy wpisać nazwę pliku, który chcemy odczytać (w przypadku pominięcia rozszerzenia zostanie ono zostanie dodane automatyczne) i zakończyć operację wciśnięciem `Enter`.

### Zapis grafu do pliku
Podobnie w przypadku chęci zapisania grafu  - należy kliknąć przycisk "Zapis do pliku", oraz wpisać jego nazwę. Należy pamiętać, aby przypadkowo nie nadpisać uprzednio zapisanego pliku o tej samej nazwie. Podobnie, na koniec należy wcisnąć przycisk `Enter`. Projekty są odczytywane jak i zapisywane w dedykowanym do tego folderze `savedGraphs`, który jest podkatalogiem projektu.

## Struktura projektu
```.
├── README.md
├── makefile
└── src
    └── algorithms
    |     ├── algorithms.hpp
    |     ├── bfs.cpp
    |     ├── bipartial.cpp
    |     ├── colors.cpp
    |     ├── dfs.cpp
    |     ├── dijkstra.cpp    
    |     ├── mst.cpp
    |     ├── postorder.cpp
    |     └── scc.cpp
    └── graphics
    |     ├── button.cpp
    |     ├── button.hpp
    |     ├── textbox.cpp
    |     └── textbox.hpp
    ├── app.cpp
    ├── app.hpp
    ├── edge.cpp
    ├── edge.hpp
    ├── events.cpp
    ├── filehandle.cpp
    ├── filehandle.hpp
    ├── graph.cpp
    ├── graph.hpp
    ├── main.cpp
    ├── utils.cpp
    ├── utils.hpp
    ├── vertex.cpp
    └── vertex.hpp
```


## Autorzy
Mikołaj Jaszcza
Michał Kierul
Marcin Wróbel
Marcin Sarnecki
