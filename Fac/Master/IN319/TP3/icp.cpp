#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <math.h>

#include "CImg.h"

#include "mesh.h"
#include "mathematics.h"

using namespace cimg_library;
using namespace std;

static const unsigned char red[]={255,0,0},green[]={0,255,0},blue[]={0,0,255},lightblue[]={150,150,255},white[]={255,255,255},black[]={0,0,0},grey[]={128,128,128};
enum transformationType {affine, rigid, similitude};

void Registration(float A[3][3],  float t[3], MESH& source, MESH& target, const transformationType &transformType)
{
    target.updateNormals();
    source.updateNormals();

    // compute correspondences
    for(unsigned int i=0;i<source.getNbPoints();i++)
    {
        float p[3]; source.getPoint(p,i);
        float cp[3]={p[0],p[1],p[2]};

        ///********   TO BE COMPLETED  ************///

        source.setCorrespondence(cp,i);
    }


    // weight correspondences and reject outliers
    for(unsigned int i=0;i<source.getNbPoints();i++)
    {
        source.setWeight( 1,i);
        ///********   TO BE COMPLETED  ************///
    }

    // compute centroids
    float c0[]={0,0,0}, c[]={0,0,0}, N=0;

    ///********   TO BE COMPLETED  ************///

    // fill matrices
    float Q[][3]={{1,0,0},{0,1,0},{0,0,1}}, K[][3]={{1,0,0},{0,1,0},{0,0,1}},sx=3;

    ///********   TO BE COMPLETED  ************///


    // compute solution for affine part
    if(transformType==affine) { float Qinv[3][3]; Invert(Qinv,Q); Mult(A,K,Qinv); }
    else if(transformType==rigid)            ClosestRigid(K,A);
    else if(transformType==similitude)
    {
        ClosestRigid(K,A);
        float s=0; for(unsigned int j=0;j<3;j++) s+=A[j][0]*K[j][0]+A[j][1]*K[j][1]+A[j][2]*K[j][2];
        s/=sx;
        for(unsigned int j=0;j<3;j++) for(unsigned int k=0;k<3;k++) A[j][k]*=s;
    }

    // compute solution for translation
    Mult(t,A,c0); for(unsigned int j=0;j<3;j++) t[j]=c[j]-t[j];
}


