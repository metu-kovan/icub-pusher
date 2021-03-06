#include <yarp/os/all.h>
#include "../class/ObjPosClient.h"
#include "../class/NewObjPosClient.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <unistd.h>
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <vector>
#include <math.h>
#define diff 0.00001 
#define change 0.1
using namespace std;
NewObjPosClient headOrObj("localhost",12348);
ObjPosClient head("localhost",12345);
ObjPosClient obj1("localhost",12344);
ObjPosClient obj2("localhost",12343);
ObjPosClient objToLogger("localhost",13000);
ObjPosClient headToLogger("localhost",13001);
NewObjPosClient headOrObjToLogger("localhost",13002);

bool  which = false; //false -> head ,true -> obj
bool isEqual(double a,double b){
	if(fabs(a-b)>diff)
		return false;
	return true;
}
bool isChanged(double a,double b){
	if(fabs(a-b)>change)
		return true;
	return false;
}
bool isZero(vector<double> holder){
	if(isEqual(holder[0],0.0) && isEqual(holder[1],0.0) && isEqual(holder[2],0.0))
		return true;
	return false;
}


void calcAverage(vector<double> &average,vector< vector<double> > &general,int divider,bool isO,bool isS){
	if(isO && isS) {
		average[0] = (general[1][0] + general[2][0])/divider;
		average[1] = (general[1][1] + general[2][1])/divider;
		average[2] = (general[1][2] + general[2][2])/divider;
	}
	else {
		if(isO) {
			average[0] = general[1][0];
			average[1] = general[1][1];
			average[2] = general[1][2];
		}
		else {
			average[0] = general[2][0];
			average[1] = general[2][1];
			average[2] = general[2][2];			
		}
	}
}




void updateVectors(vector<double> &icubToHat2,vector<double> &hat1ToHat2,vector< vector<double> > &general,vector<double> &icub,vector<double> &loneLedToHat2,vector<double> &loneLed){
	int divider = 2;
	bool isOneActive = true;
	bool isSecondActive = true;
	if(isZero(general[0])){
		cout<<"need to see 2.15"<<endl;
		return;
	}
	if(isZero(general[1])){
		cout<<"2.14 is not active"<<endl;
		divider--;
		isOneActive = false;
	}
	if(isZero(general[2])){
		cout<<"2.10 is not active"<<endl;
		divider--;
		isSecondActive = false;
	}
	if(divider == 0){
		cout<<"need to see at least one of 2.10 or 2.14"<<endl;
		return;
	}
	vector<double > average(3);
	calcAverage(average,general,divider,isOneActive,isSecondActive);
	icubToHat2[0] = icub[0]-average[0];
	icubToHat2[1] = icub[1]-average[1];
	icubToHat2[2] = icub[2]-average[2];
	hat1ToHat2[0] = general[0][0]-average[0];
	hat1ToHat2[1] = general[0][1]-average[1];
	hat1ToHat2[2] = general[0][2]-average[2];
	loneLedToHat2[0] = loneLed[0]-average[0];
	loneLedToHat2[1] = loneLed[1]-average[1];
	loneLedToHat2[2] = loneLed[2]-average[2];
		
}
double dotProduct(vector<double> &v1,vector<double> &v2){
	double xx,yy,zz;
	double l1,l2;
	xx = v1[0]*v2[0];
	yy = v1[1]*v2[1];
	zz = v1[2]*v2[2];
	l1 = sqrt((v1[0]*v1[0])+(v1[1]*v1[1])+(v1[2]*v1[2]));
	l2 = sqrt((v2[0]*v2[0])+(v2[1]*v2[1])+(v2[2]*v2[2]));
	return acos((xx+yy+zz)/(l1*l2));
}


