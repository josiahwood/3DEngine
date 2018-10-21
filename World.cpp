// World.cpp: implementation of the CWorld class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "3DEngine.h"
#include "World.h"
#include <math.h>
//#include <d3dtypes.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#ifndef M_PI
#define M_PI 3.1415927
#endif

#define RGB_GETBLUE(rgb)    (((rgb) >> 16) & 0xff)
#define RGB_GETGREEN(rgb)    (((rgb) >> 8) & 0xff)
#define RGB_GETRED(rgb)    ((rgb) & 0xff)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWorld::CWorld()
{
	GroupCount=0;
	//PolygonCount=0;
	wall=1;

	DrawCount=0;

	brush=new CBrush;
	pen=new CPen;

	zbuffer=new double[1];

	vw=0;
	vh=0;

	control=-1;
}

CWorld::~CWorld()
{
	//if(PolygonCount>0)
	//	delete[]Polygons;
	if(GroupCount>0)
		delete[]Groups;
	if(LightCount>0)
		delete[]Lights;

	delete brush;
	delete pen;
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
	dc=aWorld.dc;
	DrawCount=aWorld.DrawCount;
	if(GroupCount>0)
		delete[]Groups;
	GroupCount=aWorld.GroupCount;
	Groups=new CGroup[GroupCount];
	for(int x=0;x<GroupCount;x++)
		Groups[x]=aWorld.Groups[x];

	//if(PolygonCount>0)
	//	delete[]Polygons;
	//PolygonCount=aWorld.PolygonCount;
	//Polygons=new CPolygon[PolygonCount];
	//for(x=0;x<PolygonCount;x++)
	//	Polygons[x]=aWorld.Polygons[x];
	Polygons.Copy(aWorld.Polygons);

	vh=aWorld.vh;
	vw=aWorld.vw;

	wall=aWorld.wall;

	return *this;
}

void CWorld::DrawPolygons()
{	
	brush->CreateSolidBrush(RGB(0,0,0));
	oldbrush=dc->SelectObject(brush);
	
	dc->Rectangle(0,0,vw,vh);

	dc->SelectObject(oldbrush);
	brush->DeleteObject();
	
	/*int index=-1;
	
	for(int x=0;x<Polygons.GetSize();x++)
	{
		if(Polygons[x].orderignore)
		{
			for(int y=0;y<Polygons.GetSize();y++)
			{
				if(!Polygons[y].orderignore && (Polygons[x].dist>Polygons[y].dist))
				{
					index=y;
					break;
				}
			}
			if(index==-1)
				index==Polygons.GetSize();

			Polygons[x].orderignore=false;

			CPolygon tp=Polygons[x];
			
			Polygons.InsertAt(index,tp);

			if(index<=x)
				x++;

			Polygons.RemoveAt(x);
			x=-1;
		}
	}*/
	
	for(int x=0;x<Polygons.GetSize();x++)
		DrawPolygon(&Polygons[x]);
}

#define complex 0
#define notcomplex 1

