#ifndef STDD_UTILITIES_H
#define STDD_UTILITIES_H

#include <iostream>
#include <vector>

namespace stdd {

	class Utilities {
	public:
		size_t MainMenu(std::ostream& os);
		size_t PlayType(std::ostream& os);
		std::vector<int> generateLuckyNumbers(int num);
	};
	extern Utilities ut;

} // !namespace_stdd

#endif // !STDD_UTILITIES_H
