#include "tcp_receiver.hh"

using namespace std;

void TCPReceiver::receive( TCPSenderMessage message, Reassembler& reassembler, Writer& inbound_stream )
{
	if(!isn_.has_value()){
		if(!message.SYN){
			return ;	
		}	
		isn_ = message.seqno;	
	}
	auto const checkpoint = inbound_stream.bytes_pushed()+1;
	auto const uint64_seqno = message.seqno.unwrap(isn_.value(),checkpoint);
	auto const first_index = message.SYN? 0:uint64_seqno-1;
	reassembler.insert(first_index,message.payload.release(),message.FIN,inbound_stream);
	

}

TCPReceiverMessage TCPReceiver::send( const Writer& inbound_stream ) const
{
		TCPReceiverMessage tmsg{};
		auto const win_size = inbound_stream.available_capacity();
		tmsg.window_size = win_size <UINT16_MAX? win_size:UINT16_MAX;

		if(isn_.has_value()){
			uint64_t const abs_seq = inbound_stream.bytes_pushed()+1+inbound_stream.is_closed();
			tmsg.ackno = Wrap32::wrap(abs_seq,isn_.value());	
		}
		return tmsg;
}
