#include <iostream>
#include <stdlib.h>
#include <conio.h>
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
        return 0;
    }
    if((arbol->der == NULL) && (arbol->izq == NULL)){
        return 1;
    }
    else{
        return contarHojas(arbol->izq) + contarHojas(arbol->der);
    }
}
void limpiar(){
		cout<<"\n\nPresione cualquier tecla";
        getch();
}

int main(){
	int opc;
	do{
	
	
	cout<<"tMenu\n";
	cout <<"1.Insertar un elemento\n";
	cout<<"2.Mostrar arbol\n";
	cout<<"3.Recorridos de arbol\n";
	cout<<"4.Buscar elemento\n";
	cout<<"5. Eliminar elemento\n";
	cout<<"6.Recorrido por niveles\n";
	cout<<"7. Altura del arbol\n";
	cout<<"8.Construir arbol reflejo\n";
	cout<<"9.Contar hojas\n";
	cout<<"10.Nodos menores que k\n";
	cout<<"11.Salir\n";
	cout<<"Eliga una opcion:";
	cin>>opc;
	int x;
	ABB arbol;
	
	switch(opc){
		case 1:
			cout<<"Inserte el elemento a insertar: ";
			cin>>x;
			insertar(arbol,x);
			limpiar();
		break;
		case 2:
			verArbol(arbol,x);
			limpiar();
			 
		break;
		case 3:
			int opc2;
			cout<<"\tMenu\n";
				cout<<"1. PreOrden\n";
			 	cout<<"2. InOrden\n";
				cout<<"3. PostOrden\n";
				cout<<"Eliga una opcion: ";
			cin>>opc2;
			if (opc2==1){
				preorden(arbol);
			}else if(opc2==2){
				inorden(arbol);
			}else if(opc2==3){
				postorden(arbol);
			}
			limpiar();
		break;
		case 4:
			int dato;
			cout<<"Ingrese el valor a buscar: ";
			cin>>dato;
			if(buscarArbol(arbol,dato))
			
				cout<<"El dato exite";
			else
			
				cout<<"Dato no exite";
			limpiar();
		break;
		case 5:
			int datoE;
			cout<<"Ingrese el dato a eliminar: ";
			cin>>datoE;
			eliminar(arbol,datoE);
			limpiar();
		break;
		case 6:
			recorrerNiveles(arbol);
			limpiar();
		break;
		case 7:
			cout<<alturaABB(arbol);
			
			limpiar();
		break;
		case 8:
		arbolEspejo(arbol);
		limpiar(); 
		break;
		case 9:
			cout<<contarHojas(arbol);
			limpiar(); 
		break;
		case 10:
		int dato12; 
			cout<<"Ingrese el valor del dato";
			cin>>dato12;
			nodosMenoresQueK(arbol,dato12);
			limpiar();
		break;
		case 11: 
			exit(0);
		break;
		default:
			cout<<"no valida";
			break;	
	}
	system("cls");
}while(opc);    
}
