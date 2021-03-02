#include <catch.hpp>

#include <ConcurrentList.hpp>

TEST_CASE("Stripped list single thread", "[unit]")
{
	Spatial::ConcurrentStrippedList<int> list;
}
