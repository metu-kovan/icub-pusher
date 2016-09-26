#include <yarp/os/all.h>
#include <yarp/sig/all.h>
#include <yarp/dev/all.h>
#include <iostream>
#include <vector>

class ObjPosServer : public yarp::os::Thread {
	private:
		double obj_x, obj_y, obj_z;
		int sockfd;
		int portno;
		void startServer(int portno);
		yarp::os::Mutex coorMutex;
	public:
		ObjPosServer(int p) : yarp::os::Thread(), portno(p) {}
		~ObjPosServer(){}
		void run();
		void onStop();
		void beforeStart();
		void afterStart(bool success);
		bool threadInit();
		void threadRelease();
		std::vector<double> getObjCoordinates();
};