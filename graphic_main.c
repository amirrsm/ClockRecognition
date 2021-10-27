#include <stdio.h>
#include <bmpio.h>
#include <math.h>
#include <windows.h>
#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_primitives.h>


//global variables
double xs=400,ys=150,xm=400,ym=200,xh=400,yh=250;
double degree_s=-90, degree_m=-90, degree_h=-90, angel;
int fh,fm,fs;

int i, j, k, l, x=0, y=0, z=0, m=0, n=0; // n&m count number of vertical & horizontal lines in the picture
int width=0, height=0;
int nwidth=0, nheight=0; // new width  &  new height for each cropped shape
int width1, height1, width2, height2;
int horizontal[20]={};
int vertical[20]={};
char path[150]; // path of picture.bmp
char destination[150]; // destination of croped shapes.bmp
char datapath[150];
char datades[150];
int des=0; // its for change the name of output files -->> pic(des).bmp
int h1, h2, m1, m2, s1, s2;     //h1 h2 : m1 m2 : s1 s2

unsigned char pic_array[2000][2000][3];
unsigned char new_pic_array[2000][2000][3];
unsigned char new_pic_array_2[2000][2000][3];
unsigned char new_pic_array_3[2000][2000][3];
unsigned char avg[2000][2000][3];
long long int sum[2000][2000][3];
unsigned char check_clock[2000][2000][3];
unsigned char check_data[2000][2000][3];

/*
pic[i][j][0]=Red
pic[i][j][1]=Green
pic[i][j][2]=Blue
*/

// end of global variables


void frame();
void crop_pic();
void resize_pic();

void dataset();
void data_crop_pic();
void data_resize_pic();

void fixing_color();
void final_check();

void setTextColor(int textColor, int backColor);
void sleep(unsigned int mseconds);

