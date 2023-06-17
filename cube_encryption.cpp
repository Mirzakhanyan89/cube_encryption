/*	cube_encription.cpp	*/

#include <iostream>
#include <string>
#include <vector>

const int cube_size {8};

class Cube {
private:
	std::string message;
public:
	Cube(const std::string&);
	const std::string& get_message();
	void rotate_up(std::string&);
	void rotate_down(std::string&);
	void rotate_left(std::string&);
	void rotate_right(std::string&);
	std::vector<std::string> cut_into_pieces();
	std::string key_generation();
	std::string encode_txt(const std::string&);
};


Cube::Cube(const std::string& m) : message{m} { }

const std::string& Cube::get_message() {
	return message;
}

void Cube::rotate_up(std::string& data) {
	std::string str {};
	str += data[3];
	str += data[2];
	str += data[6];
	str += data[7];
	str += data[0];
	str += data[1];
	str += data[5];
	str += data[4];
	data = str;
//	std::cout<< data << "\n";
}

void Cube::rotate_down(std::string& data) {
	std::string str {};
	str += data[4];
	str += data[5];
	str += data[1];
	str += data[0];
	str += data[7];
	str += data[6];
	str += data[2];
	str += data[3];
	data = str;
//	std::cout<< data << "\n";
}

void Cube::rotate_left(std::string& data) {
	std::string str {};
	str += data[1];
	str += data[5];
	str += data[6];
	str += data[2];
	str += data[0];
	str += data[4];
	str += data[7];
	str += data[3];
	data = str;
//	std::cout<< data << "\n";
}

void Cube::rotate_right(std::string& data) {
	std::string str {};
	str += data[4];
	str += data[0];
	str += data[3];
	str += data[7];
	str += data[5];
	str += data[1];
	str += data[2];
	str += data[6];
	data = str;
//	std::cout<< data << "\n";
}

std::vector<std::string> Cube::cut_into_pieces() {
	std::vector<std::string> vec;
	int i {};
	int count {1};
	std::string chunk {};
	while (message[i] != '\0') {
		chunk += message[i++];
		if (i == count*cube_size or message[i] == '\0') {
			vec.push_back(chunk);
			chunk.clear();
			++count;
			}
		}
	return vec;
}

std::string Cube::key_generation() {
	std::string key {};
	char letters[] {'U','D','L','R'}; 
	int count {0};
	if (!(message.size() % cube_size)) {
		count = message.size() / cube_size;
	} else {
		count = (message.size() / cube_size) + 1;
	}		
	while (count) {
		key += letters[rand() % 4];
		key += std::to_string(rand() % 4);
		key += ':';
		--count;
		}	

return key;
}


std::string Cube::encode_txt(const std::string& key) {
	std::vector<std::string> vec = cut_into_pieces();
	int j {};
	int i {};
	while (key[j] != '\0') {
		int number {};
		switch (key[j]) {
			case 'U':	
				// cube has 4 session, after four the rotations are repeated
				number = (key[++j] - '0') % 4;
				for (int k{}; k<number; ++k) {
					rotate_up(vec[i]);
				}
				if (key[++j] == ',') {
				} else {
					++i;
					}
				++j;
				break;
			case 'D':
					number = (key[++j] - '0') % 4;
					for (int k{}; k<number; ++k) {
						rotate_down(vec[i]);
					}
					if (key[++j] == ',') {
					} else {
						++i;
						}
					++j;
					break;
			case 'L':
					number = (key[++j] - '0') % 4;
					for (int k{}; k<number; ++k) {
						rotate_left(vec[i]);
					}
					if (key[++j] == ',') {
					} else {
						++i;
						}
					++j;
					break;
			case 'R':
					number = (key[++j] - '0') % 4;
					for (int k{}; k<number; ++k) {
						rotate_right(vec[i]);
					}
					if (key[++j] == ',') {
					} else {
						++i;
						}
					++j;
					break;
			}
		}
	// message assigne vectors change value after encoding
	std::string encoded_msg {};
	for (const auto& elem : vec) {
		encoded_msg += elem;
		}
	return encoded_msg;
}


int main() {
	std::string msg {"hello dear students. Today we will learn print hello world in python."};
	Cube cube(msg);
	std::string key = cube.key_generation();
	std::cout<< "Starting message is:\t" << msg;
	std::cout<< "\nkey is: " << key << std::endl; 
	std::cout<< "Encryption message is:\t" << cube.encode_txt(key);


return 0;
}





