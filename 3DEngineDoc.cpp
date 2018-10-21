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
	LoadShapes();
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
		CFile* f;
		f=ar.GetFile();

		MessageBox(NULL,f->GetFilePath(),"Opening File",NULL);

		if(world.GroupCount>0)
			delete[]world.Groups;
		world.GroupCount=1;
		world.Groups=new CGroup[1];

		CPolygon tempPolygon;
		//tempPolygon.copy=true;
		//tempPolygon.x=new double[4];
		//tempPolygon.y=new double[4];
		//tempPolygon.z=new double[4];
		tempPolygon.PointCount=4;
		/*tempPolygon.x.Add(0);
		tempPolygon.x.Add(0);
		tempPolygon.x.Add(0);
		tempPolygon.x.Add(0);
		tempPolygon.y.Add(0);
		tempPolygon.y.Add(0);
		tempPolygon.y.Add(0);
		tempPolygon.y.Add(0);
		tempPolygon.z.Add(0);
		tempPolygon.z.Add(0);
		tempPolygon.z.Add(0);
		tempPolygon.z.Add(0);*/
		tempPolygon.color=RGB(0,255,0);
		
		bool eof=false;
		int code;
		CString sval;
		//int ival;
		double dval;
		//float fval;
		bool secopen=false;

		enum {secNone,secEntities} section=secNone;
		enum {entNone,ent3DFace} entitytype=entNone;

		while(!eof)
		{
			ar.ReadString(sval);
			code=atoi(sval);
			switch(code)
			{
			case 0:
				switch(section)
				{
				case secNone:
					ar.ReadString(sval);
					if(sval=="SECTION")
					{
						secopen=true;
					}
					else if(sval=="EOF")
					{
						eof=true;
					}
					break;
				case secEntities:
					ar.ReadString(sval);
					if(sval=="3DFACE")
					{
						entitytype=ent3DFace;
					}
					else if(sval=="ENDSEC")
					{
						entitytype=entNone;
						section=secNone;
					}
					break;
				}
				break;
			
			case 2:
				ar.ReadString(sval);
				if(sval=="ENTITIES" && secopen)
				{
					section=secEntities;
					secopen=false;
				}
				break;
			case 10:
				ar.ReadString(sval);
				dval=atof(sval);
				tempPolygon.x[0]=dval;
				break;
			case 20:
				ar.ReadString(sval);
				dval=atof(sval);
				tempPolygon.y[0]=dval;
				break;
			case 30:
				ar.ReadString(sval);
				dval=atof(sval);
				tempPolygon.z[0]=dval;
				break;

			case 11:
				ar.ReadString(sval);
				dval=atof(sval);
				tempPolygon.x[1]=dval;
				break;
			case 21:
				ar.ReadString(sval);
				dval=atof(sval);
				tempPolygon.y[1]=dval;
				break;
			case 31:
				ar.ReadString(sval);
				dval=atof(sval);
				tempPolygon.z[1]=dval;
				break;

			case 12:
				ar.ReadString(sval);
				dval=atof(sval);
				tempPolygon.x[2]=dval;
				break;
			case 22:
				ar.ReadString(sval);
				dval=atof(sval);
				tempPolygon.y[2]=dval;
				break;
			case 32:
				ar.ReadString(sval);
				dval=atof(sval);
				tempPolygon.z[2]=dval;
				
				break;

			case 13:
				ar.ReadString(sval);
				dval=atof(sval);
				tempPolygon.x[3]=dval;
				break;
			case 23:
				ar.ReadString(sval);
				dval=atof(sval);
				tempPolygon.y[3]=dval;
				break;
			case 33:
				ar.ReadString(sval);
				dval=atof(sval);
				tempPolygon.z[3]=dval;
				world.Groups[0].Polygons.Add(tempPolygon);
				break;
			default:
				ar.ReadString(sval);
			}
		}
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

