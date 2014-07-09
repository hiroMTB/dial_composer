//
//  dt_rhythm_lib.cpp
//  dial_t
//
//  Created by mtb on 5/5/14.
//
//

#include "dt_rhythm_lib.h"

dt_rhythm_lib::dt_rhythm_lib(){}

dt_rhythm_lib::~dt_rhythm_lib(){
    shapes.clear();
}

int dt_rhythm_lib::getRhythmSize(int slotNum){
    if(0<= slotNum && slotNum < shapes.size())
        return shapes[slotNum].size();
    else
        return -1;
}

const RHYTHM_SHAPE& dt_rhythm_lib::getRhythm(int slotNum, int type){
    return shapes[slotNum][type];
}

void dt_rhythm_lib::setup(int start_slot, int end_slot){
	cout << "setting up Rhythm Library" << endl;

    // add fake data for slot0, slot1
    SLOT_SHAPE ss0, ss1;
	//    ss0.push_back("fake");
	//    ss1.push_back("fake");
    shapes.push_back(ss0);
    shapes.push_back(ss1);
    
    string directryName = "rhythmShape";
    ofDirectory dir;
    int numFile = dir.listDir(directryName);
    
    for(int i=0; i<numFile; i++){
		string fileName = dir.getFile(i).getFileName();
        string path = directryName+ "/" + fileName;
		int slot_num = ofToInt(dir.getFile(i).getBaseName());
        
		if(start_slot<= slot_num && slot_num<=end_slot){
		
			ifstream file(ofToDataPath(path).c_str());
	//        cout << "loading " << ofToDataPath(path).c_str() << endl;
			
			SLOT_SHAPE ss;

			int line_num=0;
			while( file.good()){

				string binst;
				getline(file, binst, '\n');
				if(line_num++<=1) continue;	// avoid to load 0000 or 1000

				if(binst!=""){
					RHYTHM_SHAPE s;
					for(int b=0; b<binst.size(); b++){
						bool bin = 0;
						char c = binst[b];
						if(c == '1'){
							bin = 1;
						}
						s.push_back(bin);
					}
					ss.push_back(s);
					//                cout << ofToString(++n) + " : " + binst <<endl;
				}
			}
			shapes.push_back(ss);
		}
    }
    
    maxSlot = numFile+1;
    
//#ifdef _DEBUG
//    //check
//    for(int i=0; i<shapes.size(); i++){
//        SLOT_SHAPE ss = shapes[i];
//        for(int j=0; j<ss.size(); j++){
//            cout << ofToString(ss[j]) << endl;
//        }
//
//    }
//#endif
	
}



