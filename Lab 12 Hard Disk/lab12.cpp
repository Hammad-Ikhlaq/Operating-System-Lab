#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fcntl.h>
#include <fstream>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

using namespace std;

//#define HDSize 100
//#define blockSize 20
int HDSize;
int blockSize;
int totalBlocks;
//int current = 0; // Current index in HD file

void callList(const int, const char*);
int main(int argc, char* argv[])
{
    if(argc != 4)
    {
        cout << "Usage: <command> <fileName> <HDSize> <BlockSize>\n";
        return -1;
    }
    
    const char* fName = argv[1];
    HDSize = atoi(argv[2]);
    blockSize = atoi(argv[3]);
    totalBlocks = HDSize/blockSize;
    
    int fd = open(fName, O_RDONLY);
    const char* fl = (const char*)mmap(NULL, HDSize, PROT_READ, MAP_PRIVATE, fd, 0);
    
    //Change directory
    char* cmd = new char[20]{};
    char* folName = new char[10];
    strcpy(folName, "root");
    int startBlock = 0; // in root
    do{
        cout << folName << " >> ";
        cin.getline(cmd, 20);
        
        if(cmd[0] == 'c' && cmd[1] == 'd') // cd command
        {
            //Change start block
            char* tempfol;
            tempfol = strtok(cmd, " ");
            tempfol= strtok(NULL, " ");

            char* fptr = strstr((char*)fl, tempfol);
            if(fptr && fptr < fl + startBlock*blockSize+blockSize && fptr > fl + startBlock*blockSize)
            {
                char* tempPtr = fptr;
                //Check if folder
                while(*tempPtr != '0')
                    tempPtr++;
                
                tempPtr++;
                if(!(*tempPtr == 'F' && *(tempPtr+1) == 'O' && *(tempPtr+2) == 'L'))
                {
                    cout << tempfol << " is not a folder!\n";
                    continue;
                }
                //Change current and startBlock
                fptr -= 2;
                startBlock = *fptr - 48;
                strcpy(folName, tempfol);
                cout << "Folder changed to " << folName << endl;
            }
            else
            {
                cout << "No such directory exists.\n";
            }
        }
        else if (strcmp(cmd, "list") == 0)
        {
//            cout << folName << endl;
            cout << "Current directory: " << folName << endl;
            callList(startBlock, fl);
        }
        else if(cmd[0] != 'q')
            cout << "Command not recognized.\n";
    } while(cmd[0] != 'q');
    
    if(cmd)
        delete[] cmd;
    if(folName) delete[] folName;
    close(fd);
    return 0;
}

void callList(const int stBlock, const char* fl)
{
    int blockNo;
    int start = stBlock * blockSize;
    //Implement ls
    cout << "\nBlockNo\tName\t\tType\n\n";
    for(int i = start; i < start + blockSize; i++)
    {
        if(totalBlocks <= 10)
            blockNo = fl[i] - 48;
        else
        {
            char bNo[3] = {};
            for(int k = 0; fl[i] != '0'; k++)
                bNo[k] = fl[i++];
            blockNo = atoi(bNo);
        }
        // Skip to item Name
        i++;
        while(fl[i] == '0')
            i++;
        
        cout << blockNo << "\t";
        // Item name
        while(fl[i] != '0')
        {
            cout << fl[i];
            i++;
        }
        
        i++;
        
        if(fl[i] == 'F' && fl[i+1] == 'O' && fl[i+2] == 'L')
            cout << "\t\tFolder\n";
        else if(fl[i] == 'F' && fl[i+1] == 'I' && fl[i+2] == 'L')
            cout << "\t\tFile\n";
        else
            cout << "\t\tUndefined type\n";
        i += 2;
    }   
}