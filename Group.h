// Group.h: interface for the CGroup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GROUP_H__7039CD77_DB84_11D5_8358_00A024E92462__INCLUDED_)
#define AFX_GROUP_H__7039CD77_DB84_11D5_8358_00A024E92462__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Line.h"
#include "Polygon.h"

class CGroup  
{
public:
	int PolygonCount;
	CPolygon* Polygons;
	double a,t,p;
	bool Visible;
	CLine* Lines;
	int LineCount;

	double x,y,z;

	CGroup();
	virtual ~CGroup();

	CGroup& operator =(const CGroup& aGroup);
};

#endif // !defined(AFX_GROUP_H__7039CD77_DB84_11D5_8358_00A024E92462__INCLUDED_)