int main(int argc,char **argv)
{
    // load meshes from obj files
    string sourceFilename("data/femur_m.obj");    if(argc>=2)  sourceFilename=string(argv[1]);
    string targetFilename("data/femur_f.obj");    if(argc>=3)  targetFilename=string(argv[2]);

    MESH source;    source.LoadObj(sourceFilename.c_str());
    MESH target;    target.LoadObj(targetFilename.c_str());

    // 3d view parameters
    CImg<float> pose;
    float   Xoff = 0, Yoff = 0, Zoff = 0, sprite_scale = 1;
    int x0 = 0, y0 = 0, x1 = 0, y1 = 0;

    // rendering parameters
    bool showCorrespondences=true;
    bool showNormals=false;
    int renderMode = 4;
    const float focale = 500;
    const float scaleNormal = 0.05;
    transformationType transformType = rigid;

    // init display
    CImgDisplay disp(1024,768,"");       // display window
    CImg<unsigned char> visu0(disp.width(),disp.height(),1,3,255), visu;
    CImg<float> zbuffer(visu0.width(),visu0.height(),1,1,0);
    bool init_pose = true, clicked = false, redraw = true;
    disp.show().flush();

    while (!disp.is_closed() && !disp.is_keyQ() && !disp.is_keyESC()) // main loop
    {
        // Init camera pose
        if (init_pose)
        {
            float xm = 0, xM = target.vertices.get_shared_row(0).max_min(xm), ym = 0, yM = target.vertices.get_shared_row(1).max_min(ym), zm = 0, zM = target.vertices.get_shared_row(2).max_min(zm);
            const float delta = cimg::max(xM-xm,yM-ym,zM-zm);
            const float ratio = delta>0?(2.0f*cimg::min(disp.width(),disp.height())/(3.0f*delta)):1, dx = (xM + xm)/2, dy = (yM + ym)/2, dz = (zM + zm)/2;
            CImg<float>(4,3,1,1, ratio,0.,0.,-ratio*dx, 0.,ratio,0.,-ratio*dy, 0.,0.,ratio,-ratio*dz).move_to(pose);
            Xoff = Yoff = Zoff = 0; sprite_scale = 1;
            init_pose = false;
            redraw = true;
        }

        // Rotate and draw 3d object
        if (redraw)
        {
            visu = visu0;
            zbuffer.fill(0);
            source.drawMesh(visu,zbuffer,lightblue,1,focale,pose,renderMode,Xoff,Yoff,Zoff,sprite_scale);
            target.drawMesh(visu,zbuffer,green,1,focale,pose,renderMode,Xoff,Yoff,Zoff,sprite_scale);
            if(showCorrespondences) source.drawCorrespondences(visu,zbuffer,blue,1,focale,pose,renderMode,Xoff,Yoff,Zoff,sprite_scale);

            if(showNormals) {source.updateNormals(); source.drawNormals(scaleNormal,visu,zbuffer,red,1,focale,pose,renderMode,Xoff,Yoff,Zoff,sprite_scale);}
            if(showNormals) {target.updateNormals(); target.drawNormals(scaleNormal,visu,zbuffer,red,1,focale,pose,renderMode,Xoff,Yoff,Zoff,sprite_scale);}
            visu.display(disp);
            redraw = false;
        }

        // Handle user interaction
        disp.wait(1);
        if ((disp.button() || disp.wheel()) && disp.mouse_x()>=0 && disp.mouse_y()>=0)
        {
            redraw = true;
            if (!clicked) { x0 = x1 = disp.mouse_x(); y0 = y1 = disp.mouse_y(); if (!disp.wheel()) clicked = true; }
            else { x1 = disp.mouse_x(); y1 = disp.mouse_y(); }
            if (disp.button()&1)
            {
                const float R = 0.45f*cimg::min(disp.width(),disp.height()),R2 = R*R,u0 = (float)(x0-disp.width()/2),v0 = (float)(y0-disp.height()/2),u1 = (float)(x1-disp.width()/2),v1 = (float)(y1-disp.height()/2),n0 = (float)std::sqrt(u0*u0+v0*v0),n1 = (float)std::sqrt(u1*u1+v1*v1),nu0 = n0>R?(u0*R/n0):u0,nv0 = n0>R?(v0*R/n0):v0,nw0 = (float)std::sqrt(cimg::max(0,R2-nu0*nu0-nv0*nv0)),nu1 = n1>R?(u1*R/n1):u1,nv1 = n1>R?(v1*R/n1):v1,nw1 = (float)std::sqrt(cimg::max(0,R2-nu1*nu1-nv1*nv1)),u = nv0*nw1-nw0*nv1,v = nw0*nu1-nu0*nw1,w = nv0*nu1-nu0*nv1,n = (float)std::sqrt(u*u+v*v+w*w),alpha = (float)std::asin(n/R2);
                (CImg<float>::rotation_matrix(u,v,w,alpha)*pose).move_to(pose);
                x0 = x1; y0 = y1;
            }
            if (disp.button()&2) { if (focale>0) Zoff-=(y0-y1)*focale/400; else { const float s = std::exp((y0-y1)/400.0f); pose*=s; sprite_scale*=s; } x0 = x1; y0 = y1; }
            if (disp.wheel()) { if (focale>0) Zoff-=disp.wheel()*focale/20; else { const float s = std::exp(disp.wheel()/20.0f); pose*=s; sprite_scale*=s; } disp.set_wheel(); }
            if (disp.button()&4) { Xoff+=(x1-x0); Yoff+=(y1-y0); x0 = x1; y0 = y1; }
        }
        else if (clicked) { x0 = x1; y0 = y1; clicked = false; redraw = true; }

        switch ( disp.key())
        {
        case cimg::keyF1 :  renderMode = 0; disp.set_key(); redraw = true; break;
        case cimg::keyF2 :  renderMode = 1; disp.set_key(); redraw = true; break;
        case cimg::keyF3 :  renderMode = 2; disp.set_key(); redraw = true; break;
        case cimg::keyF4 :  renderMode = 3; disp.set_key(); redraw = true; break;
        case cimg::keyF5 :  renderMode = 4; disp.set_key(); redraw = true; break;
        case cimg::keyF6 :  renderMode = 5; disp.set_key(); redraw = true; break;
        case cimg::keyR :  init_pose = true; x0 = x1; y0 = y1; pose = CImg<float>(4,3,1,1, 1,0,0,0, 0,1,0,0, 0,0,1,0); disp.set_key();  redraw = true; break;
        case cimg::keyC :  showCorrespondences=!showCorrespondences; disp.set_key(); redraw = true; break;
        case cimg::keyN :  showNormals=!showNormals; disp.set_key(); redraw = true; break;
        case cimg::keyPADADD :   if(transformType==affine) { transformType=rigid; std::cout<<"rigid"<<std::endl; } else if(transformType==rigid) { transformType=similitude; std::cout<<"similitude"<<std::endl; } else if(transformType==similitude) { transformType=affine; std::cout<<"affine"<<std::endl; } disp.set_key(); redraw = true; break;

        case cimg::keySPACE :  // one step of icp

            // update global transformation
            float A[3][3]={{1,0,0},{0,1,0},{0,0,1}};  float t[3]={0,0,0};
            Registration(A,t,source,target,transformType);

            // update points
            for(unsigned int i=0;i<source.getNbPoints();i++)
            {
                float p0[3]; source.getPoint0(p0,i);
                float p[3]; Mult(p,A,p0); for(unsigned int j=0;j<3;j++) p[j]+=t[j];
                source.setPoint(p,i);
            }

            disp.set_key(); redraw = true;
            break;

        }
        if (disp.is_resized()) { disp.resize(false); visu0 = visu0.get_resize(disp,1); zbuffer.assign(disp.width(),disp.height()); redraw = true; }
    }



    return 0;
}

