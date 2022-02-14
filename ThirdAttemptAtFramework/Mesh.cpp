#include "Mesh.h"
#include "Utils.h"
#include "Vertex.h"
#include <DirectXMath.h>

using namespace DirectX;

INT Mesh::init(IDirect3DDevice9* pD3DDevice)
{
	INT error = initVertexBuffer(pD3DDevice);
	CheckError(error);

	error = initIndexBuffer(pD3DDevice);
	CheckError(error);

	XMMATRIX identity = XMMatrixIdentity();
	XMFLOAT4X4 worldMatrix = {};
	XMStoreFloat4x4(&worldMatrix, identity);
	_worldMatrix = *reinterpret_cast<D3DMATRIX*>(&worldMatrix);

	return 0;
}

void Mesh::update(FLOAT dt)
{
	static FLOAT posX = 0.0f;
	static FLOAT posY = 0.0f;
	static FLOAT posZ = 0.0f;

	static FLOAT rotZ = 0.0f;
	//rotZ += XM_PI / 3.0f * dt; // this line makes the quad rotate

	FLOAT move = 5.0f * dt;

	if ((GetAsyncKeyState(VK_LEFT) & 0x8000) || (GetAsyncKeyState('A') & 0x8000)) posX -= move;
	if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) || (GetAsyncKeyState('D') & 0x8000)) posX += move;
	if ((GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState('W') & 0x8000)) posY += move;
	if ((GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('S') & 0x8000)) posY -= move;
	if ((GetAsyncKeyState(VK_SUBTRACT) & 0x8000) || (GetAsyncKeyState('Q') & 0x8000)) posZ -= move;
	if ((GetAsyncKeyState(VK_ADD) & 0x8000) || (GetAsyncKeyState('E') & 0x8000)) posZ += move;


	XMMATRIX translation = XMMatrixTranslation(posX, posY, posZ);
	XMMATRIX rotation = XMMatrixRotationRollPitchYaw(0.0f, 0.0f, rotZ);
	XMMATRIX localScale = XMMatrixScaling(1.0f, 1.0f, 1.0f);

	XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(&_worldMatrix), localScale * rotation * translation);
}

void Mesh::render(IDirect3DDevice9* pD3DDevice)
{
	// set world transformation matrix 
	pD3DDevice->SetTransform(D3DTS_WORLD, &_worldMatrix);

	// set flexibel vertex format
	pD3DDevice->SetFVF(FVF);

	// set vertex buffer data
	pD3DDevice->SetStreamSource(0, _pVertexBuffer, 0, _vertexStride);

	// draw without index buffer
	//pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, _vertexCount / 3);
	//pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, _vertexCount - 2);
	//pD3DDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, _vertexCount - 2);

	// draw with index buffer
	pD3DDevice->SetIndices(_pIndexBuffer);
	pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, _vertexCount, 0, _indexCount / 3);


}

void Mesh::deInit()
{
	safeRelease<IDirect3DVertexBuffer9>(_pVertexBuffer);
	safeRelease< IDirect3DIndexBuffer9>(_pIndexBuffer);
}

INT Mesh::initVertexBuffer(IDirect3DDevice9* pD3DDevice)
{
	_vertexCount = 4;
	_vertexStride = sizeof(Vertex);

	HRESULT hr = pD3DDevice->CreateVertexBuffer(
		_vertexCount * _vertexStride, // byte length of buffer
		D3DUSAGE_WRITEONLY, // give write acsess
		FVF, // FVF - flexible vertex format
		D3DPOOL_MANAGED, // managed memory management
		&_pVertexBuffer,
		nullptr
	);
	CheckFailed(hr, 30);

	Vertex* vertices = nullptr;
	hr = _pVertexBuffer->Lock(0, 0, reinterpret_cast<void**>(&vertices), 0);
	CheckFailed(hr, 32);

	//// triangle
	//vertices[0] = Vertex(0.0f, 0.5f, 0.0f);
	//vertices[1] = Vertex(0.5f, -0.5f, 0.0f);
	//vertices[2] = Vertex(-0.5f, -0.5f, 0.0f);

	//// quad without index buffer and w/ triangle list
	//// primitive 1
	//vertices[0] = Vertex(-0.5f, 0.5f, 0.0f);
	//vertices[1] = Vertex(0.5f, 0.5f, 0.0f);
	//vertices[2] = Vertex(0.5f, -0.5f, 0.0f);
	//// primitive 2
	//vertices[3] = Vertex(-0.5f, 0.5f, 0.0f);
	//vertices[4] = Vertex(0.5f, -0.5f, 0.0f);
	//vertices[5] = Vertex(-0.5f, -0.5f, 0.0f);

	////quad with triangle strip
	//vertices[0] = Vertex(-0.5f, 0.5f, 0.0f);
	//vertices[1] = Vertex(0.5f, 0.5f, 0.0f);
	//vertices[2] = Vertex(-0.5f, -0.5f, 0.0f);
	//vertices[3] = Vertex(0.5f, -0.5f, 0.0f);

	////quad with triangle fan or with index buffer and triangle list
	//vertices[0] = Vertex(-0.5f, 0.5f, 0.0f);
	//vertices[1] = Vertex(0.5f, 0.5f, 0.0f);
	//vertices[2] = Vertex(0.5f, -0.5f, 0.0f);
	//vertices[3] = Vertex(-0.5f, -0.5f, 0.0f);

	////quad with color
	//vertices[0] = Vertex(-0.5f, 0.5f, 0.0f, 255, 0, 0);
	//vertices[1] = Vertex(0.5f, 0.5f, 0.0f, 0, 255, 0);
	//vertices[2] = Vertex(0.5f, -0.5f, 0.0f, 0, 0, 255);
	//vertices[3] = Vertex(-0.5f, -0.5f, 0.0f, 255, 0, 255);

	//quad with UV
	vertices[0] = Vertex(-0.5f, 0.5f, 0.0f,0.0f, 0.0f);
	vertices[1] = Vertex(0.5f, 0.5f, 0.0f, 1.0f, 0.0f);
	vertices[2] = Vertex(0.5f, -0.5f, 0.0f, 1.0f, 1.0f);
	vertices[3] = Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 1.0f);

	//quad with UV + Normal
	vertices[0] = Vertex(-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	vertices[1] = Vertex(0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	vertices[2] = Vertex(0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
	vertices[3] = Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);

	hr = _pVertexBuffer->Unlock();
	CheckFailed(hr, 34);

	vertices = nullptr;

	return 0;
}

INT Mesh::initIndexBuffer(IDirect3DDevice9* pD3DDevice)
{
	_indexCount = 6;

	HRESULT hr = pD3DDevice->CreateIndexBuffer(_indexCount * sizeof(USHORT), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &_pIndexBuffer, nullptr);
	CheckFailed(hr, 35);

	USHORT* indices = nullptr;
	hr = _pIndexBuffer->Lock(0, 0, reinterpret_cast<void**>(&indices), 0);
	CheckFailed(hr, 38);

	// quad
	// primitive 1
	indices[0] = 0; indices[1] = 1; indices[2] = 2;

	// primitive 2
	indices[3] = 0; indices[4] = 2; indices[5] = 3;

	hr = _pIndexBuffer->Unlock();
	CheckFailed(hr, 39);

	return 0;
}
