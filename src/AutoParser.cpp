/*
 * AutoParser.cpp
 *
 *  Created on: Jul 21, 2017
 *      Author: kaess
 */

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include "XercesConvenience.hpp"
namespace xc = xercesc;

#include <iostream>


using namespace po;
using namespace xc;
using namespace std;

int main(int argc, char ** argv) {
	try {
		XMLPlatformUtils::Initialize();
	} catch (const XMLException& toCatch) {
		TranscodedStringWrapper message(toCatch.getMessage());
		cerr << "Exception message is: \n" << message.value << endl;
		return 1;
	}

	options_description desc("Options");
	desc.add_options()("help,h", "print this help message")("file,f",
			value<string>(), "file input for AutoParse to execute");
	variables_map vm;
	store(po::parse_command_line(argc, argv, desc), vm);
	notify(vm);
	if (vm.count("help")) {
		cout << desc << endl;
	} else if (vm.count("file")) {
		string filename = vm["file"].as<string>();
		XercesDOMParser * parser = new XercesDOMParser();
		ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
		parser->setValidationScheme(XercesDOMParser::Val_Always);
		parser->setDoNamespaces(true);
		parser->setErrorHandler(errHandler);
		cout << "Here we go!" << endl;
		try {
			parser->parse(filename.c_str());
		} catch (const XMLException& toCatch) {
			TranscodedStringWrapper message(toCatch.getMessage());
			cout << "Exception message is: \n" << message.value << endl;
			return -1;
		} catch (const SAXParseException& toCatch) {
			TranscodedStringWrapper message(toCatch.getMessage());
			cout << "Exception message is: \n" << message.value << endl;
			return -1;
		} catch (const DOMException& toCatch) {
			TranscodedStringWrapper message(toCatch.getMessage());
			cout << "Exception message is: \n" << message.value << endl;
			return -1;
		} catch (const exception& e) {
			cout << "Exception message is: \n" << e.what() << endl;
			return -1;
		}

		const DOMDocument * dom { parser->getDocument() };
		const XMLCh * name = XMLString::transcode("tag");
		DOMNodeList * nodeList = dom->getElementsByTagName(name);
		auto length = nodeList->getLength();
		cout << "Number of Elements: " << length << endl;
		for (XMLSize_t i = 0; i < length; i++) {
			auto dNode = nodeList->item(i);
			if (dNode) {
				TranscodedStringWrapper text(dNode->getTextContent());
				cout << dNode->getNodeType() << "\t"
						<< dNode->getChildNodes()->getLength() << "\t"
						<< text.value << endl;
			}
		}

	}

	XMLPlatformUtils::Terminate();
	return 0;
}

