
#include "Guideline12.h"

#include <cstdlib>
#include <utility>
#include <memory>

using namespace Guideline12;

void Guideline12_main()
{
    auto strategy = std::make_unique<OpenGLStrategy>();

    Circle circle(std::move(strategy));
    circle.Draw();
}
