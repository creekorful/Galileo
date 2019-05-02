#ifndef GALILEO_SHADERFACTORY_H
#define GALILEO_SHADERFACTORY_H

#include <map>

#include "Shader.h"
#include "../IO/Files.h"

// todo remove ptr use ref & instead?

class ShaderFactory
{
public:

    /**
     * Ensure all shader are deleted when factory goes out of scope
     */
    ~ShaderFactory();

    /**
     * Load shader using name and return ptr to built shader if successful
     * @param name shader name
     * @return ptr to built shader or nullptr
     */
    Shader* Load(const std::string& name);

    /**
     * Retrieve shader using given name
     *
     * @param name shader name
     * @return found shader or nullptr
     */
    Shader* Get(const std::string& name);

    /**
     * Manually delete / cleanup shader
     * do not delete shader manually, call this method instead
     *
     * @param name shader name
     */
    void Deinitialize(const std::string& name);

    static ShaderFactory& p()
    {
        static ShaderFactory p;
        return p;
    }

private:
    std::map<std::string, Shader*> _pShaders;
};


#endif //GALILEO_SHADERFACTORY_H
