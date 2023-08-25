#include "reassembler.hh"

using namespace std;
	
		
void Reassembler::write_into_bytestream(Writer & output){
	while(output.available_capacity() >= 0&&(bytes_pushed <= output.available_capacity()){
		auto it = mp.begin();
		output.push(std::move(it->second));
		mp.erase(it);	
	}
	if(bytes_pushed > output.available_capacity() ){
		auto tmp_len = output.available_capacity();		
		
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
  if(is_last_substring){
	output.close();
	return;
  } 
  uint64_t end_index = first_index + data.size();
  first_unacceptable_index = first_unassemble_index + output.available_capacity();
  if(first_index < first_unassemble_index || first_index > first_unacceptable_index|| end_index > first_unacceptable_index)
  	return ;
  first_unassemble_index += data.size(); 
  bytes_pushed += data.size();
  mp.emplace(std::make_pair(first_index,std::move(data)));
  write_into_bytestream(output); 
}


uint64_t Reassembler::bytes_pending() const
{
  // Your code here.
  return {};
}