void CWorld::AddPolygon(CPolygon *Polygon)
{
	int index=0;
	int x;
	
#if notcomplex
	double dist=0;//,dist2=0;
	
	for(x=0;x<Polygon->PointCount;x++)
		dist+=sqrt(sqr(Polygon->x[x])+sqr(Polygon->y[x])+sqr(Polygon->z[x]));
	dist/=Polygon->PointCount;
	Polygon->dist=dist;

#else

	if(!Polygon->split)
		Polygon->color=RGB(0,255,0);
	
	double t1x,t1y,t1z,t2x,t2y,t2z,lv;
	double x1=Polygon->x[0];
	double y1=Polygon->y[0];
	double z1=Polygon->z[0];

	double x2=Polygon->x[1];
	double y2=Polygon->y[1];
	double z2=Polygon->z[1];

	double x3=Polygon->x[2];
	double y3=Polygon->y[2];
	double z3=Polygon->z[2];
	
	t1x=x2-x1;
	t1y=y2-y1;
	t1z=z2-z1;
	t2x=x3-x1;
	t2y=y3-y1;
	t2z=z3-z1;

	Polygon->Nx=t1y*t2z-t1z*t2y;
	Polygon->Ny=t1z*t2x-t1x*t2z;
	Polygon->Nz=t1x*t2y-t1y*t2x;

	lv=sqrt(sqr(Polygon->Nx)+sqr(Polygon->Ny)+sqr(Polygon->Nz));
	Polygon->Nx/=lv;
	Polygon->Ny/=lv;
	Polygon->Nz/=lv;

	Polygon->Sd=(Polygon->Nx * x1)+(Polygon->Ny * y1)+(Polygon->Nz * z1);
	if(Polygon->Sd<0)
	{
		Polygon->Nx=-Polygon->Nx;
		Polygon->Ny=-Polygon->Ny;
		Polygon->Nz=-Polygon->Nz;
		Polygon->Sd=-Polygon->Sd;
	}

	double front=0;
	double behind=0;
	double val,sd;
	double nx,ny,nz;
	int y;
#endif

	index=-1;

	for(x=0;x<Polygons.GetSize();x++)
	{
#if complex
		if(Polygons[x].orderignore)
			continue;
		
		front=0;
		behind=0;

		for(y=0;y<Polygon->PointCount;y++)
		{
			sd=Polygons[x].Sd;
			x1=Polygon->x[y];
			y1=Polygon->y[y];
			z1=Polygon->z[y];
			nx=Polygons[x].Nx;
			ny=Polygons[x].Ny;
			nz=Polygons[x].Nz;
			val=(nx * x1)+(ny * y1)+(nz * z1);

			if((val-sd)>behind)
				behind=val-sd;
			else if((sd-val)>front)
				front=sd-val;
		}

		if(front && behind)
		{
			front=0;
			behind=0;

			for(y=0;y<Polygons[x].PointCount;y++)
			{
				sd=Polygon->Sd;
				x1=Polygons[x].x[y];
				y1=Polygons[x].y[y];
				z1=Polygons[x].z[y];
				nx=Polygon->Nx;
				ny=Polygon->Ny;
				nz=Polygon->Nz;
				val=(nx * x1)+(ny * y1)+(nz * z1);

				if((val-sd)>front)
					front=val-sd;
				else if((sd-val)>behind)
					behind=sd-val;
			}	
		}
		
		if(front && behind && false)
		{
			CPolygon Poly1=Polygons[x];
			CPolygon Poly2=*Polygon;

			for(int z=0;z<2;z++)
			{
				if(z)
				{
					Poly1=*Polygon;
					Poly2=Polygons[x];
				}

				CPolygon PolyB, PolyF;

				PolyB.split=x+1;
				PolyB.color=RGB(255,0,0);

				PolyF.split=x+1;
				PolyF.color=RGB(0,0,255);

				PolyB.PointCount=0;
				int pcb=0;

				PolyF.PointCount=0;
				int pcf=0;

				double Na,len;
				
				for(y=0;y<Poly2.PointCount;y++)
				{
					len=_hypot(Poly2.x[y],Poly2.y[y]);
					Na=-(GetA(Poly1.Nx,Poly1.Ny)-90);
					Na+=GetA(Poly2.x[y],Poly2.y[y]);
					Poly2.x[y]=cos(Na/180*M_PI)*len;
					Poly2.y[y]=sin(Na/180*M_PI)*len;
					
					len=_hypot(Poly2.y[y],Poly2.z[y]);
					Na=-GetA(_hypot(Poly1.Nx,Poly1.Ny),Poly1.Nz);
					Na+=GetA(Poly2.y[y],Poly2.z[y]);
					Poly2.y[y]=cos(Na/180*M_PI)*len;
					Poly2.z[y]=sin(Na/180*M_PI)*len;
				}

				int less,more;
				double bwall=Poly1.Sd+.1;
				double fwall=Poly1.Sd-.1;

				double sx,sy,sz,nx,ny,nz;
				
				for(int c=0;c<Poly2.PointCount;c++)
				{
					if(Poly2.y[c]>bwall)
					{
						PolyB.x[pcb]=Poly2.x[c];
						PolyB.y[pcb]=Poly2.y[c];
						PolyB.z[pcb]=Poly2.z[c];
						pcb++;
					}
					else
					{
						less=c-1;
						if(less==-1)
							less=Poly2.PointCount-1;

						more=c+1;
						if(more==Poly2.PointCount)
							more=0;

						if(Poly2.y[less]>bwall)
						{
							sx=Poly2.x[less]-Poly2.x[c];
							sy=Poly2.y[less]-Poly2.y[c];
							sz=Poly2.z[less]-Poly2.z[c];
							nx=Poly2.x[c]+((sx/sy) * (bwall-Poly2.y[c]));
							ny=bwall;
							nz=Poly2.z[c]+((sz/sy) * (bwall-Poly2.y[c]));

							PolyB.x[pcb]=nx;
							PolyB.y[pcb]=ny;
							PolyB.z[pcb]=nz;
							pcb++;
						}
						
						if(Poly2.y[more]>bwall)
						{
							sx=Poly2.x[more]-Poly2.x[c];
							sy=Poly2.y[more]-Poly2.y[c];
							sz=Poly2.z[more]-Poly2.z[c];
							nx=Poly2.x[c]+((sx/sy) * (bwall-Poly2.y[c]));
							ny=bwall;
							nz=Poly2.z[c]+((sz/sy) * (bwall-Poly2.y[c]));

							PolyB.x[pcb]=nx;
							PolyB.y[pcb]=ny;
							PolyB.z[pcb]=nz;
							pcb++;
						}
					}
					
					//front
					if(Poly2.y[c]<fwall)
					{
						PolyF.x[pcf]=Poly2.x[c];
						PolyF.y[pcf]=Poly2.y[c];
						PolyF.z[pcf]=Poly2.z[c];
						pcf++;
					}
					else
					{
						less=c-1;
						if(less==-1)
							less=Poly2.PointCount-1;

						more=c+1;
						if(more==Poly2.PointCount)
							more=0;

						if(Poly2.y[less]<fwall)
						{
							sx=Poly2.x[less]-Poly2.x[c];
							sy=Poly2.y[less]-Poly2.y[c];
							sz=Poly2.z[less]-Poly2.z[c];
							nx=Poly2.x[c]+((sx/sy) * (fwall-Poly2.y[c]));
							ny=fwall;
							nz=Poly2.z[c]+((sz/sy) * (fwall-Poly2.y[c]));

							PolyF.x[pcf]=nx;
							PolyF.y[pcf]=ny;
							PolyF.z[pcf]=nz;
							pcf++;
						}
						
						if(Poly2.y[more]<fwall)
						{
							sx=Poly2.x[more]-Poly2.x[c];
							sy=Poly2.y[more]-Poly2.y[c];
							sz=Poly2.z[more]-Poly2.z[c];
							nx=Poly2.x[c]+((sx/sy) * (fwall-Poly2.y[c]));
							ny=fwall;
							nz=Poly2.z[c]+((sz/sy) * (fwall-Poly2.y[c]));

							PolyF.x[pcf]=nx;
							PolyF.y[pcf]=ny;
							PolyF.z[pcf]=nz;
							pcf++;
						}
					}
				}

				for(y=0;y<Poly2.PointCount;y++)
				{
					len=_hypot(Poly2.y[y],Poly2.z[y]);
					Na=GetA(_hypot(Poly1.Nx,Poly1.Ny),Poly1.Nz);
					Na+=GetA(Poly2.y[y],Poly2.z[y]);
					Poly2.y[y]=cos(Na/180*M_PI)*len;
					Poly2.z[y]=sin(Na/180*M_PI)*len;

					len=_hypot(Poly2.x[y],Poly2.y[y]);
					Na=GetA(Poly1.Nx,Poly1.Ny)-90;
					Na+=GetA(Poly2.x[y],Poly2.y[y]);
					Poly2.x[y]=cos(Na/180*M_PI)*len;
					Poly2.y[y]=sin(Na/180*M_PI)*len;
				}

				PolyB.PointCount=pcb;
				PolyF.PointCount=pcf;
				
				for(y=0;y<pcb;y++)
				{
					len=_hypot(PolyB.y[y],PolyB.z[y]);
					Na=GetA(_hypot(Poly1.Nx,Poly1.Ny),Poly1.Nz);
					Na+=GetA(PolyB.y[y],PolyB.z[y]);
					PolyB.y[y]=cos(Na/180*M_PI)*len;
					PolyB.z[y]=sin(Na/180*M_PI)*len;

					len=_hypot(PolyB.x[y],PolyB.y[y]);
					Na=GetA(Poly1.Nx,Poly1.Ny)-90;
					Na+=GetA(PolyB.x[y],PolyB.y[y]);
					PolyB.x[y]=cos(Na/180*M_PI)*len;
					PolyB.y[y]=sin(Na/180*M_PI)*len;
				}

				for(y=0;y<pcf;y++)
				{
					len=_hypot(PolyF.y[y],PolyF.z[y]);
					Na=GetA(_hypot(Poly1.Nx,Poly1.Ny),Poly1.Nz);
					Na+=GetA(PolyF.y[y],PolyF.z[y]);
					PolyF.y[y]=cos(Na/180*M_PI)*len;
					PolyF.z[y]=sin(Na/180*M_PI)*len;

					len=_hypot(PolyF.x[y],PolyF.y[y]);
					Na=GetA(Poly1.Nx,Poly1.Ny)-90;
					Na+=GetA(PolyF.x[y],PolyF.y[y]);
					PolyF.x[y]=cos(Na/180*M_PI)*len;
					PolyF.y[y]=sin(Na/180*M_PI)*len;
				}
				
				if(pcb>=3)
					AddPolygon(&PolyB);
				if(pcf>=3)
					AddPolygon(&PolyF);

				if(z)
					return;
			}
		}

		if(index!=-1 && front)
		{
			//return;
			Polygon->orderignore=true;
			break;
		}
		else if(index==-1 && behind/*Polygon->dist>Polygons[x].dist*/)
		{	
			Polygon->orderignore=false;
			index=x;
			//break;
		}
		/*else if(!behind && !front)
		{
			if(Polygon->dist>Polygons[x].dist)
			{
				index=x;
				break; 
			}
		}*/

#else
		if(Polygon->dist>Polygons[x].dist)
		{
			index=x;
			break;
		}
#endif
	}

	if(index==-1)
		Polygons.Add(*Polygon);
	else
		Polygons.InsertAt(index,*Polygon);
}

