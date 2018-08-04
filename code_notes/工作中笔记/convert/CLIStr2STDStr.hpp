/// <summary>
/// Author�� Huangl
/// ת���й��ַ��������й��ַ���
/// ת����ANSI����
/// </summary>
/// <param name="strObj"></param>
/// <returns></returns>
inline std::string CLIStrToStdStr(System::String^ strObj)
{
    using namespace System::Runtime::InteropServices;
    auto ptr = Marshal::StringToHGlobalAnsi(strObj);
    std::string str(static_cast<char*>(ptr.ToPointer()));
    Marshal::FreeHGlobal(ptr);
    return str;
}