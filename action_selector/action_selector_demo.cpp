#include <iostream>
#include <yarp/os/all.h>
#include <yarp/sig/all.h>
#include <yarp/dev/all.h>
#include "../class/YarpPortReader.h"
#include <vector>
#include "../class/MotorController.h"
#include <gsl/gsl_math.h>
#include <unistd.h>
#include "../class/StringServer.h"
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <sys/time.h>
#include "../class/face_controller.h"

long long int get_timeval() {
	timeval tv;
	gettimeofday(&tv, 0);
	long long int ret = tv.tv_sec*1000000+tv.tv_usec;
	return ret;
}

void arm_point_obj1(MotorController* icub) {
	std::vector<double> vect;
	vect.resize(16);
	vect[0]=-5;
	vect[1]=26;
	vect[2]=0;
	vect[3]=45;
	vect[4]=0;
	vect[5]=0;
	vect[6]=0;
	vect[7]=24;
	vect[8]=10;
	vect[9]=39;
	vect[10]=91;
	vect[11]=7;
	vect[12]=6;
	vect[13]=60;
	vect[14]=178;
	vect[15]=180;
	icub->sendCommand(vect);
}

void arm_point_obj2(MotorController* icub) {
	std::vector<double> vect;
	vect.resize(16);
	vect[0]=-39;
	vect[1]=15;
	vect[2]=47;
	vect[3]=22;
	vect[4]=39;
	vect[5]=0;
	vect[6]=-8;
	vect[7]=24;
	vect[8]=10;
	vect[9]=39;
	vect[10]=91;
	vect[11]=7;
	vect[12]=6;
	vect[13]=60;
	vect[14]=178;
	vect[15]=180;
	icub->sendCommand(vect);
}

void arm_point_obj3(MotorController* icub) {
	std::vector<double> vect;
	vect.resize(16);
	vect[0]=-22;
	vect[1]=15;
	vect[2]=47;
	vect[3]=60;
	vect[4]=39;
	vect[5]=0;
	vect[6]=-8;
	vect[7]=24;
	vect[8]=10;
	vect[9]=39;
	vect[10]=91;
	vect[11]=7;
	vect[12]=6;
	vect[13]=60;
	vect[14]=178;
	vect[15]=180;
	icub->sendCommand(vect);
}

void arm_point_none(MotorController* icub) {
	std::vector<double> vect;
	vect.resize(16);
	vect[0]=-5;
	vect[1]=18;
	vect[2]=0;
	vect[3]=15;
	vect[4]=0;
	vect[5]=0;
	vect[6]=0;
	vect[7]=22;
	vect[8]=10;
	vect[9]=3;
	vect[10]=2;
	vect[11]=5;
	vect[12]=1;
	vect[13]=5;
	vect[14]=180;
	vect[15]=203;
	icub->sendCommand(vect);
}


