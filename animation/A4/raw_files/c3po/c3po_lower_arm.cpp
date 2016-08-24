#include <bits/stdc++.h>

using namespace std;

float height = 80.0; //height = 2*height, height = multiple of 5
float r = 9.0;	//radius
float normal[3], tex[2];

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

void update_cylinder(float x, float y, float z){
	normal[0] = x; normal[1]=0.0; normal[2] = z;
	tex[0] = atan2( z , x )/(2*PI);
  	if(tex[0] < 0)
  	  tex[0] = -tex[0];
  	else
  	  tex[0] = 1-tex[0];
  	tex[1] = y/(14.0) + 0.5;
}

int main() {
	float a = 90*PI/8/180;
	float circle[33][2];
	float c1=0.0,c2=1.0,c3=0.0;
	for(int i = 0; i<=8; i++){
		//cout<<floor(150*cos(i*a))<<" "<<floor(150*sin(i*a))<<endl;
		circle[i][0] = (r*cos(i*a));
		circle[i][1] = (r*sin(i*a));
	}
	for(int i = 9; i<=16; i++){
		//cout<<floor(150*cos(i*a))<<" "<<floor(150*sin(i*a))<<endl;
		circle[i][0] = -1*circle[16-i][0];
		circle[i][1] = circle[16-i][1];
	}
	for(int i = 17; i<=24; i++){
		//cout<<floor(150*cos(i*a))<<" "<<floor(150*sin(i*a))<<endl;
		circle[i][0] = -1*circle[i-16][0];
		circle[i][1] = -1*circle[i-16][1];
	}
	for(int i = 25; i<=32; i++){
		//cout<<floor(150*cos(i*a))<<" "<<floor(150*sin(i*a))<<endl;
		circle[i][0] = circle[32-i][0];
		circle[i][1] = -1*circle[32-i][1];
	}
	
	

	for(int i = 0; i<32;i++){
		if(i == 15){
			c1=0.0;
			c2=0.0;
			c3=1.0;
		}

		update_cylinder(norm_x(256+circle[i+1][0]),norm_y(256-(0.0)),norm_z(circle[i+1][1]));
		cout<<norm_x(256+circle[i+1][0])<<" "<<norm_y(256-(0.0))<<" "<<norm_z(circle[i+1][1])<<" "<<c1<<" "<<c2<<" "<<c3<<" "<<normal[0]<<" "<<normal[1]<<" "<<normal[2]<<" "<<tex[0]<<" "<<tex[1]<<endl;
		update_cylinder(norm_x(256+circle[i+1][0]),norm_y(256-(-height)),norm_z(circle[i+1][1]));
		cout<<norm_x(256+circle[i+1][0])<<" "<<norm_y(256-(-height))<<" "<<norm_z(circle[i+1][1])<<" "<<c1<<" "<<c2<<" "<<c3<<" "<<normal[0]<<" "<<normal[1]<<" "<<normal[2]<<" "<<tex[0]<<" "<<tex[1]<<endl;
		update_cylinder(norm_x(256+circle[i][0]),norm_y(256-(-height)),norm_z(circle[i][1]));
		cout<<norm_x(256+circle[i][0])<<" "<<norm_y(256-(-height))<<" "<<norm_z(circle[i][1])<<" "<<c1<<" "<<c2<<" "<<c3<<" "<<normal[0]<<" "<<normal[1]<<" "<<normal[2]<<" "<<tex[0]<<" "<<tex[1]<<endl;
		update_cylinder(norm_x(256+circle[i][0]),norm_y(256-(-height)),norm_z(circle[i][1]));
		cout<<norm_x(256+circle[i][0])<<" "<<norm_y(256-(-height))<<" "<<norm_z(circle[i][1])<<" "<<c1<<" "<<c2<<" "<<c3<<" "<<normal[0]<<" "<<normal[1]<<" "<<normal[2]<<" "<<tex[0]<<" "<<tex[1]<<endl;
		update_cylinder(norm_x(256+circle[i][0]),norm_y(256-(0.0)),norm_z(circle[i][1]));
		cout<<norm_x(256+circle[i][0])<<" "<<norm_y(256-(0.0))<<" "<<norm_z(circle[i][1])<<" "<<c1<<" "<<c2<<" "<<c3<<" "<<normal[0]<<" "<<normal[1]<<" "<<normal[2]<<" "<<tex[0]<<" "<<tex[1]<<endl;
		update_cylinder(norm_x(256+circle[i+1][0]),norm_y(256-(0.0)),norm_z(circle[i+1][1]));
		cout<<norm_x(256+circle[i+1][0])<<" "<<norm_y(256-(0.0))<<" "<<norm_z(circle[i+1][1])<<" "<<c1<<" "<<c2<<" "<<c3<<" "<<normal[0]<<" "<<normal[1]<<" "<<normal[2]<<" "<<tex[0]<<" "<<tex[1]<<endl;
		cout<<endl;

		//top circle
		normal[0]=0.0; normal[1]=1.0; normal[2]=0.0; tex[0] = 0.0; tex[1]=0.0;
		cout<<norm_x(256+circle[i+1][0])<<" "<<norm_y(256-(-height))<<" "<<norm_z(circle[i+1][1])<<" "<<c1<<" "<<c2<<" "<<c3<<" "<<normal[0]<<" "<<normal[1]<<" "<<normal[2]<<" "<<tex[0]<<" "<<tex[1]<<endl;
		cout<<norm_x(256+circle[i][0])<<" "<<norm_y(256-(-height))<<" "<<norm_z(circle[i][1])<<" "<<c1<<" "<<c2<<" "<<c3<<" "<<normal[0]<<" "<<normal[1]<<" "<<normal[2]<<" "<<tex[0]<<" "<<tex[1]<<endl;
		cout<<norm_x(256+0.0)<<" "<<norm_y(256-(-height))<<" "<<norm_z(0.0)<<" "<<c1<<" "<<c2<<" "<<c3<<" "<<normal[0]<<" "<<normal[1]<<" "<<normal[2]<<" "<<tex[0]<<" "<<tex[1]<<endl;

		//bottom circle
		normal[0]=0.0; normal[1]=-1.0; normal[2]=0.0; tex[0] = 0.0; tex[1]=0.0;
		cout<<norm_x(256+circle[i][0])<<" "<<norm_y(256-(0.0))<<" "<<norm_z(circle[i][1])<<" "<<c1<<" "<<c2<<" "<<c3<<" "<<normal[0]<<" "<<normal[1]<<" "<<normal[2]<<" "<<tex[0]<<" "<<tex[1]<<endl;
		cout<<norm_x(256+circle[i+1][0])<<" "<<norm_y(256-(0.0))<<" "<<norm_z(circle[i+1][1])<<" "<<c1<<" "<<c2<<" "<<c3<<" "<<normal[0]<<" "<<normal[1]<<" "<<normal[2]<<" "<<tex[0]<<" "<<tex[1]<<endl;
		cout<<norm_x(256+0.0)<<" "<<norm_y(256-(0.0))<<" "<<norm_z(0.0)<<" "<<c1<<" "<<c2<<" "<<c3<<" "<<normal[0]<<" "<<normal[1]<<" "<<normal[2]<<" "<<tex[0]<<" "<<tex[1]<<endl;

	}
		
	
	
}
