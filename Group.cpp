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
	x=0;
	y=0;
	z=0;
	a=0;
	t=0;
	p=0;
	LineCount=0;
	PolygonCount=0;
}

CGroup::~CGroup()
{
	if(LineCount>0)
		delete[]Lines;
	if(PolygonCount>0)
		delete[]Polygons;
}

CGroup& CGroup::operator =(const CGroup& aGroup)
{
	a=aGroup.a;
	LineCount=aGroup.LineCount;
	Lines=new CLine[LineCount];
	for(int c=0;c<LineCount;c++)
		Lines[c]=aGroup.Lines[c];
	p=aGroup.p;
	PolygonCount=aGroup.PolygonCount;
	Polygons=new CPolygon[PolygonCount];
	for(c=0;c<PolygonCount;c++)
		Polygons[c]=aGroup.Polygons[c];
	t=aGroup.t;
	Visible=aGroup.Visible;
	x=aGroup.x;
	y=aGroup.y;
	z=aGroup.z;

	return *this;
}