
#include "../class/ObjPosServer.h"

#include <yarp/os/Network.h>
#include <yarp/os/RFModule.h>
#include <yarp/os/RateThread.h>
#include <yarp/os/Time.h>
#include <yarp/sig/Vector.h>
#include <yarp/math/Math.h>

#include <yarp/dev/Drivers.h>
#include <yarp/dev/CartesianControl.h>
#include <yarp/dev/PolyDriver.h>

#include <gsl/gsl_math.h>

#include <iostream>




// Change these for arm movement bounds.
#define RIGHT_ARM_X_LOWER_BOUND 0.15
#define RIGHT_ARM_Y_LOWER_BOUND -0.30
#define RIGHT_ARM_Z_LOWER_BOUND -0.40
#define RIGHT_ARM_X_UPPER_BOUND 0.55
#define RIGHT_ARM_Y_UPPER_BOUND 0.0
#define RIGHT_ARM_Z_UPPER_BOUND 0.0


using namespace yarp::os;
using namespace yarp::dev;
using namespace yarp::sig;
using namespace yarp::math;

double inpx,inpy,inpz;
Vector conf;
int jnts=0;

int checkbound(double x,double y,double z){
    if(RIGHT_ARM_X_LOWER_BOUND>x)
        return 0;
    if(RIGHT_ARM_Y_LOWER_BOUND>y)
        return 0;
    if(RIGHT_ARM_Z_LOWER_BOUND>z)
        return 0;
    if(RIGHT_ARM_X_UPPER_BOUND<x)
        return 0;
    if(RIGHT_ARM_Y_UPPER_BOUND<y)
        return 0;
    if(RIGHT_ARM_Z_UPPER_BOUND<z)
        return 0;
    return 1;
    

}
int main()
{   
    Network yarp;
    if (!yarp.checkNetwork())
    {
        fprintf(stdout,"Error: yarp server does not seem available\n");
        return 1;
    }
    
	ObjPosServer obj_server(12343);
	obj_server.start();
	yarp::os::BufferedPort<yarp::os::Bottle> obj_port;
	obj_port.open("/icub_kovan/cartesian_server/obj_arm_motor_command");
    
	Property option;
	option.put("device","cartesiancontrollerclient");
	option.put("remote","/icub/cartesianController/right_arm");
	option.put("local","/client/right_arm");
	PolyDriver clientCartCtrl(option);
	ICartesianControl *icart=NULL;
	IPositionControl *ipos=NULL;
	if (clientCartCtrl.isValid()) {
 	 	 clientCartCtrl.view(icart);
 	 	 clientCartCtrl.view(ipos);
	}
	int jnts=0;
	ipos->getAxes(&jnts);
	std::vector<double> coordinates;
	Vector oy(4), oz(4);
	oy[0]=0.0; oy[1]=1.0; oy[2]=0.0; oy[3]=+M_PI/2.0;
	oz[0]=0.0; oz[1]=0.0; oz[2]=1.0; oz[3]=-M_PI/2.0;
	Matrix Ry=yarp::math::axis2dcm(oy);        // from axis/angle to rotation matrix notation
	Matrix Rz=yarp::math::axis2dcm(oz);
	Matrix R=Rz*Ry;                            // compose the two rotations keeping the order
	Vector od=yarp::math::dcm2axis(R);          // from rotation matrix back to the axis/angle notation
	while(1){
	    coordinates=obj_server.getObjCoordinates();
	    inpx=-coordinates[0];
	    inpy=-coordinates[1];
	    inpz=coordinates[2];
	    if(checkbound(inpx,inpy,inpz)){
	        Vector xd(3),xdhat,odhat;
	        xd[0]=inpx-5.5;
	        xd[1]=inpy;
	        xd[2]=inpz+36;
	        icart->askForPose(xd,od,xdhat,odhat,conf);
	    }
        yarp::os::Bottle& obj_bottle = obj_port.prepare();
        obj_bottle.clear();
	    for(int i=0; i<jnts; i++) {
		    obj_bottle.addDouble(conf[i]);
	    }
	    obj_port.write();
		
	}
   	clientCartCtrl.close();
   	return 0;
}

