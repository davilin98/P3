/// @file

#include <iostream>
#include <math.h>
#include "pitch_analyzer.h"

using namespace std;

/// Name space of UPC
namespace upc {
  FILE *result;
  
  void PitchAnalyzer::autocorrelation(const vector<float> &x, vector<float> &r) const {
    result = fopen("autocorrelation.txt", "a");
    
    for (unsigned int l = 0; l < r.size(); ++l) {
  	  	/// \TODO Compute the autocorrelation r[l]
         r[l]=0;
      for(unsigned int k=0; k<frameLen-l; ++k ){
        r[l] += x[k]*x[k+l]; 
            /*printf("%f\n", x[k]);*/
      }
      r[l]=r[l]/r.size();
     /* printf("%f\n",r[l]);*/ 
    }

    if (r[0] == 0.0F) //to avoid log() and divide zero 
      r[0] = 1e-10; 

    for(unsigned int i=0; i<r.size(); i++){
      fprintf(result, "%f\n",r[i]);
    }
    fclose(result);
  }

  void PitchAnalyzer::set_window(Window win_type) {
    if (frameLen == 0)
      return;

    window.resize(frameLen);
    float a = 0.53836, b = 0.46164, pi = 3.1415926535;
    switch (win_type) {
    case HAMMING:
      /// \TODO Implement the Hamming window
     
      for(unsigned int n = 0; n < frameLen; n++){
          float coseno = cos((2 * pi * n )/ (frameLen-1));
          window[n] = (a - b * coseno);
       }
      break;
    case RECT:
    default:
      window.assign(frameLen, 1);
    }
  }

  void PitchAnalyzer::set_f0_range(float min_F0, float max_F0) {
    npitch_min = (unsigned int) samplingFreq/max_F0;
    if (npitch_min < 2)
      npitch_min = 2;  // samplingFreq/2

    npitch_max = 1 + (unsigned int) samplingFreq/min_F0;

    //frameLen should include at least 2*T0
    if (npitch_max > frameLen/2)
      npitch_max = frameLen/2;
  }

  bool PitchAnalyzer::unvoiced(float pot, float r1norm, float rmaxnorm) const {
    /// \TODO Implement a rule to decide whether the sound is voiced or not.
    /// * You can use the standard features (pot, r1norm, rmaxnorm),
    ///   or compute and use other ones.

   bool unvoiced = false;
    if(pot>-30 && r1norm > 0.86 && rmaxnorm < 0.15){
      unvoiced=true;
    }
    
    return unvoiced;
    
  }

  float PitchAnalyzer::compute_pitch(vector<float> & x) const {
    if (x.size() != frameLen)
      return -1.0F;

    //Window input frame
    for (unsigned int i=0; i<x.size(); ++i)
      x[i] *= window[i];

    vector<float> r(npitch_max);

    //Compute correlation
    autocorrelation(x, r);

    vector<float>::const_iterator iR = r.begin(), iRMax = iR;

    /// \TODO 
	/// Find the lag of the maximum value of the autocorrelation away from the origin.<br>
	/// Choices to set the minimum value of the lag are:
	///    - The first negative value of the autocorrelation.
	///    - The lag corresponding to the maximum value of the pitch.
    ///	   .
	/// In either case, the lag should not exceed that of the minimum value of the pitch.

  for(iR=r.begin()+npitch_min ; iR !=r.begin()+npitch_max; ++iR){
    if(*iR>*(iRMax+npitch_min)){
      iRMax= iR;
    }
  
  }
    unsigned int lag = iRMax - r.begin();

    

    float pot = 10 * log10(r[0]);
   // printf("%f ",pot);

    //You can print these (and other) features, look at them using wavesurfer
    //Based on that, implement a rule for unvoiced
    //change to #if 1 and compile
   /* printf("%f\n", r[lag]);*/

   FILE *rnorm= fopen("rnorm.txt","a");
   FILE *rnormmax = fopen("rnormmax.txt","a");

#if 0
    if (r[0] > 0.0F){
      cout << pot << '\t' << r[1]/r[0] << '\t' << r[lag]/r[0] << endl;
      fprintf(rnorm,"%f\n",r[1]/r[0]);
      fprintf(rnormmax, "%f\n",r[lag]/r[0]);
    }
#endif

  fclose(rnorm);
  fclose(rnormmax); 
    if (unvoiced(pot, r[1]/r[0], r[lag]/r[0]))
      return 0;
    else
      return (float) samplingFreq/(float) lag;
  }
}
