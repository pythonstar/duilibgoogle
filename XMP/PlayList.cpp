#include "PlayList.h"
#include <tchar.h>
#include <iostream>			
#include <sstream> 		
#include <fstream>	
using namespace std;	

// 播放列表的文件类型，暂时只解析M3U类型
enum enum_PlaylistType   
{
    em_Unknown,  // 未知类型
    em_PLS,      // PLS类型
    em_M3U       // M3U类型
};


CPlaylist::CPlaylist(void)
{
}

CPlaylist::~CPlaylist(void)
{
}
    
void CPlaylist::Add(string_t strPath)
{
    m_vctPath.push_back(strPath);
}

bool CPlaylist::ReadFile(const string_t &strPath)
{
    return ReadFile(strPath, m_vctPath);
}

bool CPlaylist::WriteFile(const string_t &strPath)
{
    return WriteFile(strPath, m_vctPath);
}

bool CPlaylist::ReadFile(const string_t &strPath, vector<string_t> &vctPlaylist)
{
    ifstream_t  fin;
    string_t    strInput;
    char_t      ch;

    fin.imbue(locale(""));
    fin.open(strPath.c_str(), ios::in);
    if(!fin.is_open())
    {
        return	false;
    }

    while(fin.get(ch))
    {   
        strInput = _T("");

        while(ch != _T('\n'))
        {		
            strInput.push_back(ch);	
            if(! fin.get(ch))	
            {
                break;
            }
        }

        vctPlaylist.push_back(strInput);
    }

    fin.close();
    return true;
}

bool CPlaylist::WriteFile(const string_t &strPath, vector<string_t> &vctPlaylist)
{
    ofstream_t fout;

    fout.imbue(locale(""));
    fout.open(strPath.c_str(), ios::out | ios::trunc);
    if(!fout.is_open())
    {
        return false;
    }

    vector<string_t>::iterator it;
    for(it = vctPlaylist.begin();	it < vctPlaylist.end();	it++)
    {
        fout << *it << endl;
    }

    fout.close();	
    return true;
}

vector<string_t> CPlaylist::GetPlaylist()
{
    return m_vctPath;
}

duilib::string_t CPlaylist::GetPlaylist( unsigned uIndex )
{
    if (uIndex < 0 || uIndex >= m_vctPath.size())
    {
        return _T("");
    }

    return m_vctPath[uIndex];
}
