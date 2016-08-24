#include <bits/stdc++.h>

using namespace std;

float thickness = 60.0;
float rad = 60.0;
float rad_pivot = 10.0;
float upper_arm_len = 80.0;
float elbow = 20.0;
float lower_arm_len = 140.0;
float lower_arm_width = 60.0;
float normal[3], tex[2];

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

	cout<<a.x<<" "<<a.y<<" "<<a.z<<" "<<r<<" "<<g<<" "<<b1<<" "<<normal[0]<<" "<<normal[1]<<" "<<normal[2]<<" "<<tex[0]<<" "<<tex[1]<<endl;
	cout<<b.x<<" "<<b.y<<" "<<b.z<<" "<<r<<" "<<g<<" "<<b1<<" "<<normal[0]<<" "<<normal[1]<<" "<<normal[2]<<" "<<tex[0]<<" "<<tex[1]<<endl;
	cout<<c.x<<" "<<c.y<<" "<<c.z<<" "<<r<<" "<<g<<" "<<b1<<" "<<normal[0]<<" "<<normal[1]<<" "<<normal[2]<<" "<<tex[0]<<" "<<tex[1]<<endl;
	cout<<c.x<<" "<<c.y<<" "<<c.z<<" "<<r<<" "<<g<<" "<<b1<<" "<<normal[0]<<" "<<normal[1]<<" "<<normal[2]<<" "<<tex[0]<<" "<<tex[1]<<endl;
	cout<<d.x<<" "<<d.y<<" "<<d.z<<" "<<r<<" "<<g<<" "<<b1<<" "<<normal[0]<<" "<<normal[1]<<" "<<normal[2]<<" "<<tex[0]<<" "<<tex[1]<<endl;
	cout<<a.x<<" "<<a.y<<" "<<a.z<<" "<<r<<" "<<g<<" "<<b1<<" "<<normal[0]<<" "<<normal[1]<<" "<<normal[2]<<" "<<tex[0]<<" "<<tex[1]<<endl;
}
void quad1(Point a, Point b, Point c, Point d, float r, float g, float b1){

	cout<<a.x<<" "<<a.y<<" "<<a.z<<" "<<r<<" "<<g<<" "<<b1<<" "<<0.0<<" "<<a.y<<" "<<-a.x<<" "<<tex[0]<<" "<<tex[1]<<endl;
	cout<<b.x<<" "<<b.y<<" "<<b.z<<" "<<r<<" "<<g<<" "<<b1<<" "<<0.0<<" "<<b.y<<" "<<-b.x<<" "<<tex[0]<<" "<<tex[1]<<endl;
	cout<<c.x<<" "<<c.y<<" "<<c.z<<" "<<r<<" "<<g<<" "<<b1<<" "<<0.0<<" "<<c.y<<" "<<-c.x<<" "<<tex[0]<<" "<<tex[1]<<endl;
	cout<<c.x<<" "<<c.y<<" "<<c.z<<" "<<r<<" "<<g<<" "<<b1<<" "<<0.0<<" "<<c.y<<" "<<-c.x<<" "<<tex[0]<<" "<<tex[1]<<endl;
	cout<<d.x<<" "<<d.y<<" "<<d.z<<" "<<r<<" "<<g<<" "<<b1<<" "<<0.0<<" "<<d.y<<" "<<-d.x<<" "<<tex[0]<<" "<<tex[1]<<endl;
	cout<<a.x<<" "<<a.y<<" "<<a.z<<" "<<r<<" "<<g<<" "<<b1<<" "<<0.0<<" "<<a.y<<" "<<-a.x<<" "<<tex[0]<<" "<<tex[1]<<endl;
}

