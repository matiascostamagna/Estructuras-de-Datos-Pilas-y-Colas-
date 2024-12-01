#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h> 
#include <fstream>
#include <istream>

using namespace std;

template <class T> class Nodo {
private:
    T dato;
    Nodo* next;
public:
    Nodo() { next = NULL; };
    Nodo(T a) { dato = a; next = NULL; };
    void set_dato(T a) { dato = a; };
    void set_next(Nodo* n) { next = n; };
    T get_dato() { return dato; };
    Nodo* get_next() { return next; };
    bool es_vacio() { return next == NULL; };
};

template <class T> class Lista {
private: Nodo<T>* czo;
       void borrarD(T d, Nodo<T>* ant);
public:
    Lista() { czo = new Nodo<T>(); };
    Lista(Nodo<T>* n) { czo = n; };
    void add(T d); //sumar nodos a la lista
    bool esvacia(void);
    T cabeza(void); //retorna el dato del primer nodo
    Lista* resto(void); //retorna el puntero al "resto" de la lista
                        //resto= lo que queda de la lista sin la cabeza
    string toPrint(string p);
    void impre(void);
    int size();
    bool esta(T d);// detecta si d esta en la lista
    void borrarDato(T d) { borrarD(d, NULL); }//borra el nodo que contiene d
    void borrar(void); //borra la cabeza
    void borrar_last();//borra el ultimo
    void concat(Lista<T>* l1);// le transfiere los datos de l1 a this
    Lista<T>* copy(void);// hace una copia de la lista
    void tomar(int n);//deja "vivos" los n primeros nodos y borra el resto
    T last(); //retorna el dato del ultimo nodo
};

template <class T> class Cola :public Lista<T> {
public:
    Cola(void) { Lista<T>(); };
    T tope() { return this->last(); };
    bool colavacia(void) { return this->esvacia(); };
    void encolar(T a) { this->add(a); };
    void desencolar(void) { this->borrar_last(); };
    T ultimo(void) { return this->cabeza(); };
    string imprimir(string s) { return this->toPrint(s); };
};

template <class T> T Lista<T>::last(){
    if (!this->esvacia()) {
        if (this->resto()->esvacia())return this->cabeza();
        return this->resto()->last();
    }return 0;
}

template <class T> void Lista<T>::add(T d){
    Nodo<T>* nuevo = new Nodo<T>(d);
    nuevo->set_next(czo);
    czo = nuevo;
}

template <class T> bool Lista<T>::esvacia(void){
    return czo->es_vacio();
}

template <class T> T Lista<T>::cabeza(void){
    if (this->esvacia()) {

        cout<<"Es vacia"<<endl;
        return false;
    }
    return czo->get_dato();
}

template <class T> Lista<T>* Lista<T>::resto(void){
    Lista<T>* l = new Lista<T>(czo->get_next());
    return (l);
}

template <class T> string Lista<T>::toPrint(string p){
    if (this->esvacia()) {
        return p;
    }
    else {
        ostringstream stm;
        stm << this->cabeza()  << "\n" << this->resto()->toPrint(p) << endl;
        return stm.str();
    }
}

template <class T> int Lista<T>::size(){
    if (this->esvacia()) return 0;
    return 1 + this->resto()->size();
}

template <class T> void Lista<T>::borrar(void){ //borra el nodo cabeza
    if (!this->esvacia()) {
        Nodo<T>* tmp = czo;
        czo = czo->get_next();
        delete tmp;
    }
}

template <class T> void Lista<T>::borrar_last(){ // borra el ultimo nodo
    if (!this->esvacia()) {
        if ((czo->get_next())->get_next() == NULL) {
            delete czo->get_next();
            czo->set_next(NULL);
        }
        else this->resto()->borrar_last();
    }
}

template <class T> void Lista<T>::concat(Lista<T>* l1){// le transfiere los datos de l1 a this
    if (!(l1->esvacia())) {
        this->concat(l1->resto());
        this->add(l1->cabeza());
    }
}

template <class T> Lista<T>* Lista<T>::copy(void){
    Lista<T>* aux = new Lista();
    aux->concat(this);
    return aux;
}

