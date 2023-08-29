#include "wrapping_integers.hh"

using namespace std;

Wrap32 Wrap32::wrap( uint64_t n, Wrap32 zero_point )
{
  // Your code here.
	return zero_point+static_cast<uint32_t>(n);
}

uint64_t Wrap32::unwrap( Wrap32 zero_point, uint64_t checkpoint ) const
{
  // Your code here.
	uint64_t TWO31 = 1UL << 31;
	uint64_t TWO32 = 1UL << 32;
	auto cpt = wrap(checkpoint,zero_point);
	auto dis = raw_value_ - cpt.raw_value_;
	if(dis <= TWO31){
		return checkpoint+dis;
	}
	dis = TWO32 - dis;
	if(checkpoint < dis)
		return checkpoint + TWO32 - dis;
	return checkpoint - dis;
}
