#include "ModelosWorld.h"

ModelosWorld::ModelosWorld(){

}

ModelosWorld::ModelosWorld(string nombreWorld){
	string linea;
	ifstream fe(nombreWorld);


	size_t espacio;
	string id;

	while (!fe.eof()){
		std::getline(fe, linea);
		if (!linea.empty()){
			if (linea[0] == '<' && linea[linea.length() - 1] == '>'){ //si es una instruccion <instruccion > 
				linea = linea.substr(1, linea.length() - 2);
				espacio = linea.find(" ");
				id = linea.substr(0, espacio); //Aquí tenemos el inicio de cada linea que nos indicará que hacer
				if (id == "modelo"){
					string nombre_modelo;
					string ruta_modelo;

					nombre_modelo = linea.substr(linea.find(" ") + 1);
					ruta_modelo = nombre_modelo.substr(nombre_modelo.find(" ") + 1);
					cout << "Obteniendo modelo " << nombre_modelo << endl;

					//Creo es innecesario esta parte, sólo falta no sumarle 1 en las instrucciones anteriores
					nombre_modelo = nombre_modelo.substr(0, nombre_modelo.find(" "));
					ruta_modelo = ruta_modelo.substr(0, ruta_modelo.find(" "));

					modelos[nombre_modelo] = ruta_modelo;
				}
				else if (id == "escena" || id == "objeto" || id == "personaje"){
					string nombre_modelo;
					string nombre_instancia;

					nombre_modelo = linea.substr(linea.find(" ") + 1);
					nombre_instancia = nombre_modelo.substr(nombre_modelo.find(" ") + 1);

					cout << "Creando instancia del modelo: " << nombre_modelo << " " << nombre_instancia << endl;

					//Creo es innecesario esta parte, sólo falta no sumarle 1 en las instrucciones anteriores
					nombre_modelo = nombre_modelo.substr(0, nombre_modelo.find(" "));
					nombre_instancia = nombre_instancia.substr(0, nombre_instancia.find(" "));

					ModeloObj modelo;

					if (modelos[nombre_modelo] != ""){
						modelo = { modelos[nombre_modelo] }; //Construimos el modelo
						if (id == "escena"){
							escenas[nombre_instancia] = modelo;
							escenas[nombre_instancia].cargaObjeto();
						}
						else if (id == "objeto"){
							objetos[nombre_instancia] = modelo;
							objetos[nombre_instancia].cargaObjeto();
						}
						else if (id == "personaje"){
							personajes[nombre_instancia] = modelo;
							personajes[nombre_instancia].cargaObjeto();
						}
					}
					else{
						cerr << "No existe ese tipo de modelo" << endl; //Error
					}
				}
				else if (id == "posicion" || id == "rotacion" || id == "escalamiento"){
					cout << "Estableciendo transformaciones: " << id << endl;
					string nombre_instancia;
					string p1, p2, p3; //Parámetro 1, parámetro 2, parámetro 3, 
					//faltaría comprobar que existieran todos los parámetros
					nombre_instancia = linea.substr(linea.find(" ") + 1);
					p1 = nombre_instancia.substr(nombre_instancia.find(" ") + 1);
					p2 = p1.substr(p1.find(" ") + 1);
					p3 = p2.substr(p2.find(" ") + 1);

					nombre_instancia = nombre_instancia.substr(0, nombre_instancia.find(" "));
					p1 = p1.substr(0, p1.find(" "));
					p2 = p2.substr(0, p2.find(" "));
					p3 = p3.substr(0, p3.find(" "));

					std::string::size_type sz;
					float f1, f2, f3;
					f1 = stof(p1, &sz);
					f2 = stof(p2, &sz);
					f3 = stof(p3, &sz);

					//El objeto ModeloObj no puede guardar los valores de rotación porque entonces sólo se podría
					//crear una instancia de cada modelo o que todos los modelos compartan transformaciones
					if (escenas.find(nombre_instancia) != escenas.end()){
						cout << "2 entré aquí por: " << linea << endl;
						if (id == "posicion"){
							escenas[nombre_instancia].pX = f1;
							escenas[nombre_instancia].pY = f2;
							escenas[nombre_instancia].pZ = f3;
						}
						else if (id == "rotacion"){
							escenas[nombre_instancia].rX = f1;
							escenas[nombre_instancia].rY = f2;
							escenas[nombre_instancia].rZ = f3;
						}
						else if (id == "escalamiento"){
							escenas[nombre_instancia].sX *= f1;
							escenas[nombre_instancia].sY *= f2;
							escenas[nombre_instancia].sZ *= f3;
						}
					}
					else if (objetos.find(nombre_instancia) != objetos.end()){
						if (id == "posicion"){
							objetos[nombre_instancia].pX = f1;
							objetos[nombre_instancia].pY = f2;
							objetos[nombre_instancia].pZ = f3;
						}
						else if (id == "rotacion"){
							objetos[nombre_instancia].rX = f1;
							objetos[nombre_instancia].rY = f2;
							objetos[nombre_instancia].rZ = f3;
						}
						else if (id == "escalamiento"){
							objetos[nombre_instancia].sX = f1;
							objetos[nombre_instancia].sY = f2;
							objetos[nombre_instancia].sZ = f3;
						}
					}
					else if (objetos.find(nombre_instancia) != objetos.end()){
						if (id == "posicion"){
							personajes[nombre_instancia].pX = f1;
							personajes[nombre_instancia].pY = f2;
							personajes[nombre_instancia].pZ = f3;
						}
						else if (id == "rotacion"){
							personajes[nombre_instancia].rX = f1;
							personajes[nombre_instancia].rY = f2;
							personajes[nombre_instancia].rZ = f3;
						}
						else if (id == "escalamiento"){
							personajes[nombre_instancia].sX = f1;
							personajes[nombre_instancia].sY = f2;
							personajes[nombre_instancia].sZ = f3;
						}
					}
					else{
						cerr << "No hay instancia con ese nombre, de ningún tipo" << endl;
					}
				}
			}
			else if (linea[0] == '#'){
				//cout << "COMENTARIO: " << linea << endl;
			}
		}
	}
}