template <class T> void Lista<T>::tomar(int n){ //deja "vivos" los n primeros nodos y borra el resto
    if (this->size() > n) {
        this->borrar_last();
        this->tomar(n);
    }
}

template <class T> void Lista<T>::impre(void){
    Nodo<T>* aux;
    aux = czo;
    while (aux->get_next() != NULL) {
        cout << aux->get_dato() << endl;
        aux = aux->get_next();
    }
}

template <class T> bool Lista<T>::esta(T d){// busca d en la lista
    if (this->esvacia()) return false;
    if (this->cabeza() == d) return true;

    return this->resto()->esta(d);    
}

template <class T> void Lista<T>::borrarD(T d, Nodo<T>* ant){
    if (!this->esvacia()) {
        if (d == this->cabeza()) {
            if (ant == NULL) {//al principio
                this->borrar();
            }
            else {//entre medio
                ant->set_next(czo->get_next());
                delete czo;
            }
        }
        else  this->resto()->borrarD(d, czo);
    }
}

template <class T> class Pila:public Lista<T>{
      public:
             Pila(){Lista<T>();};
             void apilar(T d){this->add(d);};
             T tope(void){return this->cabeza();};
             void desapilar(void){this->borrar();};
             bool pilavacia(){return this->esvacia();};
             void vaciar();
};     

template <class T> void Pila<T>::vaciar(){
    while (!pilavacia()){
        desapilar();
    }
}

class Puntero{
    private:
    string entrada;
    char *px;
    string buffer;
    char *posfinal;
    string error;
    public:
    Puntero(){entrada = ""; px = nullptr; buffer = '.'; buffer.clear();};
    void setEntrada(string a){entrada = a;entrada = eliminarEspacios(entrada); px = &entrada.at(0); posfinal = &entrada.back();};
    char* getPuntero(){return px;};
    char* final(){return posfinal;};
    void nextPuntero(){px+=1;};
    string getEntrada(){return entrada;};
    void setPuntero(char* a){px = a;};
    void addBuffer(char a){if(a!=' '){buffer.push_back(a);}};  
    void setBuffer(string a){buffer.append(a);}; 
    string printBuffer(){return buffer;};
    string eliminarEspacios(string a);
    void resetBufferP(){buffer.clear();};
    void ERROR(string a, string b);
    string getERROR(){return error;};
    string salida();
};

void Puntero::ERROR(string a, string b){
    string i;
    i.append("      El error esta en: ").append(salida()).append("\n").append( "           El error es: ").append(a).append("\n").append("Fallo la validacion de: ").append(b);
    error = i;
}

string Puntero::salida(){
    string i = buffer;
    i.append("*ERROR*");
    for(int j = buffer.size(); j<entrada.size(); j++){
        i.push_back(entrada.at(j));
    }
    return i;
}

string Puntero::eliminarEspacios(string a){
    string b;
    for(int i = 0; i<a.size(); i++){
        if(a.at(i)!=' '){
            b.push_back(a.at(i));
        }
    }
    return b;
}

class Palabra:public Puntero{
    private: 
    Pila<char>* pilaPalabra;
    string palabra;
    string buffer;
    public:
    Palabra(){palabra = ""; palabra.clear();};
    bool validarPalabra(Puntero& a);
    bool validarPalabra(Puntero& a, Puntero& b);
    bool esta(char c);
    string getBufferP(){return buffer;};
};

bool Palabra::esta(char c){
    if(c=='{')return true;
    else if(c=='}')return true;
    else if(c=='[')return true;
    else if(c==']')return true;
    else if(c==':')return true;
    else if(c==',')return true;
    else return false;
}

