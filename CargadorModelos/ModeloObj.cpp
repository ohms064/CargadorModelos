#include "ModeloObj.h"


ModeloObj::ModeloObj()
{
}

ModeloObj::ModeloObj(string fileName)
{
	string linea;
	this->fileName = fileName;
	ifstream fe(fileName);

	if (!fe.good()) {
		banderaFile = false;
		cout << "Error al abrir el archivo: " << fileName << endl;
		return;
	}


	size_t espacio;
	string id;
	//cout << "CuentaID" << endl;
	while (!fe.eof()){
		getline(fe, linea);
		espacio = linea.find(" ");
		id = linea.substr(0, espacio); //Aquí tenemos el inicio de cada linea que nos indicará que hacer
		if (!linea.empty()){
			if (id == "v"){
				numVertices++;
			}
			else if (id == "vt"){
				//printf("TEXTURAS: ");
				numTexturas++;
			}
			else if (id == "vn"){
				//printf("NORMALES: ");
				numNormales++;
			}
			else if (id == "s"){
				//printf("NORMALES: ");
			}
			else if (id == "f"){
				//CARAS
				numCaras++;
			}
			else if (id == "g"){
				//Grupos
				numGrupos++;
			}
			else if (id == "usemtl"){
				//Grupos
				numMtl++;
			}
			else if (id == "mtllib"){
				linea.erase(0, linea.find(" ") + 1);
				cargaMaterial(linea);
			}
		}
	}
	//cout << "\tVertices: " << numVertices << " Caras: " << numCaras << " Texturas: " << numTexturas << endl;
	//cout << "\tGrupos: " << numGrupos << "mtl: " << numMtl << endl;
	vertices = new Vertice[numVertices];
	texturas = new Texturas[numTexturas];
	normales = new Normal[numNormales];
	caras = new Cara[numCaras];
	if (numGrupos == 0) grupos = new Grupo[numMtl];//Sólo se usará si no existen grupos.
	else grupos = new Grupo[numGrupos + 1];
}

int ModeloObj::cargaObjeto(){
	if (!banderaFile){
		cout << "Error en el archivo" << endl;
		return 0;
	}
	//cout << "Obteniendo vertices y caras" << endl;
	string linea;
	ifstream fe(fileName);
	int contador_lineas = 0;
	int contador_punto = 0;//Es el que lleva el conteo del número de puntos que se va a dibujar
	int contador_texturas = 0;//Es el que lleva el conteo del número de puntos que se va a dibujar
	int contador_normales = 0;//Es el que lleva el conteo del número de puntos que se va a dibujar
	int contador_cara = 0;
	int contador_grupos = 0;
	int contador_mtl = 0;
	size_t espacio;
	string id;
	while (!fe.eof()){
		contador_lineas++;
		getline(fe, linea);
		//printf("LINEA NO %d:\n\t%s\n", contador_lineas++, linea);	//printf("%s\n", linea);
		espacio = linea.find(" ");
		id = linea.substr(0, espacio); //Aquí tenemos el inicio de cada linea que nos indicará que hacer
		linea.erase(0, linea.find(" ") + 1); //Borramos el identificador de la linea para trabajar sólo con los datos.
		if (id == "#"){
			//printf("COMENTARIO: ");
		}

		else if (id == "usemtl"){
			if (numGrupos != 0){ 
				grupos[contador_grupos - 1].tex = linea; //Creamos la textura dentro de la variable tex de Grupos para futuro bind
			}
			else {//Si nunca hubiera habido grupos, se utilizan el usemtl como grupos
				if (contador_mtl == 0) grupos[0].inicio = 0;
				else grupos[contador_mtl].inicio = contador_cara + 1;//
				grupos[contador_mtl].tex = linea; //Creamos la textura dentro de la variable tex de Grupos para futuro bind
				contador_mtl++;

			}
		}
		else if (id == "v"){
			//Aquí se guardan las variables x,y,z del objeto vertices[]
			vertices[contador_punto].setAll(linea);// Cada vez que se llama a aspe retorna el token al que este apuntando y cambio su apuntador al siguiente token
			//vertices[contador_punto].print();
			contador_punto++;
		}
		else if (id == "vt"){
			//Aquí se guardan las variables x,y del objeto texturas[]
			texturas[contador_texturas].setAll(linea);// Cada vez que se llama a aspe retorna el token al que este apuntando y cambio su apuntador al siguiente token
			//texturas[contador_texturas].print();
			contador_texturas++;
		}
		else if (id == "vn"){
			//Aquí se guardan las variables x,y del objeto texturas[]
			normales[contador_normales].setAll(linea);// Cada vez que se llama a aspe retorna el token al que este apuntando y cambio su apuntador al siguiente token
			//normales[contador_normales].print();
			contador_normales++;
		}
		else if (id == "s"){
			//printf("NORMALES: ");
		}
		else if (id == "f"){
			//CARAS
			size_t pos = linea.find(" ");
			while (pos != std::string::npos){//Mientras haya espacios dentro de la cadena, esto significa que hay más de un vértice que guardar.
				caras[contador_cara].setCara(linea.substr(0, pos));//Aquí mismo se guarda vértice/textura/normal
				linea.erase(0, linea.find(" ") + 1);
				pos = linea.find(" ");
			}
			caras[contador_cara].setCara(linea);
			contador_cara++;
		}
		else if (id == "g"){
			//Grupos
			if (contador_grupos == 0){
				grupos[0].inicio = 0;
			}
			else {
				grupos[contador_grupos].inicio = contador_cara + 1;
				grupos[contador_grupos].id = linea;
			}
			contador_grupos++;
		}
		else{
			//printf("OTROS     : ");
		}
	}
	//cout << "Dibujando objeto" << endl;
	//cout << "Controles:\n\t '+', '-': Zoom\n\t '1': Textura\n\t '2': Normal\n\t '4', '5': Brillo" << endl;
	return 1;
}

