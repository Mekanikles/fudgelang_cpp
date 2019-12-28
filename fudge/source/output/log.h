#pragma once
#include "core/core.h"

#include <iostream>

class Indenter
{
public:
	Indenter(int indent) : m_indent(indent) {}
	friend std::ostream& operator<<(std::ostream& out, const Indenter& indenter);
private:
	int m_indent;
};

std::ostream& operator<<(std::ostream& out, const Indenter& indenter)
{
	for (int i = 0; i < indenter.m_indent; ++i)
		out << "    ";
	return out;
} 

Indenter indent(int i)
{
	return Indenter(i);
}

void printIndent(int i)
{
	std::clog << indent(i);	
}

void print(const string& str, int i = 0)
{
	printIndent(i);
	std::clog << str;
}

void printLine(const string& str, int i = 0)
{
	printIndent(i);
	std::clog << str << std::endl;
}

void printError(const string& str)
{
	std::cerr << str << std::endl;
}

#define LOG_INFO(text) printLine(text)
#define LOG_ERROR(text) do { printError(text); exit(-1); } while(false)
