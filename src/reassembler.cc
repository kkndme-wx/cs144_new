#include "reassembler.hh"

using namespace std;
	
void Reassembler::insert_into_buffer(uint64_t first_index,string data)
{
	uint64_t begin_index = first_index;
	uint64_t end_index = first_index + data.size();	

	for(auto it = buffer_.begin();it != buffer_.end()){
		if(it->first <= begin_index ){
			begin_index = max(begin_index,it->first+it->second.size());
			++it;
			continue;	
		}
	}
	buffer_.emplace()

}		
void Reassembler::insert( uint64_t first_index, string data, bool is_last_substring, Writer& output )
{
  // Your code here.
 /* (void)first_index;
  (void)data;
  (void)is_last_substring;
  (void)output;
*/
	
	uint64_t first_unacceptable_index = first_unassemble_index + output.available_capacity();
	uint64_t end_index = first_index + data.size();
	if(end_index < first_unassemble_index || first_index > first_unacceptable_index){
		return ;
	}	
	if(end_index > first_unacceptable_index){
		data = data.substr(0,first_unacceptable_index-first_index);
		is_last_substring = false;
	}
	if(first_index > first_unassemble_index){
		insert_into_buffer(first_index,data);
		return ;
	}
	if(first_index < first_unassemble_index){
		data = data.substr(first_unassemble_index - first_index);
	}
	first_unassemble_index += data.size();
	output.push(std::move(data));
	
	if(!buffer_.empty()  && buffer_.begin()->first < first_unassemble_index){
		pop_from_buffer(output);
	}
	








}


uint64_t Reassembler::bytes_pending() const
{
  // Your code here.
  return {};
}
