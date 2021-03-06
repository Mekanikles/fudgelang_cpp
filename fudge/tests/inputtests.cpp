#include "gtest/gtest.h"

#include "input/source.h"
#include "input/bufferedinputstream.h"

using namespace fudge;

TEST(Input, EmptyInputStream) 
{
	BufferSource source("");
	BufferedInputStream inStream(source.createStream());

	char c = inStream.peek();
	EXPECT_TRUE(c == EOF) << "Expected EOF but was: " << c;
}

TEST(Input, NonEmptyInputStream) 
{
	const char* input = "abcdefghijklmnopqrstuvxy0123456789";
	BufferSource source(input);
	BufferedInputStream inStream(source.createStream());

	char c;
	int p = 0;
	while ((c = inStream.peek()) != EOF)
	{
		EXPECT_TRUE(c == input[p]) << "Character mismatch at position " << p;
		inStream.advance();
		++p;
	}
}

TEST(Input, CurrentPos) 
{
	const char* input = 
		"123456789\n"
		"123456789\n"
		"123456789\n"
		"123456789\n"
		"123456789\n"
		"123456789\n"
		"123456789\n"
		"123456789\n"
		"123456789\n"
		"123456789\n";
		
	BufferSource source(input);
	BufferedInputStream inStream(source.createStream());	
	int p = 0;
	while (inStream.peek() != EOF)
	{
		EXPECT_EQ(inStream.currentPos(), p++);
		inStream.advance();
	}

	EXPECT_EQ(inStream.currentPos(), 100);
}
