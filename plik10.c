// Rekurencyjne DFS - macierz incydencji
// Data: 22.07.2013
// (C)2013 mgr Jerzy Wa�aszek
//--------------------------------------

#include <iostream>
#include <iomanip>

using namespace std;

// Zmienne globalne

int n,m;                 // Liczba wierzcho�k�w
signed char ** A;        // Macierz incydencji
bool * visited;          // Tablica odwiedzin

// Rekurencyjna procedura przej�cia w g��b
//----------------------------------------
void DFS(int v)
{
  int i,j;

  visited[v] = true;     // Zaznaczamy w�ze� jako odwiedzony
  cout << setw(3) << v;  // Przetwarzamy w�ze� (wypisujemy jego numer)

// Rekurencyjnie odwiedzamy nieodwiedzonych s�siad�w

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
// *** PROGRAM G��WNY ***
// **********************

int main()
{
  int i,j,v1,v2;

  cin >> n >> m;               // Czytamy liczb� wierzcho�k�w i kraw�dzi

  A = new signed char * [n];   // Tworzymy tablic� wska�nik�w
  visited = new bool[n];       // Tworzymy tablic� odwiedzin

  for(i = 0; i < n; i++)
    A[i] = new signed char[m]; // Tworzymy wiersze

  // Macierz wype�niamy zerami

  for(i = 0; i < n; i++)
  {
    visited[i] = false;        // Zerujemy tablic� odwiedzin
    for(j = 0; j < m; j++) A[i][j] = 0;
  }

  // Odczytujemy kolejne definicje kraw�dzi

  for(i = 0; i < m; i++)
  {
    cin >> v1 >> v2;    // Wierzcho�ek startowy i ko�cowy kraw�dzi
    A[v1][i] = 1;       // Wierzcho�ek startowy
    A[v2][i] = -1;      // Wierzcho�ek ko�cowy
  }

  cout << endl;

  // Przechodzimy graf w g��b

  DFS(0);

  // Usuwamy macierz

  for(i = 0; i < n; i++) delete A[i];
  delete [] A;
  delete [] visited;

  cout << endl;

  return 0;
}
