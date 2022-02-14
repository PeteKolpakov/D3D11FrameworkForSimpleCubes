#pragma once
#include <d3d9.h>

#define FVF D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_NORMAL

struct Vertex
{
	// position
	FLOAT _x = 0.0f;
	FLOAT _y = 0.0f;
	FLOAT _z = 0.0f;

	// normal
	FLOAT _nx = 0.0f;
	FLOAT _ny = 0.0f;
	FLOAT _nz = 0.0f;

	// color
	D3DCOLOR _color;

	// uv
	FLOAT _u = 0.0f;
	FLOAT _v = 0.0f;


	Vertex(FLOAT x, FLOAT y, FLOAT z) : _x(x), _y(y), _z(z), _color(0xffffffff), _nx(0.0f), _ny(0.0f), _nz(0.0f), _u(0.0f), _v(0.0f) {}
	Vertex(FLOAT x, FLOAT y, FLOAT z, D3DCOLOR color) : _x(x), _y(y), _z(z), _color(color), _nx(0.0f), _ny(0.0f), _nz(0.0f), _u(0.0f), _v(0.0f) { }
	Vertex(FLOAT x, FLOAT y, FLOAT z, BYTE r, BYTE g, BYTE b) : _x(x), _y(y), _z(z), _color(D3DCOLOR_XRGB(r, g, b)), _nx(0.0f), _ny(0.0f), _nz(0.0f), _u(0.0f), _v(0.0f) { }
	Vertex(FLOAT x, FLOAT y, FLOAT z, FLOAT u, FLOAT v) : _x(x), _y(y), _z(z), _color(0xffffffff), _nx(0.0f), _ny(0.0f), _nz(0.0f), _u(u), _v(v) {}
	Vertex(FLOAT x, FLOAT y, FLOAT z, FLOAT nx, FLOAT ny, FLOAT nz, FLOAT u, FLOAT v) : _x(x), _y(y), _z(z), _color(0xffffffff), _nx(nx), _ny(ny), _nz(nz), _u(u), _v(v) {} 
};