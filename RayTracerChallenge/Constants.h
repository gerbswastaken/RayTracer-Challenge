#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace constants {
	inline constexpr int gWidth{ 96 };					//Width of the image generated
	inline constexpr int gHeight{ 54 };					//Height of the image generated
	inline constexpr float gEpsilon{ 0.0001f };			//A small floating point value for comparing floating point numbers
	inline constexpr float gPI{ 3.141592f };			//The value of Pi. Add more digits for more accuracy or whatever
	inline constexpr float gFieldOfView{ 1.570796f };	//Field of View of the camera, basically the angular limits of the camera (in radians of course)
	inline constexpr int gNumOfThreads{ 3 };			//Number of CPU cores to use (I found 3 to work the best on my PC, but it's a piece of shit, so mess around with it)

}

#endif
