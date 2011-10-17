//
//  Model.h
//  Project
//
//  Created by Inês on 10/13/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef MODEL_H
#define MODEL_H

#define LINE_SIZE 128

#include "cg/cg.h"
#include <vector>
#include <map>
#include "Loader.h"

namespace CastleBlast {
	class Model {
	private:
		
		//Material Properties
		struct Material
		{
			float m_ambient[4], m_diffuse[4], m_specular[4];
			float m_shininess;
			float transparency;
			bool m_asTexture;
			GLuint m_textures;
			char m_pTextureFilename[LINE_SIZE];
		};
		
		// Materials Used
		int m_numMatrials;
		std::map<std::string, Material*> m_pMaterial;
		
		//Vertex Structure
		struct Vertex 
		{
			char m_boneID; //For Skeletal Animation
			float m_location[3];
		};
		
		//Vertices Used
		int m_numVertices;
		std::vector<Vertex*> m_pVertices;
		
		//Texture Point
		struct TexturePoint
		{
			float m_location[2];
		};
		
		int m_numTexturePoints;
		std::vector<TexturePoint*> m_pTexturePoints;
		
		//Normal Structure
		struct Normal
		{
			float m_normal[3];
		};
		
		int m_numNormals;
		std::vector<Normal*> m_pNormals;
		
		//Triangle Structure (3 vertices)
		struct Triangle
		{
			int m_normals[3];
			int m_textures[3]; //Texture coordinates for the 3 vertices (s,t)
			int m_vertexIndices[3]; //Store the 3 vertices of the triangle
			bool m_asNormals;
			bool m_asTexturePoints;
			Material *m_useMaterial; //the material to be applied to each vertex
		};
		
		//Triangles Used
		int m_numTriangles;
		std::vector<Triangle*> m_pTriangles;
		
		//Mesh (group of triangles)
		struct Mesh
		{
			int m_materialIndex;
			int m_numTriangles;
			int *m_pTriangleIndices; //Store the triangles in the mesh
		};
		
		//Mesh Used
		int n_numMeshes;
		std::vector<Mesh*> m_pMeshes;
		
		char mtllibname[LINE_SIZE]; //name of the .mtl file
		
	public:
		Model();
		~Model();
		bool loadModelData (const char *filename);
		bool readMTL (const char *filename);
		void drawModel();
	};
}

#endif