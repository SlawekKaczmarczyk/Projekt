// Wyszukiwanie cyklu lub �cie�ki Eulera
// Algorytm Fleury'ego
// Data: 8.02.2014
// (C)2014 mgr Jerzy Wa�aszek
//---------------------------

#include <iostream>
#include <iomanip>

using namespace std;

// Zmienne globalne

int n,m,cv,sptr;
char **A;                       // Macierz s�siedztwa
int *S;                         // Stos w tablicy
int *D;                         // Tablica numer�w wierzcho�k�w

// Funkcja wyszukuj�ca mosty w grafie
// We:
// v  - numer wierzcho�ka startowego
// vf - ojciec wierzcho�ka v na drzewie rozpinaj�cym
// Wy:
// Parametr Low dla wierzcho�ka v
//---------------------------------------------------
int DFSb(int v,int vf)
{
  int Low,temp,i;

  D[v] = cv;                    // Numerujemy wierzcho�ek
  Low  = cv;                    // Wst�pna warto�� Low
  cv++;                         // Numer dla nast�pnego wierzcho�ka
  for(i = 0; i < n; i++)        // Przegl�damy s�siad�w v
    if(A[v][i] && (i != vf))
    {
      if(!D[i])                 // Je�li s�siad nieodwiedzony, to
      {
        temp = DFSb(i,v);       // to wywo�ujemy rekurencyjnie DFSb()
        if(temp < Low) Low = temp; // Modyfikujemy Low
      }
      else if(D[i] < Low) Low = D[i];
    }

  if((vf > -1) && (Low == D[v])) // Mamy most?
    A[vf][v] = A[v][vf] = 2;    // Oznaczamy kraw�d� vf-v jako most

  return Low;
}

// Procedura wyszukuje cykl lub �cie�k� Eulera
// We:
// v - wierzcho�ek startowy
//--------------------------------------------
void findEuler(int v)
{
  int u,w,i;

  while(true)                   // W p�tli przetwarzamy graf
  {
    S[sptr++] = v;              // v umieszczamy na stosie

    for(u = 0;(u < n) && !A[v][u];u++); // Szukamy pierwszego s�siada v

    if(u == n) break;           // Nie ma s�siad�w, ko�czymy

    for(i = 0; i < n; i++) D[i] = 0; // Zerujemy tablic� D

    cv = 1;                     // Numer pierwszego wierzcho�ka dla DFS
    DFSb(v,-1);                 // Identyfikujemy kraw�dzie-mosty

    // Szukamy kraw�dzi nie b�d�cej mostem

    for(w = u + 1;(A[v][u] == 2) && (w < n); w++)
      if(A[v][w]) u = w;

    A[v][u] = A[u][v] = 0;      // Usuwamy kraw�d� v-u
    v = u;                      // Przechodzimy do u
  }
}

// **********************
// *** Program g��wny ***
// **********************

int main()
{
  int i,j,v1,v2;
  int *VD;                      // Stopnie wierzcho�k�w

  cin >> n >> m;                // Czytamy liczb� wierzcho�k�w i kraw�dzi

  A = new char * [n];           // Tworzymy tablic� wska�nik�w
  for(i = 0; i < n; i++)
    A[i] = new char [n];        // Tworzymy wiersze macierzy s�siedztwa

  // Macierz wype�niamy zerami

  for(i = 0; i < n; i++)
    for(j = 0; j < n; j++) A[i][j] = 0;

  VD = new int [n];             // Tworzymy tablic� stopni
  for(i = 0; i < n; i++)        // Zerujemy tablic� stopni
    VD[i] = 0;

  D = new int [n];              // Tworzymy tablic� numer�w

  S = new int [m + 1];          // Tworzymy pusty stos
  sptr = 0;

  // Odczytujemy kolejne definicje kraw�dzi

  for(i = 0; i < m; i++)
  {
    cin >> v1 >> v2;    // Wierzcho�ek startowy i ko�cowy kraw�dzi
    A[v1][v2] = 1;      // Kraw�d� v1->v2 obecna
    A[v2][v1] = 1;      // Kraw�d� v2->v1 obecna
    VD[v1]++;
    VD[v2]++;           // Obliczamy stopnie v1 i v2
  }

  cout << endl;

  // Szukamy pozycji startowej v1

  for(v1 = 0; v1 < n; v1++)
    if(VD[v1]) break;

  for(i = v1; i < n; i++)
    if(VD[i] % 2)
    {
      v1 = i;
      break;
    }

  // Wyznaczamy cykl lub �cie�k� Eulera

  findEuler(v1);

  // Wypisujemy zawarto�� stosu

  if(VD[v1] % 2) cout << "EULERIAN PATH :"; else cout << "EULERIAN CYCLE :";

  for(i = 0; i < sptr; i++) cout << setw(3) << S[i];
  cout << endl;

 //To zmieni�em

  for(i = 0; i < n; i++) delete [] A[i];
  delete [] A;
  delete [] S;
  delete [] D;
  delete [] VD;

  return 0;
} 
