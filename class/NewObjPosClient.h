#include <yarp/os/all.h>
#include <yarp/sig/all.h>
#include <yarp/dev/all.h>
#include <string>


class NewObjPosClient {
	private:
		std::string host;
		int portno;
	public:
		NewObjPosClient();
		NewObjPosClient(std::string host, int portno);
		NewObjPosClient(const char* host, int portno);
		void sendData(double x, double y, double z);
		void sendHorO(char* HeadOrObj);
		void setHost(std::string newHost);
		void setPort(int newPort);
		int getPort();
};
