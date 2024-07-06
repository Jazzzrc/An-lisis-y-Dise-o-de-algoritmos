#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <cstdint>

using namespace std;
using namespace std::chrono;


int fibonacci(int n)
{
  if (n <= 1 || n == 2)
  {
    return n;
  }
  else {
    return fibonacci(n-1) + fibonacci(n-2);
  }
}

int main()
{

  auto start = high_resolution_clock::now();
  int numero;
  cout<<"CANTIDAD DE NUMEROS A CALCULAR: ";
  cin>>numero;

  for(int i=1;i<=numero;i++)
  {
    cout<<fibonacci(i)<<"   ";
  }

  auto stop = high_resolution_clock::now();


  auto duration = duration_cast<microseconds>(stop-start);

  cout <<"\nTiempo ejecucion: " <<duration.count() <<" microsegundos" <<endl;

  cout <<endl;

  return 0;
}