bool Palabra::validarPalabra(Puntero& a, Puntero& b){
    pilaPalabra = new Pila<char>;
    if(*a.getPuntero()!='"'){
        a.ERROR("Falta una comilla \'\"\'", "String");
        return false;
    }
    else{
        a.addBuffer(*a.getPuntero());
        b.addBuffer(*a.getPuntero());
        pilaPalabra->apilar(*a.getPuntero());
        a.nextPuntero();
        while(*a.getPuntero()!='"' && a.getPuntero()<=a.final()){
            if(esta(*a.getPuntero())){
                a.ERROR("Falta una comilla \'\"\'", "String");
                return false;
            }
            a.addBuffer(*a.getPuntero());
            b.addBuffer(*a.getPuntero());
            a.nextPuntero();
        }
        if(*a.getPuntero()=='"'){
            a.addBuffer(*a.getPuntero());
            b.addBuffer(*a.getPuntero());
            a.nextPuntero();
            if(!pilaPalabra->esvacia()){
                pilaPalabra->desapilar();
                bool i = pilaPalabra->esvacia();
                pilaPalabra->vaciar();
                if(i==0){
                  a.ERROR("Falta una comilla \'\"\'", "String");
                  return i;
                }
                return i;
            }
            else{
                pilaPalabra->vaciar();
                a.ERROR("Falta una comilla \'\"\'", "String");
                return false;
            }
        }
        else{
            pilaPalabra->vaciar();
            a.ERROR("Falta una comilla \'\"\'", "String");
            return false;
        }
    }
}

bool Palabra::validarPalabra(Puntero& a){
    pilaPalabra = new Pila<char>;
    if(*a.getPuntero()!='"'){
        a.ERROR("Falta una comilla \'\"\'", "String");
        return false;
    }
    else{
        a.addBuffer(*a.getPuntero());
        pilaPalabra->apilar(*a.getPuntero());
        a.nextPuntero();
        while(*a.getPuntero()!='"' && a.getPuntero()<=a.final()){
            if(esta(*a.getPuntero())){
                a.ERROR("Falta una comilla \'\"\'", "String");
                return false;
            }
            a.addBuffer(*a.getPuntero());
            a.nextPuntero();
        }
        if(*a.getPuntero()=='"'){
            a.addBuffer(*a.getPuntero());
            if(!pilaPalabra->esvacia() && pilaPalabra->tope()=='"'){
              pilaPalabra->desapilar();
              bool i = pilaPalabra->esvacia();
              pilaPalabra->vaciar();
              if(i==0){
                a.ERROR("Falta una comilla \'\"\'", "String");
                return i;
              }
              return i;
            }
            else{
                pilaPalabra->vaciar();
                a.ERROR("Falta una comilla \'\"\'", "String");
                return false;
            }
        }
        else{
            pilaPalabra->vaciar();
            a.ERROR("Falta una comilla \'\"\'", "String");
            return false;
        }
    }
}

class LlaveValor:public Palabra{
    private:
    Pila<char>* pilaLV;
    char* px;
    public:
    LlaveValor(){pilaLV = new Pila<char>(); px = nullptr;};
    bool validarLV(Puntero& a);
    char* getPuntero(){return px;};

};

bool LlaveValor::validarLV(Puntero& a){
    Puntero b = a;
    b.resetBufferP();
    if(!validarPalabra(b)){
        return false;
    }
    b.nextPuntero();
    if(*b.getPuntero()!=':'){
        a.ERROR("Falta una comilla \':\'", "Llave Valor");
        return false;
    }
    b.addBuffer(*b.getPuntero());
    b.nextPuntero();
    if(validarPalabra(b) ){
        a.setBuffer(b.printBuffer());
        a.setPuntero(b.getPuntero());
        return true; 
    }
    else{
        return false;
    }
}

class LlaveLista: public LlaveValor{
    private:
    Pila<char>* pilaLL;
    Cola<string>* colaLL = new Cola<string>();
    public:
    bool validarLL(Puntero& a);
    string getCola(){return colaLL->imprimir("\n");};
};

