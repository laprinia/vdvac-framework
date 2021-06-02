#pragma once
#include <math.h>
#include <vector>
#include <Component/SimpleScene.h>
#include <iostream>


using namespace std;
namespace FFD
{

	float BernsteinPoly(int i, float u)
	{
		switch (i) {
		case 0: return pow(1 - u, 3);
		case 1: return 3 * u * pow(1 - u, 2);
		case 2: return 3 * u * u * (1 - u);
		case 3: return pow(u, 3);
		}

		return 0;
	}

	void CreateBernsteinCoefficients(std::vector<float>& coefficients, std::vector<glm::vec3> vertices)
	{

		int offset = 0;
		for (int vertex = 0; vertex < vertices.size(); vertex++)
		{
			for (int k = 0; k <= 3; k++)
			{

				for (int j = 0; j <= 3; j++)
				{

					for (int i = 0; i <= 3; i++)
					{
						coefficients[offset] = BernsteinPoly(i, vertices[vertex].x) * BernsteinPoly(j, vertices[vertex].y) * BernsteinPoly(k, vertices[vertex].z);
						offset++;
					}
				}
			}
		}

	}



	void InitControlPoints(std::vector<glm::vec3>& control_points)
	{
		int i, j, k, offset;
		offset = 0;
		for (k = 0; k <= 3; k++)
		{
			for (j = 0; j <= 3; j++)
			{
				for (i = 0; i <= 3; i++)
				{

					control_points[offset] = glm::vec3(k / 3, j / 3, i / 3); 

					offset++;
				}
			}
		}

	}

	void ComputeVerticesPosition(std::vector<glm::vec3> control_points, std::vector<float> coefficients, std::vector<glm::vec3>& vertices)
	{

		for (int vertex = 0; vertex < vertices.size(); vertex++)
		{
			vertices[vertex].x = 0;
			vertices[vertex].y = 0;
			vertices[vertex].z = 0;

			int offset = 0;
			for (int k = 0; k <= 3; k++)
			{
				for (int j = 0; j <= 3; j++)
				{
					for (int i = 0; i <= 3; i++)
					{

						
						vertices[vertex] += control_points[offset] * coefficients[vertex * 64 + offset];
						offset++;
					}
				}
			}
		}

	}

	void ComputeNewControlPointsPositions(std::vector<glm::vec3>& control_points)
	{
		int i, j, k, offset;
		offset = 0;
		for (k = 0; k <= 3; k++)
		{
			for (j = 0; j <= 3; j++)
			{
				for (i = 0; i <= 3; i++)
				{
					control_points[offset].x = (float)i / 3.0f + (rand() - (signed)RAND_MAX / 2) / (3.0f * RAND_MAX);
					control_points[offset].y = (float)j / 3.0f + (rand() - (signed)RAND_MAX / 2) / (3.0f * RAND_MAX);
					control_points[offset].z = (float)k / 3.0f + (rand() - (signed)RAND_MAX / 2) / (3.0f * RAND_MAX);
					offset++;
				}
			}
		}
	}


	void AnimateControlPointPositions(std::vector<glm::vec3>& control_points1, std::vector<glm::vec3>& control_points2, std::vector<glm::vec3>& control_points, int frame, int no_frames)
	{

		if (frame == 0)
		{
			for (int offset = 0; offset < 64; offset++)
			{
				control_points1[offset] = control_points2[offset];
			}


			ComputeNewControlPointsPositions(control_points2);
		}

		for (int offset = 0; offset < 64; offset++)
		{
			control_points[offset].x = ((float)frame * control_points2[offset].x + (no_frames - (float)frame) * control_points1[offset].x) / (float)no_frames;
			control_points[offset].y = ((float)frame * control_points2[offset].y + (no_frames - (float)frame) * control_points1[offset].y) / (float)no_frames;
			control_points[offset].z = ((float)frame * control_points2[offset].z + (no_frames - (float)frame) * control_points1[offset].z) / (float)no_frames;

		}

	}



}

