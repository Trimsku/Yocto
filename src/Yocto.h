#ifndef YOCTO_H
#define YOCTO_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>

#include "Exception.h"
#include "Lexer.h"
#include "Parser.h"
#include "ParseTreePrinter.h"
#include "backend/YoctoVisitor.h"

class Yocto {
public:
	Yocto();
	virtual ~Yocto() = default;

	void run_prompt();
	void run_script(const std::string & path);

	void run(const std::string & script);

private:
};

#endif