void CMy3DEngineDoc::LoadTank()
{
	world.LightCount=1;
	world.Lights=new CLight[1];
	world.Lights[0].x=0;
	world.Lights[0].y=-60;
	world.Lights[0].z=-2;
	
	world.vw=400;
	world.vh=400;
	
	world.cw=50;
	world.ch=50;
	world.ca=90;
	world.ct=0;

	world.cx=0;
	world.cy=-60;
	world.cz=2;

	world.Groups=new CGroup[2];
	world.GroupCount=2;

	CPolygon blank;

	world.Groups[0].Polygons.InsertAt(0,blank,5);
	world.Groups[0].Visible=true;
	world.Groups[0].a=0;
	world.Groups[0].x=0;
	world.Groups[0].y=0;
	world.Groups[0].z=0;

	world.Groups[0].Polygons[0].color=RGB(0,255,0);
	world.Groups[0].Polygons[0].PointCount=4;
	world.Groups[0].Polygons[0].x[0]=-2;
	world.Groups[0].Polygons[0].y[0]=3;
	world.Groups[0].Polygons[0].z[0]=2;
	world.Groups[0].Polygons[0].x[1]=2;
	world.Groups[0].Polygons[0].y[1]=3;
	world.Groups[0].Polygons[0].z[1]=2;
	world.Groups[0].Polygons[0].x[2]=2;
	world.Groups[0].Polygons[0].y[2]=-3;
	world.Groups[0].Polygons[0].z[2]=2;
	world.Groups[0].Polygons[0].x[3]=-2;
	world.Groups[0].Polygons[0].y[3]=-3;
	world.Groups[0].Polygons[0].z[3]=2;

	world.Groups[0].Polygons[1].color=RGB(0,255,0);
	world.Groups[0].Polygons[1].PointCount=4;
	world.Groups[0].Polygons[1].x[0]=-2;
	world.Groups[0].Polygons[1].y[0]=3;
	world.Groups[0].Polygons[1].z[0]=2;
	world.Groups[0].Polygons[1].x[1]=2;
	world.Groups[0].Polygons[1].y[1]=3;
	world.Groups[0].Polygons[1].z[1]=2;
	world.Groups[0].Polygons[1].x[2]=2;
	world.Groups[0].Polygons[1].y[2]=3;
	world.Groups[0].Polygons[1].z[2]=0;
	world.Groups[0].Polygons[1].x[3]=-2;
	world.Groups[0].Polygons[1].y[3]=3;
	world.Groups[0].Polygons[1].z[3]=0;

	world.Groups[0].Polygons[2].color=RGB(0,255,0);
	world.Groups[0].Polygons[2].PointCount=4;
	world.Groups[0].Polygons[2].x[0]=-2;
	world.Groups[0].Polygons[2].y[0]=-3;
	world.Groups[0].Polygons[2].z[0]=2;
	world.Groups[0].Polygons[2].x[1]=2;
	world.Groups[0].Polygons[2].y[1]=-3;
	world.Groups[0].Polygons[2].z[1]=2;
	world.Groups[0].Polygons[2].x[2]=2;
	world.Groups[0].Polygons[2].y[2]=-3;
	world.Groups[0].Polygons[2].z[2]=0;
	world.Groups[0].Polygons[2].x[3]=-2;
	world.Groups[0].Polygons[2].y[3]=-3;
	world.Groups[0].Polygons[2].z[3]=0;

	world.Groups[0].Polygons[3].color=RGB(0,255,0);
	world.Groups[0].Polygons[3].PointCount=4;
	world.Groups[0].Polygons[3].x[0]=-2;
	world.Groups[0].Polygons[3].y[0]=-3;
	world.Groups[0].Polygons[3].z[0]=2;
	world.Groups[0].Polygons[3].x[1]=-2;
	world.Groups[0].Polygons[3].y[1]=3;
	world.Groups[0].Polygons[3].z[1]=2;
	world.Groups[0].Polygons[3].x[2]=-2;
	world.Groups[0].Polygons[3].y[2]=3;
	world.Groups[0].Polygons[3].z[2]=0;
	world.Groups[0].Polygons[3].x[3]=-2;
	world.Groups[0].Polygons[3].y[3]=-3;
	world.Groups[0].Polygons[3].z[3]=0;

	world.Groups[0].Polygons[4].color=RGB(0,255,0);
	world.Groups[0].Polygons[4].PointCount=4;
	world.Groups[0].Polygons[4].x[0]=2;
	world.Groups[0].Polygons[4].y[0]=-3;
	world.Groups[0].Polygons[4].z[0]=2;
	world.Groups[0].Polygons[4].x[1]=2;
	world.Groups[0].Polygons[4].y[1]=3;
	world.Groups[0].Polygons[4].z[1]=2;
	world.Groups[0].Polygons[4].x[2]=2;
	world.Groups[0].Polygons[4].y[2]=3;
	world.Groups[0].Polygons[4].z[2]=0;
	world.Groups[0].Polygons[4].x[3]=2;
	world.Groups[0].Polygons[4].y[3]=-3;
	world.Groups[0].Polygons[4].z[3]=0;

	world.Groups[1].Polygons.InsertAt(0,blank,1);
	world.Groups[1].Visible=true;
	world.Groups[1].a=0;
	world.Groups[1].x=0;
	world.Groups[1].y=0;
	world.Groups[1].z=0;

	world.Groups[1].Polygons[0].color=RGB(0,255,0);
	world.Groups[1].Polygons[0].PointCount=4;
	world.Groups[1].Polygons[0].x[0]=-1;
	world.Groups[1].Polygons[0].y[0]=1;
	world.Groups[1].Polygons[0].z[0]=3;
	world.Groups[1].Polygons[0].x[1]=1;
	world.Groups[1].Polygons[0].y[1]=1;
	world.Groups[1].Polygons[0].z[1]=3;
	world.Groups[1].Polygons[0].x[2]=1;
	world.Groups[1].Polygons[0].y[2]=-1;
	world.Groups[1].Polygons[0].z[2]=3;
	world.Groups[1].Polygons[0].x[3]=-1;
	world.Groups[1].Polygons[0].y[3]=-1;
	world.Groups[1].Polygons[0].z[3]=3;
}

