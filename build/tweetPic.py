#!/usr/bin/env python
# coding=utf-8
from __future__ import unicode_literals
# 
# PiCameraTweet: Send a picture to a twitter account from Raspberry Pi3!
# Implemented with: C++'s raspicam & opencv, Python's tweepy, etc.
# See PiCameraTweet.cpp for more details
#
# Carlos Jimenez, por.aca@gmail.com, June 2017
# GitHub: https://github.com/por-aca/PiCameraTweet.git
#
# Usage: tweetPic.py [-h] -i <input_file>
#
import tweepy 
import sys, getopt
from subprocess import call  
from datetime import datetime  

global path
path = ''  # 'images/' not necessary when called from C++ program
input_file = ''

print
print " Preparing image to tweet it through tweepy... "

# Command line arguments
	# print 'Number of arguments:', len(sys.argv), 'arguments.'
	# print 'Argument List:', str(sys.argv)
def main(argv):	
	try:
		opts, args = getopt.getopt(argv,"hi:",["ifile="])
	except getopt.GetoptError:
		print 'tweetPic.py [-h] -i <input_file>'
		sys.exit(2)
	for opt, arg in opts:
		if opt == '-h':
			print 'tweetPic.py [-h] -i <input_file>'
			sys.exit()
		elif opt in ("-i", "--ifile"):
			global input_file
			input_file = arg

if __name__ == "__main__":
	main(sys.argv[1:])

# Consumer keys and access tokens, used for OAuth  
# Important: Need to obtain keys & tokens by creating an application
# in the Twitter Developer webpage. Check the following pages:
#	http://www.tweepy.org/
#	https://apps.twitter.com/app/new
consumer_key = '*************************'
consumer_secret = '**************************************************'
access_token = '**************************************************'
access_token_secret = '*********************************************'
      
# OAuth process, using the keys and tokens  
auth = tweepy.OAuthHandler(consumer_key, consumer_secret)  
auth.set_access_token(access_token, access_token_secret)  
       
# Creation of the actual interface, using authentication  
api = tweepy.API(auth)
      
# Send the tweet with photo  
output_path_file = path + input_file
status = 'Photo auto-tweet from Pi: ' + input_file
api.update_with_media(output_path_file, status=status)
print " Tweet should be ready by now @por_aca "
print
	#print "path: " + path
	#print "input_file: " + input_file
	#print "output_path_file: " + output_path_file
