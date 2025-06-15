#include "Message.h"
Message::Message(const String& content) : content(content) {
    timestamp = std::time(nullptr);
}

void Message::display() const {
    std::cout << "[" << std::ctime(&timestamp) << "] " << content.c_str() << "\n";
}

String Message::getContent() const
{
	return content;
}

void Message::readFromFile(std::ifstream& ifs)
{
	std::string tempContent;
	std::getline(ifs, tempContent);
	content = String(tempContent.c_str());
	ifs >> timestamp;
	ifs.ignore(); 
}

void Message::writeToFile(std::ofstream& ofs) const
{
	ofs << content.c_str() << '\n';
	ofs << timestamp << '\n';
	if (ofs.is_open()) {
		std::cout << "Error writing Message to file.\n";
	}
	else {
		std::cout << "Message written successfully.\n";
	}
}