void ModeloObj::dibujaObjeto(bool banderaTextura, bool banderaNormal){
	//Es llamado dentro de display
	int iterCaras = 0;
	int iterVertices = 0;
	int iterGrupos = 0;
	static int imprime = 0;
	char* temp; //Utilicé un char* porque CTexture recibe valores de este tipo
	string id;
	//cout << "Caras: " << iterCaras << " Grupos: " << iterGrupos << endl;
	for (iterCaras = 0; iterCaras < numCaras; iterCaras++){
		if (banderaTextura && iterCaras == grupos[iterGrupos].inicio){ 
			id = materiales[grupos[iterGrupos].tex].mapKd; //Obtenemos la textura
			temp = new char[id.size()]; //Obtenemos el tamaño del nombre de la textura
			strcpy(temp, id.c_str()); //Debemos copiar el c_str porque c_str retorna un apuntador
			size_t pos = id.find(".");
			if (id.substr(pos + 1, id.length()) == "tga") {
				tCubo.LoadTGA(temp);
			}
			else if (id.substr(pos + 1, id.length()) == "bmp") {
				tCubo.LoadBMP(temp);
			}
			tCubo.BuildGLTexture();
			//tCubo.ReleaseImage(); //La verdad no sé porque esta linea rompe el programa pero antes estaba
			iterGrupos++;
		}
		glBegin(GL_POLYGON);

		//Se empieza a dibujar las caras con los datos guarado en el arreglo "vertices" obtenida en cargaObjeto
		for (iterVertices = 0; iterVertices < caras[iterCaras].vertice.size(); iterVertices++){
			if (banderaNormal && !caras[iterCaras].normal.empty()){
				glNormal3f(normales[caras[iterCaras].normal.front()].x, normales[caras[iterCaras].normal.front()].y, normales[caras[iterCaras].normal.front()].z);
				caras[iterCaras].popNormal();
			}
			if (banderaTextura && !caras[iterCaras].textura.empty()){
				glTexCoord2f(texturas[caras[iterCaras].textura.front() - 1].x, texturas[caras[iterCaras].textura.front() - 1].y);
				caras[iterCaras].popTextura();
			}
			glVertex3f(vertices[caras[iterCaras].vertice.front()].x, vertices[caras[iterCaras].vertice.front()].y, vertices[caras[iterCaras].vertice.front()].z);
			caras[iterCaras].popVertice();
		}
		glEnd();
	}
}

void ModeloObj::cargaMaterial(string matName){
	Material temporal;
	string idMaterial = "";
	size_t espacio;
	string id;
	string linea;
	ifstream fe(matName);
	if (!fe.good()) {
		cout << "Error al abrir el archivo: " << matName << endl;
		return;
	}
	while (!fe.eof()){
		getline(fe, linea);
		espacio = linea.find(" ");
		id = linea.substr(0, espacio);
		linea.erase(0, linea.find(" ") + 1);
		if (id == "newmtl"){
			if (idMaterial != ""){//Significa que por lo menos ya creamos un material completamente
				materiales[idMaterial] = temporal;
				temporal = {};
			}
			idMaterial = linea;
		}
		else if (id == "Ns"){
			temporal.Ns = stof(linea);
		}
		else if (id == "Ka"){
			temporal.setKa(linea);
		}
		else if (id == "Ks"){
			temporal.setKs(linea);
		}
		else if (id == "Kd"){
			temporal.setKd(linea);
		}
		else if (id == "Ni"){
			temporal.Ni = stof(linea);
		}
		else if (id == "d"){
			temporal.d = stof(linea);
		}
		else if (id == "illum"){
			temporal.illum = stoi(linea);
		}
		else if (id == "map_Kd"){
			temporal.mapKd = linea;
		}
	}
	materiales[idMaterial] = temporal; //Llegamos al final y guardamos el último material
}

ModeloObj::~ModeloObj()
{
}
