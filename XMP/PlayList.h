#pragma once
#include <vector>
#include "DefineUnicode.h"
using namespace duilib;
using namespace std;

// 播放列表文件解析，只支持简单的M3U播放列表，后期可添加PLS等列表格式的支持
// 此类只是简单示例，VLC内部已经实现了播放列表功能，请自行阅读文档
class CPlaylist
{
public:
    CPlaylist(void);
    ~CPlaylist(void);

    bool ReadFile (const string_t &strPath);    // 读取播放列表文件到m_vctPath      
    bool WriteFile(const string_t &strPath);    // 根据m_vctPath生成播放列表      
    bool ReadFile (const string_t &strPath, vector<string_t> &vctPlaylist);      // 读取播放列表文件到vctPlaylist
    bool WriteFile(const string_t &strPath, vector<string_t> &vctPlaylist);      // 根据vctPlaylist生成播放列表
    void Add(string_t strPath);                 // 添加路径到列表尾部
    vector<string_t> GetPlaylist();             // 获取播放列表所有路径
    string_t GetPlaylist(unsigned uIndex);      // 获取播放列表指定下标的路径

private:
    vector<string_t> m_vctPath;                 // 存放播放列表的路径
};

