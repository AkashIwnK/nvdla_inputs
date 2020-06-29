//#include <dirent.h>
//#include <sys/types.h>
#include <bits/stdc++.h> 
#include <iostream>
#include <string>
#include <vector>

#define DEFAULT_DIR		    "."
#define NVDLA_RUNTIME_PATH  "./nvdla_runtime"
#define NVDLA_MODULE_NAME   "hpvm-miniera_int8.nvdla"
#define OUTPUT_FILE_NAME    "output.dimg"
#define MAX_NUM_FILE_NAMES  20

void ExecuteWithImage(std::string &ImageName) {
	std::string Cmd = std::string(NVDLA_RUNTIME_PATH) + std::string(" --loadable ") 
					+  std::string(NVDLA_MODULE_NAME) + std::string(" --image ") 
					+ std::string(ImageName) + std::string(" --rawdump");
	std::cout << "Executing command: " << Cmd << "\n";
	system(Cmd.c_str());
	std::cout << "Execution completed\n";
}

void GenerateFileNames(std::vector<std::string> &FileNamesList) {
	std::string Prefix = "00";
	for(int i = 0; i < MAX_NUM_FILE_NAMES; i++) {
		FileNamesList.push_back(Prefix + std::to_string(i) + std::string("_0.jpg"));
	}
	Prefix = "10";
	for(int i = 0; i < MAX_NUM_FILE_NAMES; i++)
		FileNamesList.push_back(Prefix + std::to_string(i) + std::string("_1.jpg"));
	
	Prefix = "20";
	for(int i = 0; i < MAX_NUM_FILE_NAMES; i++)
		FileNamesList.push_back(Prefix + std::to_string(i) + std::string("_2.jpg"));
	
	Prefix = "30";
	for(int i = 0; i < MAX_NUM_FILE_NAMES; i++)
		FileNamesList.push_back(Prefix + std::to_string(i) + std::string("_3.jpg"));
	
	Prefix = "40";
	for(int i = 0; i < MAX_NUM_FILE_NAMES; i++)
		FileNamesList.push_back(Prefix + std::to_string(i) + std::string("_4.jpg"));
}

int main() {
	// Open the default directory
	//DIR *DirHandle = opendir(DEFAULT_DIR);
	//assert (DirHandle && "Cannot open given directory.");
	
	// Generate all the file names
	std::vector<std::string> FileNamesList;
	GenerateFileNames(FileNamesList);
	
	int Correct = 0;
	int numImages = 0;
	for(auto &FileName : FileNamesList) {
	//while (auto *Dp = readdir(DirHandle)) {
		//std::string FileName = Dp->d_name;
		std::cout << "Found file: " << FileName << "\n";
		
		// We are just looking for jpg or pgm images
		std::string Extension = FileName.substr(FileName.find(".") + 1);
		std::cout << "File Extension: " << Extension << "\n";
 		if(Extension != "jpg" && Extension != "pgm" )
			continue;
 		numImages++;
		
		// Get ground label and class
		std::string ImageNameWithoutExt = FileName.substr(0, FileName.find("."));
		std::cout << "ImageNameWithoutExt: " << ImageNameWithoutExt <<  "\n";
		std::string GroundLabel = ImageNameWithoutExt.substr(ImageNameWithoutExt.find("_") + 1);
		std::cout << "GroundLabel: " << GroundLabel << "\n";
		int GroundClass = std::stoi(GroundLabel);
		std::cout << "Class from file Name: " << GroundClass << "\n";
		
		// Execute binary and module with this image
		ExecuteWithImage(FileName);
		
		// Parse the output file and get class with highest probablity
		std::ifstream OutputFile(OUTPUT_FILE_NAME);
		assert(!OutputFile.fail() && "Failed to open output file.");
		std::string Line;
		int OutputClass = -1;
		int Class = 0;
		while (std::getline(OutputFile, Line)) {
			// Read all the numbers and get the class with the highest
			float MaxProbablity = 0;
			size_t Pos = 0;
			std::string Delimiter = " ";
			while ((Pos = Line.find(Delimiter)) != std::string::npos) {
				std::string Token = Line.substr(0, Pos);
			    std::cout << Token << "\n";
			    Line.erase(0, Pos + Delimiter.length());
			    size_t Size;
			    float Prob = std::stof(Token, &Size);
			    if(Prob > MaxProbablity) {
			    	Prob = MaxProbablity;
			    	OutputClass = Class;
			    }
			    Class++;
			}
		}
		
		// If the expected and output classes are the same, classification is correct
		std::cout << "OUTPUT CLASS: " << OutputClass << "\n";
		if(OutputClass == GroundClass)
			Correct++;
	}
	
	// Compute final accuracy
	float Accuracy = 100 * (((float)Correct) * 1.0 / ((float)numImages));
	std::cout << "FINAL ACCURACY: " << Accuracy << "\n";
	
	return 0;
}