int main() {
	float PI = 3.141592;
	float a = 90*PI/8/180;
	float circle[33][2];
	float c1=0.0,c2=1.0,c3=0.0;
	//initialize circle[33][2]
	for(int i = 0; i<=8; i++){
		//cout<<floor(150*cos(i*a))<<" "<<floor(150*sin(i*a))<<endl;
		circle[i][0] = (cos(i*a));
		circle[i][1] = (sin(i*a));
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
	
	Point p1,p2,p3,p4,p5,p6,p7,p8;
	tex[0]=0.0;tex[1]=0.0;
	//upper disk - shoulder
	for(int i = 0; i<16;i++){
		c1=0.1,c2=0.2,c3=0.3;
		//front triangle1
		p1.x=norm_x(256+rad*circle[i+1][0]);p1.y=norm_y(256-rad*circle[i+1][1]);p1.z=norm_z(thickness/2.0);
		p2.x=norm_x(256+rad_pivot*circle[i+1][0]);p2.y=norm_y(256-rad_pivot*circle[i+1][1]);p2.z=norm_z(thickness/2.0);
		p3.x=norm_x(256+rad_pivot*circle[i][0]);p3.y=norm_y(256-rad_pivot*circle[i][1]);p3.z=norm_z(thickness/2.0);
		p4.x=norm_x(256+rad*circle[i][0]);p4.y=norm_y(256-rad*circle[i][1]);p4.z=norm_z(thickness/2.0);

		p5.x=norm_x(256+rad*circle[i+1][0]);p5.y=norm_y(256-rad*circle[i+1][1]);p5.z=norm_z(-thickness/2.0);
		p6.x=norm_x(256+rad_pivot*circle[i+1][0]);p6.y=norm_y(256-rad_pivot*circle[i+1][1]);p6.z=norm_z(-thickness/2.0);
		p7.x=norm_x(256+rad_pivot*circle[i][0]);p7.y=norm_y(256-rad_pivot*circle[i][1]);p7.z=norm_z(-thickness/2.0);
		p8.x=norm_x(256+rad*circle[i][0]);p8.y=norm_y(256-rad*circle[i][1]);p8.z=norm_z(-thickness/2.0);

		normal[0]=1.0;normal[1]=0.0; normal[2]=0.0;
		quad(p1,p2,p3,p4,0.1,0.2,0.3);
		quad1(p1,p4,p8,p5,0.3,0.2,0.1);
		normal[0]=-1.0;normal[1]=0.0;normal[2]=0.0;
		quad(p6,p5,p8,p7,0.1,0.2,0.3);
		quad1(p3,p2,p6,p7,0.3,0.2,0.1);

		
	}	//shoulder drawn

	//upper arm
	p1.x=norm_x(256+rad*circle[0][0]);p1.y=norm_y(256-rad*circle[0][1]);p1.z=norm_z(thickness/2.0);
	p2.x=norm_x(256+rad*circle[16][0]);p2.y=norm_y(256-rad*circle[16][1]);p2.z=norm_z(thickness/2.0);
	p3.x=norm_x(256+rad*circle[16][0]);p3.y=norm_y(256-(rad*circle[16][1]-upper_arm_len));p3.z=norm_z(thickness/2.0);
	p4.x=norm_x(256+rad*circle[0][0]);p4.y=norm_y(256-(rad*circle[0][1]-upper_arm_len));p4.z=norm_z(thickness/2.0);

	p5.x=norm_x(256+rad*circle[0][0]);p5.y=norm_y(256-rad*circle[0][1]);p5.z=norm_z(-thickness/2.0);
	p6.x=norm_x(256+rad*circle[16][0]);p6.y=norm_y(256-rad*circle[16][1]);p6.z=norm_z(-thickness/2.0);
	p7.x=norm_x(256+rad*circle[16][0]);p7.y=norm_y(256-(rad*circle[16][1]-upper_arm_len));p7.z=norm_z(-thickness/2.0);
	p8.x=norm_x(256+rad*circle[0][0]);p8.y=norm_y(256-(rad*circle[0][1]-upper_arm_len));p8.z=norm_z(-thickness/2.0);

	normal[0]=1.0;normal[1]=0.0; normal[2]=0.0;
	quad(p1,p2,p3,p4,0.2,0.3,0.4);
	normal[0]=0.0;normal[1]=0.0; normal[2]=-1.0;
	quad(p1,p4,p8,p5,0.4,0.3,0.2);
	normal[0]=-1.0;normal[1]=0.0; normal[2]=0.0;
	quad(p6,p5,p8,p7,0.2,0.3,0.4);
	normal[0]=0.0;normal[1]=0.0; normal[2]=1.0;
	quad(p3,p2,p6,p7,0.4,0.3,0.2);

	
	//elbow
	p1.x=norm_x(256+rad*circle[0][0]);p1.y=norm_y(256-(rad*circle[0][1]-upper_arm_len));p1.z=norm_z(thickness/2.0);
	p2.x=norm_x(256+rad*circle[16][0]);p2.y=norm_y(256-(rad*circle[16][1]-upper_arm_len));p2.z=norm_z(thickness/2.0);
	p3.x=norm_x(256+(rad*circle[16][0]+elbow));p3.y=norm_y(256-(rad*circle[16][1]-(elbow + upper_arm_len)));p3.z=norm_z(thickness/2.0);
	p4.x=norm_x(256+(rad*circle[0][0]-elbow));p4.y=norm_y(256-(rad*circle[0][1]-(elbow + upper_arm_len)));p4.z=norm_z(thickness/2.0);

	p5.x=norm_x(256+rad*circle[0][0]);p5.y=norm_y(256-(rad*circle[0][1]-upper_arm_len));p5.z=norm_z(-thickness/2.0);
	p6.x=norm_x(256+rad*circle[16][0]);p6.y=norm_y(256-(rad*circle[16][1]-upper_arm_len));p6.z=norm_z(-thickness/2.0);
	p7.x=norm_x(256+(rad*circle[16][0]+elbow));p7.y=norm_y(256-(rad*circle[16][1]-(elbow + upper_arm_len)));p7.z=norm_z(-thickness/2.0);
	p8.x=norm_x(256+(rad*circle[0][0]-elbow));p8.y=norm_y(256-(rad*circle[0][1]-(elbow + upper_arm_len)));p8.z=norm_z(-thickness/2.0);


	normal[0]=1.0;normal[1]=0.0; normal[2]=0.0;
	quad(p1,p2,p3,p4,0.2,0.3,0.4);
	normal[0]=0.0;normal[1]=-1.0; normal[2]=-1.0;
	quad(p1,p4,p8,p5,0.4,0.3,0.2);
	normal[0]=-1.0;normal[1]=0.0; normal[2]=0.0;
	quad(p6,p5,p8,p7,0.2,0.3,0.4);
	normal[0]=0.0;normal[1]=-1.0; normal[2]=1.0;
	quad(p3,p2,p6,p7,0.4,0.3,0.2);

	//lower arm
	p1.x=norm_x(256+(rad*circle[0][0]-elbow));p1.y=norm_y(256-(rad*circle[0][1]-(elbow + upper_arm_len)));p1.z=norm_z(thickness/2.0);
	p2.x=norm_x(256+(rad*circle[16][0]+elbow));p2.y=norm_y(256-(rad*circle[16][1]-(elbow + upper_arm_len)));p2.z=norm_z(thickness/2.0);
	p3.x=norm_x(256+(rad*circle[16][0]+elbow));p3.y=norm_y(256-(rad*circle[16][1]-(elbow + upper_arm_len + lower_arm_len)));p3.z=norm_z(thickness/2.0);
	p4.x=norm_x(256+(rad*circle[0][0]-elbow));p4.y=norm_y(256-(rad*circle[0][1]-(elbow + upper_arm_len + lower_arm_len)));p4.z=norm_z(thickness/2.0);

	p5.x=norm_x(256+(rad*circle[0][0]-elbow));p5.y=norm_y(256-(rad*circle[0][1]-(elbow + upper_arm_len)));p5.z=norm_z(-thickness/2.0);
	p6.x=norm_x(256+(rad*circle[16][0]+elbow));p6.y=norm_y(256-(rad*circle[16][1]-(elbow + upper_arm_len)));p6.z=norm_z(-thickness/2.0);
	p7.x=norm_x(256+(rad*circle[16][0]+elbow));p7.y=norm_y(256-(rad*circle[16][1]-(elbow + upper_arm_len + lower_arm_len)));p7.z=norm_z(-thickness/2.0);
	p8.x=norm_x(256+(rad*circle[0][0]-elbow));p8.y=norm_y(256-(rad*circle[0][1]-(elbow + upper_arm_len + lower_arm_len)));p8.z=norm_z(-thickness/2.0);

	normal[0]=1.0;normal[1]=0.0; normal[2]=0.0;
	quad(p1,p2,p3,p4,0.2,0.3,0.4);
	normal[0]=0.0;normal[1]=0.0; normal[2]=-1.0;
	quad(p1,p4,p8,p5,0.4,0.3,0.2);
	normal[0]=-1.0;normal[1]=0.0; normal[2]=0.0;
	quad(p6,p5,p8,p7,0.2,0.3,0.4);
	normal[0]=0.0;normal[1]=0.0; normal[2]=1.0;
	quad(p3,p2,p6,p7,0.4,0.3,0.2);

	normal[0]=0.0;normal[1]=-1.0; normal[2]=0.0;
	quad(p4,p3,p7,p8,0.9,0.5,0.5);

}