bool LlaveLista::validarLL(Puntero& a){
    Puntero b = a;
    b.resetBufferP();
    pilaLL = new Pila<char>;
    Puntero aux;
    if(!validarPalabra(b)){
        return false;
    }
    b.nextPuntero();
    if(*b.getPuntero()!=':'){
        a.ERROR("Falta una dos puntos \':\'", "LlaveLista");
        return false;
    }
    b.addBuffer(*b.getPuntero());
    b.nextPuntero();

    if(*b.getPuntero()!='['){
        a.ERROR("Falta una corchete \'[\'", "Lista");
        return false;
    }
    else{
        b.addBuffer(*b.getPuntero());
        pilaLL->apilar(*b.getPuntero());
        b.nextPuntero();
        while(*b.getPuntero()!=']' && b.getPuntero()<=b.final()){
            if(!(validarPalabra(b, aux))){
                return false;
            }
            else{
                colaLL->encolar(aux.printBuffer());
                aux.resetBufferP();
                b.addBuffer(*b.getPuntero());
                if(*b.getPuntero()==']'){
                    if(pilaLL->tope() == '['){
                        pilaLL->desapilar();
                        a.setBuffer(b.printBuffer());
                        a.setPuntero(b.getPuntero());
                        return true;      
                    }
                    else{
                        pilaLL->vaciar();
                        a.ERROR("Falta un corchete \'[\'", "Lista");
                        return false; 
                    }
                }
                else if(*b.getPuntero()==','){
                    b.nextPuntero();
                }
                else{
                    pilaLL->vaciar();
                    a.ERROR("Error en la validacion LlaveLista \']\'", "Lista");
                    return false;
                }
            }           
        }
        pilaLL->vaciar();
        return false;
    }
}

class LlaveExpresion: public LlaveLista{
    private:
    Pila<char>* pilaLE;
    public:
    LlaveExpresion(){pilaLE = new Pila<char>();};
    bool validarLE(Puntero& a);
};

bool LlaveExpresion::validarLE(Puntero& a){
    Puntero b = a;
    b.resetBufferP();
    if(!validarPalabra(a)){
        return false;
    }
    a.nextPuntero();
    if(*a.getPuntero()!=':'){
        a.ERROR("Falta una llave \':\'", "Par CLAVE:VALOR");
      return false;
    }
    a.addBuffer(*a.getPuntero());
    a.nextPuntero();
    if(*a.getPuntero()!='{'){
       a.ERROR("Falta una llave \'{\'", "Llave-Expresion");
      return false;
    }
    a.addBuffer(*a.getPuntero());
    pilaLE->apilar(*a.getPuntero());
    a.nextPuntero();
    while(*a.getPuntero()!='}' && a.getPuntero()<=a.final()){
        if(validarLV(a)){
            a.nextPuntero();
            a.addBuffer(*a.getPuntero());
            if(*a.getPuntero()==','){
                a.nextPuntero();
            }
            else if(*a.getPuntero()=='}'){
                if(!pilaLE->esvacia() && pilaLE->tope()=='{'){
                    pilaLE->desapilar();
                    return true;
                }
                else{
                    pilaLE->vaciar();
                    a.ERROR("Falta una llave \'}\'", "Llave-Expresion");
                    return false;
                }
            }
            else{
                pilaLE->vaciar();
                a.ERROR("Error en la validacion de Llave-Expresion", "Llave-Expresion");
                return false;
            }
        }   
        else if(validarLL(a)){
            a.nextPuntero();
            a.addBuffer(*a.getPuntero());
            if(*a.getPuntero()==','){
                a.nextPuntero();
                a.addBuffer(*a.getPuntero());
            }
            else if(*a.getPuntero()=='}'){
                if(!pilaLE->esvacia() && pilaLE->tope()=='{'){
                    pilaLE->desapilar();
                    return true;
                }
                else{
                    pilaLE->vaciar();
                    a.ERROR("Falta una llave \'}\'", "Llave-Expresion");
                    return false;
                }
            }
            else{
                pilaLE->vaciar();
                a.ERROR("Falta una llave \'}\'", "Llave-Expresion");
                return false;
            }
        }
        else if(validarLE(a)){
            a.nextPuntero();
            a.addBuffer(*a.getPuntero());
            if(*a.getPuntero()=='}' && a.getPuntero()<=a.final()){
                if(!pilaLE->esvacia() && pilaLE->tope()=='{'){
                    pilaLE->desapilar();
                    return true;
                }
                else{
                    pilaLE->vaciar();
                    a.ERROR("Falta una llave \'}\'", "Llave-Expresion");
                    return false;
                }
            }
            else if(*a.getPuntero()==','){
                a.nextPuntero();
            }
            else{
                pilaLE->vaciar();
                a.ERROR("Falta una llave \'}\'", "Llave-Expresion");
                return false;
            }
        }
        else{
            a.ERROR("Error en la validacion de Llave-Expresion", "Llave-Expresion");
            return false; 
        }
    }
    a.ERROR("Error en la validacion de Llave-Expresion", "Llave-Expresion");
    return false; 
}

