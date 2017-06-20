# PiCameraTweet

 PiCameraTweet: Send a picture to a twitter account from Raspberry Pi3!
 Implemented with: C++'s raspicam & opencv, Python's tweepy, etc.
 
 Carlos Jimenez, por.aca@gmail.com, June 2017
 GitHub: https://github.com/por-aca/PiCameraTweet.git

 References:
  http://www.uco.es/investiga/grupos/ava/node/40
  http://opencv.org/
  http://www.tweepy.org/
  https://apps.twitter.com/app/new
  https://www.tutorialspoint.com/python/python_command_line_arguments.htm 
  http://man7.org/linux/man-pages/man3/strftime.3.html
  http://raspi.tv/?p=5918 
  and a lot others...
 
 File structure:
  |------------------- CMakeLists.txt
  |------------------- PiCameraTweet.sh
  |------------------- README.md
  |--[ build ]-------- tweetPic.py
  |                |-- PiCameraTweet (once compiled)
  |                \-- [ images ]
  |--[ interface ]---- clearscreen.h
  \--[ source ]------- clearscreen.cpp
                   \-- PiCameraTweet.cpp
             
 Build steps:
  create CMakeLists.txt
  mkdir build
  cd build
  cmake ..
  make
  ./PiCameraTweet
 
 Raspicam/OpenCV Compile Reference (lmmal might not work):
  g++ file.cpp -o file -I/usr/local/include/ -lraspicam -lraspicam_cv \
      -lmmal -lmmal_core -lmmal_util -lopencv_core -lopencv_highgui
 