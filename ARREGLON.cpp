#include <iostream>
using namespace std;

int main() {
    int N;
    cout << "Ingrese la cantidad de elementos: ";
    cin >> N;

    int A[N];

    for(int i = 0; i < N; i++){
        cout << "Elemento " << i+1 << ": ";
        cin >> A[i];
    }

    int mayor = A[0];
    int segundo = A[0];

    for(int i = 1; i < N; i++){
        if(A[i] > mayor){
            segundo = mayor;
            mayor = A[i];
        }
        else if(A[i] > segundo && A[i] != mayor){
            segundo = A[i];
        }
    }

    cout << "El segundo valor mas alto es: " << segundo;

    return 0;
}
