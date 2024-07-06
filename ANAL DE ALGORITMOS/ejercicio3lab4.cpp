#include <iostream>

using namespace std;


void moverTorre(int numeroDiscos, int torreOrigen, int torreDestino, int torreAuxiliar){

  if(numeroDiscos == 1){

    cout<<"Mover disco de la torre "<< torreOrigen << " a la torre " << torreDestino <<endl;
    return;
  }

  moverTorre(numeroDiscos - 1, torreOrigen, torreAuxiliar, torreDestino);

  cout<<"Mover disco de la torre " <<torreOrigen<<" a la torre " <<torreDestino<<endl;

  moverTorre(numeroDiscos - 1, torreAuxiliar, torreDestino, torreOrigen);


}
int main(){

  int numeroDiscos,
      torreOrigen   = 1,
      torreAuxiliar = 2,
      torreDestino  = 3;

  cout<<"Ingrese cantidad de discos: ";
  cin>>numeroDiscos;

  cout<<"\n************************************************\n"<<endl;



  moverTorre(numeroDiscos, torreOrigen, torreDestino, torreAuxiliar);

  return 0;

}