void CWorld::DrawPolygon(CPolygon *Polygon)
{
	double a,t;

	POINT* points;
	points=new POINT[Polygon->PointCount * 2];

	int pc=0,less,more;
	double sx,sy,sz,nx,nz;

	for(int c=0;c<Polygon->PointCount;c++)
	{
		if(Polygon->y[c]>wall)
		{
			a=Polygon->x[c]/Polygon->y[c];
			t=Polygon->z[c]/Polygon->y[c];

			points[pc].x=((a/.5) * (vw/2))+(vw/2);
			points[pc].y=(vh/2)-((t/(.5*(vh/vw))) * (vh/2));
			pc++;
		}
		else
		{
			less=c-1;
			if(less==-1)
				less=Polygon->PointCount-1;

			more=c+1;
			if(more==Polygon->PointCount)
				more=0;

			if(Polygon->y[less]>wall)
			{
				sx=Polygon->x[less]-Polygon->x[c];
				sy=Polygon->y[less]-Polygon->y[c];
				sz=Polygon->z[less]-Polygon->z[c];
				nx=Polygon->x[c]+((sx/sy) * (wall-Polygon->y[c]));
				nz=Polygon->z[c]+((sz/sy) * (wall-Polygon->y[c]));

				a=nx/wall;
				t=nz/wall;

				points[pc].x=((a/.5) * (vw/2))+(vw/2);
				points[pc].y=(vh/2)-((t/(.5*(vh/vw))) * (vh/2));
				pc++;
			}
			
			if(Polygon->y[more]>wall)
			{
				sx=Polygon->x[more]-Polygon->x[c];
				sy=Polygon->y[more]-Polygon->y[c];
				sz=Polygon->z[more]-Polygon->z[c];
				nx=Polygon->x[c]+((sx/sy) * (wall-Polygon->y[c]));
				nz=Polygon->z[c]+((sz/sy) * (wall-Polygon->y[c]));

				a=nx/wall;
				t=nz/wall;

				points[pc].x=((a/.5) * (vw/2))+(vw/2);
				points[pc].y=(vh/2)-((t/(.5*(vh/vw))) * (vh/2));
				pc++;
			}
		}
	}

	COLORREF col;
	COLORREF cblack=RGB(0,0,0);
	
	if(pc>0)
	{	
		brush->CreateSolidBrush(Polygon->dcolor);
		oldbrush=dc->SelectObject(brush);

		//pen->CreatePen(PS_NULL,0,RGB(0,0,0));
		//oldpen=dc->SelectObject(pen);

		dc->Polygon(points,pc);

		dc->SelectObject(oldbrush);
		brush->DeleteObject();

		//dc->SelectObject(oldpen);
		//pen->DeleteObject();

		/*if(vw>1000)
			vw=0;

		for(int x=0;x<vw;x++)
		{
			for(int y=0;y<vh;y++)
			{
				col=tdc.GetPixel(x,y);
				if(col)
				{
					dc->SetPixelV(x,y,col);
					tdc.SetPixelV(x,y,cblack);
				}
			}
		}*/
	}

	delete[]points;

	return;
}

