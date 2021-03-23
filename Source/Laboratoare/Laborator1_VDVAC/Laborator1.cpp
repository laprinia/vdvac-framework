#include "Laborator1.h"
#include "LookupTables.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

using namespace std;
float epsilon = 0.0001;

// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/SPG-Framework/blob/master/Source/Core/World.cpp

Laborator1::Laborator1()
{
}

Laborator1::~Laborator1()
{
	//distruge obiecte

	if (volumeData) delete[] volumeData;
	if (tri) delete[] tri;
}

bool Laborator1::loadRAWFile(const string& fileLocation, unsigned int x, unsigned int y, unsigned int z)
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

glm::vec3 Laborator1::VertexInterp(double isolevel, glm::vec3 p1, glm::vec3 p2, double valp1, double valp2)
{
	double mu;
	glm::vec3 p;

	if (abs(isolevel - valp1) < epsilon)
		return(p1);
	if (abs(isolevel - valp2) < epsilon)
		return(p2);
	if (abs(valp1 - valp2) < epsilon)
		return(p1);
	mu = (isolevel - valp1) / (valp2 - valp1);
	p.x = p1.x + mu * (p2.x - p1.x);
	p.y = p1.y + mu * (p2.y - p1.y);
	p.z = p1.z + mu * (p2.z - p1.z);

	return(p);
}


int Laborator1::PolygoniseCube(GRIDCELL g, double iso, TRIANGLE* tri) {

	int i, ntri = 0;
	int cubeindex;
	glm::vec3 vertlist[12];
	glm::vec3 normlist[12];
	glm::vec3 normal1, normal2, normal3;

	/*
	Determine the index into the edge table which
	tells us which vertices are inside of the surface
	*/
	cubeindex = 0;
	if (g.val[0] < iso) cubeindex |= 1;
	if (g.val[1] < iso) cubeindex |= 2;
	if (g.val[2] < iso) cubeindex |= 4;
	if (g.val[3] < iso) cubeindex |= 8;
	if (g.val[4] < iso) cubeindex |= 16;
	if (g.val[5] < iso) cubeindex |= 32;
	if (g.val[6] < iso) cubeindex |= 64;
	if (g.val[7] < iso) cubeindex |= 128;

	/* Cube is entirely in/out of the surface */
	if (edgeTable[cubeindex] == 0)
		return(0);

	/* Find the vertices where the surface intersects the cube */
	if (edgeTable[cubeindex] & 1) {
		vertlist[0] = VertexInterp(iso, g.p[0], g.p[1], g.val[0], g.val[1]);
		normlist[0] = VertexInterp(iso, g.n[0], g.n[1], g.val[0], g.val[1]);


	}
	if (edgeTable[cubeindex] & 2) {
		vertlist[1] = VertexInterp(iso, g.p[1], g.p[2], g.val[1], g.val[2]);
		normlist[1] = VertexInterp(iso, g.n[1], g.n[2], g.val[1], g.val[2]);

	}
	if (edgeTable[cubeindex] & 4) {
		vertlist[2] = VertexInterp(iso, g.p[2], g.p[3], g.val[2], g.val[3]);
		normlist[2] = VertexInterp(iso, g.n[2], g.n[3], g.val[2], g.val[3]);

	}
	if (edgeTable[cubeindex] & 8) {
		vertlist[3] = VertexInterp(iso, g.p[3], g.p[0], g.val[3], g.val[0]);
		normlist[3] = VertexInterp(iso, g.n[3], g.n[0], g.val[3], g.val[0]);

	}
	if (edgeTable[cubeindex] & 16) {
		vertlist[4] = VertexInterp(iso, g.p[4], g.p[5], g.val[4], g.val[5]);
		normlist[4] = VertexInterp(iso, g.n[4], g.n[5], g.val[4], g.val[5]);

	}
	if (edgeTable[cubeindex] & 32) {
		vertlist[5] = VertexInterp(iso, g.p[5], g.p[6], g.val[5], g.val[6]);
		normlist[5] = VertexInterp(iso, g.n[5], g.n[6], g.val[5], g.val[6]);

	}
	if (edgeTable[cubeindex] & 64) {
		vertlist[6] = VertexInterp(iso, g.p[6], g.p[7], g.val[6], g.val[7]);
		normlist[6] = VertexInterp(iso, g.n[6], g.n[7], g.val[6], g.val[7]);

	}
	if (edgeTable[cubeindex] & 128) {
		vertlist[7] = VertexInterp(iso, g.p[7], g.p[4], g.val[7], g.val[4]);
		normlist[7] = VertexInterp(iso, g.n[7], g.n[4], g.val[7], g.val[4]);

	}
	if (edgeTable[cubeindex] & 256) {
		vertlist[8] = VertexInterp(iso, g.p[0], g.p[4], g.val[0], g.val[4]);
		normlist[8] = VertexInterp(iso, g.n[0], g.n[4], g.val[0], g.val[4]);

	}
	if (edgeTable[cubeindex] & 512) {
		vertlist[9] = VertexInterp(iso, g.p[1], g.p[5], g.val[1], g.val[5]);
		normlist[9] = VertexInterp(iso, g.n[1], g.n[5], g.val[1], g.val[5]);

	}
	if (edgeTable[cubeindex] & 1024) {
		vertlist[10] = VertexInterp(iso, g.p[2], g.p[6], g.val[2], g.val[6]);
		normlist[10] = VertexInterp(iso, g.n[2], g.n[6], g.val[2], g.val[6]);

	}
	if (edgeTable[cubeindex] & 2048) {
		vertlist[11] = VertexInterp(iso, g.p[3], g.p[7], g.val[3], g.val[7]);
		normlist[11] = VertexInterp(iso, g.n[3], g.n[7], g.val[3], g.val[7]);
	}

	/* Create the triangles */
	for (i = 0; triTable[cubeindex][i] != -1; i += 3) {
		tri[ntri].p[0] = vertlist[triTable[cubeindex][i]];
		tri[ntri].p[1] = vertlist[triTable[cubeindex][i + 1]];
		tri[ntri].p[2] = vertlist[triTable[cubeindex][i + 2]];

		glm::vec3 n1 = normlist[triTable[cubeindex][i]];
		glm::vec3 n2 = normlist[triTable[cubeindex][i + 1]];
		glm::vec3 n3 = normlist[triTable[cubeindex][i + 2]];

		if (glm::length(n1) > epsilon)
			n1 = glm::normalize(n1);
		if (glm::length(n2) > epsilon)
			n2 = glm::normalize(n2);
		if (glm::length(n3) > epsilon)
			n3 = glm::normalize(n3);

		tri[ntri].n[0] = n1;
		tri[ntri].n[1] = n2;
		tri[ntri].n[2] = n3;

		ntri++;
	}

	return(ntri);

}


