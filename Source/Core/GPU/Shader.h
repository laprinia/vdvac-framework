#pragma once
#include <string>
#include <vector>
#include <list>
#include <functional>

#include <include/gl.h>

#define MAX_2D_TEXTURES		16
#define INVALID_LOC			0

class Shader
{
	public:
		Shader(const char *name);
		~Shader();

		const char *GetName() const;
		GLuint GetProgramID() const;

		void Use() const;
		unsigned int Reload();

		void AddShader(const std::string &shaderFile, GLenum shaderType);
		void ClearShaders();
		unsigned int CreateAndLink();

		void BindTexturesUnits();
		GLint GetUniformLocation(const char * uniformName) const;

		void OnLoad(std::function<void()> onLoad);

	private:
		void GetUniforms();
		static unsigned int CreateShader(const std::string &shaderFile, GLenum shaderType);
		static unsigned int CreateProgram(const std::vector<unsigned int> &shaderObjects);

	public:
		GLuint program;

		// Textures
		GLint loc_textures[MAX_2D_TEXTURES];

		// MVP
		GLint loc_model_matrix;
		GLint loc_view_matrix;
		GLint loc_projection_matrix;

		// Shadow
		GLint loc_light_pos;
		GLint loc_light_color;
		GLint loc_light_radius;
		GLint loc_light_direction;

		// Camera
		GLint loc_eye_pos;
		GLint loc_eye_forward;
		GLint loc_z_far;
		GLint loc_z_near;

		// General
		GLint loc_resolution;
		
		// Text
		GLint text_color;

	private:

		bool compileErrors;

		struct ShaderFile
		{
			std::string file;
			GLenum type;
		};

		std::string shaderName;
		std::vector<ShaderFile> shaderFiles;
		std::list<std::function<void()>> loadObservers;
};