int main(int argc, char* argv[]) {
	if(argc != 3) {
		std::cout << "You must provide test case and test run number" << std::endl;
		return 0;
	}
	std::string file_root = std::string("test_cases/") + std::string(argv[1]) + std::string("/");
	std::ifstream command_file((file_root + std::string("icub_commands")).c_str());
	if(!command_file.good()) {
		std::cout << file_root + std::string("icub_commands") << " does not exist" << std::endl;
		return 0;
	}
	std::ofstream output_file((file_root + std::string("test_case_run_results/") + std::string(argv[2])).c_str());

	yarp::os::Network yarp;
	YarpPortReader obj1_command("/icub_kovan/action_selector/obj1_head_motor_command");
	YarpPortReader obj2_command("/icub_kovan/action_selector/obj2_head_motor_command");
	YarpPortReader obj3_command("/icub_kovan/action_selector/obj3_head_motor_command");
	YarpPortReader gaze1_command("/icub_kovan/action_selector/gaze1_head_motor_command");
	YarpPortReader gaze2_command("/icub_kovan/action_selector/gaze2_head_motor_command");
	YarpPortReader human_command("/icub_kovan/action_selector/human_head_motor_command");
	YarpPortReader hand_command("/icub_kovan/action_selector/hand_head_motor_command");
	StringServer human_gaze_where(15006);
	human_gaze_where.start();

	StringServer hand_on_where(15005);
	hand_on_where.start();

	yarp::os::Network::connect("/icub_kovan/head_motor_calculator/obj1_head_motor_command", "/icub_kovan/action_selector/obj1_head_motor_command");
	yarp::os::Network::connect("/icub_kovan/head_motor_calculator/obj2_head_motor_command", "/icub_kovan/action_selector/obj2_head_motor_command");
	yarp::os::Network::connect("/icub_kovan/head_motor_calculator/obj3_head_motor_command", "/icub_kovan/action_selector/obj3_head_motor_command");
	yarp::os::Network::connect("/icub_kovan/head_motor_calculator/gaze1_head_motor_command", "/icub_kovan/action_selector/gaze1_head_motor_command");
	yarp::os::Network::connect("/icub_kovan/head_motor_calculator/gaze2_head_motor_command", "/icub_kovan/action_selector/gaze2_head_motor_command");
	yarp::os::Network::connect("/icub_kovan/head_motor_calculator/human_head_motor_command", "/icub_kovan/action_selector/human_head_motor_command");
	yarp::os::Network::connect("/icub_kovan/head_motor_calculator/hand_head_motor_command", "/icub_kovan/action_selector/hand_head_motor_command");
	

	faceController FC;

	bool icub_sim_on = false;

	MotorController* sim_head_controller;
	MotorController* head_controller;
	MotorController* sim_right_arm_controller;
	MotorController* right_arm_controller;

	try {
		sim_head_controller = new MotorController("icubSim", "head", 10, 10);
		sim_right_arm_controller = new MotorController("icubSim", "right_arm", 10, 10);
		icub_sim_on = true;
		std::cout << "[SCC] Connected to icubSim" << std::endl;
	} catch (std::string e) {
		std::cout << "[ERR] Connecting to icubSim failed" << std::endl;
		std::cout << e << std::endl;
	}

	bool icub_on = false;

	try {
		head_controller = new MotorController("icub", "head", 10, 25);
		right_arm_controller = new MotorController("icub", "right_arm", 10, 25);
		icub_on = true;
		std::cout << "[SCC] Connected to icub" << std::endl;
	} catch(std::string e) {
		std::cout << "[ERR] Connecting to icub failed" << std::endl;
		std::cout << e << std::endl;
	}

	while(!command_file.eof()) {
		std::string line;
		command_file>>line;
		std::cout << line << std::endl;
		std::vector<double> obj1_mc = obj1_command.getData();
		std::vector<double> obj2_mc = obj2_command.getData();
		std::vector<double> obj3_mc = obj3_command.getData();
		std::vector<double> gaze1_mc = gaze1_command.getData();
		std::vector<double> gaze2_mc = gaze2_command.getData();
		std::vector<double> human_mc = human_command.getData();
		std::vector<double> hand_mc = hand_command.getData();
		
		if(line == "gaze(obj1)") {
			output_file << get_timeval() << ",icub,gaze(obj1)" << std::endl; 
			if(icub_on)
				head_controller->sendCommand(obj1_mc);
			if(icub_sim_on)
				sim_head_controller->sendCommand(obj1_mc);
		} else if(line == "gaze(obj2)") {
			output_file << get_timeval() << ",icub,gaze(obj2)" << std::endl;
			if(icub_on)
				head_controller->sendCommand(obj2_mc);
			if(icub_sim_on)
				sim_head_controller->sendCommand(obj2_mc);
		} else if(line == "gaze(obj3)") {
			output_file << get_timeval() << ",icub,gaze(obj3)" << std::endl;
			if(icub_on)
				head_controller->sendCommand(obj3_mc);
			if(icub_sim_on)
				sim_head_controller->sendCommand(obj3_mc);
		} else if(line == "gaze(right)") {
			output_file << get_timeval() << ",icub,gaze(right)" << std::endl;
			if(icub_on)
				head_controller->sendCommand(gaze1_mc);
			if(icub_sim_on)
				sim_head_controller->sendCommand(gaze1_mc);
		} else if(line == "gaze(left)") {
			output_file << get_timeval() << ",icub,gaze(left)" << std::endl;
			if(icub_on)
				head_controller->sendCommand(gaze2_mc);
			if(icub_sim_on)
				sim_head_controller->sendCommand(gaze2_mc);
		} else if (line == "gaze(human)") {
			output_file << get_timeval() << ",icub,gaze(human)" << std::endl; 
			if(icub_on)
				head_controller->sendCommand(human_mc);
			if(icub_sim_on)
				sim_head_controller->sendCommand(human_mc);
		} else if(line == "reach(obj1)") {
			output_file << get_timeval() << ",icub,reach(obj1)" << std::endl;
			if(icub_on)
				arm_point_obj1(right_arm_controller);
			if(icub_sim_on)
				arm_point_obj1(sim_right_arm_controller);
		} else if(line == "reach(obj2)") {
			output_file << get_timeval() << ",icub,reach(obj2)" << std::endl;
			if(icub_on)
				arm_point_obj2(right_arm_controller);
			if(icub_sim_on)
				arm_point_obj2(sim_right_arm_controller);
		} else if(line == "reach(obj3)") {
			output_file << get_timeval() << ",icub,reach(obj3)" << std::endl;
			if(icub_on)
				arm_point_obj3(right_arm_controller);
			if(icub_sim_on)
				arm_point_obj3(sim_right_arm_controller);
		} else if(line == "reach(none)") {
			output_file << get_timeval() << ",icub,reach(none)" << std::endl;
			if(icub_on) 
				arm_point_none(right_arm_controller);
			if(icub_sim_on)
				arm_point_none(sim_right_arm_controller);
		}else if(line == "face(happy)") {
			FC.setFace("all", "hap");
			output_file << get_timeval() << ",icub,face(happy)" << std::endl;
		} else if(line == "face(sad)") {
			FC.setFace("all", "evi");
			output_file << get_timeval() << ",icub,face(sad)" << std::endl;
		} else if(line == "face(neutral)") {
			FC.setFace("all", "neu");
			FC.setFace("eli", "hap");
			output_file << get_timeval() << ",icub,face(neutral)" << std::endl;
		} else if(line == "face(talking)") {
			FC.setFace("all", "sur");
			FC.setFace("eli", "hap");
			output_file << get_timeval() << ",icub,face(talking)" << std::endl;
		} else if(line == "say(x)") {
		} else if(line == ".") {
			usleep(1000*1000*3);
			break;
		} else {
			double delay_sec = std::atof(line.c_str());
			for(int i=0; i<100; i++) {
				std::string hand_where = hand_on_where.getString();
				std::string head_where = human_gaze_where.getString();
				if(hand_where != "")
					output_file << get_timeval() << ",human,reach(" << hand_where << ")" << std::endl;
				if(head_where != "")
					output_file << get_timeval() << ",human,gaze(" << head_where << ")" << std::endl;
				usleep(1000*1000*delay_sec/100);
			}
		}
	}
	output_file.close();
	return 0;
}
