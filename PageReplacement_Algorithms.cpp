#include <iostream> // for input/output
#include <vector> // for vectors
#include <unordered_map> // for unordered_map that stores the page and the last time it was used
#include <algorithm> // for find function
#include <sstream>  // for string stream

// to check if a page exists in the frames
bool pageExist(std::vector<int>& frames, int page) {
    return std::find(frames.begin(), frames.end(), page) != frames.end();
}

// to find the index of the least recently used page in the frames vector using the pageLastUsed map
int find_LRU_index(std::unordered_map<int, int>& pageLastUsed, std::vector<int>& frames) {
    int minIndex = 0;
    int minTime = pageLastUsed[frames[0]];
    for (size_t i = 1; i < frames.size(); ++i) {
        if (pageLastUsed[frames[i]] < minTime) {
            minTime = pageLastUsed[frames[i]];
            minIndex = i;
        }
    }
    return minIndex;
}
// simulate LRU page replacement algorithm
int LRU(std::vector<int>& pageReference, int numFrames) {
    std::vector<int> frames;
    std::unordered_map<int, int> pageLastUsed;
    int PF = 0;
    // loop through the page reference string
    for (int page : pageReference) {
        if (!pageExist(frames, page)) {
            PF++;
            if (frames.size() < numFrames) {
                frames.push_back(page);
                pageLastUsed[page] = PF;
            }
            else {
                int lruIndex = find_LRU_index(pageLastUsed, frames);
                frames[lruIndex] = page;
                pageLastUsed[page] = PF;
            }
        }
        // if the page already exists in the frames, update the last time it was used
        else {
            pageLastUsed[page] = PF;
        }
        // print the page table, frames, and the number of faults
        std::cout << "Step " << PF << ": Page fault(" << page << ")- ";
        std::cout << "Page Table: {";
        for (int p : frames) {
            std::cout << p << ", ";
        }
        std::cout << "}, Frames: [";
        for (int p : frames) {
            std::cout << p << ", ";
        }
        std::cout << "], Faults: " << PF << std::endl;
    }

    return PF;
}
// to simulate Optimal page replacement algorithm
int Optimal(std::vector<int>& pageReference, int numFrames) {
    std::vector<int> frames;
    int PF = 0;

    // loop through the page reference string
    for (int i = 0; i < pageReference.size(); ++i) {
        int page = pageReference[i];
        // if the page does not exist in the frames
        if (!pageExist(frames, page)) {
            PF++;
            if (frames.size() < numFrames) {
                frames.push_back(page);
            }
            // if the frames are full, find the farthest page in the future and replace it
            else {
                int farthestIndex = -1;
                int farthestDistance = -1;
                for (int j = 0; j < frames.size(); ++j) {
                    int distance = 0;
                    for (int k = i + 1; k < pageReference.size(); ++k) {
                        if (frames[j] == pageReference[k]) {
                            break;
                        }
                        distance++;
                    }
                    if (distance > farthestDistance) {
                        farthestDistance = distance;
                        farthestIndex = j;
                    }
                }
                frames[farthestIndex] = page;
            }
        }
        std::cout << "Step " << PF << ": Page fault(" << page << ")- ";
        std::cout << "Page Table: {";
        for (int p : frames) {
            std::cout << p << ", ";
        }
        std::cout << "}, Frames: [";
        for (int p : frames) {
            std::cout << p << ", ";
        }
        std::cout << "], Faults: " << PF << std::endl;
    }

    return PF;
}

// to simulate FIFO page replacement algorithm
int FIFO(std::vector<int>& pageReference, int numFrames) {
    std::vector<int> frames;
    int PF = 0;
    int currentIndex = 0;

    for (int page : pageReference) {
        if (!pageExist(frames, page)) {
            PF++;
            // if the frames are not full, add the page to the frames
            if (frames.size() < numFrames) {
                frames.push_back(page);
            }
            // if the frames are full, replace the page at the currentIndex
            else {
                frames[currentIndex] = page;
                currentIndex = (currentIndex + 1) % numFrames;
            }
        }
        std::cout << "Step " << PF << ": Page fault(" << page << ")- ";
        std::cout << "Page Table: {";
        for (int p : frames) {
            std::cout << p << ", ";
        }
        std::cout << "}, Frames: [";
        for (int p : frames) {
            std::cout << p << ", ";
        }
        std::cout << "], Faults: " << PF << std::endl;
    }

    return PF;
}

int main() {
    std::vector<int> pageReference;
    int numFrames;

    std::cout << "Enter the page reference string (Separate numbers by commas (,)): ";
    std::string input;
    std::getline(std::cin, input);

    //gets input from user and stores it in pageReference vector
    std::stringstream ss(input);
    std::string token;
    while (std::getline(ss, token, ',')) {
        pageReference.push_back(std::stoi(token));
    }
    //gets the number of frames from user
    std::cout << "Enter the number of frames:";
    std::cin >> numFrames;

    std::cout << "For LRU Algorithm:"<<std::endl;
    int lruFaults = LRU(pageReference, numFrames);
    std::cout << "Total Page Faults: " << lruFaults << std::endl;

    std::cout << "\nFor Optimal Algorithm:"<<std::endl;
    int optimalFaults = Optimal(pageReference, numFrames);
    std::cout << "Total Page Faults: " << optimalFaults << std::endl;

    std::cout << "\nFor FIFO Algorithm:"<<std::endl;
    int fifoFaults = FIFO(pageReference, numFrames);
    std::cout << "Total Page Faults: " << fifoFaults << std::endl;

    return 0;
}
