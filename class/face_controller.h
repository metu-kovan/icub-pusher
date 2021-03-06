#include <yarp/os/all.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <unistd.h>
#include <sstream>
#include <vector>
#include <math.h>

#ifndef FACE_CONTROLLER_H
#define FACE_CONTROLLER_H
#define _USE_MATH_DEFINES

class faceController{
	private:
		const char * no;
		std::string last_opt;
		std::string current_opt;
		std::string last_emo;
		std::string current_emo;
		const char *client_name;
		const char *server_name;
	public:
		faceController();
		void setFace(const char * opt,const char * emo);
		std::string getLastOpt();
		std::string getCurrentOpt();
		std::string getLastEmo();
		std::string getCurrentEmo();
};
#endif
