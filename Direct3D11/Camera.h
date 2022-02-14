#pragma once
#include <d3d9.h>

class Camera
{
public:
	INT init(UINT screenwidth, UINT screenheight);
	void render(IDirect3DDevice9* pD3DDevice);
	void deInit();

private:
	D3DMATRIX _viewMatrix = {}; // view transofrmation matrix
	D3DMATRIX _projectionMatrix = {}; // projection matrix

};
