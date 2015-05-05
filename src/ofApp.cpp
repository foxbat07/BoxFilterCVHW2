#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    // getting in notredame image
    inputImage.loadImage("notredame.png");
   
    imageWidth = inputImage.getWidth();
    imageHeight= inputImage.getHeight();
    
    //testWidth = imageWidth;
    //testHeight = imageHeight;
    
    // creating an image of 1s,using ofImage to intialize then convert to Mat
    testOneImage.allocate(testWidth, testHeight, OF_IMAGE_GRAYSCALE);
    testIntegralImage.allocate(testWidth, testHeight, OF_IMAGE_GRAYSCALE);
    newBlurImage.allocate(testWidth, testHeight, OF_IMAGE_GRAYSCALE);
    cout<< "allocated images"<<endl;
    //inputImageWithBorders = addBorders(inputImage);
    testOneImage = createTestImage(testOneImage);
    cout<< "added borders"<<endl;
    //testIntegralImage = calculateIntegralImage(inputImageWithBorders);
    testIntegralImage = calculateIntegralImage(testOneImage);
    cout<<"created integral image";
    newBlurImage = blurImage(testIntegralImage);
    cout<<"created blur image";
    
    
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(128);
    
    //testOneImage.draw(ofGetWidth()/2,0, testWidth* 20, testHeight *10);
    int xDisplacement = 100 ;
    int yDisplacement = 300 ;
    int multiplier = 5;
    
    
    testOneImage.draw( xDisplacement, yDisplacement / 2 , testWidth * multiplier, testHeight* multiplier);
    testIntegralImage.draw(xDisplacement* 5.5 ,yDisplacement /2  , testWidth* multiplier, testHeight* multiplier);
    newBlurImage.draw(xDisplacement* 11, yDisplacement /2 , testWidth* multiplier, testHeight* multiplier);
    
    ofDrawBitmapString("Black image with padding ", xDisplacement , yDisplacement /4);
    
    ofDrawBitmapString("integral image ", xDisplacement* 5.5, yDisplacement /4);
    
    ofDrawBitmapString(" blurred image", xDisplacement* 11, yDisplacement /4);
    
    ofDrawBitmapString("noise from the surroudding padding ", xDisplacement* 11, yDisplacement /6);
    
    

    
    //testIntegralImage.draw(testWidth ,0 , ofGetWidth()  , ofGetHeight());
    drawNumbers();
    
    
    
    
    
}





ofImage ofApp::addBorders (ofImage image)
{
    imageWidth = inputImage.getWidth();
    imageHeight= inputImage.getHeight();
    
    testWidth = imageWidth + 2 * boxFilterSize;
    testHeight = imageHeight + 2 * boxFilterSize;
    inputImageWithBorders.allocate(testWidth, testHeight, OF_IMAGE_GRAYSCALE);

    for (int i = 0 ; i < image.getPixelsRef().size()  ;i++) {
        
        inputImageWithBorders.getPixelsRef()[i] = 0.0f; // make them white for now
        
    }
    
    for ( int i = 0 ; i < testHeight ; i++ )
    {
        for (int j = 0 ; j< testWidth ; j++)
        {
            inputImageWithBorders.getPixelsRef()[( i+boxFilterSize) * testWidth + (j+boxFilterSize) ] = image.getPixelsRef()[i * testWidth + j] ;
            
        }
    }
    
    inputImageWithBorders.reloadTexture();
    return inputImageWithBorders;
    
}





ofImage ofApp::calculateIntegralImage (ofImage image)
{
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
                    tempSum += image.getPixels()[a * testHeight + b ];
                    
                }
            }
            cout<< tempSum << " ";
            testIntegralImage.getPixelsRef()[i*testHeight+ j] = tempSum;
            
        }
        cout<<endl;
        
    }
    
    return testIntegralImage;
    

}

ofImage ofApp::blurImage (ofImage image)
{
    cout<<"creating the blurred image "<<endl;
    
    // calcualting points of interest for the image
    //sum = D - B - C + A
    // THE FILTER SIZE = 3 FOR NOW, THE IMAGE POINT WILL BE
    
    for ( int i = boxFilterSize; i < testHeight - 1; i++ )
    {
        for (int j = boxFilterSize ; j< testWidth  - 1; j++)
        {
            float tempCalc = 0.0f;
            //D-B-C+A
            
            tempCalc = testIntegralImage.getPixelsRef()[ i*testHeight+ j]
            +testIntegralImage.getPixelsRef()[ (i - boxFilterSize)*testHeight+ (j - boxFilterSize) ]
            - testIntegralImage.getPixelsRef()[ (i - boxFilterSize)*testHeight+ j ]
            - testIntegralImage.getPixelsRef()[ i * testHeight+ (j - boxFilterSize) ];
            
            
            float normalizedCalc = tempCalc;
            cout<< normalizedCalc << " ";
            newBlurImage.getPixelsRef()[i * testWidth + j] = normalizedCalc ;

        }
        
        cout<< endl;
    }
    
    return newBlurImage;
    
    
}


ofImage ofApp::createTestImage (ofImage image)
{
    // insiializng it with 0s, then changing it to 1s
    for (int i = 0 ; i < image.getPixelsRef().size()  ;i++) {
        
        image.getPixelsRef()[i] = 0.0f; // make them white for now
        
    }
    
    for ( int i = boxFilterSize ; i < testHeight - boxFilterSize ; i++ )
    {
        for (int j = boxFilterSize ; j< testWidth - boxFilterSize ; j++)
        {
            image.getPixelsRef()[i * testWidth + j] = 1.0f;
            
        }
    }
    
    image.reloadTexture();
    
    // printing the test image
    
    for ( int a = 0 ; a < testHeight ; a ++)
    {
        for ( int b = 0 ; b < testWidth ; b++ )
        {
            //cout<< "entering loop";
            
            float value =  image.getPixelsRef()[ a * testWidth + b ] ;
            cout<< value << " ";
            
        }
        
        cout << endl;
    }
    
    
    return image;
    
}


void ofApp::drawNumbers()
{
    //time to draw all the numbers image, integral,blurred
    //use ofDrawBitmapToString
    
    
    for ( int a = 0 ; a < testHeight ; a ++)
    {
        for ( int b = 0 ; b < testWidth ; b++ )
        {
            //cout<< "entering loop";
            
            float testOneImageValue =  testOneImage.getPixelsRef()[ a * testWidth + b ] ;
            float testIntegralImageValue = testIntegralImage.getPixelsRef()[ a * testWidth + b ] ;
            float blurImageValue = newBlurImage.getPixelsRef()[ a * testWidth + b ] ;
            
            int xDisplacement = 100 ;
            int yDisplacement = 300 ;
            int multiplier = 25;
            ofDrawBitmapString( ofToString( testOneImageValue ) , a * multiplier + xDisplacement , b* multiplier + yDisplacement);
            
            ofDrawBitmapString( ofToString( testIntegralImageValue ) , a * multiplier + 5.5 * xDisplacement, b* multiplier + yDisplacement);
            
            if( ( a>=boxFilterSize && a <= testHeight - boxFilterSize) && ( b>=boxFilterSize && b <= testWidth - boxFilterSize))
                ofDrawBitmapString( ofToString( blurImageValue ) , a * multiplier + 10 * xDisplacement, b* multiplier + yDisplacement);
            
            
            

            
        }
        
        
    }
    

    
    
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
