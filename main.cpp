#include <iostream>
#include <fstream> // archivo de texto
#include <cstdlib>
#include <cstring>
#include <string>
#include <climits>
#include <vector>
#include <stdio.h>

#include <stdlib.h>
#include <conio.h>
#include <windows.h>
using namespace std;

class Articulo{
	public:
		string referencia; //codigo
		string nombre ;//nnobre libro
		int existente;
		int entrega;
		int retorno;
		
		Articulo(){}
		bool operator == (const Articulo &articulo) const{
			return this == &articulo || this -> referencia == articulo.referencia;
		}
		bool operator <(const Articulo &articulo) const{
			return this -> referencia<articulo.referencia;
		}
		Articulo & operator = (const Articulo &articulo){
			if (this!=&articulo){
				this -> referencia = articulo.referencia;
				this -> nombre = articulo.nombre;
				this -> existente = articulo.existente;
				this -> entrega = articulo.entrega;
				this -> retorno = articulo.retorno;
				
			}
			return *this;
		}
		static void imprimir(Articulo &articulo , int *contador){
			cout << " Codigo del libro                               : " << articulo.referencia.c_str() << endl;
			cout << " Nombre del libro                               : " << articulo.nombre.c_str() << endl;
			cout << " Horas acumuladas del prestamo                  : " << articulo.existente << endl;
			cout << " Horas habilitadas de prestamo                  : " << articulo.entrega << endl;
			cout << " Horas maxima para devolucion del libro         : " << articulo.retorno << endl;
			cout << endl;
			(*contador)++;
			
		}
		//imprimir en archivo
		static void imprimir_en_archivo(Articulo &articulo , ostream *archivo){
			*archivo << articulo.referencia.c_str() << "\t";
			*archivo << articulo.nombre.c_str() << "\t";
			*archivo << articulo.existente << "\t";
			*archivo << articulo.entrega << "\t";
			*archivo << articulo.retorno << endl ;
			
		}
};
//funciones
string leer_cadena (const char *mensaje);
int leer_entero (const char *mensaje , int menor , int mayor);
bool leer_campo (istream &archivo , char *campo , char delimitador);
template <class T> T* vector_buscar (vector <T> &arreglo , const T &dato);
template <class T> void vector_quitar (vector <T> &arreglo , T &dato);
template <class T> void quick_sort (vector <T> &arreglo , int inicio =0 , int fin =-1);
void gotoxy(int x,int y);
//FUNCION GOTOXY
void gotoxy(int x,int y){  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
 }
 //FUNCION DIBUJAR CUADRO
void dibujarCuadro(int x1,int y1,int x2,int y2)
{

    int i;
    for (i=x1;i<x2;i++)
    {
	gotoxy(i,y1);printf("Ä") ;//linea horizontal superior
	gotoxy(i,y2);printf("Ä") ;//linea horizontal inferior
    }

    for (i=y1;i<y2;i++)
    {
	gotoxy(x1,i);printf("³") ;//linea vertical izquierda
	gotoxy(x2,i);printf("³") ;//linea vertical derecha
    }
    gotoxy(x1,y1);printf("Ú");
    gotoxy(x1,y2);printf("À");
    gotoxy(x2,y1);printf("¿");
    gotoxy(x2,y2);printf("Ù");
}


