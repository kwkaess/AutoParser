/*
 * XercesConvenience.hpp
 *
 *  Created on: Jul 21, 2017
 *      Author: kaess
 */
#include <xercesc/util/XMLString.hpp>
using namespace xercesc;

#ifndef SRC_XERCESCONVENIENCE_HPP_
#define SRC_XERCESCONVENIENCE_HPP_

class TranscodedStringWrapper {
public:
	TranscodedStringWrapper(const XMLCh * input) {
		value = XMLString::transcode(input);
	}
	virtual ~TranscodedStringWrapper() {
		XMLString::release(&value);
	}
	char * value;
};
#endif /* SRC_XERCESCONVENIENCE_HPP_ */

