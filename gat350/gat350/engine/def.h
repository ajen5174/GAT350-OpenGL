#pragma once

#include <sdl.h>
#include <glad/glad.h>
#include <imgui.h>
#include <imGuIZMOquat.h>

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include "../core/core.h"
#include "math/math.h"

#include "../framework/factory.h"
#include "../framework/object_manager.h"

using object_factory_t = Factory<class Object, class Name>;
using resource_manager_t = ObjectManager<class Resource>;
