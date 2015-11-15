#include "Face.h"

Face::Face(){
	//ctr
}

Face::Face(vector<float> as, vector<float> bs, 
            vector<float> ipr, vector<float> ipg, vector<float> ipb){
	apoints = as;
	bpoints = bs;

  IpR = ipr;
  IpG = ipg;
  IpB = ipb;
}

void Face::printData(){
  cout << "ab" << endl;
  for(int i = 0; i < (int)apoints.size(); i++){
    cout << apoints[i] << " " << bpoints[i] << endl;
  }

  cout << "Ip" << endl;
  for(int i = 0; i < (int)IpR.size(); i++){
        cout << IpR[i] << " " << IpG[i] << " " << IpB[i] << " " << endl;
  }

  cout << "------------------------------------" << endl;
}

float Face::getAPoint(int i){
  return apoints[i];
}

float Face::getBPoint(int i){
  return bpoints[i];
}

int Face::getNumPoints(){
  return apoints.size();
}

float Face::getLocalMaxB(){
  //need to get local max from stored edge points 
  float max = edgebpoints[0];
  for(int i = 0; i < (int)edgebpoints.size(); i++){
    if(edgebpoints[i] > max){
      max = edgebpoints[i];
    }
  }
  return max;
}

float Face::getLocalMinB(){
  //need to get local min from stored edge points 
  int min = edgebpoints[0];
  for(int i = 0; i < (int)edgebpoints.size(); i++){
    if(edgebpoints[i] < min){
      min = edgebpoints[i];
    }
  }
  return min;
}

void Face::addEdgeA(float a){
  edgeapoints.push_back(a);
}

void Face::addEdgeB(float b){
  edgebpoints.push_back(b);
}

void Face::resetEdgePoints(){
  edgeapoints.clear();
  edgebpoints.clear();
}

void Face::sortEdgePoints(){
  float i, j, tmpa, tmpb, tmpiar, tmpiag, tmpiab;
  for (i = 1; i < getNumEdgePoints(); i++){
    j = i; 
    while(j > 0 && edgebpoints[j - 1] > edgebpoints[j]){
      tmpa = edgeapoints[j];
      tmpb = edgebpoints[j];
      edgeapoints[j] = edgeapoints[j - 1];
      edgebpoints[j] = edgebpoints[j - 1];
      edgeapoints[j - 1] = tmpa;
      edgebpoints[j - 1] = tmpb;

      tmpiar = edgeiar[j];
      tmpiag = edgeiag[j];
      tmpiab = edgeiab[j];
      edgeiar[j] = edgeiar[j-1];
      edgeiag[j] = edgeiag[j-1];
      edgeiab[j] = edgeiab[j-1];
      edgeiar[j - 1] = tmpiar;
      edgeiag[j - 1] = tmpiag;
      edgeiab[j - 1] = tmpiab;

      j--;
    }
  }

  float low = 0, high = 0;
  while(low < getNumEdgePoints()){
    high++;
    if(edgebpoints[high] != edgebpoints[high -1]){
      for (i = low; i < high; i++){
        j = i; 
        while(j > low && edgeapoints[j - 1] > edgeapoints[j]){
          tmpa = edgeapoints[j];
          tmpb = edgebpoints[j];
          edgeapoints[j] = edgeapoints[j - 1];
          edgebpoints[j] = edgebpoints[j - 1];
          edgeapoints[j - 1] = tmpa;
          edgebpoints[j - 1] = tmpb;

          tmpiar = edgeiar[j];
          tmpiag = edgeiag[j];
          tmpiab = edgeiab[j];
          edgeiar[j] = edgeiar[j-1];
          edgeiag[j] = edgeiag[j-1];
          edgeiab[j] = edgeiab[j-1];
          edgeiar[j - 1] = tmpiar;
          edgeiag[j - 1] = tmpiag;
          edgeiab[j - 1] = tmpiab;            

          j--;
        }
      }
      low = high;
    }
  }

//   for(int a = 0; a < (int)edgeapoints.size(); a++){
//     cout << edgeapoints[a] << ", " << edgebpoints[a] << " : " << edgeiar[a] << " " << edgeiag[a] << " " << edgeiab[a] <<endl;
//   }
//   cout << "----------------------" << endl;
}

// void Face::sortEdgePoints(){
//   int i, j, tmpx, tmpy;
//   for (i = 1; i < getNumEdgePoints(); i++){
//     j = i; 
//     while(j > 0 && edgeypoints[j - 1] > edgeypoints[j]){
//       tmpx = edgexpoints[j];
//       tmpy = edgeypoints[j];
//       edgexpoints[j] = edgexpoints[j - 1];
//       edgeypoints[j] = edgeypoints[j - 1];
//       edgexpoints[j - 1] = tmpx;
//       edgeypoints[j - 1] = tmpy;
//       j--;
//     }
//   }

//   int low = 0, high = 0;
//   while(low < getNumEdgePoints()){
//     high++;
//     if(edgeypoints[high] != edgeypoints[high -1]){
//       for (i = low; i < high; i++){
//         j = i; 
//         while(j > low && edgexpoints[j - 1] > edgexpoints[j]){
//           tmpx = edgexpoints[j];
//           tmpy = edgeypoints[j];
//           edgexpoints[j] = edgexpoints[j - 1];
//           edgeypoints[j] = edgeypoints[j - 1];
//           edgexpoints[j - 1] = tmpx;
//           edgeypoints[j - 1] = tmpy;
//           j--;
//         }
//       }
//       low = high;
//     }
//   }
// }

int Face::getNumEdgePoints(){
  return edgeapoints.size();
}

float Face::getEdgeAPoint(int i){
  return edgeapoints[i];
}

float Face::getEdgeBPoint(int i){
  return edgebpoints[i];
}

//color: 0 = red, 1 = green, 2 = blue
float Face::getPointIntensity(int i, int color){
  if(color == 0){
    return IpR[i];
  }
  else if(color == 1){
    return IpG[i];
  }
  else if(color == 2){
    return IpB[i];
  }
  return 0;
}

void Face::setEdgeIntensity(float iar, float iag, float iab){
  edgeiar.push_back(iar);
  edgeiag.push_back(iag);
  edgeiab.push_back(iab);
}

//color: 0 = red, 1 = green, 2 = blue
float Face::getEdgeIntensity(int i, int color){
  if(color == 0){
    return edgeiar[i];
  }
  else if(color == 1){
    return edgeiag[i];
  }
  else if(color == 2){
    return edgeiab[i];
  }
  return 0;
}