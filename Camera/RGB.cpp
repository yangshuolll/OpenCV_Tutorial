/* Date: 25.Mar.2016
 * Author: Tom
 * Target: Calculate the average of RGB Values 
 * Tool: C++ and OpenCV
 * OS: OS X Yosemite
 * Camera: 10fps, 720p
 */
#include<iostream>
#include<stdio.h>
#include<opencv/highgui.h>
#include<opencv2/opencv.hpp>
#include<sys/time.h>
#include<time.h>
#include<unistd.h>
#include<signal.h>
#include<vector>
using namespace std;
using namespace cv;
//Length Width and FPS
int const ROWS = 720; 
int const COLS = 1280;
int const FPS = 10;
// Store final answer
int r_pixels[ROWS * COLS];
int g_pixels[ROWS * COLS];
int b_pixels[ROWS * COLS];
// Sum all the values in each channel per sec
void Sum_All(int *pixels,Mat src){
	for(int i = 0; i < ROWS; i++){  //ROWS -> 1
		for(int j = 0; j < COLS; j++){
			pixels[i * COLS + j] += (int)src.at<uchar>(i,j);
		}
	}		
}
// calculte the average
void Average(int pixels[]){
	for(int i = 0; i < ROWS * COLS; i++){
		pixels[i] /= FPS;
	}
}
// show the final result
void Show_Ans(int pixels[]){
		for(int i = 0; i < ROWS; i++){  //ROWS -> 1
			for(int j = 0; j < COLS; j++){
				if(j == 0){
					cout << "[" << pixels[i * COLS + j];
				}else{
					cout << "," <<pixels[i * COLS + j];
					if(j == COLS-1){
						cout << "]" << endl;
					}
				}
			}
		}
}

int main(int argc, char* argv[]){
	freopen("ans.out","w",stdout);
	VideoCapture cap(0);
	char name[]= "camera";
	if(!cap.isOpened()){
		cout << "error: can not open the camera" << endl;
		return -1;
	}
	namedWindow(name,WINDOW_NORMAL);
	moveWindow(name, 100, 100);
	vector<Mat> p;
	int temp = 10;
	Mat red, green, blue;
	int flag = 0;
	memset(r_pixels,0,sizeof(r_pixels));
	memset(g_pixels,0,sizeof(g_pixels));
	memset(b_pixels,0,sizeof(b_pixels));
	while(1){
		Mat frame;
		bool bSuccess = cap.read(frame);
		if(!bSuccess){
			cout << "Can not read a frame from the video stream" << endl;
			break;
		}
		split(frame, p);
		
		Sum_All(b_pixels,p[0]);
		Sum_All(g_pixels,p[1]);
		Sum_All(r_pixels,p[2]);
		if((flag != 0) && (flag % FPS == 0) ){
			Average(b_pixels);
			Average(g_pixels);
			Average(r_pixels);
			cout <<"------------------"<<flag/10<<" sec-----------------"<<endl;
			cout << "------------RED Channel--------------" << endl;
			Show_Ans(r_pixels);
			cout << "--------------Green Channel---------" << endl;
			Show_Ans(g_pixels);
			cout << "--------------Blue Channel----------" << endl;
			Show_Ans(b_pixels);
			memset(r_pixels,0,sizeof(r_pixels));
			memset(g_pixels,0,sizeof(g_pixels));
			memset(b_pixels,0,sizeof(b_pixels));
		}
		imshow(name,frame);
		flag++;
		if(waitKey(30) == 30){
			cout << "Exit the programme" << endl;
			break;
		}
	}
	return 0;
}
