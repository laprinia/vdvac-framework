#include "Laborator3.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/SPG-Framework/blob/master/Source/Core/World.cpp

Laborator3::Laborator3()
{
}

Laborator3::~Laborator3()
{




	glDeleteTextures(xsize, textures_idX);
	if (volumeData) delete[] volumeData;
	if (textures_idX) delete[] textures_idX;

}

bool Laborator3::loadRAWFile(const string& fileLocation, unsigned int x, unsigned int y, unsigned int z)
{

	FILE* File = NULL;

	if (!fileLocation.c_str())
	{
		return false;
	}

	fopen_s(&File, fileLocation.c_str(), "rb");

	if (!File)
		return false;

	xsize = x;
	ysize = y;
	zsize = z;
	volumeData = new unsigned char[xsize * ysize * zsize];

	int sliceSize = xsize * ysize;

	for (int slice = 0; slice < zsize; slice++)
	{
		fread(&volumeData[slice * ysize * xsize], sizeof(unsigned char), sliceSize, File);

	}

	fclose(File);

	return true;

}

bool Laborator3::load2DTexturesRAW_X(unsigned int* textures_id, unsigned char* volumeData, unsigned int xsize, unsigned int ysize, unsigned int zsize) {


	float* currentSlice;


	currentSlice = new float[ysize * zsize];

	bool Status = false;
	float val;

	if (volumeData)
	{
		Status = true;

		glGenTextures(xsize, &textures_id[0]);

		//OX
		for (int slice = 0; slice < xsize; slice++)
		{
			glBindTexture(GL_TEXTURE_2D, textures_id[slice]);

			//filtrare
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			float maxAnisotropy;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);

			
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			//genereaza textura
			for (int k = 0; k < zsize; k++)
			{
				for (int j = 0; j < ysize; j++)
				{

					currentSlice[k * ysize + j] = ((float)volumeData[k * ysize * xsize + j * xsize + slice]) / 255.0f;
				}
			}
			glTexImage2D(GL_TEXTURE_2D, 0, GL_INTENSITY, ysize, zsize, 0, GL_LUMINANCE, GL_FLOAT, currentSlice);

			//creaza ierarhia de mipmapuri
			glGenerateMipmap(GL_TEXTURE_2D);
		}

	}
	delete[]currentSlice;
	return Status;
}


bool Laborator3::load2DTexturesRAW_Y(unsigned int* textures_id, unsigned char* volumeData, unsigned int xsize, unsigned int ysize, unsigned int zsize) {

	float* currentSlice;


	currentSlice = new float[xsize * zsize];

	bool Status = false;
	float val;
	// Incarca datele din volum
	if (volumeData)
	{
		Status = true;

		glGenTextures(ysize, &textures_id[0]);

		//OY
		for (int slice = 0; slice < ysize; slice++)
		{
			glBindTexture(GL_TEXTURE_2D, textures_id[slice]);

			//filtrare
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			float maxAnisotropy;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);

	
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			//genereaza textura xoz
			for (int k = 0; k < zsize; k++)
			{
				for (int i = 0; i < xsize; i++)
				{

					currentSlice[k * xsize + i] = ((float)volumeData[k * ysize * xsize + slice * xsize + i]) / 255.0f;
				}
			}
			glTexImage2D(GL_TEXTURE_2D, 0, GL_INTENSITY, ysize, zsize, 0, GL_LUMINANCE, GL_FLOAT, currentSlice);

			//creaza ierarhia de mipmapuri
			glGenerateMipmap(GL_TEXTURE_2D);
		}

	}
	delete[]currentSlice;
	return Status;
}



