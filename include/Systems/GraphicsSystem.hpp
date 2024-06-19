#ifndef GRAPHICSSYSTEM_HPP
#define GRAPHICSSYSTEM_HPP
#include "System.hpp"

class GraphicsSystem final : public System
{
public:
    /** Default constructor */
    GraphicsSystem();
    /** Default destructor */
    ~GraphicsSystem() override;
    /** Copy constructor
     *  \param other Object to copy from
     */
    void update() const;
};

#endif // GRAPHICSSYSTEM_HPP
