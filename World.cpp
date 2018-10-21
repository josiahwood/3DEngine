// World.cpp: implementation of the CWorld class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "3DEngine.h"
#include "World.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWorld::CWorld()
{
	GroupCount=0;
}

CWorld::~CWorld()
{
	if(GroupCount>0)
		delete[]Groups;
}

CWorld& CWorld::operator =(const CWorld& aWorld)
{
	ca=aWorld.ca;
	ch=aWorld.ch;
	ct=aWorld.ct;
	cw=aWorld.cw;
	cx=aWorld.cx;
	cy=aWorld.cy;
	cz=aWorld.cz;
	GroupCount=aWorld.GroupCount;
	Groups=new CGroup[GroupCount];
	for(int x=0;x<GroupCount;x++)
		Groups[x]=aWorld.Groups[x];

	vh=aWorld.vh;
	vw=aWorld.vw;

	return *this;
}