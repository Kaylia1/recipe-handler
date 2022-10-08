#include "../include/file_manager.h"

FileManager::FileManager(std::string ingredientPath, std::string recipePath) {
    this->ingredientPath = ingredientPath;
    this->recipePath = recipePath;
}

FileManager::~FileManager(){
    
}