bool Laborator3::load2DTexturesRAW_Z(unsigned int* textures_id, unsigned char* volumeData, unsigned int xsize, unsigned int ysize, unsigned int zsize) {

	float* currentSlice;


	currentSlice = new float[ysize * xsize];

	bool Status = false;
	float val;
	// Incarca datele din volum
	if (volumeData)
	{
		Status = true;

		glGenTextures(ysize, &textures_id[0]);

		//OY
		for (int slice = 0; slice < zsize; slice++)
		{
			glBindTexture(GL_TEXTURE_2D, textures_id[slice]);

			//filtrare
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			float maxAnisotropy;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);

			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			//genereaza textura xo
			for (int k = 0; k < ysize; k++)
			{
				for (int i = 0; i < xsize; i++)
				{

					currentSlice[k * xsize + i] = ((float)volumeData[slice * ysize * xsize + k * xsize + i]) / 255.0f;
				}
			}
			glTexImage2D(GL_TEXTURE_2D, 0, GL_INTENSITY, xsize, ysize, 0, GL_LUMINANCE, GL_FLOAT, currentSlice);

			//creaza ierarhia de mipmapuri
			glGenerateMipmap(GL_TEXTURE_2D);
		}

	}
	delete[]currentSlice;
	return Status;
}

Mesh* Laborator3::createPoligX()
{
	vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(0,-1,-1), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0),glm::vec2(0,0)),
		VertexFormat(glm::vec3(0,1, -1), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0),glm::vec2(1,0)),
		VertexFormat(glm::vec3(0,1, 1), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0),glm::vec2(1,1)),
		VertexFormat(glm::vec3(0,-1, 1), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0),glm::vec2(0,1))
	};
	vector<unsigned int> indices =
	{
		0, 1, 2,
		2, 3, 0
	};

	meshes["poligX"] = new Mesh("poligX");
	meshes["poligX"]->InitFromData(vertices, indices);
	meshes["poligX"]->UseMaterials(false);
	return meshes["poligX"];
}

Mesh* Laborator3::createPoligY()
{
	vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(-1,0,-1), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0),glm::vec2(0,0)),
		VertexFormat(glm::vec3(1,0, -1), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0),glm::vec2(1,0)),
		VertexFormat(glm::vec3(1,0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0),glm::vec2(1,1)),
		VertexFormat(glm::vec3(-1,0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0),glm::vec2(0,1))
	};
	vector<unsigned int> indices =
	{
		0, 1, 2,
		2, 3, 0
	};

	meshes["poligY"] = new Mesh("poligY");
	meshes["poligY"]->InitFromData(vertices, indices);
	meshes["poligY"]->UseMaterials(false);
	return meshes["poligY"];
}



Mesh* Laborator3::createPoligZ()
{
	vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(-1,-1,0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0),glm::vec2(0,0)),
		VertexFormat(glm::vec3(1, -1,0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0),glm::vec2(1,0)),
		VertexFormat(glm::vec3(1, 1,0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0),glm::vec2(1,1)),
		VertexFormat(glm::vec3(-1, 1,0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0),glm::vec2(0,1))
	};
	vector<unsigned int> indices =
	{
		0, 1, 2,
		2, 3, 0
	};

	meshes["poligZ"] = new Mesh("poligZ");
	meshes["poligZ"]->InitFromData(vertices, indices);
	meshes["poligZ"]->UseMaterials(false);
	return meshes["poligZ"];
}





