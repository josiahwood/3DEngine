// Group.cpp: implementation of the CGroup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "3DEngine.h"
#include "Group.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGroup::CGroup()
{
	dexp=0;
	x=0;
	y=0;
	z=0;
	a=0;
	t=0;
	p=0;
	Visible=true;
	fx=fy=fz=0;
	dx=dy=dz=0;
	exp=0;
	sx=sy=sz=0;
	rx=ry=rz=0;
	//PolygonCount=0;
}

CGroup::~CGroup()
{
	//if(PolygonCount>0)
	//	delete[]Polygons;
}

CGroup& CGroup::operator =(const CGroup& aGroup)
{
	a=aGroup.a;
	dexp=aGroup.dexp;
	p=aGroup.p;
	//PolygonCount=aGroup.PolygonCount;
	//Polygons=new CPolygon[PolygonCount];
	//for(int c=0;c<PolygonCount;c++)
	//	Polygons[c]=aGroup.Polygons[c];
	t=aGroup.t;
	Visible=aGroup.Visible;
	x=aGroup.x;
	y=aGroup.y;
	z=aGroup.z;
	dx=aGroup.dx;
	dy=aGroup.dy;
	dz=aGroup.dz;
	exp=aGroup.exp;
	fx=aGroup.fx;
	fy=aGroup.fy;
	fz=aGroup.fz;
	sx=aGroup.sx;
	sy=aGroup.sy;
	sz=aGroup.sz;
	rx=aGroup.rx;
	ry=aGroup.ry;
	rz=aGroup.rz;

	Polygons.Copy(aGroup.Polygons);

	return *this;
}