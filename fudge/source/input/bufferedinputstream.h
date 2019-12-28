#pragma once

#include <istream>
#include <cassert>

namespace fudge
{

class BufferedInputStream
{
public:
	BufferedInputStream(std::unique_ptr<std::istream> inStream) 
		: m_inStream(std::move(inStream))
	{
	}

	uint currentPos() { return m_bufferEndStreamPos - (m_end - m_begin); }

	void advance()
	{
		assert(m_end != m_begin && "advance called without peeking first");

		const char c = m_circBuffer[m_begin++];
		m_begin = m_begin % BUF_SIZE;
	}

	char peek()
	{
		bool empty = false;
		if (m_end == m_begin)
			empty = fillBuffer() == 0;

		if (!empty)
			return m_circBuffer[m_begin];
		else
			return EOF;
	}

	char peekAhead(uint count = 1)
	{
		assert(count < MAX_LOOKAHEAD);
		uint buffered = bufferedLength();
		if (buffered <= count)
			buffered = fillBuffer();

		if (buffered > count)
			return m_circBuffer[(m_begin + count) % BUF_SIZE];
		else
			return EOF;
	}

private:
	uint bufferedLength()
	{
		return (m_end + BUF_SIZE - m_begin) % BUF_SIZE;
	}

	uint fillBuffer()
	{
		auto& stream = *m_inStream;

		const uint bufSpace = BUF_SIZE - bufferedLength();
		const uint fill = bufSpace - 1; // Leave one char for m_end
		if (fill)
		{
			uint fill1 = std::min(BUF_SIZE - m_end, fill);
			stream.read(&m_circBuffer[m_end], fill1);
			m_end += stream.gcount();

			m_end = m_end % BUF_SIZE;

			uint fill2 = fill - fill1;
			if (fill2)
			{
				stream.read(&m_circBuffer[m_end], fill2);
				m_end += stream.gcount();
			}
		}

		m_bufferEndStreamPos = stream.tellg();

		return bufferedLength();
	}

private:
	static const uint MAX_LOOKAHEAD = 63;
	static const uint BUF_SIZE = MAX_LOOKAHEAD + 1;
	char m_circBuffer[BUF_SIZE];
	uint m_begin = 0;
	uint m_end = 0;
	std::unique_ptr<std::istream> m_inStream;
	uint m_bufferEndStreamPos = 0;
};

}