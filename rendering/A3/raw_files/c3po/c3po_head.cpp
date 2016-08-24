#include <bits/stdc++.h>

using namespace std;

float normal[3], tex[2];
float r = 25.0;
float PI = 3.141592;

float norm_x(float x){
	return (x-256.0)/(512/14.0);

}
float norm_y(float y){
	return (256.0-y)/(512/14.0);
}

float norm_z(float z){
	return z/(512/14.0);
}

void update_sphere(float x, float y, float z){
	normal[0]=x;
	normal[1]=y;
	normal[2]=z;
	tex[0] = atan2( z , x )/(2*PI);
  	if(tex[0] < 0)
  	  tex[0] = -tex[0];
  	else
  	  tex[0] = 1-tex[0];
  	tex[1] = asin(y/(r/(512.0/14.0)))/PI + 0.5;


}

int main() {
	// float r = 145.0;
	float r1,r2;	//r2 is y+delta_y, r1 is y
	//float PI = 3.141592;
	float a = 90*PI/8/180;	//wuarter into 8 parts
	float circle_b[33][2];
	float circle_s[33][2];
	float c1=0.0,c2=1.0,c3=0.0;
	for(float y = -r; y<r; y += 5.0){
		r1 = sqrt(r*r - y*y);
		r2 = sqrt(r*r - (y+5)*(y+5));
		for(int i = 0; i<=8; i++){
			//cout<<floor(150*cos(i*a))<<" "<<floor(150*sin(i*a))<<endl;
			circle_b[i][0] = (r1*cos(i*a));
			circle_b[i][1] = (r1*sin(i*a));
			circle_s[i][0] = (r2*cos(i*a));
			circle_s[i][1] = (r2*sin(i*a));
		}
		for(int i = 9; i<=16; i++){
			//cout<<floor(150*cos(i*a))<<" "<<floor(150*sin(i*a))<<endl;
			circle_b[i][0] = -1*circle_b[16-i][0];
			circle_b[i][1] = circle_b[16-i][1];
			circle_s[i][0] = -1*circle_s[16-i][0];
			circle_s[i][1] = circle_s[16-i][1];
		}
		for(int i = 17; i<=24; i++){
			//cout<<floor(150*cos(i*a))<<" "<<floor(150*sin(i*a))<<endl;
			circle_b[i][0] = -1*circle_b[i-16][0];
			circle_b[i][1] = -1*circle_b[i-16][1];
			circle_s[i][0] = -1*circle_s[i-16][0];
			circle_s[i][1] = -1*circle_s[i-16][1];
		}
		for(int i = 25; i<=32; i++){
			//cout<<floor(150*cos(i*a))<<" "<<floor(150*sin(i*a))<<endl;
			circle_b[i][0] = circle_b[32-i][0];
			circle_b[i][1] = -1*circle_b[32-i][1];
			circle_s[i][0] = circle_s[32-i][0];
			circle_s[i][1] = -1*circle_s[32-i][1];
		}
		
		for(int i = 0; i<32;i++){
			if(circle_s[i+1][1] == 0){
				c1 = 0.0; c2=0.0; c3=1.0;
			}
			else{
				c1= 1.0; c2 = 0.0; c3 = 0.0;
			}

			update_sphere(norm_x(256+circle_s[i+1][0]),norm_y(256-(y+5)),norm_z(circle_s[i+1][1]));
			cout<<norm_x(256+circle_s[i+1][0])<<" "<<norm_y(256-(y+5+r))<<" "<<norm_z(circle_s[i+1][1])<<" "<<c1<<" "<<c2<<" "<<c3<<" "<<normal[0]<<" "<<normal[1]<<" "<<normal[2]<<" "<<tex[0]<<" "<<tex[1]<<endl;
			update_sphere(norm_x(256+circle_b[i+1][0]),norm_y(256-y),norm_z(circle_b[i+1][1]));
			cout<<norm_x(256+circle_b[i+1][0])<<" "<<norm_y(256-(y+r))<<" "<<norm_z(circle_b[i+1][1])<<" "<<c1<<" "<<c2<<" "<<c3<<" "<<normal[0]<<" "<<normal[1]<<" "<<normal[2]<<" "<<tex[0]<<" "<<tex[1]<<endl;
			update_sphere(norm_x(256+circle_b[i][0]),norm_y(256-y),norm_z(circle_b[i][1]));
			cout<<norm_x(256+circle_b[i][0])<<" "<<norm_y(256-(y+r))<<" "<<norm_z(circle_b[i][1])<<" "<<c1<<" "<<c2<<" "<<c3<<" "<<normal[0]<<" "<<normal[1]<<" "<<normal[2]<<" "<<tex[0]<<" "<<tex[1]<<endl;
			update_sphere(norm_x(256+circle_b[i][0]),norm_y(256-y),norm_z(circle_b[i][1]));
			cout<<norm_x(256+circle_b[i][0])<<" "<<norm_y(256-(y+r))<<" "<<norm_z(circle_b[i][1])<<" "<<c1<<" "<<c2<<" "<<c3<<" "<<normal[0]<<" "<<normal[1]<<" "<<normal[2]<<" "<<tex[0]<<" "<<tex[1]<<endl;
			update_sphere(norm_x(256+circle_s[i][0]),norm_y(256-(y+5)),norm_z(circle_s[i][1]));
			cout<<norm_x(256+circle_s[i][0])<<" "<<norm_y(256-(y+5+r))<<" "<<norm_z(circle_s[i][1])<<" "<<c1<<" "<<c2<<" "<<c3<<" "<<normal[0]<<" "<<normal[1]<<" "<<normal[2]<<" "<<tex[0]<<" "<<tex[1]<<endl;
			update_sphere(norm_x(256+circle_s[i+1][0]),norm_y(256-(y+5)),norm_z(circle_s[i+1][1]));
			cout<<norm_x(256+circle_s[i+1][0])<<" "<<norm_y(256-(y+5+r))<<" "<<norm_z(circle_s[i+1][1])<<" "<<c1<<" "<<c2<<" "<<c3<<" "<<normal[0]<<" "<<normal[1]<<" "<<normal[2]<<" "<<tex[0]<<" "<<tex[1]<<endl;
			cout<<endl;
		}
		
	}
	
	
}
