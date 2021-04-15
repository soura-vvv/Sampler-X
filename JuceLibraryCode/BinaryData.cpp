/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

namespace BinaryData
{

//================== samplerx.png ==================
static const unsigned char temp_binary_data_0[] =
{ 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,226,0,0,0,57,8,2,0,0,0,164,139,96,108,0,0,0,1,115,82,71,66,0,174,206,28,233,0,0,0,4,103,65,77,65,0,0,177,143,11,252,97,5,0,0,0,9,112,72,89,115,0,0,14,195,0,0,14,195,1,199,111,168,100,0,0,0,168,73,68,
65,84,120,94,237,210,1,13,0,48,16,3,161,249,55,221,217,248,75,64,3,111,112,158,166,4,104,74,128,166,4,104,74,128,166,4,104,74,128,166,4,104,74,128,166,4,104,74,128,166,4,104,74,128,166,4,104,74,128,166,4,104,74,128,166,4,104,74,128,166,4,104,74,128,166,
4,104,74,128,166,4,104,74,128,166,4,104,74,128,166,4,104,74,128,166,4,104,74,128,166,4,104,74,128,166,4,104,74,128,166,4,104,74,128,166,4,104,74,128,166,4,104,74,128,166,4,104,74,128,166,4,104,74,128,166,4,104,74,128,166,4,104,74,128,166,4,104,74,128,
166,4,104,74,128,166,4,104,74,128,166,4,104,202,121,219,7,241,27,103,213,158,119,211,183,0,0,0,0,73,69,78,68,174,66,96,130,0,0 };

const char* samplerx_png = (const char*) temp_binary_data_0;


const char* getNamedResource (const char* resourceNameUTF8, int& numBytes)
{
    unsigned int hash = 0;

    if (resourceNameUTF8 != nullptr)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x3bcf6ada:  numBytes = 275; return samplerx_png;
        default: break;
    }

    numBytes = 0;
    return nullptr;
}

const char* namedResourceList[] =
{
    "samplerx_png"
};

const char* originalFilenames[] =
{
    "samplerx.png"
};

const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8)
{
    for (unsigned int i = 0; i < (sizeof (namedResourceList) / sizeof (namedResourceList[0])); ++i)
    {
        if (namedResourceList[i] == resourceNameUTF8)
            return originalFilenames[i];
    }

    return nullptr;
}

}
