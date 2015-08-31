#include <iostream>
#include <vigra/multi_array.hxx>
#include <vigra/stdimage.hxx>
#include <vigra/impex.hxx>
#include <vigra/multi_convolution.hxx>
#include <vigra/tinyvector.hxx>
#include "inc/random_distribution.cpp"

using namespace vigra;

void gradient(MultiArray<2, UInt8> &imageArray, int method, int max) {
  
  MultiArray<2, TinyVector<UInt8, 2> > grad(imageArray.shape());
  //gaussianGradientMultiArray(imageArray, grad, 0.5);
  symmetricGradientMultiArray(imageArray, grad);
    
  std::vector<double> v;
  double sum = 0;
  for(int i = 0; i < imageArray.size(); i++) {
    v.push_back(((double) sqrt(squaredNorm(grad[i]))));
    sum += v[i];
    imageArray[i] = 0;
  }
  for(int i = 0; i < v.size(); i++)
    v[i] /= sum;
 
  random_distribution r(v,method);
  
  for(int i = 0; i < max; i++)
    imageArray[r.dist(method)]++;
}

int main(int argc, char ** argv) 
{

    if(argc != 3)
    {
        std::cout << "Usage: " << argv[0] << " infile outfile" << std::endl;
        std::cout << "(grayscale only, supported formats: " << impexListFormats() << ")" << std::endl;
        
        return 1;
    }
    try 
    {
        char * in_filename  = argv[1];
        char * out_filename = argv[2];

	// read image header information from in_filename
        ImageImportInfo imageInfo(in_filename);
        // instantiate array for image data
        MultiArray<2, UInt8> imageArray(imageInfo.shape());
        // copy image data from file into array
        importImage(imageInfo, imageArray);
        
        // if you don't need the information from ImageImportInfo, you can also
        // simply pass the filename (this will resize imageArray internally!)
        importImage(in_filename, imageArray);
        // set every second horizontal line to black
	
	
	gradient(imageArray, 1, 100000);
	out_filename[3] = '1';
        exportImage(imageArray, ImageExportInfo(out_filename));
	
	gradient(imageArray, 2, 100000);
	out_filename[3] = '2';
        exportImage(imageArray, ImageExportInfo(out_filename));
	
	gradient(imageArray, 2, 100000);
	out_filename[3] = '3';
        exportImage(imageArray, ImageExportInfo(out_filename));
        
    }
    catch (std::exception & e) 
    {
        // catch any errors that might have occurred and print their reason
        std::cout << e.what() << std::endl;
        return 1;
    }
    
return 0;
}
