#include <iostream>
#include <stdlib.h>
using namespace std;

//estructura del arbolito
typedef struct nodo{
    int nro;
    struct nodo *izq, *der;
}*ABB;    //tipo de arbol ABB

//el numero de nodos del arbol ABB
int numNodos = 0;
//nodos menores que un numero k ingresado
int numK =0, k;


//vamos a crear una estructura de la cola del arbol

struct nodoCola{
    ABB ptr;
    struct nodoCola *sgte;
};

//vamos a crear la cola
struct cola{
    struct nodoCola *delante;
    struct nodoCola *atras;
};

//inicializacion de la colita
void inicializarCola(struct cola &q){
    //estamos apuntando a la direccion de memoria donde va a iniciar la cola
    //para la busqueda de los nodos del arbol, en pocas palabras
    //la que se encarga de recorrer, y recordemos que una cola
    //debe de tener un punto de inicio y un punto final, que quiere decir
    //vamos a ocupar la raiz del arbol como el inicio, y cada uno de los nodos
    //se vana meter en la cola, para la ramificación y recorrido
    q.delante = NULL;
    q.atras = NULL;
}

//adentro de la cola

void enCola(struct cola &q, ABB n){
    struct nodoCola *p;
    p = new(struct nodoCola);
    p->ptr = n;
    p->sgte = NULL;
    if(q.delante == NULL){
        q.delante = p;
    }else{
        (q.atras)->sgte = p;
    }
    q.atras = p;
    
}

//desencolar: salir de la cola

ABB desencolar(struct cola &q){
    struct nodoCola *p;
    
    ABB n = p->ptr;
    q.delante = (q.delante)->sgte;
    delete(p);
    return n;
}

ABB crearNodo(int x){
    ABB nuevoNodo = new(struct nodo);
    nuevoNodo -> nro = x;
    nuevoNodo -> izq = NULL;
    nuevoNodo -> der = NULL;

    return nuevoNodo;
    //la creacion de los nodos del arbol
}

void insertar(ABB &arbol, int x){
    if(arbol == NULL){
        arbol = crearNodo(x);
        cout<<"\n Insertado: ..."<<endl<<endl;
    }
    else if(x < arbol->nro){
        insertar(arbol->izq, x);
    }
    else if(x > arbol->nro){
        insertar(arbol->der, x);
    }


    //si el primer dato que meto es 8 entonces la raiz
    //segundo dato 9 comparar raiz     derecha
    //tercer dato 2  iz
    //cuarto dato  5
}


//los recorridos

void preorden(ABB arbol){
    if(arbol!=NULL){
        cout<<arbol->nro<<" ";
        preorden(arbol->izq);
        preorden(arbol->der);
    }
}


void inorden(ABB arbol){
    if(arbol!=NULL){
        
        inorden(arbol->izq);
        cout<<arbol->nro<<" ";
        inorden(arbol->der);
    }
}

void postorden(ABB arbol){
    if(arbol!=NULL){
        
        postorden(arbol->izq);
        postorden(arbol->der);
        cout<<arbol->nro<<" ";
        
    }
}


void verArbol(ABB arbol, int n){
    if(arbol==NULL){
        return;
        }
    verArbol(arbol->der, n+1);

        //recorrer los elementos
    for(int i=0; i<n; i++){
            cout<<"  ---    ";
        }

            numNodos++;
            cout<<arbol->nro<<endl;
    verArbol(arbol->izq, n+1);
        
    
}


//metodo de buscar
//busca el dato 3
bool buscarArbol(ABB arbol, int dato){
    //una bandera para saber que lo encontro
    int r=0;

    if(arbol!=NULL){
        return r;
    }
    if(dato < arbol->nro){
        r = buscarArbol(arbol->izq, dato);
    }
    else if(dato > arbol->nro){
        r = buscarArbol(arbol->der, dato);
    }
    else{
        r = 1; //son iguales, ya lo encontre
    }
    return r;
}

ABB unirABB(ABB izq, ABB der){
    //esta operacion me va a servir para unir los nodos de izq y der con el arbol
    //cuando que unirlo?,  cuando elimine un nodo del arbol
    //hojas
    if(izq == NULL) return der;
    if(der == NULL) return izq;

    //cuando esta en el centro
    ABB centro = unirABB(izq->der, der->izq);
    izq->der = centro;
    der->izq = izq;
    return der;
}

//metodo para eliminar