double CWorld::GetA(double x, double y)
{
	double a;

	if(x==0)
	{
		if(y>0)
			a=90;
		else if(y<0)
			a=270;
		else
			a=0;
	}
	else
	{
		a=atan(y/x)/3.14159*180;
		if(x<0)
			a+=180;
		else if(y<0)
			a+=360;
	}

	return a;
}

void CWorld::Draw()
{
	if(ca<0)
		ca+=360;
	if(ca>=360)
		ca-=360;
	if(ct<0)
		ct+=360;
	if(ct>=360)
		ct-=360;

	//Physics();

	UpdateWall();
	
	Polygons.RemoveAll();

	CPolygon pg;
	double a,t,p,d,ta,td;

	int x,y,z;

	for(x=0;x<GroupCount;x++)
	{
		if(Groups[x].Visible)
		{
			for(y=0;y<Groups[x].Polygons.GetSize();y++)
			{
				pg=Groups[x].Polygons[y];

				double xt=0,yt=0,zt=0;

				for(z=0;z<Groups[x].Polygons[y].PointCount;z++)
				{
					xt+=pg.x[z];
					yt+=pg.y[z];
					zt+=pg.z[z];
				}
				
				xt/=Groups[x].Polygons[y].PointCount;
				yt/=Groups[x].Polygons[y].PointCount;
				zt/=Groups[x].Polygons[y].PointCount;

				double len=Groups[x].exp/sqrt(sqr(xt)+sqr(yt)+sqr(zt))+1;
				
				double dxt=xt*len;
				double dyt=yt*len;
				double dzt=zt*len;

				dxt-=xt;
				dyt-=yt;
				dzt-=zt;

				for(z=0;z<Groups[x].Polygons[y].PointCount;z++)
				{
					pg.x[z]+=dxt;
					pg.y[z]+=dyt;
					pg.z[z]+=dzt;
				}
				
				for(z=0;z<Groups[x].Polygons[y].PointCount;z++)
				{
					if(pg.y[z]!=0 || pg.z[z]!=0)
					{
						d=_hypot(pg.y[z],pg.z[z]);
						t=GetA(pg.y[z],pg.z[z]);
						t+=Groups[x].t;

						pg.y[z]=cos(t/180*M_PI)*d;
						pg.z[z]=sin(t/180*M_PI)*d;
					}
					if(pg.x[z]!=0 || pg.z[z]!=0)
					{
						d=_hypot(pg.x[z],pg.z[z]);
						p=GetA(pg.x[z],pg.z[z]);
						p+=Groups[x].p;

						pg.x[z]=cos(p/180*M_PI)*d;
						pg.z[z]=sin(p/180*M_PI)*d;
					}
					if(pg.x[z]!=0 || pg.y[z]!=0)
					{
						d=_hypot(pg.x[z],pg.y[z]);
						a=GetA(pg.x[z],pg.y[z]);
						a+=Groups[x].a;

						pg.x[z]=cos(a/180*M_PI)*d;
						pg.y[z]=sin(a/180*M_PI)*d;
					}

					pg.x[z]+=Groups[x].x;
					pg.y[z]+=Groups[x].y;
					pg.z[z]+=Groups[x].z;
					
					Groups[x].Polygons[y].tx[z]=pg.x[z];
					Groups[x].Polygons[y].ty[z]=pg.y[z];
					Groups[x].Polygons[y].tz[z]=pg.z[z];
					
					pg.x[z]-=cx;
					pg.y[z]-=cy;
					pg.z[z]-=cz;

					ta=GetA(pg.x[z],pg.y[z])-(ca-90);
					td=_hypot(pg.x[z],pg.y[z]);
					pg.x[z]=cos(ta/180*M_PI)*td;
					pg.y[z]=sin(ta/180*M_PI)*td;

					ta=GetA(pg.y[z],pg.z[z])-ct;
					td=_hypot(pg.y[z],pg.z[z]);
					pg.y[z]=cos(ta/180*M_PI)*td;
					pg.z[z]=sin(ta/180*M_PI)*td;
				}

				AddPolygon(&pg);
			}
		}
	}
	DrawLight(&Lights[0]);
	DrawPolygons();

	//DrawRadar();
	//DrawCount++;
}

