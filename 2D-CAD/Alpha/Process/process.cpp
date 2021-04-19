
#include <vector>
#include <iostream>


/*Process::Process()
{
	vtx3d.clear();  
	nom.clear(); 
	mouse_nom.clear(); 
	color.clear(); 
	surface.clear();
}*/


std::vector <float> Process::GetSameNormals(std::vector <float> vtx, std::vector <float> nom,
									std::vector <float> mouse_nom)//Input: Vertices, normals, and mouse clicked triangle normal 
{
	//reset color
	color.clear();
	surface.clear();
	
	//Find all triangles with same NX NY NZ
	int NumVtc = nom.size();
	//Initialize the vector to store all triangles with the same normal
	std::vector <float> surface;
	for (int i = 0; i < NumVtc; i+=9)//not the end of vector?
	{
		//Compare all normals to be less than epsilon value
		if (abs(mouse_nom[0] - nom[i]  ) < 0.01 && abs(mouse_nom[1] - nom[i+1]) < 0.01 && abs(mouse_nom[2] - nom[i+2]) < 0.01)
		{
			//store triangles vertices in surface vector 
			surface.push_back(vtx[i]); surface.push_back(vtx[i+1]);surface.push_back(vtx[i+2]);
			surface.push_back(vtx[i+3]); surface.push_back(vtx[i + 4]); surface.push_back(vtx[i + 5]);
			surface.push_back(vtx[i+6]); surface.push_back(vtx[i + 7]); surface.push_back(vtx[i + 8]);

			//****Set up color??************
			//give new color
			color.push_back(0); color.push_back(1); color.push_back(0);
			color.push_back(0); color.push_back(1); color.push_back(0);
			color.push_back(0); color.push_back(1); color.push_back(0);
		}
		else
		{
			//color for other normals
			color.push_back(0); color.push_back(0); color.push_back(1);
			color.push_back(0); color.push_back(0); color.push_back(1);
			color.push_back(0); color.push_back(0); color.push_back(1);
		}

	}
	printf("Surface vertices: \n");
	for (int i = 0; i < surface.size(); i+=3)
	{
		printf("(X,Y,Z) = (%f, %f, %f)\n", surface[i], surface[i + 1], surface[i + 2]);
	}
	printf("\n");
	GetShape(surface);
	
	return surface;
}