void Laborator1::reconstructSurface(Mesh* mesh)
{


	GRIDCELL grid;
	TRIANGLE triangles[10];

	int ntri = 0;

	int i, j, k, n, l, vPoint;
	int x, y, z;
	int frontX, backX, frontY, backY, frontZ, backZ;
	glm::vec3 normal;
	for (i = 0; i < xsize - 1; i++)
	{
		for (j = 0; j < ysize - 1; j++)
		{
			for (k = 0; k < zsize - 1; k++)
			{
				for (vPoint = 0; vPoint < 8; vPoint++) {
					if (vPoint == 0 || vPoint == 3 || vPoint == 4 || vPoint == 7)
					{
						x = i;
					}
					else {
						x = i + 1;
					}
					if (vPoint == 0 || vPoint == 1 || vPoint == 5 || vPoint == 4)
					{
						y = j;
					}
					else {
						y = j + 1;
					}
					if (vPoint == 0 || vPoint == 1 || vPoint == 2 || vPoint == 3)
					{
						z = k;
					}
					else {
						z = k + 1;
					}
					frontX = x + 1; frontY = y + 1; frontZ = z + 1;
					backX = x - 1; backY = y - 1; backZ = z - 1;
					if (frontX > xsize - 1) frontX = xsize - 1;
					if (frontY > ysize - 1) frontY = ysize - 1;
					if (frontZ > zsize - 1) frontZ = zsize - 1;

					if (backX < 0) backX = 0;
					if (backY < 0) backY = 0;
					if (backZ < 0) backZ = 0;


					grid.p[vPoint] = glm::vec3(x, y, z);
					grid.val[vPoint] = volumeData[z * xsize * ysize + y * xsize + x];
					normal = glm::vec3(volumeData[z * xsize * ysize + y * xsize + frontX] - volumeData[z * xsize * ysize + y * xsize + backX],
						volumeData[z * xsize * ysize + frontY * xsize + x] - volumeData[z * xsize * ysize + backY * xsize + x],
						volumeData[frontZ * xsize * ysize + y * xsize + x] - volumeData[backZ * xsize * ysize + y * xsize + x]);

					if (glm::length(normal) > epsilon) {
						normal = glm::normalize(normal);
					}
					grid.n[vPoint] = normal;

				}



				n = PolygoniseCube(grid, isolevel, triangles);

				tri = (TRIANGLE*)realloc(tri, (ntri + n) * sizeof(TRIANGLE));
				for (l = 0; l < n; l++)
					tri[ntri + l] = triangles[l];
				ntri += n;
			}
		}
	}



	vector<glm::vec3> positions;
	vector<glm::vec3> normals;
	vector<unsigned int> indices;
	for (i = 0; i < ntri; i++)
	{
		positions.push_back(glm::vec3(tri[i].p[0].x, tri[i].p[0].y, tri[i].p[0].z));
		positions.push_back(glm::vec3(tri[i].p[1].x, tri[i].p[1].y, tri[i].p[1].z));
		positions.push_back(glm::vec3(tri[i].p[2].x, tri[i].p[2].y, tri[i].p[2].z));

		normals.push_back(glm::vec3(tri[i].n[0].x, tri[i].n[0].y, tri[i].n[0].z));
		normals.push_back(glm::vec3(tri[i].n[1].x, tri[i].n[1].y, tri[i].n[1].z));
		normals.push_back(glm::vec3(tri[i].n[2].x, tri[i].n[2].y, tri[i].n[2].z));

		indices.push_back(i * 3);
		indices.push_back(i * 3 + 1);
		indices.push_back(i * 3 + 2);

	}

	mesh->InitFromData(positions, normals, indices);

}