// main function
int main(){

	/*---------------- main part ----------------*/	
	setTextColor(12,0);
	printf("\n Please wait while the Dataset is ready...\n\n");		
	dataset();
	setTextColor(3,0);
	printf(" Dataset is ready  *_*  \n\n");
	
	sleep(1000);
	setTextColor(10,0);
	printf(" Please enter the path of picture:\n\n ");
	setTextColor(5,7);
	gets(path);
	setTextColor(10,0);
	printf("\n The path was received  :)\n\n");
	
	readBMP(path, &width, &height, pic_array);

	crop_pic();
	
	fixing_color();
	final_check();
	setTextColor(6,0);
	printf(" your clock is");
	setTextColor(4,0);
	printf("  >>>>>  ");
	setTextColor(1,15);
	printf("%d%d:%d%d:%d%d\n\n", h1, h2, m1, m2, s1, s2);
	
	setTextColor(0,0);
	printf(" ");
	setTextColor(2,0);
	sleep(500);
	printf("Loading Graphic part...\n\n");
	setTextColor(0,0);
	printf(" ");
	sleep(250);
	setTextColor(2,0);
	printf("%c%c", 219, 219);
	sleep(500);
	setTextColor(2,0);
	printf("%c%c%c%c", 219, 219, 219, 219);
	sleep(750);
	setTextColor(2,0);
	printf("%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219);
	sleep(375);
	setTextColor(2,0);
	printf("%c%c%c", 219, 219, 219);
	sleep(500);
	setTextColor(2,0);
	printf("%c%c%c%c", 219, 219, 219, 219);
	sleep(500);
	setTextColor(2,0);
	printf("%c%c%c%c", 219, 219, 219, 219);
	sleep(500);
	setTextColor(2,0);
	printf("%c%c%c%c", 219, 219, 219, 219);
	sleep(125);
	setTextColor(2,0);
	printf("%c", 219);
	sleep(750);
	setTextColor(2,0);
	printf("%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219);
	sleep(750);
	setTextColor(2,0);
	printf("%c%c%c%c%c%c ", 219, 219, 219, 219, 219, 219);
	sleep(300);
	printf("Ready!\n\n");
	sleep(1000);
	
	/*---------------- Allegro part ----------------*/
		fh=(h1*10)+(h2);
		fm=(m1*10)+(m2);
		fs=(s1*10)+(s2);
			if(fh>=12){
				fh-=12;
			}
	  	
	  	degree_s+=fs*6;
	  	degree_m+=fm*6;
	  	degree_h+=(fh*30)+(fm*0.5);
	  
	    al_init();
        al_init_primitives_addon();
        al_init_image_addon();
        
        ALLEGRO_DISPLAY*display=al_create_display(800,800);
        
        ALLEGRO_BITMAP *back1=al_load_bitmap("3.bmp");
        al_set_display_icon(display, back1);
        
        char appname[30]="CLOCK READER _ Amirreza";
        al_set_window_title(display,appname);
		al_clear_to_color(al_map_rgb(0,0,0));
        ALLEGRO_TIMER*time1=al_create_timer(1.0);
        ALLEGRO_EVENT_QUEUE*time2=al_create_event_queue();

		
        al_register_event_source(time2, al_get_timer_event_source(time1));
        al_register_event_source(time2, al_get_display_event_source(display));

        al_start_timer(time1);
		
		xs=250*cos(((degree_s)*M_PI)/180)+400;
        ys=250*sin(((degree_s)*M_PI)/180)+400;
        xm=200*cos(((degree_m)*M_PI)/180)+400;
        ym=200*sin(((degree_m)*M_PI)/180)+400;
        xh=150*cos(((degree_h)*M_PI)/180)+400;
        yh=150*sin(((degree_h)*M_PI)/180)+400;
						
		al_draw_line(400,400,xs,ys,al_map_rgb(255,0,0),3);
		al_draw_line(400,400,xm,ym,al_map_rgb(0,0,255),4);  
		al_draw_line(400,400,xh,yh,al_map_rgb(0,255,0),5);  
		
	while(1){

	    ALLEGRO_BITMAP *back=al_load_bitmap("2.bmp");
		al_draw_bitmap(back, 0, 0, 0);
    	ALLEGRO_EVENT time3;
    	al_wait_for_event(time2, &time3);
    		
			if (time3.type == ALLEGRO_EVENT_TIMER){
			degree_s+=6;
	    	xs=250*cos(((degree_s)*M_PI)/180)+400;
        	ys=250*sin(((degree_s)*M_PI)/180)+400;	
    		}
			if( (degree_s+90)-360>=0 ){
    	    degree_m+=6;
        	degree_s-=360;        
			xm=200*cos(((degree_m)*M_PI)/180)+400;
        	ym=200*sin(((degree_m)*M_PI)/180)+400;
			}	
			if( (degree_m+90)-360>=0 ){
			degree_m-=360;
        	xh=150*cos(((degree_h)*M_PI)/180)+400;
        	yh=150*sin(((degree_h)*M_PI)/180)+400;
			}
      
    		al_draw_circle(400, 400, 300, al_map_rgb(255,0,0), 5);
	    	al_draw_filled_circle(400, 400, 300, al_map_rgb(100,0,0));
    		al_draw_circle(400, 400, 10, al_map_rgb(0,0,0), 5);
    		al_draw_line(400, 400, xs, ys, al_map_rgb(100, 100, 100), 3);
    		al_draw_line(400, 400, xm, ym, al_map_rgb(0, 0, 255), 4);  
    		al_draw_line(400, 400, xh, yh, al_map_rgb(0, 255, 0), 5);
    
			for(i=0;i<=60;i++){ 
        		angel=(i*(M_PI/30)-(M_PI/2));
        		int x=280*cos(angel);
				int y=280*sin(angel);
           
        		al_draw_line(400+x,400+y,400+x+15*cos(angel), 400+y+15*sin(angel),al_map_rgb(0,119,255),2);
			}   
			for(i=0;i<=60;i+=5){ 
        		angel=(i*(M_PI/30)-(M_PI/2));
        		int x=280*cos(angel);
				int y=280*sin(angel);
           
        		al_draw_line(400+x,400+y,400+x+15*cos(angel), 400+y+15*sin(angel),al_map_rgb(0,178,136),8);
			}   
			al_flip_display();
    		al_clear_to_color(al_map_rgb(0,0,255));

	}
	al_destroy_display(display);
	al_destroy_display(display);	

return 0;
}


/*---------------------------------------------------------------------------------------------------*/
// (find frame function)...find the location of pictures(actually find the frame of each shape)
// use this function in the "crop_pic" function.
void frame(){

		int check1=0; // used to find the first & last pixel of shapes 

	for(i=0 , m=0; i<height; i++){
		for(j=0; j<width; j++){
			if(j==width-1 && check1==0){
				horizontal[m]=i;
			}
			else if(j==width-1 && check1!=0){
				m++;
				horizontal[m]=i;
				check1=0;
			}
			
			if( (pic_array[i][j][0]!=255 || pic_array[i][j][1]!=255 || pic_array[i][j][2]!=255) && check1==0){
				check1++;
				break;
			}
			else if( (pic_array[i][j][0]!=255 || pic_array[i][j][1]!=255 || pic_array[i][j][2]!=255) && check1!=0){
				break;
			}
		}
	}
	
		check1=0;
	
	for(j=0 , n=0; j<width; j++){
		for(i=0; i<height; i++){
			if(i==height-1 && check1==0){
				vertical[n]=j;
			}
			else if(i==height-1 && check1!=0){
				n++;
				vertical[n]=j;
				check1=0;
			}
			
			if( (pic_array[i][j][0]!=255 || pic_array[i][j][1]!=255 || pic_array[i][j][2]!=255) && check1==0){
				check1++;
				break;
			}
			else if( (pic_array[i][j][0]!=255 || pic_array[i][j][1]!=255 || pic_array[i][j][2]!=255) && check1!=0){
				break;
			}
		}
	}

}


/*---------------------------------------------------------------------------------------------------*/
// (crop picture function)... crop each shape in the picture & save it.
// use this function in "main" function.
void crop_pic(){
	
	int i_start=-1, i_end=-1, j_start=-1, j_end=-1;
	
	frame();
	
	for(x=0; x<m; x++){
		for(y=0; y<n; y++){
	
			i_start=-1;
			i_end=-1;
			j_start=-1;
			j_end=-1;
	
			// crop shape
			//up
			for(i=horizontal[x]; i<horizontal[x+1]; i++){
				for(j=vertical[y]; j<vertical[y+1]; j++){
					if(pic_array[i][j][0]+pic_array[i][j][1]+pic_array[i][j][2]<=400){
						i_start=i;
						break;
					}	
				}
				if(i_start==i){
					break;
				}
			}
			//left
			for(j=vertical[y]; j<vertical[y+1]; j++){
				for(i=horizontal[x]; i<horizontal[x+1]; i++){
					if(pic_array[i][j][0]+pic_array[i][j][1]+pic_array[i][j][2]<=400){
						j_start=j;
						break;
					}
				}
				if(j_start==j){
					break;
				}
			}	
			//down
			for(i=horizontal[x+1]; i>=horizontal[x]; i--){
				for(j=vertical[y+1]; j>=vertical[y]; j--){
					if(pic_array[i][j][0]+pic_array[i][j][1]+pic_array[i][j][2]<=400){
						i_end=i;
						break;
					}
				}
				if(i_end==i){
					break;
				}
			}
			//right
			for(j=vertical[y+1]; j>=vertical[y]; j--){
				for(i=horizontal[x+1]; i>=horizontal[x]; i--){
					if(pic_array[i][j][0]+pic_array[i][j][1]+pic_array[i][j][2]<=400){
						j_end=j;
						break;
					}
				}
				if(j_end==j){
					break;
				}
			}	
					
				// save it to new 3D array called new_pic_array
				for(i=i_start; i<=i_end; i++){
					for(j=j_start; j<=j_end; j++){
						for(k=0; k<3; k++){
							new_pic_array[i-i_start][j-j_start][k]=pic_array[i][j][k];
						}
					}
				}
				if(i_start!=-1){// if frame==white(without shape) -->> i_start==-1
					
					nwidth=j_end-j_start;
					nheight=i_end-i_start;
					
					resize_pic();

					des++;
					sprintf(destination, "test\\clock_%d.bmp", des);
					saveBMP(new_pic_array_3, 600, 1000, destination);
				}
	
		}// end of for(y)
	}// end of for(x)
	
}


/*---------------------------------------------------------------------------------------------------*/
// (resize picture function)... resize the picture by new scale
// use this function in "crop_pic" function
void resize_pic(){
	
	double widthscale;
	double heightscale;
	double scale;
	
	widthscale=(double) 600/nwidth;      // always widthscale>=1
	heightscale=(double) 1000/nheight;    // always heightscale>=1
	
	
	// change the width of picture
		scale=widthscale;

		for(i=0; i<nheight; i++){
		
			k=0;
			for(j=0; j<600; j++){
			
				if(scale>=1){
					new_pic_array_2[i][j][0]=new_pic_array[i][k][0];
					new_pic_array_2[i][j][1]=new_pic_array[i][k][1];
					new_pic_array_2[i][j][2]=new_pic_array[i][k][2];
				
					scale--;
				}
				else{
					new_pic_array_2[i][j][0]=( new_pic_array[i][k][0]*scale )+( new_pic_array[i][k+1][0]*(1-scale) );		
					new_pic_array_2[i][j][1]=( new_pic_array[i][k][1]*scale )+( new_pic_array[i][k+1][1]*(1-scale) );
					new_pic_array_2[i][j][2]=( new_pic_array[i][k][2]*scale )+( new_pic_array[i][k+1][2]*(1-scale) );
				
					scale--;
					
					k++; // border between 2 horizontal pixels in source picture (pic_array)
					
					if(scale<=0){
						scale+=widthscale;
					}
				}
			}
		}	
		
		
	// change the height of picture
		scale=heightscale;
	
		for(j=0; j<600; j++){
		
			k=0;
			for(i=0; i<1000; i++){
			
				if(scale>=1){
					new_pic_array_3[i][j][0]=new_pic_array_2[k][j][0];
					new_pic_array_3[i][j][1]=new_pic_array_2[k][j][1];
					new_pic_array_3[i][j][2]=new_pic_array_2[k][j][2];
				
					scale--;				
				}
				else{
					new_pic_array_3[i][j][0]=( new_pic_array_2[k][j][0]*scale )+( new_pic_array_2[k+1][j][0]*(1-scale) );		
					new_pic_array_3[i][j][1]=( new_pic_array_2[k][j][1]*scale )+( new_pic_array_2[k+1][j][1]*(1-scale) );
					new_pic_array_3[i][j][2]=( new_pic_array_2[k][j][2]*scale )+( new_pic_array_2[k+1][j][2]*(1-scale) );
				
					scale--;
				
					k++; // border between 2 vertical pixels in source picture (pic_array)
				
					if(scale<=0){
						scale+=heightscale;
					}
				}
			}
		}
}


/*---------------------------------------------------------------------------------------------------*/
// (find avg of dataset pics function)
// use this function in "main" function
void dataset(){

long long int ii=0, jj=0, kk=0, ll=0, kkk=0;

	for(kk=0; kk<=9; kk++){
		
		for(ll=1; ll<=15; ll++){
			sprintf(datapath, "Data\\%d\\%d.bmp", kk, ll);
			readBMP(datapath, &width, &height, pic_array);
			
			data_crop_pic();

			for(ii=0; ii<1000; ii++){
				for(jj=0; jj<600; jj++){
					sum[ii][jj][0]+=new_pic_array_3[ii][jj][0];
					sum[ii][jj][1]+=new_pic_array_3[ii][jj][1];
					sum[ii][jj][2]+=new_pic_array_3[ii][jj][2];
				}
			}
			
		}
		
			for(ii=0; ii<1000; ii++){
				for(jj=0; jj<600; jj++){
					avg[ii][jj][0]=sum[ii][jj][0]/15;
					avg[ii][jj][1]=sum[ii][jj][1]/15;
					avg[ii][jj][2]=sum[ii][jj][2]/15;
				}
			}
			for(ii=0; ii<1000; ii++){
				for(jj=0; jj<600; jj++){
					for(kkk=0; kkk<3; kkk++){
						sum[ii][jj][kkk]=0;
					}
				}
			}

		sprintf(datades, "test\\data%d.bmp", kk);
		saveBMP(avg, 600, 1000, datades);
	}
	
}


/*---------------------------------------------------------------------------------------------------*/
// (crop picture function)... crop data pictures
// use this function in "dataset" function.
void data_crop_pic(){

	int i_start=-1, i_end=-1, j_start=-1, j_end=-1;
	
			// crop shape
			//up
			for(i=0; i<height; i++){
				for(j=0; j<width; j++){
					if(pic_array[i][j][0]!=255 || pic_array[i][j][1]!=255 || pic_array[i][j][2]!=255){
						i_start=i;
						break;
					}	
				}
				if(i_start==i){
					break;
				}
			}
			//left
			for(j=0; j<width; j++){
				for(i=0; i<height; i++){
					if(pic_array[i][j][0]!=255 || pic_array[i][j][1]!=255 || pic_array[i][j][2]!=255){
						j_start=j;
						break;
					}
				}
				if(j_start==j){
					break;
				}
			}	
			//down
			for(i=height-1; i>=0; i--){
				for(j=width-1; j>=0; j--){
					if(pic_array[i][j][0]!=255 || pic_array[i][j][1]!=255 || pic_array[i][j][2]!=255){
						i_end=i;
						break;
					}
				}
				if(i_end==i){
					break;
				}
			}
			//right
			for(j=width-1; j>=0; j--){
				for(i=height-1; i>=0; i--){
					if(pic_array[i][j][0]!=255 || pic_array[i][j][1]!=255 || pic_array[i][j][2]!=255){
						j_end=j;
						break;
					}
				}
				if(j_end==j){
					break;
				}
			}	
					
				// save it to new 3D array called new_pic_array
				for(i=i_start; i<=i_end; i++){
					for(j=j_start; j<=j_end; j++){
						for(k=0; k<3; k++){
							new_pic_array[i-i_start][j-j_start][k]=pic_array[i][j][k];
						}
					}
				}
					width=j_end-j_start;
					height=i_end-i_start;
					data_resize_pic();			
}
	

/*---------------------------------------------------------------------------------------------------*/
// (resize picture function)... resize the data picture by new scale(600*1000)
// use this function in "data_crop_pic" function
void data_resize_pic(){
	
	double widthscale;
	double heightscale;
	double scale;

	widthscale=(double) 600/width;      // always widthscale>=1
	heightscale=(double) 1000/height;    // always heightscale>=1
	
	
	// change the width of picture
		scale=widthscale;

		for(i=0; i<height; i++){
		
			k=0;
			for(j=0; j<600; j++){
			
				if(scale>=1){
					new_pic_array_2[i][j][0]=new_pic_array[i][k][0];
					new_pic_array_2[i][j][1]=new_pic_array[i][k][1];
					new_pic_array_2[i][j][2]=new_pic_array[i][k][2];
				
					scale--;
				}
				else{
					new_pic_array_2[i][j][0]=( new_pic_array[i][k][0]*scale )+( new_pic_array[i][k+1][0]*(1-scale) );		
					new_pic_array_2[i][j][1]=( new_pic_array[i][k][1]*scale )+( new_pic_array[i][k+1][1]*(1-scale) );
					new_pic_array_2[i][j][2]=( new_pic_array[i][k][2]*scale )+( new_pic_array[i][k+1][2]*(1-scale) );
				
					scale--;
					
					k++; // border between 2 horizontal pixels in source picture (pic_array)
					
					if(scale<=0){
						scale+=widthscale;
					}
				}
			}
		}	
		
	// change the height of picture
		scale=heightscale;
	
		for(j=0; j<600; j++){
		
			k=0;
			for(i=0; i<1000; i++){
			
				if(scale>=1){
					new_pic_array_3[i][j][0]=new_pic_array_2[k][j][0];
					new_pic_array_3[i][j][1]=new_pic_array_2[k][j][1];
					new_pic_array_3[i][j][2]=new_pic_array_2[k][j][2];
				
					scale--;				
				}
				else{
					new_pic_array_3[i][j][0]=( new_pic_array_2[k][j][0]*scale )+( new_pic_array_2[k+1][j][0]*(1-scale) );		
					new_pic_array_3[i][j][1]=( new_pic_array_2[k][j][1]*scale )+( new_pic_array_2[k+1][j][1]*(1-scale) );
					new_pic_array_3[i][j][2]=( new_pic_array_2[k][j][2]*scale )+( new_pic_array_2[k+1][j][2]*(1-scale) );
				
					scale--;
				
					k++; // border between 2 vertical pixels in source picture (pic_array)
				
					if(scale<=0){
						scale+=heightscale;
					}
				}
			}
		}
}


/*---------------------------------------------------------------------------------------------------*/
// (fix color function)...makes picture black and white
// use this function in "main" function
void fixing_color(){
	
	int i, j, k, x, y;
	
	//clock pics color
	for(i=1; i<=8; i++){
		if(i%3!=0){
			sprintf(path, "test\\clock_%d.bmp", i);
			readBMP(path, &width1, &height1, check_clock);
			
			for(x=0; x<height1; x++){
				for(y=0; y<width1; y++){
					if(check_clock[x][y][0]+check_clock[x][y][1]+check_clock[x][y][2]>=730){
						check_clock[x][y][0]=255;
						check_clock[x][y][1]=255;
						check_clock[x][y][2]=255;
					}
					else{
						check_clock[x][y][0]=0;
						check_clock[x][y][1]=0;
						check_clock[x][y][2]=0;
					}
				}
			}
			saveBMP(check_clock, width1, height1, path);
		}
	}
	
	//data pics color
	for(i=0; i<=9; i++){
			sprintf(path, "test\\data%d.bmp", i);
			readBMP(path, &width1, &height1, check_data);
			
			for(x=0; x<height1; x++){
				for(y=0; y<width1; y++){
					if(check_data[x][y][0]+check_data[x][y][1]+check_data[x][y][2]>=730){
						check_data[x][y][0]=255;
						check_data[x][y][1]=255;
						check_data[x][y][2]=255;
					}
					else{
						check_data[x][y][0]=0;
						check_data[x][y][1]=0;
						check_data[x][y][2]=0;
					}
				}
			}
			saveBMP(check_data, width1, height1, path);
	}
}

// (compare function)...compare dataset and clock pics
// use this function in "main" function.
void final_check(){
	
	int i, j, k, x, y;
	long long int count=0;
	long long int max=0;	
	
	for(i=1; i<=8; i++){ //clock pics

		if(i%3!=0){
			sprintf(path, "test\\clock_%d.bmp", i);
			readBMP(path, &width1, &height1, check_clock);
			max=0;
			for(j=0; j<=9; j++){ //data pics
				sprintf(destination, "test\\data%d.bmp", j);
				readBMP(destination, &width2, &height2, check_data);	
					
				for(x=0; x<1000; x++){
					for(y=0; y<600; y++){
						if(check_clock[x][y][0]==check_data[x][y][0] && check_clock[x][y][1]==check_data[x][y][1] && check_clock[x][y][2]==check_data[x][y][2]){
								count++;
						}
					}
				}

				if(count>max){
					max=count;
					
					if(i==1){
						h1=j;
					}
					else if(i==2){
						h2=j;
					}
					else if(i==4){
						m1=j;
					}
					else if(i==5){
						m2=j;
					}
					else if(i==7){
						s1=j;
					}
					else if(i==8){
						s2=j;
					}
					
				}
				count=0;
			}
		}
	}

}

/* -------------design without allegro-------------*/
void setTextColor(int textColor, int backColor){
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	int colorAttribute = backColor << 4 | textColor;
	SetConsoleTextAttribute(consoleHandle, colorAttribute);
}

void sleep(unsigned int mseconds){
	clock_t goal = mseconds + clock();
	while (goal > clock());
}