void ModelosWorld::dibujaWorld(bool banderaTextura, bool banderaNormal){

	map<string, ModeloObj>::const_iterator itr;
	//Mostrar escenas guardadas
	for (itr = escenas.begin(); itr != escenas.end(); ++itr){
		//cout << "ESCENA: Key: " << (*itr).first << " Value: " << (*itr).second.fileName << endl;
	}
	//Mostrar objetos guardados
	for (itr = objetos.begin(); itr != objetos.end(); ++itr){
		//cout << "OBJETO: Key: " << (*itr).first << " Value: " << (*itr).second.fileName << endl;
	}
	//Mostrar objetos guardados
	for (itr = personajes.begin(); itr != personajes.end(); ++itr){
		//cout << "PERSONAJE: Key: " << (*itr).first << " Value: " << (*itr).second.fileName << endl;
	}

	for (itr = escenas.begin(); itr != escenas.end(); ++itr){
		glPushMatrix();
		glTranslatef((*itr).second.pX, (*itr).second.pY, (*itr).second.pZ);
		glRotatef((*itr).second.rX, 1, 0, 0);
		glRotatef((*itr).second.rY, 0, 1, 0);
		glRotatef((*itr).second.rZ, 0, 0, 1);
		glScalef((*itr).second.sX, (*itr).second.sY, (*itr).second.sZ);
		escenas[(*itr).first].dibujaObjeto(banderaTextura, banderaNormal);
		glPopMatrix();
	}
	for (itr = objetos.begin(); itr != objetos.end(); ++itr){
		glPushMatrix();
		glTranslatef((*itr).second.pX, (*itr).second.pY, (*itr).second.pZ);
		glRotatef((*itr).second.rX * 180 / M_PI, 1, 0, 0);
		glRotatef((*itr).second.rY * 180 / M_PI, 0, 1, 0);
		glRotatef((*itr).second.rZ * 180 / M_PI, 0, 0, 1);
		glScalef((*itr).second.sX, (*itr).second.sY, (*itr).second.sZ);
		objetos[(*itr).first].dibujaObjeto(banderaTextura, banderaNormal);
		glPopMatrix();
	}
	for (itr = personajes.begin(); itr != personajes.end(); ++itr){
		glPushMatrix();
		glTranslatef((*itr).second.pX, (*itr).second.pY, (*itr).second.pZ);
		glRotatef((*itr).second.rX, 1, 0, 0);
		glRotatef((*itr).second.rY, 0, 1, 0);
		glRotatef((*itr).second.rZ, 0, 0, 1);
		glScalef((*itr).second.sX, (*itr).second.sY, (*itr).second.sZ);
		personajes[(*itr).first].dibujaObjeto(banderaTextura, banderaNormal);
		glPopMatrix();
	}
	glPopMatrix();
}

ModelosWorld::~ModelosWorld()
{
}
