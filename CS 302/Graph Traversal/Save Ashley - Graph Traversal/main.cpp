#include <iostream>
#include <unordered_map>
#include<list>
#include<fstream>
#include<vector>

bool saveAshley(std::string leon, int ammo, 
std::unordered_map <std::string , std::list<std::string>> map,
std::unordered_map<std::string, int> enemiesAtLocation,
std::unordered_map <std::string, int>& ammoAtLocation,
std::unordered_map <std::string, std::string>& predecessor){
    // if ammo is less then the ammo passed in return false
    if (ammoAtLocation[leon] > ammo)
        return false;
    ammoAtLocation[leon] = ammo - enemiesAtLocation[leon];
    //update ammo
    ammo -= enemiesAtLocation[leon];
    //if ammo is negative, can't traverse the graph anymore
    if (ammo < 0)
        return false;
    //if church is found, return true
    if (leon == "Church")
        return true;
    //recursively loop through its neighbors
    for (auto neighbor : map[leon]){
        if (saveAshley(neighbor, ammoAtLocation[leon], map, 
        enemiesAtLocation, ammoAtLocation, predecessor)){
            predecessor[neighbor] = leon;
            return true;
        }
    }
    return false;

    
}

int main(){

    //variables on the pdf
    std::unordered_map <std::string, std::list<std::string>> adjList;
    std::unordered_map <std::string, int> enemiesAtLocation;
    std::unordered_map <std::string, int> ammoAtLocation;
    std::unordered_map <std::string, std::string> predecessor;

    //input variables
    std::ifstream mapFile;
    std::string mapFileName;
    std::ifstream enemyFile;
    std::string enemyFileName;

    //printing to get map input
    std::cout << "LEON!!!" << std::endl << std::endl;
    std::cout << "Enter map file: ";
    std::cin >> mapFileName;

    //check if Mapfile is valid
    mapFile.open(mapFileName);
    if (!mapFile.is_open())
        return 0;
    //printing to get enemy input
    std::cout << "Enter enemies file: ";
    std::cin >> enemyFileName;
    
    //check if enemyfile is valid
    enemyFile.open(enemyFileName);
    if (!enemyFile.is_open())
        return 0;
    
    //extract information from the mapfile
    std::string from, to;
    while(mapFile >> from >> to){
        adjList[from].push_back(to);
    }
    mapFile.close();
    std::string location;
    int count;
    //extract information from the enemyfile
    while(enemyFile >> location >> count){
        enemiesAtLocation[location] = count;
        //also make ammo at location = 0 
        ammoAtLocation[location] = 0;
    }
    enemyFile.close();


    bool found = saveAshley("Village", 10, adjList, enemiesAtLocation, ammoAtLocation, predecessor);
    if (!found){
        std::cout << "Leon DIED" << std::endl;
        return 0;
    }
    std::cout << "I'm coming Ashley!"<< std::endl;
    //print using the predecessor array

    //construct a path using vectos
    std::vector<std::string> path;
    std::string current = "Church";
    while (current != "Village") {
        path.push_back(current);
        current = predecessor[current];
    }
    path.push_back("Village");

    //print from path vector
    for (int i = path.size() - 1; i >= 0; i--) {
        std::cout << path[i];
        if (i != 0) 
            std::cout << " -> ";
    }
    std::cout << std::endl;



    return 0;
}