#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;


void splitString(string& line, char delimiter, vector<string>* r)
{
    int begin = 0;
    for(int i = 0; i < line.size(); ++i)
    {
        if(line[i] == delimiter)
        {
            (*r).push_back(line.substr(begin, i - begin));
            begin = i + 1;
        }
    }
    if(begin < line.size())
        (*r).push_back(line.substr(begin, line.size() - begin));
}


vector<string> argv_to_args(int argc, char* argv[]) 
{
    vector<string> args;
    for(int i = 1; i < argc; ++i)
        args.push_back(string(argv[i]));
    return args;
}


int main(int argc, char* argv[])
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    if(argc != 2)
    {
        cout << "wrong argc" << endl;
        cout << "cat predictFile | ./logloss class_num" << endl;
        return EXIT_FAILURE;
    }
    int classNum = stoi(argv[1]);
    string line;
    vector<string> segList;
    unsigned long long lineNum = 0;
    long double loss = 0.0;
    const double epsilon = 1e-15;
    while(getline(cin, line))
    {
        segList.clear();
        splitString(line, ' ', &segList);
        if(classNum + 1 != segList.size())
        {
            cout << "error line:" << line << endl;
            return EXIT_FAILURE;
        }
        int label = stoi(segList[0]);
        if(label < 1 || label > classNum)
        {
            cout << "error label out of range:" << label << endl;
            return EXIT_FAILURE;
        }
        double p = stod(segList[label]);
        p = max(p, epsilon);
        p = min(p, 1 - epsilon);
        loss += log(p);
        lineNum++;
    }
    loss /= lineNum;
    cout << "lineNum = " << lineNum << endl;
    cout << "logloss = " << -loss << endl;
}