#define Lighting 1
#define Glasses 0

void CWorld::DrawLight(CLight *Light)
{
#if Lighting
	double x1,x2,x3,y1,y2,y3,z1,z2,z3,xv,yv,zv,lv;
	for(int x=0;x<Polygons.GetSize();x++)
	{
		x1=Polygons[x].x[0];
		y1=Polygons[x].y[0];
		z1=Polygons[x].z[0];
		x2=Polygons[x].x[1];
		y2=Polygons[x].y[1];
		z2=Polygons[x].z[1];
		x3=Polygons[x].x[2];
		y3=Polygons[x].y[2];
		z3=Polygons[x].z[2];

		double t1x,t1y,t1z,t2x,t2y,t2z;
		t1x=x1-x2;
		t1y=y1-y2;
		t1z=z1-z2;
		t2x=x3-x2;
		t2y=y3-y2;
		t2z=z3-z2;

		xv=t1y*t2z-t1z*t2y;
		yv=t1z*t2x-t1x*t2z;
		zv=t1x*t2y-t1y*t2x;
		lv=sqrt(sqr(xv)+sqr(yv)+sqr(zv));
		xv/=lv;
		yv/=lv;
		zv/=lv;
		//lv=1;
		//<xv,yv,zv> is now the unit-normal of the polygon

		double xa=0,ya=0,za=0;
		for(int y=0;y<Polygons[x].PointCount;y++)
		{
			xa+=Polygons[x].x[y];
			ya+=Polygons[x].y[y];
			za+=Polygons[x].z[y];
		}
		xa/=Polygons[x].PointCount;
		ya/=Polygons[x].PointCount;
		za/=Polygons[x].PointCount;

		
		double dx,dy,dz;
		dx=Light->x-cx;
		dy=Light->y-cy;
		dz=Light->z-cz;

		double ta,td;
		ta=GetA(dx,dy)-(ca-90);
		td=_hypot(dx,dy);
		dx=cos(ta/180*M_PI)*td;
		dy=sin(ta/180*M_PI)*td;

		ta=GetA(dy,dz)-ct;
		td=_hypot(dy,dz);
		dy=cos(ta/180*M_PI)*td;
		dz=sin(ta/180*M_PI)*td;

		double d,distp,dist;
		d=-((x1*xv)+(y1*yv)+(z1*zv));
		dist=sqrt(sqr(xa-dx)+sqr(ya-dy)+sqr(za-dz));
		
		distp=(xv*dx)+(yv*dy)+(zv*dz)+d;
		if(distp<0)
			distp=-distp;
		double z=distp/dist;
		
		double ang=(z*.9)+.1;
		int nr,ng,nb;
		nb=(double)RGB_GETBLUE(Polygons[x].color)*ang;
		ng=(double)RGB_GETGREEN(Polygons[x].color)*ang;
		nr=(double)RGB_GETRED(Polygons[x].color)*ang;
		Polygons[x].dcolor=RGB(nr,ng,nb);
	}
#elif Glasses
	double dif=Polygons[0].dist-Polygons[Polygons.GetSize()-1].dist;
	
	for(int x=0;x<Polygons.GetSize();x++)
	{
		double r=(Polygons[x].dist-Polygons[Polygons.GetSize()-1].dist)/dif;
		double red, gre, blu;

		if(r<.5)
		{
			red=1;
			gre=r/.5;
			blu=0;
		}
		else
		{
			red=(.75-r)/.25;
			if(red<0)
				red=0;
			if(r<.75)
				gre=1;
			else
				gre=(1-r)/.25;
			blu=(r-.75)/.25;
			if(blu<0)
				blu=0;
		}

		Polygons[x].dcolor=RGB(red*255,gre*255,blu*255);
	}
#else
	for(int x=0;x<Polygons.GetSize();x++)
		Polygons[x].dcolor=Polygons[x].color;
#endif
}

