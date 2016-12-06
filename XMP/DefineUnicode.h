#ifndef __DEFINE_UNICODE_H__
#define __DEFINE_UNICODE_H__

namespace duilib
{
#ifdef _UNICODE
    typedef wchar_t              char_t;
    typedef std::wstring         string_t;
    typedef std::wstringstream   stringstream_t;
    typedef std::wifstream       ifstream_t;   
    typedef std::wofstream       ofstream_t;   
    typedef std::wfstream        fstream_t;   
#else
    typedef char                 char_t;
    typedef std::string          string_t;
    typedef std::stringstream    stringstream_t;
    typedef std::ifstream_t      ifstream_t;
    typedef std::ofstream_t      ofstream_t;   
    typedef std::fstream         fstream_t;   
#endif
}

#endif
