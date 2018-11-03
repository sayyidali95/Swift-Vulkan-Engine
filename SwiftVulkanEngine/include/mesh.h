#ifndef __MESH_H__
#define __MESH_H__


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>



#include "shader.h"
#include "graphics.h"
#include "stb_image.h"


#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace sa3d {
	namespace graphics {


		/**
		@brief Vertex buffer class to create triangles for mesh 
		**/
		struct Vertex {
			glm::vec3 Position;
			glm::vec3 Normal;
			glm::vec2 TexCoords;
			glm::vec3 Tangent;
			glm::vec3 Bitangent;
		};

		/**
		@brief  Texture class take getting Image path and file type of image file
		**/

		struct Texture {
			unsigned int id;
			std::string type;
			aiString path;
		};

		/**
		@brief Mesh class for creating object from file
		*/
		class Mesh {
		public:
			/*  Mesh Data  */
			std::vector<Vertex> vertices;
			std::vector<GLuint> indices;
			std::vector<Texture> textures;
			unsigned int VAO;
			/*  Functions  */
			/**Constructor */
			Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
			
			/** Draw mesh from file*/
			void Draw(Shader shader);
		private:
			/*  Render data  */
			GLuint VBO, EBO;
			/*  Functions    */
			void setupMesh();
		};

	}
}
#endif