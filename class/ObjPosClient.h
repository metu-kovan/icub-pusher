#include <yarp/os/all.h>
#include <yarp/sig/all.h>
#include <yarp/dev/all.h>
#include <string>


class ObjPosClient {
	private:
		std::string host;
		int portno;
	public:
		ObjPosClient(std::string host, int portno);
		ObjPosClient(const char* host, int portno);
		void sendData(double x, double y, double z);
		void sendHorO(double x, double y, double z);
};
