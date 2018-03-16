#include <jscript.h>

#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <thread>

int main(int, char**) {
    std::cout << "--------Running--------" << std::endl;
/*    
    const wchar_t* argv[] = {
        L"test_jscript",
        L"--version"
    };
    jscript::Initialize(2, argv);
    jscript::Uninitilize();
*/    
    const std::string origin = "http://127.0.0.1:8080";
    const std::string externalOrigin = "http://127.0.0.1:8080";
    const std::string executeFile = "D:/TEST/Test.exe";
    const std::string coreFolder = "D:/ODA";
    const std::string nodeFolder = coreFolder + "/web/node_modules";
    
    jscript::Initialize(origin, externalOrigin, executeFile, coreFolder, nodeFolder);
    std::cout << "jscript::Initialize() done" << std::endl;
    
    jscript::result_t res;
    jscript::JSInstance* instance{nullptr};
    res = CreateInstance(&instance);
    if (res != jscript::JS_SUCCESS || !instance) {
        std::cout << "Failed instance create" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    std::cout << "Instance created" << std::endl;
    
    const char* script = "console.log(\"Is work?\");";
    res = RunScriptText(instance, script);
    if (res != jscript::JS_SUCCESS) {
        std::cout << "Failed running script" << std::endl;
        std::exit(EXIT_FAILURE);
    }
        
    std::cout << "Script running, waiting..." << std::endl;
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(20s);
    std::cout << "End waiting" << std::endl;
    
    res = StopInstance(instance);
    if (res != jscript::JS_SUCCESS) {
        std::cout << "Failed instance stop" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    std::cout << "Instance stopped" << std::endl;
        
    jscript::Uninitilize();
    std::cout << "jscript::Uninitilize() done" << std::endl;
    
    return EXIT_SUCCESS;
}