void Laborator1::Init()
{

	tri = NULL;

	auto camera = GetSceneCamera();
	camera->SetPositionAndRotation(glm::vec3(2, 5, 10), glm::quat(glm::vec3(-30 * TO_RADIANS, 0, 0)));
	camera->Update();

	// Load a mesh from file into GPU memory
	{
		loadRAWFile(RESOURCE_PATH::VOLUMES + "Bucky.raw", 32, 32, 32);
		isolevel = 100;
		Mesh* mesh_volume = new Mesh("volume");
		reconstructSurface(mesh_volume);
		meshes[mesh_volume->GetMeshID()] = mesh_volume;
	}

	std::string shaderPath = "Source/Laboratoare/Laborator1_VDVAC/Shaders/";

	// Create a shader program for rendering to texture
	{
		Shader* shader = new Shader("MainShader");
		shader->AddShader(shaderPath + "VertexShader.glsl", GL_VERTEX_SHADER);

		shader->AddShader(shaderPath + "FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
}

void Laborator1::FrameStart()
{

}

void Laborator1::Update(float deltaTimeSeconds)
{
	ClearScreen();

	{
		auto shader = shaders["MainShader"];

		shader->Use();

		RenderMesh(meshes["volume"], shaders["MainShader"], glm::vec3(0, 0, 0), glm::vec3(5.0f / xsize));
	}
}

void Laborator1::FrameEnd()
{
	DrawCoordinatSystem();
}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/SPG-Framework/blob/master/Source/Core/Window/InputController.h

void Laborator1::OnInputUpdate(float deltaTime, int mods)
{
	//TODO schimba isovaloarea 
	if (window->KeyHold(GLFW_KEY_Z) && isolevel < 200) {
		isolevel += 2;
		Laborator1::reconstructSurface(meshes["volume"]);
	}
	else if (window->KeyHold(GLFW_KEY_X) && isolevel > 2) {
		isolevel -= 2;
		Laborator1::reconstructSurface(meshes["volume"]);
	}
};

void Laborator1::OnKeyPress(int key, int mods)
{



};

void Laborator1::OnKeyRelease(int key, int mods)
{
	// add key release event
};

void Laborator1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
};

void Laborator1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Laborator1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Laborator1::OnWindowResize(int width, int height)
{
	// treat window resize event
}