bool Process::Compare_Vectors(std::vector<float> vtx1, std::vector<float> vtx2,
	                 std::vector<float> surface, int NumTri, int Indx)
{
	printf("Vector from (%f, %f, %f) to (%f, %f, %f)\n", vtx1[0], vtx1[1], vtx1[2], vtx2[0], vtx2[1], vtx2[2]);
	float vctx = vtx1[0] - vtx2[0];
	float vcty = vtx1[1] - vtx2[1];
	float vctz = vtx1[2] - vtx2[2];
	float vct1_x, vct1_y, vct1_z, vct2_x, vct2_y, vct2_z, vct3_x , vct3_y, vct3_z;
	int count = 0;

	printf("vec_xyz = (%f, %f, %f)\n", vctx, vcty, vctz);
	

	for (int j = 0; j < NumTri; j+=9)
	{
		//add check to not compare the same triangle
		if (j != Indx)
		{
			//Create vectors with triangle vertices 
			vct1_x = surface[j]     - surface[j + 3];
			vct1_y = surface[j + 1] - surface[j + 4];
			vct1_z = surface[j + 2] - surface[j + 5];

			vct2_x = surface[j + 3] - surface[j + 6];
			vct2_y = surface[j + 4] - surface[j + 7];
			vct2_z = surface[j + 5] - surface[j + 8];

			vct3_x = surface[j + 6] - surface[j];
			vct3_y = surface[j + 7] - surface[j + 1];
			vct3_z = surface[j + 8] - surface[j + 2];

			printf("vec_1 = (%f, %f, %f)\n", vct1_x, vct1_y, vct1_z);
			printf("vec_2 = (%f, %f, %f)\n", vct2_x, vct2_y, vct2_z);
			printf("vec_3 = (%f, %f, %f)\n", vct3_x, vct3_y, vct3_z);
			//Compare all triangle vectors with calculated vectors 
			if (vctx ==  vct1_x && vcty ==  vct1_y && vctz ==  vct1_z )
			{
				//If the same vector in equal or opposite direction exist return false
				if (vtx1[0] == surface[j] && vtx1[1] == surface[j + 1] && vtx1[2] == surface[j + 2])
				{
					printf("False on 1.1\n");
					return false;
				}
				if (vtx1[0] == surface[j + 3] && vtx1[1] == surface[j + 4] && vtx1[2] == surface[j + 5])
				{
					printf("False on 1.2\n");
					return false;
				}

			}
			else if (vctx == vct2_x && vcty == vct2_y && vctz == vct2_z)
			{
				//If the same vector in equal or opposite direction exist return false
				if (vtx1[0] == surface[j + 3] && vtx1[1] == surface[j + 4] && vtx1[2] == surface[j + 5])
				{
					printf("False on 2.1\n");
					return false;
				}
				if (vtx1[0] == surface[j + 6] && vtx1[1] == surface[j + 7] && vtx1[2] == surface[j + 8])
				{
					printf("False on 2.2\n");
					return false;
				}

			}
			else if (vctx == vct3_x && vcty == vct3_y && vctz == vct3_z )
			{
				//If the same vector in equal or opposite direction exist return false
				if (vtx1[0] == surface[j + 6] && vtx1[1] == surface[j + 7] && vtx1[2] == surface[j + 8])
				{
					printf("False on 3.1\n");
					return false;
				}
				if (vtx1[0] == surface[j + 0] && vtx1[1] == surface[j + 1] && vtx1[2] == surface[j + 2])
				{
					printf("False on 3.2\n");
					return false;
				}
				
			}
			else if (vctx == -vct1_x && vcty == -vct1_y && vctz == -vct1_z )
			{
				//If the same vector in equal or opposite direction exist return false
				
				if (vtx1[0] == surface[j] && vtx1[1] == surface[j + 1] && vtx1[2] == surface[j + 2])
				{printf("False on 4.1\n");
					return false;
				}
				if (vtx1[0] == surface[j + 3] && vtx1[1] == surface[j + 4] && vtx1[2] == surface[j + 5])
				{
					printf("False on 4.2\n");
					return false;
				}
					
	
			}
			else if (vctx == -vct2_x && vcty == -vct2_y && vctz == -vct2_z )
			{
				//If the same vector in equal or opposite direction exist return false
				if (vtx1[0] == surface[j+3] && vtx1[1] == surface[j + 4] && vtx1[2] == surface[j + 5])
				{
					printf("False on 5.1\n");
					return false;
				}
				if (vtx1[0] == surface[j + 6] && vtx1[1] == surface[j + 7] && vtx1[2] == surface[j + 8])
				{
					printf("False on 5.2\n");
					return false;
				}

			}
			else if (vctx == -vct3_x && vcty == -vct3_y && vctz == -vct3_z)
			{
				//If the same vector in equal or opposite direction exist return false
				if (vtx1[0] == surface[j + 6] && vtx1[1] == surface[j + 7] && vtx1[2] == surface[j + 8])
				{
					printf("False on 6.1\n");
					return false;
				}
				if (vtx1[0] == surface[j + 0] && vtx1[1] == surface[j + 1] && vtx1[2] == surface[j + 2])
				{
					printf("False on 6.2\n");
					return false;
				}
				
			}
		}
	}

	return true;//Return true if the given vertices create a unique vector on the surface
}

