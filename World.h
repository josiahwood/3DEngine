// World.h: interface for the CWorld class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORLD_H__7039CD76_DB84_11D5_8358_00A024E92462__INCLUDED_)
#define AFX_WORLD_H__7039CD76_DB84_11D5_8358_00A024E92462__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Group.h"

class CWorld  
{
public:
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
