// 3D EngineDoc.cpp : implementation of the CMy3DEngineDoc class
//

#include "stdafx.h"
#include "3DEngine.h"

#include "3DEngineDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMy3DEngineDoc

IMPLEMENT_DYNCREATE(CMy3DEngineDoc, CDocument)

BEGIN_MESSAGE_MAP(CMy3DEngineDoc, CDocument)
	//{{AFX_MSG_MAP(CMy3DEngineDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy3DEngineDoc construction/destruction

CMy3DEngineDoc::CMy3DEngineDoc()
{
	world.vw=400;
	world.vh=400;
	
	world.cw=50;
	world.ch=50;
	world.ca=90;
	world.ct=0;

	world.cx=0;
	world.cy=-20;
	world.cz=-2;

	world.Groups=new CGroup[3];
	world.GroupCount=3;
	//world.Groups[0].Lines=new CLine[29];
	//world.Groups[0].LineCount=29;
	world.Groups[0].Polygons=new CPolygon[16];
	world.Groups[0].PolygonCount=16;
	world.Groups[0].Visible=true;
	world.Groups[0].a=0;

	world.Groups[1].Lines=new CLine[36];
	world.Groups[1].LineCount=36;
	world.Groups[1].Visible=false;
	world.Groups[1].a=0;

	world.Groups[2].Lines=new CLine[50];
	world.Groups[2].LineCount=50;
	world.Groups[2].Visible=false;

	world.Groups[2].Lines[0].x1=-1;
	world.Groups[2].Lines[0].y1=0;
	world.Groups[2].Lines[0].z1=0;
	world.Groups[2].Lines[0].x2=0;
	world.Groups[2].Lines[0].y2=0;
	world.Groups[2].Lines[0].z2=0;

	world.Groups[0].Polygons[0].color=RGB(255,0,0);
	world.Groups[0].Polygons[0].PointCount=3;
	world.Groups[0].Polygons[0].x=new double[3];
	world.Groups[0].Polygons[0].y=new double[3];
	world.Groups[0].Polygons[0].z=new double[3];

	world.Groups[0].Polygons[0].x[0]=-5;
	world.Groups[0].Polygons[0].y[0]=-5;
	world.Groups[0].Polygons[0].z[0]=-5;
	world.Groups[0].Polygons[0].x[1]=5;
	world.Groups[0].Polygons[0].y[1]=-5;
	world.Groups[0].Polygons[0].z[1]=-5;
	world.Groups[0].Polygons[0].x[2]=0;
	world.Groups[0].Polygons[0].y[2]=0;
	world.Groups[0].Polygons[0].z[2]=5;

	world.Groups[0].Polygons[1].color=RGB(0,255,0);
	world.Groups[0].Polygons[1].PointCount=3;
	world.Groups[0].Polygons[1].x=new double[3];
	world.Groups[0].Polygons[1].y=new double[3];
	world.Groups[0].Polygons[1].z=new double[3];

	world.Groups[0].Polygons[1].x[0]=-20;
	world.Groups[0].Polygons[1].y[0]=-5;
	world.Groups[0].Polygons[1].z[0]=-5;
	world.Groups[0].Polygons[1].x[1]=-10;
	world.Groups[0].Polygons[1].y[1]=-5;
	world.Groups[0].Polygons[1].z[1]=-5;
	world.Groups[0].Polygons[1].x[2]=-15;
	world.Groups[0].Polygons[1].y[2]=-5;
	world.Groups[0].Polygons[1].z[2]=5;

	world.Groups[0].Polygons[2].color=RGB(0,0,255);
	world.Groups[0].Polygons[2].PointCount=4;
	world.Groups[0].Polygons[2].x=new double[4];
	world.Groups[0].Polygons[2].y=new double[4];
	world.Groups[0].Polygons[2].z=new double[4];

	world.Groups[0].Polygons[2].x[0]=10;
	world.Groups[0].Polygons[2].y[0]=-5;
	world.Groups[0].Polygons[2].z[0]=-5;
	world.Groups[0].Polygons[2].x[1]=10;
	world.Groups[0].Polygons[2].y[1]=-5;
	world.Groups[0].Polygons[2].z[1]=5;
	world.Groups[0].Polygons[2].x[2]=20;
	world.Groups[0].Polygons[2].y[2]=-5;
	world.Groups[0].Polygons[2].z[2]=5;
	world.Groups[0].Polygons[2].x[3]=20;
	world.Groups[0].Polygons[2].y[3]=-5;
	world.Groups[0].Polygons[2].z[3]=-5;

	world.Groups[0].Polygons[3].color=RGB(255,0,0);
	world.Groups[0].Polygons[3].PointCount=3;
	world.Groups[0].Polygons[3].x=new double[3];
	world.Groups[0].Polygons[3].y=new double[3];
	world.Groups[0].Polygons[3].z=new double[3];

	world.Groups[0].Polygons[3].x[0]=-5;
	world.Groups[0].Polygons[3].y[0]=5;
	world.Groups[0].Polygons[3].z[0]=-5;
	world.Groups[0].Polygons[3].x[1]=5;
	world.Groups[0].Polygons[3].y[1]=5;
	world.Groups[0].Polygons[3].z[1]=-5;
	world.Groups[0].Polygons[3].x[2]=0;
	world.Groups[0].Polygons[3].y[2]=0;
	world.Groups[0].Polygons[3].z[2]=5;

	world.Groups[0].Polygons[4].color=RGB(255,0,0);
	world.Groups[0].Polygons[4].PointCount=3;
	world.Groups[0].Polygons[4].x=new double[3];
	world.Groups[0].Polygons[4].y=new double[3];
	world.Groups[0].Polygons[4].z=new double[3];

	world.Groups[0].Polygons[4].x[0]=-5;
	world.Groups[0].Polygons[4].y[0]=-5;
	world.Groups[0].Polygons[4].z[0]=-5;
	world.Groups[0].Polygons[4].x[1]=-5;
	world.Groups[0].Polygons[4].y[1]=5;
	world.Groups[0].Polygons[4].z[1]=-5;
	world.Groups[0].Polygons[4].x[2]=0;
	world.Groups[0].Polygons[4].y[2]=0;
	world.Groups[0].Polygons[4].z[2]=5;

	world.Groups[0].Polygons[5].color=RGB(255,0,0);
	world.Groups[0].Polygons[5].PointCount=3;
	world.Groups[0].Polygons[5].x=new double[3];
	world.Groups[0].Polygons[5].y=new double[3];
	world.Groups[0].Polygons[5].z=new double[3];

	world.Groups[0].Polygons[5].x[0]=5;
	world.Groups[0].Polygons[5].y[0]=-5;
	world.Groups[0].Polygons[5].z[0]=-5;
	world.Groups[0].Polygons[5].x[1]=5;
	world.Groups[0].Polygons[5].y[1]=5;
	world.Groups[0].Polygons[5].z[1]=-5;
	world.Groups[0].Polygons[5].x[2]=0;
	world.Groups[0].Polygons[5].y[2]=0;
	world.Groups[0].Polygons[5].z[2]=5;

	world.Groups[0].Polygons[6].color=RGB(255,0,0);
	world.Groups[0].Polygons[6].PointCount=4;
	world.Groups[0].Polygons[6].x=new double[4];
	world.Groups[0].Polygons[6].y=new double[4];
	world.Groups[0].Polygons[6].z=new double[4];

	world.Groups[0].Polygons[6].x[0]=-5;
	world.Groups[0].Polygons[6].y[0]=-5;
	world.Groups[0].Polygons[6].z[0]=-5;
	world.Groups[0].Polygons[6].x[1]=-5;
	world.Groups[0].Polygons[6].y[1]=5;
	world.Groups[0].Polygons[6].z[1]=-5;
	world.Groups[0].Polygons[6].x[2]=5;
	world.Groups[0].Polygons[6].y[2]=5;
	world.Groups[0].Polygons[6].z[2]=-5;
	world.Groups[0].Polygons[6].x[3]=5;
	world.Groups[0].Polygons[6].y[3]=-5;
	world.Groups[0].Polygons[6].z[3]=-5;

	world.Groups[0].Polygons[7].color=RGB(0,0,255);
	world.Groups[0].Polygons[7].PointCount=4;
	world.Groups[0].Polygons[7].x=new double[4];
	world.Groups[0].Polygons[7].y=new double[4];
	world.Groups[0].Polygons[7].z=new double[4];

	world.Groups[0].Polygons[7].x[0]=10;
	world.Groups[0].Polygons[7].y[0]=-5;
	world.Groups[0].Polygons[7].z[0]=-5;
	world.Groups[0].Polygons[7].x[1]=10;
	world.Groups[0].Polygons[7].y[1]=5;
	world.Groups[0].Polygons[7].z[1]=-5;
	world.Groups[0].Polygons[7].x[2]=20;
	world.Groups[0].Polygons[7].y[2]=5;
	world.Groups[0].Polygons[7].z[2]=-5;
	world.Groups[0].Polygons[7].x[3]=20;
	world.Groups[0].Polygons[7].y[3]=-5;
	world.Groups[0].Polygons[7].z[3]=-5;

	world.Groups[0].Polygons[8].color=RGB(0,255,0);
	world.Groups[0].Polygons[8].PointCount=3;
	world.Groups[0].Polygons[8].x=new double[3];
	world.Groups[0].Polygons[8].y=new double[3];
	world.Groups[0].Polygons[8].z=new double[3];

	world.Groups[0].Polygons[8].x[0]=-20;
	world.Groups[0].Polygons[8].y[0]=5;
	world.Groups[0].Polygons[8].z[0]=-5;
	world.Groups[0].Polygons[8].x[1]=-15;
	world.Groups[0].Polygons[8].y[1]=5;
	world.Groups[0].Polygons[8].z[1]=5;
	world.Groups[0].Polygons[8].x[2]=-10;
	world.Groups[0].Polygons[8].y[2]=5;
	world.Groups[0].Polygons[8].z[2]=-5;

	world.Groups[0].Polygons[9].color=RGB(0,255,0);
	world.Groups[0].Polygons[9].PointCount=4;
	world.Groups[0].Polygons[9].x=new double[4];
	world.Groups[0].Polygons[9].y=new double[4];
	world.Groups[0].Polygons[9].z=new double[4];

	world.Groups[0].Polygons[9].x[0]=-10;
	world.Groups[0].Polygons[9].y[0]=-5;
	world.Groups[0].Polygons[9].z[0]=-5;
	world.Groups[0].Polygons[9].x[1]=-10;
	world.Groups[0].Polygons[9].y[1]=5;
	world.Groups[0].Polygons[9].z[1]=-5;
	world.Groups[0].Polygons[9].x[2]=-15;
	world.Groups[0].Polygons[9].y[2]=5;
	world.Groups[0].Polygons[9].z[2]=5;
	world.Groups[0].Polygons[9].x[3]=-15;
	world.Groups[0].Polygons[9].y[3]=-5;
	world.Groups[0].Polygons[9].z[3]=5;

	world.Groups[0].Polygons[10].color=RGB(0,255,0);
	world.Groups[0].Polygons[10].PointCount=4;
	world.Groups[0].Polygons[10].x=new double[4];
	world.Groups[0].Polygons[10].y=new double[4];
	world.Groups[0].Polygons[10].z=new double[4];

	world.Groups[0].Polygons[10].x[0]=-20;
	world.Groups[0].Polygons[10].y[0]=-5;
	world.Groups[0].Polygons[10].z[0]=-5;
	world.Groups[0].Polygons[10].x[1]=-20;
	world.Groups[0].Polygons[10].y[1]=5;
	world.Groups[0].Polygons[10].z[1]=-5;
	world.Groups[0].Polygons[10].x[2]=-15;
	world.Groups[0].Polygons[10].y[2]=5;
	world.Groups[0].Polygons[10].z[2]=5;
	world.Groups[0].Polygons[10].x[3]=-15;
	world.Groups[0].Polygons[10].y[3]=-5;
	world.Groups[0].Polygons[10].z[3]=5;

	world.Groups[0].Polygons[11].color=RGB(0,255,0);
	world.Groups[0].Polygons[11].PointCount=4;
	world.Groups[0].Polygons[11].x=new double[4];
	world.Groups[0].Polygons[11].y=new double[4];
	world.Groups[0].Polygons[11].z=new double[4];

	world.Groups[0].Polygons[11].x[0]=-20;
	world.Groups[0].Polygons[11].y[0]=-5;
	world.Groups[0].Polygons[11].z[0]=-5;
	world.Groups[0].Polygons[11].x[1]=-10;
	world.Groups[0].Polygons[11].y[1]=-5;
	world.Groups[0].Polygons[11].z[1]=-5;
	world.Groups[0].Polygons[11].x[2]=-10;
	world.Groups[0].Polygons[11].y[2]=5;
	world.Groups[0].Polygons[11].z[2]=-5;
	world.Groups[0].Polygons[11].x[3]=-20;
	world.Groups[0].Polygons[11].y[3]=5;
	world.Groups[0].Polygons[11].z[3]=-5;

	world.Groups[0].Polygons[12].color=RGB(0,0,255);
	world.Groups[0].Polygons[12].PointCount=4;
	world.Groups[0].Polygons[12].x=new double[4];
	world.Groups[0].Polygons[12].y=new double[4];
	world.Groups[0].Polygons[12].z=new double[4];

	world.Groups[0].Polygons[12].x[0]=10;
	world.Groups[0].Polygons[12].y[0]=-5;
	world.Groups[0].Polygons[12].z[0]=-5;
	world.Groups[0].Polygons[12].x[1]=10;
	world.Groups[0].Polygons[12].y[1]=5;
	world.Groups[0].Polygons[12].z[1]=-5;
	world.Groups[0].Polygons[12].x[2]=10;
	world.Groups[0].Polygons[12].y[2]=5;
	world.Groups[0].Polygons[12].z[2]=5;
	world.Groups[0].Polygons[12].x[3]=10;
	world.Groups[0].Polygons[12].y[3]=-5;
	world.Groups[0].Polygons[12].z[3]=5;

	world.Groups[0].Polygons[13].color=RGB(0,0,255);
	world.Groups[0].Polygons[13].PointCount=4;
	world.Groups[0].Polygons[13].x=new double[4];
	world.Groups[0].Polygons[13].y=new double[4];
	world.Groups[0].Polygons[13].z=new double[4];

	world.Groups[0].Polygons[13].x[0]=10;
	world.Groups[0].Polygons[13].y[0]=-5;
	world.Groups[0].Polygons[13].z[0]=5;
	world.Groups[0].Polygons[13].x[1]=10;
	world.Groups[0].Polygons[13].y[1]=5;
	world.Groups[0].Polygons[13].z[1]=5;
	world.Groups[0].Polygons[13].x[2]=20;
	world.Groups[0].Polygons[13].y[2]=5;
	world.Groups[0].Polygons[13].z[2]=5;
	world.Groups[0].Polygons[13].x[3]=20;
	world.Groups[0].Polygons[13].y[3]=-5;
	world.Groups[0].Polygons[13].z[3]=5;

	world.Groups[0].Polygons[14].color=RGB(0,0,255);
	world.Groups[0].Polygons[14].PointCount=4;
	world.Groups[0].Polygons[14].x=new double[4];
	world.Groups[0].Polygons[14].y=new double[4];
	world.Groups[0].Polygons[14].z=new double[4];

	world.Groups[0].Polygons[14].x[0]=10;
	world.Groups[0].Polygons[14].y[0]=5;
	world.Groups[0].Polygons[14].z[0]=-5;
	world.Groups[0].Polygons[14].x[1]=20;
	world.Groups[0].Polygons[14].y[1]=5;
	world.Groups[0].Polygons[14].z[1]=-5;
	world.Groups[0].Polygons[14].x[2]=20;
	world.Groups[0].Polygons[14].y[2]=5;
	world.Groups[0].Polygons[14].z[2]=5;
	world.Groups[0].Polygons[14].x[3]=10;
	world.Groups[0].Polygons[14].y[3]=5;
	world.Groups[0].Polygons[14].z[3]=5;

	world.Groups[0].Polygons[15].color=RGB(0,0,255);
	world.Groups[0].Polygons[15].PointCount=4;
	world.Groups[0].Polygons[15].x=new double[4];
	world.Groups[0].Polygons[15].y=new double[4];
	world.Groups[0].Polygons[15].z=new double[4];

	world.Groups[0].Polygons[15].x[0]=20;
	world.Groups[0].Polygons[15].y[0]=-5;
	world.Groups[0].Polygons[15].z[0]=-5;
	world.Groups[0].Polygons[15].x[1]=20;
	world.Groups[0].Polygons[15].y[1]=5;
	world.Groups[0].Polygons[15].z[1]=-5;
	world.Groups[0].Polygons[15].x[2]=20;
	world.Groups[0].Polygons[15].y[2]=5;
	world.Groups[0].Polygons[15].z[2]=5;
	world.Groups[0].Polygons[15].x[3]=20;
	world.Groups[0].Polygons[15].y[3]=-5;
	world.Groups[0].Polygons[15].z[3]=5;

	/*world.Groups[0].Lines[0].x1=0;
	world.Groups[0].Lines[0].y1=0;
	world.Groups[0].Lines[0].z1=5;
	world.Groups[0].Lines[0].x2=-5;
	world.Groups[0].Lines[0].y2=-5;
	world.Groups[0].Lines[0].z2=-5;

	world.Groups[0].Lines[1].x1=0;
	world.Groups[0].Lines[1].y1=0;
	world.Groups[0].Lines[1].z1=5;
	world.Groups[0].Lines[1].x2=-5;
	world.Groups[0].Lines[1].y2=5;
	world.Groups[0].Lines[1].z2=-5;

	world.Groups[0].Lines[2].x1=0;
	world.Groups[0].Lines[2].y1=0;
	world.Groups[0].Lines[2].z1=5;
	world.Groups[0].Lines[2].x2=5;
	world.Groups[0].Lines[2].y2=-5;
	world.Groups[0].Lines[2].z2=-5;

	world.Groups[0].Lines[3].x1=0;
	world.Groups[0].Lines[3].y1=0;
	world.Groups[0].Lines[3].z1=5;
	world.Groups[0].Lines[3].x2=5;
	world.Groups[0].Lines[3].y2=5;
	world.Groups[0].Lines[3].z2=-5;

	world.Groups[0].Lines[4].x1=-5;
	world.Groups[0].Lines[4].y1=-5;
	world.Groups[0].Lines[4].z1=-5;
	world.Groups[0].Lines[4].x2=-5;
	world.Groups[0].Lines[4].y2=5;
	world.Groups[0].Lines[4].z2=-5;

	world.Groups[0].Lines[5].x1=-5;
	world.Groups[0].Lines[5].y1=5;
	world.Groups[0].Lines[5].z1=-5;
	world.Groups[0].Lines[5].x2=5;
	world.Groups[0].Lines[5].y2=5;
	world.Groups[0].Lines[5].z2=-5;

	world.Groups[0].Lines[6].x1=5;
	world.Groups[0].Lines[6].y1=5;
	world.Groups[0].Lines[6].z1=-5;
	world.Groups[0].Lines[6].x2=5;
	world.Groups[0].Lines[6].y2=-5;
	world.Groups[0].Lines[6].z2=-5;

	world.Groups[0].Lines[7].x1=-5;
	world.Groups[0].Lines[7].y1=-5;
	world.Groups[0].Lines[7].z1=-5;
	world.Groups[0].Lines[7].x2=5;
	world.Groups[0].Lines[7].y2=-5;
	world.Groups[0].Lines[7].z2=-5;

	//Cube
	world.Groups[0].Lines[8].x1=10;
	world.Groups[0].Lines[8].y1=-5;
	world.Groups[0].Lines[8].z1=-5;
	world.Groups[0].Lines[8].x2=10;
	world.Groups[0].Lines[8].y2=5;
	world.Groups[0].Lines[8].z2=-5;

	world.Groups[0].Lines[9].x1=10;
	world.Groups[0].Lines[9].y1=-5;
	world.Groups[0].Lines[9].z1=-5;
	world.Groups[0].Lines[9].x2=20;
	world.Groups[0].Lines[9].y2=-5;
	world.Groups[0].Lines[9].z2=-5;

	world.Groups[0].Lines[10].x1=20;
	world.Groups[0].Lines[10].y1=-5;
	world.Groups[0].Lines[10].z1=-5;
	world.Groups[0].Lines[10].x2=20;
	world.Groups[0].Lines[10].y2=5;
	world.Groups[0].Lines[10].z2=-5;

	world.Groups[0].Lines[11].x1=10;
	world.Groups[0].Lines[11].y1=5;
	world.Groups[0].Lines[11].z1=-5;
	world.Groups[0].Lines[11].x2=20;
	world.Groups[0].Lines[11].y2=5;
	world.Groups[0].Lines[11].z2=-5;

	world.Groups[0].Lines[12].x1=10;
	world.Groups[0].Lines[12].y1=5;
	world.Groups[0].Lines[12].z1=-5;
	world.Groups[0].Lines[12].x2=10;
	world.Groups[0].Lines[12].y2=5;
	world.Groups[0].Lines[12].z2=5;

	world.Groups[0].Lines[13].x1=20;
	world.Groups[0].Lines[13].y1=5;
	world.Groups[0].Lines[13].z1=-5;
	world.Groups[0].Lines[13].x2=20;
	world.Groups[0].Lines[13].y2=5;
	world.Groups[0].Lines[13].z2=5;

	world.Groups[0].Lines[14].x1=10;
	world.Groups[0].Lines[14].y1=-5;
	world.Groups[0].Lines[14].z1=-5;
	world.Groups[0].Lines[14].x2=10;
	world.Groups[0].Lines[14].y2=-5;
	world.Groups[0].Lines[14].z2=5;

	world.Groups[0].Lines[15].x1=20;
	world.Groups[0].Lines[15].y1=-5;
	world.Groups[0].Lines[15].z1=-5;
	world.Groups[0].Lines[15].x2=20;
	world.Groups[0].Lines[15].y2=-5;
	world.Groups[0].Lines[15].z2=5;

	world.Groups[0].Lines[16].x1=10;
	world.Groups[0].Lines[16].y1=-5;
	world.Groups[0].Lines[16].z1=5;
	world.Groups[0].Lines[16].x2=10;
	world.Groups[0].Lines[16].y2=5;
	world.Groups[0].Lines[16].z2=5;

	world.Groups[0].Lines[17].x1=10;
	world.Groups[0].Lines[17].y1=-5;
	world.Groups[0].Lines[17].z1=5;
	world.Groups[0].Lines[17].x2=20;
	world.Groups[0].Lines[17].y2=-5;
	world.Groups[0].Lines[17].z2=5;

	world.Groups[0].Lines[18].x1=20;
	world.Groups[0].Lines[18].y1=-5;
	world.Groups[0].Lines[18].z1=5;
	world.Groups[0].Lines[18].x2=20;
	world.Groups[0].Lines[18].y2=5;
	world.Groups[0].Lines[18].z2=5;

	world.Groups[0].Lines[19].x1=10;
	world.Groups[0].Lines[19].y1=5;
	world.Groups[0].Lines[19].z1=5;
	world.Groups[0].Lines[19].x2=20;
	world.Groups[0].Lines[19].y2=5;
	world.Groups[0].Lines[19].z2=5;

	world.Groups[0].Lines[20].x1=-20;
	world.Groups[0].Lines[20].y1=-5;
	world.Groups[0].Lines[20].z1=-5;
	world.Groups[0].Lines[20].x2=-10;
	world.Groups[0].Lines[20].y2=-5;
	world.Groups[0].Lines[20].z2=-5;

	world.Groups[0].Lines[21].x1=-15;
	world.Groups[0].Lines[21].y1=-5;
	world.Groups[0].Lines[21].z1=5;
	world.Groups[0].Lines[21].x2=-10;
	world.Groups[0].Lines[21].y2=-5;
	world.Groups[0].Lines[21].z2=-5;

	world.Groups[0].Lines[22].x1=-20;
	world.Groups[0].Lines[22].y1=-5;
	world.Groups[0].Lines[22].z1=-5;
	world.Groups[0].Lines[22].x2=-15;
	world.Groups[0].Lines[22].y2=-5;
	world.Groups[0].Lines[22].z2=5;

	world.Groups[0].Lines[23].x1=-20;
	world.Groups[0].Lines[23].y1=5;
	world.Groups[0].Lines[23].z1=-5;
	world.Groups[0].Lines[23].x2=-10;
	world.Groups[0].Lines[23].y2=5;
	world.Groups[0].Lines[23].z2=-5;

	world.Groups[0].Lines[24].x1=-15;
	world.Groups[0].Lines[24].y1=5;
	world.Groups[0].Lines[24].z1=5;
	world.Groups[0].Lines[24].x2=-10;
	world.Groups[0].Lines[24].y2=5;
	world.Groups[0].Lines[24].z2=-5;

	world.Groups[0].Lines[25].x1=-20;
	world.Groups[0].Lines[25].y1=5;
	world.Groups[0].Lines[25].z1=-5;
	world.Groups[0].Lines[25].x2=-15;
	world.Groups[0].Lines[25].y2=5;
	world.Groups[0].Lines[25].z2=5;

	world.Groups[0].Lines[26].x1=-20;
	world.Groups[0].Lines[26].y1=-5;
	world.Groups[0].Lines[26].z1=-5;
	world.Groups[0].Lines[26].x2=-20;
	world.Groups[0].Lines[26].y2=5;
	world.Groups[0].Lines[26].z2=-5;

	world.Groups[0].Lines[27].x1=-15;
	world.Groups[0].Lines[27].y1=-5;
	world.Groups[0].Lines[27].z1=5;
	world.Groups[0].Lines[27].x2=-15;
	world.Groups[0].Lines[27].y2=5;
	world.Groups[0].Lines[27].z2=5;

	world.Groups[0].Lines[28].x1=-10;
	world.Groups[0].Lines[28].y1=-5;
	world.Groups[0].Lines[28].z1=-5;
	world.Groups[0].Lines[28].x2=-10;
	world.Groups[0].Lines[28].y2=5;
	world.Groups[0].Lines[28].z2=-5;*/

	world.Groups[1].Lines[0].x1=-1;
	world.Groups[1].Lines[0].y1=-1;
	world.Groups[1].Lines[0].z1=-5;
	world.Groups[1].Lines[0].x2=-1;
	world.Groups[1].Lines[0].y2=-1;
	world.Groups[1].Lines[0].z2=0;

	world.Groups[1].Lines[1].x1=-1;
	world.Groups[1].Lines[1].y1=-1;
	world.Groups[1].Lines[1].z1=0;
	world.Groups[1].Lines[1].x2=-3;
	world.Groups[1].Lines[1].y2=-1;
	world.Groups[1].Lines[1].z2=0;

	world.Groups[1].Lines[2].x1=-3;
	world.Groups[1].Lines[2].y1=-1;
	world.Groups[1].Lines[2].z1=0;
	world.Groups[1].Lines[2].x2=-3;
	world.Groups[1].Lines[2].y2=-1;
	world.Groups[1].Lines[2].z2=1;

	world.Groups[1].Lines[3].x1=-3;
	world.Groups[1].Lines[3].y1=-1;
	world.Groups[1].Lines[3].z1=1;
	world.Groups[1].Lines[3].x2=-1;
	world.Groups[1].Lines[3].y2=-1;
	world.Groups[1].Lines[3].z2=1;

	world.Groups[1].Lines[4].x1=-1;
	world.Groups[1].Lines[4].y1=-1;
	world.Groups[1].Lines[4].z1=1;
	world.Groups[1].Lines[4].x2=-1;
	world.Groups[1].Lines[4].y2=-1;
	world.Groups[1].Lines[4].z2=3;

	world.Groups[1].Lines[5].x1=-1;
	world.Groups[1].Lines[5].y1=-1;
	world.Groups[1].Lines[5].z1=3;
	world.Groups[1].Lines[5].x2=0;
	world.Groups[1].Lines[5].y2=-1;
	world.Groups[1].Lines[5].z2=3;

	world.Groups[1].Lines[6].x1=0;
	world.Groups[1].Lines[6].y1=-1;
	world.Groups[1].Lines[6].z1=3;
	world.Groups[1].Lines[6].x2=0;
	world.Groups[1].Lines[6].y2=-1;
	world.Groups[1].Lines[6].z2=1;

	world.Groups[1].Lines[7].x1=0;
	world.Groups[1].Lines[7].y1=-1;
	world.Groups[1].Lines[7].z1=1;
	world.Groups[1].Lines[7].x2=2;
	world.Groups[1].Lines[7].y2=-1;
	world.Groups[1].Lines[7].z2=1;

	world.Groups[1].Lines[8].x1=2;
	world.Groups[1].Lines[8].y1=-1;
	world.Groups[1].Lines[8].z1=1;
	world.Groups[1].Lines[8].x2=2;
	world.Groups[1].Lines[8].y2=-1;
	world.Groups[1].Lines[8].z2=0;

	world.Groups[1].Lines[9].x1=2;
	world.Groups[1].Lines[9].y1=-1;
	world.Groups[1].Lines[9].z1=0;
	world.Groups[1].Lines[9].x2=0;
	world.Groups[1].Lines[9].y2=-1;
	world.Groups[1].Lines[9].z2=0;

	world.Groups[1].Lines[10].x1=0;
	world.Groups[1].Lines[10].y1=-1;
	world.Groups[1].Lines[10].z1=0;
	world.Groups[1].Lines[10].x2=0;
	world.Groups[1].Lines[10].y2=-1;
	world.Groups[1].Lines[10].z2=-5;

	world.Groups[1].Lines[11].x1=0;
	world.Groups[1].Lines[11].y1=-1;
	world.Groups[1].Lines[11].z1=-5;
	world.Groups[1].Lines[11].x2=-1;
	world.Groups[1].Lines[11].y2=-1;
	world.Groups[1].Lines[11].z2=-5;

	world.Groups[1].Lines[12].x1=-1;
	world.Groups[1].Lines[12].y1=0;
	world.Groups[1].Lines[12].z1=-5;
	world.Groups[1].Lines[12].x2=-1;
	world.Groups[1].Lines[12].y2=0;
	world.Groups[1].Lines[12].z2=0;

	world.Groups[1].Lines[13].x1=-1;
	world.Groups[1].Lines[13].y1=0;
	world.Groups[1].Lines[13].z1=0;
	world.Groups[1].Lines[13].x2=-3;
	world.Groups[1].Lines[13].y2=0;
	world.Groups[1].Lines[13].z2=0;

	world.Groups[1].Lines[14].x1=-3;
	world.Groups[1].Lines[14].y1=0;
	world.Groups[1].Lines[14].z1=0;
	world.Groups[1].Lines[14].x2=-3;
	world.Groups[1].Lines[14].y2=0;
	world.Groups[1].Lines[14].z2=1;

	world.Groups[1].Lines[15].x1=-3;
	world.Groups[1].Lines[15].y1=0;
	world.Groups[1].Lines[15].z1=1;
	world.Groups[1].Lines[15].x2=-1;
	world.Groups[1].Lines[15].y2=0;
	world.Groups[1].Lines[15].z2=1;

	world.Groups[1].Lines[16].x1=-1;
	world.Groups[1].Lines[16].y1=0;
	world.Groups[1].Lines[16].z1=1;
	world.Groups[1].Lines[16].x2=-1;
	world.Groups[1].Lines[16].y2=0;
	world.Groups[1].Lines[16].z2=3;

	world.Groups[1].Lines[17].x1=-1;
	world.Groups[1].Lines[17].y1=0;
	world.Groups[1].Lines[17].z1=3;
	world.Groups[1].Lines[17].x2=0;
	world.Groups[1].Lines[17].y2=0;
	world.Groups[1].Lines[17].z2=3;

	world.Groups[1].Lines[18].x1=0;
	world.Groups[1].Lines[18].y1=0;
	world.Groups[1].Lines[18].z1=3;
	world.Groups[1].Lines[18].x2=0;
	world.Groups[1].Lines[18].y2=0;
	world.Groups[1].Lines[18].z2=1;

	world.Groups[1].Lines[19].x1=0;
	world.Groups[1].Lines[19].y1=0;
	world.Groups[1].Lines[19].z1=1;
	world.Groups[1].Lines[19].x2=2;
	world.Groups[1].Lines[19].y2=0;
	world.Groups[1].Lines[19].z2=1;

	world.Groups[1].Lines[20].x1=2;
	world.Groups[1].Lines[20].y1=0;
	world.Groups[1].Lines[20].z1=1;
	world.Groups[1].Lines[20].x2=2;
	world.Groups[1].Lines[20].y2=0;
	world.Groups[1].Lines[20].z2=0;

	world.Groups[1].Lines[21].x1=2;
	world.Groups[1].Lines[21].y1=0;
	world.Groups[1].Lines[21].z1=0;
	world.Groups[1].Lines[21].x2=0;
	world.Groups[1].Lines[21].y2=0;
	world.Groups[1].Lines[21].z2=0;

	world.Groups[1].Lines[22].x1=0;
	world.Groups[1].Lines[22].y1=0;
	world.Groups[1].Lines[22].z1=0;
	world.Groups[1].Lines[22].x2=0;
	world.Groups[1].Lines[22].y2=0;
	world.Groups[1].Lines[22].z2=-5;

	world.Groups[1].Lines[23].x1=0;
	world.Groups[1].Lines[23].y1=0;
	world.Groups[1].Lines[23].z1=-5;
	world.Groups[1].Lines[23].x2=-1;
	world.Groups[1].Lines[23].y2=0;
	world.Groups[1].Lines[23].z2=-5;

	world.Groups[1].Lines[24].x1=-1;
	world.Groups[1].Lines[24].y1=-1;
	world.Groups[1].Lines[24].z1=-5;
	world.Groups[1].Lines[24].x2=-1;
	world.Groups[1].Lines[24].y2=0;
	world.Groups[1].Lines[24].z2=-5;

	world.Groups[1].Lines[25].x1=-1;
	world.Groups[1].Lines[25].y1=-1;
	world.Groups[1].Lines[25].z1=0;
	world.Groups[1].Lines[25].x2=-1;
	world.Groups[1].Lines[25].y2=0;
	world.Groups[1].Lines[25].z2=0;

	world.Groups[1].Lines[26].x1=-3;
	world.Groups[1].Lines[26].y1=-1;
	world.Groups[1].Lines[26].z1=0;
	world.Groups[1].Lines[26].x2=-3;
	world.Groups[1].Lines[26].y2=0;
	world.Groups[1].Lines[26].z2=0;

	world.Groups[1].Lines[27].x1=-3;
	world.Groups[1].Lines[27].y1=-1;
	world.Groups[1].Lines[27].z1=1;
	world.Groups[1].Lines[27].x2=-3;
	world.Groups[1].Lines[27].y2=0;
	world.Groups[1].Lines[27].z2=1;

	world.Groups[1].Lines[28].x1=-1;
	world.Groups[1].Lines[28].y1=-1;
	world.Groups[1].Lines[28].z1=3;
	world.Groups[1].Lines[28].x2=-1;
	world.Groups[1].Lines[28].y2=0;
	world.Groups[1].Lines[28].z2=3;

	world.Groups[1].Lines[29].x1=0;
	world.Groups[1].Lines[29].y1=-1;
	world.Groups[1].Lines[29].z1=3;
	world.Groups[1].Lines[29].x2=0;
	world.Groups[1].Lines[29].y2=0;
	world.Groups[1].Lines[29].z2=3;

	world.Groups[1].Lines[30].x1=0;
	world.Groups[1].Lines[30].y1=-1;
	world.Groups[1].Lines[30].z1=0;
	world.Groups[1].Lines[30].x2=0;
	world.Groups[1].Lines[30].y2=0;
	world.Groups[1].Lines[30].z2=0;

	world.Groups[1].Lines[31].x1=-1;
	world.Groups[1].Lines[31].y1=-1;
	world.Groups[1].Lines[31].z1=1;
	world.Groups[1].Lines[31].x2=-1;
	world.Groups[1].Lines[31].y2=0;
	world.Groups[1].Lines[31].z2=1;

	world.Groups[1].Lines[32].x1=0;
	world.Groups[1].Lines[32].y1=-1;
	world.Groups[1].Lines[32].z1=1;
	world.Groups[1].Lines[32].x2=0;
	world.Groups[1].Lines[32].y2=0;
	world.Groups[1].Lines[32].z2=1;

	world.Groups[1].Lines[33].x1=2;
	world.Groups[1].Lines[33].y1=-1;
	world.Groups[1].Lines[33].z1=1;
	world.Groups[1].Lines[33].x2=2;
	world.Groups[1].Lines[33].y2=0;
	world.Groups[1].Lines[33].z2=1;

	world.Groups[1].Lines[34].x1=2;
	world.Groups[1].Lines[34].y1=-1;
	world.Groups[1].Lines[34].z1=0;
	world.Groups[1].Lines[34].x2=2;
	world.Groups[1].Lines[34].y2=0;
	world.Groups[1].Lines[34].z2=0;

	world.Groups[1].Lines[35].x1=0;
	world.Groups[1].Lines[35].y1=-1;
	world.Groups[1].Lines[35].z1=-5;
	world.Groups[1].Lines[35].x2=0;
	world.Groups[1].Lines[35].y2=0;
	world.Groups[1].Lines[35].z2=-5;
}

CMy3DEngineDoc::~CMy3DEngineDoc()
{
}

BOOL CMy3DEngineDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMy3DEngineDoc serialization

void CMy3DEngineDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMy3DEngineDoc diagnostics

#ifdef _DEBUG
void CMy3DEngineDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy3DEngineDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMy3DEngineDoc commands