class JSON: public LlaveExpresion{
    private:
    Pila<char>* pilaJ;
    Puntero c;
    public:
    JSON(Puntero i){c=i; pilaJ = new Pila<char>();};
    bool validarJSON(Puntero& a);
};

bool JSON::validarJSON(Puntero& a){
    if(*a.getPuntero()!='{'){
        a.ERROR("Falta una llave \'{\'", "JSON");
        return false;
    }
    a.addBuffer(*a.getPuntero());
    pilaJ->apilar(*a.getPuntero());
    a.nextPuntero();
    while(*a.getPuntero()!='}'&& a.getPuntero()<=a.final()){
        if(validarLV(a)){
            a.nextPuntero();
            if(*a.getPuntero()==','){
                a.addBuffer(*a.getPuntero());
                a.nextPuntero();
            }
            else if(*a.getPuntero()=='}' && a.getPuntero()==a.final()){
                if(pilaJ->tope()=='{'){
                    pilaJ->vaciar();
                    return true;
                }
                pilaJ->vaciar();
                a.ERROR("Falta una llave \'{\'", "JSON");
                return false;
            }
            else{
                pilaJ->vaciar();
                a.ERROR("Error en la validacion de JSON", "JSON");
                return false;
            }
        }
        else if(validarLL(a)){
            a.nextPuntero();
            if(*a.getPuntero()==','){
                a.nextPuntero();
            }
            else if(*a.getPuntero()=='}' && a.getPuntero()==a.final()){
                a.addBuffer(*a.getPuntero());
                if(!pilaJ->esvacia() && pilaJ->tope()=='{' ){
                      pilaJ->desapilar();
                      bool i = pilaJ->esvacia();
                      pilaJ->vaciar();
                      if(i==0){
                      a.ERROR("Falta una comilla \'}\'", "JSON");
                      return i;
                  }
                  return i;
                }
                pilaJ->vaciar();
                a.ERROR("Falta una llave \'{\'", "JSON");
                return false;
            }
            else{
                pilaJ->vaciar();
                a.ERROR("Error en la validacion de JSON", "JSON");
                return false;
            }
        }
        else if(validarLE(a)){
            a.nextPuntero();
            if(*a.getPuntero()==','){
                a.addBuffer(*a.getPuntero());
                a.nextPuntero();  
            }
            else{
              if(*a.getPuntero()=='}' && pilaJ->tope()=='{' && a.getPuntero()==a.final()){
                a.addBuffer(*a.getPuntero());
                pilaJ->desapilar();
                return true;
              }            
              else{
                pilaJ->vaciar();
                a.ERROR("Error en la validacion de JSON", "JSON");
                return false; 
              }
            }  
        }
        else{
            pilaJ->vaciar();
            a.ERROR("Error en la validacion de JSON", "JSON");
            return false;
        }
    }
    pilaJ->vaciar();
    a.ERROR("Error en la validacion de JSON", "JSON");
    return false;
}

int main(){
    Puntero expresion;
    ifstream archivo;
	string texto, entrada;
	archivo.open("Ejemplo.txt",ios::in);
	if(archivo.fail()){
		cout<<"Error en abrir el archivo";
		exit(1);
	}
	while(!archivo.eof()){
		getline(archivo,texto);
        entrada.append(texto);
	}
    expresion.setEntrada(entrada);
    JSON validar = JSON(expresion);
    if(validar.validarJSON(expresion)){
        cout<<"Expresion valida: " << "\n" << expresion.printBuffer() << endl;
        cout << "Valores enlistados: \n" << validar.getCola() << endl;
    }
    else{
        cout<<"Expresion invalida" << "\n" << expresion.getERROR() << endl;
    }
    archivo.close();
};