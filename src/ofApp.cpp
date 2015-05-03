#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    // getting in notredame image
    inputImage.loadImage("notredame.png");
    inputImagetoMat = toCv(inputImage);
    imageWidth = inputImage.getWidth();
    imageHeight= inputImage.getHeight();
    
    
    //testWidth = imageWidth;
    //testHeight = imageHeight;
    
    
    // creating an image of 1s,using ofImage to intialize then convert to Mat
    testOneImage.allocate(testWidth, testHeight, OF_IMAGE_GRAYSCALE);
    testIntegralImage.allocate(testWidth, testHeight, OF_IMAGE_GRAYSCALE);
    
    
    // insiializng it with 0s, then changing it to 1s
    for (int i = 0 ; i < testOneImage.getPixelsRef().size()  ;i++) {
        
        testOneImage.getPixelsRef()[i] = 0.0f; // make them white for now

    }
    
    for ( int i = boxFilterSize ; i < testHeight -boxFilterSize ; i++ )
        {
        for (int j = boxFilterSize ; j< testWidth -boxFilterSize ; j++)
            {
                testOneImage.getPixelsRef()[i * testWidth + j] = 1.0f;
                
            }
        }
            
            
    
    testOneImage.reloadTexture();
    
    // converting it to Mat for ops
    testOneImagetoMat = toCv(testOneImage);
    
    
    
    // printing the test image
    /*
    for ( int a = 0 ; a < testHeight ; a ++)
    {
        for ( int b = 0 ; b < testWidth ; b++ )
        {
           cout<< "entering loop";
           cout<< testOneImage.getPixelsRef()[ a * testWidth + b ] ;
            
        }
     
        cout << endl;
    }
    
    */
    
    
    cout<<"Creating the integral image"<<endl;

    
    
    for ( int i = 0 ; i < testHeight ; i++ )
        {
            for (int j = 0 ; j< testWidth  ; j++)      //loops to iterate over the correct pixel, use a sum to add everything in that area
            {
                
                float tempSum  = 0.0f;
                
                for ( int a = 0 ;  a <= i ; a ++)
                    {
                        for ( int b = 0 ; b <= j ; b++ )
                        {
                            tempSum += testOneImage.getPixels()[a * testHeight + b ];
                        
                        }
                    }
                cout<< tempSum << " ";
                testIntegralImage.getPixelsRef()[i*testHeight+ j] = tempSum;
                
            }
            cout<<endl;
            
        }
    
    
    
    cout<<"creating the blurred image "<<endl;

    // calcualting points of interest for the image
    //sum = D - B - C + A
    // THE FILTER SIZE = 3 FOR NOW, THE IMAGE POINT WILL BE
    
    for ( int i = boxFilterSize; i < testHeight  ; i++ )
        {
        for (int j = boxFilterSize ; j< testWidth  ; j++)
            {
             float tempCalc = 0.0f;
             //D-B-C+A
                
             tempCalc = testIntegralImage.getPixelsRef()[ i*testHeight+ j]
                        +testIntegralImage.getPixelsRef()[ (i - boxFilterSize)*testHeight+ (j - boxFilterSize) ]
                        - testIntegralImage.getPixelsRef()[ (i - boxFilterSize)*testHeight+ j ]
                        - testIntegralImage.getPixelsRef()[ i*testHeight+ (j - boxFilterSize) ];
                
                
                
                cout<< tempCalc << " ";
            }
            
            cout<< endl;
        }
    
             
                
                
    
    
    
    
    myKernel.ones(boxFilterSize, boxFilterSize, 1);
    myKernel= myKernel/25;      //normalizing
    
    
    
    
    
    
    //testOneImagetoMat.ones(testWidth, testHeight, 1);
    //allocating the integral image
    //testOneImage = Mat(testHeight, testWidth, CV_8UC1, pixels, 100);
    
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(255);
    drawMat(inputImagetoMat,0, 0);
    
    
    //testOneImage.draw(ofGetWidth()/2,0, testWidth* 20, testHeight *10);
    
    drawMat( testOneImagetoMat, 500, 100 );
    drawMat(myKernel, 600, 100);
    
    //drawMat(testOneImage, ofGetWidth()/2 , 0);
    
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
