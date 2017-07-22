/*
 * AutoParser.cpp
 *
 *  Created on: Jul 21, 2017
 *      Author: kaess
 */

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <xercesc/dom/DOM.hpp>
namespace xc = xercesc;
using namespace po;
using namespace xc;
using namespace std;

int main(int argc, char ** argv) {
	options_description desc("Options");
	desc.add_options()("help,h", "print this help message")("file,f",
			value<string>(), "file input for AutoParse to execute");
	variables_map vm;
	store(po::parse_command_line(argc, argv, desc), vm);
	notify(vm);
	return 0;
}

