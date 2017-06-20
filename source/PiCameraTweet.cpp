/*
 * PiCameraTweet: Send a picture to a twitter account from Raspberry Pi3!
 * Implemented with: C++'s raspicam & opencv, Python's tweepy, etc.
 * 
 * Carlos Jimenez, por.aca@gmail.com, June 2017
 * GitHub: https://github.com/por-aca/PiCameraTweet.git
 *
 * References:
 *  http://www.uco.es/investiga/grupos/ava/node/40
 *  http://opencv.org/
 *  http://www.tweepy.org/
 *  https://apps.twitter.com/app/new
 *  https://www.tutorialspoint.com/python/python_command_line_arguments.htm 
 *  http://man7.org/linux/man-pages/man3/strftime.3.html
 *  http://raspi.tv/?p=5918 
 *  and a lot others...
 * 
 * File structure:
 *  |------------------- CMakeLists.txt
 *  |------------------- PiCameraTweet.sh
 *  |------------------- README.md
 *  |--[ build ]-------- tweetPic.py
 *  |                |-- PiCameraTweet (once compiled)
 *  |                \-- [ images ]
 *  |--[ interface ]---- clearscreen.h
 *  \--[ source ]------- clearscreen.cpp
 *                   \-- PiCameraTweet.cpp
 *             
 * Build steps:
 *  create CMakeLists.txt
 *  mkdir build
 *  cd build
 *  cmake ..
 *  make
 *  ./PiCameraTweet
 * 
 * Raspicam/OpenCV Compile Reference (lmmal might not work):
 *  g++ file.cpp -o file -I/usr/local/include/ -lraspicam -lraspicam_cv \
 *      -lmmal -lmmal_core -lmmal_util -lopencv_core -lopencv_highgui
 * 
 */
 
#include <ctime>
#include <iostream>
#include <raspicam/raspicam_cv.h>
#include <unistd.h>
#include <term.h>
#include <limits>
#include "clearscreen.h"
#include <string>
#include <sstream>

#define fileNameFormat "images/%Y%m%d_%H%M%S_PiCameraTweet.jpg\0"

const unsigned short int fileNameSize = 41;
const unsigned short int framesCount = 20;

using namespace std;
using namespace cv;

int main( int argc, char **argv ) {  
  
	//
	// Initialize timer and libraries variables
	//   
	time_t timer_begin, timer_end;
	raspicam::RaspiCam_Cv Camera;
	cv::Mat image;
	
    //
    // Set camera parameters
    //
    Camera.set( CV_CAP_PROP_FORMAT, CV_8UC3 );
		// Any primitive type from the list can be defined by an identifier
		// in the form CV_<bit-depth>{U|S|F}C(<number_of_channels>)
		// where U is unsigned integer type, S is signed integer type,
		// and F is float type.
    
   	//
	// Clear the screen and print header
	//
	ClearScreen();
	cout << endl << "========================================================================" << endl;
	cout <<         " PiCameraTweet: Send a picture to a twitter account from Raspberry Pi3! ";
	cout << endl << "========================================================================" << endl << endl;

    //
    // Open camera
    //
    cout << " Opening Camera... " << endl;
    if( !Camera.open() ) {
		cerr << " Error opening the camera! " << endl;
		return -1;
	}
	
	//
    // Start image capture
    //
    cout << " Capturing " << framesCount << " frames... " << endl;
    time( &timer_begin );
    for( int i=1; i < framesCount + 1; i++ ) {
		Camera.grab();
        Camera.retrieve( image );
        if( i%5 == 0 ) cout << "\r Captured " << i << " images " << std::flush;
    }
    cout << endl << " Stop camera " << endl;
    Camera.release();
    
	//
	// Generate file name using timestamp
	//
	static char fileName[fileNameSize];
    time_t now = time(0);
    strftime( fileName, sizeof(fileName), fileNameFormat, localtime(&now) );
		// cout << fileName << endl;
		//
		// size_t strftime(char *s, size_t max, const char *format, const struct tm *tm);
		//
		// The strftime() function formats the broken-down time tm according to
		// the format specification format and places the result in the
		// character array s of size max.  The broken-down time structure tm is
		// defined in <time.h>.  See also ctime(3).
    
    //
    // Show time statistics
    //
    time( &timer_end );		// get current time; same as: timer = time(NULL)
    double secondsElapsed = difftime ( timer_end, timer_begin );
    cout << " " << secondsElapsed << " seconds for " << framesCount << " frames: FPS = " << \
			( float ) ( ( float )( framesCount ) / secondsElapsed ) << endl;
    
    //
    // Save and display image
    //
    cv::imwrite( fileName, image );
    cout << " Color Image saved at: ../" << fileName << endl << endl;
		// image = imread( imageName, IMREAD_COLOR ); // Read an image file
	if( image.empty() ) {		// Check for invalid input
		cout << " Could not open or find the image! " << endl ;
		return -1;
	}
	namedWindow( "Display window", WINDOW_NORMAL );	// Create a window
								// WINDOW_KEEPRATIO
								// WINDOW_AUTOSIZE
	moveWindow( "Display window", 840, 48);
	imshow( "Display window", image );		// Show image inside it
	cout << " Check if you like the picture, then press any key... " << endl << endl;
	
	cvWaitKey(0);	// Wait for a keystroke in the window
	
	image.release();
	cvDestroyAllWindows();	// cvDestroyWindow( "Display window" );
	//delete[] &image;	// Segmentation fault if used alone;
						// Double free or corruption error when used
						// with image.release or cvDestroy...
    
	//
	// Ask user to accept photo for twitter
	//
	string input = "";
	char inputChar = {0};
	while ( true ) {
		cout << "   Enter 'y' to tweet photo (or another key to cancel): ";
		getline(cin, input);
		if( input.length() == 1 ) {
			inputChar = toupper( input[0] );
			// inputChar = putchar( toupper( input[0] ) );
			break;
		}
		cout << "   Invalid character, please try again " << endl;
	}
		// cout << " You entered: " << inputChar << endl << endl;
	if( inputChar == 'Y' ) {
		cout << endl;
	}
	else {
		cout << endl << " OK, re-run the program to try another shot! " << endl << endl;
		return 0;
	}
	
    //
    // Call tweetPic.py Python script to tweet image 
    //
    cout << " Calling python script to tweet image... " << endl;
    string command = "python tweetPic.py -i ";
    command += fileName;
		// Example:  command = "python tweetPic.py -i images/image.jpg";    
    system(command.c_str());

	return 0;
    
}