double CWorld::sqr(double x)
{
	return x * x;
}

void CWorld::UpdateWall()
{
	if(wall<0)
		wall=0;

	/*Groups[3].a=ca-90;

	Groups[3].x=cx;
	Groups[3].y=cy;
	Groups[3].z=cz;
	
	Groups[3].Polygons[0].x[0]=5;
	Groups[3].Polygons[0].y[0]=wall;
	Groups[3].Polygons[0].z[0]=-5;
	Groups[3].Polygons[0].x[1]=-5;
	Groups[3].Polygons[0].y[1]=wall;
	Groups[3].Polygons[0].z[1]=-5;
	Groups[3].Polygons[0].x[2]=-5;
	Groups[3].Polygons[0].y[2]=wall;
	Groups[3].Polygons[0].z[2]=5;
	Groups[3].Polygons[0].x[3]=5;
	Groups[3].Polygons[0].y[3]=wall;
	Groups[3].Polygons[0].z[3]=5;*/
}

void CWorld::Physics()
{
	bool change=true;
	
	while(change)
	{
		change=false;

		for(int x=0;x<GroupCount;x++)
		{
			if(!Groups[x].Visible)
				continue;
			
			for(int y=x+1;y<GroupCount;y++)
			{
				if(!Groups[y].Visible)
					continue;

				if(sqrt(sqr(Groups[x].x-Groups[y].x)+sqr(Groups[x].y-Groups[y].y)+sqr(Groups[x].z-Groups[y].z))<5 && x!=0 && y!=0)
				{
					Groups[x].dexp=.1;
					Groups[y].dexp=.1;
				}
				
				for(int a=0;a<Groups[x].Polygons.GetSize();a++)
				{
					for(int b=0;b<Groups[y].Polygons.GetSize();b++)
					{
						if(PolyIntersect(&Groups[x].Polygons[a],&Groups[y].Polygons[b]))
						{
							
						}
					}
				}
			}
		}
	}

	for(int x=0;x<GroupCount;x++)
	{
		if(!Groups[x].Visible)
			continue;
		
		Groups[x].dx+=Groups[x].fx;
		Groups[x].dy+=Groups[x].fy;
		Groups[x].dz+=Groups[x].fz;
		Groups[x].exp+=Groups[x].dexp;
		Groups[x].x+=Groups[x].dx;
		Groups[x].y+=Groups[x].dy;
		Groups[x].z+=Groups[x].dz;
		Groups[x].fx=0;
		Groups[x].fy=0;
		if(Groups[x].z>0)
			Groups[x].fz=-.001;
		else
		{
			Groups[x].z=0;
			Groups[x].fz=0;
		}

		Groups[x].sx+=Groups[x].rx;
		Groups[x].sy+=Groups[x].ry;
		Groups[x].sz+=Groups[x].rz;
		Groups[x].t+=Groups[x].sx;
		Groups[x].p+=Groups[x].sy;
		Groups[x].a+=Groups[x].sz;
		Groups[x].rx=0;
		Groups[x].ry=0;
		Groups[x].rz=0;

		if(x==1 || x==2 && Groups[x].exp==0)
		{
			Groups[x].sz+=(rand()%3-1.0)/20.0;
			if(Groups[x].sz>1)
				Groups[x].sz=1;
			if(Groups[x].sz<-1)
				Groups[x].sz=-1;
			Groups[x].dx=cos(Groups[x].a/180*3.14159)/4;
			Groups[x].dy=sin(Groups[x].a/180*3.14159)/4;
		}
		
		if(Groups[x].exp>5 || sqrt(sqr(Groups[x].x)+sqr(Groups[x].y)+sqr(Groups[x].z))>100)
		{
			if(x==0 || x==1 || x==2)
			{
				Groups[x].x=rand()%100-50;
				Groups[x].y=rand()%100-50;
				Groups[x].exp=0;
				Groups[x].dexp=0;
			}
			else			
				Groups[x].Visible=false;
		}
	}
}