void Laborator3::Init()
{

	ToggleGroundPlane();
	auto camera = GetSceneCamera();
	camera->SetPositionAndRotation(glm::vec3(2, 2, 2), glm::quat(glm::vec3(-30 * TO_RADIANS, 45 * TO_RADIANS, 0)));
	camera->Update();



	{
		loadRAWFile(RESOURCE_PATH::VOLUMES + "engine.raw", 256, 256, 256);
	}

	textures_idZ = new unsigned int[zsize];
	textures_idX = new unsigned int[xsize];
	textures_idY = new unsigned int[ysize];

	load2DTexturesRAW_Z(textures_idZ, volumeData, xsize, ysize, zsize);
	load2DTexturesRAW_Y(textures_idY, volumeData, xsize, ysize, zsize);
	load2DTexturesRAW_X(textures_idX, volumeData, xsize, ysize, zsize);

	createPoligX();
	createPoligY();
	createPoligZ();

	std::string shaderPath = "Source/Laboratoare/Laborator3_VDVAC/Shaders/";

	// Create a shader program for rendering to texture
	{
		Shader* shader = new Shader("MainShader");
		shader->AddShader(shaderPath + "VertexShader.glsl", GL_VERTEX_SHADER);

		shader->AddShader(shaderPath + "FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
}

void Laborator3::FrameStart()
{

}

void Laborator3::DesenStivaAxaYNegativa(unsigned int* textures_id, unsigned int num_polig)
{
	cout << "axa Y negativa" << endl;

	float yPos = -1.0f;
	float pas = 2.0f / (float)num_polig;

	glm::mat4 model_matrix_slice = glm::translate(glm::mat4(1), glm::vec3(0, yPos, 0));


	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	Shader* shader = shaders["MainShader"];
	shader->Use();

	for (int slice = 0; slice < num_polig; slice++)
	{


		unsigned int slice_unitate_texturare = slice;
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures_id[slice]);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
		glUniform1i(glGetUniformLocation(shader->program, "textura1"), 0);

		RenderMesh(meshes["poligY"], shader, model_matrix_slice);
		yPos += pas;
		model_matrix_slice = glm::translate(glm::mat4(1), glm::vec3(0, yPos, 0));

	}
	glDisable(GL_BLEND);
}
void Laborator3::DesenStivaAxaYPozitiva(unsigned int* textures_id, unsigned int num_polig)
{
	cout << "axa Y pozitiva" << endl;
	float yPos = 1.0f;
	float pas = 2.0f / (float)num_polig;

	glm::mat4 model_matrix_slice = glm::translate(glm::mat4(1), glm::vec3(0, yPos, 0));

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	Shader* shader = shaders["MainShader"];
	shader->Use();

	for (int slice = num_polig - 1; slice >= 0; slice--)
	{


		unsigned int slice_unitate_texturare = slice;
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures_id[slice]);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
		glUniform1i(glGetUniformLocation(shader->program, "textura1"), 0);

		RenderMesh(meshes["poligY"], shader, model_matrix_slice);
		yPos -= pas;
		model_matrix_slice = glm::translate(glm::mat4(1), glm::vec3(0, yPos, 0));

	}
	glDisable(GL_BLEND);
}

void Laborator3::DesenStivaAxaZNegativa(unsigned int* textures_id, unsigned int num_polig)
{
	cout << "axa Z negativa" << endl;

	float zPos = -1.0f;
	float pas = 2.0f / (float)num_polig;

	glm::mat4 model_matrix_slice = glm::translate(glm::mat4(1), glm::vec3(0, 0, zPos));

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	Shader* shader = shaders["MainShader"];
	shader->Use();

	for (int slice = 0; slice < num_polig; slice++)
	{


		unsigned int slice_unitate_texturare = slice;
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures_id[slice]);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
		glUniform1i(glGetUniformLocation(shader->program, "textura1"), 0);

		RenderMesh(meshes["poligZ"], shader, model_matrix_slice);
		zPos += pas;
		model_matrix_slice = glm::translate(glm::mat4(1), glm::vec3(0, 0, zPos));

	}
	glDisable(GL_BLEND);
}

void Laborator3::DesenStivaAxaZPozitiva(unsigned int* textures_id, unsigned int num_polig)
{
	cout << "axa Z pozitiva" << endl;
	float zPos = 1.0f;
	float pas = 2.0f / (float)num_polig;

	glm::mat4 model_matrix_slice = glm::translate(glm::mat4(1), glm::vec3(0, 0, zPos));


	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	Shader* shader = shaders["MainShader"];
	shader->Use();

	for (int slice = num_polig - 1; slice >= 0; slice--)
	{


		unsigned int slice_unitate_texturare = slice;
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures_id[slice]);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
		glUniform1i(glGetUniformLocation(shader->program, "textura1"), 0);

		RenderMesh(meshes["poligZ"], shader, model_matrix_slice);
		zPos -= pas;
		model_matrix_slice = glm::translate(glm::mat4(1), glm::vec3(0, 0, zPos));

	}
	glDisable(GL_BLEND);

}


