

// will initiate later
class utils {
private:
	int width{ 1920 }, height{ 1080 };
public:
	utils(int w, int h) 
		: width(w), height(h) {	
		// constructor	
	}
	int getWidth() { return width; }
	int getHeight() { return height; }
	

	// getPixel functions
	bool checkForBlackScreen() {

		return false;
	}

};