int CWorld::PolyIntersect(CPolygon *a, CPolygon *b)
{
	//0=front side
	//1=same plane
	//2=back side
	//3=both sides


	
	return 3;
}

bool CWorld::GroupIntersect(CGroup *a, CGroup *b)
{
	CPolygon a1,b1,a2,b2;
	
	for(int x=0;x<a->Polygons.GetSize();x++)
	{
		a1=a->Polygons[x];
		a2=a1;

		for(int z=0;z<a1.PointCount;z++)
		{
			double t,p,d;
			
			if(a1.y[z]!=0 || a1.z[z]!=0)
			{
				d=_hypot(a1.y[z],a1.z[z]);
				t=GetA(a1.y[z],a1.z[z]);
				t+=Groups[x].t;

				a1.y[z]=cos(t/180*M_PI)*d;
				a1.z[z]=sin(t/180*M_PI)*d;
			}
			if(a1.x[z]!=0 || a1.z[z]!=0)
			{
				d=_hypot(a1.x[z],a1.z[z]);
				p=GetA(a1.x[z],a1.z[z]);
				p+=Groups[x].p;

				a1.x[z]=cos(p/180*M_PI)*d;
				a1.z[z]=sin(p/180*M_PI)*d;
			}
			if(a1.x[z]!=0 || a1.y[z]!=0)
			{
				d=_hypot(a1.x[z],a1.y[z]);
				p=GetA(a1.x[z],a1.y[z]);
				p+=Groups[x].a;

				a1.x[z]=cos(p/180*M_PI)*d;
				a1.y[z]=sin(p/180*M_PI)*d;
			}
			a1.x[z]+=a->x;
			a1.y[z]+=a->y;
			a1.z[z]+=a->z;

			a2.x[z]=a1.x[z]+a->dx;
			a2.y[z]=a1.y[z]+a->dy;
			a2.z[z]=a1.z[z]+a->dz;
		}

		for(int y=0;y<b->Polygons.GetSize();y++)
		{
			b1=b->Polygons[x];
			b2=b1;

			for(int z=0;z<b1.PointCount;z++)
			{
				double t,p,d;
				
				if(b1.y[z]!=0 || b1.z[z]!=0)
				{
					d=_hypot(b1.y[z],b1.z[z]);
					t=GetA(b1.y[z],b1.z[z]);
					t+=Groups[x].t;

					b1.y[z]=cos(t/180*M_PI)*d;
					b1.z[z]=sin(t/180*M_PI)*d;
				}
				if(b1.x[z]!=0 || b1.z[z]!=0)
				{
					d=_hypot(b1.x[z],b1.z[z]);
					p=GetA(b1.x[z],b1.z[z]);
					p+=Groups[x].p;

					b1.x[z]=cos(p/180*M_PI)*d;
					b1.z[z]=sin(p/180*M_PI)*d;
				}
				if(b1.x[z]!=0 || b1.y[z]!=0)
				{
					d=_hypot(b1.x[z],b1.y[z]);
					p=GetA(b1.x[z],b1.y[z]);
					p+=Groups[x].a;

					b1.x[z]=cos(p/180*M_PI)*d;
					b1.y[z]=sin(p/180*M_PI)*d;
				}
				b1.x[z]+=b->x;
				b1.y[z]+=b->y;
				b1.z[z]+=b->z;

				b2.x[z]=b1.x[z]+b->dx;
				b2.y[z]=b1.y[z]+b->dy;
				b2.z[z]=b1.z[z]+b->dz;

				//if(PolyIntersect(&a1,&b1)!=PolyIntersect(&a2,&b2))

			}
		}
	}

	return false;
}

