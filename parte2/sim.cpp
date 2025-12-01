#include <fstream>
#include <iostream>
#include <vector>
#include <string>

int checkFrames(std::vector<std::pair<int, bool>>& frames, int npv){
    for(int i = 0; i < frames.size(); i++){
        if(frames[i].first == npv){
            return i;
        }
    }
    return -1;
}

int main(int argc, char* argv[]) {
    std::string filename;
    int nFrames, nFramesSize;
    bool verbose = false;
    if(argc == 3){
        nFrames = std::stoi(argv[1]);
        nFramesSize = std::stoi(argv[2]);
        filename = argv[3];
    }
    else if(argc == 5){
        nFrames = std::stoi(argv[1]);
        nFramesSize = std::stoi(argv[2]);
        filename = argv[4];
        verbose = true;
    }
    else{
        std::cerr << "Uso: sim <nFrames> <nFramesSize> [--verbose] <filename>" << std::endl;
        return 1;
    }

    std::vector<std::pair<int, bool>> frames(nFrames, std::make_pair(-1, false));
    int pointer = 0;
    int b = 0;
    while(nFramesSize){
        nFramesSize = nFramesSize >> 1;
        b++;
    }
    b--;
    int mask = (1 << b) - 1;

    std::ifstream file(filename);
    std::ofstream out("output.txt");
    std::string vaStr;

    int total = 0;
    int fallos = 0;

    while(file >> vaStr){
        total++;
        int va = strtol(vaStr.c_str(), nullptr, 0);
        int offset = va & mask;
        int npv = va >> b;
        std::cout<<b;
        if(verbose) out << va << " " << npv << " " << offset << " ";
        int frame;
        if(checkFrames(frames, npv) == -1){
            fallos++;
            if(verbose) out << "FALLO ";

            while(frames[pointer].second){
                frames[pointer].second = false;
                pointer++;
                pointer %= nFrames;
            }
            frames[pointer].first = npv;
            frames[pointer].second = true;
            frame = pointer;
        }
        else{
            if(verbose) out << "HIT ";
            frame = checkFrames(frames, npv);
        }

        int df = (frame << b) | offset;
        if(verbose) out << frame << " " << df << std::endl;
    }

}