int main(int argc, char *argv[]) {



	yarp::os::Network yarp;
	yarp::os::BufferedPort<yarp::os::Bottle>  outPort;
	vector< vector<double> > general(3);//2.15,2.14,2.10
	vector<double> icubToHat2(3); 	//hat2 is average of 2.14 and 2.10
	vector<double> hat1ToHat2(3);	// hat1 is 2.15
	vector<double> icub; //x,y,z
	vector<double> loneLed(3); //1.3
	vector<double> loneLedToHat2(3);
	double degree1;
	double degree2;
	for(int i = 0;i<3;i++){
		vector<double > tempv(3);
		tempv[0]=0.0;
		tempv[1]=0.0;
		tempv[2]=0.0;
		general[i] = tempv;
		icubToHat2[i] = 0.0;
		hat1ToHat2[i] = 0.0;
		loneLed[i] = 0.0;
		loneLedToHat2[i] = 0.0;
	}

	icub.push_back(0.97);icub.push_back(-0.03);icub.push_back(0.64);
	bool ok = outPort.open("/GazeDegree");
	if (!ok) {
	fprintf(stderr, "Failed to create ports.\n");
	fprintf(stderr, "Maybe you need to start a nameserver (run 'yarpserver')\n");
	return 1;
	}
	yarp.connect("/vzPout",outPort.getName());
	
	while (true) {
	        usleep(1000*100);
        yarp::os::Bottle *input =outPort.read();
        if (input!=NULL) {
            yarp::os::Bottle& output = outPort.prepare();
            output.clear();
            double current;
            string c2;
            double x,y,z;
            int tcm,ledid;
	        int helper = 0;
	        int jumper = 0;
	        bool handled = false;
            for(int j = 1;j<input->size();j++){
            	if(helper == 0)
            	{
            		c2 = input->get((jumper*5)+1).asString();
		            tcm = atoi(c2.substr(7,1).c_str());
		            ledid = atoi(c2.substr(8,2).c_str());
		            
		            
		            helper++;
		            if(tcm == 1 && ledid==3){
		            	
		            }
		            else if(tcm != 2 || (ledid != 15 && ledid != 14 && ledid != 10)){
		            	helper = 0;
		            	jumper++;
		            	j+=4;
		            	continue;
		            }
		            
		            
		            //cout<<"tcm "<<tcm<<" ledid "<<ledid<<" ";
            	}
				else if(helper == 4)
				{

					helper = 0;
					jumper++;
					x = output.get(0).asDouble();
					y = output.get(1).asDouble();
					z = output.get(2).asDouble();
					if(isEqual(x,0.0) && isEqual(y,0.0) && isEqual(z,0.0)){
						handled = true;
					}
					else{
						x = x+3.059691;
						y = y-0.552323; 
						z = z-9.433398;
					}
					if(tcm == 2 && ledid == 15 && handled == false){
		
						if(isChanged(general[0][0],x) || isChanged(general[0][1],y) || isChanged(general[0][2],z)){
							general[0][0] = x;
							general[0][1] = y;
							general[0][2] = z;
							head.sendData(x,y,z);
							headToLogger.sendData(x,y,z);
						}
					}
					else if(tcm == 2 && ledid == 14 && handled == false){
							general[1][0] = x;
							general[1][1] = y;
							general[1][2] = z;
					}
					else if(tcm == 2 && ledid == 10 && handled == false){
							general[2][0] = x;
							general[2][1] = y;
							general[2][2] = z;
					}
					else if(tcm == 1 && ledid == 3 && handled == false){
						if(isChanged(loneLed[0],x) || isChanged(loneLed[1],y) || isChanged(loneLed[2],z)){
							loneLed[0] = x;
							loneLed[1] = y;
							loneLed[2] = z;
							obj1.sendData(x,y,z);
							obj2.sendData(x,y,z);
							objToLogger.sendData(x,y,z);
						}
					}

					handled= false;
					output.clear();
				}
				else{
					current = input->get((jumper*5)+helper+1).asDouble();
				   	output.addDouble(current);
				   	helper++;
				}
				outPort.write();

           }

        }
        updateVectors(icubToHat2,hat1ToHat2,general,icub,loneLedToHat2,loneLed);
        degree1 = dotProduct(icubToHat2,hat1ToHat2);
        degree2 = dotProduct(loneLedToHat2,hat1ToHat2);
        cout<<"degree1 " <<degree1 << " degree2 "<<degree2<<endl;
        usleep(1000*10);
        if(degree1>degree2 && !which){					// if degree1 is bigger hat is looking to obj
        	headOrObj.sendHorO((char *)"obj");
        	headOrObjToLogger.sendHorO((char *)"obj");
        	which =true;
       	}
        else if(degree2>=degree1 && which){
        	headOrObj.sendHorO((char *)"head");
        	headOrObjToLogger.sendHorO((char *)"head");
        	which =false;
        }
    }
//	pthread_join(socket_thread, NULL);
    
  
  return 0;
}
