#include <Windows.h>
#include <random>
#include "Window.h"
#include "D3D.h"
#include "Utils.h"
#include "Mesh.h"
#include "Camera.h"
#include "Time.h"
#include "Material.h"
#include "Light.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR szCmdLine, _In_ int nCmdShow)
{
	INT  error = 0;
	UINT width = 1080;
	UINT height = 720;
	BOOL isFullscreen = FALSE;

	// 1 - create window 
	Window window = {};
	error = window.init(hInstance, width, height);
	CheckError(error);

	// 2 - set up connection to Direct3D 9
	D3D d3d = {};
	error = d3d.init(window.getWindowHandle(), width, height, isFullscreen);
	CheckError(error);

	////d3d.getDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//d3d.getDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	//d3d.getDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//d3d.getDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);
	//d3d.getDevice()->SetRenderState(D3DRS_COLORVERTEX, FALSE);
	//d3d.getDevice()->SetRenderState(D3DRS_SPECULARENABLE, TRUE);

	// 3 - create mesh/object
	Mesh mesh = {};
	error = mesh.init(d3d.getDevice());
	CheckError(error);

	//// 4 - create camera
	//Camera camera = {};
	//error = camera.init(width, height);
	//CheckError(error);

	// 5 - set up time
	Time time = {};
	error = time.init();
	CheckError(error);

	//// 6 - create material
	//Material material = {};
	//material.init(d3d.getDevice(), TEXT("Resources/Wall.jpg"));
	//CheckError(error);

	//// 7 create light 
	//D3DLIGHT9 lightData = {};
	//lightData.Type = D3DLIGHT_POINT;
	////lightData.Direction = { -1.0f, -1.0f, 1.0f };
	//lightData.Position = { 0.0f, 0.0f, -1.0f };
	//lightData.Ambient   = { 0.2f, 0.2f, 0.2f, 1.0f };
	//lightData.Diffuse   = { 1.0f, 1.0f, 1.0f, 1.0f };
	//lightData.Specular  = { 1.0f, 1.0f, 1.0f, 1.0f };
	//lightData.Range = 10.0f;
	//// attenuation equasion = a0 + a1 * distance + * distance * distance (there are also different approaches, it is possible to write your own formulas)
	//lightData.Attenuation0 = 1.0f;  // CONSTANT
	//lightData.Attenuation1 = 0.1f;  // LINEAR
	//lightData.Attenuation2 = 0.01f; // QUADRATIC

	//Light light = {};
	//error = light.init(lightData);
	//CheckError(error)

	// 8 - run application
	while (window.run())
	{
		// 8.1 update the objects
		time.update();
		//mesh.update(time.getDeltaTime());


	//	// 8.2 draw the objects

	d3d.beginScene(1.0f, 0.0f, 1.0f);

	//	camera.render(d3d.getDevice());
	//	material.render(d3d.getDevice());
	//	light.render(d3d.getDevice());
		mesh.render(d3d.getDeviceContext());

	d3d.endScene();

	}

	//// 9 - tidy up memory
	//light.deInit();
	//material.deInit();
	time.deInit();
	//camera.deInit();
	mesh.deInit();
	d3d.deInit();
	window.deInit();

	return 0;
}