// World.h: interface for the CWorld class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORLD_H__7039CD76_DB84_11D5_8358_00A024E92462__INCLUDED_)
#define AFX_WORLD_H__7039CD76_DB84_11D5_8358_00A024E92462__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Group.h"
#include "Light.h"
//#include <afxtempl.h>

class CWorld  
{
public:
	void AddGroup(CGroup* a);
	bool GroupIntersect(CGroup* a,CGroup* b);
	int PolyIntersect(CPolygon* a,CPolygon* b);
	void Physics();
	CBitmap tbit;
	CDC tdc;
	double* zbuffer;

	CPen* oldpen;
	CPen* pen;
	bool drawnext;
	CBrush* oldbrush;
	CBrush* brush;
	void UpdateWall();
	double wall;
	//CArray <CLight,CLight> Lights;
	CLight* Lights;
	int LightCount;
	double sqr(double x);
	void DrawLight(CLight* Light);
	int DrawCount;
	void Draw();
	double GetA(double x,double y);
	void DrawPolygon(CPolygon* Polygon);
	void AddPolygon(CPolygon *Polygon);
	
	CArray <CPolygon,CPolygon> Polygons;
	//CPolygon* Polygons;
	//int PolygonCount;
	
	void DrawPolygons();
	CDC* dc;
	double vw,vh;
	CGroup* Groups;
	int GroupCount;

	//Camera Position
	double cx,cy,cz;

	//Camera Direction
	double ca,ct;

	//Camera Zoom
	double cw,ch;
	
	CWorld();
	virtual ~CWorld();

	CWorld& operator =(const CWorld& aWorld);

};

#endif // !defined(AFX_WORLD_H__7039CD76_DB84_11D5_8358_00A024E92462__INCLUDED_)
