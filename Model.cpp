//
//  Model.cpp
//  Project
//
//  Created by Inês on 10/13/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Model.h"

namespace CastleBlast {
	
	Model::Model()
	{
		m_numVertices = 0;
		m_numTexturePoints = 0;
		m_numNormals = 0;
		m_numTriangles = 0;
	}
	
	bool Model::readMTL(const char *filename)
	{
		FILE *file;
		char buf[LINE_SIZE];
		
		file = fopen(filename, "r");
		if (!file)
			return false;
		
		std::string materialName;
		Material *tempMat;
		
		while (fscanf(file, "%s", buf) != EOF) {
			switch (buf[0]) {
				case '#':
					fgets(buf, sizeof(buf), file);
					break;
				case 'n':
				{
					fgets(buf, sizeof(buf), file);
					sscanf(buf, "%s", buf);
					Material *mat = (Material*)malloc(sizeof(Material));
					materialName = buf;
					m_pMaterial.insert(std::pair<std::string, Material*>(materialName, mat));
					tempMat = mat;
					tempMat->m_asTexture = false;
					break;
				}
				case 'N':
				{
					if (buf[1] == 's') {
						float shininess;
						fscanf(file, "%f", &shininess);
						shininess = (shininess*128) / 1000;
						tempMat->m_shininess = shininess;
					}
					else fgets(buf, sizeof(buf), file);
					break;
				}
				case 'K':
				{
					float r, g, b;
					switch (buf[1]) {
						case 'd':
						{
							fscanf(file, "%f %f %f", &r, &g, &b);
							tempMat->m_diffuse[0] = r;
							tempMat->m_diffuse[1] = g;
							tempMat->m_diffuse[2] = b;
							tempMat->m_diffuse[3] = 1;
							break;
						}
						case 's':
						{
							fscanf(file, "%f %f %f", &r, &g, &b);
							tempMat->m_specular[0] = r;
							tempMat->m_specular[1] = g;
							tempMat->m_specular[2] = b;
							tempMat->m_specular[3] = 1;
							break;
						}
						case 'a':
						{
							fscanf(file, "%f %f %f", &r, &g, &b);
							tempMat->m_ambient[0] = r;
							tempMat->m_ambient[1] = g;
							tempMat->m_ambient[2] = b;
							tempMat->m_ambient[3] = 1;
							break;
						}
						default:
							fgets(buf, sizeof(buf), file);
							break;
					}
					break;
				}
				case 'd':
				{
					float transparency;
					fscanf(file, "%f", &transparency);
					tempMat->transparency = transparency;
					break;
				}
				case 'm':
				{
					//char mapType[7];
					char filename[LINE_SIZE];
					char *path;
					fscanf(file, "%s", filename);
					
					char tempFilename[LINE_SIZE];
					strcpy(tempFilename, filename);
					path = strtok(tempFilename, "/");
#ifdef __APPLE__
					strcpy(filename, path);
#else
					strcpy(filename, "..\\..\\src\\");
					strncat(filename, path, strlen(filename));
#endif
					path = strtok(NULL, "/");
					while (path != NULL) {
#ifdef __APPLE__
						strncat(filename, "/", strlen(filename));
						strncat(filename, path, strlen(filename));
#else
						strncat(filename, "\\", strlen(filename));
						strncat(filename, path, strlen(filename));
#endif
						path = strtok(NULL, "/");
					}
					
					tempMat->m_textures = Loader::loadTexture(filename);
					strcpy(tempMat->m_pTextureFilename, filename);
					tempMat->m_asTexture = true;
					break;
				}
				default:
					fgets(buf, sizeof(buf), file);
					break;
			}
		}
	}
	
