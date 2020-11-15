#include "PPMWriter.h"

PPMWriter::PPMWriter() {
	//Do nothing for now -_-
}

void PPMWriter::generatePPM(Canvas& canvas) {
	//First, let's set up the .ppm file
	char extension[20]{ ".ppm" };

	time_t rawTime;
	struct tm timeInfo;
	char buffer[120];
	errno_t err;

	time(&rawTime);

	err = localtime_s(&timeInfo, &rawTime);
	if (err) {
		std::cout << "Invalid Input to localtime_s! Exiting...\n";
		std::exit(-1);
	}

	strftime(buffer, sizeof(buffer), "%d-%m-%Y_%H-%M-%S", &timeInfo);
	strcat_s(buffer, extension);

	std::cout << buffer << " has been created! \n";

	std::ofstream fileOut{ buffer };

	if (!fileOut) {
		// Print an error
		std::cerr << "Uh oh, "<<buffer<<" could not be opened for writing!\n";
	}


	//Now we have to get the Data in there!
	fileOut << "P3\n";	//Magic Number, specifies what kind of file it is
	fileOut << canvas.getWidth() << ' ' << canvas.getHeight() << '\n';	//Width and Height of the image
	fileOut << "255\n"; //Denotes the largest possible color value
	for (int y = 0; y < canvas.getHeight(); ++y) {
		for (int x = 0; x < canvas.getWidth(); ++x) {
			Color temp = canvas.getColor(x,y);
			fileOut << (int)(254.99f * temp.getRed()) << ' ' << (int)(254.99f * temp.getGreen()) << ' ' << (int)(254.99f * temp.getBlue()) << '\n';
		}
	}
	fileOut.close();
}