void Laborator3::DesenStivaAxaXNegativa(unsigned int* textures_id, unsigned int num_polig)
{
	cout << "axa X negativa" << endl;
	float xPos = -1.0f;
	float pas = 2.0f / (float)num_polig;

	glm::mat4 model_matrix_slice = glm::translate(glm::mat4(1), glm::vec3(xPos, 0, 0));


	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	Shader* shader = shaders["MainShader"];
	shader->Use();

	for (int slice = 0; slice < num_polig; slice++)
	{


		unsigned int slice_unitate_texturare = slice;
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures_id[slice]);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
		glUniform1i(glGetUniformLocation(shader->program, "textura1"), 0);

		RenderMesh(meshes["poligX"], shader, model_matrix_slice);
		xPos += pas;
		model_matrix_slice = glm::translate(glm::mat4(1), glm::vec3(xPos, 0, 0));

	}
	glDisable(GL_BLEND);
}


void Laborator3::DesenStivaAxaXPozitiva(unsigned int* textures_id, unsigned int num_polig)
{
	cout << "axa X pozitiva" << endl;
	float xPos = 1.0f;
	float pas = 2.0f / (float)num_polig;

	glm::mat4 model_matrix_slice = glm::translate(glm::mat4(1), glm::vec3(xPos, 0, 0));


	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	Shader* shader = shaders["MainShader"];
	shader->Use();

	for (int slice = num_polig - 1; slice >= 0; slice--)
	{


		unsigned int slice_unitate_texturare = slice;
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures_id[slice]);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
		glUniform1i(glGetUniformLocation(shader->program, "textura1"), 0);

		RenderMesh(meshes["poligX"], shader, model_matrix_slice);
		xPos -= pas;
		model_matrix_slice = glm::translate(glm::mat4(1), glm::vec3(xPos, 0, 0));

	}
	glDisable(GL_BLEND);
}

void Laborator3::Update(float deltaTimeSeconds)
{
	ClearScreen();

	{
		auto shader = shaders["MainShader"];

		shader->Use();
		int dir = detMostPerpendicularAxis();
		switch (dir)
		{
		case 1: DesenStivaAxaXNegativa(textures_idX, xsize); break;
		case -1: DesenStivaAxaXPozitiva(textures_idX, xsize); break;
		case 2: DesenStivaAxaYNegativa(textures_idY, xsize); break;
		case -2: DesenStivaAxaYPozitiva(textures_idY, xsize); break;
		case 3: DesenStivaAxaZNegativa(textures_idZ, xsize); break;
		case -3: DesenStivaAxaZPozitiva(textures_idZ, xsize); break;
		default:  DesenStivaAxaXNegativa(textures_idX, xsize); break;
		}



	}
}


int Laborator3::detMostPerpendicularAxis()
{

	auto camera = GetSceneCamera();
	glm::vec3 view_vec = glm::normalize(camera->transform->GetLocalOZVector());
	float cosX = glm::dot(view_vec, glm::vec3(1, 0, 0));
	float cosY = glm::dot(view_vec, glm::vec3(0, 1, 0));
	float cosZ = glm::dot(view_vec, glm::vec3(0, 0, 1));

	float maxValue;
	int axis;

	if (glm::max(glm::abs(cosX), glm::abs(cosY)) == glm::abs(cosX)) {
		maxValue = cosX;
		axis = 1;
	}
	else {
		maxValue = cosY;
		axis = 2;
	}
	if (glm::max(glm::abs(maxValue), glm::abs(cosZ)) == glm::abs(cosZ)) {
		maxValue = cosZ;
		axis = 3;

	}

	if (maxValue < 0) {
		axis *= -1;
	}

	return axis;

}



void Laborator3::FrameEnd()
{
	DrawCoordinatSystem();

}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/SPG-Framework/blob/master/Source/Core/Window/InputController.h

void Laborator3::OnInputUpdate(float deltaTime, int mods)
{
	
};

void Laborator3::OnKeyPress(int key, int mods)
{



};

void Laborator3::OnKeyRelease(int key, int mods)
{
	// add key release event
};

void Laborator3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
};

void Laborator3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Laborator3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Laborator3::OnWindowResize(int width, int height)
{
	// treat window resize event
}