	bool Model::loadModelData(const char *filename)
	{
		FILE *inputfile;
		
		inputfile = fopen(filename, "r");
		if (!inputfile)
			return false; //"Couldn't Open The Model File.
		
		//temporary buffer where aech lines will be stored
		char buf[LINE_SIZE];
		
		float x, y, z;
		Material *tempMat;
		
		while (fscanf(inputfile, "%s", buf) != EOF) {
			switch (buf[0]) {
				case '#': //comment
					fgets(buf, sizeof(buf), inputfile);
					break;
				case 'v':
				{
					switch (buf[1]) {
						case '\0':
						{
							fscanf(inputfile, "%f %f %f", &x, &y, &z);
							m_numVertices++;
							Vertex *vert = (Vertex*)malloc(sizeof(Vertex));
							vert->m_location[0] = x;
							vert->m_location[1] = y;
							vert->m_location[2] = z;
							m_pVertices.push_back(vert);
							break;
						}
						case 'n':
						{
							fscanf(inputfile, "%f %f %f", &x, &y, &z);
							m_numNormals++;
							Normal *normal = (Normal*)malloc(sizeof(Normal));
							normal->m_normal[0] = x;
							normal->m_normal[1] = y;
							normal->m_normal[2] = z;
							m_pNormals.push_back(normal);
						}
						case 't':
						{
							fscanf(inputfile, "%f %f", &x, &y);
							m_numTexturePoints++;
							TexturePoint *text = (TexturePoint*)malloc(sizeof(TexturePoint));
							text->m_location[0] = x;
							text->m_location[1] = y;
							m_pTexturePoints.push_back(text);
							break;
						}
							
					}
					break;
				}
				case 'm':
				{
					fgets(buf, sizeof(buf), inputfile);
					sscanf(buf, "%s", buf, buf);
#ifdef __APPLE__
					strcpy(mtllibname, buf);
#else
					char tempFilename[LINE_SIZE];
					char *path;

					strcpy(tempFilename, buf);
					path = strtok(tempFilename, "/");

					strcpy(mtllibname, "..\\..\\src\\");
					strncat(mtllibname, path, strlen(mtllibname));

					path = strtok(NULL, "/");
					while (path != NULL) {
						strncat(mtllibname, "\\", strlen(mtllibname));
						strncat(mtllibname, path, strlen(mtllibname));
						path = strtok(NULL, "/");
					}
#endif
					readMTL(mtllibname);
					break;
				}
				case 'u':
				{
					char tempMaterialName[LINE_SIZE];
					std::string materialName;
					fscanf(inputfile, "%s", tempMaterialName);
					materialName = tempMaterialName;
					tempMat = m_pMaterial.find(materialName)->second;
					break;
				}
				case 'f':
				{
					int v, n, t;
					m_numTriangles++;
					Triangle *tri = (Triangle*)malloc(sizeof(Triangle));
					tri->m_useMaterial = tempMat;
					tri->m_asNormals =false;
					tri->m_asTexturePoints = false;
					fscanf(inputfile, "%s", buf);
					if (strstr(buf, "//")) {
						/* v//n */
						sscanf(buf, "%d//%d", &v, &n);
						tri->m_normals[0] = n - 1;
						tri->m_vertexIndices[0] = v - 1;
						fscanf(inputfile, "%d//%d", &v, &n);
						tri->m_normals[1] = n - 1;
						tri->m_vertexIndices[1] = v - 1;
						fscanf(inputfile, "%d//%d", &v, &n);
						tri->m_normals[2] = n - 1;
						tri->m_vertexIndices[2] = v - 1;
						tri->m_asNormals = true;
					}
					else if (sscanf(buf, "%d/%d/%d", &v, &t, &n) == 3) {
						tri->m_vertexIndices[0] = v - 1 ;
						tri->m_textures[0] = t - 1;
						tri->m_normals[0] = n - 1;
						(fscanf(inputfile, "%d/%d/%d", &v, &t, &n));
						tri->m_vertexIndices[1] = v - 1;
						tri->m_textures[1] = t - 1;
						tri->m_normals[1] = n - 1;
						(fscanf(inputfile, "%d/%d/%d", &v, &t, &n));
						tri->m_vertexIndices[2] = v - 1;
						tri->m_textures[2] = t - 1;
						tri->m_normals[2] = n - 1;
						
						tri->m_asNormals = true;
						tri->m_asTexturePoints = true;
					}
					else if (sscanf(buf, "%d/%d", &v, &t) == 2){
						tri->m_vertexIndices[0] = v - 1;
						tri->m_textures[0] = t - 1;
						fscanf(inputfile, "%d/%d", &v, &t);
						tri->m_vertexIndices[1] = v - 1;
						tri->m_textures[1] = t - 1;
						fscanf(inputfile, "%d/%d", &v, &t);
						tri->m_vertexIndices[2] = v - 1;
						tri->m_textures[2] = t - 1;
						
						tri->m_asTexturePoints = true;
					}
					else {
						sscanf(buf, "%d", &v);
						tri->m_vertexIndices[0] = v - 1;
						fscanf(inputfile, "%d", &v);
						tri->m_vertexIndices[1] = v - 1;
						fscanf(inputfile, "%d", &v);
						tri->m_vertexIndices[2] = v - 1;
					}
					m_pTriangles.push_back(tri);
					break;
				}
				default:
					fgets(buf, sizeof(buf), inputfile);
					break;
			}
			
		}
		std::map<std::string, Material*>::iterator it;
		
		for (it = m_pMaterial.begin() ; it != m_pMaterial.end(); it++) {
			std::cout << "Material " << it->first << ":" << std::endl;
			std::cout << "    Ambient: " << it->second->m_ambient[0] << " " << it->second->m_ambient[1] << " " << it->second->m_ambient[2] << std::endl;
			std::cout << "    Diffuse: " << it->second->m_diffuse[0] << " " << it->second->m_diffuse[1] << " " << it->second->m_diffuse[2] << " " << std::endl;
			std::cout << "    Specular: " << it->second->m_specular[0] << " " << it->second->m_specular[1] << " " << it->second->m_specular[2] << " " << std::endl;
			std::cout << "    Shininess: " << it->second->m_shininess << std::endl;
			if (it->second->m_asTexture) {
				std::cout << "    Texture: " << it->second->m_pTextureFilename << std::endl;
			}
		}
	}
	
	void Model::drawModel()
	{
		for(int i = 0; i < m_pTriangles.size(); i++) {
			Triangle *tri = m_pTriangles[i];
			
			glMaterialfv(GL_FRONT, GL_AMBIENT, tri->m_useMaterial->m_ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, tri->m_useMaterial->m_diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, tri->m_useMaterial->m_specular);
			glMaterialf(GL_FRONT, GL_SHININESS, tri->m_useMaterial->m_shininess);
			
			if (tri->m_useMaterial->m_asTexture) {
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, tri->m_useMaterial->m_textures);
				
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			}
			
			glBegin(GL_TRIANGLES);
				for (int j = 0; j < 3; j++){
					int index;
					if (tri->m_asNormals){
						index = tri->m_normals[j];
						glNormal3fv(m_pNormals[index]->m_normal);
					}
					if (tri->m_asTexturePoints) {
						index = tri->m_textures[j];
						glTexCoord2f(m_pTexturePoints[index]->m_location[0], m_pTexturePoints[index]->m_location[1]);
					}
					index = tri->m_vertexIndices[j];
					glVertex3d(m_pVertices[index]->m_location[0], m_pVertices[index]->m_location[1], m_pVertices[index]->m_location[2]);
				
				}
			glEnd();
			
			if (tri->m_useMaterial->m_asTexture)
				glDisable(GL_TEXTURE_2D);
		}
	}
}