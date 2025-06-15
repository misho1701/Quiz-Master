#include "ChallengeProgress.h"

ChallengeProgress::ChallengeProgress(Type type, int target) :
	type(type), target(target), current(0), completed(false), completedAt(0) {}

void ChallengeProgress::updateProgress(int value) {
	if (!completed) {
		current += value;
		if (current >= target) {
			completed = true;
			completedAt = std::time(nullptr);
		}
	}
	if (current < 0) current = 0;
	if (current > target) current = target;
	if (completed) {
		std::cout << "Challenge completed! Type: " << type << ", Reward: " << target << " points.\n";
	}
	else {
		std::cout << "Challenge progress updated! Type: " << type << ", Current: " << current << "/" << target << "\n";
	}
}

void ChallengeProgress::display() const {
	std::cout << "Challenge type: " << type << ", Progress: " << current << "/" << target;
	if (completed) std::cout << " (Completed)";
	std::cout << "\n";
	if (completed) {
		std::cout << "Completed at: " << std::ctime(&completedAt);
	}
	else {
		std::cout << "Not completed yet.\n";
	}
}

void ChallengeProgress::readFromFile(std::ifstream& ifs)
{
	String typeStr;
	ifs >> typeStr;
	if (typeStr == "TEST_SOLVE") 
	{
		type = TEST_SOLVE;
	}
	else if (typeStr == "NORMAL_SOLVE") {
		type = NORMAL_SOLVE;
	}
	else if (typeStr == "QUIZ_CREATE") {
		type = QUIZ_CREATE;
	}
	else 
	{
		std::cerr << "Unknown challenge type: " << typeStr.c_str() << "\n";
		return;
	}
	ifs >> target;
	ifs >> current;
	ifs >> completed;
	ifs >> completedAt;
	ifs.ignore(); 
	if (ifs.is_open()) {
		std::cout << "Error reading ChallengeProgress from file.\n";
	}
	else {
		std::cout << "ChallengeProgress read successfully.\n";
	}
	ifs.clear(); 
}

void ChallengeProgress::writeToFile(std::ofstream& ofs) const
{
	ofs << type << '\n';
	ofs << target << '\n';
	ofs << current << '\n';
	ofs << completed << '\n';
	ofs << completedAt << '\n';
	if (ofs.is_open()) {
		std::cerr << "Error writing ChallengeProgress to file.\n";
	}
	else {
		std::cout << "ChallengeProgress written successfully.\n";
	}
	ofs.clear();
}