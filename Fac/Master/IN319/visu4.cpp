/* Compilation:
	(Windows version) g++ -o visu4.exe visu4.cpp -O2 -lgdi32
	(Linux  version) g++  -o visu4.exe visu4.cpp -O2 -L/usr/X11R6/lib  -lm  -lpthread -lX11

	Execution :
	visu4.exe .\data\knix.hdr
*/
	
#include "CImg.h"
using namespace cimg_library;

/* Main program */
int main(int argc,char **argv)
{
	/* Create and load the 3D image */
	/* See http://cimg.sourceforge.net/reference/group__cimg__storage.html */
	/* See "Construct image from reading an image file" at http://cimg.sourceforge.net/reference/structcimg__library_1_1CImg.html */
	CImg<unsigned short> img;
	float voxelsize[3];
	/* Load in Analyze format */
	img.load_analyze(argv[1],voxelsize);
	
	/* Get the image dimensions */
    unsigned int dim[]={img.width(),img.height(),img.depth()}; 
	printf("Reading %s. Dimensions=%d %d %d\n",argv[1],dim[0],dim[1],dim[2]);
	printf("Voxel size=%f %f %f\n",voxelsize[0],voxelsize[1],voxelsize[2]);
		
	/* Create the display window */
	/* See http://cimg.sourceforge.net/reference/structcimg__library_1_1CImgDisplay.html */
	CImgDisplay disp(512,512,"");    
	
	/* The 3 displayed slices of the MPR visualisation */
	int displayedSlice[]={dim[0]/2,dim[1]/2,dim[2]/2}; 
		
	/* Slice corresponding to mouse position: */
	unsigned int coord[]={0,0,0};
	
	/* in MPR [2=original slice size=x y       0 size=z y
	1= size=x z                                */
	/* -1 corresponds to the 4th quarter where there is no MPR plane */
	int plane=2;
	
	/* For a first drawing, activate the redrawing */
	bool redraw=true;
	
	/* Manage the display windows: ESC, or closed -> close the main window*/
	while (!disp.is_closed() && !disp.is_keyESC()) // main loop
	{
		/* Wait for any event on the display windows during 1 ms.
		If nothing, at the beginning draw for the first time the window */
		disp.wait(1);
		
		/* List of events */
		
		/* - Resizing */
		if (disp.is_resized()) 
		{
			disp.resize();
		}
		/* Movement of the mouse */
		
		/* If the mouse is inside the window, find its position w.r.t. to the 
		3 planes */
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
		
		/* - Click Right button */
		if (disp.button()&2  && (plane!=-1))  
		{
			for(unsigned int i=0;i<3;i++) 
			{
				displayedSlice[i]=coord[i];
			}
			redraw = true;
		}
		/* - Wheel interaction */
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
			
		/* Flush all mouse wheel events in order to not repeat the wheel event */
		disp.set_wheel();
			
		redraw = true;
		}
		
		/* If any change, we need to redraw the main windows */
		if (redraw)
		{
			/* Create a 2D image based on the MPR projections given by a projection point which is the intersection of the displayed slices */
			CImg<> mpr_img=img.get_projections2d(displayedSlice[0],displayedSlice[1],displayedSlice[2]);  
						
			/* The MPR image has a given size. It needs to be resized in order to fit at best in the display window */
			mpr_img.resize(512,512); 
			
			/* Display the MPR image in the display windows */
			disp.display(mpr_img);
			
			/* To avoid repetitive continuous redrawing */
			redraw=false;
		}
	}
	return 0;
}