void CWorld::AddGroup(CGroup *a)
{
	if(GroupCount>0)
	{
		CGroup* tGroups=Groups;

		Groups=new CGroup[GroupCount+1];

		for(int x=0;x<GroupCount;x++)
			Groups[x]=tGroups[x];

		delete[]tGroups;
	}
	else
	{
		Groups=new CGroup[1];
	}

	Groups[GroupCount]=*a;

	GroupCount++;
}

void CWorld::DrawRadar()
{	
	dc->Ellipse(0,0,200,200);
	
	for(int x=0;x<GroupCount;x++)
	{
		if(!Groups[x].Visible)
			continue;

		for(int y=0;y<Groups[x].Polygons.GetSize();y++)
		{
			CPoint points[10];

			for(int z=0;z<Groups[x].Polygons[y].PointCount;z++)
			{
				double t;
				
				if(control!=-1)
				{
					points[z].x=Groups[x].Polygons[y].tx[z]-Groups[control].x;
					points[z].y=Groups[x].Polygons[y].ty[z]-Groups[control].y;

					t=GetA(points[z].x,points[z].y);
					t-=Groups[control].a-90;
				}
				else
				{
					points[z].x=Groups[x].Polygons[y].tx[z]-cx;
					points[z].y=Groups[x].Polygons[y].ty[z]-cy;

					t=GetA(points[z].x,points[z].y);
					t-=ca-90;
				}
				
				double len=_hypot(points[z].x,points[z].y);
				points[z].x=cos(t/180*3.14159)*len;
				points[z].y=sin(t/180*3.14159)*len;

				points[z].x+=100;
				points[z].y=-points[z].y+100;
			}

			points[Groups[x].Polygons[y].PointCount]=points[0];
			
			dc->Polyline(&points[0],Groups[x].Polygons[y].PointCount+1);
		}
	}
}