void CMy3DEngineDoc::LoadShapes()
{
	world.LightCount=1;
	world.Lights=new CLight[1];
	world.Lights[0].x=0;
	world.Lights[0].y=-60;
	world.Lights[0].z=-2;
	
	world.vw=400;
	world.vh=400;
	
	world.cw=50;
	world.ch=50;
	world.ca=90;
	world.ct=0;

	world.cx=0;
	world.cy=-60;
	world.cz=-2;
	
	world.Groups=new CGroup[4];
	world.GroupCount=4;
	
	
	CPolygon blank;

	world.Groups[0].Polygons.InsertAt(0,blank,5);
	//world.Groups[0].PolygonCount=5;
	world.Groups[0].Visible=true;
	world.Groups[0].a=0;
	world.Groups[0].x=0;
	world.Groups[0].y=0;
	world.Groups[0].z=0;

	world.Groups[1].Polygons.InsertAt(0,blank,5);
	//world.Groups[1].PolygonCount=5;
	world.Groups[1].Visible=true;
	world.Groups[1].a=0;
	world.Groups[1].x=-15;
	world.Groups[1].y=0;
	world.Groups[1].z=0;

	world.Groups[2].Polygons.InsertAt(0,blank,6);
	//world.Groups[2].PolygonCount=6;
	world.Groups[2].Visible=true;
	world.Groups[2].a=0;
	world.Groups[2].x=15;
	world.Groups[2].y=0;
	world.Groups[2].z=0;

	world.Groups[3].Polygons.InsertAt(0,blank,1);
	//world.Groups[3].PolygonCount=1;
	world.Groups[3].Visible=false;
	world.Groups[3].a=world.ca-90;
	world.Groups[3].x=world.cx;
	world.Groups[3].y=world.cy;
	world.Groups[3].z=world.cz;

	//Pyramid
	world.Groups[0].Polygons[0].color=RGB(255,0,0);
	world.Groups[0].Polygons[0].PointCount=3;
	//world.Groups[0].Polygons[0].x=new double[3];
	//world.Groups[0].Polygons[0].y=new double[3];
	//world.Groups[0].Polygons[0].z=new double[3];

	world.Groups[0].Polygons[0].x[0]=-5;
	world.Groups[0].Polygons[0].y[0]=-5;
	world.Groups[0].Polygons[0].z[0]=-5;
	world.Groups[0].Polygons[0].x[1]=5;
	world.Groups[0].Polygons[0].y[1]=-5;
	world.Groups[0].Polygons[0].z[1]=-5;
	world.Groups[0].Polygons[0].x[2]=0;
	world.Groups[0].Polygons[0].y[2]=0;
	world.Groups[0].Polygons[0].z[2]=5;

	world.Groups[0].Polygons[1].color=RGB(255,0,0);
	world.Groups[0].Polygons[1].PointCount=3;
	//world.Groups[0].Polygons[1].x=new double[3];
	//world.Groups[0].Polygons[1].y=new double[3];
	//world.Groups[0].Polygons[1].z=new double[3];

	world.Groups[0].Polygons[1].x[0]=-5;
	world.Groups[0].Polygons[1].y[0]=5;
	world.Groups[0].Polygons[1].z[0]=-5;
	world.Groups[0].Polygons[1].x[1]=5;
	world.Groups[0].Polygons[1].y[1]=5;
	world.Groups[0].Polygons[1].z[1]=-5;
	world.Groups[0].Polygons[1].x[2]=0;
	world.Groups[0].Polygons[1].y[2]=0;
	world.Groups[0].Polygons[1].z[2]=5;

	world.Groups[0].Polygons[2].color=RGB(255,0,0);
	world.Groups[0].Polygons[2].PointCount=3;
	//world.Groups[0].Polygons[2].x=new double[3];
	//world.Groups[0].Polygons[2].y=new double[3];
	//world.Groups[0].Polygons[2].z=new double[3];

	world.Groups[0].Polygons[2].x[0]=-5;
	world.Groups[0].Polygons[2].y[0]=-5;
	world.Groups[0].Polygons[2].z[0]=-5;
	world.Groups[0].Polygons[2].x[1]=-5;
	world.Groups[0].Polygons[2].y[1]=5;
	world.Groups[0].Polygons[2].z[1]=-5;
	world.Groups[0].Polygons[2].x[2]=0;
	world.Groups[0].Polygons[2].y[2]=0;
	world.Groups[0].Polygons[2].z[2]=5;

	world.Groups[0].Polygons[3].color=RGB(255,0,0);
	world.Groups[0].Polygons[3].PointCount=3;
	//world.Groups[0].Polygons[3].x=new double[3];
	//world.Groups[0].Polygons[3].y=new double[3];
	//world.Groups[0].Polygons[3].z=new double[3];

	world.Groups[0].Polygons[3].x[0]=5;
	world.Groups[0].Polygons[3].y[0]=-5;
	world.Groups[0].Polygons[3].z[0]=-5;
	world.Groups[0].Polygons[3].x[1]=5;
	world.Groups[0].Polygons[3].y[1]=5;
	world.Groups[0].Polygons[3].z[1]=-5;
	world.Groups[0].Polygons[3].x[2]=0;
	world.Groups[0].Polygons[3].y[2]=0;
	world.Groups[0].Polygons[3].z[2]=5;

	world.Groups[0].Polygons[4].color=RGB(255,0,0);
	world.Groups[0].Polygons[4].PointCount=4;
	//world.Groups[0].Polygons[4].x=new double[4];
	//world.Groups[0].Polygons[4].y=new double[4];
	//world.Groups[0].Polygons[4].z=new double[4];

	world.Groups[0].Polygons[4].x[0]=-5;
	world.Groups[0].Polygons[4].y[0]=-5;
	world.Groups[0].Polygons[4].z[0]=-5;
	world.Groups[0].Polygons[4].x[1]=-5;
	world.Groups[0].Polygons[4].y[1]=5;
	world.Groups[0].Polygons[4].z[1]=-5;
	world.Groups[0].Polygons[4].x[2]=5;
	world.Groups[0].Polygons[4].y[2]=5;
	world.Groups[0].Polygons[4].z[2]=-5;
	world.Groups[0].Polygons[4].x[3]=5;
	world.Groups[0].Polygons[4].y[3]=-5;
	world.Groups[0].Polygons[4].z[3]=-5;

	//Triangular Prism
	world.Groups[1].Polygons[0].color=RGB(0,255,0);
	world.Groups[1].Polygons[0].PointCount=3;
	//world.Groups[1].Polygons[0].x=new double[3];
	//world.Groups[1].Polygons[0].y=new double[3];
	//world.Groups[1].Polygons[0].z=new double[3];

	world.Groups[1].Polygons[0].x[0]=-5;
	world.Groups[1].Polygons[0].y[0]=-5;
	world.Groups[1].Polygons[0].z[0]=-5;
	world.Groups[1].Polygons[0].x[1]=5;
	world.Groups[1].Polygons[0].y[1]=-5;
	world.Groups[1].Polygons[0].z[1]=-5;
	world.Groups[1].Polygons[0].x[2]=0;
	world.Groups[1].Polygons[0].y[2]=-5;
	world.Groups[1].Polygons[0].z[2]=5;

	world.Groups[1].Polygons[1].color=RGB(0,255,0);
	world.Groups[1].Polygons[1].PointCount=3;
	//world.Groups[1].Polygons[1].x=new double[3];
	//world.Groups[1].Polygons[1].y=new double[3];
	//world.Groups[1].Polygons[1].z=new double[3];

	world.Groups[1].Polygons[1].x[0]=-5;
	world.Groups[1].Polygons[1].y[0]=5;
	world.Groups[1].Polygons[1].z[0]=-5;
	world.Groups[1].Polygons[1].x[1]=0;
	world.Groups[1].Polygons[1].y[1]=5;
	world.Groups[1].Polygons[1].z[1]=5;
	world.Groups[1].Polygons[1].x[2]=5;
	world.Groups[1].Polygons[1].y[2]=5;
	world.Groups[1].Polygons[1].z[2]=-5;

	world.Groups[1].Polygons[2].color=RGB(0,255,0);
	world.Groups[1].Polygons[2].PointCount=4;
	//world.Groups[1].Polygons[2].x=new double[4];
	//world.Groups[1].Polygons[2].y=new double[4];
	//world.Groups[1].Polygons[2].z=new double[4];

	world.Groups[1].Polygons[2].x[0]=5;
	world.Groups[1].Polygons[2].y[0]=-5;
	world.Groups[1].Polygons[2].z[0]=-5;
	world.Groups[1].Polygons[2].x[1]=5;
	world.Groups[1].Polygons[2].y[1]=5;
	world.Groups[1].Polygons[2].z[1]=-5;
	world.Groups[1].Polygons[2].x[2]=0;
	world.Groups[1].Polygons[2].y[2]=5;
	world.Groups[1].Polygons[2].z[2]=5;
	world.Groups[1].Polygons[2].x[3]=0;
	world.Groups[1].Polygons[2].y[3]=-5;
	world.Groups[1].Polygons[2].z[3]=5;

	world.Groups[1].Polygons[3].color=RGB(0,255,0);
	world.Groups[1].Polygons[3].PointCount=4;
	//world.Groups[1].Polygons[3].x=new double[4];
	//world.Groups[1].Polygons[3].y=new double[4];
	//world.Groups[1].Polygons[3].z=new double[4];

	world.Groups[1].Polygons[3].x[0]=-5;
	world.Groups[1].Polygons[3].y[0]=-5;
	world.Groups[1].Polygons[3].z[0]=-5;
	world.Groups[1].Polygons[3].x[1]=-5;
	world.Groups[1].Polygons[3].y[1]=5;
	world.Groups[1].Polygons[3].z[1]=-5;
	world.Groups[1].Polygons[3].x[2]=0;
	world.Groups[1].Polygons[3].y[2]=5;
	world.Groups[1].Polygons[3].z[2]=5;
	world.Groups[1].Polygons[3].x[3]=0;
	world.Groups[1].Polygons[3].y[3]=-5;
	world.Groups[1].Polygons[3].z[3]=5;

	world.Groups[1].Polygons[4].color=RGB(0,255,0);
	world.Groups[1].Polygons[4].PointCount=4;
	//world.Groups[1].Polygons[4].x=new double[4];
	//world.Groups[1].Polygons[4].y=new double[4];
	//world.Groups[1].Polygons[4].z=new double[4];

	world.Groups[1].Polygons[4].x[0]=-5;
	world.Groups[1].Polygons[4].y[0]=-5;
	world.Groups[1].Polygons[4].z[0]=-5;
	world.Groups[1].Polygons[4].x[1]=5;
	world.Groups[1].Polygons[4].y[1]=-5;
	world.Groups[1].Polygons[4].z[1]=-5;
	world.Groups[1].Polygons[4].x[2]=5;
	world.Groups[1].Polygons[4].y[2]=5;
	world.Groups[1].Polygons[4].z[2]=-5;
	world.Groups[1].Polygons[4].x[3]=-5;
	world.Groups[1].Polygons[4].y[3]=5;
	world.Groups[1].Polygons[4].z[3]=-5;

	//Cube
	world.Groups[2].Polygons[0].color=RGB(0,0,255);
	world.Groups[2].Polygons[0].PointCount=4;
	//world.Groups[2].Polygons[0].x=new double[4];
	//world.Groups[2].Polygons[0].y=new double[4];
	//world.Groups[2].Polygons[0].z=new double[4];

	world.Groups[2].Polygons[0].x[0]=-5;
	world.Groups[2].Polygons[0].y[0]=-5;
	world.Groups[2].Polygons[0].z[0]=-5;
	world.Groups[2].Polygons[0].x[1]=-5;
	world.Groups[2].Polygons[0].y[1]=-5;
	world.Groups[2].Polygons[0].z[1]=5;
	world.Groups[2].Polygons[0].x[2]=5;
	world.Groups[2].Polygons[0].y[2]=-5;
	world.Groups[2].Polygons[0].z[2]=5;
	world.Groups[2].Polygons[0].x[3]=5;
	world.Groups[2].Polygons[0].y[3]=-5;
	world.Groups[2].Polygons[0].z[3]=-5;

	world.Groups[2].Polygons[1].color=RGB(0,0,255);
	world.Groups[2].Polygons[1].PointCount=4;
	//world.Groups[2].Polygons[1].x=new double[4];
	//world.Groups[2].Polygons[1].y=new double[4];
	//world.Groups[2].Polygons[1].z=new double[4];

	world.Groups[2].Polygons[1].x[0]=-5;
	world.Groups[2].Polygons[1].y[0]=-5;
	world.Groups[2].Polygons[1].z[0]=-5;
	world.Groups[2].Polygons[1].x[1]=-5;
	world.Groups[2].Polygons[1].y[1]=5;
	world.Groups[2].Polygons[1].z[1]=-5;
	world.Groups[2].Polygons[1].x[2]=5;
	world.Groups[2].Polygons[1].y[2]=5;
	world.Groups[2].Polygons[1].z[2]=-5;
	world.Groups[2].Polygons[1].x[3]=5;
	world.Groups[2].Polygons[1].y[3]=-5;
	world.Groups[2].Polygons[1].z[3]=-5;

	world.Groups[2].Polygons[2].color=RGB(0,0,255);
	world.Groups[2].Polygons[2].PointCount=4;
	//world.Groups[2].Polygons[2].x=new double[4];
	//world.Groups[2].Polygons[2].y=new double[4];
	//world.Groups[2].Polygons[2].z=new double[4];

	world.Groups[2].Polygons[2].x[0]=-5;
	world.Groups[2].Polygons[2].y[0]=-5;
	world.Groups[2].Polygons[2].z[0]=-5;
	world.Groups[2].Polygons[2].x[1]=-5;
	world.Groups[2].Polygons[2].y[1]=5;
	world.Groups[2].Polygons[2].z[1]=-5;
	world.Groups[2].Polygons[2].x[2]=-5;
	world.Groups[2].Polygons[2].y[2]=5;
	world.Groups[2].Polygons[2].z[2]=5;
	world.Groups[2].Polygons[2].x[3]=-5;
	world.Groups[2].Polygons[2].y[3]=-5;
	world.Groups[2].Polygons[2].z[3]=5;

	world.Groups[2].Polygons[3].color=RGB(0,0,255);
	world.Groups[2].Polygons[3].PointCount=4;
	//world.Groups[2].Polygons[3].x=new double[4];
	//world.Groups[2].Polygons[3].y=new double[4];
	//world.Groups[2].Polygons[3].z=new double[4];

	world.Groups[2].Polygons[3].x[0]=-5;
	world.Groups[2].Polygons[3].y[0]=-5;
	world.Groups[2].Polygons[3].z[0]=5;
	world.Groups[2].Polygons[3].x[1]=-5;
	world.Groups[2].Polygons[3].y[1]=5;
	world.Groups[2].Polygons[3].z[1]=5;
	world.Groups[2].Polygons[3].x[2]=5;
	world.Groups[2].Polygons[3].y[2]=5;
	world.Groups[2].Polygons[3].z[2]=5;
	world.Groups[2].Polygons[3].x[3]=5;
	world.Groups[2].Polygons[3].y[3]=-5;
	world.Groups[2].Polygons[3].z[3]=5;

	world.Groups[2].Polygons[4].color=RGB(0,0,255);
	world.Groups[2].Polygons[4].PointCount=4;
	//world.Groups[2].Polygons[4].x=new double[4];
	//world.Groups[2].Polygons[4].y=new double[4];
	//world.Groups[2].Polygons[4].z=new double[4];

	world.Groups[2].Polygons[4].x[0]=-5;
	world.Groups[2].Polygons[4].y[0]=5;
	world.Groups[2].Polygons[4].z[0]=-5;
	world.Groups[2].Polygons[4].x[1]=5;
	world.Groups[2].Polygons[4].y[1]=5;
	world.Groups[2].Polygons[4].z[1]=-5;
	world.Groups[2].Polygons[4].x[2]=5;
	world.Groups[2].Polygons[4].y[2]=5;
	world.Groups[2].Polygons[4].z[2]=5;
	world.Groups[2].Polygons[4].x[3]=-5;
	world.Groups[2].Polygons[4].y[3]=5;
	world.Groups[2].Polygons[4].z[3]=5;

	world.Groups[2].Polygons[5].color=RGB(0,0,255);
	world.Groups[2].Polygons[5].PointCount=4;
	//world.Groups[2].Polygons[5].x=new double[4];
	//world.Groups[2].Polygons[5].y=new double[4];
	//world.Groups[2].Polygons[5].z=new double[4];

	world.Groups[2].Polygons[5].x[0]=5;
	world.Groups[2].Polygons[5].y[0]=-5;
	world.Groups[2].Polygons[5].z[0]=-5;
	world.Groups[2].Polygons[5].x[1]=5;
	world.Groups[2].Polygons[5].y[1]=5;
	world.Groups[2].Polygons[5].z[1]=-5;
	world.Groups[2].Polygons[5].x[2]=5;
	world.Groups[2].Polygons[5].y[2]=5;
	world.Groups[2].Polygons[5].z[2]=5;
	world.Groups[2].Polygons[5].x[3]=5;
	world.Groups[2].Polygons[5].y[3]=-5;
	world.Groups[2].Polygons[5].z[3]=5;

	//wall
	world.Groups[3].Polygons[0].color=RGB(0,255,255);
	world.Groups[3].Polygons[0].PointCount=4;
	//world.Groups[3].Polygons[0].x=new double[4];
	//world.Groups[3].Polygons[0].y=new double[4];
	//world.Groups[3].Polygons[0].z=new double[4];

	world.Groups[3].Polygons[0].x[0]=-5;
	world.Groups[3].Polygons[0].y[0]=world.wall;
	world.Groups[3].Polygons[0].z[0]=0;
	world.Groups[3].Polygons[0].x[1]=5;
	world.Groups[3].Polygons[0].y[1]=world.wall;
	world.Groups[3].Polygons[0].z[1]=0;
	world.Groups[3].Polygons[0].x[2]=5;
	world.Groups[3].Polygons[0].y[2]=world.wall-5;
	world.Groups[3].Polygons[0].z[2]=0;
	world.Groups[3].Polygons[0].x[3]=-5;
	world.Groups[3].Polygons[0].y[3]=world.wall-5;
	world.Groups[3].Polygons[0].z[3]=0;

	/*hand
	world.Groups[1].Polygons=new CPolygon[4];
	world.Groups[1].PolygonCount=4;
	world.Groups[1].a=0;

	world.Groups[1].Polygons[0].PointCount=6;
	world.Groups[1].Polygons[0].x=new double[6];
	world.Groups[1].Polygons[0].y=new double[6];
	world.Groups[1].Polygons[0].z=new double[6];

	world.Groups[1].Polygons[0].x[0]=0;
	world.Groups[1].Polygons[0].y[0]=0;
	world.Groups[1].Polygons[0].z[0]=0;*/
}
