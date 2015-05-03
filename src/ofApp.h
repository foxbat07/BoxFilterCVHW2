#pragma once

#include "ofMain.h"
#include "ofxOpenCV.h"
#include "ofxcv.h"
using namespace ofxCv;
using namespace cv;


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofImage addBorders (ofImage image);
        ofImage calculateIntegralImage (ofImage image);
        ofImage blurImage (ofImage image);
        ofImage createTestImage (ofImage image);
    
    
    
        int boxFilterSize = 5;
        int testHeight = 10 + 2 * boxFilterSize;
        int testWidth = 10 + 2 * boxFilterSize;
        
    
        ofImage inputImage;
        ofImage testOneImage;
        ofImage testIntegralImage;
        ofImage POIImage;
        ofImage newBlurImage;
    
        ofImage inputImageWithBorders;
    
    
        Mat inputImagetoMat;
        Mat testOneImagetoMat;
        Mat testIntegralImageMat ;
        Mat blurredImageMat;
    
        int imageWidth;
        int imageHeight;
    
        Mat myKernel;
    
    
    
    
    
        
    
    
		
};
