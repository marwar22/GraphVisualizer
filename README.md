# Graph Visualizer 1.3.0

[![Project Status: Active – The project has reached a stable, usable state and is being actively developed.](http://www.repostatus.org/badges/latest/active.svg)](http://www.repostatus.org/#active) [![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0) [![Lines of Code](https://tokei.rs/b1/github/marwar22/GraphVisualizer)](https://github.com/marwar22/GraphVisualizer) [![GitHub contributors](https://img.shields.io/github/contributors/marwar22/GraphVisualizer)](https://GitHub.com/marwar22/GraphVisualizer/graphs/contributors/) [![Open Source Love svg1](https://badges.frapsoft.com/os/v1/open-source.svg?v=103)](https://github.com/ellerbrock/open-source-badges/)

<img alt="C++" src="https://img.shields.io/badge/c++%20-%2300599C.svg?&style=for-the-badge&logo=c%2B%2B&ogoColor=white"/>


## Wstęp
Program oferuje możliwość tworzenia, edycji, wczytywania oraz zapisu grafu. Pozwala na wizualizację krok po kroku działania szeregu algorytmów takich jak DFS, BFS, algorytm Dijkstry, wyznaczanie kolejności wierzchołków postorder, podział grafu na silnie spójne składowe i inne. Rozbudowany silnik fizyczny pomaga w zautomatyzowany sposób estetycznie rozmieścić wierzchołki i krawędzie w polu edycji grafu. Zapis oraz odczyt do pliku pozwalają na kontynuację pracy nawet po przerwaniu wykonywania programu. Zmiany kolorów zarówno wierzchołków jak i krawędzi podczas wykonywania kolejnych kroków algorytmów pozwalają na przejrzystą obserwację sposobu działania algorytmu. Interaktywne poruszanie się po liście kroków algorytmu, ze szczególnym uzwględnieniem w pełni działającej możliwości cofania tych dotychczasowo wykonanych, pozwala na dogłębną analizę i pełne zrozumienie podstaw algorytmiki. Program może być świetnym dopełnieniem klasycznej formy nauczania algorytmów, w szczególności dla zawodników oraz potencjalnych zawodników Olimpiady Informatycznej, Olimpiady Informatycznej Juniorów oraz innych osób zaczynających swoją przygodę w świecie algorytmiki konkursowej. 

## Wykorzystane narzędzia
`C++ 17`
`SFML 2.5.1` - najwyższa wspierana wersja biblioteki SFML,
Zapewniane wsparcie dla wersji starszych, takich jak `2.4.2` czy `2.3.2` jest ograniczone, przykładowo nie jest możliwa obsługa technologii antyaliasing'u (ang. anti-aliasing). Ponadto dla wersji `2.5.1` automatycznie dobierany jest odpowiedni współczynnik próbkowania (ang. sampling level.). Autorzy pragną zaznaczyć, że instalowana domyślnie wersja biblioteki SFML może zależeć od wersji systemu operacyjnego użytkownika.

## Instalacja niezbędnych zależności
Zalecane jest uruchomienie programu na systemach z rodziny Linux, jednak użytkownicy systemu Windows 10 również mogą korzystać z programu (szczegóły w temacie "Uruchomienie w systemie Windows 10"). Pozwala on na łatwą instalację potrzebnych pakietów.

Dla rodziny Debian/Ubuntu:
* `libsfml-dev`
* `build-essential`

Dla rodziny Arch Linux:
*  `base-devel`
*  `sfml`

### Instalacja pakietów dla Linux:
#### Debian/Ubuntu:
* `sudo apt-get update`
* `sudo apt-get install libsfml-dev`
* `sudo apt-get install build-essential`

#### Arch Linux:
* `sudo pacman -S base-devel`
* `sudo pacman -S sfml`


## Uruchomienie programu
Dzięki utworzonemu plikowi `makefile` kompilacja jest prosta i intuicyjna. Polega na wejściu w lokalizację pobranego repozytorium oraz wpisaniu polecenia:
`make`
Powstanie wtedy plik wykonywalny `GraphVisualizer`, który należy wykonać poleceniem
`./GraphVisualizer`

Jednak w przypadku, gdy powyższy sposób okaże się nieskuteczny, przewidziana jest również druga, zastępcza metoda kompilacji i uruchomienia. Po wejściu do katalogu repozytorium w terminalu należy wpisać:
* `g++ -c src/*.cpp src/algorithms/*.cpp src/graphics/*.cpp -std=c++17`
* `g++ *.o -o GraphVisualizer -lsfml-graphics -lsfml-window -lsfml-system`

Ponadto powyższa metoda pozwala na dodanie flagi kompilacji `-DDEBUG`, która umożliwia ułatwioną analizę stanu grafu, tj. informacje dotyczące wierzchołków i krawędzi.

## Uruchomienie w systemie Windows 10
Autorzy przygotowali również wersję "Windows 10 Release" dla systemu Windows 10. Jedynym jej ograniczeniem jest brak wsparcia dla polskich znaków. Uruchomienie na systemie Windows 10 następuje po kliknięciu pliku wykonywalnego "GraphVisualizer.exe" w rozpakowanym archiwum pobranym z GitHuba - sekcja "Release". Obecna wersja release odpowiada wersji 1.3.0 programu. Należy wspomnieć, że może wystąpić potrzeba zezwolenia na wykonanie pliku w aplikacji Windows Defender (oraz innych programach antywirusowych).

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

### Edycja grafu
#### Dodawanie wierzchołka
Aby dodać wierzchołek należy nacisnąć przycisk "Dodaj wierzchołek", a następnie kliknąć w dowolne miejsce w polu edycji grafu - tam, gdzie chcemy by pojawił się nowy wierzchołek.

#### Usunięcie wierzchołka
Aby usunąć wierzchołek należy nacisnąć przycisk "Usuń wierzchołek", a następnie kliknąć w wierzchołek, który chcemy usunąć. Uwaga - przy usunięciu wierzchołka usunięte zostaną również wszystkie krawędzie do niego wchodzące i z niego wychodzące.

#### Przesunięcie wierzchołka
Aby usunąć wierzchołek należy nacisnąć przycisk "Przesuń wierzchołek", a następnie przytrzymać wierzchołek i upuścić go w docelowym miejscu.

#### Dodawanie krawędzi
Aby dodać krawędź należy kliknąć "Dodaj krawędź", a następnie kliknąć kolejno 2 wierzchołki. Krawędź zostanie utworzona od pierwszego do drugiego. Kolejność wyboru jest istotna jeżeli chcemy, by nasz graf był skierowany. Twórcy zapewnili wsparcie dla krawędzi wielokrotnych oraz tzw. "pętli" (ang. self-loops).

#### Usuwanie krawędzi
Aby usunąć krawędź należy kliknąć "Usuń krawędź". Na środkach krawędzi pojawią się pomocnicze okrągłe pola - aby usunąć wybraną krawędź należy kliknąć na pole w jej centrum.

#### Edycja krawędzi
Chcąc zmienić wagę krawędzi należy kliknąć "Edycja krawędzi", a następnie kliknąć odpowiednie pole analogicznie do procesu usuwania krawędzi. Następnie należy wpisać wagę krawędzi i zakończyć wciśnięciem "Enter"

#### Automatyczne rozmieszczenie grafu
W celu skorzystania z automatycznego rozmieszczenia wierzchołków i krawędzi, używającego zaawansowanego silnika fizycznego, w głównym obszarze roboczym należy kliknąć "Symulacja sił". Analogiczne działanie należy podjąć w celu wyłączenia sił działających na graf.

#### Odczyt grafu z pliku
Zapisane przez program pliki korzystają z własnego rozrzerzenia `*.gv`. Aby odczytać własne, jak i uprzednio dodane przez autorów przykładowe grafy, należy kliknąć przycisk "Odczyt z pliku", a następnie w polu które pojawi się na środku ekranu należy wpisać nazwę pliku, który chcemy odczytać (w przypadku pominięcia rozszerzenia zostanie ono dodane automatyczne) i zakończyć operację wciśnięciem `Enter`.

#### Zapis grafu do pliku
Podobnie w przypadku chęci zapisania grafu  - należy kliknąć przycisk "Zapis do pliku", oraz wpisać jego nazwę. Należy pamiętać, aby przypadkowo nie nadpisać uprzednio zapisanego pliku o tej samej nazwie. Podobnie, na koniec należy wcisnąć przycisk `Enter`. Projekty są odczytywane jak i zapisywane w dedykowanym do tego folderze `savedGraphs`, który jest podkatalogiem projektu. Lista stworzonych plików przykładowych dostępna jest w części "Struktura projektu" tego dokumentu, podkatalog: `savedGraphs`. 

#### Skierowanie grafu
Aby zmienić graf nieskierowany w skierowany bądź wykonać operację przeciwną, należy kliknąć przycisk "Graf skierowany". Należy pamiętać, że nawet jeśli do pewnych algorytmów (takich jak algorytm Prima) przekażemy graf skierowany, graf automatycznie zostanie na czas trwania wizualizacji algorytmu przekonwertowany na swój nieskierowany odpowiednik. Analogicznie skierowanie zostanie włączone dla algorytmu znajdowania silnie spójnych składowych.

### Wizualizacje algorytmów
Aby przejść do panelu wyboru algorytmów, należy kliknąć przycisk "Wybierz algorytm". Następnie, po kliknięciu przycisku powiązanego z wybranym algorytmem, użytkownik zostaje przeniesiony do nowego panelu. W przypadku  wyboru "Powrót" użytkownik zostanie z powrotem przeniesiony do panelu edycji grafu.

Wszystkie algorytmy, poza algorytmami "Kolory" i "SCC" wymagają wyboru wierzchołka początkowego. W tym celu należy kliknąć w wybrany wierzchołek. 

Następnie użytkownik znajduje się w polu docelowym - w polu wizualizacji wybranego algorytmu. Do jego dyspozycji oddajemy zarówno możliwość ręcznej nawigacji w przód i tył po liście kroków algorytmu (za pomocą przycisków "->" i "<-"), oraz wersję zautomatuzowaną - przyciski "<" i ">" rozpoczynające automatyczne wykonywanie kroków wykonywaych odpowiednio wstecz bądź naprzód.  Działanie przycisku "||" odpowiada poleceniu `pause`. Ponadto przyciski "-" i "+" pozwalają zmniejszyć i zwiększyć prędkość prezentacji kroków algorytmów. Pole tekstowe po prawej stronie informuje o aktualnej prędkości odtwarzania.

## Struktura projektu
```.
├── README.md
├── makefile
├── RUNME.exe
└── savedGraphs
|     ├── bipartial1.gv
|     ├── bipartial2.gv
|     ├── clique7.gv
|     ├── cycle1.gv
|     ├── cycle2.gv
|     ├── Dij_dir_example1.gv
|     ├── Dij_dir_example2.gv
|     ├── Dij_undir_example1.gv
|     ├── Dij_undir_example2.gv
|     ├── duzo.gv
|     ├── MST_example1.gv
|     ├── MST_example2.gv
|     ├── niespojny.gv
|     ├── path1.gv
|     ├── path2.gv
|     ├── SCC_example1.gv
|     ├── SCC_example2.gv
|     ├── tree1.gv
|     ├── tree2.gv
|     └── tree3.gv
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
    |
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
## Wersja
Obecna wersja programu: 1.3.0

## Autorzy
Mikołaj Jaszcza | Michał Kierul | Marcin Wróbel | Marcin Sarnecki