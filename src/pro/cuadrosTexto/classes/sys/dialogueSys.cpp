#include "./dialogueSys.hpp"


void leerFichero (string s) {
 
 //abrimos el fichero de texto
 texto.open (s, ios::in);

 //mientras el archivo esta abierto leer
 if (texto.is_open()) {
 while (! texto.eof() ) {
 texto >> letra;
 cout << letra << " ";
 }
 //cerramos al terminar IMPORTANTE
 texto.close();
 }

 //si no encontramos el fichero
 else cout << "No encuentro el fichero" << endl;

}
