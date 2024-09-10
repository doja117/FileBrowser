        #include<iostream>
        #include<stdlib.h>
        #include <filesystem>
        #include <unistd.h>
        #include<vector>
        #include<fstream>
        #include <cstdlib>
        namespace fs = std::filesystem;

        void returnPaths(){
            std::cout<<"Press q to quit\nPress index of file left to the file whenever asked\n";
            fs::path current_path=fs::current_path();
            while (true){
                std::vector<fs::path>v;
                for (const auto &entry:fs::directory_iterator(current_path)){
                    v.push_back(entry.path());
                }         
                int count=0;   
                for (auto x:v){
                    std::cout<<++count<<".\t"<<x.filename().string()<<"\n";
                }
                std::cout<<"Enter B to go back\nF to go forward\nN to get fileName\nPress L to List All Files\nPress P to get complete path\nPress D to remove Current Path\nPress E to Edit File\nPress C to create New File\nPress R to Read File\n";
                char c; std::cin>>c;    if (c=='B'||c=='b'){current_path=current_path.parent_path();}
                if (c=='f'||c=='F'){
                    std::cout<<"Select file you want to go(Linux every dir is a file)"<<"\n";   int f;std::cin>>f;
                    if ((int)f>v.size()){perror("Input out of bounds");} else {
                        current_path=v[(int)f-1];
                    }
                }
                if (c=='l' || c=='L'){
                    int c=0;
                    for (auto x:v){std::cout<<++c<<".\t"<<x.filename().string()<<"\n";}
                }
                if (c=='N'||c=='n'){std::cout<<current_path.filename()<<"\n";}
                if (c=='p'||c=='P'){std::cout<<current_path<<"\n";}
                if (c=='D'||c=='d'){
                    std::cout<<"Going to Delete The File Path"<<((char*)current_path.string().c_str())<<"\nPress Y to continue\n";
                    char f; std::cin>>f;
                    if (f=='y' || f=='Y'){
                    const fs::path parent_path=current_path.parent_path();
                    int x=rmdir((char*)current_path.string().c_str());
                    current_path=parent_path;
                    std::cout<<"Current Path Deleted\n";   
                }}
                if (c=='C'||c=='c'){
                    std::cout<<"Enter fileName\n";
                    std::string fName;std::cin>>fName;
                    const std::string newFilePath=current_path.string()+"/"+fName;
                    std::ofstream file(newFilePath);
                    if (file.is_open()){
                        std::cout<<"File Created Successfully\n";
                    }
                }
                if (c=='e' || c=='E'){
                    int c=0;
                    for (auto x:v){std::cout<<++c<<".\t"<<x.filename().string()<<"\n";}std::cout<<"Select File To Edit\n";  int fileNum;    std::cin>>fileNum;
                    if (fileNum>v.size()){perror("File Num Out of Bounds");}    else {
                        const fs::path filePath=v[fileNum-1];
                         std::string command = "vim " + filePath.string();
                        int result = std::system(command.c_str());
                        if (result!=0){perror("Failed to Open Vim to Edit\n");}
                    }
                }
                if (c=='r'||c=='R'){
                     int c=0;
                        for (auto x:v){std::cout<<++c<<".\t"<<x.filename().string()<<"\n";}std::cout<<"Select File To Read\n";
                        int fileNum;    std::cin>>fileNum;
                        if (fileNum>v.size()){perror("File Num Out of Bounds");}    else {
                        const fs::path filePath=v[fileNum-1];
                        std::string command="cat "+filePath.string();
                        int result=std::system(command.c_str());
                        if (result!=0){perror("Failed to Read File\n");}                                            
                }}

                if (c=='q'||c=='Q'){std::cout<<"Exiting Function, GB!!!!!!!!";  return;}
            }
        }










        
