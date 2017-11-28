// Rekurencyjne DFS - macierz incydencji
// Data: 22.07.2013
// (C)2013 mgr Jerzy Wa³aszek
//--------------------------------------

#include <iostream>
#include <iomanip>

using namespace std;

// Zmienne globalne

int n,m;                 // Liczba wierzcho³ków
signed char ** A;        // Macierz incydencji
bool * visited;          // Tablica odwiedzin

// Rekurencyjna procedura przejœcia w g³¹b
//----------------------------------------
void DFS(int v)
{
  int i,j;

  visited[v] = true;     // Zaznaczamy wêze³ jako odwiedzony
  cout << setw(3) << v;  // Przetwarzamy wêze³ (wypisujemy jego numer)

// Rekurencyjnie odwiedzamy nieodwiedzonych s¹siadów

  for(i = 0; i < m; i++)
    if(A[v][i] == 1)
      for(j = 0; j < n; j++)
        if(A[j][i] == -1)
        {
          if(!visited[j]) DFS(j);
          break;
        }
}

// **********************
// *** PROGRAM G£ÓWNY ***
// **********************

int main()
{
  int i,j,v1,v2;

  cin >> n >> m;               // Czytamy liczbê wierzcho³ków i krawêdzi

  A = new signed char * [n];   // Tworzymy tablicê wskaŸników
  visited = new bool[n];       // Tworzymy tablicê odwiedzin

  for(i = 0; i < n; i++)
    A[i] = new signed char[m]; // Tworzymy wiersze

  // Macierz wype³niamy zerami

  for(i = 0; i < n; i++)
  {
    visited[i] = false;        // Zerujemy tablicê odwiedzin
    for(j = 0; j < m; j++) A[i][j] = 0;
  }

  // Odczytujemy kolejne definicje krawêdzi

  for(i = 0; i < m; i++)
  {
    cin >> v1 >> v2;    // Wierzcho³ek startowy i koñcowy krawêdzi
    A[v1][i] = 1;       // Wierzcho³ek startowy
    A[v2][i] = -1;      // Wierzcho³ek koñcowy
  }

  cout << endl;

  // Przechodzimy graf w g³¹b

  DFS(0);

  // Usuwamy macierz

  for(i = 0; i < n; i++) delete A[i];
  delete [] A;
  delete [] visited;

  cout << endl;

  return 0;
}