std::vector <float>  Process::GetShape(std::vector <float> surface)//Get unique vectors of Same Normals
{
	//Initialize 2D Shape Vector
	twoDvtx.clear();
	std::vector <float> vec1, vec2, vec3;
	vec1.push_back(0.0); vec1.push_back(0.0); vec1.push_back(0.0);
	vec2.push_back(0.0); vec2.push_back(0.0); vec2.push_back(0.0);
	vec3.push_back(0.0); vec3.push_back(0.0); vec3.push_back(0.0);
	//********Need to differetiate which 2D vectors to store here
	int NumTri = surface.size();

	//for all triangles

	for (int i = 0; i < NumTri; i+=9)
	{
		vec1[0] = surface[i];     vec1[1] = surface[i + 1]; vec1[2] = surface[i + 2];
		vec2[0] = surface[i + 3]; vec2[1] = surface[i + 4]; vec2[2] = surface[i + 5];
		vec3[0] = surface[i + 6]; vec3[1] = surface[i + 7]; vec3[2] = surface[i + 8];

		printf("vec1 = (%f, %f, %f)\n", vec1[0], vec1[1], vec1[2]);
		printf("vec2 = (%f, %f, %f)\n", vec2[0], vec2[1], vec2[2]);
		printf("vec3 = (%f, %f, %f)\n", vec3[0], vec3[1], vec3[2]);
		
		if (true == Compare_Vectors(vec1, vec2, surface, NumTri, i))
		{
			//store unique vector
			printf("True on first\n");
			twoDvtx.push_back(vec1[0]); twoDvtx.push_back(vec1[1]); twoDvtx.push_back(vec1[2]);
			twoDvtx.push_back(vec2[0]); twoDvtx.push_back(vec2[1]); twoDvtx.push_back(vec2[2]);

		}
		if (true == Compare_Vectors(vec2, vec3, surface, NumTri, i))
		{
			//store unique vector
			printf("True on second\n");
			twoDvtx.push_back(vec2[0]); twoDvtx.push_back(vec2[1]); twoDvtx.push_back(vec2[2]);
			twoDvtx.push_back(vec3[0]); twoDvtx.push_back(vec3[1]); twoDvtx.push_back(vec3[2]);
		}
		if (true == Compare_Vectors(vec1, vec3, surface, NumTri, i))
		{
			//store unique vector
			printf("True on third\n");
			twoDvtx.push_back(vec1[0]); twoDvtx.push_back(vec1[1]); twoDvtx.push_back(vec1[2]);
			twoDvtx.push_back(vec3[0]); twoDvtx.push_back(vec3[1]); twoDvtx.push_back(vec3[2]);
		}
	}

	printf("2D Vtx: Size = %d\n", twoDvtx.size());
	for (int i = 0; i < twoDvtx.size(); i += 3)
	{
		printf("(X,Y,Z) = (%f, %f, %f)\n", twoDvtx[i], twoDvtx[i + 1], twoDvtx[i + 2]);
	}
	printf("\n");
	return twoDvtx;
}

