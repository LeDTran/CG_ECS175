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

  // cout << "line points" << endl;
  // for(int i = 0; i < (int)linep1.size(); i++){
  //   cout << linep1[i] + 1 << " " << linep2[i] + 1 << endl;
  // }

  // cout << "face points" << endl;
  // for(int i = 0; i < (int)facep1.size(); i++){
  //   cout << facep1[i] + 1 << " " << facep2[i] + 1 << " " << facep3[i] + 1 << endl;
  // }

  // cout << "normal points" << endl;
  // for(int i = 0; i < (int)facep1.size(); i++){
  //   cout << fnormx[i] << " " << fnormy[i] << " " << fnormz[i] << " " << endl;
  // }

  // cout << "Ip" << endl;
  // for(int i = 0; i < (int)IpR.size(); i++){
  //       cout << IpR[i] << " " << IpG[i] << " " << IpB[i] << " " << endl;
  // }

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
  float i, j, tmpa, tmpb;
  for (i = 1; i < getNumEdgePoints(); i++){
    j = i; 
    while(j > 0 && edgebpoints[j - 1] > edgebpoints[j]){
      tmpa = edgeapoints[j];
      tmpb = edgebpoints[j];
      edgeapoints[j] = edgeapoints[j - 1];
      edgebpoints[j] = edgebpoints[j - 1];
      edgeapoints[j - 1] = tmpa;
      edgebpoints[j - 1] = tmpb;
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
          j--;
        }
      }
      low = high;
    }
  }

  // for(int a = 0; a < (int)edgeapoints.size(); a++){
  //   cout << edgeapoints[a] << ", " << edgebpoints[a] << endl;
  // }
  // cout << "----------------------" << endl;
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

