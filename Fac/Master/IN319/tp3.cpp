#include "CImg.h"
#include <iostream>
using namespace std;
using namespace cimg_library;

int main(int argc,char **argv)
{
	CImg<unsigned short> img;
	float voxelsize[3];
	img.load_analyze(argv[1],voxelsize);

    unsigned int dim[]={img.width(),img.height(),img.depth()}; 
	printf("Reading %s. Dimensions=%d %d %d\n",argv[1],dim[0],dim[1],dim[2]);
	printf("Voxel size=%f %f %f\n",voxelsize[0],voxelsize[1],voxelsize[2]);
	CImgDisplay disp(512,512,"");
	
	int displayedSlice[]={dim[0]/2,dim[1]/2,dim[2]/2}; 
		
	unsigned int coord[]={0,0,0};
	int plane=2;
	bool redraw=true;
	
	while (!disp.is_closed() && !disp.is_keyESC())
	{
		disp.wait(1);
		if (disp.is_resized()) 
		{
			disp.resize();
		}

		/* Movement of the mouse */
		if(disp.mouse_x()>=0 && disp.mouse_y()>=0) 
		{
			
			unsigned int mX = disp.mouse_x()*(dim[0]+dim[2])/disp.width();
			unsigned int mY = disp.mouse_y()*(dim[1]+dim[2])/disp.height();
			
			if (mX>=dim[0] && mY<dim[1]) 
			{ 
				plane = 0; 
				coord[1] = mY; 
				coord[2] = mX - dim[0];   
				coord[0] = displayedSlice[0]; 
			}
			else 
			{
				if (mX<dim[0] && mY>=dim[1]) 
				{ 
					plane = 1; 
					coord[0] = mX; 
					coord[2] = mY - dim[1];   
					coord[1] = displayedSlice[1]; 
				}
				else 
				{
					if (mX<dim[0] && mY<dim[1])       
					{ 
						plane = 2; 
						coord[0] = mX; 
						coord[1] = mY;     
						coord[2] = displayedSlice[2]; 
					}
					else 
					{
						plane = -1; 
						coord[0] = 0;
						coord[1] = 0;
						coord[2] = 0;
					}
				}
			}
			redraw = true;
		}
		
		/* Click Left */
		if (disp.button()&1  && (plane!=-1))  
		{
			int color[3] = {50,50,50};
			img.draw_fill(coord[0], coord[1], coord[2], color, (float)1, (float)3);
			redraw = true;
		}
		
		/* Click Right */
		if (disp.button()&2  && (plane!=-1))  
		{
			for(unsigned int i=0;i<3;i++) 
			{
				displayedSlice[i]=coord[i];
			}
			redraw = true;
		}
		
		/* Click Middle */
		if (disp.button()&4  && (plane!=-1))  
		{
			int sigma = 20, threshold = img.atXYZ(coord[0], coord[1], coord[2]);
			int seuil1 = threshold-sigma, seuil2 = threshold+sigma;
			long segmented = 0;
			for(long x=0 ; x<img.width() ; x++) {
				for(long y=0 ; y<img.height() ; y++) {
					for(long z=0 ; z<img.depth() ; z++) {
						if(img.atXYZ(x,y,z) <= seuil1 || img.atXYZ(x,y,z) >= seuil2) {
							*(img.data(x,y,z)) = 0;
						}
						else {
							segmented++;
						}
					}
				}
			}
			cout << "Seuil : " << threshold << " -> segmented : " << segmented << endl;
		}

		/* Wheel */
		if (disp.wheel()) 
		{
			displayedSlice[plane]=displayedSlice[plane]+disp.wheel();
			
			if (displayedSlice[plane]<0) 
			{
				displayedSlice[plane] = 0;
			}
			else 
			{
				if (displayedSlice[plane]>=(int)dim[plane])
				{
					displayedSlice[plane] = (int)dim[plane]-1;
				}
			}
			
		/* Flush */
		disp.set_wheel();
			
		redraw = true;
		}
		
		/* Redraw */
		if (redraw)
		{
			CImg<> mpr_img=img.get_projections2d(displayedSlice[0],displayedSlice[1],displayedSlice[2]);
			mpr_img.resize(512,512); 
			disp.display(mpr_img);
			redraw=false;
		}
	}
	//img.save_raw("img/saved.raw");
	return 0;
}

