// Polygon.cpp: implementation of the CPolygon class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "3DEngine.h"
#include "Polygon.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPolygon::CPolygon()
{
	PointCount=0;
}

CPolygon::~CPolygon()
{
	if(PointCount>0)
	{
		delete[]x;
		delete[]y;
		delete[]z;
	}
}

CPolygon& CPolygon::operator =(const CPolygon& aPolygon)
{
	PointCount=aPolygon.PointCount;
	x=new double[PointCount];
	y=new double[PointCount];
	z=new double[PointCount];
	for(int a=0;a<PointCount;a++)
	{
		x[a]=aPolygon.x[a];
		y[a]=aPolygon.y[a];
		z[a]=aPolygon.z[a];
	}

	color=aPolygon.color;

	return *this;
}