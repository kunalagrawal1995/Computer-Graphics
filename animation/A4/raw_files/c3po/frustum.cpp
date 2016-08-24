#include <bits/stdc++.h>

using namespace std;

float thickness = 60.0;
float height = 2*thickness;
float thickness1 = 2*thickness;
float rad = 60.0;
float rad_pivot = 10.0;
float upper_arm_len = 80.0;
float elbow = 20.0;
float lower_arm_len = 140.0;
float lower_arm_width = 60.0;

float norm_x(float x){
	return (x-256.0)/(512/14.0);

}
float norm_y(float y){
	return (256.0-y)/(512/14.0);
}

float norm_z(float z){
	return z/(512/14.0);
}

class Point{
public:
	float x,y,z;
	Point(){
		x=y=z=0.0;
	}
};

void quad(Point a, Point b, Point c, Point d, float r, float g, float b1){
	cout<<a.x<<" "<<a.y<<" "<<a.z<<" "<<r<<" "<<g<<" "<<b1<<endl;
	cout<<b.x<<" "<<b.y<<" "<<b.z<<" "<<r<<" "<<g<<" "<<b1<<endl;
	cout<<c.x<<" "<<c.y<<" "<<c.z<<" "<<r<<" "<<g<<" "<<b1<<endl;
	cout<<c.x<<" "<<c.y<<" "<<c.z<<" "<<r<<" "<<g<<" "<<b1<<endl;
	cout<<d.x<<" "<<d.y<<" "<<d.z<<" "<<r<<" "<<g<<" "<<b1<<endl;
	cout<<a.x<<" "<<a.y<<" "<<a.z<<" "<<r<<" "<<g<<" "<<b1<<endl;
}

int main() {
	float PI = 3.141592;
	float a = 90*PI/8/180;
	float circle[33][2];
	float c1=0.0,c2=1.0,c3=0.0;
	
	Point p1,p2,p3,p4,p5,p6,p7,p8;

	p1.x=norm_x(256.0+(thickness/2.0));p1.y=norm_y(256.0-0.0);p1.z=norm_z(thickness/2.0);
	p2.x=norm_x(256.0-(thickness/2.0));p2.y=norm_y(256.0-0.0);p2.z=norm_z(thickness/2.0);
	p3.x=norm_x(256.0-(thickness1/2.0));p3.y=norm_y(256.0-(-height));p3.z=norm_z(thickness1/2.0);
	p4.x=norm_x(256.0+(thickness1/2.0));p4.y=norm_y(256.0-(-height));p4.z=norm_z(thickness1/2.0);
	p5.x=norm_x(256.0+(thickness/2.0));p5.y=norm_y(256.0-0.0);p5.z=norm_z(-thickness/2.0);
	p6.x=norm_x(256.0-(thickness/2.0));p6.y=norm_y(256.0-0.0);p6.z=norm_z(-thickness/2.0);
	p7.x=norm_x(256.0-(thickness1/2.0));p7.y=norm_y(256.0-(-height));p7.z=norm_z(-thickness1/2.0);
	p8.x=norm_x(256.0+(thickness1/2.0));p8.y=norm_y(256.0-(-height));p8.z=norm_z(-thickness1/2.0);

	quad(p1,p2,p3,p4,0.0,1.0,0.0);
	quad(p1,p4,p8,p5,0.0,1.0,0.0);
	quad(p5,p8,p7,p6,0.0,1.0,0.0);
	quad(p2,p6,p7,p3,0.0,1.0,0.0);
	quad(p1,p5,p6,p2,0.0,1.0,0.0);
	quad(p8,p4,p3,p7,0.0,1.0,0.0);
}
