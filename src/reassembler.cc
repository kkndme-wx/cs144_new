#include "reassembler.hh"

using namespace std;
	
void Reassembler::insert_into_buffer(uint64_t first_index,string&& data,bool is_last_substring)
{
	uint64_t begin_index = first_index;
	uint64_t end_index = first_index + data.size();	

	for(auto it = buffer_.begin();it != buffer_.end()&& begin_index < end_index;){
		if(it->first <= begin_index ){
			begin_index = max(begin_index,it->first+it->second.size());
			++it;
			continue;	
		}
		if(begin_index == first_index&&end_index <= it->first){
			bytes_pushed_ += data.size();
			buffer_.emplace(it,first_index,std::move(data));	
			return;
		}
			uint64_t right_index = std::min(it->first,end_index);
			data = data.substr(begin_index-first_index,right_index-begin_index);
			bytes_pushed_ += data.size();
			buffer_.emplace(it,begin_index,std::move(data));	
			begin_index = right_index;
			
		}
		if(begin_index < end_index){
			bytes_pushed_ += end_index-begin_index;
			buffer_.emplace_back(begin_index,end_index- begin_index);	
		}	
		if(is_last_substring){
			has_last = true;	
		}

}		
void Reassembler::pop_from_buffer(Writer & output){
	for(auto it = buffer_.begin();it != buffer_.end();){
		if(it->first > first_unassemble_index)break;	
		const auto end = it->first + it->second.size();
		if(end <= first_unassemble_index){
			bytes_pushed_ -= it->second.size();	
		}
		else{
			auto data = std::move(it->second)	;
				bytes_pushed_ -= data.size();
			if(it->first < first_unassemble_index){
				data = data.substr(first_unassemble_index - it->first);
			}
				first_unassemble_index += data.size();
				output.push(std::move(data));
		}
		it = buffer_.erase(it);
	}
	if(buffer_.empty()&& has_last){
		output.close();	
	}
}
void Reassembler::insert( uint64_t first_index, string data, bool is_last_substring, Writer& output )
{
  // Your code here.
 /* (void)first_index;
  (void)data;
  (void)is_last_substring;
  (void)output;
*/
	if(data.empty()){
		if(is_last_substring){
			output.close();
			return;	
		}	
	}	
	if(output.available_capacity() == 0)return ;
	uint64_t first_unacceptable_index = first_unassemble_index + output.available_capacity();
	uint64_t end_index = first_index + data.size();
	if(end_index <= first_unassemble_index || first_index >= first_unacceptable_index){
		return ;
	}	
	if(end_index > first_unacceptable_index){
		data = data.substr(0,first_unacceptable_index-first_index);
		is_last_substring = false;
	}
	if(first_index > first_unassemble_index){
		insert_into_buffer(first_index,std::move(data),is_last_substring);
		return ;
	}
	if(first_index < first_unassemble_index){
		data = data.substr(first_unassemble_index - first_index);
	}
	first_unassemble_index += data.size();
	output.push(std::move(data));
	
	if(!buffer_.empty()  && buffer_.begin()->first <= first_unassemble_index){
		pop_from_buffer(output);
	}
	








}


uint64_t Reassembler::bytes_pending() const
{
  // Your code here.
  return bytes_pushed;
}
