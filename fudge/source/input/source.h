#pragma once
#include "core/core.h"

#include <istream>
#include <fstream>

namespace fudge
{

///////////////////////////////////////////////////////////////////////////////

interface Source
{
	virtual std::unique_ptr<std::istream> createStream() const = 0;
};

///////////////////////////////////////////////////////////////////////////////

class FileSource : public Source
{
public:	
	FileSource(const string& filePath)
		: filePath(filePath)
	{
	}

	virtual std::unique_ptr<std::istream> createStream() const override
	{
		return std::make_unique<std::ifstream>(filePath);
	}
private:
	const string filePath;
};

///////////////////////////////////////////////////////////////////////////////

class BufferSource : public Source
{
public:	
	BufferSource(const char* data, size_t size)
		: data(data), size(size)
	{
	}

	BufferSource(const char* str)
		: data(str), size(strlen(str))
	{
	}

	std::unique_ptr<std::istream> createStream() const override
	{
		return std::make_unique<MemoryInputStream>(data, size);
	}

private:
	class MemoryBuffer : public std::streambuf 
	{
	public:
		MemoryBuffer(const char* base, size_t size) 
		{
			char* p = const_cast<char*>(base);
			this->setg(p, p, p + size);
		}
	};

	class MemoryInputStream : virtual MemoryBuffer, public std::istream 
	{
	public:
		MemoryInputStream(const char* base, size_t size)
			: MemoryBuffer(base, size)
			, std::istream(static_cast<std::streambuf*>(this)) 
		{
		}
	};

	const char* data;
	size_t size;
};

///////////////////////////////////////////////////////////////////////////////

}