/*int main()//int argc,char *argv[])
{
	//FsOpenWindow(0,0,800,600,1);
	Process app;//argc,argv);
	
	//app.ApplicationMain();
	/*while(true!=app.MustTerminate())
	{
		FsPollDevice();
		app.RunOneStep();
		app.Draw();
	}
	return 0;
}
//bottom
	/*vtx.push_back(0); vtx.push_back(0); vtx.push_back(0);
	vtx.push_back(1); vtx.push_back(1); vtx.push_back(0);
	vtx.push_back(1); vtx.push_back(0); vtx.push_back(0);

	vtx.push_back(0); vtx.push_back(0); vtx.push_back(0);
	vtx.push_back(0); vtx.push_back(1); vtx.push_back(0);
	vtx.push_back(1); vtx.push_back(1); vtx.push_back(0);

	nom.push_back(0); nom.push_back(0); nom.push_back(-1);
	nom.push_back(0); nom.push_back(0); nom.push_back(-1);
	nom.push_back(0); nom.push_back(0); nom.push_back(-1);

	nom.push_back(0); nom.push_back(0); nom.push_back(-1);
	nom.push_back(0); nom.push_back(0); nom.push_back(-1);
	nom.push_back(0); nom.push_back(0); nom.push_back(-1);

	//top
	vtx.push_back(0); vtx.push_back(0); vtx.push_back(1);
	vtx.push_back(1); vtx.push_back(0); vtx.push_back(1);
	vtx.push_back(1); vtx.push_back(1); vtx.push_back(1);

	vtx.push_back(0); vtx.push_back(0); vtx.push_back(1);
	vtx.push_back(1); vtx.push_back(1); vtx.push_back(1);
	vtx.push_back(0); vtx.push_back(1); vtx.push_back(1);

	nom.push_back(0); nom.push_back(0); nom.push_back(1);
	nom.push_back(0); nom.push_back(0); nom.push_back(1);
	nom.push_back(0); nom.push_back(0); nom.push_back(1);

	nom.push_back(0); nom.push_back(0); nom.push_back(1);
	nom.push_back(0); nom.push_back(0); nom.push_back(1);
	nom.push_back(0); nom.push_back(0); nom.push_back(1);

	//side 000 100
	vtx.push_back(0); vtx.push_back(0); vtx.push_back(0);
	vtx.push_back(1); vtx.push_back(0); vtx.push_back(0);
	vtx.push_back(0); vtx.push_back(0); vtx.push_back(1);

	vtx.push_back(1); vtx.push_back(0); vtx.push_back(0);
	vtx.push_back(1); vtx.push_back(0); vtx.push_back(1);
	vtx.push_back(0); vtx.push_back(0); vtx.push_back(1);

	nom.push_back(0); nom.push_back(-1); nom.push_back(0);
	nom.push_back(0); nom.push_back(-1); nom.push_back(0);
	nom.push_back(0); nom.push_back(-1); nom.push_back(0);

	nom.push_back(0); nom.push_back(-1); nom.push_back(0);
	nom.push_back(0); nom.push_back(-1); nom.push_back(0);
	nom.push_back(0); nom.push_back(-1); nom.push_back(0);

	//side 100 110
	vtx.push_back(1); vtx.push_back(0); vtx.push_back(0);
	vtx.push_back(1); vtx.push_back(1); vtx.push_back(0);
	vtx.push_back(1); vtx.push_back(0); vtx.push_back(1);

	vtx.push_back(1); vtx.push_back(1); vtx.push_back(0);
	vtx.push_back(1); vtx.push_back(1); vtx.push_back(1);
	vtx.push_back(1); vtx.push_back(0); vtx.push_back(1);

	nom.push_back(1); nom.push_back(0); nom.push_back(0);
	nom.push_back(1); nom.push_back(0); nom.push_back(0);
	nom.push_back(1); nom.push_back(0); nom.push_back(0);

	nom.push_back(1); nom.push_back(0); nom.push_back(0);
	nom.push_back(1); nom.push_back(0); nom.push_back(0);
	nom.push_back(1); nom.push_back(0); nom.push_back(0);

	//side  110 010
	vtx.push_back(1); vtx.push_back(1); vtx.push_back(0);
	vtx.push_back(0); vtx.push_back(1); vtx.push_back(0);
	vtx.push_back(1); vtx.push_back(1); vtx.push_back(1);

	vtx.push_back(0); vtx.push_back(1); vtx.push_back(0);
	vtx.push_back(0); vtx.push_back(1); vtx.push_back(1);
	vtx.push_back(1); vtx.push_back(1); vtx.push_back(1);

	nom.push_back(0); nom.push_back(1); nom.push_back(0);
	nom.push_back(0); nom.push_back(1); nom.push_back(0);
	nom.push_back(0); nom.push_back(1); nom.push_back(0);

	nom.push_back(0); nom.push_back(1); nom.push_back(0);
	nom.push_back(0); nom.push_back(1); nom.push_back(0);
	nom.push_back(0); nom.push_back(1); nom.push_back(0);

	//side 000 010
	vtx.push_back(0); vtx.push_back(0); vtx.push_back(0);
	vtx.push_back(0); vtx.push_back(1); vtx.push_back(1);
	vtx.push_back(0); vtx.push_back(1); vtx.push_back(0);

	vtx.push_back(0); vtx.push_back(0); vtx.push_back(0);
	vtx.push_back(0); vtx.push_back(0); vtx.push_back(1);
	vtx.push_back(0); vtx.push_back(1); vtx.push_back(1);

	nom.push_back(-1); nom.push_back(0); nom.push_back(0);
	nom.push_back(-1); nom.push_back(0); nom.push_back(0);
	nom.push_back(-1); nom.push_back(0); nom.push_back(0);

	nom.push_back(-1); nom.push_back(0); nom.push_back(0);
	nom.push_back(-1); nom.push_back(0); nom.push_back(0);
	nom.push_back(-1); nom.push_back(0); nom.push_back(0);


	//mouse selected

	/*mouse_nom.push_back(0); mouse_nom.push_back(0); mouse_nom.push_back(1);
	mouse_nom.push_back(0); mouse_nom.push_back(0); mouse_nom.push_back(1);
	mouse_nom.push_back(0); mouse_nom.push_back(0); mouse_nom.push_back(1);

	mouse_nom.push_back(1); mouse_nom.push_back(0); mouse_nom.push_back(0);
	mouse_nom.push_back(1); mouse_nom.push_back(0); mouse_nom.push_back(0);
	mouse_nom.push_back(1); mouse_nom.push_back(0); mouse_nom.push_back(0);
	//LoadSTL(argv[1]);
	GetSameNormals(vtx, nom, mouse_nom); */