int main(){	
	system ("color F0");
	dibujarCuadro(0,0,78,24);//Cuadro grande
	dibujarCuadro(1,1,77,3);//Cuadro del titulo
	Articulo *dato , articulo ; // crea objeto
	vector <Articulo> arreglo ;
	int i , n , opcion , contador=0 ;
	char campo[255],ruta[]= "datos.txt" ;// nombre archivo txt para almacenar los datos 
	
	ifstream entrada (ruta);
	if (entrada !=NULL){
		while (leer_campo (entrada,campo,'\t')){
			articulo.referencia=campo;
			leer_campo(entrada,campo,'\t');
			articulo.nombre =campo ;
			leer_campo (entrada,campo,'\t');
			articulo.existente=atoi (campo);
			leer_campo(entrada,campo,'\t');
			articulo.entrega=atoi(campo);
			leer_campo (entrada ,campo,'\n');
			articulo.retorno =atoi (campo) ;
			arreglo.push_back (articulo);
			}
		entrada.close();
	    }
	do { 
	system ("cls");
	// Menu en pantalla 
	gotoxy(16,2);printf("--------------------------------------------------------------");
	gotoxy(19,4);printf("                 B I B L I O T E C A");
	gotoxy(16,6);printf("--------------------------------------------------------------");
	cout << "\n               Programa para registrar prestamos de libros en la biblioteca \n\n" << endl << "\n     MENU PRINCIPAL\n " << endl;
	cout << "     1. Ingresar nuevo prestamo "
	<< endl << "     2. Consultar si el libro esta habilitado"
	<< endl << "     3. Modificar prestamo existente"
	<< endl << "     4. Eliminar prestamo existente "
	<< endl << "     5. Ordenar libros "
	<< endl << "     6. Editar prestamos de libros existentes\n "
	<< endl << "     Nota : Para guardar los prestamos es necesario al final seleccionar la opcion :\n" 
	<< endl << "     7. Guardar todo y Salir del sistema "
	<< endl ;
	opcion == leer_entero ("\n     Seleccione una opcion : " , 1,7);
	cout << endl ;
	// condicionales 
	//opcion 2 : consulta de registros
	// aparece " no existen registros " cuando el archivo creado existen " 
	if (arreglo.empty() && opcion!=1 && opcion!=7){
		cout << endl << "     No existen prestamos registrados " << endl << endl;
		gotoxy(5,29);system("pause");
		continue ;
	}
	//ingreso de articulo
	if ( opcion < 5){
		articulo.referencia = leer_cadena("     Ingrese el codigo del libro : " ) ;
		dato = vector_buscar (arreglo ,articulo);
		if (dato !=NULL)
			Articulo::imprimir (*dato,&contador);
	}
	//buscar el archivo si esta creado si  no , continua con el ingreso de dato
	if (dato != NULL && opcion ==1)
		cout << endl << "     Registro de prestamos existente ";
	else if (dato ==NULL && opcion >= 2 && opcion <=4 )
		cout << endl << "     No se encontro el prestamo solicitado ";
	else switch (opcion){
		case 1 :
			articulo.nombre = leer_cadena ("     Nombre del libro : " ); //permite el ingreso de letras y nombres 
			articulo.existente =leer_entero ("     Ingresar numero de horas de prestamo: " ,0,INT_MAX);//ingreso de enteros 
			articulo.entrega=leer_entero("     Ingrese hora de entrega de prestamo del libro  : ", 0 ,INT_MAX); // enteros
			articulo.retorno = leer_entero("     Ingrese hora de retorno del libro : " , 0 , INT_MAX); //enteros
			arreglo.push_back(articulo);
			cout << endl << "     Registro de prestamo agregado correctamente " ;
			break;
		case 3 :
		//modificar campos ya guardados en archivo
			cout << "\n      Menu de modificacion de campos\n" << endl;
			cout << "     1.- Nombre del libro " << endl;
			cout << "     2.- Cantidad de horas de prestamo " << endl ;
			cout << "     3.- Hora del prestamo de libro  " << endl ;
			cout << "     4.- Hora de retorno del prestamo de libro " << endl;
			switch (leer_entero("\n      Seleccione un numero de campo a modificar : ",1,4)){
				case 1:
					dato ->nombre = leer_cadena("     Ingrese el nombre del libro:" );
					break;
				case 2 :
					dato ->existente =leer_entero ("     Cantidad de horas habilitadas para el prestamo del libro: " ,0,INT_MAX );
					break;
				case 3 :
					dato ->entrega = leer_entero ("     Ingrese hora de entrega:" ,0, INT_MAX);
					break;
				case 4 :
					dato ->retorno= leer_entero("     Ingrese hora de retorno : ",0, INT_MAX);
					break;
				}
			cout << endl << "     Registro actualizado correctamente " ;
			break;
		case 4:
			vector_quitar (arreglo , *dato);
			cout << endl << "     Registro borrado correctamente " ;
			break ;
		case 5:
			quick_sort (arreglo);
			cout << endl << "      Registro ordenados correctamente . " ;
			break;
		case 6:
			n= arreglo.size();
			contador =0 ;
			for(i=0;i<n ;i++)
				Articulo::imprimir(arreglo[i], &contador);
			cout << "     Total de registros : " << contador << "." ;
			break ;		
		}
		if (opcion <7 && opcion >=1){
			cout << endl << endl ;
			system("pause");
			}
			
		}
		while (opcion !=7);
		ofstream salida (ruta);
		if(salida !=NULL){
			n=arreglo.size();
			for(i=0;i<n;i++)
			Articulo::imprimir_en_archivo(arreglo[i],&salida);
			salida.close();
		}
		return EXIT_SUCCESS;
	
	}
	//Vector para busqueda de informacion ya registrada en archivo
	template <class T>
	T* vector_buscar (vector <T> &arreglo , const T &dato){
		int i , n=arreglo.size();
		for (i=0 ;i <n ;i++)
			if (dato ==arreglo[i])
				return &arreglo[i];
		return NULL;
	}
	
	//vector para eliminar los datos registrados
	template <class T >
	void vector_quitar (vector <T> &arreglo , T &dato){
		int i , n=arreglo.size();
		for (i=0 ; i<n ; i++)
			 if (dato ==arreglo[i]){
			 	arreglo.erase (arreglo.begin() +i);
			 	return ;
			 	
			 }
	}
	
	//vector que valida numeros negativos
	template <class T>
	void quick_sort(vector<T> &arreglo , int inicio , int fin ){
		int menor= inicio, mayor;
		if( fin == -1)
			fin= arreglo.size()-1;
		mayor =fin ;
		T pivote;
		if (fin > inicio){
			for (pivote=arreglo[(inicio+fin)/2]; menor <= mayor ;){
				for (;menor< fin &&arreglo[menor]< pivote ; menor++);
				for(;mayor > inicio && pivote < arreglo [mayor]; mayor --);
				if (menor <=mayor){
					pivote=arreglo[menor];
					arreglo[menor]=arreglo[mayor];
					arreglo[mayor]=pivote;
					menor++;
					mayor--;
					
				}
			}
		if (inicio < mayor)
			quick_sort (arreglo ,inicio,mayor);
		if(menor < fin)
		quick_sort(arreglo,menor,fin);
		}
	}
	//valida cualquier caracter
	string leer_cadena(const char *mensaje){
		char cadena[255];
		cout << mensaje << " " ;
		cin.getline(cadena ,sizeof(cadena));
		char *salto =strchr(cadena , '\n');
		if (salto !=NULL)
			*salto = '\0';
		string str(cadena);
		return str ;
		}
	//valida solo enteros
	int leer_entero (const char *mensaje , int menor , int mayor){
		int entero ;
		do{
			cout << mensaje <<" " ;
			cin >> entero ;
			cin.get();
			if(entero < menor || entero >mayor)
				cout << "     Numero no valido " <<endl ;
		}
		while (entero < menor || entero >mayor);
		return entero ;
		}
	bool leer_campo(istream &archivo , char *cadena , char delimitador){
		archivo.getline(cadena ,255 , delimitador);
		if(archivo.eof())
			return false;
		char *tab =strchr(cadena,delimitador);
		if(tab!=NULL)
			*tab ='\0';
		return true;
	}