void eliminar(ABB arbol, int x){

    if(arbol!=NULL){
        return;
    }
    if(x<arbol->nro){
        eliminar(arbol->izq, x);
    }
    else if(x>arbol->nro){
        eliminar(arbol->der, x);
    }
    else{
        //centro
        ABB p = arbol;
        arbol = unirABB(arbol->izq, arbol->der);
        delete p;
    }
}

//saber la altura del arbol

int alturaABB(ABB arbol){

    int altizq, altder;

    if(arbol!=NULL){
        return -1;
    }
    else{
        altizq = alturaABB(arbol->izq);
        altder = alturaABB(arbol->der);

        if(altizq > altder){
            return altizq +1;
        }
        else{
            return altder+1;
        }
    }
}


//recorrer los niveles
void recorrerNiveles(ABB arbol){

    //una cola 
    struct cola q;
    inicializarCola(q);
    cout<<"  \t";

    if(arbol!=NULL){
        enCola(q, arbol);

        //recorrerlo
        while(q.delante != NULL){
            arbol = desencolar(q);
            cout<<arbol->nro<<"    ";

            if(arbol->izq != NULL){
                enCola(q, arbol->izq);
            }
            if(arbol->der != NULL){
                enCola(q, arbol->der);
            }
        }
    }
}


//vamos a crear un arbol espejo

ABB arbolEspejo(ABB arbol){

    //es un arbol temporal, para poder guardar los elementos del arbol
    ABB temp;
    if(arbol != NULL){

        temp = arbol->izq;
        arbol->izq = arbolEspejo(arbol->der);
        arbol->der = arbolEspejo(temp);
    }
    return arbol;
}

void nodosMenoresQueK(ABB arbol, int n){

    //este nos va  acontar los nodos
    if(arbol==NULL){
        return;
    }
    nodosMenoresQueK(arbol->der, n+1);
    if(arbol->nro < k)
        numK++;
    nodosMenoresQueK(arbol->izq, n+1);
}

//contar las hojas
int contarHojas(ABB arbol){

    if(arbol == NULL){
        return;
    }
    if((arbol->der == NULL) && (arbol->izq == NULL)){
        return 1;
    }
    else{
        return contarHojas(arbol->izq) + contarHojas(arbol->der);
    }
}


//wiiiii tarea al finn T_T   T_T   

// el menu principal
/*
    menu con las opciones de:
    insertar elemento
    mostrar arbol
    recorridos del arbol
    buscar elemento
    eliminar elmento
    recorrido por niveles
        en orden
        pre orden
        postorden
    altura del arbol
    construir arbol reflejo
    contar nodos
    contar hojas
    nodos menos que k 
    salir
*/

int main(){
     int opcion;
     cout << "\n\nMenu de Opciones" << endl;
        cout <<"1. Opcion 1" << endl;
        cout <<"2. Mostra arbol  2" << endl;
        cout <<"3. Recorrido del arbol 3" << endl;
        cout <<"4. Buscar elemento 4" << endl;
        cout <<"5. Eliminar elemento 5" << endl;
        cout <<"6. Recorrido por niveles 6" << endl;
        cout <<"7.Altura por niveles   7" << endl;
        cout <<"8. Costruir arbol reflejo  8" << endl;
        cout <<"9.Contar nodos  9" << endl;
        cout <<"10.Contar hojas 10" << endl;
        cout <<"11. Nodos menos que k" << endl;
         cout <<"12. SALIR" << endl;
        cout << "\nIngrese una opcion: ";
        cin >> opcion;
        
        switch (opcion) {
            case 1:
               
                break;
                
            case 2:
               
                break;
                
            case 3:
                        
                break;
                
            case 4:
                               
                break;

            case 5:

                break;

            case 6:
                 int op;
                 cout<<"Ingrese la forma en la que quiere el recorrido";
                 cout<<"1.In Orden";
                 cout<<"2.Pos Orden";
                 cout<<"3. Pre Orden";
                    cout << "\nIngrese una opcion: ";
                     cin >> op;
                     switch (op){
                     case 1:
                         cout<< inorden;
                         break;
                      case 2:
                         break;
                      case 3:
                          break;      
                     default:
                         break;
                     }

                break;

            case 7:
                break;

            case 8:
                break;

            case 9:
                break; 

            case 10:
                break;

            case 11:
                break;

            case 12:
                break;
        }        

    
}